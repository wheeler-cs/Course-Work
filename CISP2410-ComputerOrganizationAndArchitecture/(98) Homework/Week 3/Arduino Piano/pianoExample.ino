// An Arduino-based piano able to play 7 tones in multiple octaves.
// Author: amwheeler1

// Global Variable Declarations
// Input
const int noteA = 2, noteB = 3, noteC = 4, noteD = 5, noteE = 6,	// 7 Musical notes pinouts
	noteF = 7, noteG = 8;
const int octaveUp = 10, octaveDown = 9;							// Octave change pinouts

// Output
const int speakerOut = 13;											// Piezo speaker pin
const int green = A0, blue = A1, red = A2;							// RGB indicator pin

// Utility
double octaveMultiplier = 1;										// Multiplier to change frequency of triggered note
int triggeredKey = 0;												// Key pressed by user

// Program setup
void setup()
{
  for (int i = 2; i <= 10; i++)										// Set pins 2 - 10 as input
    pinMode (i, INPUT);
  pinMode(speakerOut, OUTPUT);										// Set pin speakerOut as output
  Serial.begin(9600);												// Initialize serial port at rate of 9600
}

// Recurring loop 
void loop()
{
  triggeredKey = 0;													// triggeredKey reset to 0 every loop cycle so last key
  																	// doesn't continually execute if nothing is pressed
  for (int i = 2; i <=10; i++) {									// Scan input buttons for pressed key
    if (digitalRead(i))
      triggeredKey = i;
  }
  switch (triggeredKey) {											// Compare triggeredKey against list of valid inputs
    case noteA:														// Every case has:
    	analogWrite(red, 255);										// At least 1 RGB LED line set
    	tone (speakerOut, 220*octaveMultiplier, 100);				// Some tone played for 100 milliseconds
    	break;
    case noteB:
    	analogWrite(red, 255);
    	analogWrite(green, 164);
    	tone (speakerOut, 247*octaveMultiplier, 100);
    	break;
    case noteC:
    	analogWrite (red, 255);
    	analogWrite (green, 255);
  		tone(speakerOut, 262*octaveMultiplier, 100);
    	break;
    case noteD:
    	analogWrite(green, 255);
    	tone(speakerOut, 294*octaveMultiplier, 100);
    	break;
    case noteE:
    	analogWrite(blue, 255);
   		analogWrite(green, 255);
    	tone(speakerOut, 330*octaveMultiplier, 100);
    	break;
    case noteF:
    	analogWrite(blue, 255);
    	tone(speakerOut, 349*octaveMultiplier, 100);
    	break;
    case noteG:
    	analogWrite(red, 255);
    	analogWrite(blue, 255);
   	 	tone(speakerOut, 392*octaveMultiplier, 100);
    	break;
    case octaveUp:
    	analogWrite(green, 255);
    	octaveMultiplier *= 2;
    	delay(500);													// Delay required so if key is pressed and held for a
    	break;														// moment too long, octave won't jump too much; this
    case octaveDown:												// is the case for both octaveUp and octaveDown
    	analogWrite(red, 255);
    	octaveMultiplier /= 2;
    	delay(500);
    	break;
    default:														// If there is no key pressed, set RGB LED to unlit
    	analogWrite(red, 0);
  		analogWrite(green, 0);
  		analogWrite(blue, 0);
  }

  // Serial Port Information
  // Print octave multiplier
  Serial.print("\nOctave Multiplier: ");
  Serial.print(octaveMultiplier);
  
  // Print key currently being pressed
  Serial.print("\nTriggered Key: ");
  Serial.print(triggeredKey);
}
