#include <Mouse.h>

// Flex sensor pins - 47K ohms
const int X_FLEX_PIN = A0;
const int Y_FLEX_PIN = A1;

const float VCC = 4.98;                     // Measured voltage of 5V line
const float R_DIV = 47000.0;                // Measured resistance of 47k resistor

const float STRAIGHT_R = 37300.0;           // resistance when straight
const float BEND_R = 90000.0;               // resistance at 90 deg

const int bend_threshold = 600;

// Tilt sensor pins
const int xTiltPin = 11;
const int yTiltPin = 13;

const int buttonPin = 2;     // the number of the pushbutton pin

int print_readings = 1;

void setup() {
  Serial.begin(9600);
  Mouse.begin();
  
  pinMode(xTiltPin, INPUT);
  pinMode(yTiltPin, INPUT);
  
  pinMode(X_FLEX_PIN, INPUT);
  pinMode(Y_FLEX_PIN, INPUT);
  
  pinMode(buttonPin, INPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
    
  int xFlexADC = analogRead(X_FLEX_PIN);
  int yFlexADC = analogRead(Y_FLEX_PIN);

  int xInput = check_bend_threshold(xFlexADC);
  int yInput = check_bend_threshold(yFlexADC);

  if (xInput || yInput) {
    mouseMovement(xInput, yInput, xFlexADC, yFlexADC);
  }

  if (print_readings) {
    int readings[4] = { xFlexADC, yFlexADC, xInput, yInput };
    printReadings(readings);
  }
  
  delay(100);
}

void mouseMovement(int xInt, int yInt, int xFlex, int yFlex) {
  int x = 0;
  int y = 0;
  if (xInt) {
    int xTiltVal = digitalRead(xTiltPin);
    Serial.println("X TILT: " + String(xTiltVal));
    x = 670 - xFlex;
    x = xTiltVal ? 5 : -5;
  }
  if (yInt) {
    int yTiltVal = digitalRead(yTiltPin);
    Serial.println("Y TILT: " + String(yTiltVal));
    y = 670 - yFlex;
    y = yTiltVal ? 5 : -5;
  }
  Mouse.move(x, y, 0);
}

int check_bend_threshold(float bend) {
  return bend < bend_threshold;
}

void printReadings(int readings[4]) {
  Serial.println("X ADC: " + String(readings[0]));
  Serial.println("Y ADC: " + String(readings[1]));
  Serial.println("X Input: " + String(readings[2]));
  Serial.println("Y Input: " + String(readings[3]));
  Serial.println("\n\n\n");
}

