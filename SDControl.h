//Header file for SDControl. Methods open up SD card for data logging and stores a pointer to the PID Table

/* Will Burgin (waburgin), 2015.
 * If you find my files helpful, please give credit!
 */

#ifndef SD_CONTROL_HEADER_FILE
#define SD_CONTROL_HEADER_FILE

#include <SPI.h>
#include <SD.h>

#include "can.h"
#include "BufferedMap.h"

//SD Card Chip Select (SD Card uses pins 50 (MISO), 51 (MOSI), 52 (SCK), 53 (SS)//
#define SD_CHIP_SEL 53

class CanSD{
  private:
    BufferedMap *data;      //Pointer to BufferedMap with realtime data
    bool busOpen = false;   //Boolean that stores whether or not data logging is initialized and the SD card is ready for input

    //Data file (.txt)
    File dumpFile;
  
  public:
    CanSD(){};
    CanSD(BufferedMap*);
    ~CanSD();

    bool init();

    bool write(char*);
    bool write(short);    //Lookup realtime data using a (short)key and print to file
    bool write(int*, int);     //Print an array to the file (like a buffer)
};


#endif
