#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include "HX711.h"

const int PIN_SERVO_BASE   = 13;
const int PIN_SERVO_SHOULDER = 12;
const int PIN_SERVO_ELBOW  = 14;
const int PIN_SERVO_WRIST  = 27;
const int PIN_SERVO_GRIPPER = 26;

const int PIN_HX711_DOUT   = 4;
const int PIN_HX711_SCK    = 5;

Servo servoBase;
Servo servoShoulder;
Servo servoElbow;
Servo servoWrist;
Servo servoGripper;


// Initialize TCS34725 color sensor (integration time = 50ms, gain = 4X)
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Initialize HX711 load cell
HX711 scale;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Initializing 4-DOF Auto-Sorting Arm...");

  ESP32Servo::allocateTimer(0);
  ESP32Servo::allocateTimer(1);
  ESP32Servo::allocateTimer(2);
  ESP32Servo::allocateTimer(3);
  
  servoBase.attach(PIN_SERVO_BASE);
  servoShoulder.attach(PIN_SERVO_SHOULDER);
  servoElbow.attach(PIN_SERVO_ELBOW);
  servoWrist.attach(PIN_SERVO_WRIST);
  servoGripper.attach(PIN_SERVO_GRIPPER);

  homeArm();
  
  // Initialize Color Sensor
  if (tcs.begin()) {
    Serial.println("TCS34725 color sensor found!");
  } else {
    Serial.println("ERROR: TCS34725 not found. Check wiring!");
    while (1);
  }

  // Initialize Load Cell / HX711
  scale.begin(PIN_HX711_DOUT, PIN_HX711_SCK);
  scale.set_scale(2280.f); // Replace with calculated calibration factor
  scale.tare();            // Reset scale to 0
  Serial.println("HX711 scale initialized and tared.");
}

void loop() {
  // 1. Check if an item has slid into the bowl/weighing station
  if (scale.is_ready() && scale.get_units(3) > 5.0) { // Weight threshold
    float itemWeight = scale.get_units(5);
    
    // 2. Read colour immediately as the item sits in front of the sensor
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);
    
    Serial.print("Item in bowl -> Weight: "); Serial.print(itemWeight); Serial.print("g | ");
    Serial.print("R: "); Serial.print(r); Serial.print(" G: "); Serial.print(g); Serial.print(" B: "); Serial.println(b);

    // 3. Pick up the item directly from the bowl and sorts
    sortObjectFromBowl(r, g, b, itemWeight);

    // 4. Return arm to home position
    homeArm();
  }

  delay(100);
}