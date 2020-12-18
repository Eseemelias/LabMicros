
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "NombreWifi" // nombre del wifi
#define WIFI_PASSWORD "claveWifi" // password del wifi

#define FIREBASE_HOST "lab-10-c6131.firebaseio.com"  //direccion de la database de Firebase sin https://  ni el ultimo /
#define FIREBASE_AUTH "uLrppawdqD50bm705350dV0mONDiQrrr5sIZKF68"// poner codigo secreto. 
//Configuracion proyecto-cuentas servicio-secretos de la base de datos

int value_A = 0;

void setup() {
  pinMode(2, OUTPUT);
  
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

//int n = 0;

void loop() {
   value_A = analogRead(A0);

  //Set Value
  Firebase.setInt("test_1", value_A);
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  //Get Value
  Serial.print("From AppInventor: "); 
  Serial.println(Firebase.getString("App"));// Solo se pone el numbre entre comillas de la etiqueta que nos interese. tambien se puede sustituir "setString" por setInt o setFloat...
  if (Firebase.getString("App") == "\"ON\""){
      digitalWrite(2,LOW);
    }
  else if (Firebase.getString("App") == "\"OFF\""){
      digitalWrite(2,HIGH);
    }
  delay(1000);

  }
