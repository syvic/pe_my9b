#include <Ticker.h>
Ticker get_status;


uint8_t churro_lee_modo[] =         {0x5A, 0xA5, 0x01, 0x3E, 0x20, 0x01, 0x75, 0x01, 0x29, 0xFF};


void ticker_setup() {
  get_status.attach_ms(500, ticker_get_status);
}


void ticker_get_status() {
  static byte check_idx = 0;
  if (!connected) return;

  switch (check_idx) {
    case 0:
      p_remote_characteristic_rx->writeValue(churro_lee_modo, sizeof churro_lee_modo, false);
      break;
    case 1:
      break;
  }
  check_idx++;

  if (check_idx > 2) check_idx=0;


}
