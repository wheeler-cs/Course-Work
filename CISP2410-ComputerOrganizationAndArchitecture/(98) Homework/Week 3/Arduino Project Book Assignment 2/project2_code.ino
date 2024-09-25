int inputLine = 2;				// Alias for pin 2
int grn = 3, ylw = 4, blu = 5;	// Alias for pins relating to LED color
int pushButton = 0;				// Current state of circuit


void setup(){
  pinMode (inputLine, INPUT);	// Digital line 2 is input
  pinMode (grn, OUTPUT);		// Digital line 3 is output
  pinMode (ylw, OUTPUT);		// Digital line 4 is output
  pinMode (blu, OUTPUT);		// Digital line 5 is output
}

void loop(){
    // Read if button is pushed
	pushButton = digitalRead(inputLine);

    // Turn lights on or off based on if button is pushed
 	if (pushButton == LOW) {
    	digitalWrite (grn, HIGH);
      	digitalWrite (ylw, HIGH);
      	digitalWrite (blu, HIGH);
  	}
    else {
    	digitalWrite (grn, LOW);
    	
    	digitalWrite (ylw, HIGH);
    	digitalWrite (blu, LOW);
    
    	delay(250);
    
    	digitalWrite (ylw, LOW);
    	digitalWrite (blu, HIGH);
    
    	delay (250);
  }
}