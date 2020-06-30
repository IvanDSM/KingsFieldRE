#ifndef KFTYPES_H
#define KFTYPES_H

#include <QtGlobal>

typedef quint8 byte;
typedef byte undefined;

/*!
 * \brief I have no idea what the fuck this thing does.
 */
struct KingsField80175914OddStruct {
    undefined field_0x0;
    byte SomeType;
    undefined field_0x2;
    undefined field_0x3;
    quint16 CollisionRadius;
    undefined field_0x6;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    undefined field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
};

/*!
 * \brief Enum for the Magic IDs in King's Field
 */
enum KingsFieldMagicID {
    KingsFieldMagic_WaterFall=0,
    KingsFieldMagic_Stone=1,
    KingsFieldMagic_EarthWave=2,
    KingsFieldMagic_Meteor=3,
    KingsFieldMagic_WindCutter=4,
    KingsFieldMagic_IceStorm=5,
    KingsFieldMagic_Freeze=6,
    KingsFieldMagic_FireBall=7,
    KingsFieldMagic_FireWall=8,
    KingsFieldMagic_FireStorm=9,
    KingsFieldMagic_Flame=10,
    KingsFieldMagic_LightningVolt=11,
    KingsFieldMagic_Flash=12,
    KingsFieldMagic_Seath=13,
    KingsFieldMagic_Dispoison=14,
    KingsFieldMagic_ResistFire=15,
    KingsFieldMagic_EarthHeal=16,
    KingsFieldMagic_MissileShield=17,
    KingsFieldMagic_Light=18,
    KingsFieldMagic_Breath=19,
    KingsFieldMagic_None=255,
};

/*!
 * \brief Structure for the definition of magic spells
 */
struct KingsFieldMagicStructure {
    bool PlayerHas;
    byte ChargeRecoveryTime;
    undefined field_0x2;
    undefined field_0x3;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    quint16 SomeDmg1;
    quint16 SomeDmg2;
    quint16 SomeDmg3;
    quint16 FireDmg;
    quint16 EarthDmg;
    quint16 WindDmg;
    quint16 WaterDmg;
    quint16 MPCost;
    undefined field_0x18;
    undefined field_0x19;
};

/*!
 * \brief Holds HP, MP, Str and Magic Power Differences and Experience for the next level for each level the player can achieve.
 */
struct KingsFieldPlayerLvlData {
    quint16 BaseHP;
    quint16 BaseMP;
    quint16 StrPowerPlus;
    quint16 MagPowerPlus;
    quint32 ExpForNextLevel;
};

/*!
 * \brief Stats structure for weapons
 */
struct KingsFieldWeaponStats {
    quint16 OffSlash;
    quint16 OffChop;
    quint16 OffStab;
    quint16 OffHolyM;
    quint16 OffFireM;
    quint16 OffEarthM;
    quint16 OffWindM;
    quint16 OffWaterM;
    quint8 field_0x10;
    quint8 field_0x11;
    quint8 field_0x12;
    quint8 field_0x13;
    quint8 field_0x14;
    quint8 field_0x15;
    quint8 field_0x16;
    quint8 field_0x17;
    quint8 field_0x18;
    quint8 field_0x19;
    quint8 field_0x1a;
    quint8 field_0x1b;
    quint8 field_0x1c;
    quint8 field_0x1d;
    quint8 field_0x1e;
    quint8 field_0x1f;
    quint8 field_0x20;
    quint8 field_0x21;
    quint8 field_0x22;
    quint8 field_0x23;
    quint8 field_0x24;
    quint8 field_0x25;
    quint8 field_0x26;
    quint8 field_0x27;
    quint8 field_0x28;
    quint8 field_0x29;
    quint8 field_0x2a;
    quint8 field_0x2b;
    quint8 field_0x2c;
    quint8 field_0x2d;
    quint8 field_0x2e;
    quint8 field_0x2f;
    quint8 field_0x30;
    quint8 field_0x31;
    quint8 field_0x32;
    quint8 field_0x33;
    quint8 field_0x34;
    quint8 field_0x35;
    quint8 field_0x36;
    quint8 field_0x37;
    quint8 field_0x38;
    quint8 field_0x39;
    quint8 field_0x3a;
    quint8 field_0x3b;
    quint8 field_0x3c;
    quint8 field_0x3d;
    quint8 field_0x3e;
    quint8 field_0x3f;
    quint8 field_0x40;
    quint8 field_0x41;
    quint8 field_0x42;
    quint8 field_0x43;
};
#endif // KFTYPES_H
