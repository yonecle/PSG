#ifndef AY38910_H
#define AY38910_H

/*
  GI AY3-8910A
  aitendo AY389C10
  
*/


#include "PSG.h"

// #include "AY38910.h"
class AY38910 : public PSG {
public:
    AY38910(byte wrcs_pin, byte a0_pin);
    AY38910(byte wrcs_pin, byte a0_pin, RegisterSetter* setter);
    
    virtual void preSetAddress();
    virtual void postSetAddress();
    virtual void preSetData();
    virtual void postSetData();
    
private:
    const byte BC1_PIN;
    const byte BCDIR_PIN;
};



//  // Square Wave
//  void SetEnable(Channel channel, bool enable);
//  void SetFreqBit(Channel ch, word freqbit);
//  void SetFrequency(Channel ch, word freq);
//  void SetVolume(Channel ch, byte Volume);

//  // Envelope
//  void SetEnvEnable(Channel ch, bool enable);
//  void SetEnvFreqBit(word freq);
//  void SetEnvFrequency(word freq);
//  void SetEnvShape(bool cont, bool att, bool alt, bool hold);

    // Noise Channel
//  void SetNoiseEnable(bool enable);
//  void SetNoiseFreqBit(byte freqbit);
//  void SetNoiseFrequency(word freq);

    // Set Mixer Channel
//  void SetMixer(byte noisemsk, byte tonemsk);

    // Get Parameter
//  word FreqBit(Channel ch){return sq_freqbits[ch];}
//  byte NoiseFreqBit(void){return noise_freqbit;}
//  byte Mixer(void){return mixer;}
//  byte Volume(byte ch){return volumes[ch];}
//  word EnvFreqBit(void){return env_freqbit;}
//  byte EnvShape(void){return env_shape;}

    // Get Pin No.
//  byte GetWRCS(){return WRCS_PIN;}
//  byte GetA0(){return A0_PIN;}
//  byte GetRESET(){return RESET_PIN;}
    
// private:
    // Arduino Pins
//  const byte WRCS_PIN;
//  const byte A0_PIN;
//  const byte RESET_PIN;
//  const byte DATA_PIN;
//  const byte LATCH_PIN;
//  const byte CLOCK_PIN;
    
    // YMZ294 Parameters
//  word sq_freqbits[CH_COUNT]; // Square Wave Frequency Information A/B/C (12bit * 3)
//  byte noise_freqbit;         // Noise Frequency Information (5bit)
//  byte mixer;                 // Mixer Status (6bit)
//  byte volumes[CH_COUNT];     // Volume Status (5bit * 3)
//  word env_freqbit;           // Envelope Frequency Information (16bit)
//  byte env_shape;             // Envelope Shape (4bit)
    
//  void param_reset(void);
//  void hardware_reset(void);
//  void set_register(byte addr, byte value);

//  void useShiftRegister(byte data);
// };

#endif

