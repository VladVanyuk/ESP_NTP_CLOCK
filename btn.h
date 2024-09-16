#ifndef BTN_H
#define BTN_H

#include <EncButton.h>

#define BTN_PIN D6


Button btn(BTN_PIN);


void decode(uint16_t action) {
    switch (action) {
        case EB_PRESS:
            Serial.println("press");
            break;
        case EB_STEP:
            Serial.println("step");
            break;
        case EB_RELEASE:
            Serial.println("release");
            break;
        case EB_CLICK:
            Serial.println("click");
            break;
        case EB_CLICKS:
            Serial.print("clicks");
            break;
        case EB_REL_HOLD:
            Serial.println("release hold");
            break;
        case EB_REL_HOLD_C:
            Serial.print("release hold clicks ");
            break;
        case EB_REL_STEP:
            Serial.println("release step");
            break;
        case EB_REL_STEP_C:
            Serial.print("release step clicks ");
            break;
    }
}

void setupBtn()
{
    pinMode(BTN_PIN, INPUT_PULLUP);
    btn.attach([]() {
        uint16_t action = static_cast<VirtButton*>(EB_self)->action();
        if (action != EB_HOLD) Serial.println("b0");
        decode(action);
    });

}

bool handleBtn()
{
    btn.tick();

    if (btn.click()){
        return true;
    }
    return false;
}

#endif // BTN_H