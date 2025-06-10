#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

#include "wifi_conf.h"
#include "led_sts.h"
#include "lcd.h"
#include "clock.h"
#include "weather.h"

void setup(void) {
    Serial.begin(115200);
    delay(1000);
    Serial.println();
    Serial.print("Starting; Compiled on ");
    Serial.println(__DATE__);
    Serial.println(__TIME__);
    Serial.println(__FILE__);

    ledStsSetup();
    lcdSetupOne();
    LittleFS.begin();
    listFiles("/");
    setupWifi(&LCD);
    if (is_wifi_connected)
    {
        lcdSetupTwo();
        weather.setup();
        Serial.println("Weater setup done");
        setupNTPClock();
        Serial.println("NTP setup done");
        Serial.println("LCD setup done");
        Serial.println("Setup done");
    }
}

void loop() {
    delay(1);
    handleDnsLoop();
    weather.loop();
    getNTPtime(timer_clock_delay);
    lcdLoop();
}