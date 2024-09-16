#ifndef LED_STS_H
#define LED_STS_H



void ledStsSetup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void ledStsOn()
{
    digitalWrite(LED_BUILTIN, LOW);
}

void ledStsOff()
{
    digitalWrite(LED_BUILTIN, HIGH);
}

#endif // LED_STS_H