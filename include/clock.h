#pragma once

#include <Arduino.h>
#include <time.h>

const char *NTP_SERVER = "ch.pool.ntp.org";
const char *NTP_SERVER2 = "pool.ntp.org";
const char *NTP_SERVER3 = "europe.pool.ntp.org";
// timezone (Kyiv, Ukraine)
const char *TZ_INFO = "EET-2EEST,M3.5.0/3,M10.5.0/4";

tm time_info;
time_t now;
uint32_t last_ntp_time   = 0;
uint32_t last_entry_time = 0;

const uint32_t timer_clock_delay = 120; //2 mins

void showTime(tm local_time)
{
    Serial.print(local_time.tm_mday);
    Serial.print('/');
    Serial.print(local_time.tm_mon + 1);
    Serial.print('/');
    Serial.print(local_time.tm_year - 100);
    Serial.print('-');
    Serial.print(local_time.tm_hour);
    Serial.print(':');
    Serial.print(local_time.tm_min);
    Serial.print(':');
    Serial.print(local_time.tm_sec);
    Serial.print(" Day of Week ");

    local_time.tm_wday == 0 ? Serial.print(7) 
                            : Serial.print(local_time.tm_wday);
}

void showTimeShort(tm local_time)
{
    Serial.printf(
        "%04d-%02d-%02d %02d:%02d:%02d, day %d, %s time\n",
        local_time.tm_year + 1900,
        local_time.tm_mon + 1,
        local_time.tm_mday,
        local_time.tm_hour,
        local_time.tm_min,
        local_time.tm_sec,
        (local_time.tm_wday > 0 ? local_time.tm_wday : 7),
        (local_time.tm_isdst == 1 ? "summer" : "standard")
    );
}


bool getNTPtime(uint32_t sec)
{
    uint32_t start = millis();
    do
    {
        time(&now);
        localtime_r(&now, &time_info);
        Serial.print(".");
        delay(10);
    } while (((millis() - start) <= (1000 * sec)) && (time_info.tm_year < (2016 - 1900)));

    Serial.println();

    if (time_info.tm_year <= (2016 - 1900))
    {
        Serial.println("ERR: NTP time not set");
        return false; // the NTP call failed
    }

    char time_output[30];
    strftime(time_output, 30, "%a  %d-%m-%y %T", localtime(&now));
    Serial.println(time_output);
    return true;
}


void setupNTPClock()
{
    if (WiFi.status() == WL_CONNECTED)
    {
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
        
        last_ntp_time = time(&now);
        last_entry_time = millis();
        showTime(time_info);
    }
}