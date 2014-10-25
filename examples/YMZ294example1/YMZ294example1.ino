#include <YMZ294.h>

const int dataPin = 5;
const int latchPin = 6;
const int clockPin = 7;
const byte WRCS_PIN = 8;
const byte A0_PIN = 9;
const byte RESET_PIN = 10;

YMZ294* psg;

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
    pinMode(WRCS_PIN, OUTPUT);
    pinMode(A0_PIN, OUTPUT);
    pinMode(RESET_PIN, OUTPUT);
    
    psg = new YMZ294(WRCS_PIN, A0_PIN, RESET_PIN, new ShiftMSBRegisterSetter(5,6,7) );
    
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
