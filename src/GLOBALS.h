#include "BUZZER.h"
#include "BTS7960_Motordriver.h"
#include "LED.h"
#include "CONFIG.h"

// Miscellaneous variables
bool initOnce = true;

//Motor PWM properties
const uint32_t frequency = 10000;
const uint8_t resolution = 8;

//BTS7960 motor driver 2 pin definitions
constexpr int8_t leftMotorsId = 1;
constexpr int8_t RPWM1 = 26;
constexpr int8_t LPWM1 = 27;                   
constexpr int8_t R_EN1 = 25;  
constexpr int8_t L_EN1 = 14;
constexpr int8_t R_IS1 = -1;        //Alarm pin
constexpr int8_t L_IS1 = -1;        //Alarm pin

//BTS7960 motor driver 2 pin definitions
constexpr int8_t rightMotorsId = 2;
constexpr int8_t RPWM2 = 15;         
constexpr int8_t LPWM2 = 5;          
constexpr int8_t R_EN2 = 16;
constexpr int8_t L_EN2 = 4;
constexpr int8_t R_IS2 = -1;        //Alarm pin
constexpr int8_t L_IS2 = -1;        //Alarm pin 

//Led definition section
//use between 150 ohms to 330 ohms resistor

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


/*==================================================Object declaration===================================================*/  
// Create iBus Object
BTS7960 motor1(L_EN1, R_EN1, LPWM1, RPWM1, frequency, resolution, L_IS1, R_IS1, leftMotorsId);      //Create an object of class motor1
BTS7960 motor2(L_EN2, R_EN2, RPWM2, LPWM2, frequency, resolution, L_IS2, R_IS2, rightMotorsId);      //Create an object of class motor2 should have been LPWM2, RPWM2
led redLed(redLedPin, frequency, resolution, redLedId);                                                    //Create object for red led
led blueLed(blueLedPin, frequency, resolution, blueLedId);                                                 //Create object for blue led
buzzer buzz(buzzId, buzzPin, resolutionBuzz, frequencyBuzz);                                               //Create object f
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++MOTOR STATES++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

enum class motorStates : uint8_t
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
   STOPALL = 'D',
   FRONTLIGHTSON = 'W',
   FRONTLIGHTSOFF = 'w',
   BACKLIGHTSON = 'U',
   BACKLIGHTSOFF = 'u',
   HORNON = 'V',
   HORNOFF = 'v',
   EXTRAON = 'X',
   EXTRAOFF = 'x',
   SPEED0 = '0',
   SPEED1 = '1',
   SPEED2 = '2',
   SPEED3 = '3',
   SPEED4 = '4',
   SPEED5 = '5',
   SPEED6 = '6',
   SPEED7 = '7',
   SPEED8 = '8',
   SPEED9 = '9',
   MAXSPEED = 'q',
   
};
motorStates motorStatus = motorStates::STOPALL;                        //State variable set to STOP initially
//motorStates motorPrevStatus;                                         //Previous motor state

/*==================================================Function prototyping section========================================================*/
inline void initSystem() __attribute__((always_inline));
inline void standbySystem() __attribute__((always_inline));
/*======================================================================================================================================*/

void initSystem()
{
  //Initlization sequence
  Serial.println("System initlized, waiting for Transmitter...");
  motor1.enable();  motor2.enable();                                  //Makes all enable pins go high
  blueLed.on();                                                       //Turns the blue led on
  redLed.on();                                                        //Turns the red led on
  buzz.initBuzzer();                                                  //puts the buzzer on

  if(initOnce && 1)
  {
    BTS7960::printInfo();
    Serial.println();

    buzz.alarm();
    Serial.println();

    buzz.alarm();
    Serial.println();
    
    buzz.alarm();
    redLed.printInfo();
    Serial.println();
    
    buzz.alarm();
    blueLed.printInfo();
    Serial.println();
    
    buzz.alarm();
    Serial.println();
    
    buzz.initBuzzer();
    Serial.println("System initlized, waiting for Transmitter...");
    delay(3000);
    
    initOnce = false;
  }

  //Ready state
  blueLed.off();                                                      //Turns the blue led on
  redLed.on();                                                        //Turns the red led on

  //Initial statemachine setting
  motorStatus = motorStates::STOP;                                    //State variable set to STOP initially
}

void standbySystem()
{
  Serial.println("Receiver disconnected...");
  motor1.disable(); motor2.disable();
  blueLed.off();  redLed.off();
  buzz.deinitBuzzer();  
}

//namespaces here
