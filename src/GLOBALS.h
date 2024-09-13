#pragma once 

#include <Ps3Controller.h>
#include <Wire.h>
#include "LED.h"
#include "DAC.h"
#include "DRIVESYSTEM.h"
#include "CONFIG.h"

//PS3 variables
uint8_t player = 0;
uint8_t battery = 0;
uint8_t stateCount = 0;

//Led definition section
//use between 150 ohms to 330 ohms resistor

//Left Motor
const int8_t dacPin1 =  25;
const int8_t dacPin2 =  26;
//LED1
const String redLedId = "Red Led";
constexpr int8_t redLedPin = 17;

//LED2
const String blueLedId = "Blue Led";
constexpr int8_t blueLedPin = 2;

//Buzzer definition section
constexpr int8_t buzzId = 1;
constexpr int8_t buzzPin = 18; //Active buzzer use 100 ohms resistor
constexpr uint8_t resolutionBuzz = 8;
constexpr uint32_t frequencyBuzz = 5000;

/*==============================================Object declaration===============================================*/  
// Create iBus Object
Dac motor1(dacPin1, leftMotorsId, MOTORDEBUG);     //Create an object of class motor1
Dac motor2(dacPin2, rightMotorsId, MOTORDEBUG);    //Create an object of class motor2 should have been LPWM2, RPWM2
led redLed(redLedPin, frequency, resolution, redLedId, LEDDEBUG);                                                    //Create object for red led
led blueLed(blueLedPin, frequency, resolution, blueLedId, LEDDEBUG);                                                 //Create object for blue led
buzzer buzz(buzzId, buzzPin, resolutionBuzz, frequencyBuzz, BUZZERDEBUG);                                            //Create object for buzzer
driveMode mode(motor1, motor2, redLed, blueLed, buzz, player);                                                       // Drive System object
/*==============================================Function section====================================================*/