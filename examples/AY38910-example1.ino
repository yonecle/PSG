//AY-3-8910
#include "AY38910.h"

const int dataPin = 5;
const int latchPin = 6;
const int clockPin = 7;
const int pinBC1 =  8;
const int pinBCDIR =  9;

// 2mz clock pin
const int freqOutputPin = 11;   // OC2A output pin for ATmega328 boards

const int prescale  = 1;
const int ocr2aval  = 3; 
const float period    = 2.0 * prescale * (ocr2aval+1) / (F_CPU/1.0e6);
const float freq      = 1.0e6 / period;

void  init2MhzClock()
{
    // Set Timer 2 CTC mode with no prescaling.  OC2A toggles on compare match
    //
    // WGM22:0 = 010: CTC Mode, toggle OC 
    // WGM2 bits 1 and 0 are in TCCR2A,
    // WGM2 bit 2 is in TCCR2B
    // COM2A0 sets OC2A (arduino pin 11 on Uno or Duemilanove) to toggle on compare match
    //
    TCCR2A = ((1 << WGM21) | (1 << COM2A0));

    // Set Timer 2  No prescaling  (i.e. prescale division = 1)
    //
    // CS22:0 = 001: Use CPU clock with no prescaling
    // CS2 bits 2:0 are all in TCCR2B
    TCCR2B = (1 << CS20);

    // Make sure Compare-match register A interrupt for timer2 is disabled
    TIMSK2 = 0;
    // This value determines the output frequency
    OCR2A = ocr2aval;
}

class DirectRegisterSetter : public RegisterSetter {
public:
//  DirectRegisterSetter(){
//    DDRD = 0b11111111;
//  }
  void set(byte data){
    PORTD = data;
  }
};

AY38910* psg;

struct score{
  int oct;
  char note;
  int length;
};

struct score song[] = {
{4,'c', 500},
{4,'d', 500},
{4,'e', 500},
{4,'f', 500},
{4,'e', 500},
{4,'d', 500},
{4,'c', 500},
{4,'r', 500},
{4,'e', 500},
{4,'f', 500},
{4,'g', 500},
{4,'a', 500},
{4,'g', 500},
{4,'f', 500},
{4,'e', 500},
{4,'r', 500},
{4,'c', 500},
{4,'r', 500},
{4,'c', 500},
{4,'r', 500},
{4,'c', 500},
{4,'r', 500},
{4,'c', 500},
{4,'r', 500},
{4,'c', 128},
{4,'r', 128},
{4,'c', 128},
{4,'r', 128},
{4,'d', 128},
{4,'r', 128},
{4,'d', 128},
{4,'r', 128},
{4,'e', 128},
{4,'r', 128},
{4,'e', 128},
{4,'r', 128},
{4,'f', 128},
{4,'r', 128},
{4,'f', 128},
{4,'r', 128},
{4,'e', 250},
{4,'r', 250},
{4,'d', 250},
{4,'r', 250},
{4,'c', 250},
{4,'r', 1000}  
};


void setup(){

    //init pins
    //DDRD |= 0b11111111;
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);  
    pinMode(clockPin, OUTPUT);
    pinMode(pinBC1, OUTPUT);
    pinMode(pinBCDIR, OUTPUT);
    //psg = new AY38910(pinBC1, pinBCDIR, new DirectRegisterSetter());
    psg = new AY38910(pinBC1, pinBCDIR, new ShiftRegisterSetter(5,6,7) );
    
    pinMode(freqOutputPin, OUTPUT);
    init2MhzClock();
    
    // Initialize the mixer of the AY
    psg->reset();
    psg->enableChannel(CH_A);
    psg->setVolume(CH_A, 0x0f);
    
    pipo();
    
    delay(300);
}


void loop() {
  //This is test song converted to array, thanks to Alan!
  for(int i=0; i< 47; ++i){
     struct score tmp = song[i];
     psg->setFrequency(CH_A, CalcFreqByMML(tmp.oct, tmp.note));
     delay(tmp.length);
  }
}

void pipo(){
  psg->setFrequency(CH_A, CalcFreqByMML(7, 'C'));
  psg->setFrequency(CH_B, CalcFreqByMML(7, 'C') - 1);
  delay(100);
  psg->setFrequency(CH_A, CalcFreqByMML(6, 'C'));
  psg->setFrequency(CH_B, CalcFreqByMML(6, 'C') - 1);
  delay(100);
  psg->setFreqBit(CH_A, 0);
  psg->setFreqBit(CH_B, 0);
}
