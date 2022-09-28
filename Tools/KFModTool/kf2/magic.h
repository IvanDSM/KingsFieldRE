#ifndef KF2_MAGIC_H
#define KF2_MAGIC_H

#include <cstdint>
#include <QString>

namespace KF2
{

// Enums

/*!
 * \brief Enum for the Magic IDs in King's Field.
 */
enum class MagicID : uint8_t
{
    ArcherArrow = 31,
    ArcherParalyzeArrow = 29,
    Breath = 19,
    DarkSlayerMagicA = 44,
    DarkSlayerMagicB = 45,
    Dispoison = 14,
    DoubleFireball = 23,
    EarthHeal = 16,
    EarthWave = 2,
    EnemyEarthMagic = 32,
    EnemyHomingEarthMagic = 33,
    EnemyLightningVolt = 54,
    FireBall = 7,
    FireStorm = 9,
    FireWall = 8,
    Flame = 10,
    FlameSwordMagicA = 49,
    FlameSwordMagicB = 50,
    Flash = 12,
    Freeze = 6,
    IceBladeMagicA = 38,
    IceBladeMagicB = 39,
    IceStorm = 5,
    Light = 18,
    LightningVolt = 11,
    Meteor = 3,
    MissileShield = 17,
    MoonlightSwordMagicA = 42,
    MoonlightSwordMagicB = 43,
    None = 255,
    PsytheCurseOrb = 26,
    ResistFire = 15,
    SKnightPoisonBreath = 22,
    Seath = 13,
    SeathsSwordMagicA = 40,
    ShidenMagicA = 34,
    ShidenMagicB = 35,
    SpiderSwordMagicA = 51,
    SpiderSwordMagicB = 52,
    Stone = 1,
    TarnWindMagic = 24,
    WaterFall = 0,
    WindCutter = 4
};

// Structs

/*!
 * \brief Structure for the definition of magic spells.
 */
struct Magic
{
    bool PlayerHas;
    uint8_t ChargeRecoveryTime;
    uint8_t field_0x2;
    uint8_t field_0x3;
    uint8_t StatusEffect;
    uint8_t field_0x7;
    uint8_t field_0x5;
    uint8_t field_0x6;
    uint16_t SomeDmg1;
    uint16_t SomeDmg2;
    uint16_t SomeDmg3;
    uint16_t FireDmg;
    uint16_t EarthDmg;
    uint16_t WindDmg;
    uint16_t WaterDmg;
    uint16_t MPCost;
    uint8_t field_0x18;
    uint8_t field_0x19;
} __attribute__((packed, aligned(1)));

// Functions

QString getMagicIDName(const MagicID magicId);

}

#endif // KF2_MAGIC_H
