

enum field_type {
  DEVICE_ADDR = 0,
  CMD = 1,
  REG = 2
};

typedef struct {
  byte key;
  char name[30];
} hash_t;


hash_t device_addr_item[DEVICE_ADDR_NO_ITEMS];
hash_t cmd_item[CMD_NO_ITEMS];
hash_t reg_item[REG_NO_ITEMS];



void msg_defs_init_reg() {
  //Esto molaría poder hacerlo en preprocesador...
  int idx = 0;

  reg_item[idx].key = REG_MAGIC_ACK;
  strcpy (reg_item[idx++].name, "MAGIC ACK");

  reg_item[idx].key = REG_SERIAL_NO;
  strcpy (reg_item[idx++].name, "SERIALNO");

  reg_item[idx].key = REG_FW_VER;
  strcpy (reg_item[idx++].name, "FW VER");

  reg_item[idx].key = REG_OP_MODE;
  strcpy (reg_item[idx++].name, "OP MODE");

  reg_item[idx].key = REG_BAT_LVL;
  strcpy (reg_item[idx++].name, "BAT LEVEL");

  reg_item[idx].key = REG_MILEAGE;
  strcpy (reg_item[idx++].name, "MILEAGE");

  reg_item[idx].key = REG_REMAINING_MILEAGE;
  strcpy (reg_item[idx++].name, "REMAINING MILEAGE");

  reg_item[idx].key = REG_REMAINING_PREDICTED_MILEAGE;
  strcpy (reg_item[idx++].name, "REMAINING PREDICTED MILEAGE");

  reg_item[idx].key = REG_CURRENT_MILEAGE;
  strcpy (reg_item[idx++].name, "CURRENT MILEAGE");

  reg_item[idx].key = REG_FRAME_TEMP;
  strcpy (reg_item[idx++].name, "FRAME TEMP");

  reg_item[idx].key = REG_BAT1_TEMP;
  strcpy (reg_item[idx++].name, "BAT1 TEMP");

  reg_item[idx].key = REG_BAT2_TEMP;
  strcpy (reg_item[idx++].name, "BAT2 TEMP");

  reg_item[idx].key = REG_MOS_TEMP;
  strcpy (reg_item[idx++].name, "MOS TEMP");

  reg_item[idx].key = REG_BAT_CURRENT;
  strcpy (reg_item[idx++].name, "BAT CURRENT");

  reg_item[idx].key = REG_POWER;
  strcpy (reg_item[idx++].name, "POWER");
}



void msg_defs_init_cmd() {
  //Esto molaría poder hacerlo en preprocesador...
  int idx = 0;

  cmd_item[idx].key = CMD_READ_REG;
  strcpy (cmd_item[0].name, "READ REG");

  cmd_item[idx].key = CMD_WRITE_REG;
  strcpy (cmd_item[idx++].name, "WRITE REG");

  cmd_item[idx].key = CMD_RES1;
  strcpy (cmd_item[idx++].name, "GOT QUERY RESPONSE");

  cmd_item[idx].key = CMD_RES2;
  strcpy (cmd_item[idx++].name, "GET RES2?");
}


void msg_defs_init_device_addr() {
  //Esto molaría poder hacerlo en preprocesador...
  int idx = 0;

  device_addr_item[idx].key = ADDR_ESC;
  strcpy (device_addr_item[idx++].name, "ESC");

  device_addr_item[idx].key = ADDR_BLE;
  strcpy (device_addr_item[idx++].name, "BLE");

  device_addr_item[idx].key = ADDR_BMS1;
  strcpy (device_addr_item[idx++].name, "BMS1");

  device_addr_item[idx].key = ADDR_BMS2;
  strcpy (device_addr_item[idx++].name, "BMS2");

  device_addr_item[idx].key = ADDR_APP1;
  strcpy (device_addr_item[idx++].name, "APP1");

  device_addr_item[idx].key = ADDR_APP2;
  strcpy (device_addr_item[idx++].name, "APP2");

  device_addr_item[idx].key = ADDR_APP3;
  strcpy (device_addr_item[idx++].name, "APP3");

}

char * msg_defs_hash_get_element(int key, int type) {
  int i;
  int element_count;
  hash_t *hash_table;

  switch (type) {
    case DEVICE_ADDR:
      element_count = DEVICE_ADDR_NO_ITEMS;
      hash_table = device_addr_item;
      break;
    case CMD:
      element_count = CMD_NO_ITEMS;
      hash_table = cmd_item;
      break;
    case REG:
      element_count = REG_NO_ITEMS;
      hash_table = reg_item;
      break;
  }

  for (i = 0; i < element_count; i++) {
    if (key == hash_table[i].key) {
      return hash_table[i].name;
    }
  }
  return (char*) "NOT FOUND";
}
