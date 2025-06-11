#pragma once

#include <Arduino.h>

class SwitchInput
{
public:
    enum DisplayState
    {
        SHOW_TIME,
        SHOW_TEMP,
        SHOW_HUM,
        SHOW_ALL
    };

    SwitchInput(uint8_t bit0, uint8_t bit1, uint8_t bit2, uint8_t bit3, uint16_t debounce_ms = 100)
        : pins{bit0, bit1, bit2, bit3}, debounce_delay(debounce_ms)
        {
            for (int i = 0; i < 3; ++i)
            {
                pinMode(pins[i], INPUT_PULLUP);
                
            }
            pinMode(D0, INPUT);
    }

    void update() {
        uint8_t raw = read_raw();

        if (raw != last_raw)
        {
            last_change = millis();
            last_raw = raw;
        }
        else if (millis() - last_change >= debounce_delay && raw != raw_value)
        {
            raw_value = raw;
            current_display = map_raw_to_state(raw_value);
            value_changed = true;
        }
        else
        {
            value_changed = false;
        }
    }

    bool hasChanged() const
    {
        return value_changed;
    }

    DisplayState get_state() const
    {
        return current_display;
    }

    uint8_t get_raw_value() const
    {
        return raw_value;
    }

private:
    uint8_t pins[4];
    uint8_t last_raw  {255};
    uint8_t raw_value {255};
    unsigned long last_change{};
    uint16_t debounce_delay{};
    bool value_changed {false};
    DisplayState current_display {SHOW_ALL};

    uint8_t read_raw()
    {
        uint8_t val{};
        for (int i = 0; i < 4; ++i)
        {
            val |= (!digitalRead(pins[i])) << i;
        }
        return val;
    }

    DisplayState map_raw_to_state(uint8_t raw)
    {
        const DisplayState modeMap[16] = 
        {
            SHOW_TIME, SHOW_TEMP, SHOW_HUM, SHOW_ALL,
            SHOW_TIME, SHOW_TEMP, SHOW_HUM, SHOW_ALL,
            SHOW_TIME, SHOW_TEMP, SHOW_HUM, SHOW_ALL,
            SHOW_TIME, SHOW_TEMP, SHOW_HUM, SHOW_ALL
        };
        return modeMap[raw & 0x0F];
    }
};
