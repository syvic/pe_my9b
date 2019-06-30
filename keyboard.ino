#define PASO_LETRAS 10
#define INTERVALO_LECTURA 200


void keyboard_check() {
  static unsigned long t_keyboard = 0;
  uint8_t churro_apaga_led[] =        {0x5A, 0xA5, 0x02, 0x3E, 0x20, 0x02, 0x7D, 0x00, 0x00, 0x20, 0xFF};
  uint8_t churro_enciende_led[] =     {0x5A, 0xA5, 0x02, 0x3E, 0x20, 0x02, 0x7D, 0x02, 0x00, 0x1E, 0xFF};
  uint8_t churro_bloquea_patin[] =    {0x5A, 0xA5, 0x02, 0x3E, 0x20, 0x02, 0x70, 0x01, 0x00, 0x2C, 0xFF};
  uint8_t churro_desbloquea_patin[] = {0x5A, 0xA5, 0x02, 0x3E, 0x20, 0x02, 0x71, 0x01, 0x00, 0x2B, 0xFF};
  uint8_t churro_lee_modo[] =         {0x5A, 0xA5, 0x01, 0x3E, 0x20, 0x01, 0x75, 0x01, 0x29, 0xFF};

  if (millis() - t_keyboard > INTERVALO_LECTURA) {
    t_keyboard = millis();

    //Desbloquear patín
    if (GO.BtnStart.isPressed() == 1) {
      p_remote_characteristic_rx->writeValue(churro_desbloquea_patin, sizeof churro_desbloquea_patin, false);
      GO.lcd.setCursor(170, 0);
      GO.lcd.setTextFont(4);
      GO.lcd.setTextColor(RED);
      GO.lcd.println("LOCK: OFF");
      GO.Speaker.tone(7000, 10);
    }

    //Bloquear patín
    if (GO.BtnSelect.isPressed() == 1) {
      p_remote_characteristic_rx->writeValue(churro_bloquea_patin, sizeof churro_bloquea_patin, false);
      GO.lcd.setCursor(170, 0);
      GO.lcd.setTextFont(4);
      GO.lcd.setTextColor(GREEN);
      GO.lcd.println("LOCK: ON");
      GO.Speaker.tone(7000, 10);
    }

    //Encender TAIL
    if (GO.BtnA.isPressed() == 1) {
      p_remote_characteristic_rx->writeValue(churro_enciende_led, sizeof churro_enciende_led, false);
      GO.lcd.setCursor(25, 0);
      GO.lcd.setTextFont(4);
      GO.lcd.setTextColor(RED);
      GO.lcd.println("TAIL: ON");
      GO.Speaker.tone(5000, 10);
    }

    //Apagar TAIL
    if (GO.BtnB.isPressed() == 1) {
      p_remote_characteristic_rx->writeValue(churro_apaga_led, sizeof churro_apaga_led, false);
      GO.lcd.setCursor(25, 0);
      GO.lcd.setTextFont(4);
      GO.lcd.setTextColor(GREEN);
      GO.lcd.println("TAIL: OFF");
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
  GO.lcd.setTextFont(1);
  GO.lcd.setTextColor(WHITE);
}
