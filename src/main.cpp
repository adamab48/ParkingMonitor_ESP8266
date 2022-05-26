#include <Arduino.h>
#include <Firebase_ESP_Client.h> 
#include <ESP8266WiFi.h>
#include <addons/RTDBHelper.h>
#include <addons/TokenHelper.h>
#include <ArduinoJson.h>
#define SSID "WIFI SSID"
#define PASS "WIFI PASSWORD"
#define DATABASE_URL "INSERT YOUR DB URL"
FirebaseData data_object ;
FirebaseAuth db_auth ;
FirebaseConfig db_config;


void setup() {
  
  db_config.database_url = DATABASE_URL;
  db_config.signer.test_mode = true ;

  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
 
  WiFi.begin(SSID,PASS);
  delay(1000);
  while (WiFi.status() != WL_CONNECTED)
  {
    //Serial.println("Connecting");
    delay(1000);
  }
  /* Serial.print("Connected to ");
  Serial.print(SSID);
  Serial.println(" ");
  Serial.print("IP Address ");
  Serial.print(WiFi.localIP()); */
  Firebase.reconnectWiFi(true);
  Firebase.begin(&db_config,&db_auth);

  
}

void loop() {
DynamicJsonDocument doc(1024);
int cap1 = 0 ,cap2 =0 ;

doc["type"] = "request";
serializeJson(doc,Serial);

bool messageR = false;
String message = "" ;
while (messageR==false)
{
  if(Serial.available()) {
    message = Serial.readString();
    messageR = true;
  }
}

DeserializationError err = deserializeJson(doc,message);

 if (err) {
   Serial.print(F("Failed "));
   Serial.println(err.c_str());
 }
  cap1 = doc["Cap 1"];
  cap2 = doc["Cap 2"];
  if(Firebase.ready()) {
  Firebase.RTDB.setInt(&data_object,"cap1",cap1);
  }
  if (Firebase.ready()) {
    Firebase.RTDB.setInt(&data_object,"cap2",cap2);
  }
  


  delay(300);
}