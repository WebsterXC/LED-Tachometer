/* Header file for Buffered Map. This buffered map was created with the intention
   that data writes to the map faster than it can be written to an SD card. On
   each new data placement, the buffer is also written to. Depending on implementation,
   the map data buffer can be cleared during a burn task or a dedicated task, but in
   either case, if the buffer fills, it will ignore incoming data.
   */

/* Will Burgin (waburgin), 2015.
 * If you find my files helpful, please give credit!
 */

#ifndef BUFFERED_MAP_HEADER_FILE
#define BUFFERED_MAP_HEADER_FILE

#include "can.h"
#define DEFAULT_BUFFER_SIZE 128

//Directives that define whether the flush() method can be interrupted.
//#define POSTPONE_NO     //Dumps all data
//#define POSTPONE_YES    //Dumps data until specified time

typedef struct{
  short command;  //Hexadecimal PID code
  int value;      //Value currently associated with the PID
}entry;

class BufferedMap{
  private:
    //Array that stores all subscribed entrys, allocated on heap
    entry *table;
    unsigned int _nparams = NUM_PARAMS;

    //Data buffer stores the history of a single PID code value
    int *buffer;
    //Array max size and current size variables
    unsigned int container_size = DEFAULT_BUFFER_SIZE;
    unsigned int current_size = 0;

  public:
    BufferedMap();
    BufferedMap(int, int, short*);  //Buffer size (units, not bytes), number of params, short array of parameters
    ~BufferedMap();

    int get(short) const;   //Gets a value with key (Hex PID Code)
    void set(short, int);   //Set value with key

    int* flush();           //Dump buffer data

};

#endif

