#include <Arduino.h>
// #include <NTPClient.h>
// #include <ESP8266WiFi.h>
// #include <WiFiUdp.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#else
#include <WiFi.h>
#include <HTTPClient.h>
#endif

#include "btn.h"
#include "led_sts.h"
#include "lcd.h"
#include "wifiConf.h"
#include "clock.h"
#include "weather.h"

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP);

void setup(void) {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.print("Starting; Compiled on ");
  Serial.println(__DATE__);
  Serial.println(__TIME__);
  Serial.println(__FILE__);  //__BASE_FILE__

  ledStsSetup();
  lcdSetupOne();
  setupWifi(&LCD);

  weatherSetup();
  Serial.println("Weater setup done");
  setupNTPClock();
  Serial.println("NTP setup done");
  lcdSetupTwo();
  Serial.println("LCD setup done");
  Serial.println("Setup done");
}

void loop() {
  getWeatherLoop(timerSyncDelay_w);
  getNTPtime(timerClockDelay);
  lcdLoop();
}
