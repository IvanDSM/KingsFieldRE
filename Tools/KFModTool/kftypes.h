#ifndef KFTYPES_H
#define KFTYPES_H

#include <QDataStream>
#include <QString>

#if __GNUC__ >= 10
#include <unordered_map>
#else
#include <map>
#endif

typedef quint8 byte;
typedef byte undefined;
#if (defined(__GNUC__) && defined(__MINGW32__)) || defined(EMSCRIPTEN)
typedef quint16 u_short;
typedef quint32 u_int;
#endif


namespace KingsField
{

    // Enums

    /*!
     * \brief Enum for the entity meshes in King's Field.
     */
    enum class EntityMeshID {
        AlHunt=83,
        Archer=18,
        Baltail=4,
        BaltailTail=5,
        Billent=42,
        Bitt=50,
        Cable=41,
        CellfyFoss=64,
        CellfyFoss2=65,
        CliffLore=86,
        CopperKnight=34,
        DalfVice=89,
        DavidTabler=88,
        DemonLord=28,
        DiasBagil=35,
        DragonGrass=107,
        EarnestClyde=96,
        EarnestClydeSitting=106,
        EarthElemental=31,
        FaiFadlin=85,
        FireElemental=9,
        Ghost=10,
        GiantTermite=25,
        GigiBudwell=74,
        GigiBudwellWatering=76,
        GreenSlime=0,
        GreenSlime2=12,
        GreenSlime3=13,
        GreenSlime4=19,
        GreenSlimeDeath=36,
        GreenSlimeDeath2=37,
        GreenSlimeDeath3=38,
        GreenSlimeDeath4=43,
        Guyra=39,
        HarrisCarvitto=84,
        HeadEater=14,
        JoseHarven=67,
        JoseHavenDeath=104,
        JoseHavenDeath2=108,
        Kald=23,
        KarenShore=80,
        KarenShoreChair=99,
        KehlHunt=97,
        KehlHunt2=98,
        KrakenBody=29,
        KrakenHead=30,
        KrolaAmgun=91,
        KrolaAmgunCooking=92,
        LeonShore=81,
        LeonShoreWatering=82,
        LogStalker=27,
        MagesCandlesticks=49,
        MarkWozz=95,
        MechaDemonLord=46,
        MechaReik=48,
        MechaTermite=47,
        Meryl=73,
        Miria=109,
        Mogle=15,
        NolaBagil=70,
        None=255,
        PoisonSlime=1,
        Psythe=24,
        RaddBilheim=90,
        RaffyFoss=66,
        RandFerrer=87,
        RedSpikeBall=26,
        Refma=32,
        Refma2=51,
        Reik=11,
        SKnight=16,
        SaintGrave=105,
        Salamander=40,
        SandlerAmgun=93,
        SandlerAmgun2=94,
        Sigill=2,
        Skeleton=21,
        SkeletonOfOneEyedGiant=44,
        Soldier=17,
        StingFly=6,
        StingFlyTail=7,
        Tarn=33,
        TeoBudwell=77,
        TeoBudwellMowing=79,
        TeoBudwellWithGigi=78,
        Termite=22,
        ThePictureOfAKing=45,
        Transparent=128,
        Unused=3,
        Unused10=58,
        Unused11=59,
        Unused12=60,
        Unused13=61,
        Unused14=62,
        Unused15=63,
        Unused16=68,
        Unused17=69,
        Unused18=71,
        Unused19=72,
        Unused2=8,
        Unused20=75,
        Unused21=100,
        Unused22=101,
        Unused23=102,
        Unused24=103,
        Unused3=20,
        Unused4=52,
        Unused5=53,
        Unused6=54,
        Unused7=55,
        Unused8=56,
        Unused9=57
    };

    /*!
     * \brief Enum for the Magic IDs in King's Field.
     */
    enum class MagicID
    {
        ArcherArrow=31,
        ArcherParalyzeArrow=29,
        Breath=19,
        DarkSlayerMagicA=44,
        DarkSlayerMagicB=45,
        Dispoison=14,
        DoubleFireball=23,
        EarthHeal=16,
        EarthWave=2,
        EnemyEarthMagic=32,
        EnemyHomingEarthMagic=33,
        EnemyLightningVolt=54,
        FireBall=7,
        FireStorm=9,
        FireWall=8,
        Flame=10,
        FlameSwordMagicA=49,
        FlameSwordMagicB=50,
        Flash=12,
        Freeze=6,
        IceBladeMagicA=38,
        IceBladeMagicB=39,
        IceStorm=5,
        Light=18,
        LightningVolt=11,
        Meteor=3,
        MissileShield=17,
        MoonlightSwordMagicA=42,
        MoonlightSwordMagicB=43,
        None=255,
        PsytheCurseOrb=26,
        ResistFire=15,
        SKnightPoisonBreath=22,
        Seath=13,
        SeathsSwordMagicA=40,
        ShidenMagicA=34,
        ShidenMagicB=35,
        SpiderSwordMagicA=51,
        SpiderSwordMagicB=52,
        Stone=1,
        TarnWindMagic=24,
        WaterFall=0,
        WindCutter=4
    };

    /*!
     * \brief Enum for the Item IDs in King's Field.
     */
    enum class ObjectID
    {
        ABrokenSword=264,
        ASoldierOfVerdite=141,
        ArmsA=46,
        ArmsDemonsHands=44,
        ArmsIronGloves=41,
        ArmsRuinousGloves=45,
        ArmsSilverArms=43,
        ArmsStoneHands=42,
        Barrel=179,
        Bed=282,
        BigGreyDoorLeft=128,
        BigGreyDoorRight=127,
        BigRoughStoneDoor=129,
        BigStoneDoor=135,
        BodyA=33,
        BodyBreastPlate=28,
        BodyDarkArmor=31,
        BodyIceArmor=30,
        BodyKnightPlate=29,
        BodySeathsArmor=32,
        Bones=143,
        Bones2=144,
        Bucket=180,
        CeilingTorch=280,
        Chair=259,
        ColosseumDoor=140,
        CopperKnightStatue=169,
        CrossFeetTable=256,
        DaytimeSkybox=244,
        DeadCrystalMiner=146,
        DeadDudeRENAME_ME=147,
        DemonLordFromMadScientistTube=275,
        DemonLordStatue=170,
        DragonGrass=278,
        DragonStoneSlot=187,
        DrawbridgeSwitch=210,
        DummyItem1=60,
        DummyItem2=61,
        DummyItem3=62,
        DummyItem4=63,
        DummyItem5=64,
        DummyItem6=65,
        DummyItem7=66,
        EarthElementalStatue=168,
        ElfsGrave=153,
        EquipItemAmuletOfMist=58,
        EquipItemEarthRing=56,
        EquipItemLightwaveRing=59,
        EquipItemPsycprosCollar=57,
        EquipItemScorpionsBracelet=53,
        EquipItemSeathsBracelet=55,
        EquipItemSeathsTear=54,
        FeetA=52,
        FeetDeathWalkers=50,
        FeetIronBoots=47,
        FeetLegGuarders=48,
        FeetRuinousBoots=51,
        FeetSilverBoots=49,
        GoldenThingRENAME_ME=265,
        GreenWallFloorTrap=206,
        GreenWallSecretDoor=205,
        GreenWallWithSecret1=209,
        GreenWallWithSecret2=214,
        GreenWallWithSpikeTrap=213,
        Guidepost=189,
        GuyraTeleportCube=231,
        HarvineCastleSign=159,
        HarvinesCastleDoor=194,
        HarvinesThrone=262,
        HeadA=27,
        HeadBloodCrown=24,
        HeadGreatHelm=23,
        HeadIronMask=21,
        HeadKnightHelm=22,
        HeadLightningHelm=25,
        HeadSeathsHelm=26,
        InvisibleObject=183,
        ItemAHerb=110,
        ItemAHerb2=119,
        ItemAPotion=81,
        ItemARing=98,
        ItemAntidote=75,
        ItemArrowForTheBow=117,
        ItemBloodStone=71,
        ItemBluePotion=77,
        ItemCrystal=96,
        ItemCrystalFlask=82,
        ItemCrystalShard=97,
        ItemDarkCrystal=95,
        ItemDemonsPick=87,
        ItemDragonCrystal=76,
        ItemDragonStone=105,
        ItemEarthCrystal=92,
        ItemEarthHerb=74,
        ItemElfsBolt=118,
        ItemElfsKey=99,
        ItemFigureOfSeath=83,
        ItemFireCrystal=90,
        ItemGoldCoin=70,
        ItemGoldKey=108,
        ItemGoldPotion=80,
        ItemGreenPotion=79,
        ItemGroundBell=89,
        ItemHarvinesFlute=88,
        ItemHarvinesKey=104,
        ItemJailKey=102,
        ItemLightCrystal=94,
        ItemMagiciansKey=106,
        ItemMinersMap=68,
        ItemMoonGate=111,
        ItemMoonKey=114,
        ItemMoonStone=72,
        ItemNecronsMap=69,
        ItemPhantomRod=84,
        ItemPiratesKey=100,
        ItemPiratesMap=67,
        ItemRedPotion=78,
        ItemRhombusKey=103,
        ItemSeathsPlume=86,
        ItemShrineKey=109,
        ItemSilverKey=107,
        ItemSkullKey=101,
        ItemStarGate=112,
        ItemStarKey=115,
        ItemSunGate=113,
        ItemSunKey=116,
        ItemTruthGlass=85,
        ItemVerdite=73,
        ItemWaterCrystal=91,
        ItemWindCrystal=93,
        JailDoor=132,
        KnockerDoorLeft=126,
        KnockerDoorRight=125,
        Lantern=277,
        LoadArea=240,
        MadScientistBox=173,
        MadScientistLightCrystalMachine=145,
        MadScientistTube=276,
        MarbleWallFloorTrap=203,
        MineSign=165,
        Minecart=177,
        MinersGraveMaybe=151,
        Moon=248,
        MountainSkybox=245,
        NighttimeSkybox=247,
        NighttimeSkybox2=249,
        None=255,
        PillarOfWind=157,
        RedFlower=287,
        RhombusKeyDoor=139,
        RhombusKeySlot=184,
        SamuraisGrave=149,
        Savepoint=230,
        SeathsFountainDoorLeft=133,
        SeathsFountainDoorRight=134,
        SeathsFountainPillar=191,
        SecretDoor=130,
        Shelf=285,
        ShieldA=40,
        ShieldCrystalGuard=37,
        ShieldLargeShield=35,
        ShieldLeatherShield=34,
        ShieldMoonGuard=36,
        ShieldSeathsShield=39,
        ShieldSkullShield=38,
        ShovelAndHammer=263,
        ShrineKeySlot=188,
        Sign=158,
        SimpleStoolMaybeRENAME_ME=284,
        SkullKeySlot=185,
        SkullKeyWaterObstacle=204,
        SlotForSomethingRENAME_ME=186,
        SmallBed=283,
        SmallStackOfLogs=286,
        SmallTable=136,
        SmallWeirdPillarRENAME_ME=274,
        SomeBrokenGrave=155,
        SomeBrokenGrave2=156,
        SomeDoorHandleRENAME_ME=211,
        SomeGrave=154,
        SquareWell=124,
        StoneChestBody=123,
        StoneChestLid=122,
        StoneGobletWithLavaRENAME_ME=272,
        StonePillar=172,
        StoneThing2RENAME_ME=267,
        StoneThing3RENAME_ME=268,
        StoneThingRENAME_ME=266,
        Stool=261,
        SwingingScythe=200,
        SwingingSpikeBall=201,
        TableWithThingie=257,
        TarnStatue=171,
        TheMagiciansLamp=163,
        TheSoldiersGrave=152,
        ThreeStones=289,
        TinyXFeetTable=260,
        Tree=270,
        WHATTHEFUCKStatue=193,
        WTF=65535,
        WallTorch=279,
        WallWithSecret=131,
        WallWithSecret2=138,
        WallWithSpikeTrap=202,
        WallWriting=160,
        WallWriting2=161,
        WallWriting3=162,
        WaterWell=195,
        WeaponA1=7,
        WeaponA2=8,
        WeaponA3=18,
        WeaponA4=19,
        WeaponA5=20,
        WeaponArbalest=17,
        WeaponBastardSword=5,
        WeaponBattleHammer=4,
        WeaponBow=16,
        WeaponCrescentAxe=6,
        WeaponDagger=0,
        WeaponDarkSlayer=15,
        WeaponFlameSword=9,
        WeaponIceBlade=12,
        WeaponKnightSword=2,
        WeaponMoonlightSword=14,
        WeaponMorningStar=3,
        WeaponSeathsSword=13,
        WeaponShiden=10,
        WeaponShortSword=1,
        WeaponSpider=11,
        WeirdPillarRENAME_ME=273,
        WhitePinkFlower=288,
        WoodenChestBody=121,
        WoodenChestLid=120,
        WoodenThingRENAME_ME=182,
        XFeetTable=258
    };

    // Maps

#if __GNUC__ >= 10
    static const std::unordered_map<const EntityMeshID, const QString> entityMeshIdNameMap =
#else
    static const std::map<const EntityMeshID, const QString> entityMeshIdNameMap =
#endif
    {
        {EntityMeshID::AlHunt, "AlHunt"},
        {EntityMeshID::Archer, "Archer"},
        {EntityMeshID::Baltail, "Baltail"},
        {EntityMeshID::BaltailTail, "BaltailTail"},
        {EntityMeshID::Billent, "Billent"},
        {EntityMeshID::Bitt, "Bitt"},
        {EntityMeshID::Cable, "Cable"},
        {EntityMeshID::CellfyFoss, "CellfyFoss"},
        {EntityMeshID::CellfyFoss2, "CellfyFoss2"},
        {EntityMeshID::CliffLore, "CliffLore"},
        {EntityMeshID::CopperKnight, "CopperKnight"},
        {EntityMeshID::DalfVice, "DalfVice"},
        {EntityMeshID::DavidTabler, "DavidTabler"},
        {EntityMeshID::DemonLord, "DemonLord"},
        {EntityMeshID::DiasBagil, "DiasBagil"},
        {EntityMeshID::DragonGrass, "DragonGrass"},
        {EntityMeshID::EarnestClyde, "EarnestClyde"},
        {EntityMeshID::EarnestClydeSitting, "EarnestClydeSitting"},
        {EntityMeshID::EarthElemental, "EarthElemental"},
        {EntityMeshID::FaiFadlin, "FaiFadlin"},
        {EntityMeshID::FireElemental, "FireElemental"},
        {EntityMeshID::Ghost, "Ghost"},
        {EntityMeshID::GiantTermite, "GiantTermite"},
        {EntityMeshID::GigiBudwell, "GigiBudwell"},
        {EntityMeshID::GigiBudwellWatering, "GigiBudwellWatering"},
        {EntityMeshID::GreenSlime, "GreenSlime"},
        {EntityMeshID::GreenSlime2, "GreenSlime2"},
        {EntityMeshID::GreenSlime3, "GreenSlime3"},
        {EntityMeshID::GreenSlime4, "GreenSlime4"},
        {EntityMeshID::GreenSlimeDeath, "GreenSlimeDeath"},
        {EntityMeshID::GreenSlimeDeath2, "GreenSlimeDeath2"},
        {EntityMeshID::GreenSlimeDeath3, "GreenSlimeDeath3"},
        {EntityMeshID::GreenSlimeDeath4, "GreenSlimeDeath4"},
        {EntityMeshID::Guyra, "Guyra"},
        {EntityMeshID::HarrisCarvitto, "HarrisCarvitto"},
        {EntityMeshID::HeadEater, "HeadEater"},
        {EntityMeshID::JoseHarven, "JoseHarven"},
        {EntityMeshID::JoseHavenDeath, "JoseHavenDeath"},
        {EntityMeshID::JoseHavenDeath2, "JoseHavenDeath2"},
        {EntityMeshID::Kald, "Kald"},
        {EntityMeshID::KarenShore, "KarenShore"},
        {EntityMeshID::KarenShoreChair, "KarenShoreChair"},
        {EntityMeshID::KehlHunt, "KehlHunt"},
        {EntityMeshID::KehlHunt2, "KehlHunt2"},
        {EntityMeshID::KrakenBody, "KrakenBody"},
        {EntityMeshID::KrakenHead, "KrakenHead"},
        {EntityMeshID::KrolaAmgun, "KrolaAmgun"},
        {EntityMeshID::KrolaAmgunCooking, "KrolaAmgunCooking"},
        {EntityMeshID::LeonShore, "LeonShore"},
        {EntityMeshID::LeonShoreWatering, "LeonShoreWatering"},
        {EntityMeshID::LogStalker, "LogStalker"},
        {EntityMeshID::MagesCandlesticks, "MagesCandlesticks"},
        {EntityMeshID::MarkWozz, "MarkWozz"},
        {EntityMeshID::MechaDemonLord, "MechaDemonLord"},
        {EntityMeshID::MechaReik, "MechaReik"},
        {EntityMeshID::MechaTermite, "MechaTermite"},
        {EntityMeshID::Meryl, "Meryl"},
        {EntityMeshID::Miria, "Miria"},
        {EntityMeshID::Mogle, "Mogle"},
        {EntityMeshID::NolaBagil, "NolaBagil"},
        {EntityMeshID::None, "None"},
        {EntityMeshID::PoisonSlime, "PoisonSlime"},
        {EntityMeshID::Psythe, "Psythe"},
        {EntityMeshID::RaddBilheim, "RaddBilheim"},
        {EntityMeshID::RaffyFoss, "RaffyFoss"},
        {EntityMeshID::RandFerrer, "RandFerrer"},
        {EntityMeshID::RedSpikeBall, "RedSpikeBall"},
        {EntityMeshID::Refma, "Refma"},
        {EntityMeshID::Refma2, "Refma2"},
        {EntityMeshID::Reik, "Reik"},
        {EntityMeshID::SKnight, "SKnight"},
        {EntityMeshID::SaintGrave, "SaintGrave"},
        {EntityMeshID::Salamander, "Salamander"},
        {EntityMeshID::SandlerAmgun, "SandlerAmgun"},
        {EntityMeshID::SandlerAmgun2, "SandlerAmgun2"},
        {EntityMeshID::Sigill, "Sigill"},
        {EntityMeshID::Skeleton, "Skeleton"},
        {EntityMeshID::SkeletonOfOneEyedGiant, "SkeletonOfOneEyedGiant"},
        {EntityMeshID::Soldier, "Soldier"},
        {EntityMeshID::StingFly, "StingFly"},
        {EntityMeshID::StingFlyTail, "StingFlyTail"},
        {EntityMeshID::Tarn, "Tarn"},
        {EntityMeshID::TeoBudwell, "TeoBudwell"},
        {EntityMeshID::TeoBudwellMowing, "TeoBudwellMowing"},
        {EntityMeshID::TeoBudwellWithGigi, "TeoBudwellWithGigi"},
        {EntityMeshID::Termite, "Termite"},
        {EntityMeshID::ThePictureOfAKing, "ThePictureOfAKing"},
        {EntityMeshID::Transparent, "Transparent"},
        {EntityMeshID::Unused, "Unused"},
        {EntityMeshID::Unused10, "Unused10"},
        {EntityMeshID::Unused11, "Unused11"},
        {EntityMeshID::Unused12, "Unused12"},
        {EntityMeshID::Unused13, "Unused13"},
        {EntityMeshID::Unused14, "Unused14"},
        {EntityMeshID::Unused15, "Unused15"},
        {EntityMeshID::Unused16, "Unused16"},
        {EntityMeshID::Unused17, "Unused17"},
        {EntityMeshID::Unused18, "Unused18"},
        {EntityMeshID::Unused19, "Unused19"},
        {EntityMeshID::Unused2, "Unused2"},
        {EntityMeshID::Unused20, "Unused20"},
        {EntityMeshID::Unused21, "Unused21"},
        {EntityMeshID::Unused22, "Unused22"},
        {EntityMeshID::Unused23, "Unused23"},
        {EntityMeshID::Unused24, "Unused24"},
        {EntityMeshID::Unused3, "Unused3"},
        {EntityMeshID::Unused4, "Unused4"},
        {EntityMeshID::Unused5, "Unused5"},
        {EntityMeshID::Unused6, "Unused6"},
        {EntityMeshID::Unused7, "Unused7"},
        {EntityMeshID::Unused8, "Unused8"},
        {EntityMeshID::Unused9, "Unused9"}
    };

#if __GNUC__ >= 10
    static const std::unordered_map<const MagicID, const QString> magicIdNameMap =
#else
    static const std::map<const MagicID, const QString> magicIdNameMap =
#endif
        {
        {MagicID::ArcherArrow, "ArcherArrow"},
        {MagicID::ArcherParalyzeArrow, "ArcherParalyzeArrow"},
        {MagicID::Breath, "Breath"},
        {MagicID::DarkSlayerMagicA, "DarkSlayerMagicA"},
        {MagicID::DarkSlayerMagicB, "DarkSlayerMagicB"},
        {MagicID::Dispoison, "Dispoison"},
        {MagicID::DoubleFireball, "DoubleFireball"},
        {MagicID::EarthHeal, "EarthHeal"},
        {MagicID::EarthWave, "EarthWave"},
        {MagicID::EnemyEarthMagic, "EnemyEarthMagic"},
        {MagicID::EnemyHomingEarthMagic, "EnemyHomingEarthMagic"},
        {MagicID::EnemyLightningVolt, "EnemyLightningVolt"},
        {MagicID::FireBall, "FireBall"},
        {MagicID::FireStorm, "FireStorm"},
        {MagicID::FireWall, "FireWall"},
        {MagicID::Flame, "Flame"},
        {MagicID::FlameSwordMagicA, "FlameSwordMagicA"},
        {MagicID::FlameSwordMagicB, "FlameSwordMagicB"},
        {MagicID::Flash, "Flash"},
        {MagicID::Freeze, "Freeze"},
        {MagicID::IceBladeMagicA, "IceBladeMagicA"},
        {MagicID::IceBladeMagicB, "IceBladeMagicB"},
        {MagicID::IceStorm, "IceStorm"},
        {MagicID::Light, "Light"},
        {MagicID::LightningVolt, "LightningVolt"},
        {MagicID::Meteor, "Meteor"},
        {MagicID::MissileShield, "MissileShield"},
        {MagicID::MoonlightSwordMagicA, "MoonlightSwordMagicA"},
        {MagicID::MoonlightSwordMagicB, "MoonlightSwordMagicB"},
        {MagicID::None, "None"},
        {MagicID::PsytheCurseOrb, "PsytheCurseOrb"},
        {MagicID::ResistFire, "ResistFire"},
        {MagicID::SKnightPoisonBreath, "SKnightPoisonBreath"},
        {MagicID::Seath, "Seath"},
        {MagicID::SeathsSwordMagicA, "SeathsSwordMagicA"},
        {MagicID::ShidenMagicA, "ShidenMagicA"},
        {MagicID::ShidenMagicB, "ShidenMagicB"},
        {MagicID::SpiderSwordMagicA, "SpiderSwordMagicA"},
        {MagicID::SpiderSwordMagicB, "SpiderSwordMagicB"},
        {MagicID::Stone, "Stone"},
        {MagicID::TarnWindMagic, "TarnWindMagic"},
        {MagicID::WaterFall, "WaterFall"},
        {MagicID::WindCutter, "WindCutter"}
    };

#if __GNUC__ >= 10
    static const std::unordered_map<const ObjectID, const QString> objectIdNameMap =
#else
    static const std::map<const ObjectID, const QString> objectIdNameMap =
#endif
    {
        {ObjectID::ABrokenSword, "ABrokenSword"},
        {ObjectID::ASoldierOfVerdite, "ASoldierOfVerdite"},
        {ObjectID::ArmsA, "ArmsA"},
        {ObjectID::ArmsDemonsHands, "ArmsDemonsHands"},
        {ObjectID::ArmsIronGloves, "ArmsIronGloves"},
        {ObjectID::ArmsRuinousGloves, "ArmsRuinousGloves"},
        {ObjectID::ArmsSilverArms, "ArmsSilverArms"},
        {ObjectID::ArmsStoneHands, "ArmsStoneHands"},
        {ObjectID::Barrel, "Barrel"},
        {ObjectID::Bed, "Bed"},
        {ObjectID::BigGreyDoorLeft, "BigGreyDoorLeft"},
        {ObjectID::BigGreyDoorRight, "BigGreyDoorRight"},
        {ObjectID::BigRoughStoneDoor, "BigRoughStoneDoor"},
        {ObjectID::BigStoneDoor, "BigStoneDoor"},
        {ObjectID::BodyA, "BodyA"},
        {ObjectID::BodyBreastPlate, "BodyBreastPlate"},
        {ObjectID::BodyDarkArmor, "BodyDarkArmor"},
        {ObjectID::BodyIceArmor, "BodyIceArmor"},
        {ObjectID::BodyKnightPlate, "BodyKnightPlate"},
        {ObjectID::BodySeathsArmor, "BodySeathsArmor"},
        {ObjectID::Bones, "Bones"},
        {ObjectID::Bones2, "Bones2"},
        {ObjectID::Bucket, "Bucket"},
        {ObjectID::CeilingTorch, "CeilingTorch"},
        {ObjectID::Chair, "Chair"},
        {ObjectID::ColosseumDoor, "ColosseumDoor"},
        {ObjectID::CopperKnightStatue, "CopperKnightStatue"},
        {ObjectID::CrossFeetTable, "CrossFeetTable"},
        {ObjectID::DaytimeSkybox, "DaytimeSkybox"},
        {ObjectID::DeadCrystalMiner, "DeadCrystalMiner"},
        {ObjectID::DeadDudeRENAME_ME, "DeadDudeRENAME_ME"},
        {ObjectID::DemonLordFromMadScientistTube, "DemonLordFromMadScientistTube"},
        {ObjectID::DemonLordStatue, "DemonLordStatue"},
        {ObjectID::DragonGrass, "DragonGrass"},
        {ObjectID::DragonStoneSlot, "DragonStoneSlot"},
        {ObjectID::DrawbridgeSwitch, "DrawbridgeSwitch"},
        {ObjectID::DummyItem1, "DummyItem1"},
        {ObjectID::DummyItem2, "DummyItem2"},
        {ObjectID::DummyItem3, "DummyItem3"},
        {ObjectID::DummyItem4, "DummyItem4"},
        {ObjectID::DummyItem5, "DummyItem5"},
        {ObjectID::DummyItem6, "DummyItem6"},
        {ObjectID::DummyItem7, "DummyItem7"},
        {ObjectID::EarthElementalStatue, "EarthElementalStatue"},
        {ObjectID::ElfsGrave, "ElfsGrave"},
        {ObjectID::EquipItemAmuletOfMist, "EquipItemAmuletOfMist"},
        {ObjectID::EquipItemEarthRing, "EquipItemEarthRing"},
        {ObjectID::EquipItemLightwaveRing, "EquipItemLightwaveRing"},
        {ObjectID::EquipItemPsycprosCollar, "EquipItemPsycprosCollar"},
        {ObjectID::EquipItemScorpionsBracelet, "EquipItemScorpionsBracelet"},
        {ObjectID::EquipItemSeathsBracelet, "EquipItemSeathsBracelet"},
        {ObjectID::EquipItemSeathsTear, "EquipItemSeathsTear"},
        {ObjectID::FeetA, "FeetA"},
        {ObjectID::FeetDeathWalkers, "FeetDeathWalkers"},
        {ObjectID::FeetIronBoots, "FeetIronBoots"},
        {ObjectID::FeetLegGuarders, "FeetLegGuarders"},
        {ObjectID::FeetRuinousBoots, "FeetRuinousBoots"},
        {ObjectID::FeetSilverBoots, "FeetSilverBoots"},
        {ObjectID::GoldenThingRENAME_ME, "GoldenThingRENAME_ME"},
        {ObjectID::GreenWallFloorTrap, "GreenWallFloorTrap"},
        {ObjectID::GreenWallSecretDoor, "GreenWallSecretDoor"},
        {ObjectID::GreenWallWithSecret1, "GreenWallWithSecret1"},
        {ObjectID::GreenWallWithSecret2, "GreenWallWithSecret2"},
        {ObjectID::GreenWallWithSpikeTrap, "GreenWallWithSpikeTrap"},
        {ObjectID::Guidepost, "Guidepost"},
        {ObjectID::GuyraTeleportCube, "GuyraTeleportCube"},
        {ObjectID::HarvineCastleSign, "HarvineCastleSign"},
        {ObjectID::HarvinesCastleDoor, "HarvinesCastleDoor"},
        {ObjectID::HarvinesThrone, "HarvinesThrone"},
        {ObjectID::HeadA, "HeadA"},
        {ObjectID::HeadBloodCrown, "HeadBloodCrown"},
        {ObjectID::HeadGreatHelm, "HeadGreatHelm"},
        {ObjectID::HeadIronMask, "HeadIronMask"},
        {ObjectID::HeadKnightHelm, "HeadKnightHelm"},
        {ObjectID::HeadLightningHelm, "HeadLightningHelm"},
        {ObjectID::HeadSeathsHelm, "HeadSeathsHelm"},
        {ObjectID::InvisibleObject, "InvisibleObject"},
        {ObjectID::ItemAHerb, "ItemAHerb"},
        {ObjectID::ItemAHerb2, "ItemAHerb2"},
        {ObjectID::ItemAPotion, "ItemAPotion"},
        {ObjectID::ItemARing, "ItemARing"},
        {ObjectID::ItemAntidote, "ItemAntidote"},
        {ObjectID::ItemArrowForTheBow, "ItemArrowForTheBow"},
        {ObjectID::ItemBloodStone, "ItemBloodStone"},
        {ObjectID::ItemBluePotion, "ItemBluePotion"},
        {ObjectID::ItemCrystal, "ItemCrystal"},
        {ObjectID::ItemCrystalFlask, "ItemCrystalFlask"},
        {ObjectID::ItemCrystalShard, "ItemCrystalShard"},
        {ObjectID::ItemDarkCrystal, "ItemDarkCrystal"},
        {ObjectID::ItemDemonsPick, "ItemDemonsPick"},
        {ObjectID::ItemDragonCrystal, "ItemDragonCrystal"},
        {ObjectID::ItemDragonStone, "ItemDragonStone"},
        {ObjectID::ItemEarthCrystal, "ItemEarthCrystal"},
        {ObjectID::ItemEarthHerb, "ItemEarthHerb"},
        {ObjectID::ItemElfsBolt, "ItemElfsBolt"},
        {ObjectID::ItemElfsKey, "ItemElfsKey"},
        {ObjectID::ItemFigureOfSeath, "ItemFigureOfSeath"},
        {ObjectID::ItemFireCrystal, "ItemFireCrystal"},
        {ObjectID::ItemGoldCoin, "ItemGoldCoin"},
        {ObjectID::ItemGoldKey, "ItemGoldKey"},
        {ObjectID::ItemGoldPotion, "ItemGoldPotion"},
        {ObjectID::ItemGreenPotion, "ItemGreenPotion"},
        {ObjectID::ItemGroundBell, "ItemGroundBell"},
        {ObjectID::ItemHarvinesFlute, "ItemHarvinesFlute"},
        {ObjectID::ItemHarvinesKey, "ItemHarvinesKey"},
        {ObjectID::ItemJailKey, "ItemJailKey"},
        {ObjectID::ItemLightCrystal, "ItemLightCrystal"},
        {ObjectID::ItemMagiciansKey, "ItemMagiciansKey"},
        {ObjectID::ItemMinersMap, "ItemMinersMap"},
        {ObjectID::ItemMoonGate, "ItemMoonGate"},
        {ObjectID::ItemMoonKey, "ItemMoonKey"},
        {ObjectID::ItemMoonStone, "ItemMoonStone"},
        {ObjectID::ItemNecronsMap, "ItemNecronsMap"},
        {ObjectID::ItemPhantomRod, "ItemPhantomRod"},
        {ObjectID::ItemPiratesKey, "ItemPiratesKey"},
        {ObjectID::ItemPiratesMap, "ItemPiratesMap"},
        {ObjectID::ItemRedPotion, "ItemRedPotion"},
        {ObjectID::ItemRhombusKey, "ItemRhombusKey"},
        {ObjectID::ItemSeathsPlume, "ItemSeathsPlume"},
        {ObjectID::ItemShrineKey, "ItemShrineKey"},
        {ObjectID::ItemSilverKey, "ItemSilverKey"},
        {ObjectID::ItemSkullKey, "ItemSkullKey"},
        {ObjectID::ItemStarGate, "ItemStarGate"},
        {ObjectID::ItemStarKey, "ItemStarKey"},
        {ObjectID::ItemSunGate, "ItemSunGate"},
        {ObjectID::ItemSunKey, "ItemSunKey"},
        {ObjectID::ItemTruthGlass, "ItemTruthGlass"},
        {ObjectID::ItemVerdite, "ItemVerdite"},
        {ObjectID::ItemWaterCrystal, "ItemWaterCrystal"},
        {ObjectID::ItemWindCrystal, "ItemWindCrystal"},
        {ObjectID::JailDoor, "JailDoor"},
        {ObjectID::KnockerDoorLeft, "KnockerDoorLeft"},
        {ObjectID::KnockerDoorRight, "KnockerDoorRight"},
        {ObjectID::Lantern, "Lantern"},
        {ObjectID::LoadArea, "LoadArea"},
        {ObjectID::MadScientistBox, "MadScientistBox"},
        {ObjectID::MadScientistLightCrystalMachine, "MadScientistLightCrystalMachine"},
        {ObjectID::MadScientistTube, "MadScientistTube"},
        {ObjectID::MarbleWallFloorTrap, "MarbleWallFloorTrap"},
        {ObjectID::MineSign, "MineSign"},
        {ObjectID::Minecart, "Minecart"},
        {ObjectID::MinersGraveMaybe, "MinersGraveMaybe"},
        {ObjectID::Moon, "Moon"},
        {ObjectID::MountainSkybox, "MountainSkybox"},
        {ObjectID::NighttimeSkybox, "NighttimeSkybox"},
        {ObjectID::NighttimeSkybox2, "NighttimeSkybox2"},
        {ObjectID::None, "None"},
        {ObjectID::PillarOfWind, "PillarOfWind"},
        {ObjectID::RedFlower, "RedFlower"},
        {ObjectID::RhombusKeyDoor, "RhombusKeyDoor"},
        {ObjectID::RhombusKeySlot, "RhombusKeySlot"},
        {ObjectID::SamuraisGrave, "SamuraisGrave"},
        {ObjectID::Savepoint, "Savepoint"},
        {ObjectID::SeathsFountainDoorLeft, "SeathsFountainDoorLeft"},
        {ObjectID::SeathsFountainDoorRight, "SeathsFountainDoorRight"},
        {ObjectID::SeathsFountainPillar, "SeathsFountainPillar"},
        {ObjectID::SecretDoor, "SecretDoor"},
        {ObjectID::Shelf, "Shelf"},
        {ObjectID::ShieldA, "ShieldA"},
        {ObjectID::ShieldCrystalGuard, "ShieldCrystalGuard"},
        {ObjectID::ShieldLargeShield, "ShieldLargeShield"},
        {ObjectID::ShieldLeatherShield, "ShieldLeatherShield"},
        {ObjectID::ShieldMoonGuard, "ShieldMoonGuard"},
        {ObjectID::ShieldSeathsShield, "ShieldSeathsShield"},
        {ObjectID::ShieldSkullShield, "ShieldSkullShield"},
        {ObjectID::ShovelAndHammer, "ShovelAndHammer"},
        {ObjectID::ShrineKeySlot, "ShrineKeySlot"},
        {ObjectID::Sign, "Sign"},
        {ObjectID::SimpleStoolMaybeRENAME_ME, "SimpleStoolMaybeRENAME_ME"},
        {ObjectID::SkullKeySlot, "SkullKeySlot"},
        {ObjectID::SkullKeyWaterObstacle, "SkullKeyWaterObstacle"},
        {ObjectID::SlotForSomethingRENAME_ME, "SlotForSomethingRENAME_ME"},
        {ObjectID::SmallBed, "SmallBed"},
        {ObjectID::SmallStackOfLogs, "SmallStackOfLogs"},
        {ObjectID::SmallTable, "SmallTable"},
        {ObjectID::SmallWeirdPillarRENAME_ME, "SmallWeirdPillarRENAME_ME"},
        {ObjectID::SomeBrokenGrave, "SomeBrokenGrave"},
        {ObjectID::SomeBrokenGrave2, "SomeBrokenGrave2"},
        {ObjectID::SomeDoorHandleRENAME_ME, "SomeDoorHandleRENAME_ME"},
        {ObjectID::SomeGrave, "SomeGrave"},
        {ObjectID::SquareWell, "SquareWell"},
        {ObjectID::StoneChestBody, "StoneChestBody"},
        {ObjectID::StoneChestLid, "StoneChestLid"},
        {ObjectID::StoneGobletWithLavaRENAME_ME, "StoneGobletWithLavaRENAME_ME"},
        {ObjectID::StonePillar, "StonePillar"},
        {ObjectID::StoneThing2RENAME_ME, "StoneThing2RENAME_ME"},
        {ObjectID::StoneThing3RENAME_ME, "StoneThing3RENAME_ME"},
        {ObjectID::StoneThingRENAME_ME, "StoneThingRENAME_ME"},
        {ObjectID::Stool, "Stool"},
        {ObjectID::SwingingScythe, "SwingingScythe"},
        {ObjectID::SwingingSpikeBall, "SwingingSpikeBall"},
        {ObjectID::TableWithThingie, "TableWithThingie"},
        {ObjectID::TarnStatue, "TarnStatue"},
        {ObjectID::TheMagiciansLamp, "TheMagiciansLamp"},
        {ObjectID::TheSoldiersGrave, "TheSoldiersGrave"},
        {ObjectID::ThreeStones, "ThreeStones"},
        {ObjectID::TinyXFeetTable, "TinyXFeetTable"},
        {ObjectID::Tree, "Tree"},
        {ObjectID::WHATTHEFUCKStatue, "WHATTHEFUCKStatue"},
        {ObjectID::WTF, "WTF"},
        {ObjectID::WallTorch, "WallTorch"},
        {ObjectID::WallWithSecret, "WallWithSecret"},
        {ObjectID::WallWithSecret2, "WallWithSecret2"},
        {ObjectID::WallWithSpikeTrap, "WallWithSpikeTrap"},
        {ObjectID::WallWriting, "WallWriting"},
        {ObjectID::WallWriting2, "WallWriting2"},
        {ObjectID::WallWriting3, "WallWriting3"},
        {ObjectID::WaterWell, "WaterWell"},
        {ObjectID::WeaponA1, "WeaponA1"},
        {ObjectID::WeaponA2, "WeaponA2"},
        {ObjectID::WeaponA3, "WeaponA3"},
        {ObjectID::WeaponA4, "WeaponA4"},
        {ObjectID::WeaponA5, "WeaponA5"},
        {ObjectID::WeaponArbalest, "WeaponArbalest"},
        {ObjectID::WeaponBastardSword, "WeaponBastardSword"},
        {ObjectID::WeaponBattleHammer, "WeaponBattleHammer"},
        {ObjectID::WeaponBow, "WeaponBow"},
        {ObjectID::WeaponCrescentAxe, "WeaponCrescentAxe"},
        {ObjectID::WeaponDagger, "WeaponDagger"},
        {ObjectID::WeaponDarkSlayer, "WeaponDarkSlayer"},
        {ObjectID::WeaponFlameSword, "WeaponFlameSword"},
        {ObjectID::WeaponIceBlade, "WeaponIceBlade"},
        {ObjectID::WeaponKnightSword, "WeaponKnightSword"},
        {ObjectID::WeaponMoonlightSword, "WeaponMoonlightSword"},
        {ObjectID::WeaponMorningStar, "WeaponMorningStar"},
        {ObjectID::WeaponSeathsSword, "WeaponSeathsSword"},
        {ObjectID::WeaponShiden, "WeaponShiden"},
        {ObjectID::WeaponShortSword, "WeaponShortSword"},
        {ObjectID::WeaponSpider, "WeaponSpider"},
        {ObjectID::WeirdPillarRENAME_ME, "WeirdPillarRENAME_ME"},
        {ObjectID::WhitePinkFlower, "WhitePinkFlower"},
        {ObjectID::WoodenChestBody, "WoodenChestBody"},
        {ObjectID::WoodenChestLid, "WoodenChestLid"},
        {ObjectID::WoodenThingRENAME_ME, "WoodenThingRENAME_ME"},
        {ObjectID::XFeetTable, "XFeetTable"}
    };

    // Functions

    static const QString &getEntityMeshName(EntityMeshID entityMeshId)
    {
        if (entityMeshIdNameMap.count(entityMeshId) == 1)
            return entityMeshIdNameMap.at(entityMeshId);

        return entityMeshIdNameMap.at(EntityMeshID::None);
    }

    static EntityMeshID getEntityMeshIDFromByte(byte meshId)
    {
        return static_cast<EntityMeshID>(meshId);
    }

    static byte getEntityMeshIDAsByte(EntityMeshID entityMeshId)
    {
        return static_cast<byte>(entityMeshId);
    }

    static const QString &getMagicIDName(MagicID magicId)
    {
        if (magicIdNameMap.count(magicId) == 1)
            return magicIdNameMap.at(magicId);

        return magicIdNameMap.at(MagicID::None);
    }

    static MagicID getMagicIDFromByte(byte magicId)
    {
        return static_cast<MagicID>(magicId);
    }

    static byte getMagicIDAsByte(MagicID magicId)
    {
        return static_cast<byte>(magicId);
    }

    static const QString &getObjectName(ObjectID itemId)
    {
        if (objectIdNameMap.count(itemId) == 1)
            return objectIdNameMap.at(itemId);

        return objectIdNameMap.at(ObjectID::None);
    }

    static ObjectID getObjectIDFromByte(byte objectId)
    {
        return static_cast<ObjectID>(objectId);
    }

    static ObjectID getObjectIDFromUShort(unsigned short objectId)
    {
        return static_cast<ObjectID>(objectId);
    }

    static byte getObjectIDAsByte(ObjectID objectId)
    {
        return static_cast<byte>(objectId);
    }

    static unsigned short getObjectIDAsUShort(ObjectID objectId)
    {
        return static_cast<unsigned short>(objectId);
    }

    static const QString getWeaponStatsName(byte weaponStatsIndex)
    {
        switch(weaponStatsIndex)
        {
            case 0: return "Dagger";
            case 1: return "Short Sword";
            case 2: return "Knight Sword";
            case 3: return "Morning Star";
            case 4: return "Battle Hammer";
            case 5: return "Bastard Sword";
            case 6: return "Crescent Axe";
            case 7: return "A";
            case 8: return "A";
            case 9: return "Flame Sword";
            case 10: return "Shiden";
            case 11: return "Spider";
            case 12: return "Ice Blade";
            case 13: return "Seath's Sword";
            case 14: return "Moonlight Sword";
            case 15: return "Dark Slayer";
            case 16: return "Bow";
            case 17: return "Arbalest";
            default: return "ERROR";
        }
    }

    // Structs

    /*!
     * \brief Structure for the entity declarations at the beginning of each map file.
     */
    struct EntityClassDeclaration {
        EntityMeshID MeshID;
        byte FourOrForty;
        undefined field_0x2;
        undefined field_0x3;
        undefined field_0x4;
        undefined field_0x5;
        undefined field_0x6;
        byte Unknown_x07;
        byte Unknown_x08;
        undefined field_0x9;
        byte SpawnDistance;
        byte DespawnDistance;
        undefined field_0xc;
        undefined field_0xd;
        undefined field_0xe;
        undefined field_0xf;
        undefined field_0x10;
        undefined field_0x11;
        u_short Unknown_x12;
        u_short Unknown_x14;
        undefined field_0x16;
        undefined field_0x17;
        undefined field_0x18;
        undefined field_0x19;
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

        friend QDataStream &operator>>(QDataStream &in, EntityClassDeclaration &classDecl)
        {
            quint8 tempByte;
            in >> tempByte;
            classDecl.MeshID = KingsField::getEntityMeshIDFromByte(tempByte);
            in >> classDecl.FourOrForty;
            in >> classDecl.field_0x2;
            in >> classDecl.field_0x3;
            in >> classDecl.field_0x4;
            in >> classDecl.field_0x5;
            in >> classDecl.field_0x6;
            in >> classDecl.Unknown_x07;
            in >> classDecl.Unknown_x08;
            in >> classDecl.field_0x9;
            in >> classDecl.SpawnDistance;
            in >> classDecl.DespawnDistance;
            in >> classDecl.field_0xc;
            in >> classDecl.field_0xd;
            in >> classDecl.field_0xe;
            in >> classDecl.field_0xf;
            in >> classDecl.field_0x10;
            in >> classDecl.field_0x11;
            in >> classDecl.Unknown_x12;
            in >> classDecl.Unknown_x14;
            in >> classDecl.field_0x16;
            in >> classDecl.field_0x17;
            in >> classDecl.field_0x18;
            in >> classDecl.field_0x19;
            in >> classDecl.HP;
            in >> classDecl.Unknown_x1c;
            in >> classDecl.ExperienceGain;
            in >> classDecl.DefSlash;
            in >> classDecl.DefChop;
            in >> classDecl.DefStab;
            in >> classDecl.DefHolyMagic;
            in >> classDecl.DefFireMagic;
            in >> classDecl.DefEarthMagic;
            in >> classDecl.DefWindMagic;
            in >> classDecl.DefWaterMagic;
            in >> classDecl.GoldSomething;
            in >> classDecl.Scale;
            in >> classDecl.UknBitField34;
            for (size_t i = 0; i < 16; i++)
                in >> classDecl.SomePointers[i];

            return in;
        }

        friend QDataStream &operator<<(QDataStream &out, const EntityClassDeclaration &classDecl)
        {
            out << KingsField::getEntityMeshIDAsByte(classDecl.MeshID);
            out << classDecl.FourOrForty;
            out << classDecl.field_0x2;
            out << classDecl.field_0x3;
            out << classDecl.field_0x4;
            out << classDecl.field_0x5;
            out << classDecl.field_0x6;
            out << classDecl.Unknown_x07;
            out << classDecl.Unknown_x08;
            out << classDecl.field_0x9;
            out << classDecl.SpawnDistance;
            out << classDecl.DespawnDistance;
            out << classDecl.field_0xc;
            out << classDecl.field_0xd;
            out << classDecl.field_0xe;
            out << classDecl.field_0xf;
            out << classDecl.field_0x10;
            out << classDecl.field_0x11;
            out << classDecl.Unknown_x12;
            out << classDecl.Unknown_x14;
            out << classDecl.field_0x16;
            out << classDecl.field_0x17;
            out << classDecl.field_0x18;
            out << classDecl.field_0x19;
            out << classDecl.HP;
            out << classDecl.Unknown_x1c;
            out << classDecl.ExperienceGain;
            out << classDecl.DefSlash;
            out << classDecl.DefChop;
            out << classDecl.DefStab;
            out << classDecl.DefHolyMagic;
            out << classDecl.DefFireMagic;
            out << classDecl.DefEarthMagic;
            out << classDecl.DefWindMagic;
            out << classDecl.DefWaterMagic;
            out << classDecl.GoldSomething;
            out << classDecl.Scale;
            out << classDecl.UknBitField34;
            for (size_t i = 0; i < 16; i++)
                out << classDecl.SomePointers[i];

            return out;
        }
    };

    /*!
     * \brief Structure for declarations of entity instances in the map files.
     */
    struct EntityInstance {
        byte RespawnMode;
        byte EntityClass;
        bool NonRandomRotation;
        byte WEXTilePos;
        byte NSYTilePos;
        byte RespawnChance;
        ObjectID DroppedItem;
        byte Layer;
        u_short ZRotation;
        short FineWEXPos;
        short FineNSYPos;
        short FineZPos;

        friend QDataStream &operator>>(QDataStream &in, EntityInstance &instance)
        {
            quint8 tempByte;
            in >> instance.RespawnMode;
            in >> instance.EntityClass;
            in >> instance.NonRandomRotation;
            in >> instance.WEXTilePos;
            in >> instance.NSYTilePos;
            in >> instance.RespawnChance;
            in >> tempByte;
            instance.DroppedItem = KingsField::getObjectIDFromByte(tempByte);
            in >> instance.Layer;
            in >> instance.ZRotation;
            in >> instance.FineWEXPos;
            in >> instance.FineNSYPos;
            in >> instance.FineZPos;
            return in;
        }

        friend QDataStream &operator<< (QDataStream &out, const EntityInstance &instance)
        {
            out << instance.RespawnMode;
            out << instance.EntityClass;
            out << instance.NonRandomRotation;
            out << instance.WEXTilePos;
            out << instance.NSYTilePos;
            out << instance.RespawnChance;
            out << getObjectIDAsByte(instance.DroppedItem);
            out << instance.Layer;
            out << instance.ZRotation;
            out << instance.FineWEXPos;
            out << instance.FineNSYPos;
            out << instance.FineZPos;

            return out;
        }
    };

    /*!
     * \brief Structure for the definition of magic spells.
     */
    struct Magic {
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

        friend QDataStream &operator>> (QDataStream &in, Magic& magic)
        {
            in >> magic.PlayerHas;
            in >> magic.ChargeRecoveryTime;
            in >> magic.field_0x2;
            in >> magic.field_0x3;
            in >> magic.StatusEffect;
            in >> magic.field_0x5;
            in >> magic.field_0x6;
            in >> magic.field_0x7;
            in >> magic.SomeDmg1;
            in >> magic.SomeDmg2;
            in >> magic.SomeDmg3;
            in >> magic.FireDmg;
            in >> magic.EarthDmg;
            in >> magic.WindDmg;
            in >> magic.WaterDmg;
            in >> magic.MPCost;
            in >> magic.field_0x18;
            in >> magic.field_0x19;

            return in;
        }

        friend QDataStream &operator<< (QDataStream &out, const Magic& magic)
        {
            out << magic.PlayerHas;
            out << magic.ChargeRecoveryTime;
            out << magic.field_0x2;
            out << magic.field_0x3;
            out << magic.StatusEffect;
            out << magic.field_0x5;
            out << magic.field_0x6;
            out << magic.field_0x7;
            out << magic.SomeDmg1;
            out << magic.SomeDmg2;
            out << magic.SomeDmg3;
            out << magic.FireDmg;
            out << magic.EarthDmg;
            out << magic.WindDmg;
            out << magic.WaterDmg;
            out << magic.MPCost;
            out << magic.field_0x18;
            out << magic.field_0x19;

            return out;
        }
    };

    /*!
     * \brief Structure for the object declarations at the database.
     */
    struct ObjectClassDeclaration {
        undefined field_0x0;
        byte SomeType;
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

        friend QDataStream &operator>>(QDataStream &in, ObjectClassDeclaration &objClassDecl)
        {
            in >> objClassDecl.field_0x0;
            in >> objClassDecl.SomeType;
            in >> objClassDecl.field_0x2;
            in >> objClassDecl.field_0x3;
            in >> objClassDecl.CollisionRadius;
            in >> objClassDecl.field_0x6;
            in >> objClassDecl.field_0x7;
            in >> objClassDecl.field_0x8;
            in >> objClassDecl.field_0x9;
            in >> objClassDecl.field_0xa;
            in >> objClassDecl.field_0xb;
            in >> objClassDecl.field_0xc;
            in >> objClassDecl.field_0xd;
            in >> objClassDecl.field_0xe;
            in >> objClassDecl.field_0xf;
            in >> objClassDecl.field_0x10;
            in >> objClassDecl.field_0x11;
            in >> objClassDecl.field_0x12;
            in >> objClassDecl.field_0x13;
            in >> objClassDecl.field_0x14;
            in >> objClassDecl.field_0x15;
            in >> objClassDecl.field_0x16;
            in >> objClassDecl.field_0x17;
            return in;
        }

        friend QDataStream &operator<<(QDataStream &out, const ObjectClassDeclaration &objClassDecl)
        {
            out << objClassDecl.field_0x0;
            out << objClassDecl.SomeType;
            out << objClassDecl.field_0x2;
            out << objClassDecl.field_0x3;
            out << objClassDecl.CollisionRadius;
            out << objClassDecl.field_0x6;
            out << objClassDecl.field_0x7;
            out << objClassDecl.field_0x8;
            out << objClassDecl.field_0x9;
            out << objClassDecl.field_0xa;
            out << objClassDecl.field_0xb;
            out << objClassDecl.field_0xc;
            out << objClassDecl.field_0xd;
            out << objClassDecl.field_0xe;
            out << objClassDecl.field_0xf;
            out << objClassDecl.field_0x10;
            out << objClassDecl.field_0x11;
            out << objClassDecl.field_0x12;
            out << objClassDecl.field_0x13;
            out << objClassDecl.field_0x14;
            out << objClassDecl.field_0x15;
            out << objClassDecl.field_0x16;
            out << objClassDecl.field_0x17;
            return out;
        }

    };

    /*!
     * \brief Structure for declarations of object instances in the map files.
     */
    struct ObjectInstanceDeclaration {
        byte TileLayer;
        byte WEXTilePos;
        byte NSYTilePos;
        undefined field_0x3;
        enum ObjectID ObjectID;
        u_short ZRotation;
        short FineWEXPos;
        short FineNSYPos;
        short FineZPos;
        byte Flags[10];

        friend QDataStream &operator>>(QDataStream &in, ObjectInstanceDeclaration &objInstance)
        {
            quint16 tempUShort;
            in >> objInstance.TileLayer;
            in >> objInstance.WEXTilePos;
            in >> objInstance.NSYTilePos;
            in >> objInstance.field_0x3;
            in >> tempUShort;
            objInstance.ObjectID = getObjectIDFromUShort(tempUShort);
            in >> objInstance.ZRotation;
            in >> objInstance.FineWEXPos;
            in >> objInstance.FineNSYPos;
            in >> objInstance.FineZPos;
            for (size_t i = 0; i < 10; i++)
                in >> objInstance.Flags[i];

            return in;
        }

        friend QDataStream &operator<<(QDataStream &out, const ObjectInstanceDeclaration &objInstance)
        {
            out << objInstance.TileLayer;
            out << objInstance.WEXTilePos;
            out << objInstance.NSYTilePos;
            out << objInstance.field_0x3;
            out << getObjectIDAsUShort(objInstance.ObjectID);
            out << objInstance.ZRotation;
            out << objInstance.FineWEXPos;
            out << objInstance.FineNSYPos;
            out << objInstance.FineZPos;
            for (size_t i = 0; i < 10; i++)
                out << objInstance.Flags[i];

            return out;
        }
    };

    /*!
     * \brief Holds HP, MP, Str and Magic Power Differences and Experience for the next level for each level the player can achieve.
     */
    struct PlayerLvlData {
        quint16 BaseHP;
        quint16 BaseMP;
        quint16 StrPowerPlus;
        quint16 MagPowerPlus;
        quint32 ExpForNextLevel;

        friend QDataStream &operator>> (QDataStream &in, PlayerLvlData &playerLvlData)
        {
            in >> playerLvlData.BaseHP;
            in >> playerLvlData.BaseMP;
            in >> playerLvlData.StrPowerPlus;
            in >> playerLvlData.MagPowerPlus;
            in >> playerLvlData.ExpForNextLevel;

            return in;
        }

        friend QDataStream &operator<< (QDataStream &out, const PlayerLvlData &playerLvlData)
        {
            out << playerLvlData.BaseHP;
            out << playerLvlData.BaseMP;
            out << playerLvlData.StrPowerPlus;
            out << playerLvlData.MagPowerPlus;
            out << playerLvlData.ExpForNextLevel;

            return out;
        }
    };

    /*!
     * \brief Standard PS1 short vector structure.
     */
    struct SVECTOR {
        short vx;
        short vy;
        short vz;
        short pad;

        friend QDataStream &operator>> (QDataStream &in, SVECTOR& sVec)
        {
            in >> sVec.vx;
            in >> sVec.vy;
            in >> sVec.vz;
            in >> sVec.pad;
            return in;
        }

        friend QDataStream &operator<< (QDataStream &out, const SVECTOR &sVec)
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
    struct Tile {
        byte Layer1TileID;
        byte Layer1Elev;
        byte Layer1Rotation; ///< 0-3, each step is 90°
        byte Layer1CollisionSomething; ///< Draw this to a texture to get something interesting
        byte Layer1ZoneDelimiter; ///< Draw this to a texture to get something interesting
        byte Layer2TileID;
        byte Layer2Elev;
        byte Layer2Rotation; ///< 0-3, each step is 90°
        byte Layer2CollisionSomething; ///< Draw this to a texture to get something interesting
        byte Layer2ZoneDelimiter; ///< Draw this to a texture to get something interesting

        friend QDataStream &operator>> (QDataStream &in, Tile &tile)
        {
            in >> tile.Layer1TileID;
            in >> tile.Layer1Elev;
            in >> tile.Layer1Rotation;
            in >> tile.Layer1CollisionSomething;
            in >> tile.Layer1ZoneDelimiter;
            in >> tile.Layer2TileID;
            in >> tile.Layer2Elev;
            in >> tile.Layer2Rotation;
            in >> tile.Layer2CollisionSomething;
            in >> tile.Layer2ZoneDelimiter;

            return in;
        }

        friend QDataStream &operator<< (QDataStream &out, const Tile &tile)
        {
            out << tile.Layer1TileID;
            out << tile.Layer1Elev;
            out << tile.Layer1Rotation;
            out << tile.Layer1CollisionSomething;
            out << tile.Layer1ZoneDelimiter;
            out << tile.Layer2TileID;
            out << tile.Layer2Elev;
            out << tile.Layer2Rotation;
            out << tile.Layer2CollisionSomething;
            out << tile.Layer2ZoneDelimiter;

            return out;
        }
    };

    /*!
     * \brief Stats structure for weapons.
     */
    struct WeaponStats {
        byte Unknown_x00;
        byte Unknown_x01;
        byte Unknown_x02;
        MagicID Spell1;
        MagicID Spell2;
        byte Unknown_x05;
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
        short Unknown_x1a;
        u_short Unknown_x1c;
        u_short Unknown_x1e;
        u_short Unknown_x20;
        u_short Unknown_x22;
        short Unknown_x24;
        u_short Unknown_x26;
        u_short Unknown_x28;
        u_short Unknown_x2a;
        u_short Unknown_x2c;
        u_short Unknown_x2e;
        u_short Unknown_x30;
        short Unknown_x32;
        struct SVECTOR Position;
        struct SVECTOR SomeVec;

        friend QDataStream &operator>> (QDataStream &in, WeaponStats& weaponStat)
        {
            quint8 tempByte;
            in >> weaponStat.Unknown_x00;
            in >> weaponStat.Unknown_x01;
            in >> weaponStat.Unknown_x02;
            in >> tempByte;
            weaponStat.Spell1 = KingsField::getMagicIDFromByte(tempByte);
            in >> tempByte;
            weaponStat.Spell2 = KingsField::getMagicIDFromByte(tempByte);
            in >> weaponStat.Unknown_x05;
            in >> weaponStat.OffSlash;
            in >> weaponStat.OffChop;
            in >> weaponStat.OffStab;
            in >> weaponStat.OffHolyM;
            in >> weaponStat.OffFireM;
            in >> weaponStat.OffEarthM;
            in >> weaponStat.OffWindM;
            in >> weaponStat.OffWaterM;
            in >> weaponStat.HPRestoreTimer;
            in >> weaponStat.MPRestoreTimer;
            in >> weaponStat.Unknown_x1a;
            in >> weaponStat.Unknown_x1c;
            in >> weaponStat.Unknown_x1e;
            in >> weaponStat.Unknown_x20;
            in >> weaponStat.Unknown_x22;
            in >> weaponStat.Unknown_x24;
            in >> weaponStat.Unknown_x26;
            in >> weaponStat.Unknown_x28;
            in >> weaponStat.Unknown_x2a;
            in >> weaponStat.Unknown_x2c;
            in >> weaponStat.Unknown_x2e;
            in >> weaponStat.Unknown_x30;
            in >> weaponStat.Unknown_x32;
            in >> weaponStat.Position;
            in >> weaponStat.SomeVec;

            return in;
        }

        friend QDataStream &operator<< (QDataStream &out, const WeaponStats& weaponStat)
        {
            out << weaponStat.Unknown_x00;
            out << weaponStat.Unknown_x01;
            out << weaponStat.Unknown_x02;
            out << KingsField::getMagicIDAsByte(weaponStat.Spell1);
            out << KingsField::getMagicIDAsByte(weaponStat.Spell2);
            out << weaponStat.Unknown_x05;
            out << weaponStat.OffSlash;
            out << weaponStat.OffChop;
            out << weaponStat.OffStab;
            out << weaponStat.OffHolyM;
            out << weaponStat.OffFireM;
            out << weaponStat.OffEarthM;
            out << weaponStat.OffWindM;
            out << weaponStat.OffWaterM;
            out << weaponStat.HPRestoreTimer;
            out << weaponStat.MPRestoreTimer;
            out << weaponStat.Unknown_x1a;
            out << weaponStat.Unknown_x1c;
            out << weaponStat.Unknown_x1e;
            out << weaponStat.Unknown_x20;
            out << weaponStat.Unknown_x22;
            out << weaponStat.Unknown_x24;
            out << weaponStat.Unknown_x26;
            out << weaponStat.Unknown_x28;
            out << weaponStat.Unknown_x2a;
            out << weaponStat.Unknown_x2c;
            out << weaponStat.Unknown_x2e;
            out << weaponStat.Unknown_x30;
            out << weaponStat.Unknown_x32;
            out << weaponStat.Position;
            out << weaponStat.SomeVec;

            return out;
        }
    };

    // Constants

    /*!
     * \brief Rotation coefficient used for converting PS1 format angles from/to degrees.
     * To get PS1 format angles from degrees, divide the angle in degrees by the coefficient.
     * To get degrees from PS1 format angles, multiplye the angle in PS1 format by the coffiecient.
     */
    constexpr static const double rotationCoefficient = 360.0 / 4096.0;
}


#endif // KFTYPES_H
