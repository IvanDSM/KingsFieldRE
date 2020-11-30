#include "soundbank.h"

void Sound::decodeSpuADPCM(PSXSpu::adpcm_block block, signed short *pcm)
{
    //Shift
    unsigned char shift  = block.shiftFilter.shift;

    //Make sure shift never goes above 12 by setting it to 9!!! O_o wtf sony
    if(shift > 12)
        shift = 9;

    shift = 12 - shift; //We do this so we only need to apply a << shift to our samples

    //Get Filter
    unsigned char FP = PSXSpu::pos_adpcm_filter[block.shiftFilter.filter];
    unsigned char FN = PSXSpu::neg_adpcm_filter[block.shiftFilter.filter];

    int sampleID = 0;
    signed short sampleNew, sign;

    for(int i = 0; i < 14; ++i)
    {
        //Sample 1 Decoding
        sampleNew = block.samples[sampleID].first;

        //Convert Sample to signed nibble (does this even work?..)
        sign = 1 + (-2 * (sampleNew & 0x8));     //Genius code design...
        sampleNew = (sampleNew & 0x7);           //Should result in this being a signed nibble :)
        pcm[(2 * i) + 0] = ((sampleNew << shift) * sign) + ((sampleOld*FP + sampleOldest*FN+32)/64);

        sampleOld = sampleNew;
        sampleOldest = sampleOld;

        //Sample 2 Decoding
        sampleNew = block.samples[sampleID].second;

        //Convert Sample to signed nibble (does this even work?..)
        sign = 1 + (-2 * (sampleNew & 0x8));
        sampleNew = (sampleNew & 0x7);
        pcm[(2 * i) + 0] = ((sampleNew << shift) * sign) + ((sampleOld*FP + sampleOldest*FN+32)/64);

        sampleOld = sampleNew;
        sampleOldest = sampleOld;
    }
}

void SoundBank::loadVAB(const QByteArray &vh, const QByteArray &vb)
{
    //
    //Read Vab Header
    //
    QDataStream vabHeader(vh);
    vabHeader.setByteOrder(QDataStream::LittleEndian);

    VABFormat::Header header;

    vabHeader >> header.magicNumber;
    vabHeader >> header.version;
    vabHeader >> header.bankID;
    vabHeader >> header.fileSize;
    vabHeader >> header.reserved0;
    vabHeader >> header.numProgram;
    vabHeader >> header.numTone;
    vabHeader >> header.numWaveform;
    vabHeader >> header.masterVolume;
    vabHeader >> header.masterPan;
    vabHeader >> header.attribute1;
    vabHeader >> header.attribute2;
    vabHeader >> header.reserved1;

    if(header.magicNumber != 0x70424156) //VABp
    {
        KFMTError::error("SoundBank: Invalid VAB ID.");
        return;
    }

    //Read Vab Programs (Always 128);
    program.reserve(128);

    for(int i = 0; i < 128; ++i)
    {
        VABFormat::Program *vabProg = new VABFormat::Program();

        vabHeader >> vabProg->numTone;
        vabHeader >> vabProg->volume;
        vabHeader >> vabProg->priority;
        vabHeader >> vabProg->mode;
        vabHeader >> vabProg->pan;
        vabHeader >> vabProg->reserved0;
        vabHeader >> vabProg->attribute;
        vabHeader >> vabProg->reserved1;
        vabHeader >> vabProg->reserved2;

        program.push_back(vabProg);
    }

    //Read Vab Tones (Always 16 * numProgram)
    tone.reserve(16 * header.numProgram);

    for(int i = 0; i < 16 * header.numProgram; ++i)
    {
        VABFormat::Tone *vabTone = new VABFormat::Tone();

        vabHeader >> vabTone->priority;
        vabHeader >> vabTone->mode;
        vabHeader >> vabTone->volume;
        vabHeader >> vabTone->pan;
        vabHeader >> vabTone->centerNote;
        vabHeader >> vabTone->pitchCorrection;
        vabHeader >> vabTone->minNote;
        vabHeader >> vabTone->maxNote;
        vabHeader >> vabTone->vibratoWidth;
        vabHeader >> vabTone->vibratoHz;
        vabHeader >> vabTone->portamentoWidth;
        vabHeader >> vabTone->portamentoHz;
        vabHeader >> vabTone->pitchBendMin;
        vabHeader >> vabTone->pitchBendMax;
        vabHeader >> vabTone->reserved1;
        vabHeader >> vabTone->reserved2;
        vabHeader >> vabTone->asdr1.asdr;
        vabHeader >> vabTone->asdr2.asdr;
        vabHeader >> vabTone->parentProgram;
        vabHeader >> vabTone->vagID;
        vabHeader >> vabTone->reserved[0];
        vabHeader >> vabTone->reserved[1];
        vabHeader >> vabTone->reserved[2];
        vabHeader >> vabTone->reserved[3];

        tone.push_back(vabTone);
    }

    //Read Vab Vag Offsets
    VABFormat::VagTable vagTable;

    for(int i = 0; i < 256; ++i)
    {
        vabHeader >> vagTable.vagTable[i];
        vagTable.vagTable[i] = vagTable.vagTable[i] << 3;
    }

    //
    // Read Vab Body  (samples)
    //
    QDataStream vabBody(vb);
    vabBody.setByteOrder(QDataStream::LittleEndian);

    for(int i = 0; i < header.numWaveform; ++i)
    {
        //Calculate vag size
        //Go to vag offset
        //Read vag samples and convert them to PCM samples
    }
}
