#include "GLOBALS.h"
#include "CONFIG.h"

void notify()
{
  //---------- Digital select/start/ps button events ---------
  if( Ps3.event.button_down.start )
  {
    if(++stateCount == 5)
      stateCount = 1;

    if(stateCount == 1)
    {
      Ps3.setPlayer(1);
      mode.driveStatus = mode.driveStates::mode1;
      write("Mode1");
    }
    else if(stateCount == 2)
    {
      Ps3.setPlayer(2);
      mode.driveStatus = mode.driveStates::mode2;
      write("Mode2");
    }
    else if(stateCount == 3)
    {
      Ps3.setPlayer(3);
      mode.driveStatus = mode.driveStates::mode3;
      write("Mode3");
    }
    else if(stateCount == 4)
    {
      Ps3.setPlayer(4);
      mode.driveStatus = mode.driveStates::mode4;
      write("Mode4");
    }
  }

  mode.loop();
  // switch(mode.driveStatus)
  // {
  //   case mode.driveStates::mode1:
  //   mode.driveMode1();             //Normal mode
  //   break;

  //   case mode.driveStates::mode2:
  //   mode.driveMode2();             //Speed adaptive mode
  //   break;

  //   case mode.driveStates::mode3:
  //   mode.driveMode3();             //Performance mode
  //   break;

  //   case mode.driveStates::mode4:
  //   mode.driveMode4();             //Performance mode
  //   break;

  //   case mode.driveStates::none:
  //   mode.disconnectedBlink();
  //   break;
  // }


  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Motor State machine ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  mode.motor1.loop();
  mode.motor2.loop();
  // switch(mode.motor1.motorStatus)
  // {
  //   case mode.motor1.motorStates::FRONT:
  //   mode.motor1.front();
  //   break;

  //   case mode.motor1.motorStates::BACK:
  //   mode.motor1.back();
  //   break;

  //   case mode.motor1.motorStates::ENABLE:
  //   mode.motor1.enable();
  //   mode.buzz.initBuzzer();
  //   break;

  //   case mode.motor1.motorStates::DISABLE:
  //   mode.motor1.disable();
  //   mode.buzz.deinitBuzzer();
  //   break;

  //   case mode.motor1.motorStates::STOP:
  //   mode.motor1.stop();
  //   break;
  // }

  // switch(mode.motor2.motorStatus)
  // {
  //   case mode.motor2.motorStates::FRONT:
  //   mode.motor2.front();
  //   break;

  //   case mode.motor2.motorStates::BACK:
  //   mode.motor2.back();
  //   break;

  //   case mode.motor1.motorStates::ENABLE:
  //   mode.motor2.enable();
  //   break;

  //   case mode.motor1.motorStates::DISABLE:
  //   mode.motor2.disable();
  //   break;

  //   case mode.motor2.motorStates::STOP:
  //   mode.motor2.stop();
  //   break;
  // }

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LED State machines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  mode.redLed.loop();
  mode.blueLed.loop();

  // //red LED
  // switch(mode.redLed.ledStatus)
  // {
  //   case mode.redLed.ledStates::ON:
  //   mode.redLed.on();
  //   break;

  //   case mode.redLed.ledStates::OFF:
  //   mode.redLed.off();
  //   break;

  //   case mode.redLed.ledStates::TOGGLE:
  //   mode.redLed.toggle();
  //   break;

  //   case mode.redLed.ledStates::BLINKTWICE:
  //   mode.redLed.blinkTwice();
  //   break;
  // }

  // //Blue LED
  // switch(mode.blueLed.ledStatus)
  // {
  //   case mode.blueLed.ledStates::ON:
  //   mode.blueLed.on();
  //   break;

  //   case mode.blueLed.ledStates::OFF:
  //   mode.blueLed.off();
  //   break;

  //   case mode.blueLed.ledStates::TOGGLE:
  //   mode.blueLed.toggle();
  //   break;

  //   case mode.blueLed.ledStates::BLINKTWICE:
  //   mode.blueLed.blinkTwice();
  //   break;
  // }

  /* ---------------------- Battery events --------------------- */
  if( battery != Ps3.data.status.battery )
  {
      battery = Ps3.data.status.battery;
      debug("The controller battery is ");
      if( battery == ps3_status_battery_charging )      
      {
        debugln("Battery charging"); 
        write("charging");
      }
      else if( battery == ps3_status_battery_full )
      {
        debugln("FULL");  
        write("Battery FULL");
      }     
      else if( battery == ps3_status_battery_high )     
      {
        debugln("HIGH");
        write("HIGH");
      }
      else if( battery == ps3_status_battery_low)
      {
        debugln("LOW"); 
        write("Battery LOW");
      }       
      else if( battery == ps3_status_battery_dying )
      {
        debugln("DYING"); 
        write("Battery DYING");
      }
      else if( battery == ps3_status_battery_shutdown ) 
      {
        debugln("SHUTDOWN"); 
        write("Battery SHUTDOWN");
      }
      else 
      {
        debugln("UNDEFINED");
      }
  }

}

void setup()
{
  Serial.begin(115200);

  vTaskDelay(1000 / portTICK_PERIOD_MS);

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("24:62:ab:dd:a1:d6");

  menuListBegin();
  write("Ready");  

  mode.begin();

  debugln("Ready");

}

void loop()
{
  if(!Ps3.isConnected()); 
}

void onConnect()
{
  debugln("Connected."); 
  write("Connected");
}
