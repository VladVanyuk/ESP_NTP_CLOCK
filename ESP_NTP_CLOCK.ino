#include <Arduino.h>

#include "lcd.h"
#include "wifiConf.h"
#include "clock.h"
#include "weather.h"


void setup(void) {
  Serial.begin(115200);
  delay(1000);
  Serial.print("Starting; Compiled on ");
  Serial.println(__DATE__);
  Serial.println(__TIME__);
  Serial.println(__FILE__); //__BASE_FILE__


  lcdSetupOne();
  setupWifi(&LCD);
    
 weatherSetup();
    setupNTPClock();
    lcdSetupTwo();

    Serial.println("Setup done");
}

void loop() {
    getWeatherLoop(timerSyncDelay_w);
    getNTPtime(timerClockDelay); 
    lcdLoop();

}
