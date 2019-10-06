#include <Wire.h>    // incluye libreria de bus I2C
#include <Adafruit_Sensor.h>  // incluye librerias para sensor BMP280
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;    // crea objeto con nombre bmp

float T;    // variable para almacenar valor de temperatura
float PRESION;      // variable para almacenar valor de presion atmosferica
float H;

const float SEALEVELPRESSURE_HPA = 1018.5f;

const float c1=-8.78469475556f;
const float c2=1.61139411f;
const float c3=2.33854883889f;
const float c4=-0.14611605f;
const float c5=-0.012308094f;
const float c6=-0.0164248277778f;
const float c7=0.002211732f;
const float c8=0.00072546f;
const float c9=-0.000003582f;



void setup() {
  Serial.begin(9600);       // inicializa comunicacion serie a 9600 bps
  Serial.println("Iniciando:");     // texto de inicio
  if ( !bme.begin() ) {       // si falla la comunicacion con el sensor mostrar
    Serial.println("BME280 no encontrado !"); // texto y detener flujo del programa
    while (1);          // mediante bucle infinito
  }
}

void loop() {
  T = bme.readTemperature();    // almacena en variable el valor de temperatura
  PRESION = bme.readPressure()/100;   // almacena en variable el valor de presion divido
            // por 100 para covertirlo a hectopascales
  H = bme.readHumidity();

  Serial.print("T: ");    // muestra texto
  Serial.print(T);      // muestra valor de la variable
  Serial.print("C ");        // muestra letra C indicando grados centigrados

  float SENSACIO_TERMICA = T;
  if (T >= 27 && H >= 40) {
    SENSACIO_TERMICA = c1+c2*T+c3*H+c4*T*H+c5*T*T+c6*H*H+c7*T*T*H+c8*T*H*H+c9*T*T*H*H;
  }
  Serial.print("ST: ");    // muestra texto
  Serial.print(SENSACIO_TERMICA);      // muestra valor de la variable
  Serial.print("C ");        // muestra letra C indicando grados centigrados

  Serial.print("PR: ");    // muestra texto
  Serial.print(T-(100-H)/5);      // muestra valor de la variable
  Serial.print("C ");
  
  Serial.print("P: ");      // muestra texto
  Serial.print(PRESION);      // muestra valor de la variable
  Serial.print("hPa ");     // muestra texto hPa indicando hectopascales

  Serial.print("A: ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.print("m ");

  Serial.print("H: ");      // muestra texto
  Serial.print(H);     // muestra valor de la variable
  Serial.println("%");     // muestra texto hPa indicando hectopascales

  delay(5000);          // demora de 5 segundos entre lecturas
}
