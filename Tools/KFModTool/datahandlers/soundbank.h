#ifndef SOUNDBANK_H
#define SOUNDBANK_H

#include "core/kfmterror.h"
#include "datahandlers/kfmtdatahandler.h"
#include <vector>
#include <QtMath>
/*
class SoundBank : public KFMTDataHandler
{
    class Sound
    {
        std::vector<uint16_t> samples;
        uint32_t sampleRate;
    };

public:
    SoundBank();
    ~SoundBank();

public:
    explicit SoundBank(KFMTFile& vh, KFMTFile& vb);

private:
    std::vector<Sound> sounds;
};

struct ProgramAttributes
{
    uint8_t toneCount;
    uint8_t voume;
    uint8_t priority;
    uint8_t mode;
    uint8_t pan;
    uint8_t systemReserved0;
    uint8_t attr;
    uint8_t systemReserved1;
    uint8_t systemReserved2;
} __attribute__((packed, aligned(1)));

struct ToneAttributes
{
    uint8_t priority;
    uint8_t mode;
    uint8_t volume;
    uint8_t pan;
    uint8_t centerNote;
    uint8_t centerNoteTuneOffset;
    uint8_t minimumNote;
    uint8_t maximumNote;
    uint8_t vibratoDepth;
    uint8_t vibratoLength;
    uint8_t portamentoDepth;
    uint8_t portamentoLength;
    uint8_t pitchBendMinimum;
    uint8_t pitchBendMaximum;
    uint16_t systemReserved0;
    uint16_t adsr1;
    uint16_t adsr2;
    int16_t program;
    int16_t vag;
    uint64_t systemReserved1;
};

struct VABHeader
{
    uint32_t magic;
    uint32_t version;
    uint32_t vabId;
    uint32_t fileSize;
    uint16_t systemReserved0;
    uint16_t programCount;
    uint16_t toneCount;
    uint16_t vagCount;
    uint8_t masterVolume;
    uint8_t masterPan;
    uint8_t bankAttr1;
    uint8_t bankAttr2;
    uint32_t systemReserved1;
    ProgramAttributes programAttrs[128];
} __attribute__((packed, aligned(1)));
*/
#endif // SOUNDBANK_H
