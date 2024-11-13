#include "GLOBALS.h"

void setup()
{
  Serial.begin(9600);
  initSystem();
}

void loop()
{     
  
/*==========================================================ROBOT STATE MACHINE========================================================*/  
  switch (motorStatus)
  {
    case motorStates::FRONT:
    Serial.print("Front: ");
    motor1.front(); 
    Serial.print(" : ");
    motor2.front();
    blueLed.on();
    redLed.off();
    break;
    
    case motorStates::BACK:
    Serial.print("Back: ");
    motor1.back();  
    Serial.print(" : ");
    motor2.back();
    blueLed.on();
    redLed.off();
    break;
    
    case motorStates::LEFT:
    Serial.print("Left: ");
    motor1.back();
    Serial.print(" : ");
    motor2.front();
    blueLed.on();
    redLed.off();
    break;
    
    case motorStates::RIGHT:
    Serial.print("Right: ");
    motor1.front();
    Serial.print(" : ");
    motor2.back();
    blueLed.on();
    redLed.off();
    break;
         
    case motorStates::SHARPRIGHTFRONT:
    Serial.print("Sharp Right Front: ");
    motor1.front();
    Serial.print(" : ");
    motor2.stop();
    blueLed.on();
    redLed.off();
    break;
    
    case motorStates::SHARPLEFTFRONT:
    Serial.print("Sharp Left Front: ");
    motor1.stop();
    Serial.print(" : ");
    motor2.front();
    blueLed.on();
    redLed.off(); 
    break;
   
    case motorStates::SHARPRIGHTBACK:
    Serial.print("Sharp Right Back: ");
    motor1.stop();
    Serial.print(" : ");
    motor2.back();
    blueLed.on();
    redLed.off();
    break;
    
    case motorStates::SHARPLEFTBACK:
    Serial.print("Sharp Left Back: ");
    motor1.back();
    Serial.print(" : ");
    motor2.stop();
    blueLed.on();
    redLed.off();
    break;

    case motorStates::STOP:
    Serial.print("Stop: ");
    motor1.stop();
    Serial.print(" : ");
    motor2.stop();
    blueLed.off();
    redLed.on();
    break;
    
    case motorStates::SPEED0:
    motor1.speed = motor2.speed = 0;
    Serial.print("Speed: "); Serial.print(motor1.speed);  Serial.print(" : "); Serial.println(motor2.speed);
   
    break;
    
    case motorStates::SPEED1:
    motor1.speed = motor2.speed = 25;
    Serial.print("Speed: "); Serial.print(motor1.speed);  Serial.print(" : "); Serial.println(motor2.speed);
    
    break;
    
    case motorStates::SPEED2:
    motor1.speed = motor2.speed = 51;
    Serial.print("Speed: "); Serial.print(motor1.speed);  Serial.print(" : "); Serial.println(motor2.speed);
    
    break;
    
    case motorStates::SPEED3:
    motor1.speed = motor2.speed = 76;
    Serial.print("Speed: "); Serial.print(motor1.speed);  Serial.print(" : "); Serial.println(motor2.speed);
    
    break;
    
    case motorStates::SPEED4:
    motor1.speed = motor2.speed = 102;
    Serial.print("Speed: "); Serial.print(motor1.speed);  Serial.print(" : "); Serial.println(motor2.speed);
    
    break;
    
    case motorStates::SPEED5:
    motor1.speed = motor2.speed = 127;
    Serial.print("Speed: "); Serial.print(motor1.speed);  Serial.print(" : "); Serial.println(motor2.speed);
    
    break;
    
    case motorStates::SPEED6:
    motor1.speed = motor2.speed = 153;
    Serial.print("Speed: "); Serial.print(motor1.speed);  Serial.print(" : "); Serial.println(motor2.speed);
    
    break;
    
    case motorStates::SPEED7:
    motor1.speed = motor2.speed = 178;
    Serial.print("Speed: "); Serial.print(motor1.speed);  Serial.print(" : "); Serial.println(motor2.speed);
    
    break;
    
    case motorStates::SPEED8:
    motor1.speed = motor2.speed = 204;
    Serial.print("Speed: "); Serial.print(motor1.speed);  Serial.print(" : "); Serial.println(motor2.speed);
    
    break;
    
    case motorStates::SPEED9:
    motor1.speed = motor2.speed = 229;
    Serial.print("Speed: "); Serial.print(motor1.speed);  Serial.print(" : "); Serial.println(motor2.speed);
    
    break;
    
    case motorStates::MAXSPEED:
    motor1.speed = motor2.speed = 255;
    Serial.print("Speed: "); Serial.print(motor1.speed);  Serial.print(" : "); Serial.println(motor2.speed);
    
    break;

    case motorStates::STOPALL:
    standbySystem();
    while(true)
    {
      if(Serial.available())
      {
        initSystem();
        break;
      }
      else
        redLed.toggle();
    }
    break;

    case motorStates::EXTRAON:                            //Same as EXTRAOFF
    standbySystem();
    while(true)
    {
      motorStatus = (motorStates)Serial.read();
      if(motorStates::EXTRAOFF == motorStatus)
      {
        initSystem();
        break;
      }
      else if(motorStates::STOPALL == motorStatus)
      {
        break;
      }
      else
        redLed.toggle();
    }
    break;
    
    case motorStates::EXTRAOFF:                           //Same as EXTRAON
    standbySystem();
    while(true)
    {
      motorStatus = (motorStates)Serial.read();
      if(motorStates::EXTRAOFF == motorStatus)
      {
        initSystem();
        break;
      }
      else if(motorStates::STOPALL == motorStatus)
      {
        break;
      }
      else
        redLed.toggle();
    }
    break;

    case motorStates::FRONTLIGHTSON:
    Serial.println("Front lights on");
    //Do nothing for now
    break;
    case motorStates::FRONTLIGHTSOFF:
    Serial.println("Front lights off");
    //Do nothing for now
    break;
    case motorStates::BACKLIGHTSON:
    Serial.println("Back lights on");
    //Do nothing for now
    break;
    case motorStates::BACKLIGHTSOFF:
    Serial.println("Back lights off");
    //Do nothing for now
    break;
    case motorStates::HORNON:
    Serial.println("Horn on");
    //Do nothing for now
    break;
    case motorStates::HORNOFF:
    Serial.println("Horn off");
    //Do nothing for now
    break;

    default: Serial.println("Invalid input");
  }

  Serial.println();
  
  if (Serial.available() > 0) 
    motorStatus = (motorStates)Serial.read();        //Read the state
}
