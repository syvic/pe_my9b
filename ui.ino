#define PIN_BLUE_LED 2

void ui_init(){
  pinMode(PIN_BLUE_LED, OUTPUT);
}



void ui_update(ninebot_status_t nine_status){
  Serial.println("Actualizando display");
}
