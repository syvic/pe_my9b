extern uint8_t payload_four_bytes[];
extern uint8_t payload_two_bytes[];
extern uint8_t payload_one_byte[];

void protocol_dump_all_registers() {
  Serial.println("##############################################################");
  for (int i = 0; i < 255; i++) {
    Serial.printf("@@@@@@@@@@ %X @@@@@@@@@", i);
    protocol_compose_send_msg(1, CMD_READ_REG, i, payload_two_bytes);
    delay(200);
  }
  Serial.println("##############################################################");
}


void protocol_compose_send_msg(byte msg_size, byte operation, byte esc_register, byte *payload) {
  int i;
  byte msg[20];
  uint16_t sum = 0;
  uint16_t checksum = 0xFFFF;

  //5A A5 bLen bSrcAddr bDstAddr bCmd bArg bPayload[bLen] wChecksumLE
  msg[0] = 0x5A;
  msg[1] = 0xA5;
  msg[2] = msg_size;
  msg[3] = ADDR_APP2;
  msg[4] = ADDR_ESC;
  msg[5] = operation;
  msg[6] = esc_register;

  sum = (msg[2] + msg[3] + msg[4] + msg[5] + msg[6]);

  for (i = 0; i < msg_size; i++) {
    msg[7 + i] = payload[i];
    sum += payload[i];
  }
  checksum ^= sum;
  msg[7 + msg_size] = checksum & 0xFF;
  msg[8 + msg_size] = checksum >> 8;

  Serial.print("El resultado de la composición es: ");
  for (int i = 0; i < 10; i++) {
    Serial.print(msg[i], HEX);
    Serial.print(" ");
  }
  Serial.printf("\n");

  p_remote_characteristic_rx->writeValue(msg, sizeof msg, false);
}

boolean protocol_check_cmd(int msg_size, uint8_t* msg_data) {
  boolean valid_packet = true;
  int i;
  unsigned int checksum = 0;

  Serial.printf("Longitud mensaje: %d. ", msg_size);
  Serial.printf("Datos: ");
  for (int i = 0; i < msg_size; i++) {
    Serial.printf("%02X ", (char)msg_data[i]);
  }

  Serial.printf("\nAnálisis del paquete\n--------------------\n");
  Serial.printf("  HEADER: ");
  if (msg_data[0] == 0x5A && msg_data[1] == 0xA5) {
    Serial.printf("OK\n");
  }
  else {
    Serial.printf("FAIL\n");
    valid_packet = false;
  }
  Serial.printf("  DATA LENGTH: %d\n", msg_data[2]);
  Serial.printf("  ORIG: %s\n", msg_defs_hash_get_element(msg_data[3], DEVICE_ADDR));
  Serial.printf("  DEST: %s\n", msg_defs_hash_get_element(msg_data[4], DEVICE_ADDR));
  Serial.printf("  CMD: %s\n",  msg_defs_hash_get_element(msg_data[5], CMD));
  Serial.printf("  REG: %s\n",  msg_defs_hash_get_element(msg_data[6], REG));

  for (i = 0; i < msg_data[2]; i++) {
    Serial.printf("  PAYLOAD[%d]: %X\n", i, msg_data[7 + i]);
  }

  //Cálculo del checksum
  for (i = 0; i < 5 + msg_data[2]; i++) checksum += msg_data[2 + i];
  checksum ^= 0xFFFF;

  //Serial.printf("  CHECKSUM CALCULATED: %X\n", checksum);
  //Serial.printf("  CHECKSUM 1 RECEIVED: %X\n", msg_data[7 + msg_data[2]]);
  //Serial.printf("  CHECKSUM 2 RECEIVED: %X\n", msg_data[8 + msg_data[2]]);

  Serial.printf("  CHECKSUM: ");
  if (checksum != (msg_data[7 + msg_data[2]] | (msg_data[8 + msg_data[2]]) << 8 )) {
    Serial.printf("FAIL\n");
    valid_packet = false;
  }
  else {
    Serial.printf("OK\n");
  }
  Serial.printf("--------------------\n\n");

  return valid_packet;

}

ninebot_status_t protocol_process_cmd(int msg_size, uint8_t* msg_data) {
  int i;
  static ninebot_status_t ninebot_status;

  byte cmd = msg_data[5];
  byte reg = msg_data[6];
  byte payload[2];

  if (msg_size == 0) {
    Serial.printf("REPORTANDO\n");
    return ninebot_status;
  }

  Serial.printf("\nProcesando paquete\n--------------------\n");
  Serial.printf("  CMD: %s\n",  msg_defs_hash_get_element(cmd, CMD));
  Serial.printf("  REG: %s\n",  msg_defs_hash_get_element(reg, REG));

  for (i = 0; i < msg_data[2]; i++) {
    Serial.printf("  PAYLOAD[%d]: %X\n", i, msg_data[7 + i]);
  }
  Serial.printf("--------------------\n\n");

  if (cmd == CMD_RES1) {
    switch (reg) {
      case REG_OP_MODE:
        ninebot_status.run_mode = msg_data[7];
        Serial.printf("[PROTO] Tenemos una respuesta de MODO. El valor es: %d\n", ninebot_status.run_mode);
        break;

      case REG_BAT_LVL:
        ninebot_status.bat_level = msg_data[7];
        Serial.printf("[PROTO] Tenemos una respuesta de BATERIA. El valor es: %d\n", ninebot_status.bat_level);
        break;

      case REG_MILEAGE:
        ninebot_status.mileage = msg_data[7] | msg_data[8] << 8 | msg_data[9] << 16 | msg_data[10] << 24;
        Serial.printf("[PROTO] Metros totales recorridos es: %u\n", ninebot_status.mileage);
        break;

      case REG_CURRENT_MILEAGE:
        ninebot_status.current_mileage = msg_data[7] | msg_data[8] << 8;
        Serial.printf("[PROTO] Metros actuales recorridos es: %u\n", ninebot_status.current_mileage);
        break;

      case REG_REMAINING_PREDICTED_MILEAGE:
        ninebot_status.remaining_predicted_mileage = msg_data[7] | msg_data[8] << 8;
        Serial.printf("[PROTO] Decímetros restantes (predicted): %u\n", ninebot_status.remaining_predicted_mileage);
        break;

      case REG_REMAINING_MILEAGE:
        ninebot_status.remaining_mileage = msg_data[7] | msg_data[8] << 8;
        Serial.printf("[PROTO] Decímetros restantes: %u\n", ninebot_status.remaining_mileage);
        break;

      case REG_FRAME_TEMP:
        ninebot_status.frame_temp = msg_data[7] | msg_data[8] << 8;
        Serial.printf("[PROTO] Frame temp: %u\n", ninebot_status.frame_temp);
        break;
      case REG_BAT1_TEMP:
        ninebot_status.bat1_temp = msg_data[7] | msg_data[8] << 8;
        Serial.printf("[PROTO] BAT1 temp: %u\n", ninebot_status.bat1_temp);
        break;
      case REG_BAT2_TEMP:
        ninebot_status.bat2_temp = msg_data[7] | msg_data[8] << 8;
        Serial.printf("[PROTO] BAT2 temp: %u\n", ninebot_status.bat2_temp);
        break;
      case REG_MOS_TEMP:
        ninebot_status.mos_temp = msg_data[7] | msg_data[8] << 8;
        Serial.printf("[PROTO] MOS temp: %u\n", ninebot_status.mos_temp);
        break;
      case REG_BAT_CURRENT:
        ninebot_status.bat_current = msg_data[7] | msg_data[8] << 8;
        Serial.printf("[PROTO] BAT Current: %u\n", ninebot_status.bat_current);
        break;
      case REG_POWER:
        ninebot_status.power = msg_data[7] | msg_data[8] << 8;
        Serial.printf("[PROTO] POWER: %u\n", ninebot_status.power);
        break;

      default:
        Serial.printf("[PROTO] Registro no registrado todavía\n");
        break;
    }
  }

  return ninebot_status;

}



//Cuando el patín repsonde a un mensaje entrega lo siguiente:
//15:42:00.366 -> -> 5A
//15:42:00.366 -> -> A5
//15:42:00.366 -> -> 0
//15:42:00.366 -> -> 20
//15:42:00.366 -> -> 3E
//15:42:00.366 -> -> 5
//15:42:00.366 -> -> 0
//15:42:00.366 -> -> 9C
//15:42:00.366 -> -> FF
