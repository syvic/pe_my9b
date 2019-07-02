#define PASO_LETRAS 10
#define INTERVALO_LECTURA 200

bool nbot_tail_light=false;
bool nbot_locked=false;

void keyboard_check() {
  static unsigned long t_keyboard = 0;
  uint8_t churro_apaga_led[] =        {0x5A, 0xA5, 0x02, 0x3E, 0x20, 0x02, 0x7D, 0x00, 0x00, 0x20, 0xFF};
  uint8_t churro_enciende_led[] =     {0x5A, 0xA5, 0x02, 0x3E, 0x20, 0x02, 0x7D, 0x02, 0x00, 0x1E, 0xFF};
  uint8_t churro_bloquea_patin[] =    {0x5A, 0xA5, 0x02, 0x3E, 0x20, 0x02, 0x70, 0x01, 0x00, 0x2C, 0xFF};
  uint8_t churro_desbloquea_patin[] = {0x5A, 0xA5, 0x02, 0x3E, 0x20, 0x02, 0x71, 0x01, 0x00, 0x2B, 0xFF};
  uint8_t churro_chassis1_color[]=    {0x5A, 0xA5, 0x04, 0x3E, 0x20, 0x02, 0xC8, 0x25, 0x25, 0x20, 0x20, 0x11, 0xFF};
  uint8_t churro_lee_modo[] =         {0x5A, 0xA5, 0x01, 0x3E, 0x20, 0x01, 0x75, 0x01, 0x29, 0xFF};

  if (millis() - t_keyboard > INTERVALO_LECTURA) {
    t_keyboard = millis();

    //Desbloquear patín
    if (GO.BtnStart.isPressed() == 1) {
      p_remote_characteristic_rx->writeValue(churro_desbloquea_patin, sizeof churro_desbloquea_patin, false);
      nbot_locked=false; //ESTO ES UNA ÑAPA. MODIFICAR ESTO LEYENDO EL REGISTRO CORRESPONDIENTE
      GO.Speaker.tone(7000, 10);
    }

    //Bloquear patín
    if (GO.BtnSelect.isPressed() == 1) {
      p_remote_characteristic_rx->writeValue(churro_bloquea_patin, sizeof churro_bloquea_patin, false);
      nbot_locked=true; //ESTO ES UNA ÑAPA. MODIFICAR ESTO LEYENDO EL REGISTRO CORRESPONDIENTE
      GO.Speaker.tone(7000, 10);
    }

    //Encender TAIL
    if (GO.BtnA.isPressed() == 1) {
      p_remote_characteristic_rx->writeValue(churro_enciende_led, sizeof churro_enciende_led, false);
      nbot_tail_light=true; //ESTO ES UNA ÑAPA. MODIFICAR ESTO LEYENDO EL REGISTRO CORRESPONDIENTE
      GO.Speaker.tone(5000, 10);
    }

    //Apagar TAIL
    if (GO.BtnB.isPressed() == 1) {
      p_remote_characteristic_rx->writeValue(churro_apaga_led, sizeof churro_apaga_led, false);
      nbot_tail_light=false; //ESTO ES UNA ÑAPA. MODIFICAR ESTO LEYENDO EL REGISTRO CORRESPONDIENTE
      GO.Speaker.tone(4000, 10);
    }

    if (GO.JOY_X.isAxisPressed() == 2) { //Tecla izquierda
      GO.Speaker.tone(300, 10);
    }

    if (GO.JOY_X.isAxisPressed() == 1) { //Tecla derecha
      GO.Speaker.tone(300, 10);
    }

    if (GO.JOY_Y.isAxisPressed() == 2) { //Tecla arriba
      p_remote_characteristic_rx->writeValue(churro_lee_modo, sizeof churro_lee_modo, false);
      GO.Speaker.tone(200, 5);
    }

    if (GO.JOY_Y.isAxisPressed() == 1) { //Tecla abajo
      GO.Speaker.tone(200, 5);
    }

  }
}
