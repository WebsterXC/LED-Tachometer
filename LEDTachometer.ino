
/***********************
 * 
 * LED Tachometer, "Tach in a Box".
 * Will Burgin (waburgin), 2015.
 * 
 * If you find my files helpful, please give credit!
 */

//Credit Toni Klopfenstein @ SparkFun Electronics.
#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>

//Includes
#include "BufferedMap.h"
#include "LEDTach.h"
#include "can.h"
#include "SDControl.h"

/********************************************************************************/
BufferedMap *pid_table;
LEDTach *tach;
CanSD *sdrw;
char message[DEFAULT_BUFFER_SIZE];

void setup() {
  int timeout = 0;
  
  //Set up data structure: Buffer size 425, requiring 1 parameter inside of the array req_codes.
  short req_codes[] = {ENGINE_RPM};
  pid_table = new BufferedMap(425, 1, req_codes);

  //Initialize LED Tachometer
  tach = new LEDTach();
  delay(200);

  //Call SD Card class constructor, then initialize.
  sdrw = new CanSD(pid_table);
  if(sdrw->init()){        //Blink BL_SHIFT if SD Card was initialized successfully
    digitalWrite(BL_SHIFT, HIGH);
    delay(400);          
    digitalWrite(BL_SHIFT, LOW);
  }else{
    tach->errorSD();      //Blink both red LED's if unsuccessful
    delay(500);
  }
  
  //Initialize Communication with CAN Bus at 500kbps as defined by Mazda HS_CAN. MS_CAN should use CANSPEED_125 and offers non-critical car data.
  if(Canbus.init(CANSPEED_500)){
    //Send 10 test pings, total wait time approx. 20 seconds.
    for(int i = 0; i < 10; i++){
      int temp_r = 0;
      Canbus.ecu_req(ENGINE_RPM, message);
      temp_r = atoi(message);
      delay(100);
                      
      if(temp_r > 0){   //If a valid response was recieved, display ready LED signal and begin looping.
        tach->ready();
        delay(100);
        break;
      }else{            
        tach->waiting(2);   //Repoll every 2000ms
        timeout++;
      }
      //delay(1500);        //This seems to be a good number to give the vehicle ample time to respond within set number of pings.
                            //Uncomment as a workaround for tach->waiting(int)
    }
    //No value returned from pings; Timeout. Illuminate YL2 until device restart.
    if(timeout >= 10){
      digitalWrite(YL2, HIGH);
      //Free up some memory, just in case.
      delete sdrw;
      delete pid_table;

      //REQUIRES DEVICE POWER CYCLE
      while(1){}
    }
  }else{
    //Error with CAN Bus shield / MCP2551 unreachable 
  }

//END SETUP
}

void loop() {
  
  //Get current engine RPM
  Canbus.ecu_req(ENGINE_RPM, message);
  int rounds = atoi(message);

  //Update data structure
  pid_table->set(ENGINE_RPM, rounds);
  
  //Update LED display
  tach->update(rounds);

  //Try to write to file
  sdrw->write(ENGINE_RPM);

  delay(30);    //CAN "ping rate", required as to not overload MCP2551, delay(20) seems to cause fluttering with LED's from non-accurate data
}
//EOF
