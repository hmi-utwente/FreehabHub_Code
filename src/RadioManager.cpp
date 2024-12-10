#include "RadioManager.h"

#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

#include "LEDManager.h"
#include "TimeManager.h"

const uint8_t newMacAddress[] = {0x1A, 0x01, 0x23, 0x45, 0x67, 0x89};  // customize as you wish
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

struct struct_message {
  unsigned long time;
};

struct_message sendData;
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void printMacAddress(const uint8_t mac[]) {
  Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\r\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void RadioManager::init() {
  WiFi.mode(WIFI_STA);

  uint8_t mac[6];
  esp_wifi_get_mac(WIFI_IF_STA, mac);

  Serial.print("Default ESP Board MAC Address: ");
  printMacAddress(mac);

  esp_wifi_set_mac(WIFI_IF_STA, newMacAddress);
  esp_wifi_get_mac(WIFI_IF_STA, mac);

  Serial.print("New ESP Board MAC Address:     ");
  printMacAddress(mac);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

bool ledOn = false;

void RadioManager::update() {
  if (sinceSend > 100 && ledOn) {
    ledOn = false;
    setLEDColor(0, 0, 0);
  }

  if (sinceSend < 250) return;
  sinceSend = 0;

  sendData.time = timeManager.getTime();

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&sendData, sizeof(sendData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
    setLEDColor(0, 100, 0);
    ledOn = true;
  } else {
    Serial.println("Error sending the data");
    setLEDColor(100, 0, 0);
    ledOn = true;
  }
}

RadioManager radioManager;