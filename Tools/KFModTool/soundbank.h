#ifndef SOUNDBANK_H
#define SOUNDBANK_H

#include <vector>

#include "kfmterror.h"

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

class Sound {
public:
    Sound();
    ~Sound();

public:

private:

};

class SoundBank {
public:
    SoundBank();
    ~SoundBank();

public:
    void loadVAB(); //Should take a VH and VB file
    void loadSEQ(); //Single SEQ file

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
