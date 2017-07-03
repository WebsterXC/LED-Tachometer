/* Will Burgin (waburgin), 2015.
 * If you find my files helpful, please give credit!
 */

#ifndef LED_TACHOMETER_HEADER
#define LED_TACHOMETER_HEADER

/*Make pin assignments. LED Tachometer requires any 10 digital ports, SD card
  requires (for Mega 2560) pins 50, 51, 52 and 53.
  */

//LED's | GR = Green, YL = Yellow, RD = Red, BL_SHIFT = Blue Shift Light
#define GR1 49
#define GR2 47
#define GR3 45
#define GR4 43
#define YL1 41
#define YL2 39
#define YL3 37
#define RD1 35
#define RD2 33
#define BL_SHIFT 31
#define SPKR 30

//SD card fun
#define MOS 50
#define MIS 51
#define SD_CLK 52
#define SD_SS 53

//Define RPM to trigger shift light and speaker alarm
#define SHIFT_POINT 5750

class LEDTach{
  private:
    //Shift alarm function. Flashes BL_SHIFT light and sounds the speaker.
    void alarm() const;
    
    //Set the HIGH/LOW state of all pins. Requires an array of size 9, each boolean corresponding to LED state.
    void setAll(bool*) const;
    
  public:
    LEDTach();
    ~LEDTach();
    
    //Acutally updates the LED Tachometer
    void update(int) const;

    //Various status messages
    void ready();
    void waiting(int);
    void errorSD();
    void errorCAN();
};

#endif
