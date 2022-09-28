#ifndef KF2_ARMOR_H
#define KF2_ARMOR_H

#include <cstdint>

namespace KF2
{

// Structs

/*!
 * \brief Stats structure for armor.
 */
struct Armor
{
    uint16_t Thingie;
    uint16_t DefSlash;
    uint16_t DefChop;
    uint16_t DefStab;
    uint16_t DefPoison;
    uint16_t DefDarkM;
    uint16_t DefFireM;
    uint16_t DefEarthM;
    uint16_t DefWindM;
    uint16_t DefWaterM;
    uint16_t field_0x14;
    uint16_t field_0x16;
    uint16_t field_0x18;
    uint16_t field_0x1a;
    uint16_t field_0x1c;
    uint16_t field_0x1e;
} __attribute__((packed, aligned(1)));
}

#endif // KF2_ARMOR_H
