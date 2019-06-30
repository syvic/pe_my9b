//5A A5 bLen bSrcAddr bDstAddr bCmd bArg bPayload[bLen] wChecksumLE

enum field_type {
  DEVICE_ADDR = 0,
  CMD = 1,
  REG = 2
};

typedef struct {
  byte key;
  char name[10];
} hash_t;


hash_t device_addr_item[7];

void init_device_addr() {
  //Esto molaría poder hacerlo en preprocesador...
  device_addr_item[0].key = 0x20;
  strcpy (device_addr_item[0].name, "ESC");

  device_addr_item[1].key = 0x21;
  strcpy (device_addr_item[1].name, "BLE");

  device_addr_item[2].key = 0x22;
  strcpy (device_addr_item[2].name, "BMS1");

  device_addr_item[3].key = 0x23;
  strcpy (device_addr_item[3].name, "BMS2");

  device_addr_item[4].key = 0x3D;
  strcpy (device_addr_item[4].name, "APP1");

  device_addr_item[5].key = 0x3E;
  strcpy (device_addr_item[5].name, "APP2");

  device_addr_item[6].key = 0x3F;
  strcpy (device_addr_item[6].name, "APP3");

}

char * hash_get_element(int key, int type) {
  int i;
  int element_count;

  switch (type) {
    case DEVICE_ADDR:
      element_count = 7;
      break;
    case CMD:
      element_count = 3;
      break;
    case REG:
      element_count = 20;
      break;
  }

  for (i = 0; i < element_count; i++) {
    if (key == device_addr_item[i].key) {
      return device_addr_item[i].name;
    }
  }
  return (char*) "NOT FOUND";
}


void protocol_receive_cmd(int msg_size, uint8_t* msg_data) {
  int i;
  int checksum;
  
  Serial.print("Longitud mensaje ");
  Serial.println(msg_size);
  Serial.println("Datos: ");
  for (int i = 0; i < msg_size; i++) {
    Serial.print("-> " );
    Serial.println((char)msg_data[i], HEX);
  }

  Serial.println("Análisis del paquete\n----------------");
  if (msg_data[0] == 0x5A && msg_data[1] == 0xA5) {
    Serial.println("HEADER: OK");
  }
  else {
    Serial.println("HEADER: FAIL");
  }
  Serial.printf("DATA LENGTH: %d\n", msg_data[2]);
  Serial.printf("ORIG: %s\n", hash_get_element(msg_data[3], DEVICE_ADDR));
  Serial.printf("DEST: %s\n", hash_get_element(msg_data[4], DEVICE_ADDR));
  Serial.printf("CMD: %d (1=read, 2=write, 5=¿respuesta?)\n", msg_data[5]);
  //Serial.printf("REG: %d", cmd_list[msg_data[6]]\n);
  for (i=0; i<msg_data[2]; i++){
    Serial.printf("PAYLOAD[%d]: %X\n", i, msg_data[7+i]);
  }
  for (i=0; i< 5 + msg_data[2]; i++){
    checksum += msg_data[2+i];
  }
  Serial.printf("CHECKSUM CALCULATED: %X\n", checksum);
  Serial.printf("CHECKSUM 1 RECEIVED: %X\n", msg_data[6 + msg_data[2]]);
  Serial.printf("CHECKSUM 2 RECEIVED: %X\n", msg_data[7 + msg_data[2]]);

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
