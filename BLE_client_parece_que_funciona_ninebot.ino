//TODO: El DAC hace ruido cuando está establecida la conexión BLE... no sé si podrá ser un error de diseño...

#include <odroid_go.h>
#include "BLE.h"

void setup() {
  //Inicializamos hashes:
  init_device_addr();
  
  Serial.begin(115200);
  GO.begin();
  GO.lcd.println("\n\n\nGO OK");

  BLEDevice::init("");
  GO.lcd.println("\nBLEDevice OK");

  BLEscan();
  GO.lcd.println("\nBLE Scan OK");
}


void loop() {

  GO.update();

  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
      GO.lcd.println("\nConnected to BLE Server");
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
      GO.lcd.println("\nFailed to connect to BLE Server");
    }
    doConnect = false;
  }

  if (connected) {
    keyboard_check();
  }
  else if (doScan) {
    GO.lcd.println("\nScanning");
    BLEDevice::getScan()->start(0);  // this is just example to start scan after disconnect, most likely there is better way to do it in arduino
  }

}
