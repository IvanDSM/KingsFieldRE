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
#ifdef __GNUC__
#ifdef __MINGW32__
typedef quint16 u_short;
typedef quint32 u_int;
#endif
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
        Breath=19,
        Dispoison=14,
        EarthHeal=16,
        EarthWave=2,
        FireBall=7,
        FireStorm=9,
        FireWall=8,
        Flame=10,
        Flash=12,
        Freeze=6,
        IceStorm=5,
        Light=18,
        LightningVolt=11,
        Meteor=3,
        MissileShield=17,
        None=255,
        ResistFire=15,
        Seath=13,
        Stone=1,
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
        BigWallTileRENAME_ME=203,
        BodyA=33,
        BodyBreastPlate=28,
        BodyDarkArmor=31,
        BodyIceArmor=30,
        BodyKnightPlate=29,
        BodySeathsArmor=32,
        Bones2=144,
        Bones=143,
        Bucket=180,
        CeilingTorch=280,
        Chair=259,
        ColosseumDoor=140,
        CopperKnightStatue=169,
        CrossFeetTable=256,
        DaytimeSkybox=245,
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
        GreenWallCrossRENAME_ME=205,
        GreenWallTrapdoorMaybe=206,
        GreenWallWithSecret=214,
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
        ItemAHerb2=119,
        ItemAHerb=110,
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
        MineSign=165,
        Minecart=177,
        MinersGraveMaybe=151,
        Moon=248,
        NighttimeSkybox2=249,
        NighttimeSkybox=247,
        None=255,
        PillarOfWind=157,
        RedFlower=287,
        RhombusKeyDoor=139,
        RhombusKeySlot=184,
        SamuraisGrave=149,
        Savepoint=230,
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
        SmallTable=136,
        SmallWeirdPillarRENAME_ME=274,
        SomeBrokenGrave2=156,
        SomeBrokenGrave=155,
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
        WallWithSecret=138,
        WallWithSpikeTrap=202,
        WallWriting2=161,
        WallWriting3=162,
        WallWriting=160,
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
        WeirdAsFuckObjectTile=131,
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
            {MagicID::Breath, "Breath"},
            {MagicID::Dispoison, "Dispoison"},
            {MagicID::EarthHeal, "Earth Heal"},
            {MagicID::EarthWave, "Earth Wave"},
            {MagicID::FireBall, "Fire Ball"},
            {MagicID::FireStorm, "Fire Storm"},
            {MagicID::FireWall, "Fire Wall"},
            {MagicID::Flame, "Flame"},
            {MagicID::Flash, "Flash"},
            {MagicID::Freeze, "Freeze"},
            {MagicID::IceStorm, "Ice Storm"},
            {MagicID::Light, "Light"},
            {MagicID::LightningVolt, "Lightning Volt"},
            {MagicID::Meteor, "Meteor"},
            {MagicID::MissileShield, "Missile Shield"},
            {MagicID::None, "None"},
            {MagicID::ResistFire, "Resist Fire"},
            {MagicID::Seath, "Seath"},
            {MagicID::Stone, "Stone"},
            {MagicID::WaterFall, "Water Fall"},
            {MagicID::WindCutter, "Wind Cutter"}
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
        {ObjectID::BigWallTileRENAME_ME, "BigWallTileRENAME_ME"},
        {ObjectID::BodyA, "BodyA"},
        {ObjectID::BodyBreastPlate, "BodyBreastPlate"},
        {ObjectID::BodyDarkArmor, "BodyDarkArmor"},
        {ObjectID::BodyIceArmor, "BodyIceArmor"},
        {ObjectID::BodyKnightPlate, "BodyKnightPlate"},
        {ObjectID::BodySeathsArmor, "BodySeathsArmor"},
        {ObjectID::Bones2, "Bones2"},
        {ObjectID::Bones, "Bones"},
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
        {ObjectID::GreenWallCrossRENAME_ME, "GreenWallCrossRENAME_ME"},
        {ObjectID::GreenWallTrapdoorMaybe, "GreenWallTrapdoorMaybe"},
        {ObjectID::GreenWallWithSecret, "GreenWallWithSecret"},
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
        {ObjectID::ItemAHerb2, "ItemAHerb2"},
        {ObjectID::ItemAHerb, "ItemAHerb"},
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
        {ObjectID::MineSign, "MineSign"},
        {ObjectID::Minecart, "Minecart"},
        {ObjectID::MinersGraveMaybe, "MinersGraveMaybe"},
        {ObjectID::Moon, "Moon"},
        {ObjectID::NighttimeSkybox2, "NighttimeSkybox2"},
        {ObjectID::NighttimeSkybox, "NighttimeSkybox"},
        {ObjectID::None, "None"},
        {ObjectID::PillarOfWind, "PillarOfWind"},
        {ObjectID::RedFlower, "RedFlower"},
        {ObjectID::RhombusKeyDoor, "RhombusKeyDoor"},
        {ObjectID::RhombusKeySlot, "RhombusKeySlot"},
        {ObjectID::SamuraisGrave, "SamuraisGrave"},
        {ObjectID::Savepoint, "Savepoint"},
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
        {ObjectID::SmallTable, "SmallTable"},
        {ObjectID::SmallWeirdPillarRENAME_ME, "SmallWeirdPillarRENAME_ME"},
        {ObjectID::SomeBrokenGrave2, "SomeBrokenGrave2"},
        {ObjectID::SomeBrokenGrave, "SomeBrokenGrave"},
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
        {ObjectID::WallWithSpikeTrap, "WallWithSpikeTrap"},
        {ObjectID::WallWriting2, "WallWriting2"},
        {ObjectID::WallWriting3, "WallWriting3"},
        {ObjectID::WallWriting, "WallWriting"},
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
        {ObjectID::WeirdAsFuckObjectTile, "WeirdAsFuckObjectTile"},
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

    // Structs

    /*!
     * \brief Structure for the entity declarations at the beginning of each map file.
     */
    struct EntityClassDeclaration {
        enum EntityMeshID MeshID;
        byte FourOrForty;
        undefined field_0x2;
        undefined field_0x3;
        undefined field_0x4;
        undefined field_0x5;
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
        undefined field_0x18;
        undefined field_0x19;
        u_short HP;
        undefined field_0x1c;
        undefined field_0x1d;
        u_short ExperienceGain;
        u_short DefSlash;
        u_short DefChop;
        u_short DefStab;
        u_short DefHolyMagic;
        u_short DefFireMagic;
        u_short DefEarthMagic;
        u_short DefWindMagic;
        u_short DefWaterMagic;
        undefined field_0x30;
        undefined field_0x31;
        short Scale;
        undefined field_0x34;
        undefined field_0x35;
        undefined field_0x36;
        undefined field_0x37;
        u_int SomePointers[16];

        EntityClassDeclaration& operator= (const QByteArray& array)
        {
            QDataStream arrayStream(array);
            arrayStream.setByteOrder(QDataStream::LittleEndian);
            quint8 tempByte;
            arrayStream >> tempByte;
            MeshID = KingsField::getEntityMeshIDFromByte(tempByte);
            arrayStream >> FourOrForty;
            arrayStream >> field_0x2;
            arrayStream >> field_0x3;
            arrayStream >> field_0x4;
            arrayStream >> field_0x5;
            arrayStream >> field_0x6;
            arrayStream >> field_0x7;
            arrayStream >> field_0x8;
            arrayStream >> field_0x9;
            arrayStream >> field_0xa;
            arrayStream >> field_0xb;
            arrayStream >> field_0xc;
            arrayStream >> field_0xd;
            arrayStream >> field_0xe;
            arrayStream >> field_0xf;
            arrayStream >> field_0x10;
            arrayStream >> field_0x11;
            arrayStream >> field_0x12;
            arrayStream >> field_0x13;
            arrayStream >> field_0x14;
            arrayStream >> field_0x15;
            arrayStream >> field_0x16;
            arrayStream >> field_0x17;
            arrayStream >> field_0x18;
            arrayStream >> field_0x19;
            arrayStream >> HP;
            arrayStream >> field_0x1c;
            arrayStream >> field_0x1d;
            arrayStream >> ExperienceGain;
            arrayStream >> DefSlash;
            arrayStream >> DefChop;
            arrayStream >> DefStab;
            arrayStream >> DefHolyMagic;
            arrayStream >> DefFireMagic;
            arrayStream >> DefEarthMagic;
            arrayStream >> DefWindMagic;
            arrayStream >> DefWaterMagic;
            arrayStream >> field_0x30;
            arrayStream >> field_0x31;
            arrayStream >> Scale;
            arrayStream >> field_0x34;
            arrayStream >> field_0x35;
            arrayStream >> field_0x36;
            arrayStream >> field_0x37;
            for (size_t i = 0; i < 16; i++)
                arrayStream >> SomePointers[i];

            return *this;
        }

        operator QByteArray()
        {
            QByteArray arrayified;
            QDataStream arrayStream(&arrayified, QIODevice::ReadWrite);
            arrayStream.setByteOrder(QDataStream::LittleEndian);
            arrayStream << KingsField::getEntityMeshIDAsByte(MeshID);
            arrayStream << FourOrForty;
            arrayStream << field_0x2;
            arrayStream << field_0x3;
            arrayStream << field_0x4;
            arrayStream << field_0x5;
            arrayStream << field_0x6;
            arrayStream << field_0x7;
            arrayStream << field_0x8;
            arrayStream << field_0x9;
            arrayStream << field_0xa;
            arrayStream << field_0xb;
            arrayStream << field_0xc;
            arrayStream << field_0xd;
            arrayStream << field_0xe;
            arrayStream << field_0xf;
            arrayStream << field_0x10;
            arrayStream << field_0x11;
            arrayStream << field_0x12;
            arrayStream << field_0x13;
            arrayStream << field_0x14;
            arrayStream << field_0x15;
            arrayStream << field_0x16;
            arrayStream << field_0x17;
            arrayStream << field_0x18;
            arrayStream << field_0x19;
            arrayStream << HP;
            arrayStream << field_0x1c;
            arrayStream << field_0x1d;
            arrayStream << ExperienceGain;
            arrayStream << DefSlash;
            arrayStream << DefChop;
            arrayStream << DefStab;
            arrayStream << DefHolyMagic;
            arrayStream << DefFireMagic;
            arrayStream << DefEarthMagic;
            arrayStream << DefWindMagic;
            arrayStream << DefWaterMagic;
            arrayStream << field_0x30;
            arrayStream << field_0x31;
            arrayStream << Scale;
            arrayStream << field_0x34;
            arrayStream << field_0x35;
            arrayStream << field_0x36;
            arrayStream << field_0x37;
            for (size_t i = 0; i < 16; i++)
                arrayStream << SomePointers[i];

            return arrayified;
        }
    };

    /*!
     * \brief Structure for declarations of entity instances in the map files.
     */
    struct EntityInstance {
        undefined field_0x0;
        byte EntityClass;
        undefined field_0x2;
        byte WEXTilePos;
        byte NSYTilePos;
        undefined field_0x5;
        ObjectID DroppedItem;
        byte Layer;
        byte TriggerObject;
        byte ZRotation;
        short FineWEXPos;
        short FineNSYPos;
        short FineZPos;

        EntityInstance& operator= (const QByteArray& array)
        {
            QDataStream arrayStream(array);
            arrayStream.setByteOrder(QDataStream::LittleEndian);
            quint8 tempByte;
            arrayStream >> field_0x0;
            arrayStream >> EntityClass;
            arrayStream >> field_0x2;
            arrayStream >> WEXTilePos;
            arrayStream >> NSYTilePos;
            arrayStream >> field_0x5;
            arrayStream >> tempByte;
            DroppedItem = getObjectIDFromByte(tempByte);
            arrayStream >> Layer;
            arrayStream >> TriggerObject;
            arrayStream >> ZRotation;
            arrayStream >> FineWEXPos;
            arrayStream >> FineNSYPos;
            arrayStream >> FineZPos;

            return *this;
        }

        operator QByteArray()
        {
            QByteArray arrayified;
            QDataStream arrayStream(&arrayified, QIODevice::ReadWrite);
            arrayStream.setByteOrder(QDataStream::LittleEndian);
            arrayStream << field_0x0;
            arrayStream << EntityClass;
            arrayStream << field_0x2;
            arrayStream << WEXTilePos;
            arrayStream << NSYTilePos;
            arrayStream << field_0x5;
            arrayStream << getObjectIDAsByte(DroppedItem);
            arrayStream << Layer;
            arrayStream << TriggerObject;
            arrayStream << ZRotation;
            arrayStream << FineWEXPos;
            arrayStream << FineNSYPos;
            arrayStream << FineZPos;

            return arrayified;
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
        undefined field_0x4;
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

        Magic& operator= (const QByteArray &array)
        {
            QDataStream arrayStream(array);
            arrayStream.setByteOrder(QDataStream::LittleEndian);

            arrayStream >> PlayerHas;
            arrayStream >> ChargeRecoveryTime;
            arrayStream >> field_0x2;
            arrayStream >> field_0x3;
            arrayStream >> field_0x4;
            arrayStream >> field_0x5;
            arrayStream >> field_0x6;
            arrayStream >> field_0x7;
            arrayStream >> SomeDmg1;
            arrayStream >> SomeDmg2;
            arrayStream >> SomeDmg3;
            arrayStream >> FireDmg;
            arrayStream >> EarthDmg;
            arrayStream >> WindDmg;
            arrayStream >> WaterDmg;
            arrayStream >> MPCost;
            arrayStream >> field_0x18;
            arrayStream >> field_0x19;

            return *this;
        }

        operator QByteArray()
        {
            QByteArray arrayified;
            QDataStream arrayStream(&arrayified, QIODevice::ReadWrite);
            arrayStream.setByteOrder(QDataStream::LittleEndian);

            arrayStream << PlayerHas;
            arrayStream << ChargeRecoveryTime;
            arrayStream << field_0x2;
            arrayStream << field_0x3;
            arrayStream << field_0x4;
            arrayStream << field_0x5;
            arrayStream << field_0x6;
            arrayStream << field_0x7;
            arrayStream << SomeDmg1;
            arrayStream << SomeDmg2;
            arrayStream << SomeDmg3;
            arrayStream << FireDmg;
            arrayStream << EarthDmg;
            arrayStream << WindDmg;
            arrayStream << WaterDmg;
            arrayStream << MPCost;
            arrayStream << field_0x18;
            arrayStream << field_0x19;

            return arrayified;
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

        ObjectClassDeclaration& operator= (const QByteArray& array)
        {
            QDataStream arrayStream(array);
            arrayStream.setByteOrder(QDataStream::LittleEndian);

            arrayStream >> field_0x0;
            arrayStream >> SomeType;
            arrayStream >> field_0x2;
            arrayStream >> field_0x3;
            arrayStream >> CollisionRadius;
            arrayStream >> field_0x6;
            arrayStream >> field_0x7;
            arrayStream >> field_0x8;
            arrayStream >> field_0x9;
            arrayStream >> field_0xa;
            arrayStream >> field_0xb;
            arrayStream >> field_0xc;
            arrayStream >> field_0xd;
            arrayStream >> field_0xe;
            arrayStream >> field_0xf;
            arrayStream >> field_0x10;
            arrayStream >> field_0x11;
            arrayStream >> field_0x12;
            arrayStream >> field_0x13;
            arrayStream >> field_0x14;
            arrayStream >> field_0x15;
            arrayStream >> field_0x16;
            arrayStream >> field_0x17;

            return *this;
        }

        operator QByteArray()
        {
            QByteArray arrayified;
            QDataStream arrayStream(&arrayified, QIODevice::ReadWrite);
            arrayStream.setByteOrder(QDataStream::LittleEndian);

            arrayStream << field_0x0;
            arrayStream << SomeType;
            arrayStream << field_0x2;
            arrayStream << field_0x3;
            arrayStream << CollisionRadius;
            arrayStream << field_0x6;
            arrayStream << field_0x7;
            arrayStream << field_0x8;
            arrayStream << field_0x9;
            arrayStream << field_0xa;
            arrayStream << field_0xb;
            arrayStream << field_0xc;
            arrayStream << field_0xd;
            arrayStream << field_0xe;
            arrayStream << field_0xf;
            arrayStream << field_0x10;
            arrayStream << field_0x11;
            arrayStream << field_0x12;
            arrayStream << field_0x13;
            arrayStream << field_0x14;
            arrayStream << field_0x15;
            arrayStream << field_0x16;
            arrayStream << field_0x17;

            return arrayified;
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
        undefined field_0x6;
        undefined field_0x7;
        undefined field_0x8;
        undefined field_0x9;
        undefined field_0xa;
        undefined field_0xb;
        undefined field_0xc;
        undefined field_0xd;
        byte Flags[10];

        ObjectInstanceDeclaration& operator= (const QByteArray& array)
        {
            QDataStream arrayStream(array);
            arrayStream.setByteOrder(QDataStream::LittleEndian);
            quint16 tempUShort;
            arrayStream >> TileLayer;
            arrayStream >> WEXTilePos;
            arrayStream >> NSYTilePos;
            arrayStream >> field_0x3;
            arrayStream >> tempUShort;
            ObjectID = getObjectIDFromUShort(tempUShort);
            arrayStream >> field_0x6;
            arrayStream >> field_0x7;
            arrayStream >> field_0x8;
            arrayStream >> field_0x9;
            arrayStream >> field_0xa;
            arrayStream >> field_0xb;
            arrayStream >> field_0xc;
            arrayStream >> field_0xd;
            for (size_t i = 0; i < 10; i++)
                arrayStream >> Flags[i];

            return *this;
        }

        operator QByteArray()
        {
            QByteArray arrayified;
            QDataStream arrayStream(&arrayified, QIODevice::ReadWrite);
            arrayStream.setByteOrder(QDataStream::LittleEndian);
            arrayStream << TileLayer;
            arrayStream << WEXTilePos;
            arrayStream << NSYTilePos;
            arrayStream << field_0x3;
            arrayStream << getObjectIDAsUShort(ObjectID);
            arrayStream << field_0x6;
            arrayStream << field_0x7;
            arrayStream << field_0x8;
            arrayStream << field_0x9;
            arrayStream << field_0xa;
            arrayStream << field_0xb;
            arrayStream << field_0xc;
            arrayStream << field_0xd;
            for (size_t i = 0; i < 10; i++)
                arrayStream << Flags[i];
            return arrayified;
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

        PlayerLvlData& operator= (const QByteArray& array)
        {
            QDataStream arrayStream(array);
            arrayStream.setByteOrder(QDataStream::LittleEndian);

            arrayStream >> BaseHP;
            arrayStream >> BaseMP;
            arrayStream >> StrPowerPlus;
            arrayStream >> MagPowerPlus;
            arrayStream >> ExpForNextLevel;

            return *this;
        }

        operator QByteArray()
        {
            QByteArray arrayified;
            QDataStream arrayStream(&arrayified, QIODevice::ReadWrite);
            arrayStream.setByteOrder(QDataStream::LittleEndian);

            arrayStream << BaseHP;
            arrayStream << BaseMP;
            arrayStream << StrPowerPlus;
            arrayStream << MagPowerPlus;
            arrayStream << ExpForNextLevel;

            return arrayified;
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

        Tile& operator= (const QByteArray& array)
        {
            QDataStream arrayStream(array);
            arrayStream.setByteOrder(QDataStream::LittleEndian);

            arrayStream >> Layer1TileID;
            arrayStream >> Layer1Elev;
            arrayStream >> Layer1Rotation;
            arrayStream >> Layer1CollisionSomething;
            arrayStream >> Layer1ZoneDelimiter;
            arrayStream >> Layer2TileID;
            arrayStream >> Layer2Elev;
            arrayStream >> Layer2Rotation;
            arrayStream >> Layer2CollisionSomething;
            arrayStream >> Layer2ZoneDelimiter;

            return *this;
        }

        operator QByteArray()
        {
            QByteArray arrayified;
            QDataStream arrayStream(&arrayified, QIODevice::ReadWrite);
            arrayStream.setByteOrder(QDataStream::LittleEndian);

            arrayStream << Layer1TileID;
            arrayStream << Layer1Elev;
            arrayStream << Layer1Rotation;
            arrayStream << Layer1CollisionSomething;
            arrayStream << Layer1ZoneDelimiter;
            arrayStream << Layer2TileID;
            arrayStream << Layer2Elev;
            arrayStream << Layer2Rotation;
            arrayStream << Layer2CollisionSomething;
            arrayStream << Layer2ZoneDelimiter;

            return arrayified;
        }
    };

    /*!
     * \brief Stats structure for weapons.
     */
    struct WeaponStats {
        u_short OffSlash;
        u_short OffChop;
        u_short OffStab;
        u_short OffHolyM;
        u_short OffFireM;
        u_short OffEarthM;
        u_short OffWindM;
        u_short OffWaterM;
        undefined field_0x10;
        undefined field_0x11;
        undefined field_0x12;
        undefined field_0x13;
        undefined field_0x14;
        undefined field_0x15;
        undefined field_0x16;
        undefined field_0x17;
        undefined field_0x18;
        undefined field_0x19;
        undefined field_0x1a;
        undefined field_0x1b;
        undefined field_0x1c;
        undefined field_0x1d;
        undefined field_0x1e;
        undefined field_0x1f;
        undefined field_0x20;
        undefined field_0x21;
        undefined field_0x22;
        undefined field_0x23;
        undefined field_0x24;
        undefined field_0x25;
        undefined field_0x26;
        undefined field_0x27;
        undefined field_0x28;
        undefined field_0x29;
        undefined field_0x2a;
        undefined field_0x2b;
        undefined field_0x2c;
        undefined field_0x2d;
        undefined field_0x2e;
        undefined field_0x2f;
        undefined field_0x30;
        undefined field_0x31;
        undefined field_0x32;
        undefined field_0x33;
        undefined field_0x34;
        undefined field_0x35;
        undefined field_0x36;
        undefined field_0x37;
        undefined field_0x38;
        undefined field_0x39;
        undefined field_0x3a;
        undefined field_0x3b;
        undefined field_0x3c;
        undefined field_0x3d;
        undefined field_0x3e;
        undefined field_0x3f;
        undefined field_0x40;
        undefined field_0x41;
        undefined field_0x42;
        undefined field_0x43;

        WeaponStats& operator= (const QByteArray &array)
        {
            QDataStream arrayStream(array);
            arrayStream.setByteOrder(QDataStream::LittleEndian);

            arrayStream >> OffSlash;
            arrayStream >> OffChop;
            arrayStream >> OffStab;
            arrayStream >> OffHolyM;
            arrayStream >> OffFireM;
            arrayStream >> OffEarthM;
            arrayStream >> OffWindM;
            arrayStream >> OffWaterM;
            arrayStream >> field_0x10;
            arrayStream >> field_0x11;
            arrayStream >> field_0x12;
            arrayStream >> field_0x13;
            arrayStream >> field_0x14;
            arrayStream >> field_0x15;
            arrayStream >> field_0x16;
            arrayStream >> field_0x17;
            arrayStream >> field_0x18;
            arrayStream >> field_0x19;
            arrayStream >> field_0x1a;
            arrayStream >> field_0x1b;
            arrayStream >> field_0x1c;
            arrayStream >> field_0x1d;
            arrayStream >> field_0x1e;
            arrayStream >> field_0x1f;
            arrayStream >> field_0x20;
            arrayStream >> field_0x21;
            arrayStream >> field_0x22;
            arrayStream >> field_0x23;
            arrayStream >> field_0x24;
            arrayStream >> field_0x25;
            arrayStream >> field_0x26;
            arrayStream >> field_0x27;
            arrayStream >> field_0x28;
            arrayStream >> field_0x29;
            arrayStream >> field_0x2a;
            arrayStream >> field_0x2b;
            arrayStream >> field_0x2c;
            arrayStream >> field_0x2d;
            arrayStream >> field_0x2e;
            arrayStream >> field_0x2f;
            arrayStream >> field_0x30;
            arrayStream >> field_0x31;
            arrayStream >> field_0x32;
            arrayStream >> field_0x33;
            arrayStream >> field_0x34;
            arrayStream >> field_0x35;
            arrayStream >> field_0x36;
            arrayStream >> field_0x37;
            arrayStream >> field_0x38;
            arrayStream >> field_0x39;
            arrayStream >> field_0x3a;
            arrayStream >> field_0x3b;
            arrayStream >> field_0x3c;
            arrayStream >> field_0x3d;
            arrayStream >> field_0x3e;
            arrayStream >> field_0x3f;
            arrayStream >> field_0x40;
            arrayStream >> field_0x41;
            arrayStream >> field_0x42;
            arrayStream >> field_0x43;

            return *this;
        }

        operator QByteArray()
        {
            QByteArray arrayified;
            QDataStream arrayStream(&arrayified, QIODevice::ReadWrite);
            arrayStream.setByteOrder(QDataStream::LittleEndian);

            arrayStream << OffSlash;
            arrayStream << OffChop;
            arrayStream << OffStab;
            arrayStream << OffHolyM;
            arrayStream << OffFireM;
            arrayStream << OffEarthM;
            arrayStream << OffWindM;
            arrayStream << OffWaterM;
            arrayStream << field_0x10;
            arrayStream << field_0x11;
            arrayStream << field_0x12;
            arrayStream << field_0x13;
            arrayStream << field_0x14;
            arrayStream << field_0x15;
            arrayStream << field_0x16;
            arrayStream << field_0x17;
            arrayStream << field_0x18;
            arrayStream << field_0x19;
            arrayStream << field_0x1a;
            arrayStream << field_0x1b;
            arrayStream << field_0x1c;
            arrayStream << field_0x1d;
            arrayStream << field_0x1e;
            arrayStream << field_0x1f;
            arrayStream << field_0x20;
            arrayStream << field_0x21;
            arrayStream << field_0x22;
            arrayStream << field_0x23;
            arrayStream << field_0x24;
            arrayStream << field_0x25;
            arrayStream << field_0x26;
            arrayStream << field_0x27;
            arrayStream << field_0x28;
            arrayStream << field_0x29;
            arrayStream << field_0x2a;
            arrayStream << field_0x2b;
            arrayStream << field_0x2c;
            arrayStream << field_0x2d;
            arrayStream << field_0x2e;
            arrayStream << field_0x2f;
            arrayStream << field_0x30;
            arrayStream << field_0x31;
            arrayStream << field_0x32;
            arrayStream << field_0x33;
            arrayStream << field_0x34;
            arrayStream << field_0x35;
            arrayStream << field_0x36;
            arrayStream << field_0x37;
            arrayStream << field_0x38;
            arrayStream << field_0x39;
            arrayStream << field_0x3a;
            arrayStream << field_0x3b;
            arrayStream << field_0x3c;
            arrayStream << field_0x3d;
            arrayStream << field_0x3e;
            arrayStream << field_0x3f;
            arrayStream << field_0x40;
            arrayStream << field_0x41;
            arrayStream << field_0x42;
            arrayStream << field_0x43;

            return arrayified;
        }
    };
}


#endif // KFTYPES_H
