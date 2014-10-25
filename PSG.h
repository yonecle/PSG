#ifndef PSG_H
#define PSG_H

#include "Arduino.h"
#include "RegisterSetter.h"

// PSG Registers
#define REG_A_L     0x00
#define REG_A_H     0x01
#define REG_B_L     0x02
#define REG_B_H     0x03
#define REG_C_L     0x04
#define REG_C_H     0x05
#define REG_NOISE       0x06
#define REG_MIXER       0x07
#define REG_VOLUME_A    0x08
#define REG_VOLUME_B    0x09
#define REG_VOLUME_C    0x0a
#define REG_ENV_L       0x0b
#define REG_ENV_H       0x0c
#define REG_ENV_SHAPE   0x0d

// PSG Channels
enum Channel{
  CH_A = 0,
  CH_B = 1,
  CH_C = 2,
};

const byte CH_COUNT = 3;

#define BASE_FREQ 125000   // 2MHz / 16


// MML char to Freqyency Convert Function
word CalcFreqByMML(byte octave, char note, bool is_sharp = false);


class PSG {
public:
    PSG(RegisterSetter* setter);
    PSG();

    void reset(void);

    // Square Wave
    void enableChannel(Channel ch);
    void disableChannel(Channel ch);
    void setFreqBit(Channel ch, word freqbit);
    void setFrequency(Channel ch, word freq);
    void setVolume(Channel ch, byte Volume);

    // Envelope
    void setEnvEnable(Channel ch, bool enable);
    void setEnvFreqBit(word freq);
    void setEnvFrequency(word freq);
    void setEnvShape(bool cont, bool att, bool alt, bool hold);

    // Noise Channel
//  void setNoiseEnable(bool enable);
    void setNoiseFreqBit(byte freqbit);
    void setNoiseFrequency(word freq);

    // Set Mixer Channel
    void setMixer(byte noisemsk, byte tonemsk);

    // Get Parameter
    word freqBit(Channel ch){ return sq_freqbits[ch]; }
    byte noiseFreqBit(void){ return noise_freqbit; }
    byte getMixer(void){ return mixer; }
    byte volume(byte ch){ return volumes[ch]; }
    word envFreqBit(void){ return env_freqbit; }
    byte envShape(void){ return env_shape; }

    void writeData(byte addr, byte value);

    virtual void preSetAddress() = 0;
    virtual void postSetAddress() = 0;
    virtual void preSetData() = 0;
    virtual void postSetData() = 0;

private:
    // PSG Parameters
    word sq_freqbits[CH_COUNT];     // Square Wave Frequency Information A/B/C (12bit * 3)
    byte noise_freqbit;             // Noise Frequency Information (5bit)
    byte mixer;                     // Mixer Status (6bit)
    byte volumes[CH_COUNT];         // Volume Status (5bit * 3)
    word env_freqbit;               // Envelope Frequency Information (16bit)
    byte env_shape;                 // Envelope Shape (4bit)

    RegisterSetter* reg_setter;

    void param_reset(void);
    virtual void hardware_reset(void) = 0;
};

#endif

