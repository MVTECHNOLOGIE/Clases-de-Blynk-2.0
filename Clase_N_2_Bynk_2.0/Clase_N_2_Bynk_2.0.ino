/**************************************************** ************
   Blynk es una plataforma con aplicaciones iOS y Android para controlar
   ESP32, Arduino, Raspberry Pi y similares a través de Internet.
   Puede crear fácilmente interfaces móviles y web para cualquier
   proyectos simplemente arrastrando y soltando widgets.

     Descargas, documentos, tutoriales: https://www.blynk.io
     Generador de bocetos: https://examples.blynk.cc
     Comunidad Blynk: https://community.blynk.cc
     Síguenos: https://www.fb.com/blynkapp
                                 https://twitter.com/blynk_app

   La biblioteca Blynk tiene licencia MIT
  **************************************************** ***********
   Implementos Blynk.Edgent:
   - Blynk.Inject - Aprovisionamiento dinámico de credenciales WiFi
   - Blynk.Air - Actualizaciones de firmware por aire
   - Indicación del estado del dispositivo mediante un LED físico
   - Restablecimiento de credenciales usando un botón físico
  **************************************************** ***********/

/* Complete la información de su Plantilla Blynk aquí */
/* Leer más: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL2iPdKkTTO"
#define BLYNK_TEMPLATE_NAME "Lectura Analogica"


#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Descomente su tablero, o configure un tablero personalizado en Settings.h
//#define USE_ESP32_DEV_MODULE
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI

#include "BlynkEdgent.h"

const int PotPin = 36;// Potenciometro conectado a GPIO 36
int PotValor = 0; //Almacena los valores obtenidos del pin 36
int Porcentaje; //Almacena los valores de Mapeo
BlynkTimer timer;
 
void myTimer() 
{
// Esta función describe lo que sucederá con cada tic del temporizador 

  Blynk.virtualWrite(V0, PotValor);
  Blynk.virtualWrite(V1, Porcentaje);  
}

void setup()
{
  Serial.begin(115200);
  BlynkEdgent.begin();
  timer.setInterval(1000L, myTimer);
  
  pinMode(PotPin,INPUT);
  
  delay(500);
}

void loop() {
  
  PotValor = analogRead(PotPin);// Lectura del valor en cada vuelta del bucle
  Porcentaje = map(PotValor,0,4095,0,100); 
  Serial.println(PotValor);
  BlynkEdgent.run();
    
  timer.run();// runs BlynkTimer 
}
