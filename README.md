### Author: William A. Burgin ###
### Project: CSE321, OBDII LED Tachometer ###

This repository represents my final project for my Embedded Systems course
(CSE321) at University at Buffalo. I've named it "Tach in a Box" - a series
of LED's visually display vehicle RPM and offers an adjustable shift light.
Being on a college budget, I completed the project using an Arduino, CAN Bus
shield (MCP2515/MCP2551), 10 various colored LED's, some wire, and a cardboard
box. Photos and videos of my device can be found in /documents. The rest of
this file is unchanged from the project submission README.

------------------------------------------------------------------------------

PREMIS: I am an avid racer who grew up watching Formula1 with my father almost
every weekend. After finally taking to the track myself very recently in the form of autocrossing,
I found that with a helmet on and adrenaline pumping it was simply impossible to get an accurate
reading of the tachometer. This is important because nearly every car on the track uses
a manual transmission and getting quicker lap times requires a deep understanding
of when to shift the car at different points in each gear.

SOLUTION: My device supplements the traditional tachometer by providing a heads-up display
of the vehicle's current RPM. Because it's a bright visual, racers can see the tachometer
out of the corner of their eye, eliminating the need to take eyes off the track. It uses
the automotive standard OBDII port to communicate with the CAN bus inside the vehicle
and retrieve the necessary information. When it's time to shift, a blue LED flashes.

Ten LED's are controlled using the Arduino's digital output ports, nine which
represent different ranges of the vehicle's current RPM, and a tenth LED which,
when the vehicle reaches it's preset SHIFT_POINT, flashes rapidly to let the
driver know it's time to shift.

Since I didn't have access to the traditional C++ STL, I built a small data structure
called a BufferedMap. It's similar to a standard C++ map, in that it uses <key, value> pairs
and holds on to them. However, most racers want data to review after practicing and racing,
so it's important to dump the data that was tracked to an SD card. Depending on the
filesystem and speed of SD card, this writing can take a comparably long amount
of time compared to pinging the CAN bus, so there needs to be a way to store a
certain pool of data until the processor has free time. This is where the
BufferedMap comes in; every call of the BufferedMap's set function also writes
a copy of the data to a buffer for writing later. When the executive feels it can
spare time away from updating the table to writing a buffer, it can call BufferedMap's
flush function, returning the buffer of data and clearing it for more incoming data.
(In the case of the LED Tachometer, long periods of steady RPM, such as highway driving,
 that doesn't require a quick refresh rate is a perfect time to give up a couple of update
 cycles to write to the SD card.)

 PARTS:
  - 1x Small Cardboard Box
  - 10x 5V LED's (4 Green, 3 Yellow, 2 Red, 1 Blue)
  - 10x 220Ohm Resistors
  - 50+ Jumper Cables + Spare 22ga Wire
  - Soldering Iron + Solder

  - Arduino Mega 2560 (8kB SRAM)
  - SparkFun CAN-Bus Shield | Part No. DEV-13262
  - 32GB MicroSD Card (Not Required for Normal Operation)

  CODE:
    All code is written in C++, and all but 1 third-party dependency file
    are in C++ as well. SparkFun includes a library on GitHub to get started
    with the CAN Bus shield, as well as critical bit operations to interface
    with the MCP2551.

---Standard Load Sequence & Messages---

1. Load BufferedMap and set aside memory for buffers.
      --No status messages.
2. Initialize the LED Tachometer. This establishes pin assignments and is the
    class that actually lights each LED.
      --No status messages.
3. Try to load the SD card. Disable SD read/write if unsuccessful.
      --Blue shift light blinks once: SD initialized OK
      --Two red lights blink twice: Failed to initialize SD card. Disabling SD read/write.
4. Establish a connection with MCP2551
      --No status messages.
5. Ping CAN bus repeatedly for an RPM value greater than 0.
      --All 10 LED's light up: Valid CAN data. Ready! (Move to loop).
      --Two LED's float around: Waiting for valid CAN data. Will wait for ~20 seconds.
      --Solid middle yellow LED: Couldn't get CAN data, timeout. Requires manual device restart.
