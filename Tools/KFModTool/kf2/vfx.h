#ifndef KF2_VFX_H
#define KF2_VFX_H

#include <cstdint>

namespace KF2
{

// Structs

/*!
 * \brief Structure for VFX objects in King's Field.
 */
struct VFX
{
    uint16_t VFXID;
    uint8_t AnimFrameCount;
    uint8_t AnimSpeed;
    uint8_t TileLayer;
    uint8_t TileWEX;
    uint8_t TileNSY;
    uint8_t field_0x7;
    uint8_t field_0x8;
    uint8_t field_0x9;
    int16_t FineXPos;
    int16_t FineYPos;
    int16_t FineZPos;
} __attribute__((packed, aligned(1)));

}

#endif // KF2_VFX_H
