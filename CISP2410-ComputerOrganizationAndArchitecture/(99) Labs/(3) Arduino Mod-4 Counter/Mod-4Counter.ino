// An Arduino program that counts in mod-4 binary, taking input
//	from 2 pushbuttons and sending the current state to 2 LEDs
// Author: amwheeler1


// Global constants for pins
// Input
const int upPush = 2, downPush = 3;		// Button pins

// Output
const int lowBit = 4, highBit = 5;		// LED pins

// Program state variables
int counter = 0;						// Counter for mod-4


// Setup subroutine
void setup() {
  // Set pins tied to push buttons to INPUT
  pinMode (upPush, INPUT);				// Increment counter button
  pinMode (downPush, INPUT);			// Decrement counter button
  
  // Set pins tied to LEDs to OUTPUT
  pinMode (lowBit, OUTPUT);				// Low-order bit
  pinMode (highBit, OUTPUT);			// High-order bit
}


// Main loop subroutine
void loop() {
  
  // Detect if a button is pressed
  if (digitalRead(upPush) == HIGH)
    counter++;
  else if (digitalRead(downPush) == HIGH) {
    counter--;
    if (counter < 0)					// Wrap around value if counter < 0
      counter += 4;
  }
  
  // Check binary value of counter to determine which LEDs are high
  if ((counter & 1) == 1)				// if bit 0 of counter is high
    digitalWrite(lowBit, HIGH);
  else
    digitalWrite (lowBit, LOW);
  
  if ((counter & 2) == 2)				// if bit 1 of counter is high
    digitalWrite (highBit, HIGH);
  else
    digitalWrite (highBit, LOW);
  
  delay (350);							// Delay for human usability
}
