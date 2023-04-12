
#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1 //*

// total number of bytes each package has
const int n_bytes = 8;

uint8_t macSlaves[][6] = {
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} // broadcast mode
};

//========================================================================================

void setup() {
  Serial.begin(115200);

  //Colocamos o ESP em modo station
  WiFi.mode(WIFI_STA);

  //Mostramos no Monitor Serial o Mac Address deste ESP quando em modo station
  //Serial.print("Mac Address in Station: "); 
  //Serial.println(WiFi.macAddress());

  //Chama a função que inicializa o ESPNow
  InitESPNow();

 //Cálculo do tamanho do array com os mac address dos slaves
  //sizeof(macSlaves) retorna a quantidade de bytes que o array macSlaves aponta
  //Sabemos que cada mac address é um array de 6 posições e
  //cada posição possui sizeof(uint8_t) bytes, então
  //a quantidade de slaves é a divisão da quantidade de bytes
  //total do array pela quantidade de posições e o resultado
  //dessa divisão dividimos novamente por quantos bytes cada posição possui
  int slavesCount = sizeof(macSlaves)/6/sizeof(uint8_t);

  //Para cada slave
  for(int i=0; i<slavesCount; i++){     //CHANNEL, ENCRYPT AND ADDRESS ADDED
    esp_now_peer_info_t slave;
    slave.channel = CHANNEL;
    slave.encrypt = 0;
    memcpy(slave.peer_addr, macSlaves[i], sizeof(macSlaves[i]));
    esp_now_add_peer(&slave);
  }

  esp_now_register_send_cb(OnDataSent);
  send();
}

//=========================================================================================

void InitESPNow() {
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  }
  else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }
}


void send(){
  long int timeStart = millis();
  uint8_t package[n_bytes];

  for(int i=0; i<n_bytes; i++){
    package[i] = i*5 + 1;
  }

  uint8_t broadcast[] = {0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF};
  esp_err_t result = esp_now_send(broadcast, (uint8_t*) &package, sizeof(package));
  Serial.print("Send Status: ");
  
  if (result == ESP_OK) {
    Serial.println("Success");
  }
  else {
    Serial.println("Error");
  }
  long int timeEnd = millis();
  Serial.print("speed of data transfer: ");
  if (timeEnd - timeStart != 0) Serial.println(1000/(timeEnd - timeStart));
  else Serial.println("========================================================");
  Serial.println();
}


void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//  char macStr[18];
//  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
//           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//Serial.print("Sent to: "); 
//Serial.println(macStr);
  
  Serial.print("Status: "); 
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
  send();
}

void loop() {} 
