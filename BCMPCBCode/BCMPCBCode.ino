#include "Timer.h"
#include "Keyboard.h"

Timer timer;
const int buttonPin = 8;
const int signalPin = 4;
const int pausePin = 7;
int buttonPressed = 0;
int prevRoundState = 0;
int prevState = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // Debounce delay in milliseconds
int roundCount = 0;
int prevPauseState = 0;
int isPaused = 0;
int pauseReading = 0;
//int photoDiode = 6;
int photoDiode = A7;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(signalPin, OUTPUT);
  pinMode(pausePin, INPUT);
  //pinMode(photoDiode, INPUT);
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  int photoSenseValue = analogRead(photoDiode); // was digital read
  //Serial.println(photoSenseValue);

  // SET PHOTODIODE PIN TO D6 FOR BNC CONNECTION
  if (photoSenseValue >= 5 && prevRoundState == 0) {
    prevRoundState = 1;
    delay(250); // Debounce delay
  }
  
  if (photoSenseValue <= 3 && prevRoundState == 1) {
    roundCount++;
    Serial.print("Round ");
    Serial.println(roundCount);
    Serial.println(" ");
    prevRoundState = 0;
    timer.start();
  }
  

  // down button code here
  int reading = digitalRead(buttonPin);

  // Debouncing logic
  if (reading != prevState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonPressed) {
      buttonPressed = reading;

      if (buttonPressed == HIGH) {
        Serial.print("Button pressed at: ");
        Serial.print(timer.read());
        Serial.println(" ms");
        Keyboard.press(KEY_DOWN_ARROW);
        digitalWrite(signalPin, HIGH);
      } 
      
      if (buttonPressed == LOW) {
        Serial.print("Button released at: ");
        Serial.print(timer.read());
        Serial.println(" ms");
        Serial.println(" ");
        Keyboard.release(KEY_DOWN_ARROW);
        digitalWrite(signalPin, LOW);
      }
    }
  }

  prevState = reading;

  // pause button code here
  pauseReading = digitalRead(pausePin); 
  
  if (pauseReading == HIGH && prevPauseState == LOW) {
    // Button was just pressed
    Keyboard.print("P");
    if (isPaused == 1) {
      Serial.println("\nGame Unpaused\n");
      isPaused = 0;
    } 
    else if (isPaused == 0) {
      Serial.println("\nGame Paused\n");
      isPaused = 1;
    }
    delay(250); // Debounce delay
    prevPauseState = HIGH;
  } else if (pauseReading == LOW && prevPauseState == HIGH) {
    // Button was just released
    prevPauseState = LOW;
  }

}
