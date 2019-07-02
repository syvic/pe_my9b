#define PIN_BLUE_LED 2

void ui_init() {
  pinMode(PIN_BLUE_LED, OUTPUT);
}



void ui_update(ninebot_status_t nine_status) {
  Serial.println("Actualizando display");
  //GO.lcd.setTextFont(1);
  //GO.lcd.setTextColor(WHITE);


  /*
     MODO DE FUNCIONAMIENTO
  */
  GO.lcd.fillRect(150, 100, 170, 25, BLACK);
  GO.lcd.setCursor(150, 100);
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


  /*
     ESTADO DE LA BATERÍA
  */
  GO.lcd.fillRect(0, 100, 149, 25, BLACK);
  GO.lcd.setCursor(0, 100);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print("BAT (%): ");
  GO.lcd.print(nine_status.bat_level);

  /*
     AUTONOMÍA
  */
  GO.lcd.fillRect(0, 0, 149, 25, BLACK);
  GO.lcd.setCursor(0, 0);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(GREEN);
  GO.lcd.print("RNGE: ");
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.remaining_mileage / 100.0);

  /*
     ODÓMETRO
  */
  GO.lcd.fillRect(150, 0, 170, 25, BLACK);
  GO.lcd.setCursor(150, 0);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(YELLOW);
  GO.lcd.print("ODO: ");
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.mileage / 1000.0);


  /*
     AUTONOMÍA (OTRO CÁLCULO)
  */
  GO.lcd.fillRect(0, 25, 149, 25, BLACK);
  GO.lcd.setCursor(0, 25);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(GREEN);
  GO.lcd.print("RNG2: ");
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.remaining_predicted_mileage / 100.0);

  /*
     CURRENT MILEAGE
  */
  GO.lcd.fillRect(150, 25, 170, 25, BLACK);
  GO.lcd.setCursor(150, 25);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(YELLOW);
  GO.lcd.print("CUR: ");
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.current_mileage / 1000.0);

  //BLOQUEO Y TAIL
  GO.lcd.fillRect(0, 215, 350, 25, ORANGE);

  if (nbot_locked) { //ÑAPA: debería ser nine_status.locked) {  //Patín bloqueado
    GO.lcd.setCursor(0, 217);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(RED);
    GO.lcd.println("LOCK: ON");
  }
  else {
    GO.lcd.setCursor(0, 217);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(GREEN);
    GO.lcd.println("LOCK: OFF");
  }

  if (nbot_tail_light) { //ÑAPA: debería ser nine_status.tail_light) { //Tail encendido
    GO.lcd.setCursor(170, 217);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(GREEN);
    GO.lcd.println("TAIL: ON");
  }
  else {
    GO.lcd.setCursor(170, 217);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(RED);
    GO.lcd.println("TAIL: OFF");
  }
}
