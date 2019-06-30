#define PIN_BLUE_LED 2

void ui_init() {
  pinMode(PIN_BLUE_LED, OUTPUT);
}



void ui_update(ninebot_status_t nine_status) {
  Serial.println("Actualizando display");
  //GO.lcd.setTextFont(1);
  //GO.lcd.setTextColor(WHITE);

  GO.lcd.fillRect(150, 90, 170, 22, BLACK);
  GO.lcd.setCursor(150, 90);
  GO.lcd.setTextFont(4);
  switch (nine_status.run_mode) {
    case 0:
      Serial.println("MODO ECO");
      GO.lcd.setTextColor(YELLOW);
      GO.lcd.println("MODE: ECO");
      break;
    case 1:
      Serial.println("MODO KIDS");
      GO.lcd.setTextColor(GREEN);
      GO.lcd.println("MODE: KIDS");
      break;
    case 2:
      Serial.println("MODO SPORT");
      GO.lcd.setTextColor(RED);
      GO.lcd.println("MODE: SPORT");
      break;
  }

  if (0) {  //Patín bloqueado
    GO.lcd.setCursor(170, 0);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(RED);
    GO.lcd.println("LOCK: OFF");
  }

  if (0) { //Patín desbloqueado
    GO.lcd.setCursor(170, 0);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(GREEN);
    GO.lcd.println("LOCK: ON");
  }

  if (0) { //Tail encendido
    GO.lcd.setCursor(25, 0);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(RED);
    GO.lcd.println("TAIL: ON");
  }

  if (0) {
    GO.lcd.setCursor(25, 0);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(GREEN);
    GO.lcd.println("TAIL: OFF");
  }
}
