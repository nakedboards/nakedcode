/*  **
      ** /\       
        /  \       archean nakedboards
       /    \      nakedcode - lesson 0
      /      \     hello, ide
     /   /\   \   
 ___/_ _/__\___\________________________
   
Before obtaining sound, we need a working development environment for Teensy 4.0.

[Step 1: Install Arduino IDE]
- Download and install Arduino IDE from: https://www.arduino.cc/en/software
- This will be the main environment for writing and compiling code.

[Step 2: Install Teensyduino]
- Download and install Teensyduino from: https://www.pjrc.com/teensy/teensyduino.html
- Teensyduino extends Arduino IDE with Teensy support.
- Together they provide compilation + upload.

[Step 3: Teensy Loader]
- Teensy Loader comes with Teensyduino.
- It handles the actual firmware upload to the Teensy board.
- Works in the background whenever you press "Upload" in Arduino.

[Step 4: Configure Arduino IDE]
- Tools → Board → select "Teensy 4.0"
- Tools → USB Type → select "MIDI"
- Tools → CPU Speed → select "600 MHz"
- Tools → Optimize → select "Faster"
- Tools → Port → select the port corresponding to your Teensy device

[Next]
Proceed to Lesson 01: White Noise.

*/
