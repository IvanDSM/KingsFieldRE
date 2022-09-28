#ifndef KF2_ENTITY_H
#define KF2_ENTITY_H

#include "object.h"

namespace KF2
{

// Enums

/*!
 * \brief Enum for the entity meshes in King's Field.
 */
enum class EntityMeshID : uint8_t
{
    AlHunt = 83,
    Archer = 18,
    Baltail = 4,
    BaltailTail = 5,
    Billent = 42,
    Bitt = 50,
    Cable = 41,
    CellfyFoss = 64,
    CellfyFoss2 = 65,
    CliffLore = 86,
    CopperKnight = 34,
    DalfVice = 89,
    DavidTabler = 88,
    DemonLord = 28,
    DiasBagil = 35,
    DragonGrass = 107,
    EarnestClyde = 96,
    EarnestClydeSitting = 106,
    EarthElemental = 31,
    FaiFadlin = 85,
    FireElemental = 9,
    Ghost = 10,
    GiantTermite = 25,
    GigiBudwell = 74,
    GigiBudwellWatering = 76,
    GreenSlime = 0,
    GreenSlime2 = 12,
    GreenSlime3 = 13,
    GreenSlime4 = 19,
    GreenSlimeDeath = 36,
    GreenSlimeDeath2 = 37,
    GreenSlimeDeath3 = 38,
    GreenSlimeDeath4 = 43,
    Guyra = 39,
    HarrisCarvitto = 84,
    HeadEater = 14,
    JoseHarven = 67,
    JoseHavenDeath = 104,
    JoseHavenDeath2 = 108,
    Kald = 23,
    KarenShore = 80,
    KarenShoreChair = 99,
    KehlHunt = 97,
    KehlHunt2 = 98,
    KrakenBody = 29,
    KrakenHead = 30,
    KrolaAmgun = 91,
    KrolaAmgunCooking = 92,
    LeonShore = 81,
    LeonShoreWatering = 82,
    LogStalker = 27,
    MagesCandlesticks = 49,
    MarkWozz = 95,
    MechaDemonLord = 46,
    MechaReik = 48,
    MechaTermite = 47,
    Meryl = 73,
    Miria = 109,
    Mogle = 15,
    NolaBagil = 70,
    None = 255,
    PoisonSlime = 1,
    Psythe = 24,
    RaddBilheim = 90,
    RaffyFoss = 66,
    RandFerrer = 87,
    RedSpikeBall = 26,
    Refma = 32,
    Refma2 = 51,
    Reik = 11,
    SKnight = 16,
    SaintGrave = 105,
    Salamander = 40,
    SandlerAmgun = 93,
    SandlerAmgun2 = 94,
    Sigill = 2,
    Skeleton = 21,
    SkeletonOfOneEyedGiant = 44,
    Soldier = 17,
    StingFly = 6,
    StingFlyTail = 7,
    Tarn = 33,
    TeoBudwell = 77,
    TeoBudwellMowing = 79,
    TeoBudwellWithGigi = 78,
    Termite = 22,
    ThePictureOfAKing = 45,
    Transparent = 128,
    Unused = 3,
    Unused10 = 58,
    Unused11 = 59,
    Unused12 = 60,
    Unused13 = 61,
    Unused14 = 62,
    Unused15 = 63,
    Unused16 = 68,
    Unused17 = 69,
    Unused18 = 71,
    Unused19 = 72,
    Unused2 = 8,
    Unused20 = 75,
    Unused21 = 100,
    Unused22 = 101,
    Unused23 = 102,
    Unused24 = 103,
    Unused3 = 20,
    Unused4 = 52,
    Unused5 = 53,
    Unused6 = 54,
    Unused7 = 55,
    Unused8 = 56,
    Unused9 = 57
};

/*!
 * \brief Enum for the possible entity state IDs in King's Field.
 */
enum class EntityStateID : uint8_t
{
    FlyingAttackMaybe = 11,
    FlyingWander = 10,
    MagicAttack = 25,
    ApproachingPlayer = 5,
    Wander = 1,
    MeleeAttack = 4,
    TakingDamage = 2,
    None = 255,
    MeleeAttack3 = 24,
    MeleeAttack2 = 23,
    Idle = 0,
    Dialogue = 112,
    Dying = 3
};

// Structs

/*!
 * \brief Structure for the entity declarations at the beginning of each map file.
 */
struct EntityClass
{
    EntityMeshID MeshID;
    uint8_t FourOrForty;
    uint8_t field_0x2;
    uint16_t KnockbackResistance;
    uint16_t field_0x5;
    uint8_t Unknown_x07;
    uint8_t Unknown_x08;
    uint8_t field_0x9;
    uint8_t SpawnDistance;
    uint8_t DespawnDistance;
    int16_t SomethingX;
    int16_t SomethingY;
    int16_t SomethingZ;
    uint16_t Unknown_x12;
    uint16_t Unknown_x14;
    int16_t LookingAtMargin1;
    int16_t LookingAtMargin2;
    uint16_t HP;
    uint16_t Unknown_x1c;
    uint16_t ExperienceGain;
    uint16_t DefSlash;
    uint16_t DefChop;
    uint16_t DefStab;
    uint16_t DefHolyMagic;
    uint16_t DefFireMagic;
    uint16_t DefEarthMagic;
    uint16_t DefWindMagic;
    uint16_t DefWaterMagic;
    uint16_t GoldSomething;
    int16_t Scale;
    uint32_t UknBitField34;
    uint32_t SomePointers[16];
} __attribute__((packed, aligned(1)));

/*!
 * \brief Structure for declarations of entity instances in the map files.
 */
struct EntityInstance
{
    uint8_t RespawnMode;
    uint8_t EntityClass;
    uint8_t NonRandomRotation;
    uint8_t WEXTilePos;
    uint8_t NSYTilePos;
    uint8_t RespawnChance;
    ObjectID DroppedItem : 8;
    uint8_t Layer;
    uint16_t ZRotation;
    int16_t FineWEXPos;
    int16_t FineNSYPos;
    int16_t FineZPos;
} __attribute__((packed, aligned(1)));

QString getEntityMeshName(const EntityMeshID entityMeshId);

QString getEntityStateIDName(const EntityStateID entityStateId);

}

#endif // KF2_ENTITY_H
