#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <Stepper.h>

#define PIN 20
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500

const int stepsPerRevolution = 200;
Stepper StepperA(stepsPerRevolution, 5, 6, 3, 4);
Stepper StepperB(stepsPerRevolution, 28, 29, 30, 31);

unsigned long noLoadTime = 0;
unsigned long loadTime = 0;
unsigned long turnOnDelay = 2000;
unsigned long turnOffDelay = 2000;
unsigned long time;
bool loadState = false;
long duration;
int distance;

const int trigPin = 14;
const int echoPin = 12;

void setup() {

  Serial.begin(9600);

  StepperA.setSpeed(140);
  StepperB.setSpeed(180);

  pixels.begin();
  pixels.clear();

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
}

// 20ml 910
int a = 850;
char rx_byte;

void relay_on() { digitalWrite(2, LOW); }

void relay_off() { digitalWrite(2, HIGH); }

void sleepStepperA() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void sleepStepperB() {
  digitalWrite(28, LOW);
  digitalWrite(29, LOW);
  digitalWrite(30, LOW);
  digitalWrite(31, LOW);
}

void polanie() {
  Serial.println("polanie");
  relay_on();
  delay(200);
  StepperA.step(-a);
  relay_off();
  delay(150);
  StepperA.step(32);
  delay(100);
  StepperA.step(a - 32);
  delay(200);
  sleepStepperA();
}

void up8mm() {
  Serial.println("up8mm");
  StepperA.step(-200);
  delay(200);
  sleepStepperA();
}

void down8mm() {
  Serial.println("down8mm");
  StepperA.step(200);
  delay(200);
  sleepStepperA();
}

void prawo() {
  Serial.println("prawo");
  StepperB.step(-420);
  sleepStepperB();
}

void lewo() {
  Serial.println("lewo");
  StepperB.step(420);
  sleepStepperB();
}

void led_on() {
  Serial.println("led on");
  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {
    for (int a = 0; a < 200; a++) {
      pixels.setBrightness(a);
      delay(28);
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      pixels.show();
    }
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    pixels.show();
  }
}

void led_off() {
  Serial.println("led off");
  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {
    for (int a = 200; a > 0; --a) {
      pixels.setBrightness(a);
      delay(8);

      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      pixels.show();
    }
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
  }
}

void loop() {

  if (Serial.available() > 0) {
    rx_byte = Serial.read();

    switch (rx_byte) {

    case 'k':
      // lewo();
      polanie();
      // prawo();
      break;

    case 'w':
      relay_on();
      up8mm();
      relay_off();
      break;

    case 's':
      down8mm();
      break;

    case 'a':
      prawo();
      break;

    case 'd':
      lewo();
      break;

    case 'r':
      relay_on();
      break;

    case 't':
      relay_off();
      break;

    case 'l':
      led_on();
      break;

    case ';':
      led_off();
      break;
    }
  }

  time = millis();
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  delay(100);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print("czas  ");
  Serial.println(duration);

  if (loadState == false) {

    if (duration < 180) {
      noLoadTime = time;
      // Serial.println("0");
    }

    if (time - noLoadTime <= 2000) {
      // Serial.println(time - noLoadTime);
    }

    if ((time - noLoadTime) >= turnOnDelay) {
      // Serial.println("2000");
      loadState = true;
      lewo();
      polanie();
      prawo();
      led_on();
    }
  }
  if (loadState == true) {

    if (duration > 180) {
      loadTime = time;
      // Serial.println("2000");
    }

    if (loadTime - time >= 2000) {
      Serial.println(time - loadTime);
    }

    if ((time - loadTime) >= turnOffDelay) {
      loadState = false;
      led_off();
      // Serial.println("0");
    }
  }
}
