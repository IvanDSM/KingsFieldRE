#ifndef KF2_OBJECT_H
#define KF2_OBJECT_H

#include <cstdint>
#include <QString>

namespace KF2
{

// Enums

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

// Structs

/*!
 * \brief Structure for the object class declarations in the KF2 game database.
 */
struct ObjectClass
{
    ObjectClassType ClassType;
    uint8_t TransformType;
    uint8_t field_0x2;
    uint8_t field_0x3;
    uint16_t CollisionRadius;
    uint8_t field_0x6;
    uint8_t field_0x7;
    uint8_t field_0x8;
    uint8_t field_0x9;
    uint8_t field_0xa;
    uint8_t field_0xb;
    uint8_t field_0xc;
    uint8_t field_0xd;
    uint8_t field_0xe;
    uint8_t field_0xf;
    uint8_t field_0x10;
    uint8_t field_0x11;
    uint8_t field_0x12;
    uint8_t field_0x13;
    uint8_t field_0x14;
    uint8_t field_0x15;
    uint8_t field_0x16;
    uint8_t field_0x17;
} __attribute__((packed, aligned(1)));

/*!
 * \brief Structure for declarations of object instances in the map files.
 */
struct ObjectInstance
{
    uint8_t TileLayer;
    uint8_t WEXTilePos;
    uint8_t NSYTilePos;
    uint8_t field_0x3;
    ObjectID ID : 16;
    uint16_t ZRotation;
    int16_t FineWEXPos;
    int16_t FineNSYPos;
    int16_t FineZPos;
    uint8_t Flags[10];
} __attribute__((packed, aligned(1)));

// Functions

QString getObjectClassTypeName(const ObjectClassType classType);

QString getObjectName(const ObjectID itemId);

}

#endif // KF2_OBJECT_H
