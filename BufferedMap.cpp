/* Class file for the BufferedMap. Please see the header file for description. */

/* Will Burgin (waburgin), 2015.
 * If you find my files helpful, please give credit!
 */

#include <string.h>     //for memcpy on LN: 100
#include "BufferedMap.h"

//Creates a buffered map with default buffer size and all parameters initialized
BufferedMap::BufferedMap(){
  //Initializes the table of values with every available parameter.
  table = new entry[NUM_PARAMS];

  short codes[NUM_PARAMS] = { ENGINE_LOAD, THROTTLE_LOAD, TIMING_ADVANCE,
                              STFT1, STFT2, INJECTION_TIMING, ENGINE_FUEL_RATE,
                              ENGINE_RPM, ENGINE_SPEED, PRESSURE_BAROMETRIC,
                              PRESSURE_FUEL, PRESSURE_FUEL_RAIL, PRESSURE_EVAP_VAPOR,
                              PRESSURE_INTAKE_MAN, FLOW_RATE_MAF, PRESSURE_EXHAUST,
                              TEMP_COOLANT, TEMP_OIL, INTAKE_AIR_TEMP,
                              TURBO_INLET_PRESSURE, TURBO_BOOST_CONTROL,
                              TURBO_WASTEGATE, TURBO_RPM, TURBO_TEMP_0,
                              TURBO_TEMP_1 };

  for(int i = 0; i < NUM_PARAMS; i++){
    entry temp = {codes[i], 0};
    table[i] = temp;
  }

  //Create buffer with default size
  buffer = new int[DEFAULT_BUFFER_SIZE];
}

//Preferred constructor, requires a buffer size, number of codes being passed,
//and the PID codes for the map. Important NOT to change the params.
BufferedMap::BufferedMap(int buffer_size, int nparams, short params[]){
  //Initialize the table that holds <PID, value>
  table = new entry[nparams];

  //Initialize entry struct pairs to 0 for each code needed
  for(int i = 0; i < nparams; i++){
    entry temp = {params[i], 0};
    table[i] = temp;
  }

  //Create buffer with size of buffer_size
  buffer = new int[buffer_size];
  container_size = buffer_size;
  _nparams = nparams;
}

BufferedMap::~BufferedMap(){
  //Free memory
  delete[] buffer;
  delete[] table;
}

//------------------------------------------------------\\

//Returns a value from the map given a key.
int BufferedMap::get(short key) const{
  for(int i = 0; i < _nparams; i++){
    if(table[i].command == key){
      return table[i].value;
    }
  }
  return -1;
}

//Sets a value in the map given a key and value.
void BufferedMap::set(short key, int val){
  //Update table
  for(int i = 0; i < _nparams; i++){
    if(table[i].command == key){
      //Set data structure
      table[i].value = val;

      //Add to buffer if not full
      if(current_size < container_size){
        buffer[current_size] = val;
        current_size++;
      }
    }

  }

  return;
}

//Return buffer in order for the data to be written to SD card.
//First value in array IS ALWAYS LENGTH OF THE ARRAY, EXCLUSIVE
//Example: 4, 1200, 2400, 4500, 6000 (Array is size 5, but reports length 4).
//For more parameters, can be altered to reformat output.
int* BufferedMap::flush(){
  int buff_cpy[current_size + 1];
  buff_cpy[0] = current_size;     //Put number of values in array[0]

  //Set buff_cpy values offset by one. Delete values in buffer.
  for(int i = 0; i < current_size; i++){
    buff_cpy[i+1] = buffer[i];
    buffer[i] = 0;
  }

  //Replace buffer with new string format
  memcpy(buffer, buff_cpy, sizeof(int)*(current_size+1));
  //Reset current size
  current_size = 0;
  return buffer;
}

