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
    }
    else if(stateCount == 2)
    {
      Ps3.setPlayer(2);
      mode.driveStatus = mode.driveStates::mode2;
    }
    else if(stateCount == 3)
    {
      Ps3.setPlayer(3);
      mode.driveStatus = mode.driveStates::mode3;
    }
    else if(stateCount == 4)
    {
      Ps3.setPlayer(4);
      mode.driveStatus = mode.driveStates::mode4;
    }
  }

  mode.loop();

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Motor State machine ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  mode.motor1.loop();
  mode.motor2.loop();

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LED State machines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  mode.redLed.loop();
  mode.blueLed.loop();

  /* ---------------------- Battery events --------------------- */
  if( battery != Ps3.data.status.battery )
  {
      battery = Ps3.data.status.battery;
      debug("The controller battery is ");
      if( battery == ps3_status_battery_charging )      
      {
        debugln("Battery charging"); 
      }
      else if( battery == ps3_status_battery_full )
      {
        debugln("FULL");  
      }     
      else if( battery == ps3_status_battery_high )     
      {
        debugln("HIGH");
      }
      else if( battery == ps3_status_battery_low)
      {
        debugln("LOW"); 
      }       
      else if( battery == ps3_status_battery_dying )
      {
        debugln("DYING"); 
      }
      else if( battery == ps3_status_battery_shutdown ) 
      {
        debugln("SHUTDOWN"); 
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
}

