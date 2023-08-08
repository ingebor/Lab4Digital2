
//****************************************************************
// UVG BE3015-Digital 2
// Código de ejemplo PWM
//****************************************************************
//****************************************************************
// Librerías
//****************************************************************
#include <Arduino.h>
#include "driver/ledc.h"
//****************************************************************
// Definición de etiquetas
//****************************************************************
// Paso 1: selección de parámetros de la señal PWM
#define pwmChannel 0 // 16 canales 0-15
#define ledRChannel 1
#define ledGChannel 2
#define ledBChannel 3
#define freqPWM 5000  // Frecuencia en Hz
#define freqPWM1 1000 // Frecuencia en Hz
#define freqPWM2 500  // Frecuencia en Hz
#define resolution 8  // 1-16 bits de resolución
#define pinLedR 13
#define pinLedG 12
#define pinLedB 14
#define pinPWM 15 // GPIO 2 para tener la salida del PWM

#define boton1 4
#define boton2 5
#define boton3 18
#define boton4 19

//****************************************************************
// Prototipos de funciones
//****************************************************************
void configurarPWM(void);
//****************************************************************
// Variables Globales
//****************************************************************

//int dutycycle = 0;
int color = 0; // 0 para rojo 1 para verde y 2 para azul
int dcR = 0;
int dcG = 0;
int dcB = 0;

//****************************************************************
// ISR: Interrupciones
//****************************************************************
// void IRAM_ATTR ISR(){
//
//}
//****************************************************************
// Configuración
//****************************************************************
void setup()
{
  Serial.begin(115200);
  configurarPWM();
  pinMode(boton1, INPUT_PULLDOWN);
  pinMode(boton2, INPUT_PULLDOWN);
  pinMode(boton3, INPUT_PULLDOWN);
  pinMode(boton4, INPUT_PULLDOWN);
}
//****************************************************************
// Loop Principal
//****************************************************************
void loop()
{
  int estadob1 = digitalRead(boton1); // lEER ESTADO DE LOS BOTONES
  int estadob2 = digitalRead(boton2);
  int estadob3 = digitalRead(boton3);
  int estadob4 = digitalRead(boton4);

  if (estadob3 == 1)
  {
    delay(500);
    color++;
  
    if (color == 0){
      Serial.printf("Trabajar con rojo\n");
    }
    else if(color == 1){
      Serial.printf("Trabajar con verde\n");
    }
    else if(color == 2){
      Serial.printf("Trabajar con azul\n");
    }
    else if (color > 2){
      color = 0;
      Serial.printf("%d",color);
    }
  }

  switch (color)
  {
  case 0:
    ledcWrite(ledGChannel, 0);
    ledcWrite(ledBChannel, 0);
    //dcB = 0;
    if (estadob4 == 1)
    {
      delay(500);
      dcR+=25;
      if(dcR>256){
        dcR = 0;
      }
      ledcWrite(pwmChannel, dcR);
      ledcWrite(ledRChannel, dcR);
      delay(10);
    }
    break;
  case 1:
    ledcWrite(ledRChannel, 0);
    ledcWrite(ledBChannel, 0);
    //dcR = 0;
    if (estadob4 == 1)
    {
      delay(500);
      dcG+=25;
      if(dcG>256){
        dcG = 0;
      }
      ledcWrite(pwmChannel, dcG);
      ledcWrite(ledGChannel, dcG);
      delay(10);
    }
    break;
  case 2:
    ledcWrite(ledRChannel, 0);
    ledcWrite(ledGChannel, 0);
    //dcG = 0;
    if (estadob4 == 1)
    {
      delay(500);
      dcB+=25;
      if(dcB>256){
        dcB = 0;
      }
      ledcWrite(pwmChannel, dcB);
      ledcWrite(ledBChannel, dcB);
      delay(10);
    }
    break;
  }

  /**
    for (int dutycycle = 0; dutycycle < 256; dutycycle++)
    {
      ledcWrite(pwmChannel, dutycycle);
      ledcWrite(ledRChannel, dutycycle);
      ledcWrite(ledGChannel, dutycycle);
      delay(10);
    }
    for (int dutycycle = 255; dutycycle > 0; dutycycle--)
    {
      ledcWrite(ledBChannel, dutycycle);
      ledcWrite(pwmChannel, dutycycle);
      delay(10);
    }
    **/
}
//****************************************************************
// Función para configurar módulo PWM
//****************************************************************
void configurarPWM(void)
{
  // Paso 1: Configurar el módulo PWM
  ledcSetup(pwmChannel, freqPWM, resolution);
  ledcSetup(ledRChannel, freqPWM1, resolution);
  ledcSetup(ledGChannel, freqPWM2, resolution);
  ledcSetup(ledBChannel, freqPWM, resolution);
  // Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWM, pwmChannel);
  ledcAttachPin(pinLedR, ledRChannel);
  ledcAttachPin(pinLedG, ledGChannel);
  ledcAttachPin(pinLedB, ledBChannel);
}
