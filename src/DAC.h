/*
 * Dac.h - Library for controlling a brushed DC motor using the Dac 43amp motor driver.
 * Created by Yash Herekar, August 31, 2022.
 * Released into the public domain.
 * Copyright [2022] [Yash Herekar]
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 */

/*Cannot create a .cpp file as  prototypes need the function to be present in the same file*/

#pragma once

class Dac
{
  private:
  int8_t dacPin;
  int8_t ID;

  static String version;
  bool debugStatus;
  const uint8_t DEFAULTSPEED = 0;
  
  public:

  //pwm variable to control the speed of motor
  uint8_t speed;
  int8_t deviation;
  uint8_t oldMotorSpeed;
  uint8_t changeSpeedInc, changeSpeedDec;
  /*++++++++++++++++++++++++++++++++++++++++++++++++MOTOR STATES+++++++++++++++++++++++++++++++++++++++++++++++++++++*/

  enum motorStates : uint8_t
  {
    FRONT = 'F',
    BACK = 'B',
    LEFT = 'L',
    RIGHT = 'R',
    SHARPLEFTFRONT = 'G',
    SHARPRIGHTFRONT = 'I',
    SHARPLEFTBACK = 'H',
    SHARPRIGHTBACK = 'J',
    STOP = 'S',
    STOPALL = 'X',
    ENABLE = 'E',
    DISABLE = 'D',
    FLIP = 'W',
    UNFLIP = 'U'
  };
  motorStates motorStatus = motorStates::STOPALL;                        //State variable set to STOP initially

  
  /*======================================Function prototyping section================================================*/
  inline Dac();
  inline Dac(const int8_t& = -1, const int8_t& = -1, const bool& = false);
  inline void loop() __attribute__((always_inline));
  inline void run() __attribute__((always_inline));
  inline void stop() __attribute__((always_inline));
  inline static void printInfo() __attribute__((always_inline));
  inline ~Dac() __attribute__((always_inline));
  /*===================================================================================================================*/
};

//Static variables initilisation
String Dac::version="";

//Default constructor
Dac::Dac(){}

//Parametrised constructor with 6 parameters (still need to work on it, avoid it for right now)
Dac::Dac(const int8_t& dacPin, const int8_t& ID, const bool& debugStatus) :
dacPin(dacPin),
ID(ID),                    //for seial monitor display
debugStatus(debugStatus)
{
  speed = 70;
  version = "1.0.0";
  oldMotorSpeed = 70;
  changeSpeedInc = 60;
  changeSpeedDec = 50;
}

void Dac::loop()
{
  switch(this->motorStatus)
  {
    case motorStates::RUN:
    run();
    break;

    case motorStates::STOP:
    stop();
    break;
  }
}

void Dac::run()
{
  ledcWrite(this->dacPin,this->speed);
  if(this->debugStatus) Serial.println("Motor "+(String)ID+" STOP: "+this->speed);
}

void Dac::stop()
{
  ledcWrite(this->dacPin,this->DEFAULTSPEED);
  if(this->debugStatus) Serial.println("Motor "+(String)ID+" STOP: "+this->DEFAULTSPEED);
}


void Dac::printInfo()
{
  Serial.println();
  Serial.println("Dac Motordriver library");
  Serial.println("Library version:");
  Serial.println(version);
  Serial.println("Yash Herekar 2023");
  
  delay(1000);
}

//Destructor
Dac::~Dac()
{
  if(this->debugStatus) Serial.println("motor object destroyed");
}