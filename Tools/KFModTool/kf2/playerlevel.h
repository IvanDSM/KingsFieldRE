#ifndef KF2_PLAYERLEVEL_H
#define KF2_PLAYERLEVEL_H

#include <cstdint>

namespace KF2
{

// Structs

/*!
 * \brief Holds HP, MP, Str and Magic Power Differences and Experience for the next level for each level the player can achieve.
 */
struct PlayerLevel
{
    uint16_t BaseHP;
    uint16_t BaseMP;
    uint16_t StrPowerDiff;
    uint16_t MagPowerDiff;
    uint32_t ExpForNextLevel;
} __attribute__((packed, aligned(1)));

}

#endif // KF2_PLAYERLEVEL_H
