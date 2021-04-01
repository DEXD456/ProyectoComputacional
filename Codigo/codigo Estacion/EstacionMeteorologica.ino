
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <time.h>

#define FIREBASE_HOST "estacion-meteorologica-6a5e1-default-rtdb.firebaseio.com" //Sin http:// o https:// 
#define FIREBASE_AUTH "5uNgy1s6wQKWNTfJsCCLlEecQc5KECuEYeHpJi5b"
#define WIFI_SSID "andiluable"
#define WIFI_PASSWORD "4NDreaNicol3"
#define DHTPIN D7 //Pin de ingreso de datos del DTH
#define DHTTYPE DHT11 // Tipo de DTH

String path = "/Estacion";
FirebaseJson json;
int timezone = 4*3600;
int dst = 0;

int LDR_pin = A0;  // Leer el pin 0
int LDR_val = 0;  // Variable para leer datos del LDR
int lux = 0; //valor convertido
DHT dht(DHTPIN, DHTTYPE);
//Define un objeto de Firebase
FirebaseData firebaseData;

void printResult(FirebaseData &data);
void CausaError(void);


void setup()
{
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando a ....");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Conectado con la IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Establezca el tiempo de espera de lectura de la base de datos en 1 minuto (máximo 15 minutos)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  
  //Tamaño y  tiempo de espera de escritura, tiny (1s), small (10s), medium (30s) and large (60s).
  //tiny, small, medium, large and unlimited.
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  configTime(timezone,dst,"pool.ntp.org","time.nist.gov");
  Serial.println("\nWaiting for internet time");

  while(!time(nullptr)){
      Serial.print("*");
      delay(1000);
  }
  Serial.println("Time response.....OK");
}

void loop()
{
  delay(7000);
  // Se leeran los valores contimuamnete del sensor LDR 
  LDR_val = analogRead(LDR_pin);
  lux = sensorRawToPhys(LDR_val);
  float humidity = dht.readHumidity(); //Se lee el porcentaje de la humedad en el aire
  float temperature = dht.readTemperature();//Se lee la temperatura en grados Celsios
  if(isnan(humidity) || isnan(temperature) || isnan(LDR_val)) //se comprueba que los datos obtenidos son correctos y no valores nulos
  {
    Serial.println("Error en la lectura del sensor");
  }


  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);



  Firebase.setInt(firebaseData, path + "/Fijos/Temperatura", temperature);
  Firebase.setInt(firebaseData, path + "/Fijos/LUX",lux);
  Firebase.setInt(firebaseData, path + "/Fijos/Humedad", humidity);
  Firebase.setInt(firebaseData, path + "/Fijos/Año", p_tm->tm_year+1900);
  Firebase.setInt(firebaseData, path + "/Fijos/Mes",p_tm->tm_mon+1);
  Firebase.setInt(firebaseData, path + "/Fijos/Dia", p_tm->tm_mday);
  Firebase.setInt(firebaseData, path + "/Fijos/Hora", p_tm->tm_hour);
  Firebase.setInt(firebaseData, path + "/Fijos/Minuto",p_tm->tm_min);
  Firebase.setInt(firebaseData, path + "/Fijos/Segundo", p_tm->tm_sec);
  
  json.set("Temperatura", temperature);
  json.set("LUX", lux);
  json.set("Humedad",humidity);
  json.set("Año", p_tm->tm_year+1900);
  json.set("Mes", p_tm->tm_mon+1);
  json.set("Dia", p_tm->tm_mday);
  json.set("Hora", p_tm->tm_hour);
  json.set("Minuto", p_tm->tm_min);
  json.set("Segundo", p_tm->tm_sec);
  Firebase.pushJSON(firebaseData, path + "/BD/Datos", json);
}

int sensorRawToPhys(int entrada){
  // Conversion
  float Vout = float(entrada) * (3.3 / float(1023));// Conversion de analoga
  float RLDR = (10000 * (3.3 - Vout))/Vout; // Convesion de voltaje a resistencia
  
  int resultado=500/(RLDR/1000); // Conversion de resistencia a lux
  return resultado;
}