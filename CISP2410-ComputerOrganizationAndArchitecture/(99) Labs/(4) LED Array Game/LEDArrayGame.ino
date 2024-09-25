// An Arduino program to simulate a game where the player's goal
//	is to find an enemy.
// Author: amwheeler1

// Output Pins
// LED map to allow access to the LEDs in the same way a 2D array
// can be accessed
const int LEDMAP [3] [3] = {{2, 5, 8}, {3, 6, 9}, {4, 7, 10}};
const int SPEAKER = A5;


// Input Pins
const int DPADMOVE = A0, DPADHIT = A1;
const int TEMPSENS = A3;

// Game State
int enemyX = 2, enemyY = 2;
int playerX = 0, playerY = 0;
int keyPressLeft = 0, keyPressRight = 0;
bool endGame = false;

// Game Function Prototypes
void move(int yMovement, int xMovement);
void renderPlayer (int xLoc, int yLoc);
bool hit(int xDisplacement, int yDisplacement);
void stopGame();
void placeCharacter ();
void printSerialInfo ();


// Pre-Loop program setup
//	Sets input and output pins, sets the RNG seed based on
//	temperature, and initiates the Serial Monitor; all LEDs are
//	set to HIGH when this function begins, and all LEDs are set
//	to LOW when it has finished execution
void setup()
{
  for (int i = LEDMAP[0][0]; i <= LEDMAP[2][2]; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  
  // Set pin modes
  pinMode(DPADMOVE, INPUT);
  pinMode(DPADHIT, OUTPUT);
  pinMode(TEMPSENS, INPUT);
  
  // Set RNG and generate character positions
  randomSeed(analogRead(TEMPSENS));
  placeCharacter();
  
  // Initiate serial
  Serial.begin(9600);
  delay(3000);
  
  for(int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      digitalWrite(LEDMAP[i] [j], LOW);
  }
}


// Main program loop
//	Mainly detects key presses and goes to corresponding functions
//	based on the presses; also goes to the renderPlayer and
//	printSerialInfo functions
void loop()
{
  // Get key presses on push buttons
  keyPressLeft = analogRead(DPADMOVE);
  keyPressRight = analogRead(DPADHIT);
  
  // Test movement key presses against valid inputs
  switch (keyPressLeft) {
    case 114:		// Move Up
    	move (0, -1);
    	break;
    case 25:		// Move Down
    	move (0, 1);
    	break;
    case 13:		// Move Left
    	move (-1, 0);
    	break;
    case 5:			// Move Right
    	move(1, 0);
    	break;
  }
  
  // Test hit key presses against valid inputs
  switch (keyPressRight) {
    case 21:		// Hit Up
    	endGame = hit (0, -1);
    	break;
    case 4:			// Hit Down
    	endGame = hit (0, 1);
    	break;
    case 2:			// Hit Left
    	endGame = hit (-1, 0);
    	break;
    case 1:			// Hit Right
    	endGame = hit(1, 0);
    	break;
  }
  
  // Detect the game's "endGame" state
  if (endGame == true)
    stopGame();
  
  // Redraw player
  renderPlayer(playerX, playerY);
  
  // Print current game state to Serial Monitor
  printSerialInfo();
  delay(250);			// Delay for human usability
}


// move
// Returns: Nothing
// Parameters:
//		xMovement: Displacement on the x-axis the player should
//			undergo
//		yMovement: Displacement on the y-axis the player should
//			undergo
// Moves the player on the x- and y-axis based on displacement
//	input; collission detection is also determined here, and a
//	tone is set to play based on whether the move is valid or not
void move (int xMovement, int yMovement) {
  // Get what would be player's new location
  int newX = playerX + xMovement;
  int newY = playerY + yMovement;
  
  // Test if player's new location is valid
  if (xMovement != 0) {
  	if (((newX) <= 2) && ((newX) >= 0)){	// Valid x-movement
    	playerX += xMovement;
    	tone(SPEAKER, 300, 100);
  	}
    else									// Invalid: do nothing
    	tone(SPEAKER, 100, 100);
  }
  else if (yMovement != 0) {
  	if (((newY) <= 2) && ((newY) >= 0)) {	// Valid y-movement
   	 playerY += yMovement;
  		tone(SPEAKER, 300, 100);
  	}
  	else									// Invalid: do nothing
    	tone(SPEAKER, 100, 100);
  }
}


// renderPlayer
// Returns: Nothing
// Parameters:
//		xLoc: Player's current location on the x-axis
//		yLoc: Player's current location on the y-axis
// Clears the "screen" by settings all LEDs to LOW then "draws"
// 	the character by setting the corresponding LED to high based
// 	on their coordinates
void renderPlayer (int xLoc, int yLoc) {
  // Set all LEDs to low temporarily
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++)
      digitalWrite(LEDMAP[i][j], LOW);
  }
  // Draw player's current location
  digitalWrite(LEDMAP[xLoc] [yLoc], HIGH);
}


// hit
// Returns: bool, if the hit attempt was a success
// Parameters:
//		xDisplacement: Displacement relative to the player on the
//			x-axis where the hit should take place
//		yDisplacement: Displacement relative to the player on the
//			y-axis where the hit should take place
// Determines the space the player intends to hit relative to
//	their current position; a tone plays based on the success
//	of the hit and a value returned with there was a hit (true)
//	or not (false)
bool hit(int xDisplacement, int yDisplacement) {
  // Determine hit displacement
  int hitSpaceX = xDisplacement + playerX;
  int hitSpaceY = yDisplacement + playerY;
  
  // Detect if the enemy is hit
  if ((hitSpaceX == enemyX) && (hitSpaceY == enemyY)) {
    tone(SPEAKER, 440, 200);
    return true;		// Is hit
  }
  else {
    tone(SPEAKER, 50, 200);
    return false;		// Is not hit
  }
}


// stopGame
// Returns: Nothing
// Parameters: None
// Puts the game in a "complete" state indefinitely while
//	simultaneously lighting the LEDs in a cascade pattern on
//  repeat
void stopGame() {
  // Erase player's location from LEDs
  digitalWrite(LEDMAP[playerX] [playerY], LOW);
  
  // Infinite loop to draw cascade effect to LED grid
  while (endGame == true) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        digitalWrite(LEDMAP[i][j], HIGH);
        delay(500);
      }
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        digitalWrite(LEDMAP[i][j], LOW);
        delay(500);
      }
    }
  }
}


// placeCharacter
// Returns: Nothing
// Parameters: None
// Places the player and enemy in random places based on the
//	RNG seed set by the temperature sensor
void placeCharacter () {
  // Randomly generate the player's and enemy's locations,
  // regenerating if they are the same
  do {
    playerX = random(3);
    playerY = random(3);
    enemyX = random(3);
    enemyY = random(3);
  } while ((playerX == enemyX) && (playerY == enemyY));
}


// printSerialInfo
// Returns: Nothing
// Parameters: None
// Prints the current state of the game out to the Serial Monitor
void printSerialInfo () {
  Serial.print("\nTemperature Output: ");
  Serial.print(analogRead(TEMPSENS));
  Serial.print("\nPlayer Location\nX: ");
  Serial.print(playerX);
  Serial.print("  Y: ");
  Serial.print(playerY);
  Serial.print("\nEnemy Location:\nX: ");
  Serial.print(enemyX);
  Serial.print("  Y: ");
  Serial.print(enemyY);
  Serial.print("\nLeft Key Press: ");
  Serial.print(keyPressLeft);
  Serial.print("\nRight Key Press: ");
  Serial.print(keyPressRight);
}
