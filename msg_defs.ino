//Tipos de datos
#define DEVICE_ADDR_NO_ITEMS 7
#define CMD_NO_ITEMS 4
#define REG_NO_ITEMS 5

//Comandos
#define CMD_READ_REG 0x01
#define CMD_WRITE_REG 0x02
#define CMD_RES1 0x04
#define CMD_RES2 0x05

enum field_type {
  DEVICE_ADDR = 0,
  CMD = 1,
  REG = 2
};

typedef struct {
  byte key;
  char name[10];
} hash_t;


hash_t device_addr_item[DEVICE_ADDR_NO_ITEMS];
hash_t cmd_item[CMD_NO_ITEMS];
hash_t reg_item[REG_NO_ITEMS];

#define REG_MAGIC_ACK 0x00
#define REG_SERIAL_NO 0x10
#define REG_FW_VER    0x1A
#define REG_OP_MODE   0x75
#define REG_BAT_LVL   0x22

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

}



void msg_defs_init_cmd() {
  //Esto molaría poder hacerlo en preprocesador...
  int idx = 0;

  cmd_item[idx].key = CMD_READ_REG;
  strcpy (cmd_item[0].name, "READ REG");

  cmd_item[idx].key = CMD_WRITE_REG;
  strcpy (cmd_item[idx++].name, "WRITE REG");

  cmd_item[idx].key = CMD_RES1;
  strcpy (cmd_item[idx++].name, "GET RES1?");

  cmd_item[idx].key = CMD_RES2;
  strcpy (cmd_item[idx++].name, "GET RES2?");
}


void msg_defs_init_device_addr() {
  //Esto molaría poder hacerlo en preprocesador...
  int idx = 0;

  device_addr_item[idx].key = 0x20;
  strcpy (device_addr_item[idx++].name, "ESC");

  device_addr_item[idx].key = 0x21;
  strcpy (device_addr_item[idx++].name, "BLE");

  device_addr_item[idx].key = 0x22;
  strcpy (device_addr_item[idx++].name, "BMS1");

  device_addr_item[idx].key = 0x23;
  strcpy (device_addr_item[idx++].name, "BMS2");

  device_addr_item[idx].key = 0x3D;
  strcpy (device_addr_item[idx++].name, "APP1");

  device_addr_item[idx].key = 0x3E;
  strcpy (device_addr_item[idx++].name, "APP2");

  device_addr_item[idx].key = 0x3F;
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
