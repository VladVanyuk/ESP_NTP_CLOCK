#ifndef CLOCK_NTP_H
#define CLOCK_NTP_H
#include <Arduino.h>
// #include <NTPClient.h>

#include <time.h>
// #include <WiFiUdp.h>

// #define UTC_OFFSET     0
// #define UTC_OFFSET_DST 0
const char *NTP_SERVER = "ch.pool.ntp.org";
const char *NTP_SERVER2 = "pool.ntp.org";
const char *NTP_SERVER3 = "europe.pool.ntp.org";

const char *TZ_INFO = "EET-2EEST,M3.5.0/3,M10.5.0/4"; // enter your time zone (https://remotemonitoringsystems.ca/time-zone-abbreviations.php)

tm timeinfo;
time_t now;
uint32_t lastNTPtime = 0;
uint32_t lastEntryTime = 0;

const uint32_t timerClockDelay = 120; //2mins

void showTime(tm localTime)
{
    Serial.print(localTime.tm_mday);
    Serial.print('/');
    Serial.print(localTime.tm_mon + 1);
    Serial.print('/');
    Serial.print(localTime.tm_year - 100);
    Serial.print('-');
    Serial.print(localTime.tm_hour);
    Serial.print(':');
    Serial.print(localTime.tm_min);
    Serial.print(':');
    Serial.print(localTime.tm_sec);
    Serial.print(" Day of Week ");
    if (localTime.tm_wday == 0)
        Serial.println(7);
    else
        Serial.println(localTime.tm_wday);
}

void showTimeShort(tm localTime)
{
    Serial.printf(
        "%04d-%02d-%02d %02d:%02d:%02d, day %d, %s time\n",
        localTime.tm_year + 1900,
        localTime.tm_mon + 1,
        localTime.tm_mday,
        localTime.tm_hour,
        localTime.tm_min,
        localTime.tm_sec,
        (localTime.tm_wday > 0 ? localTime.tm_wday : 7),
        (localTime.tm_isdst == 1 ? "summer" : "standard"));
}


// tm getTimeReducedTraffic(uint32_t sec)
// {
//     tm *ptm;
//     if ((millis() - lastEntryTime) <  sec)
//     {
//         now = lastNTPtime + (int)(millis() - lastEntryTime) / 1000;
//     }
//     else
//     {
//         lastEntryTime = millis();
//         lastNTPtime = time(&now);
//         now = lastNTPtime;
//         Serial.println("Get NTP time");
//     }
//     ptm = localtime(&now);
     
//     tm timeinfo_local = *ptm; 
//     showTime(timeinfo_local);
//     return timeinfo_local;
// }


bool getNTPtime(uint32_t sec)
{
    uint32_t start = millis();
    do
    {
        time(&now);
        localtime_r(&now, &timeinfo);
        Serial.print(".");
        delay(10);
    } while (((millis() - start) <= (1000 * sec)) && (timeinfo.tm_year < (2016 - 1900)));
    Serial.println();
    if (timeinfo.tm_year <= (2016 - 1900))
    {
        Serial.println("ERR: NTP time not set");
        return false; // the NTP call was not successful
    }

    char time_output[30];
    strftime(time_output, 30, "%a  %d-%m-%y %T", localtime(&now));
    Serial.println(time_output);
    return true;
}


void setupNTPClock()
{
  if(WiFi.status() == WL_CONNECTED){
    configTime(0, 0, NTP_SERVER);
    setenv("TZ", TZ_INFO, 1);
    Serial.println("Getting NTP time");
    if (getNTPtime(10))
    {
        Serial.print('*');
    }
    else
    {
        Serial.println("ERR: Time not set");
        ESP.restart();
    }
    
    lastNTPtime = time(&now);
    lastEntryTime = millis();
    showTime(timeinfo);
  }
}



#endif