#include <Servo.h>
#include <Keypad.h>

Servo ServoMotor;
char* password = "888";  // Change the password here
int position = 0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {8, 7, 6, 9};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int RedpinLock = 12;
int GreenpinUnlock = 10;
int BuzzerPin = 13;  // Define buzzer pin

void setup() {
  pinMode(RedpinLock, OUTPUT);
  pinMode(GreenpinUnlock, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);  // Set buzzer pin as output
  ServoMotor.attach(11);
  LockedPosition(true);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key == '*' || key == '#') {
      position = 0;
      LockedPosition(true);
    } 
    else if (key == password[position]) {
      position++;
    } 
    else {
      // If the key does not match, reset position and trigger buzzer
      position = 0;
      digitalWrite(BuzzerPin, HIGH);
      delay(1000);  // Buzzer active for 1 second
      digitalWrite(BuzzerPin, LOW);
    }

    if (position == 3) {
      LockedPosition(false);
    }
  }
}

void LockedPosition(int locked) {
  if (locked) {
    digitalWrite(RedpinLock, HIGH);
    digitalWrite(GreenpinUnlock, LOW);
    ServoMotor.write(11);
  } else {
    digitalWrite(RedpinLock, LOW);
    digitalWrite(GreenpinUnlock, HIGH);
    ServoMotor.write(90);
  }
}
