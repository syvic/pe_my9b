//TODO: El DAC hace ruido cuando está establecida la conexión BLE... no sé si podrá ser un error de diseño...
//TODO: Siguientes pasos:
// - ¿Cómo hago para consguir que el estado del BLE también sea gestionado por el UI? ¿Dos estructuras pintadas en diferentes sitios de la pantalla?
// - Conseguir que el cacharro esté todo el rato mirando a ver si hay dispositivos disponibles
// - Implementar el comando de petición de Serial y su respuesta:
//    - PETICIÓN: 5A A5 01 3E 20 01 10 0E 81 FF
//    - RESPUEST: 5A A5 0E 20 3E 04 10 4E 32 47 54 51 38 39 38 43 34 37 39 31 21 FC

//IMPORTANTE: EN los comandos de lectura lo que viene después del registro es la cantidad de bytes que queremos leer del mismo

#include <odroid_go.h>
#include "BLE.h"

typedef struct {
  bool ble_connected;
  bool ble_scanning;
} ble_connection_status_t;

typedef struct {
  byte run_mode;
  int bat_level;
  uint32_t mileage;
  uint16_t remaining_mileage;
  uint16_t remaining_predicted_mileage;
  uint16_t current_mileage;
  bool tail_light;
  bool locked;
} ninebot_status_t;

ble_connection_status_t ble_connection_status;

void setup() {
  //Inicializamos hashes:
  msg_defs_init_device_addr();
  msg_defs_init_cmd();
  msg_defs_init_reg();
  
  ui_init();
  
  Serial.begin(115200);

  GO.begin();
  //GO.lcd.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nGO OK");
  GO.lcd.setCursor(0, 240);
  GO.lcd.println("GO OK");

  BLEDevice::init("");

  ble_scan();
  ticker_setup();
}


void loop() {

  GO.update();

  if (do_connect == true) {
    if (ble_connect_to_server()) {
      ble_connection_status.ble_connected=true;
      Serial.println("Conectados al servidor BLE");
    } 
    else {
      ble_connection_status.ble_connected=false;
      Serial.println("Fallo al establecer conexión con el servidor BLE");
    }
    do_connect = false;
  }

  if (connected) {
    keyboard_check();
    ble_connection_status.ble_scanning=false;
  }
  else if (do_scan) {
    ble_connection_status.ble_scanning=true;
    BLEDevice::getScan()->start(0);
  }

}
