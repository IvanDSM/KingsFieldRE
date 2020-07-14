#ifndef KFTYPES_H
#define KFTYPES_H

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

    enum class EntityMeshID { /* Enum for the entity meshes. */
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

    enum class ItemID { /* Enum for the Item IDs in King's Field */
        ArmsA=46,
        ArmsDemonsHands=44,
        ArmsIronGloves=41,
        ArmsRuinousGloves=45,
        ArmsSilverArms=43,
        ArmsStoneHands=42,
        BodyA=33,
        BodyBreastPlate=28,
        BodyDarkArmor=31,
        BodyIceArmor=30,
        BodyKnightPlate=29,
        BodySeathsArmor=32,
        DummyItem1=60,
        DummyItem2=61,
        DummyItem3=62,
        DummyItem4=63,
        DummyItem5=64,
        DummyItem6=65,
        DummyItem7=66,
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
        HeadA=27,
        HeadBloodCrown=24,
        HeadGreatHelm=23,
        HeadIronMask=21,
        HeadKnightHelm=22,
        HeadLightningHelm=25,
        HeadSeathsHelm=26,
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
        None=255,
        ShieldA=40,
        ShieldCrystalGuard=37,
        ShieldLargeShield=35,
        ShieldLeatherShield=34,
        ShieldMoonGuard=36,
        ShieldSeathsShield=39,
        ShieldSkullShield=38,
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
        WeaponSpider=11
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
    static const std::unordered_map<const ItemID, const QString> itemIdNameMap =
#else
    static const std::map<const ItemID, const QString> itemIdNameMap =
#endif
    {
        {ItemID::ArmsA, "ArmsA"},
        {ItemID::ArmsDemonsHands, "ArmsDemonsHands"},
        {ItemID::ArmsIronGloves, "ArmsIronGloves"},
        {ItemID::ArmsRuinousGloves, "ArmsRuinousGloves"},
        {ItemID::ArmsSilverArms, "ArmsSilverArms"},
        {ItemID::ArmsStoneHands, "ArmsStoneHands"},
        {ItemID::BodyA, "BodyA"},
        {ItemID::BodyBreastPlate, "BodyBreastPlate"},
        {ItemID::BodyDarkArmor, "BodyDarkArmor"},
        {ItemID::BodyIceArmor, "BodyIceArmor"},
        {ItemID::BodyKnightPlate, "BodyKnightPlate"},
        {ItemID::BodySeathsArmor, "BodySeathsArmor"},
        {ItemID::DummyItem1, "DummyItem1"},
        {ItemID::DummyItem2, "DummyItem2"},
        {ItemID::DummyItem3, "DummyItem3"},
        {ItemID::DummyItem4, "DummyItem4"},
        {ItemID::DummyItem5, "DummyItem5"},
        {ItemID::DummyItem6, "DummyItem6"},
        {ItemID::DummyItem7, "DummyItem7"},
        {ItemID::EquipItemAmuletOfMist, "EquipItemAmuletOfMist"},
        {ItemID::EquipItemEarthRing, "EquipItemEarthRing"},
        {ItemID::EquipItemLightwaveRing, "EquipItemLightwaveRing"},
        {ItemID::EquipItemPsycprosCollar, "EquipItemPsycprosCollar"},
        {ItemID::EquipItemScorpionsBracelet, "EquipItemScorpionsBracelet"},
        {ItemID::EquipItemSeathsBracelet, "EquipItemSeathsBracelet"},
        {ItemID::EquipItemSeathsTear, "EquipItemSeathsTear"},
        {ItemID::FeetA, "FeetA"},
        {ItemID::FeetDeathWalkers, "FeetDeathWalkers"},
        {ItemID::FeetIronBoots, "FeetIronBoots"},
        {ItemID::FeetLegGuarders, "FeetLegGuarders"},
        {ItemID::FeetRuinousBoots, "FeetRuinousBoots"},
        {ItemID::FeetSilverBoots, "FeetSilverBoots"},
        {ItemID::HeadA, "HeadA"},
        {ItemID::HeadBloodCrown, "HeadBloodCrown"},
        {ItemID::HeadGreatHelm, "HeadGreatHelm"},
        {ItemID::HeadIronMask, "HeadIronMask"},
        {ItemID::HeadKnightHelm, "HeadKnightHelm"},
        {ItemID::HeadLightningHelm, "HeadLightningHelm"},
        {ItemID::HeadSeathsHelm, "HeadSeathsHelm"},
        {ItemID::ItemAHerb, "ItemAHerb"},
        {ItemID::ItemAHerb2, "ItemAHerb2"},
        {ItemID::ItemAPotion, "ItemAPotion"},
        {ItemID::ItemARing, "ItemARing"},
        {ItemID::ItemAntidote, "ItemAntidote"},
        {ItemID::ItemArrowForTheBow, "ItemArrowForTheBow"},
        {ItemID::ItemBloodStone, "ItemBloodStone"},
        {ItemID::ItemBluePotion, "ItemBluePotion"},
        {ItemID::ItemCrystal, "ItemCrystal"},
        {ItemID::ItemCrystalFlask, "ItemCrystalFlask"},
        {ItemID::ItemCrystalShard, "ItemCrystalShard"},
        {ItemID::ItemDarkCrystal, "ItemDarkCrystal"},
        {ItemID::ItemDemonsPick, "ItemDemonsPick"},
        {ItemID::ItemDragonCrystal, "ItemDragonCrystal"},
        {ItemID::ItemDragonStone, "ItemDragonStone"},
        {ItemID::ItemEarthCrystal, "ItemEarthCrystal"},
        {ItemID::ItemEarthHerb, "ItemEarthHerb"},
        {ItemID::ItemElfsBolt, "ItemElfsBolt"},
        {ItemID::ItemElfsKey, "ItemElfsKey"},
        {ItemID::ItemFigureOfSeath, "ItemFigureOfSeath"},
        {ItemID::ItemFireCrystal, "ItemFireCrystal"},
        {ItemID::ItemGoldCoin, "ItemGoldCoin"},
        {ItemID::ItemGoldKey, "ItemGoldKey"},
        {ItemID::ItemGoldPotion, "ItemGoldPotion"},
        {ItemID::ItemGreenPotion, "ItemGreenPotion"},
        {ItemID::ItemGroundBell, "ItemGroundBell"},
        {ItemID::ItemHarvinesFlute, "ItemHarvinesFlute"},
        {ItemID::ItemHarvinesKey, "ItemHarvinesKey"},
        {ItemID::ItemJailKey, "ItemJailKey"},
        {ItemID::ItemLightCrystal, "ItemLightCrystal"},
        {ItemID::ItemMagiciansKey, "ItemMagiciansKey"},
        {ItemID::ItemMinersMap, "ItemMinersMap"},
        {ItemID::ItemMoonGate, "ItemMoonGate"},
        {ItemID::ItemMoonKey, "ItemMoonKey"},
        {ItemID::ItemMoonStone, "ItemMoonStone"},
        {ItemID::ItemNecronsMap, "ItemNecronsMap"},
        {ItemID::ItemPhantomRod, "ItemPhantomRod"},
        {ItemID::ItemPiratesKey, "ItemPiratesKey"},
        {ItemID::ItemPiratesMap, "ItemPiratesMap"},
        {ItemID::ItemRedPotion, "ItemRedPotion"},
        {ItemID::ItemRhombusKey, "ItemRhombusKey"},
        {ItemID::ItemSeathsPlume, "ItemSeathsPlume"},
        {ItemID::ItemShrineKey, "ItemShrineKey"},
        {ItemID::ItemSilverKey, "ItemSilverKey"},
        {ItemID::ItemSkullKey, "ItemSkullKey"},
        {ItemID::ItemStarGate, "ItemStarGate"},
        {ItemID::ItemStarKey, "ItemStarKey"},
        {ItemID::ItemSunGate, "ItemSunGate"},
        {ItemID::ItemSunKey, "ItemSunKey"},
        {ItemID::ItemTruthGlass, "ItemTruthGlass"},
        {ItemID::ItemVerdite, "ItemVerdite"},
        {ItemID::ItemWaterCrystal, "ItemWaterCrystal"},
        {ItemID::ItemWindCrystal, "ItemWindCrystal"},
        {ItemID::None, "None"},
        {ItemID::ShieldA, "ShieldA"},
        {ItemID::ShieldCrystalGuard, "ShieldCrystalGuard"},
        {ItemID::ShieldLargeShield, "ShieldLargeShield"},
        {ItemID::ShieldLeatherShield, "ShieldLeatherShield"},
        {ItemID::ShieldMoonGuard, "ShieldMoonGuard"},
        {ItemID::ShieldSeathsShield, "ShieldSeathsShield"},
        {ItemID::ShieldSkullShield, "ShieldSkullShield"},
        {ItemID::WeaponA1, "WeaponA1"},
        {ItemID::WeaponA2, "WeaponA2"},
        {ItemID::WeaponA3, "WeaponA3"},
        {ItemID::WeaponA4, "WeaponA4"},
        {ItemID::WeaponA5, "WeaponA5"},
        {ItemID::WeaponArbalest, "WeaponArbalest"},
        {ItemID::WeaponBastardSword, "WeaponBastardSword"},
        {ItemID::WeaponBattleHammer, "WeaponBattleHammer"},
        {ItemID::WeaponBow, "WeaponBow"},
        {ItemID::WeaponCrescentAxe, "WeaponCrescentAxe"},
        {ItemID::WeaponDagger, "WeaponDagger"},
        {ItemID::WeaponDarkSlayer, "WeaponDarkSlayer"},
        {ItemID::WeaponFlameSword, "WeaponFlameSword"},
        {ItemID::WeaponIceBlade, "WeaponIceBlade"},
        {ItemID::WeaponKnightSword, "WeaponKnightSword"},
        {ItemID::WeaponMoonlightSword, "WeaponMoonlightSword"},
        {ItemID::WeaponMorningStar, "WeaponMorningStar"},
        {ItemID::WeaponSeathsSword, "WeaponSeathsSword"},
        {ItemID::WeaponShiden, "WeaponShiden"},
        {ItemID::WeaponShortSword, "WeaponShortSword"},
        {ItemID::WeaponSpider, "WeaponSpider"}
    };

    // Structs

    struct EntityClassDeclaration { /* Structure for the entity declarations at the beginning of each map file. */
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
    };

    struct EntityInstance { /* Structure for declarations of entity instances in the map files. */
        undefined Enabled;
        byte EntityClass;
        undefined field_0x2;
        byte WEXTilePos;
        byte NSYTilePos;
        undefined field_0x5;
        enum ItemID DroppedItem;
        byte Layer;
        undefined field_0x8;
        undefined field_0x9;
        undefined field_0xa;
        undefined field_0xb;
        undefined field_0xc;
        undefined field_0xd;
        undefined field_0xe;
        undefined field_0xf;
    };

    struct ObjectInstanceDeclaration { /* Structure for declarations of object instances in the map files. */
        byte TileLayer;
        byte WEXTilePos;
        byte NSYTilePos;
        undefined field_0x3;
        enum ItemID ItemID;
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
        enum ItemID KeyID;
        undefined field_0x11;
        byte InstanceContained;
        undefined field_0x13;
        undefined field_0x14;
        undefined field_0x15;
        undefined field_0x16;
        undefined field_0x17;
    };

    struct Tile { /* Structure for a tile in King's Field. */
        byte Layer1TileID;
        byte Layer1Elev;
        byte Layer1Rotation; /* 0-3, each step is 90° */
        byte Layer1CollisionSomething; /* Draw this to a texture to get something interesting */
        byte Layer1ZoneDelimiter; /* Draw this to a texture to get something interesting */
        byte Layer2TileID;
        byte Layer2Elev;
        byte Layer2Rotation; /* 0-3, each step is 90° */
        byte Layer2CollisionSomething; /* Draw this to a texture to get something interesting */
        byte Layer2ZoneDelimiter; /* Draw this to a texture to get something interesting */
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

    static const QString &getItemName(ItemID itemId)
    {
        if (itemIdNameMap.count(itemId) == 1)
            return itemIdNameMap.at(itemId);

        return itemIdNameMap.at(ItemID::None);
    }

    static ItemID getItemIDFromByte(byte itemId)
    {
        return static_cast<ItemID>(itemId);
    }

    static byte getItemIDAsByte(ItemID itemId)
    {
        return static_cast<byte>(itemId);
    }
}


#endif // KFTYPES_H
