#include "BLEDevice.h"

static BLEUUID serviceUUID("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
static BLEUUID charUUID_RX("6E400002-B5A3-F393-E0A9-E50E24DCCA9E"); //Aquí es donde escribimos
static BLEUUID charUUID_TX("6E400003-B5A3-F393-E0A9-E50E24DCCA9E"); //Aquí es de donde leemos

static boolean do_connect = false;
static boolean connected = false;
static boolean do_scan = false;

static BLERemoteCharacteristic* p_remote_characteristic_rx;
static BLERemoteCharacteristic* p_remote_characteristic_tx;
static BLEAdvertisedDevice* patinete;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.print("BLE Advertised Device found: ");
      Serial.println(advertisedDevice.toString().c_str());

      if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {
        BLEDevice::getScan()->stop();
        patinete = new BLEAdvertisedDevice(advertisedDevice);
        do_connect = true;
        do_scan = true;
      }
    }
};



class MyClientCallback : public BLEClientCallbacks {
    void onConnect(BLEClient* pclient) {
      //connected = true;
      Serial.println(">>>>>>>>>>>>>>>>>>> onConnect");
    }

    void onDisconnect(BLEClient* pclient) {
      connected = false;
      Serial.println(">>>>>>>>>>>>>>>>>>> onDisconnect");
    }
};
