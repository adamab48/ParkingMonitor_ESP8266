#include <Arduino.h>
#include <Firebase_ESP_Client.h> 
#include <ESP8266WiFi.h>
#include <addons/RTDBHelper.h>
#include <addons/TokenHelper.h>

#define SSID "My wifi"
#define PASS "Adam2020"
#define DATABASE_URL "espproject-a9f95-default-rtdb.europe-west1.firebasedatabase.app"
FirebaseData data_object ;
FirebaseAuth db_auth ;
FirebaseConfig db_config;
int i = 0;
const int trigPin = 12;
const int echoPin = 14;
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701 
long duration;
float distanceCm;
float distanceInch;
void setup() {
  
  db_config.database_url = DATABASE_URL;
  db_config.signer.test_mode = true ;

  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  WiFi.begin(SSID,PASS);
  delay(1000);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Connecting");
    delay(1000);
  }
  Serial.print("Connected to ");
  Serial.print(SSID);
  Serial.println(" ");
  Serial.print("IP Address ");
  Serial.print(WiFi.localIP());
  Firebase.reconnectWiFi(true);
  Firebase.begin(&db_config,&db_auth);

  
}

void loop() {
  

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_VELOCITY/2;
  
  
  if (Firebase.ready() && distanceCm < 10)
  {
    
    Firebase.RTDB.setInt(&data_object,"LED_STATUS",1);
    Serial.println("A Car is present");
   
  }
  else {
    
    Firebase.RTDB.setInt(&data_object,"LED_STATUS",0);
    Serial.println("No Car is present"); 
    }
  delay(500);
  
}