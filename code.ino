#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "HX711.h"
#include "esp_sleep.h"
#include "driver/gpio.h"

#define OLED_SDA 4
#define OLED_SCL 3

#define HX_DT   5
#define HX_SCK  6

#define TOUCH_PIN 2

Adafruit_SSD1306 display(128, 32, &Wire, -1);
HX711 scale;

float calibration_factor = 1988; // adjust later

bool wasTouch = false;
uint32_t touchStart = 0;
bool longHandled = false;

bool timerRunning = false;
bool brewStarted = false;
uint32_t brewStart = 0;
uint32_t timerElapsed = 0;

void oledMsg(const char* line1, const char* line2 = "", const char* line3 = "", const char* line4 = "") {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(line1);
  if (line2[0]) display.println(line2);
  if (line3[0]) display.println(line3);
  if (line4[0]) display.println(line4);
  display.display();
}

void goDeepSleep() {
  oledMsg("GOING TO SLEEP", "tap to wake", "                  zzz", "             (-.-)");

  scale.power_down();
  delay(30);

  // avoid instant wake if finger still touching
  while (digitalRead(TOUCH_PIN) == HIGH) delay(10);

  display.ssd1306_command(SSD1306_DISPLAYOFF);
  delay(30);

  oledMsg("COFFEE TIME !!!");

  // deep-sleep wake on GPIO
  esp_deep_sleep_enable_gpio_wakeup(1ULL << TOUCH_PIN, ESP_GPIO_WAKEUP_GPIO_HIGH);

  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);

  // pull-down for stability
  pinMode(TOUCH_PIN, INPUT_PULLDOWN);

  Wire.begin(OLED_SDA, OLED_SCL);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  pinMode(HX_SCK, OUTPUT);
  digitalWrite(HX_SCK, LOW);

  scale.begin(HX_DT, HX_SCK);
  scale.set_gain(128);
  delay(200);

  scale.set_scale(calibration_factor);
  scale.tare();

  oledMsg("COFFEE TIME!!!", "tap when ready");

  while (digitalRead(TOUCH_PIN) == LOW) delay(10);
}

void loop() {
  bool touch = (digitalRead(TOUCH_PIN) == HIGH);

  // touch edge -> start timing
  if (touch && !wasTouch) {
    touchStart = millis();
    longHandled = false;
  }

  // long hold -> deep sleep
  if (touch && !longHandled && (millis() - touchStart >= 2500)) {
    longHandled = true;
    goDeepSleep();
    return;
  }

  // release edge:
  if (!touch && wasTouch) {
    uint32_t dur = millis() - touchStart;
    if (dur < 2500) {
      // stop timer
      if (timerRunning) {
        timerRunning = false;
        timerElapsed = millis() - brewStart;
      }
      // tare only if timer NOT running
      else {
        scale.tare();
        brewStarted = false;
        timerElapsed = 0;
      }
    }
  }

  wasTouch = touch;

  // Read weight
  float w = scale.get_units(5);

  // auto start timer
  if (!brewStarted && w > 0.1) {
  brewStarted = true;
  timerRunning = true;
  brewStart = millis();
}

  // currenmt time
  uint32_t currentTime = timerElapsed;

  if (timerRunning) {
    currentTime = millis() - brewStart;
  }

  uint32_t seconds = currentTime / 1000;
  uint32_t minutes = seconds / 60;
  seconds = seconds % 60;

  // display
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Weight:");

  display.setCursor(80,0);
  display.print("Time");

  display.setTextSize(2);
  display.setCursor(0, 12);
  display.print(w, 2);
  display.print("g");

  display.setCursor(80,12);
  display.print(seconds);
  display.print("s");

  display.display();
  delay(100);
}
