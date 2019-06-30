//TODO: El DAC hace ruido cuando está establecida la conexión BLE... no sé si podrá ser un error de diseño...
//TODO: Siguientes pasos:
// - Conseguir que con la tecla cruceta arriba se envíe el mensaje de petición de firmware, por ejemplo
// - Conseguir que ocn la tecla cruceta abajo se envíe el mensaje de petición de velocidad actual
// - Hacer que este tipo de peticiones se realicen periódicamente y representarlas en la pantalla

#include <odroid_go.h>
#include "BLE.h"

typedef struct ninebot_status_t {
  byte run_mode;
};

void setup() {
  //Inicializamos hashes:
  msg_defs_init_device_addr();
  msg_defs_init_cmd();
  msg_defs_init_reg();
  
  ui_init();
  
  Serial.begin(115200);

  GO.begin();
  GO.lcd.println("\n\n\nGO OK");

  BLEDevice::init("");
  GO.lcd.println("\nBLEDevice OK");

  ble_scan();
  GO.lcd.println("\nBLE Scan OK");
}


void loop() {

  GO.update();

  if (do_connect == true) {
    if (ble_connect_to_server()) {
      Serial.println("Conectados al servidor BLE");
      GO.lcd.println("\nConectados al servidor BLE");
    } else {
      Serial.println("Fallo al establecer conexión con el servidor BLE");
      GO.lcd.println("\nFallo al establecer conexión con el servidor BLE");
    }
    do_connect = false;
  }

  if (connected) {
    keyboard_check();
  }
  else if (do_scan) {
    GO.lcd.println("\nScanning");
    BLEDevice::getScan()->start(0);
  }

}
