#ifndef KF2_WEAPON_H
#define KF2_WEAPON_H

#include <cstdint>
#include "magic.h"
#include "platform/psx.h"

namespace KF2
{

// Structs

/*!
 * \brief Stats structure for weapons.
 */
struct Weapon
{
    uint8_t SoundEffect;
    uint8_t StrStaminaCost;
    uint8_t Unknown_x02;
    MagicID Spell1;
    MagicID Spell2;
    uint8_t Spell1ShotAmount;
    uint16_t OffSlash;
    uint16_t OffChop;
    uint16_t OffStab;
    uint16_t OffHolyM;
    uint16_t OffFireM;
    uint16_t OffEarthM;
    uint16_t OffWindM;
    uint16_t OffWaterM;
    uint16_t HPRestoreTimer;
    uint16_t MPRestoreTimer;
    int16_t AttackRange;
    uint16_t SwingSpeed;
    uint16_t SwingDamageStartTime;
    uint16_t Spell1CastStartTime;
    uint16_t Spell1CastEndTime;
    int16_t Spell2AnimSpeed;
    uint16_t Unknown_x26;
    uint16_t Spell2DamageStartTime;
    uint16_t Unknown_x2a;
    uint16_t Unknown_x2c;
    uint16_t Unknown_x2e;
    uint16_t Unknown_x30;
    int16_t Unknown_x32;
    PSX::SVECTOR Position;
    PSX::SVECTOR SomeVec;
} __attribute__((packed, aligned(1)));

// Functions

QString getWeaponName(const uint8_t weaponIndex);

}

#endif // KF2_WEAPON_H
