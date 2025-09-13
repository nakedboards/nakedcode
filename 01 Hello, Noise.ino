/*  
   ▓▓▒▒░░░░▒▒▓▓
   ▒▒░░░░░░░░▒▒   archean nakedboards
   ░░░░▒▒░░░▒░░   nakedcode - lesson 1
   ▒▒░░░░▒░░░░░   hello, noise
   ▒▒░░░░░░▒░▒▒
*/

#include <SPI.h>

void setup() {
  SPI.begin();
  pinMode(1, OUTPUT);
}

void loop() {
  digitalWrite(1, LOW);
  SPI.transfer16(random(4096) | 0x7000);
  digitalWrite(1, HIGH);
}

/*

[Hardware context]
- This code runs on the Archean synthesizer.
- Multiple SPI chips are present in the system, each connected to a different CS (Chip Select) pin.
- The DAC in use here is an MCP4921, responsible for the oscillator generating the noise.
- The CS pin for this specific DAC is connected to pin 1 on the Teensy 4.0.
- Pulling this pin LOW selects this DAC among others on the SPI bus. HIGH deselects it.

[About SPI]
- SPI (Serial Peripheral Interface) is a synchronous serial protocol for fast data transfer between a master (here Teensy) and slaves (DACs, etc.).
- It uses separate lines for MOSI (Master Out), MISO (Master In), SCK (Clock), and CS (Chip Select).
- In this case only MOSI, SCK, and CS are used, since the DAC does not send data back to the master.

[What this code does]
- Generates analog white noise by sending random 12-bit values to the MCP4921 DAC.
- Each loop iteration updates the DAC output, producing a constantly changing voltage (noise).

[How it works step by step]
1. SPI.begin() initializes the SPI hardware on the Teensy.
2. pinMode(1, OUTPUT) configures Teensy pin 1 as an output so we can control CS.
3. digitalWrite(1, LOW) selects the oscillator DAC by pulling CS low.
4. random(4096) produces a 12-bit random number (0–4095).
5. Bitwise OR "|" with 0x7000 sets the upper control bits for the DAC:
  - Bit 15 (A/B) is ignored in MCP4921 (single-channel DAC)
  - Bit 14 (BUF) = 1 → input buffer enabled
  - Bit 13 (GA) = 1 → gain ×1 (full output range)
  - Bit 12 (SHDN) = 1 → output active    
6. SPI.transfer16(...) sends the 16-bit word over SPI.
7. digitalWrite(1, HIGH) releases CS → DAC latches the voltage.

[16-bit word format for MCP4921]
------------------------------------------
| 15  | 14 | 13 | 12 | 11 ............ 0 |
------------------------------------------
| A/B |BUF | GA |SHDN| D11............D0 |
------------------------------------------

- A/B (bit 15) → ignored for MCP4921 (single-channel DAC)  
- BUF (bit 14) → input buffer (1 = buffered, 0 = unbuffered)  
- GA (bit 13) → gain (1 = ×1 full range, 0 = ×2 half range)  
- SHDN (bit 12) → output enable (1 = active, 0 = shutdown)  
- D11..D0 → 12-bit data value from random(4096)

[Bitwise OR lesson]
  - The operator "|" sets bits to 1 where the mask has 1s, and keeps bits unchanged where the mask has 0s.
  - Example:
  
      Data:   0000 0000 1010 1101   (0x00AD) (noise)
      Mask:   0111 0000 0000 0000   (0x7000) (mask)
      ----------------------------------------------
      Result: 0111 0000 1010 1101   (0x70AD)
     
  - In this project:
    - The random(4096) generates the lower 12 bits (D11..D0).
    - The mask 0x7000 forces BUF=1, GA=1, SHDN=1 in the control region (bits 14–12).
    - Zeros in the mask simply pass through the original data bits unchanged.

[Result]
- MCP4921 converts the 12-bit random numbers into analog voltages.
- Fast, continuous updates create audible white noise.

*/
