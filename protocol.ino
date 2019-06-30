//5A A5 bLen bSrcAddr bDstAddr bCmd bArg bPayload[bLen] wChecksumLE




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
  ninebot_status_t ninebot_status;

  Serial.printf("\nProcesando paquete\n--------------------\n");
  Serial.printf("  CMD: %s\n",  msg_defs_hash_get_element(msg_data[5], CMD));
  Serial.printf("  REG: %s\n",  msg_defs_hash_get_element(msg_data[6], REG));

  for (i = 0; i < msg_data[2]; i++) {
    Serial.printf("  PAYLOAD[%d]: %X\n", i, msg_data[7 + i]);
  }
  Serial.printf("--------------------\n\n");

  ninebot_status.run_mode=4;

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
