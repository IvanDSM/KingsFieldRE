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
