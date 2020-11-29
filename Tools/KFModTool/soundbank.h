#ifndef SOUNDBANK_H
#define SOUNDBANK_H

#include "kfmterror.h"
#include <vector>
#include <QtMath>

//
// Formats
//
namespace VABFormat
{
    struct Header
    {
        unsigned int magicNumber;
        unsigned int version;
        unsigned int bankID;
        unsigned int fileSize;
        unsigned short reserved0;
        unsigned short numProgram;
        unsigned short numTone;
        unsigned short numWaveform;
        unsigned char  masterVolume;
        unsigned char  masterPan;
        unsigned char  attribute1;
        unsigned char  attribute2;
        unsigned int reserved1;
    };

    struct Program
    {
        unsigned char numTone;
        unsigned char volume;
        unsigned char priority;
        unsigned char mode;
        unsigned char pan;
        unsigned char reserved0;
        unsigned short attribute;
        unsigned int reserved1;
        unsigned int reserved2;
    };

    struct ASDR
    {
        unsigned short asdr;
        union {
            unsigned short attack : 4;
            unsigned short decay  : 4;
            unsigned short sustain : 4;
            unsigned short release : 4;
        };
    };

    struct Tone
    {
        unsigned char priority;
        unsigned char mode;
        unsigned char volume;
        unsigned char pan;
        unsigned char centerNote;
        unsigned char pitchCorrection;
        unsigned char minNote;
        unsigned char maxNote;
        unsigned char vibratoWidth;
        unsigned char vibratoHz;
        unsigned char portamentoWidth;
        unsigned char portamentoHz;
        unsigned char pitchBendMin;
        unsigned char pitchBendMax;
        unsigned char reserved1;
        unsigned char reserved2;
        ASDR asdr1;
        ASDR asdr2;
        unsigned short parentProgram;
        unsigned short vagID;
        unsigned short reserved[4];
    };

    struct VagTable
    {
        unsigned short vagTable[256];   //There's always 256 vag offsets (512 bytes)
    };
}
namespace PSXSpu
{
    static const signed char pos_adpcm_filter[] = {0, +60, +115, +98, +122};
    static const signed char neg_adpcm_filter[] = {0,   0,  -52, -55,  -60};

    struct adpcm_block_shift
    {
        unsigned char shiftFilter;
        union {
            unsigned char shift : 4;
            unsigned char filter : 3;
            unsigned char reserved : 1;
        };
    };

    struct adpcm_block_flag
    {
        unsigned char flag;
        union {
            unsigned char loopEnd : 1;
            unsigned char loopRepeat : 1;
            unsigned char loopStart : 1;
            unsigned char reserved : 5;
        };
    };

    struct adpcm_block_sample
    {
        unsigned char sample;
        union {
            unsigned char first : 4;
            unsigned char second : 4;
        };
    };

    struct adpcm_block
    {
        adpcm_block_shift shiftFilter;
        adpcm_block_flag  flags;
        adpcm_block_sample samples[14];
    };
}

class Sound {
public:
    Sound();
    ~Sound();

public:

    /*!
     * \brief Decode a block of SPU ADPCM (MONO) and converts it to S16 PCM (MONO)
     * \param in spu_adpcm_block
     * \param out pcm data
     * \return n/a
     */
    void decodeSpuADPCM(PSXSpu::adpcm_block block, signed short *pcm);

private:

    //These values relate to the decoding of ADPCM data.
    signed short sampleOld    = 0;
    signed short sampleOldest = 0;

};

class SoundBank {
public:
    SoundBank();
    ~SoundBank();

public:
    void loadVAB(); //Should take a VH and VB file

    /*!
     * \brief Get a sound object from the sound bank.
     * \param in Sound Index
     * \return A previously loaded sound.
     */
    Sound *getSound(unsigned int index)
    {
       if(index < 0 || index >= sounds.size())
       {
           KFMTError::error("SoundBank: Invalid Sound ID");
           return nullptr;
       }

       return sounds[index];
    }
private:
    std::vector<Sound*> sounds;

};

#endif // SOUNDBANK_H
