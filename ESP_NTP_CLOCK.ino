#include <Arduino.h>

#include "lcd.h"
#include "wifiConf.h"
#include "clock.h"
#include "weather.h"


void setup(void) {
  Serial.begin(115200);
  delay(1000);
    lcdSetupOne();
  setupWifi();
    
 weatherSetup();
    setupNTPClock();
    lcdSetupTwo();
}

void loop() {
    getWeatherLoop(timerSyncDelay_w);
    getNTPtime(timerClockDelay); 
    lcdLoop();

}
