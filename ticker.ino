#include <Ticker.h>

Ticker get_status;

//Cálculo de checksums:
//echo "obase=16;ibase=16;xor((1 + 3E + 20 + 02 + FB + 2), FFFF)" | bc -l bin/logic.bc

uint8_t payload_four_bytes[] = {READ_REG_PAYLOAD_4_BYTES};
uint8_t payload_two_bytes[] = {READ_REG_PAYLOAD_2_BYTES};
uint8_t payload_one_byte[] = {READ_REG_PAYLOAD_1_BYTE};

//Comando de GET PIN -> 5A A5 01 3E 20 01 17 06 82 FF me devuelve:
//                      5A A5 01 20 3E 04 17 30 30 30 30 30 30 60 FE.
//Comando de SET PIN -> 5A A5 06 3E 20 02 17 30 31 32 33 34 35 53 FE
//respuesta al set pin-> 5A A5 00 20 3E 05 00 9C FF
//Los comandos de pin funcionan y guardan el pin, pero luego no se ve ningún cambio...

void ticker_setup() {
  get_status.attach_ms(200, ticker_get_status);
}


void ticker_get_status() {
  static byte check_idx = 0;
  if (!connected) return;

  switch (check_idx) {
    case 0:
      protocol_compose_send_msg(1, CMD_READ_REG, REG_OP_MODE, payload_one_byte);
      break;
    case 1:
      protocol_compose_send_msg(1, CMD_READ_REG, REG_BAT_LVL, payload_one_byte);
      break;
    case 2:
      protocol_compose_send_msg(1, CMD_READ_REG, REG_MILEAGE, payload_four_bytes);
      break;
    case 3:
      protocol_compose_send_msg(1, CMD_READ_REG, REG_REMAINING_MILEAGE, payload_two_bytes);
      break;
    case 4:
      protocol_compose_send_msg(1, CMD_READ_REG, REG_REMAINING_PREDICTED_MILEAGE, payload_two_bytes);
      break;
    case 5:
      protocol_compose_send_msg(1, CMD_READ_REG, REG_CURRENT_MILEAGE, payload_two_bytes);
      break;
    case 6:
      ui_update(protocol_process_cmd(0, (uint8_t *)"00000000")); //Al llamar a protocolo_process_cmd con un paquete vacío se obtiene la estructura sin más...
      break;
    default:
      break;
  }
  check_idx++;
  if (check_idx>6) check_idx=0;

}
