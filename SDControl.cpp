/* Will Burgin (waburgin), 2015.
 * If you find my files helpful, please give credit!
 */

#include "SDControl.h"

//Constructor requires a pointer to the pid map
CanSD::CanSD(BufferedMap *bfmap){
  data = bfmap;
}

CanSD::~CanSD(){
  busOpen = false;
  dumpFile.println("---End logging---");
  dumpFile.close();
  delete data;
}

//Initialize FAT16/32 formatted SD card in the SD Card slot. Returns true/false if initializing the SD card was a success or not.
bool CanSD::init(){
  //Open SD Card for reading
  if(SD.begin(SD_CHIP_SEL)){
    busOpen = true;                //Set openBus flag
    dumpFile = SD.open("tachometer.txt", FILE_WRITE);   //Open file to write to
    dumpFile.println("---Start new logging---");        //Insert header for readability   

    return true;
  }
  return false;
}

//Write string to file.
bool CanSD::write(char str[]){
  if(busOpen == true){
    dumpFile.println(str);
    return true;
  }
  return false;
}


//Write a specific data point, get the information realtime from the BufferedMap using a key.
bool CanSD::write(short key){
  if(busOpen == true){
    dumpFile.println(data->get(key), DEC);
    return true;
  }
  return false;
}

//Write array of data, format specific
// [ NUM_DATA , DATA0, DATA1, DATA2, ...]
bool CanSD::write(int *arr, int size){
  if(busOpen == true){
    for(int i = 1; i <= arr[0]; i++){
     dumpFile.println(arr[i], DEC);
    }
    return true;
  }
  return false;
}

