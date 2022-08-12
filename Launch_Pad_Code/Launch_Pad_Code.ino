#include <Servo.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;
Servo servo10;
Servo servo11;

// Pyrochannel pins
int Pyro1 = 19;
int Pyro2 = 20;
int Pyro3 = 21;
int Pyro4 = 22;
int Pyro5 = 23;

// LED Pins
int R_LED = 41;
int G_LED = 40;
int B_LED = 39;

// Timer for HC-12
unsigned long last = millis();

// Countdown variables
const int inputTime = 40000;              // How long the countdown should be (in ms)
long countdownTime;                       // Countdown counter variable
unsigned long minutes;                    // Countdown minutes
unsigned long seconds;                    // Countdown seconds
unsigned long countdownStartTime;         // Millis at countdown start
unsigned long elapsedTime;                // Time since countdown started
bool countdownRunning = false;            // True if contdown is running

// Launch event variables
unsigned long servo1234Time = 30000;      // Time when Stabilizer will open before Countdown hits 0 (in ms)
unsigned long servo67Time = 25000;        // Time when Strongback will retract before Countdown hits 0 (in ms)
unsigned long servo891011Time = 1000;     // Time when Launch Clamps will retract before Countdown hits 0 (in ms)
bool servo1234activated = false;          // True if servos have been activated
bool servo1234detached = false;           // True if servos have been detached
bool servo67activated = false;            // True if servos have been activated
bool servo67detached = false;             // True if servos have been detached

// Servo delay between activation and detaching (non blocking)
unsigned long servoDelay = 1000;          // In ms

void setup() {
  // Begin communication to HC-12
  Serial7.begin(9600);
  
  // Set LED pins as outputs
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);

  // Turn RED LED on
  digitalWrite(R_LED, LOW);
  digitalWrite(G_LED, HIGH);
  digitalWrite(B_LED, HIGH);

  // Set Pyrochannelpins to outputs
  pinMode(Pyro1, OUTPUT);
  pinMode(Pyro2, OUTPUT);
  pinMode(Pyro3, OUTPUT);
  pinMode(Pyro4, OUTPUT);
  pinMode(Pyro5, OUTPUT);

  // Set Pyro pins to low so they dont fire accidentially
  digitalWrite(Pyro1, LOW);
  digitalWrite(Pyro2, LOW);
  digitalWrite(Pyro3, LOW);
  digitalWrite(Pyro4, LOW);
  digitalWrite(Pyro5, LOW);

  // Set up display
  lcd.begin(16, 2);
  lcd.setBacklight(0x7);                 // White
  lcd.setCursor(0,0);
  lcd.print("Waiting for");
  lcd.setCursor(0,1);
  lcd.print("Launch command");

  delay(5000);

  // Attach Servos and bring them in start position
  servo1.attach(0);
  servo2.attach(1);
  servo3.attach(2);
  servo4.attach(3);
  
  servo1.write(95);
  servo2.write(85);
  servo3.write(95);
  servo4.write(85);
  
  delay(1000);
  
  servo1.detach();
  servo2.detach();
  servo3.detach();
  servo4.detach();

  delay(1000);
  
  servo5.attach(4);
  servo5.write(70);
  
  delay(1000);
  
  servo5.detach();

  delay(1000);
  
  servo6.attach(5);
  servo7.attach(6);
  
  servo6.write(85);
  servo7.write(110);

  delay(1000);
  
  servo6.detach();
  servo7.detach();

  delay(1000);

  servo8.attach(7);
  servo9.attach(8);
  servo10.attach(9);
  servo11.attach(10);
  
  servo8.write(5);
  servo9.write(5);
  servo10.write(5);
  servo11.write(5);
  
  delay(2000);
  
  servo8.detach();
  servo9.detach();
  servo10.detach();
  servo11.detach();
  
  // Turn GREEN LED on
  digitalWrite(R_LED, HIGH);
  digitalWrite(G_LED, LOW);
  digitalWrite(B_LED, HIGH);
}

void loop() {
  checkHC12();

  if (countdownRunning) {
    calculateCountdown();

    if(!servo1234activated && countdownTime < servo1234Time) {
      servo1.attach(0);
      servo2.attach(1);
      servo3.attach(2);
      servo4.attach(3);
      
      servo1.write(145);
      servo2.write(35);
      servo3.write(135);
      servo4.write(35);
      
      servo1234activated = true;
    }
    else if (!servo1234detached && countdownTime < (servo1234Time - servoDelay)) {
      servo1.detach();
      servo2.detach();
      servo3.detach();
      servo4.detach();

      servo1234detached = true;
    }
    else if(!servo67activated && countdownTime < servo67Time) {
      servo1.attach(0);
      servo2.attach(1);
      servo3.attach(2);
      servo4.attach(3);
      
      servo1.write(145);
      servo2.write(35);
      servo3.write(135);
      servo4.write(35);
      
      servo67activated = true;
    }
    else if (!servo67detached && countdownTime < (servo67Time - servoDelay)) {
      servo1.detach();
      servo2.detach();
      servo3.detach();
      servo4.detach();

      servo67detached = true;
    }
  }
}

void checkHC12() {
  if (Serial7.available()) {
    // Read serial input from HC-12 and convert to int
    int input = Serial7.parseInt();

    // Check if 250 ms have passed since last input check
    if (millis() - last > 250) {
      if (input == 1) {
        // Start Countdown
        countdownStartTime = millis();
        countdownRunning = true;
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Fire Pyrochannel in");
      }

      if (input == 2) {
        // Turn GREEN LED on
        digitalWrite(R_LED, HIGH);
        digitalWrite(G_LED, LOW);
        digitalWrite(B_LED, HIGH);

        // Turn off Pyro Channels
        digitalWrite(Pyro1, LOW);
        digitalWrite(Pyro2, LOW);
        digitalWrite(Pyro3, LOW);
        digitalWrite(Pyro4, LOW);
        digitalWrite(Pyro5, LOW);
      }
    }

    // Save current time
    last = millis();

    // Clear serial buffer for unwanted inputs
    Serial7.flush();
  }
}

void calculateCountdown() {
  // Calculate how much time has passed since the countdown started (in ms)
  elapsedTime = millis() - countdownStartTime;

  // Calculate how much time is left on the countdown (in ms)
  countdownTime = inputTime - elapsedTime;
  
  // Calculate how many minutes are left
  minutes = countdownTime / 60000;

  // Calculate how many seconds are left (and if there are more than 60, calculate left over)
  seconds = countdownTime / 1000 % 60;

  if (countdownTime <= 0) {
    countdownRunning = false;
    firePyrochannels();
  }
  else {
    // Print the Countdown at the second line
    lcd.setCursor(0,1);
    
    if (minutes < 10) {
      lcd.print("0");
    }
    lcd.print(minutes);
    
    lcd.print(":");
  
    if (seconds < 10) {
      lcd.print("0");
    }
    lcd.print(seconds);
  }
}

void firePyrochannels() {
  // Turn RED LED on
  digitalWrite(R_LED, LOW);
  digitalWrite(G_LED, HIGH);
  digitalWrite(B_LED, HIGH);

  //Fire Pyro Channels
  digitalWrite(Pyro1, HIGH);
  digitalWrite(Pyro2, HIGH);
  digitalWrite(Pyro3, HIGH);
  digitalWrite(Pyro4, HIGH);
  digitalWrite(Pyro5, HIGH);
}