
void BLEscan(){
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
}


static void notifyCallbackTX(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  Serial.print("Notify callback for characteristic TX ");
  Serial.println(pBLERemoteCharacteristic->getUUID().toString().c_str());

  protocol_receive_cmd(length, pData);
}


static void notifyCallbackRX(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  Serial.print("Notify callback for characteristic RX ");
  Serial.println(pBLERemoteCharacteristic->getUUID().toString().c_str());
  Serial.print(" of data length ");
  Serial.println(length);
  Serial.print("data: ");
  Serial.println((char*)pData);
}



bool connectToServer() {
  Serial.print("Forming a connection to ");
  Serial.println(myDevice->getAddress().toString().c_str());

  BLEClient*  pClient  = BLEDevice::createClient();
  Serial.println(" - Created client");

  pClient->setClientCallbacks(new MyClientCallback());

  // Connect to the remove BLE Server.
  pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  Serial.println(" - Connected to server");

  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our service");

  // Obtain a reference to the TX characteristic in the service of the remote BLE server.
  pRemoteCharacteristicRX = pRemoteService->getCharacteristic(charUUID_RX);
  
  
  if (pRemoteCharacteristicRX == nullptr) {
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(charUUID_RX.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our characteristic: RX");

  // Read the value of the characteristic.
  if (pRemoteCharacteristicRX->canRead()) {
    std::string value = pRemoteCharacteristicRX->readValue();
    Serial.print("The characteristic value was: ");
    Serial.println(value.c_str());
  }

  if (pRemoteCharacteristicRX->canNotify()) {
    Serial.println("Habilitando notificaciones RX");
    pRemoteCharacteristicRX->registerForNotify(notifyCallbackRX);
  }
  
  /*NUEVO*/
  pRemoteCharacteristicTX = pRemoteService->getCharacteristic(charUUID_TX);

  if (pRemoteCharacteristicTX == nullptr) {
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(charUUID_TX.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our characteristic: TX");

  // Read the value of the characteristic.
  if (pRemoteCharacteristicTX->canRead()) {
    std::string value2 = pRemoteCharacteristicTX->readValue();
    Serial.print("The characteristic value was: ");
    Serial.println(value2.c_str());
  }

  if (pRemoteCharacteristicTX->canNotify()) {
    Serial.println("Habilitando notificaciones TX");
    pRemoteCharacteristicTX->registerForNotify(notifyCallbackTX);
  }

  /*NUEVO*/


  connected = true;

}
