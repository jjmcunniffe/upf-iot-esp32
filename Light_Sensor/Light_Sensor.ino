#include <Adafruit_NeoPixel.h>
#define LIGHT_SENSOR_PIN 3
#define LED_PIN 18
Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);

// For controlling the built-in RGB led.
enum {NONE, RED, ORANGE, GREEN};
int ledColor = NONE;

void setup() {
  // Initialise built-in LED.
  pixels.begin();
  // Initialise serial output.
  Serial.begin(9600);
}

void loop() {
  // Read the value at pin 36.
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  // Output value to Serial Monitor.
  Serial.print("Raw Light Sensor Reading = ");
  Serial.print(analogValue);

  // Categorise the brightness level.
  if (analogValue < 40) {
    // Turn off the LED.
    ledColor = NONE;
    Serial.println(" => Dark");
  } else if (analogValue < 1500) {
    ledColor = RED;
    Serial.println(" => Low");
  } else if (analogValue < 2500) {
    ledColor = ORANGE;
    Serial.println(" => Medium");
  } else {
    ledColor = GREEN;
    Serial.println(" => High");
  }

  // Add a newline in Serial for cleanliness.
  Serial.println();

  switch(ledColor) {
    case NONE:
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.show();
      break;
    case RED:
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));
      pixels.show();
      break;
    case ORANGE:
      pixels.setPixelColor(0, pixels.Color(255, 128, 0));
      pixels.show();
      break;
    case GREEN:
      pixels.setPixelColor(0, pixels.Color(0, 255, 0));
      pixels.show();
      break;
    default:
      break;
  }
  
  delay(1000);
}
