#include "PSG.h"

// MML char to FreqBit Convert Table
const int noteFreq[] = {
  0,    9,    9,    10,   10,    11,    12,    12,   13,   14,   15,   15,   //0~11   
  16,   17,   18,   19,   21,    22,    23,    25,   26,   28,   29,   31,   //12~23 0oct
  33,   35,   37,   39,   41,    44,    46,    49,   52,   55,   58,   62,   //24~35 1oct
  65,   69,   73,   78,   82,    87,    93,    98,   104,  110,  117,  124,  //36~47 2oct
  131,  139,  147,  156,  165,   175,   185,   196,  208,  220,  233,  247,  //48~59 3oct
  262,  277,  294,  311,  330,   349,   370,   392,  415,  440,  466,  494,  //60~71 4oct
  523,  554,  587,  622,  659,   699,   740,   784,  831,  880,  932,  988,  //72~83 5oct
  1047, 1109, 1175, 1245, 1319,  1397,  1480,  1568, 1661, 1760, 1865, 1976, //84~95 6oct
  2093, 2218, 2349, 2489, 2637,  2794,  2960,  3136, 3322, 3520, 3729, 3951, //96~107 7oct
  4186, 4435, 4699, 4978, 5274,  5587,  5920,  6272, 6645, 7040, 7459, 7902, //108~119 8oct
  8372, 8870, 9397, 9956, 10548, 11175, 11840, 12544,                        //120~127
  0 //off
};

// MML char to Freqyency Convert Function
word CalcFreqByMML(byte octave, char note, bool is_sharp)
{
  int pos = 0;
  switch (note) {
    case 'C':
    case 'c':
      break;
    case 'D':
    case 'd':
      pos = 2;
      break;
    case 'E':
    case 'e':
      pos = 4;
      break;
    case 'F':
    case 'f':
      pos = 5;
      break;
    case 'G':
    case 'g':
      pos = 7;
      break;
    case 'A':
    case 'a':
      pos = 9;
      break;
    case 'B':
    case 'b':
      pos = 11;
      break;
    case 'R':
    case 'r':
      pos = 128;
      octave = -1;
      break;
    default:
      break;
  }

  return noteFreq[(octave + 1) * 12 + pos + (is_sharp ? 1 : 0)];
}

/* ------------------------------------------------------------------------ */
// Constructor
/* ------------------------------------------------------------------------ */
PSG::PSG()
{
    param_reset();
}

PSG::PSG(RegisterSetter* setter)
 : reg_setter(setter)
{
    param_reset();
}

/* ------------------------------------------------------------------------ */
// Public Functions
/* ------------------------------------------------------------------------ */
void PSG::reset(void)
{
    param_reset();
//    hardware_reset();
}

// ------ Square Channel Functions ---------------------------------------- */
void PSG::enableChannel(Channel ch)
{
    mixer ^= (1 << ch);
    writeData(REG_MIXER, mixer);
}

void PSG::disableChannel(Channel ch)
{
    mixer ^= ~(1 << ch);
    writeData(REG_MIXER, mixer);
}

// Set Frequency(Hz) to Channel
void PSG::setFreqBit(Channel ch, word freqbit)
{
    sq_freqbits[ch] = freqbit & 0b0000111111111111; //12bit
    writeData(REG_A_L + (ch * 2), lowByte(sq_freqbits[ch]));
    writeData(REG_A_H + (ch * 2), highByte(sq_freqbits[ch]));
}

// Set Frequency(Hz) to Channel
void PSG::setFrequency(Channel ch, word freq)
{
    word TP = (freq != 0) ? BASE_FREQ / freq : 0; 
    setFreqBit(ch, TP);
}

// Set Volume (4bit)
void PSG::setVolume(Channel ch, byte volume)
{
    volumes[ch] = volume;
    writeData(REG_VOLUME_A + ch, volumes[ch]);
}

// ------ Envelope Functions ---------------------------------------- */
// Set Envelope (Volume Disable)
void PSG::setEnvEnable(Channel ch, bool enable)
{
    volumes[ch] = (((enable? 1: 0) << 4) | (volumes[ch] & 0b00001111));
    writeData(REG_VOLUME_A + ch, volumes[ch]);
}

// Set Envelope Frequency Bit (16bit)
void PSG::setEnvFreqBit(word freqbit)
{
    env_freqbit = freqbit;
    writeData(REG_ENV_L, lowByte(env_freqbit));
    writeData(REG_ENV_H, highByte(env_freqbit));
}

// Set Envelope Frequency(Hz)
void PSG::setEnvFrequency(word freq)
{
    word TP = (freq != 0) ? BASE_FREQ / freq : 0; 
    setEnvFreqBit(TP);
}

// Set Envelope Shape (4bit)
void PSG::setEnvShape(bool cont, bool att, bool alt, bool hold)
{
    env_shape = (cont<< 3) |
                (att << 2) |
                (alt << 1) |
                 hold;
    writeData(REG_ENV_SHAPE, env_shape);
}

// ------ Noise Channel Functions ---------------------------------------- */
// Set 5bit Frequency Bit to Noise Channel
void PSG::setNoiseFreqBit(byte freqbit)
{
    noise_freqbit = freqbit & 0b00011111; // 5bit
    writeData(REG_NOISE, noise_freqbit);
}

// Set Frequency(Hz) to Noise Channel
void PSG::setNoiseFrequency(word freq)
{
    word TP = (freq != 0) ? BASE_FREQ / freq : 0; 
    setNoiseFreqBit(TP);
}

// ------ Mixer Functions ---------------------------------------- */
void PSG::setMixer(byte noise, byte square)
{
    mixer = ((noise & 0b111) << 3) | (square & 0b111);
    writeData(REG_MIXER, mixer);
}

/* ------------------------------------------------------------------------ */
// Private Functions
/* ------------------------------------------------------------------------ */
void PSG::param_reset(void)
{
    writeData(REG_A_L, 0);
    writeData(REG_A_H, 0);
    writeData(REG_B_L, 0);
    writeData(REG_B_H, 0);
    writeData(REG_C_L, 0);
    writeData(REG_C_H, 0);
    writeData(REG_NOISE, 0);
    writeData(REG_MIXER, 0);
    writeData(REG_VOLUME_A, 0);
    writeData(REG_VOLUME_B, 0);
    writeData(REG_VOLUME_C, 0);
    writeData(REG_ENV_L, 0);
    writeData(REG_ENV_H, 0);
    writeData(REG_ENV_SHAPE, 0);

    for (int i = 0; i < CH_COUNT; i++){
        sq_freqbits[i] = 0;
        volumes[i] = 0;
    }
    mixer = 0b00111111; // All Channel Off
    env_freqbit = 0;
    env_shape = 0;
}

void PSG::writeData(byte addr, byte value)
{
  // addr
    preSetAddress();
    if(reg_setter != 0)
        reg_setter->set(addr);
    postSetAddress();

    // value
    preSetData();
    if(reg_setter != 0)
        reg_setter->set(value);
    postSetData();
}

