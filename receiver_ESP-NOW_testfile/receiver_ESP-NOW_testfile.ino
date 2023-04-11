//Libs do espnow e wifi
#include <esp_now.h>
#include <WiFi.h>

const int n_bytes = 8;

//==========================================================================================

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  //Serial.print("Mac Address in Station: "); 
  //Serial.println(WiFi.macAddress());

  InitESPNow();
  esp_now_register_recv_cb(OnDataRecv);

}

//====================================================================================================

void InitESPNow() {
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  }
  else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
//char macStr[18];
//  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
//           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//  Serial.print("Received from: "); 
//  Serial.println(macStr);
//  Serial.println("");

  for(int i=0; i<n_bytes; i++){
    Serial.print(data[i]);
    Serial.print(", ");
  }
  Serial.println();
}

void loop() {}
