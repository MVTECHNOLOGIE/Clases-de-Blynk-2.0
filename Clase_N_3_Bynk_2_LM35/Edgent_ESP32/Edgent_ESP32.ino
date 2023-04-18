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
#define BLYNK_TEMPLATE_ID "TMPL2ObCysqt-"
#define BLYNK_TEMPLATE_NAME "LM35"


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

#define ADC_VREF_mV    3300.0 // en milivoltios
#define ADC_RESOLUCION 4096.0 // Pines de entrada analógica = 12 bits = rango de lectura 0-4095.
#define LM35       36 // El pin GIOP36 (ADC0) del ESP32 está conectado al LM35
int ValorAnalogico = 0;
float milliVolt;
float TempC;
float TempF;
BlynkTimer timer;
 
void myTimer(){ 
// Esta función describe lo que sucederá con cada tic del temporizador 
  Blynk.virtualWrite(V0, TempC);
  Blynk.virtualWrite(V1, TempF);  
}

void setup(){
// Se inicializa la comunicación serial a una velocidad de 115200 baudios
  Serial.begin(115200);
  BlynkEdgent.begin();
  timer.setInterval(1000L, myTimer);
  
  pinMode(LM35,INPUT); // Se declara como Entrada
  delay(500);
}

void loop() {
  
// Se lee el valor ADC del sensor de temperatura
  ValorAnalogico = analogRead(LM35);

  // Se convierte el valor ADC a voltaje en milivoltios
  milliVolt = ValorAnalogico * (ADC_VREF_mV / ADC_RESOLUCION);

  // Se convierte el voltaje a temperatura en grados Celsius
  TempC = milliVolt / 10;

  // Se convierte la temperatura a grados Fahrenheit
  TempF = TempC * 9 / 5 + 32;

  // Se imprimen los valores de temperatura en el Monitor Serie
  Serial.print("Temperatura: ");
  Serial.print(TempC);   // Se imprime la temperatura en grados Celsius
  Serial.print("°C");
  Serial.print("  ~  "); // Separador entre grados Celsius y Fahrenheit
  Serial.print(TempF);   // Se imprime la temperatura en grados Fahrenheit
  Serial.println("°F");
  
  BlynkEdgent.run();   
  timer.run();// runs BlynkTimer 
}
