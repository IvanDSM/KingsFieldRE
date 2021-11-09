#ifndef KF2_H
#define KF2_H
// I don't want any warnings for unused functions here.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

#include "core/kfmterror.h"
#include <QItemDelegate>
#include <QString>
#include <QTextCodec>

typedef uint8_t byte;
typedef byte undefined;
#if (defined(__GNUC__) && defined(__MINGW32__)) || defined(EMSCRIPTEN)
typedef uint16_t u_short;
typedef uint32_t u_int;
#endif

#pragma once

namespace KingsFieldII
{
// Unknown string

static const QString unknownString = QStringLiteral("???");

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

/*!
 * \brief Enum for the type of an object class.
 */
enum ObjectClassType : uint8_t
{
    DragonGrass = 19,
    DragonStoneSlot = 161,
    FloorTrap = 84,
    GuidePost = 15,
    GuyraWarp = 34,
    Hider = 9,
    LoadTrigger = 224,
    Minecart = 32,
    None = 255,
    PickableItem = 64,
    RhombusKeySlot = 17,
    RotatesToOpen = 4,
    SavePoint = 14,
    SecretCompartment = 5,
    ShrineKeySlot = 164,
    Sign = 13,
    SkullKeySlot = 160,
    Skybox = 240,
    SlidesToOpen = 22,
    Switch = 83,
    Trap = 81,
    VerticalDoor = 2,
    VerticalDoor2 = 3,
    WaterWell = 18
};

/*!
 * \brief Enum for the Item IDs in King's Field.
 */
enum class ObjectID : uint32_t
{
    ABrokenSword = 264,
    ASoldierOfVerdite = 141,
    ArmsA = 46,
    ArmsDemonsHands = 44,
    ArmsIronGloves = 41,
    ArmsRuinousGloves = 45,
    ArmsSilverArms = 43,
    ArmsStoneHands = 42,
    Barrel = 179,
    Bed = 282,
    BigGreyDoorLeft = 128,
    BigGreyDoorRight = 127,
    BigRoughStoneDoor = 129,
    BigStoneDoor = 135,
    BodyA = 33,
    BodyBreastPlate = 28,
    BodyDarkArmor = 31,
    BodyIceArmor = 30,
    BodyKnightPlate = 29,
    BodySeathsArmor = 32,
    Bones = 143,
    Bones2 = 144,
    Bucket = 180,
    CeilingTorch = 280,
    Chair = 259,
    ColosseumDoor = 140,
    CopperKnightStatue = 169,
    CrossFeetTable = 256,
    DaytimeSkybox = 244,
    DeadCrystalMiner = 146,
    DeadDudeRENAME_ME = 147,
    DemonLordFromMadScientistTube = 275,
    DemonLordStatue = 170,
    DragonGrass = 278,
    DragonStoneSlot = 187,
    DrawbridgeSwitch = 210,
    DummyItem1 = 60,
    DummyItem2 = 61,
    DummyItem3 = 62,
    DummyItem4 = 63,
    DummyItem5 = 64,
    DummyItem6 = 65,
    DummyItem7 = 66,
    EarthElementalStatue = 168,
    ElfsGrave = 153,
    EquipItemAmuletOfMist = 58,
    EquipItemEarthRing = 56,
    EquipItemLightwaveRing = 59,
    EquipItemPsycprosCollar = 57,
    EquipItemScorpionsBracelet = 53,
    EquipItemSeathsBracelet = 55,
    EquipItemSeathsTear = 54,
    FeetA = 52,
    FeetDeathWalkers = 50,
    FeetIronBoots = 47,
    FeetLegGuarders = 48,
    FeetRuinousBoots = 51,
    FeetSilverBoots = 49,
    GoldenThingRENAME_ME = 265,
    GreenWallFloorTrap = 206,
    GreenWallSecretDoor = 205,
    GreenWallWithSecret1 = 209,
    GreenWallWithSecret2 = 214,
    GreenWallWithSpikeTrap = 213,
    Guidepost = 189,
    GuyraTeleportCube = 231,
    HarvineCastleSign = 159,
    HarvinesCastleDoor = 194,
    HarvinesThrone = 262,
    HeadA = 27,
    HeadBloodCrown = 24,
    HeadGreatHelm = 23,
    HeadIronMask = 21,
    HeadKnightHelm = 22,
    HeadLightningHelm = 25,
    HeadSeathsHelm = 26,
    InvisibleObject = 183,
    ItemAHerb = 110,
    ItemAHerb2 = 119,
    ItemAPotion = 81,
    ItemARing = 98,
    ItemAntidote = 75,
    ItemArrowForTheBow = 117,
    ItemBloodStone = 71,
    ItemBluePotion = 77,
    ItemCrystal = 96,
    ItemCrystalFlask = 82,
    ItemCrystalShard = 97,
    ItemDarkCrystal = 95,
    ItemDemonsPick = 87,
    ItemDragonCrystal = 76,
    ItemDragonStone = 105,
    ItemEarthCrystal = 92,
    ItemEarthHerb = 74,
    ItemElfsBolt = 118,
    ItemElfsKey = 99,
    ItemFigureOfSeath = 83,
    ItemFireCrystal = 90,
    ItemGoldCoin = 70,
    ItemGoldKey = 108,
    ItemGoldPotion = 80,
    ItemGreenPotion = 79,
    ItemGroundBell = 89,
    ItemHarvinesFlute = 88,
    ItemHarvinesKey = 104,
    ItemJailKey = 102,
    ItemLightCrystal = 94,
    ItemMagiciansKey = 106,
    ItemMinersMap = 68,
    ItemMoonGate = 111,
    ItemMoonKey = 114,
    ItemMoonStone = 72,
    ItemNecronsMap = 69,
    ItemPhantomRod = 84,
    ItemPiratesKey = 100,
    ItemPiratesMap = 67,
    ItemRedPotion = 78,
    ItemRhombusKey = 103,
    ItemSeathsPlume = 86,
    ItemShrineKey = 109,
    ItemSilverKey = 107,
    ItemSkullKey = 101,
    ItemStarGate = 112,
    ItemStarKey = 115,
    ItemSunGate = 113,
    ItemSunKey = 116,
    ItemTruthGlass = 85,
    ItemVerdite = 73,
    ItemWaterCrystal = 91,
    ItemWindCrystal = 93,
    JailDoor = 132,
    KnockerDoorLeft = 126,
    KnockerDoorRight = 125,
    Lantern = 277,
    LoadArea = 240,
    MadScientistBox = 173,
    MadScientistLightCrystalMachine = 145,
    MadScientistTube = 276,
    MarbleWallFloorTrap = 203,
    MineSign = 165,
    Minecart = 177,
    MinersGraveMaybe = 151,
    Moon = 248,
    MountainSkybox = 245,
    NighttimeSkybox = 247,
    NighttimeSkybox2 = 249,
    None = 255,
    PillarOfWind = 157,
    RedFlower = 287,
    RhombusKeyDoor = 139,
    RhombusKeySlot = 184,
    SamuraisGrave = 149,
    Savepoint = 230,
    SeathsFountainDoorLeft = 133,
    SeathsFountainDoorRight = 134,
    SeathsFountainPillar = 191,
    SecretDoor = 130,
    Shelf = 285,
    ShieldA = 40,
    ShieldCrystalGuard = 37,
    ShieldLargeShield = 35,
    ShieldLeatherShield = 34,
    ShieldMoonGuard = 36,
    ShieldSeathsShield = 39,
    ShieldSkullShield = 38,
    ShovelAndHammer = 263,
    ShrineKeySlot = 188,
    Sign = 158,
    SimpleStoolMaybeRENAME_ME = 284,
    SkullKeySlot = 185,
    SkullKeyWaterObstacle = 204,
    SlotForSomethingRENAME_ME = 186,
    SmallBed = 283,
    SmallStackOfLogs = 286,
    SmallTable = 136,
    SmallWeirdPillarRENAME_ME = 274,
    SomeBrokenGrave = 155,
    SomeBrokenGrave2 = 156,
    SomeDoorHandleRENAME_ME = 211,
    SomeGrave = 154,
    SquareWell = 124,
    StoneChestBody = 123,
    StoneChestLid = 122,
    StoneGobletWithLavaRENAME_ME = 272,
    StonePillar = 172,
    StoneThing2RENAME_ME = 267,
    StoneThing3RENAME_ME = 268,
    StoneThingRENAME_ME = 266,
    Stool = 261,
    SwingingScythe = 200,
    SwingingSpikeBall = 201,
    TableWithThingie = 257,
    TarnStatue = 171,
    TheMagiciansLamp = 163,
    TheSoldiersGrave = 152,
    ThreeStones = 289,
    TinyXFeetTable = 260,
    Tree = 270,
    WHATTHEFUCKStatue = 193,
    WTF = 65535,
    WallTorch = 279,
    WallWithSecret = 131,
    WallWithSecret2 = 138,
    WallWithSpikeTrap = 202,
    WallWriting = 160,
    WallWriting2 = 161,
    WallWriting3 = 162,
    WaterWell = 195,
    WeaponA1 = 7,
    WeaponA2 = 8,
    WeaponA3 = 18,
    WeaponA4 = 19,
    WeaponA5 = 20,
    WeaponArbalest = 17,
    WeaponBastardSword = 5,
    WeaponBattleHammer = 4,
    WeaponBow = 16,
    WeaponCrescentAxe = 6,
    WeaponDagger = 0,
    WeaponDarkSlayer = 15,
    WeaponFlameSword = 9,
    WeaponIceBlade = 12,
    WeaponKnightSword = 2,
    WeaponMoonlightSword = 14,
    WeaponMorningStar = 3,
    WeaponSeathsSword = 13,
    WeaponShiden = 10,
    WeaponShortSword = 1,
    WeaponSpider = 11,
    WeirdPillarRENAME_ME = 273,
    WhitePinkFlower = 288,
    WoodenChestBody = 121,
    WoodenChestLid = 120,
    WoodenThingRENAME_ME = 182,
    XFeetTable = 258
};

// Functions

QString getEntityMeshName(const EntityMeshID entityMeshId);

inline static EntityMeshID getEntityMeshIDFromByte(const byte meshId)
{
    return static_cast<EntityMeshID>(meshId);
}

inline static byte getEntityMeshIDAsByte(const EntityMeshID entityMeshId)
{
    return static_cast<byte>(entityMeshId);
}

QString getEntityStateIDName(const EntityStateID entityStateId);

inline static EntityStateID getEntityStateIDFromByte(const byte stateId)
{
    return static_cast<EntityStateID>(stateId);
}

inline static byte getEntityStateIDAsByte(const EntityStateID entityStateId)
{
    return static_cast<byte>(entityStateId);
}

QString getMagicIDName(const MagicID magicId);

inline static MagicID getMagicIDFromByte(const byte magicId)
{
    return static_cast<MagicID>(magicId);
}

inline static byte getMagicIDAsByte(const MagicID magicId)
{
    return static_cast<byte>(magicId);
}

QString getObjectClassTypeName(const ObjectClassType classType);

QString getObjectName(const ObjectID itemId);

inline static ObjectID getObjectIDFromByte(const byte objectId)
{
    return static_cast<ObjectID>(objectId);
}

inline static ObjectID getObjectIDFromUShort(const uint16_t objectId)
{
    return static_cast<ObjectID>(objectId);
}

inline static byte getObjectIDAsByte(const ObjectID objectId)
{
    return static_cast<byte>(objectId);
}

inline static unsigned short getObjectIDAsUShort(const ObjectID objectId)
{
    return static_cast<unsigned short>(objectId);
}

QString getWeaponStatsName(const byte weaponStatsIndex);

// Structs

/*!
 * \brief Structure for armor stats in King's Field.
 */
struct ArmorStats
{
    u_short Thingie;
    u_short DefSlash;
    u_short DefChop;
    u_short DefStab;
    u_short DefPoison;
    u_short DefDarkM;
    u_short DefFireM;
    u_short DefEarthM;
    u_short DefWindM;
    u_short DefWaterM;
    u_short field_0x14;
    u_short field_0x16;
    u_short field_0x18;
    u_short field_0x1a;
    u_short field_0x1c;
    u_short field_0x1e;
} __attribute__((packed, aligned(1)));

/*!
 * \brief Structure for the entity declarations at the beginning of each map file.
 */
struct EntityClass
{
    EntityMeshID MeshID;
    byte FourOrForty;
    undefined field_0x2;
    u_short KnockbackResistance;
    u_short field_0x5;
    byte Unknown_x07;
    byte Unknown_x08;
    undefined field_0x9;
    byte SpawnDistance;
    byte DespawnDistance;
    short SomethingX;
    short SomethingY;
    short SomethingZ;
    u_short Unknown_x12;
    u_short Unknown_x14;
    short LookingAtMargin1;
    short LookingAtMargin2;
    u_short HP;
    u_short Unknown_x1c;
    u_short ExperienceGain;
    u_short DefSlash;
    u_short DefChop;
    u_short DefStab;
    u_short DefHolyMagic;
    u_short DefFireMagic;
    u_short DefEarthMagic;
    u_short DefWindMagic;
    u_short DefWaterMagic;
    u_short GoldSomething;
    short Scale;
    u_int UknBitField34;
    u_int SomePointers[16];
} __attribute__((packed, aligned(1)));

/*!
 * \brief Structure for declarations of entity instances in the map files.
 */
struct EntityInstance
{
    byte RespawnMode;
    byte EntityClass;
    byte NonRandomRotation;
    byte WEXTilePos;
    byte NSYTilePos;
    byte RespawnChance;
    ObjectID DroppedItem : 8;
    byte Layer;
    u_short ZRotation;
    short FineWEXPos;
    short FineNSYPos;
    short FineZPos;
} __attribute__((packed, aligned(1)));

/*!
 * \brief Structure for the definition of magic spells.
 */
struct Magic
{
    bool PlayerHas;
    byte ChargeRecoveryTime;
    undefined field_0x2;
    undefined field_0x3;
    byte StatusEffect;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    u_short SomeDmg1;
    u_short SomeDmg2;
    u_short SomeDmg3;
    u_short FireDmg;
    u_short EarthDmg;
    u_short WindDmg;
    u_short WaterDmg;
    u_short MPCost;
    undefined field_0x18;
    undefined field_0x19;
} __attribute__((packed, aligned(1)));

/*!
 * \brief Structure for the object class declarations in the KF2 game database.
 */
struct ObjectClass
{
    ObjectClassType ClassType;
    byte TransformType;
    undefined field_0x2;
    undefined field_0x3;
    u_short CollisionRadius;
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
} __attribute__((packed, aligned(1)));

/*!
 * \brief Structure for declarations of object instances in the map files.
 */
struct ObjectInstance
{
    byte TileLayer;
    byte WEXTilePos;
    byte NSYTilePos;
    undefined field_0x3;
    ObjectID ID : 16;
    u_short ZRotation;
    short FineWEXPos;
    short FineNSYPos;
    short FineZPos;
    byte Flags[10];
} __attribute__((packed, aligned(1)));

/*!
 * \brief Holds HP, MP, Str and Magic Power Differences and Experience for the next level for each level the player can achieve.
 */
struct PlayerLvlData
{
    quint16 BaseHP;
    quint16 BaseMP;
    quint16 StrPowerPlus;
    quint16 MagPowerPlus;
    quint32 ExpForNextLevel;
} __attribute__((packed, aligned(1)));

/*!
 * \brief Standard PS1 short vector structure.
 */
struct SVECTOR
{
    short vx;
    short vy;
    short vz;
    short pad;

    friend QDataStream& operator>>(QDataStream& in, SVECTOR& sVec)
    {
        in >> sVec.vx;
        in >> sVec.vy;
        in >> sVec.vz;
        in >> sVec.pad;
        return in;
    }

    friend QDataStream& operator<<(QDataStream& out, const SVECTOR& sVec)
    {
        out << sVec.vx;
        out << sVec.vy;
        out << sVec.vz;
        out << sVec.pad;

        return out;
    }
};

/*!
 * \brief Structure for a tile in King's Field.
 */
struct Tile
{
    uint8_t TileID;
    uint8_t Elevation;
    uint8_t Rotation; ///< 0-3, each step is 90°
    uint8_t CollisionIndex;
    uint8_t Flags;

    bool getEnemyBlock() const { return (Flags & 0b01000000) != 0; }
    uint8_t getRenderParameterIndex() const { return Flags & 63u; }
    bool getSwitchLayer() const { return (Flags & 0b10000000) != 0; }

    void setEnemyBlock(bool newValue)
    {
        Flags = (Flags & 0b10111111) | (static_cast<uint8_t>(newValue) << 6);
    }
    void setSwitchLayer(bool newValue)
    {
        Flags = (Flags & 0b01111111) | (static_cast<uint8_t>(newValue) << 7);
    }

} __attribute__((packed, aligned(1)));

/*!
 * \brief Structure for a metatile in King's Field.
 * A metatile contains two tiles structures for one position: 
 * one for the 1st layer and one for the 2nd layer.
 */
struct MetaTile
{
    Tile layer1;
    Tile layer2;
} __attribute__((packed, aligned(1)));

/*!
 * \brief Structure for VFX objects in King's Field.
 */
struct VFX
{
    u_short VFXID;
    byte AnimFrameCount;
    byte AnimSpeed;
    byte TileLayer;
    byte TileWEX;
    byte TileNSY;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    short FineXPos;
    short FineYPos;
    short FineZPos;
} __attribute__((packed, aligned(1)));

/*!
 * \brief Stats structure for weapons.
 */
struct WeaponStats
{
    byte SoundEffect;
    byte StrStaminaCost;
    byte Unknown_x02;
    MagicID Spell1;
    MagicID Spell2;
    byte Spell1ShotAmount;
    u_short OffSlash;
    u_short OffChop;
    u_short OffStab;
    u_short OffHolyM;
    u_short OffFireM;
    u_short OffEarthM;
    u_short OffWindM;
    u_short OffWaterM;
    u_short HPRestoreTimer;
    u_short MPRestoreTimer;
    short AttackRange;
    u_short SwingSpeed;
    u_short SwingDamageStartTime;
    u_short Spell1CastStartTime;
    u_short Spell1CastEndTime;
    short Spell2AnimSpeed;
    u_short Unknown_x26;
    u_short Spell2DamageStartTime;
    u_short Unknown_x2a;
    u_short Unknown_x2c;
    u_short Unknown_x2e;
    u_short Unknown_x30;
    short Unknown_x32;
    SVECTOR Position;
    SVECTOR SomeVec;
} __attribute__((packed, aligned(1)));

struct String
{
    char str[24];
} __attribute__((packed, aligned(1)));

struct LongString
{
    char str[308];
} __attribute__((packed, aligned(1)));

struct PosString
{
    short X;
    short Y;
    char str[24];
} __attribute__((packed, aligned(1)));

// KFMT-specific

class KF2UTextCodec : public QTextCodec
{
public:
    QByteArray name() const override { return "KF2U"; }

    int mibEnum() const override { return 0x12345678; }

    KF2UTextCodec() : QTextCodec() {}

protected:
    QString convertToUnicode(const char* in, int length, ConverterState* state) const override;
    QByteArray convertFromUnicode(const QChar* in, int length, ConverterState* state) const override;

private:
    enum Direction
    {
        From,
        To
    };

    void kf2UConvert(const char* in, int length, ConverterState* state, Direction direction) const;
};

class KF2UTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit KF2UTextDelegate(QObject* parent) : QItemDelegate(parent) {}

    QWidget* createEditor(QWidget* parent,
                          const QStyleOptionViewItem&,
                          const QModelIndex&) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor,
                      QAbstractItemModel* model,
                      const QModelIndex& index) const override;
    void updateEditorGeometry(QWidget* editor,
                              const QStyleOptionViewItem& option,
                              const QModelIndex& index) const override;
};

// Constants

/*!
 * \brief Rotation coefficient used for converting PS1 format angles from/to degrees.
 * To get PS1 format angles from degrees, divide the angle in degrees by the coefficient.
 * To get degrees from PS1 format angles, multiplye the angle in PS1 format by the coffiecient.
 */
constexpr static const double rotationCoefficient = 360.0 / 4096.0;
}

#pragma GCC diagnostic pop
#endif // KF2_H
