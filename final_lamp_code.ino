#include <RTClib.h>
#include <Wire.h>

RTC_DS3231 rtc;

char t[32];

int alarmHour = 10;
int alarmMinute = 20;
int num = 1;

int switch_pin = 6;

byte leds = 0;

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        7
#define NUMPIXELS 24

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  rtc.begin();

  pixels.begin();
  pixels.clear();

  pinMode(switch_pin, INPUT);
}

void loop() {
  int beginHour;
  int beginMinute;
  if (alarmMinute < 5) {
    beginHour = beginHour - 1;
    beginMinute = 55 + alarmMinute;
  }
  else {
    beginHour = alarmHour;
    beginMinute = alarmMinute - 5;
  }
  DateTime now = rtc.now();
  Serial.print("H: ");
  Serial.print(now.hour());
  Serial.print(" M: ");
  Serial.println(now.minute());

  if (num < 255) {
    num++;
    delay(1176);
  }

  if (digitalRead(switch_pin) == HIGH) {
    for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));

      pixels.show();   // Send the updated pixel colors to the hardware
    }
  }
  if (digitalRead(switch_pin) == LOW) {
    if ((now.hour() >= beginHour) && (now.minute() >= beginMinute)) {
      for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(num, num, num));

        pixels.show();   // Send the updated pixel colors to the hardware
      }
    }
  }
  if (now.hour() > alarmHour + 1) {
    for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(100, 100, 100));

      pixels.show();   // Send the updated pixel colors to the hardware
    }
  }
}
