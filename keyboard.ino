#define PASO_LETRAS 10
#define INTERVALO_LECTURA 200

bool nbot_tail_light=false;
bool nbot_locked=false;

void keyboard_check() {
  static unsigned long t_keyboard = 0;
  uint8_t churro_chassis1_color[]=    {0x5A, 0xA5, 0x04, 0x3E, 0x20, 0x02, 0xC8, 0x25, 0x25, 0x20, 0x20, 0x11, 0xFF};

  uint8_t payload_write_zero_in_two_bytes[] = {0x00, 0x00};
  uint8_t payload_write_one_in_two_bytes[]  = {0x01, 0x00};
  uint8_t payload_write_two_in_two_bytes[]  = {0x02, 0x00};
  

  if (millis() - t_keyboard > INTERVALO_LECTURA) {
    t_keyboard = millis();

    //Desbloquear patín
    if (GO.BtnStart.isPressed() == 1) {
      protocol_compose_send_msg(2, CMD_WRITE_REG, REG_UNLOCK, payload_write_one_in_two_bytes);
      nbot_locked=false; //ESTO ES UNA ÑAPA. MODIFICAR ESTO LEYENDO EL REGISTRO CORRESPONDIENTE
      GO.Speaker.tone(7000, 10);
    }

    //Bloquear patín
    if (GO.BtnSelect.isPressed() == 1) {
      protocol_compose_send_msg(2, CMD_WRITE_REG, REG_LOCK, payload_write_one_in_two_bytes);
      nbot_locked=true; //ESTO ES UNA ÑAPA. MODIFICAR ESTO LEYENDO EL REGISTRO CORRESPONDIENTE
      GO.Speaker.tone(7000, 10);
    }

    //Encender TAIL
    if (GO.BtnA.isPressed() == 1) {
      protocol_compose_send_msg(2, CMD_WRITE_REG, REG_TAIL_LED, payload_write_two_in_two_bytes);
      nbot_tail_light=true; //ESTO ES UNA ÑAPA. MODIFICAR ESTO LEYENDO EL REGISTRO CORRESPONDIENTE
      GO.Speaker.tone(5000, 10);
    }

    //Apagar TAIL
    if (GO.BtnB.isPressed() == 1) {
      protocol_compose_send_msg(2, CMD_WRITE_REG, REG_TAIL_LED, payload_write_zero_in_two_bytes);
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
      GO.Speaker.tone(200, 5);
    }

    if (GO.JOY_Y.isAxisPressed() == 1) { //Tecla abajo
      GO.Speaker.tone(200, 5);
    }

  }
}
