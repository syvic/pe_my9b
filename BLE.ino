
void ble_scan() {
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
}


static void ble_notify_callback_TX(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  ninebot_status_t ninebot_stat;
  Serial.print("Callback recibida (TX characteristic) ");
  Serial.println(pBLERemoteCharacteristic->getUUID().toString().c_str());

  if (protocol_check_cmd(length, pData)) {
    ninebot_stat = protocol_process_cmd(length, pData);
    //SYV AQUI FUNCIONABA BIEN PERO CON UN POCO DE FLICKERING DE LA PANTALLA: ui_update(ninebot_stat);
  }

}

bool ble_connect_to_server() {
  Serial.printf("Forming a connection to %s\n", patinete->getAddress().toString().c_str() );

  BLEClient* p_client  = BLEDevice::createClient();
  Serial.println(" - Created client");

  p_client->setClientCallbacks(new MyClientCallback());

  p_client->connect(patinete);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  Serial.println(" - Connected to server");

  BLERemoteService* pRemoteService = p_client->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    p_client->disconnect();
    return false;
  }
  Serial.println(" - Found our service");

  p_remote_characteristic_rx = pRemoteService->getCharacteristic(charUUID_RX);

  if (p_remote_characteristic_rx == nullptr) {
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(charUUID_RX.toString().c_str());
    p_client->disconnect();
    return false;
  }
  Serial.println(" - Found our characteristic: RX");

  // Read the value of the characteristic.
  if (p_remote_characteristic_rx->canRead()) {
    std::string value = p_remote_characteristic_rx->readValue();
    Serial.print("The characteristic value was: ");
    Serial.println(value.c_str());
  }

  p_remote_characteristic_tx = pRemoteService->getCharacteristic(charUUID_TX);

  if (p_remote_characteristic_tx == nullptr) {
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(charUUID_TX.toString().c_str());
    p_client->disconnect();
    return false;
  }
  Serial.println(" - Found our characteristic: TX");

  // Read the value of the characteristic.
  if (p_remote_characteristic_tx->canRead()) {
    std::string value2 = p_remote_characteristic_tx->readValue();
    Serial.print("The characteristic value was: ");
    Serial.println(value2.c_str());
  }

  if (p_remote_characteristic_tx->canNotify()) {
    Serial.println("Habilitando notificaciones TX");
    p_remote_characteristic_tx->registerForNotify(ble_notify_callback_TX);
  }

  connected = true;

}
