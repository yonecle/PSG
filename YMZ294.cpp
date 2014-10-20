#include "YMZ294.h"

YMZ294::YMZ294(byte wrcs_pin, byte a0_pin, byte reset_pin)
: WRCS_PIN(wrcs_pin), A0_PIN(a0_pin), RESET_PIN(reset_pin), PSG()
{
}

YMZ294::YMZ294(byte wrcs_pin, byte a0_pin, byte reset_pin, RegisterSetter* setter)
: WRCS_PIN(wrcs_pin), A0_PIN(a0_pin), RESET_PIN(reset_pin), PSG(setter)
{
}

void YMZ294::hardware_reset(void)
{
    digitalWrite(WRCS_PIN, HIGH);
    digitalWrite(A0_PIN, LOW);
    digitalWrite(RESET_PIN, LOW);
    delay(10);
    digitalWrite(RESET_PIN, HIGH);
}


void YMZ294::preSetAddress(){
    digitalWrite(WRCS_PIN, LOW);
    digitalWrite(A0_PIN, LOW);
}

void YMZ294::postSetAddress(){
    digitalWrite(WRCS_PIN, HIGH);
}

void YMZ294::preSetData(){
    digitalWrite(WRCS_PIN, LOW);
    digitalWrite(A0_PIN, HIGH);
}

void YMZ294::postSetData(){
    digitalWrite(WRCS_PIN, HIGH);
}

