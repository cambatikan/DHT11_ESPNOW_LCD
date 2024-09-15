#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


typedef struct struct_message {
    float a;
    float b;
} struct_message;
struct_message myData;
LiquidCrystal_I2C lcd(0x27, 16, 2); 


void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
  memcpy(&myData, incomingData, sizeof(myData));
  
 
  Serial.print("Temp: ");
  Serial.println(myData.a);
  
  Serial.print("Humidity: ");
  Serial.println(myData.b); 
  
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Temperature: "); 
  lcd.print(myData.a);  
  lcd.write(0xDF);
  lcd.print("C"); 
  lcd.setCursor(0, 1); 
  lcd.print("Humidity: "); 
  lcd.print(myData.b); 
}
 
void setup() {
  
  Serial.begin(115200);


  lcd.init();
  lcd.backlight(); 
  
  WiFi.mode(WIFI_STA);//ESP32 STATION modunda başlat.
  
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {}
