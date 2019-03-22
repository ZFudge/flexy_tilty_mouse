#include <Mouse.h>

const int X_FLEX_PIN = A0;
const int Y_FLEX_PIN = A1;
const int xTiltPin = 12;
const int yTiltPin = 13;

const float VCC = 4.98;                     // Measured voltage of Ardunio 5V line
const float R_DIV = 47500.0;                // Measured resistance of 47.k resistor

const float STRAIGHT_RESISTANCE = 37300.0;  // resistance when straight
const float BEND_RESISTANCE = 90000.0;      // resistance at 90 deg

void setup() {
  Serial.begin(9600);
  pinMode(xTiltPin, INPUT);
  pinMode(yTiltPin, INPUT);
  
  pinMode(X_FLEX_PIN, INPUT);
  pinMode(Y_FLEX_PIN, INPUT);
}

void loop() {
  int xTiltVal = digitalRead(xTiltPin);
  int yTiltVal = digitalRead(yTiltPin);
  Serial.println("xTiltVal" + String(xTiltVal));
  Serial.println("yTiltVal" + String(yTiltVal));
  
  int xflexADC = analogRead(X_FLEX_PIN);
  int yflexADC = analogRead(Y_FLEX_PIN);
  
  float xflexV = xflexADC * VCC / 1023.0;
  float xflexR = R_DIV * (VCC / xflexV - 1.0);
  
  float yflexV = yflexADC * VCC / 1023.0;
  float yflexR = R_DIV * (VCC / yflexV - 1.0);
  
  Serial.println("Resistance: " + String(xflexR) + " ohms");
  Serial.println("Resistance: " + String(yflexR) + " ohms");

  float xAngle = map(xflexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
  Serial.println("Bend: " + String(xAngle) + " degrees");
  Serial.println();

  delay(500);
}


