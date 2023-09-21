/*************************************************************
 Blynk es una plataforma con aplicaciones de iOS y Android para controlar
 ESP32, Arduino, Raspberry Pi y similares a través de Internet.
 Puede crear fácilmente interfaces móviles y web para cualquier
 proyectos simplemente arrastrando y soltando widgets.

     Descargas, documentos, tutoriales: https://www.blynk.io
     Generador de bocetos: https://examples.blynk.cc
     Comunidad Blynk: https://community.blynk.cc
     Síguenos: https://www.fb.com/blynkapp
               https://twitter.com/blynk_app
               
La biblioteca Blynk tiene licencia MIT
 *************************************************************
Blynk.Edgent implementa:
   - Blynk.Inject - Aprovisionamiento dinámico de credenciales WiFi
   - Blynk.Air - Actualizaciones de firmware inalámbricas
   - Indicación del estado del dispositivo mediante un LED físico
   - Restablecimiento de credenciales mediante un botón físico
 *************************************************************/

/* Complete la información de su plantilla Blynk aquí */
/* Leer más: https://bit.ly/BlynkInject */

#define BLYNK_TEMPLATE_ID "TMPL2g5JXa0jc"
#define BLYNK_TEMPLATE_NAME "DHT11"
//#define BLYNK_AUTH_TOKEN "M5oJwlIhT9ogo3QRYuqIt1RFKWZAzSkm"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
#define USE_ESP32_DEV_MODULE
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI

#include "BlynkEdgent.h"
#include <DHT.h>

#define DHTPIN 23
#define DHTTYPE DHT11

float hum;   //HUMEDAD
float tempC;  //Temperatura C
float temof;  //Temperatura F
float Icf;   //Índice de Calor F
float Icc;   //Índice de Calor C

DHT dht(DHTPIN, DHTTYPE); //  DHT11}
BlynkTimer timer;

void myTimer(){ 
// Esta función describe lo que sucederá con cada tic del temporizador 
  Blynk.virtualWrite(V3, hum);
  Blynk.virtualWrite(V0, tempC);
  Blynk.virtualWrite(V1, temof);
  Blynk.virtualWrite(V3, Icc);
  Blynk.virtualWrite(V4, Icf);
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  dht.begin();// Inicializa el sensor DHT
  BlynkEdgent.begin();
  timer.setInterval(1000L, myTimer);
  
}

void loop() {

delay(5000); // Esperamos 5 segundos entre medidas
  
  hum = dht.readHumidity();  //Humedad relativa
  tempC = dht.readTemperature(); // Temperatura en grados centígrados (por defecto)
  temof = dht.readTemperature(true); // Temperatura en grados Fahreheit
  
  Icf = dht.computeHeatIndex(temof, hum); //Índice de calor en Fahreheit 
  Icc = dht.computeHeatIndex(tempC, hum, false); //Índice de calor en grados centígrados
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(hum) || isnan(tempC) || isnan(temof)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
Serial.print("Humedad: ");
  Serial.print(hum);
  Serial.println("%");
  Serial.print("Temperatura: ");
  Serial.print(tempC);
  Serial.print("°C - ");
  Serial.print(temof);
  Serial.println("°F");
  Serial.print("Sensación térmica: ");
  Serial.print(Icc);
  Serial.print("°C - ");
  Serial.print(Icf);
  Serial.println("°F");
  
  BlynkEdgent.run();
  timer.run();// runs BlynkTimer 
}
