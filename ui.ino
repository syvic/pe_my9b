#define PIN_BLUE_LED 2

#define LINE_WIDTH 25
#define COLUMN_SEPARATOR 150

void ui_init() {
  pinMode(PIN_BLUE_LED, OUTPUT);
}


void ui_footer_msg(char * msg) {
  GO.lcd.fillRect(0, 225, 360, 25, BLACK);
  GO.lcd.setCursor(0, 230);
  GO.lcd.printf(msg);
}


void ui_update(ninebot_status_t nine_status) {
  Serial.println("Actualizando display");

  /*
     AUTONOMÍA
  */
  GO.lcd.fillRect(0, LINE_WIDTH * 0, COLUMN_SEPARATOR - 1, LINE_WIDTH, BLACK);
  GO.lcd.setCursor(0, LINE_WIDTH * 0);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(GREEN);
  GO.lcd.print("RNGE: ");
  GO.lcd.setCursor(80, LINE_WIDTH * 0);
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.remaining_mileage / 100.0);

  /*
     ODÓMETRO
  */
  GO.lcd.fillRect(COLUMN_SEPARATOR, LINE_WIDTH * 0, 170, LINE_WIDTH, BLACK);
  GO.lcd.setCursor(COLUMN_SEPARATOR, LINE_WIDTH * 0);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(YELLOW);
  GO.lcd.print("ODO: ");
  GO.lcd.setCursor(80 + 150, LINE_WIDTH * 0);
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.mileage / 1000.0);


  /*
     AUTONOMÍA (OTRO CÁLCULO). ESTE ES IGUAL QUE EL OTRO PERO CON UN FACTOR DEL 80% (Corregido al 40%)
  */
  GO.lcd.fillRect(0, LINE_WIDTH * 1, COLUMN_SEPARATOR - 1, LINE_WIDTH, BLACK);
  GO.lcd.setCursor(0, LINE_WIDTH * 1);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(GREEN);
  GO.lcd.print("RNG2: ");
  GO.lcd.setCursor(80, LINE_WIDTH * 1);
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.remaining_mileage / 250.0); //Convertimos a metros y aplicamos el factor real de conversión del 40% obtenidos empíricamente con una carga promedio de 90Kg. (100Kg 50% del tiempo y 80Kg 50% del tiempo)

  /*
     CURRENT MILEAGE
  */
  GO.lcd.fillRect(150, LINE_WIDTH * 1, 170, LINE_WIDTH, BLACK);
  GO.lcd.setCursor(150, LINE_WIDTH * 1);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(YELLOW);
  GO.lcd.print("CUR: ");
  GO.lcd.setCursor(80 + 150, LINE_WIDTH * 1); //90 es mucho
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.current_mileage / 100.0);

  /**********************************************NUEVO**********************************************/
  /*
     BAT CURRENT
  */
  GO.lcd.fillRect(0, LINE_WIDTH * 2, COLUMN_SEPARATOR - 1, LINE_WIDTH, BLACK);
  GO.lcd.setCursor(0, LINE_WIDTH * 2);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(GREEN);
  GO.lcd.print("BAT I: ");
  GO.lcd.setCursor(80, LINE_WIDTH * 2);
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.bat_current);
  GO.lcd.print("A");
  

  /*
     POWER
  */
  GO.lcd.fillRect(150, LINE_WIDTH * 2, 170, LINE_WIDTH, BLACK);
  GO.lcd.setCursor(150, LINE_WIDTH * 2);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(YELLOW);
  GO.lcd.print("PWR: ");
  GO.lcd.setCursor(80 + 150, LINE_WIDTH * 2); //90 es mucho
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.power);
  GO.lcd.print("W");
  


  /**********************************************NUEVO**********************************************/

  /*
     ESTADO DE LA BATERÍA
  */
  GO.lcd.fillRect(0, LINE_WIDTH * 4, COLUMN_SEPARATOR - 1, LINE_WIDTH, BLACK);
  GO.lcd.setCursor(0, LINE_WIDTH * 4);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(GREEN);
  GO.lcd.print("BAT: ");
  GO.lcd.setTextColor(WHITE);
  GO.lcd.setCursor(80, LINE_WIDTH * 4); //90 es mucho
  GO.lcd.print(nine_status.bat_level);
  GO.lcd.print("%");


  /*
     MODO DE FUNCIONAMIENTO
  */
  GO.lcd.fillRect(COLUMN_SEPARATOR, LINE_WIDTH * 4, 170, LINE_WIDTH, BLACK);
  GO.lcd.setCursor(COLUMN_SEPARATOR, LINE_WIDTH * 4);
  GO.lcd.setTextFont(4);
  GO.lcd.setTextColor(YELLOW);
  GO.lcd.print("MODE: ");
  GO.lcd.setCursor(80 + 150, LINE_WIDTH * 4); //90 es mucho
  switch (nine_status.run_mode) {
    case 0:
      GO.lcd.setTextColor(GREEN);
      GO.lcd.print("ECO");
      break;
    case 1:
      GO.lcd.setTextColor(WHITE);
      GO.lcd.print("KIDS");
      break;
    case 2:
      GO.lcd.setTextColor(RED);
      GO.lcd.println("SPORT");
      break;
  }

  /*
     TEMPERATURAS
  */
  GO.lcd.fillRect(0, LINE_WIDTH * 7, 360, LINE_WIDTH, BLACK);
  GO.lcd.setCursor(0, LINE_WIDTH * 7);
  GO.lcd.setTextFont(2);
  GO.lcd.print("(TEMP) ");

  GO.lcd.setTextColor(GREEN);
  GO.lcd.print("FR: ");
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.frame_temp/10.0);

  GO.lcd.setTextColor(GREEN);
  GO.lcd.print(" B1: ");
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.bat1_temp/10.0);

  GO.lcd.setTextColor(GREEN);
  GO.lcd.print(" B2: ");
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.bat2_temp/10.0);

  GO.lcd.setTextColor(GREEN);
  GO.lcd.print(" MOS: ");
  GO.lcd.setTextColor(WHITE);
  GO.lcd.print(nine_status.mos_temp/10.0);

  /*
     BLOQUEO Y TAIL
  */
  GO.lcd.fillRect(0, LINE_WIDTH * 8, 350, LINE_WIDTH, ORANGE);

  if (nbot_locked) { //ÑAPA: debería ser nine_status.locked) {  //Patín bloqueado
    GO.lcd.setCursor(20, LINE_WIDTH * 8 + 2);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(RED);
    GO.lcd.println("LOCK: ON");
  }
  else {
    GO.lcd.setCursor(20, LINE_WIDTH * 8 + 2);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(GREEN);
    GO.lcd.println("LOCK: OFF");
  }

  if (nbot_tail_light) { //ÑAPA: debería ser nine_status.tail_light) { //Tail encendido
    GO.lcd.setCursor(170, LINE_WIDTH * 8 + 2);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(GREEN);
    GO.lcd.println("TAIL: ON");
  }
  else {
    GO.lcd.setCursor(170, LINE_WIDTH * 8 + 2);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(RED);
    GO.lcd.println("TAIL: OFF");
  }
}
