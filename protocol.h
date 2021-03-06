//Tipos de datos
#define DEVICE_ADDR_NO_ITEMS  7
#define CMD_NO_ITEMS          4
#define REG_NO_ITEMS          15

//Comandos
#define CMD_READ_REG      0x01
#define CMD_WRITE_REG     0x02
#define CMD_RES1          0x04
#define CMD_RES2          0x05

//Direcciones de dispositivos
#define ADDR_ESC          0x20
#define ADDR_BLE          0x21
#define ADDR_BMS1         0x22
#define ADDR_BMS2         0x23
#define ADDR_APP1         0x3D
#define ADDR_APP2         0x3E
#define ADDR_APP3         0x3F

//Tamaños de payload de dato en lectura
#define READ_REG_PAYLOAD_1_BYTE           0x01
#define READ_REG_PAYLOAD_2_BYTES          0x02
#define READ_REG_PAYLOAD_4_BYTES          0x04

//Registros
#define REG_MAGIC_ACK                     0x00
#define REG_SERIAL_NO                     0x10
#define REG_FW_VER                        0x1A
#define REG_BAT_LVL                       0x22
#define REG_MILEAGE                       0x29
#define REG_REMAINING_PREDICTED_MILEAGE   0x24 //Este mensaje sobra. Es el mismo que el 25 pero multiplicado por 0.8
#define REG_REMAINING_MILEAGE             0x25 
#define REG_CURRENT_MILEAGE               0x2F
#define REG_FRAME_TEMP                    0x3E
#define REG_BAT1_TEMP                     0x3F
#define REG_BAT2_TEMP                     0x40
#define REG_MOS_TEMP                      0x41
#define REG_BAT_CURRENT                   0x49
#define REG_LOCK                          0x70 
#define REG_UNLOCK                        0x71
#define REG_OP_MODE                       0x75
#define REG_TAIL_LED                      0x7D
#define REG_POWER                         0xBD
