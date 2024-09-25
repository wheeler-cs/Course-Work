const int tempSense = A0;			 // Temperature reading pin
const float baseTemp = 20.0;	 	 // Baseline reference temperature
float voltage = 0.0;				 // Current voltage on A0
float realTemp = 0.0;				 // Current temp in Celcius

void setup() {
  Serial.begin(9600);				 // Set serial port to 9600 bits per second
  for (int i = 2; i < 5; i++)
	pinMode (i, OUTPUT);
}

void loop() {
    // Read value from analog pin into temp variable
	int temp = analogRead(tempSense);
  	Serial.print("\nCurrent Temperature: ");
  	Serial.print(temp);

    // Convert temp value into a voltage reading  
  	voltage = (temp / 1024.0) * 5.0;
  	Serial.print("\nCurrent Voltage: ");
  	Serial.print(voltage);

    // Convert voltage reading into temperature in degrees Celcius
  	realTemp = (voltage - 0.5) * 100;
  	Serial.print("\nReal Temperature: ");
  	Serial.print(realTemp);
  
  // Set lights on or off based on temperature reading
  if (realTemp < 0) {
    for (int i = 2; i < 5; i++)
      digitalWrite (i, LOW);
  }
  else if ((realTemp > 0) && (realTemp <= 20)) {
    digitalWrite (2, HIGH);
    digitalWrite (3, LOW);
    digitalWrite (4, LOW);
  }
  else if ((realTemp > 20) && (realTemp <= 100)) {
    digitalWrite (2, LOW);
    digitalWrite (3, HIGH);
    digitalWrite (4, LOW);
  }
  else if (realTemp > 100) {
    digitalWrite (2, LOW);
    digitalWrite (3, LOW);
    digitalWrite (4, HIGH);
  }
  else {
    for (int i = 2; i < 5; i++)
      digitalWrite (i, HIGH);
  }
}