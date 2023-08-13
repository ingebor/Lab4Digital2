
//****************************************************************
// UVG BE3015-Digital 2
// Laboratorio 4 
// Ingebor Ayleen Rubio Vasquez - 19003
//****************************************************************
//****************************************************************
// Librerías
//****************************************************************
#include <Arduino.h>
#include "driver/ledc.h"
#include <ESP32Servo.h>
//****************************************************************
// Definición de etiquetas
//****************************************************************
// Paso 1: selección de parámetros de la señal PWM
#define pwmChannel 0 // 16 canales 0-15
#define ledRChannel 1
#define ledGChannel 2
#define ledBChannel 3
#define pwmChannelServo 4
#define freqPWM 5000  // Frecuencia en Hz
#define freqPWM1 1000 // Frecuencia en Hz
#define freqPWM2 500  // Frecuencia en Hz
#define freqPWMServo 50
#define resolution 8  // 1-16 bits de resolución
#define pinLedR 12
#define pinLedG 14
#define pinLedB 27
#define pinPWM 15 // GPIO 2 para tener la salida del PWM

#define boton1 4
#define boton2 18
#define boton3 19
#define boton4 21

#define pinServo 13

//****************************************************************
// Prototipos de funciones
//****************************************************************
void configurarPWM(void);
//****************************************************************
// Variables Globales
//****************************************************************

// int dutycycle = 0;
int color = 0; // 0 para rojo 1 para verde y 2 para azul
int dcR = 0;
int dcG = 0;
int dcB = 0;

Servo myservo;
int aumento = 10;
int pos = 0;

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
  myservo.attach(pinServo);
  myservo.write(pos);
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

  //-----------------------------------------------------Botones 3 y 4
  // Cambiar qué se desea hacer
  if (estadob3 == 1)
  {
    delay(500);
    color++;

    if (color == 0)
    {
      Serial.printf("Trabajar con rojo\n");
    }
    else if (color == 1)
    {
      Serial.printf("Trabajar con verde\n");
    }
    else if (color == 2)
    {
      Serial.printf("Trabajar con azul\n");
    }
    else if (color == 3)
    {
      Serial.printf("Trabajar con servos\n");
    }
    else if (color > 3)
    {
      color = 0;
      //Serial.printf("%d", color);
    }
  }

  switch (color)
  {
  case 0: //Servo a 0° y modificar LED rojo
    ledcWrite(ledGChannel, 0);
    ledcWrite(ledBChannel, 0);
    myservo.write(0);
    // dcB = 0;
    if (estadob4 == 1)
    {
      delay(500);
      dcR += 25;
      if (dcR > 256)
      {
        dcR = 0;
      }
      ledcWrite(pwmChannel, dcR);
      ledcWrite(ledRChannel, dcR);
      delay(10);
    }
    break;
  case 1: //Servo a 90° y modificar LED verde
    myservo.write(90);
    ledcWrite(ledRChannel, 0);
    ledcWrite(ledBChannel, 0);
    // dcR = 0;
    if (estadob4 == 1)
    {
      delay(500);
      dcG += 25;
      if (dcG > 256)
      {
        dcG = 0;
      }
      ledcWrite(pwmChannel, dcG);
      ledcWrite(ledGChannel, dcG);
      delay(10);
    }
    break;
  case 2: //Servo a 180° y modificar LED azul
    myservo.write(180);
    ledcWrite(ledRChannel, 0);
    ledcWrite(ledGChannel, 0);
    // dcG = 0;
    if (estadob4 == 1)
    {
      delay(500);
      dcB += 25;
      if (dcB > 256)
      {
        dcB = 0;
      }
      ledcWrite(pwmChannel, dcB);
      ledcWrite(ledBChannel, dcB);
      delay(10);
    }
    break;
  case 3: //Mover servo libremente con botones 1 y 2
    //myservo.write(0);
    if (estadob1 == 1 && estadob2 == 0) //Aumentar posicion del servo
    {
      //Serial.println(pos);
      pos = pos + aumento;
      if (pos > 180)
      {
        pos = 180;
      }
      else 
        pos = pos;
      
      //Serial.println(pos);
      Serial.println("sumando");
      myservo.write(pos);
      delay(500);
    }
    else if (estadob2 == 1 && estadob1 ==0) //Disminuir posicion del servo
    {
      pos = pos - aumento;
      if (pos < 0)
      {
        pos = 0;
      }
      else
        pos = pos;
      
      //Serial.println(pos);
      Serial.println("restando");
      myservo.write(pos);
      delay(500);
    }
    break;
  }

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
  ledcSetup(pwmChannelServo, freqPWMServo, resolution);
  // Paso 2: seleccionar en que GPIO tendremos nuestra señal PWM
  ledcAttachPin(pinPWM, pwmChannel);
  ledcAttachPin(pinLedR, ledRChannel);
  ledcAttachPin(pinLedG, ledGChannel);
  ledcAttachPin(pinLedB, ledBChannel);
  ledcAttachPin(pinServo, pwmChannelServo);
}
