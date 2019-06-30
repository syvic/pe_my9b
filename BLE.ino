
void ble_scan(){
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
}


static void ble_notify_callback_TX(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  Serial.print("Callback recibida (TX characteristic) ");
  Serial.println(pBLERemoteCharacteristic->getUUID().toString().c_str());

  protocol_receive_cmd(length, pData);
}

bool ble_connect_to_server() {
  Serial.printf("Forming a connection to %s\n", myDevice->getAddress().toString().c_str() );

  BLEClient*  pClient  = BLEDevice::createClient();
  Serial.println(" - Created client");

  pClient->setClientCallbacks(new MyClientCallback());

  pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  Serial.println(" - Connected to server");

  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our service");

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
    pRemoteCharacteristicTX->registerForNotify(ble_notify_callback_TX);
  }

  /*NUEVO*/


  connected = true;

}
