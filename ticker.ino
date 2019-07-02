#include <Ticker.h>
Ticker get_status;

//Cálculo de checksums:
//echo "obase=16;ibase=16;xor((1 + 3E + 20 + 02 + FB + 2), FFFF)" | bc -l bin/logic.bc

uint8_t churro_lee_modo[] =                         {0x5A, 0xA5, 0x01, 0x3E, 0x20, 0x01, 0x75, 0x01, 0x29, 0xFF};
uint8_t churro_lee_batt[] =                         {0x5A, 0xA5, 0x01, 0x3E, 0x20, 0x01, 0x22, 0x01, 0x7C, 0xFF}; //Puede ser el 22 o el B4
uint8_t churro_lee_mileage[] =                      {0x5A, 0xA5, 0x01, 0x3E, 0x20, 0x01, 0x29, 0x04, 0x72, 0xFF};
uint8_t churro_lee_remaining_mileage[] =            {0x5A, 0xA5, 0x01, 0x3E, 0x20, 0x01, 0x25, 0x2, 0x78, 0xFF};
uint8_t churro_lee_remaining_predicted_mileage[] =  {0x5A, 0xA5, 0x01, 0x3E, 0x20, 0x01, 0x24, 0x2, 0x79, 0xFF};
uint8_t churro_lee_current_mileage[] =              {0x5A, 0xA5, 0x01, 0x3E, 0x20, 0x01, 0x2F, 0x2, 0x6E, 0xFF};

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
      p_remote_characteristic_rx->writeValue(churro_lee_modo, sizeof churro_lee_modo, false);
      break;
    case 1:
      p_remote_characteristic_rx->writeValue(churro_lee_batt, sizeof churro_lee_batt, false);
      break;
    case 2:
      p_remote_characteristic_rx->writeValue(churro_lee_mileage, sizeof churro_lee_mileage, false);
      break;
    case 3:
      p_remote_characteristic_rx->writeValue(churro_lee_remaining_mileage, sizeof churro_lee_remaining_mileage, false);
      break;
    case 4:
      p_remote_characteristic_rx->writeValue(churro_lee_remaining_predicted_mileage, sizeof churro_lee_remaining_predicted_mileage, false);
      break;
    case 5:
      p_remote_characteristic_rx->writeValue(churro_lee_current_mileage, sizeof churro_lee_current_mileage, false);
      break;
    case 6:
      ui_update(protocol_process_cmd(0, (uint8_t *)"00000000")); //Al llamar a protocolo_process_cmd con un paquete vacío se obtiene la estructura sin más...
      break;
  }
  check_idx++;

  if (check_idx > 6) check_idx = 0;


}
