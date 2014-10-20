#include "AY38910.h"


AY38910::AY38910(byte bc1_pin, byte bcdir_pin)
: BC1_PIN(bc1_pin), BCDIR_PIN(bcdir_pin), PSG()
{
}

AY38910::AY38910(byte bc1_pin, byte bcdir_pin, RegisterSetter* setter)
: BC1_PIN(bc1_pin), BCDIR_PIN(bcdir_pin), PSG(setter)
{
}

void AY38910::preSetAddress(){
    digitalWrite(BC1_PIN, LOW);
    digitalWrite(BCDIR_PIN, LOW);
}

void AY38910::postSetAddress(){
    digitalWrite(BC1_PIN, HIGH);
    digitalWrite(BCDIR_PIN, HIGH);
}

void AY38910::preSetData(){
    digitalWrite(BC1_PIN, LOW);
    digitalWrite(BCDIR_PIN, HIGH);
}

void AY38910::postSetData(){
    digitalWrite(BC1_PIN, LOW);
    digitalWrite(BCDIR_PIN, LOW);
}

