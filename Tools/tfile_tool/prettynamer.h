#ifndef PRETTYNAMER_H
#define PRETTYNAMER_H

#include <QDataStream>
#include <QFile>
#include <QString>
#include <unordered_map>

class PrettyNamer
{
    public:
        PrettyNamer();
        const std::unordered_map<QString, QString> &getPrettyMap(const QByteArray &md5Hash);

    private:
        const std::unordered_map<QString, QString> emptyMap;
        const std::unordered_map<QString, QString> kfUSPrettyMap
        {
            {"FDAT.T27", "TextureDatabase"}, // TODO/FIXME: Find a better name for this file
            {"FDAT.T28", "GameData"}, // TODO/FIXME: Find a better name for this file
            {"FDAT.T29", "WeaponDaggerData"},
            {"FDAT.T30", "WeaponShortSwordData"},
            {"FDAT.T31", "WeaponKnightSwordData"},
            {"FDAT.T32", "WeaponMorningStarData"},
            {"FDAT.T33", "WeaponBattleHammerData"},
            {"FDAT.T34", "WeaponBastardSwordData"},
            {"FDAT.T35", "WeaponCrescentAxeData"},
            {"FDAT.T36", "WeaponFlameSwordData"},
            {"FDAT.T37", "WeaponShidenData"},
            {"FDAT.T38", "WeaponSpiderData"},
            {"FDAT.T39", "WeaponIceBladeData"},
            {"FDAT.T40", "WeaponSeathsSwordData"},
            {"FDAT.T41", "WeaponMoonlightSwordData"},
            {"FDAT.T42", "WeaponDarkSlayerData"},
            {"FDAT.T43", "WeaponBowData"},
            {"FDAT.T44", "WeaponArbalestData"},
            {"ITEM.T0", "WeaponDagger"},
            {"ITEM.T1", "WeaponShortSword"},
            {"ITEM.T2", "WeaponKnightSword"},
            {"ITEM.T3", "WeaponMorningStar"},
            {"ITEM.T4", "WeaponBattleHammer"},
            {"ITEM.T5", "WeaponBastardSword"},
            {"ITEM.T6", "WeaponCrescentAxe"},
            {"ITEM.T7", "WeaponFlameSword"},
            {"ITEM.T8", "WeaponShiden"},
            {"ITEM.T9", "WeaponSpider"},
            {"ITEM.T10", "WeaponIceBlade"},
            {"ITEM.T11", "WeaponSeathsSword"},
            {"ITEM.T12", "WeaponMoonlightSword"},
            {"ITEM.T13", "WeaponDarkSlayer"},
            {"ITEM.T14", "WeaponBow"},
            {"ITEM.T15", "WeaponArbalest"},
            {"ITEM.T16", "HeadIronMask"},
            {"ITEM.T17", "HeadKnightHelm"},
            {"ITEM.T18", "HeadGreatHelm"},
            {"ITEM.T19", "HeadBloodCrown"},
            {"ITEM.T20", "HeadLightningHelm"},
            {"ITEM.T21", "HeadSeathsHelm"},
            {"ITEM.T22", "BodyBreastPlate"},
            {"ITEM.T23", "BodyKnightPlate"},
            {"ITEM.T24", "BodyIceArmor"},
            {"ITEM.T25", "BodyDarkArmor"},
            {"ITEM.T26", "BodySeathsArmor"},
            {"ITEM.T27", "ShieldLeatherShield"},
            {"ITEM.T28", "ShieldLargeShield"},
            {"ITEM.T29", "ShieldMoonGuard"},
            {"ITEM.T30", "ShieldCrystalGuard"},
            {"ITEM.T31", "ShieldSkullShield"},
            {"ITEM.T32", "ShieldSeathsShield"},
            {"ITEM.T33", "ArmsIronGloves"},
            {"ITEM.T34", "ArmsStoneHands"},
            {"ITEM.T35", "ArmsSilverArms"},
            {"ITEM.T36", "ArmsDemonsHands"},
            {"ITEM.T37", "ArmsRuinousGloves"},
            {"ITEM.T38", "FeetIronBoots"},
            {"ITEM.T39", "FeetLegGuarders"},
            {"ITEM.T40", "FeetSilverBoots"},
            {"ITEM.T41", "FeetDeathWalkers"},
            {"ITEM.T42", "FeetRuinousBoots"},
            {"ITEM.T43", "EquipItemScorpionsBracelet"},
            {"ITEM.T44", "EquipItemSeathsTear"},
            {"ITEM.T45", "EquipItemSeathsBracelet"},
            {"ITEM.T46", "EquipItemEarthRing"},
            {"ITEM.T47", "EquipItemPsycprosCollar"},
            {"ITEM.T48", "EquipItemAmuletOfMist"},
            {"ITEM.T49", "EquipItemLightwaveRing"},
            {"ITEM.T50", "ItemPiratesMap"},
            {"ITEM.T51", "ItemMinersMap"},
            {"ITEM.T52", "ItemNecronsMap"},
            {"ITEM.T53", "ItemGoldCoin"},
            {"ITEM.T54", "ItemBloodStone"},
            {"ITEM.T55", "ItemMoonStone"},
            {"ITEM.T56", "ItemVerdite"},
            {"ITEM.T57", "ItemEarthHerb"},
            {"ITEM.T58", "ItemAntidote"},
            {"ITEM.T59", "ItemDragonCrystal"},
            {"ITEM.T60", "ItemBluePotion"},
            {"ITEM.T61", "ItemRedPotion"},
            {"ITEM.T62", "ItemGreenPotion"},
            {"ITEM.T63", "ItemGoldPotion"},
            {"ITEM.T64", "ItemAPotion"},
            {"ITEM.T65", "ItemCrystalFlask"},
            {"ITEM.T66", "ItemFigureOfSeath"},
            {"ITEM.T67", "ItemPhantomRod"},
            {"ITEM.T68", "ItemTruthGlass"},
            {"ITEM.T69", "ItemSeathsPlume"},
            {"ITEM.T70", "ItemDemonsPick"},
            {"ITEM.T71", "ItemHarvinesFlute"},
            {"ITEM.T72", "ItemGroundBell"},
            {"ITEM.T73", "ItemFireCrystal"},
            {"ITEM.T74", "ItemWaterCrystal"},
            {"ITEM.T75", "ItemEarthCrystal"},
            {"ITEM.T76", "ItemWindCrystal"},
            {"ITEM.T77", "ItemLightCrystal"},
            {"ITEM.T78", "ItemDarkCrystal"},
            {"ITEM.T79", "ItemCrystal"},
            {"ITEM.T80", "ItemCrystalShard"},
            {"ITEM.T81", "ItemARing"},
            {"ITEM.T82", "ItemElfsKey"},
            {"ITEM.T83", "ItemPiratesKey"},
            {"ITEM.T84", "ItemSkullKey"},
            {"ITEM.T85", "ItemJailKey"},
            {"ITEM.T86", "ItemRhombusKey"},
            {"ITEM.T87", "ItemHarvinesKey"},
            {"ITEM.T88", "ItemDragonStone"},
            {"ITEM.T89", "ItemMagiciansKey"},
            {"ITEM.T90", "ItemSilverKey"},
            {"ITEM.T91", "ItemGoldKey"},
            {"ITEM.T92", "ItemShrineKey"},
            {"ITEM.T93", "ItemAHerb"},
            {"ITEM.T94", "ItemMoonGate"},
            {"ITEM.T95", "ItemStarGate"},
            {"ITEM.T96", "ItemSunGate"},
            {"ITEM.T97", "ItemMoonKey"},
            {"ITEM.T98", "ItemStarKey"},
            {"ITEM.T99", "ItemSunKey"},
            {"ITEM.T100", "ItemArrowForTheBow"},
            {"ITEM.T101", "ItemElfsBolt"},
            {"ITEM.T102", "ItemAHerb2"},
            {"ITEM.T103", "TextAlHunt"},
            {"ITEM.T104", "TextNolaBagil"},
            {"ITEM.T105", "TextMarkWozz"},
            {"ITEM.T106", "TextRandFerrer"},
            {"ITEM.T107", "TextRaddBilheim"},
            {"ITEM.T108", "TextKehlHunt"},
            {"ITEM.T109", "TextKrolaSandlerAmgun"},
            {"ITEM.T110", "TextCliffLore"},
            {"ITEM.T111", "TextDavidTabler"},
            {"ITEM.T112", "TextDalfVice"},
            {"ITEM.T113", "TextHarrisCarvitto"},
            {"ITEM.T114", "TextTeoGigiBudwell"},
            {"ITEM.T115", "TextKarenLeonShore"},
            {"ITEM.T116", "TextBaseNo1"},
            {"ITEM.T117", "TextBaseNo2"},
            {"ITEM.T118", "TextBaseNo3"},
            {"ITEM.T119", "TextBaseNo4"},
            {"ITEM.T120", "TextBaseNo5"},
            {"ITEM.T121", "TextBaseNo6"},
            {"ITEM.T122", "TextTheMagicCaveOfIce"},
            {"ITEM.T123", "TextBaseNo7"},
            {"ITEM.T124", "TextTheEntranceToTheNorthVillage"},
            {"ITEM.T125", "TextTheEntranceToTheSouthVillage"},
            {"ITEM.T126", "TextTheSpaceForCompletionNoTrespassing"},
            {"ITEM.T127", "TextTheEntranceToTheCentralVillage"},
            {"ITEM.T128", "TextTheEntranceToTheBigMine"},
            {"ITEM.T129", "TextTheUnderworldPrisonNo1"},
            {"ITEM.T130", "TextTheUnderworldPrisonNo2"},
            {"ITEM.T131", "TextTheCemeteryForTheMilitaryGuardsOfKingHarvineIII"},
            {"ITEM.T132", "TextRoyalTreasureHouse"},
            {"ITEM.T133", "TextTheMagicCaveOfFire"},
            {"ITEM.T134", "TextWarriorsWhoWereKilledByGuyrasLegionAreBuriedHere"},
            {"ITEM.T135", "TextTheSoulsOfTheGuardsWhoWereKilledAreWaitingToWatchTheNextFight"},
            {"ITEM.T136", "TextTheKingOfWindsKingHarvineIIIHadStartedToConstructHisCastleHere"},
            {"ITEM.T137", "TextTheCastleOfTheGreatRulerOfTheNorthernContinentKingHarvineIII"},
            {"ITEM.T138", "TextDangerAhead"},
            {"ITEM.T139", "TextInTheNameOfTheGreatMageNoOneCanEnterThisCaveOfEarthSoul"},
            {"ITEM.T140", "TextGalthFreeTheDemonOfTheDarksideDiedWithTheHighElvesHeIsAPhantomOfTheWorld"},
            {"ITEM.T141", "TextAMessageFromTheEastLandRestInPeaceHere"},
            {"ITEM.T142", "TextMostSoldiersHaveAlreadyDiedThereIsNoWayToLeaveTheIslandWeRealizeThatThereIsNoWayBackHome"},
            {"ITEM.T143", "TextInTheNameOfTsedeckTheMageOfFireWhoDefeatedKingHarvineIIIAndRuledTheNorthernContinent"},
            {"ITEM.T144", "TextGigisHouseSandler"},
            {"ITEM.T145", "TextTheyCanBeAttackedByBowsTakeGoodAim"},
            {"ITEM.T146", "TextDoNotEnterOldHand"},
            {"ITEM.T147", "TextMedicalHerbsForSaleAlHunt"},
            {"ITEM.T148", "TextTheSouthGraveyardToTheSmallMine"},
            {"ITEM.T149", "TextTermitesNestAheadWatchYourStep"},
            {"ITEM.T150", "TextMyBelovedSonYouHaveFoughtForMeAndHaveLostYourLifeForMeMayYouRestInPeace"},
            {"ITEM.T151", "TextDoNotGetCloserKrakensNest"},
            {"ITEM.T152", "TextDangerousNoExit"},
            {"ITEM.T153", "TextTheElfCave"},
            {"ITEM.T154", "TextByAndByAManWhoComesHereBeatsTheBlackDragonWithTheBlessingOfSeath"},
            {"ITEM.T155", "TextTheCaveOfTheDarksideThisIsHell"},
            {"ITEM.T156", "TextOfferEverythingToGuyraWhoRulesTheLightAndTheDark"},
            {"ITEM.T157", "TextTheyAreCreatingDevilsBeCareful"},
            {"ITEM.T158", "TextWhenTheWarriorsStandUpTheGreatDoorWillBeOpenedAgain"},
            {"ITEM.T159", "TextTheEntranceToTheSmallMine"},
            {"ITEM.T160", "TextThePoisonedCaveDangerous"},
            {"ITEM.T161", "TextTheGreatDemonsGrave"},
            {"ITEM.T162", "TextEarnestsBody"},
            {"ITEM.T163", "TextThePictureOfWarriors"},
            {"ITEM.T164", "TextTruthGlassGreenSlime"},
            {"ITEM.T165", "TextTruthGlassPoisonSlime"},
            {"ITEM.T166", "TextTruthGlassSigill"},
            {"ITEM.T167", "TextTruthGlassSigill2"},
            {"ITEM.T168", "TextTruthGlassBaltail"},
            {"ITEM.T169", "TextTruthGlassBaltail2"},
            {"ITEM.T170", "TextTruthGlassPoisonBaltail"},
            {"ITEM.T171", "TextTruthGlassPoisonBaltail2"},
            {"ITEM.T172", "TextTruthGlassFireElemental"},
            {"ITEM.T173", "TextTruthGlassFireElemental2"},
            {"ITEM.T174", "TextTruthGlassGhosts"},
            {"ITEM.T175", "TextTruthGlassReiks"},
            {"ITEM.T176", "TextTruthGlassHeadEater"},
            {"ITEM.T177", "TextTruthGlassMogle"},
            {"ITEM.T178", "TextTruthGlassSKnight"},
            {"ITEM.T179", "TextTruthGlassNecronsSoldiers"},
            {"ITEM.T180", "TextTruthGlassArchers"},
            {"ITEM.T181", "TextTruthGlassSkeleton"},
            {"ITEM.T182", "TextTruthGlassTermite"},
            {"ITEM.T183", "TextTruthGlassKald"},
            {"ITEM.T184", "TextTruthGlassPsythe"},
            {"ITEM.T185", "TextTruthGlassQueenTermite"},
            {"ITEM.T186", "TextTruthGlassFreezeBall"},
            {"ITEM.T187", "TextTruthGlassLogStalker"},
            {"ITEM.T188", "TextTruthGlassDemonLord"},
            {"ITEM.T189", "TextTruthGlassKraken"},
            {"ITEM.T190", "TextTruthGlassKraken2"},
            {"ITEM.T191", "TextTruthGlassEarthElemental"},
            {"ITEM.T192", "TextTruthGlassRefma"},
            {"ITEM.T193", "TextTruthGlassTarn"},
            {"ITEM.T194", "TextTruthGlassCopperKnight"},
            {"ITEM.T195", "TextTruthGlassDiasBagil"},
            {"ITEM.T196", "TextTruthGlassGuyra"},
            {"ITEM.T197", "TextTruthGlassSalamander"},
            {"ITEM.T198", "TextTruthGlassFlameSpirit"},
            {"ITEM.T199", "TextTruthGlassBillent"},
            {"ITEM.T200", "TextTruthGlassSkeletonOfOneEyedGiant"},
            {"ITEM.T201", "TextTruthGlassThePictureOfAKing"},
            {"ITEM.T201", "TextTruthGlassThePictureOfAKing"},
            {"ITEM.T202", "TextTruthGlassMechaDemonLord"},
            {"ITEM.T203", "TextTruthGlassMechaTermite"},
            {"ITEM.T204", "TextTruthGlassMechaReiks"},
            {"ITEM.T205", "TextTruthGlassMagesCandlesticks"},
            {"ITEM.T206", "TextTruthGlassBitt"},
            {"ITEM.T207", "TextTruthGlassRefma2"},
            {"ITEM.T208", "TextTruthGlassCelffyFoss"},
            {"ITEM.T209", "TextTruthGlassCelffyFoss2"},
            {"ITEM.T210", "TextTruthGlassRaffyFoss"},
            {"ITEM.T211", "TextTruthGlassJoseHarven"},
            {"ITEM.T212", "TextTruthGlassNolaBagil"},
            {"ITEM.T213", "TextTruthGlassMeryl"},
            {"ITEM.T214", "TextTruthGlassGigiBudwell"},
            {"ITEM.T215", "TextTruthGlassGigiBudwell2"},
            {"ITEM.T216", "TextTruthGlassTeoBudwell"},
            {"ITEM.T217", "TextTruthGlassTeoBudwell2"},
            {"ITEM.T218", "TextTruthGlassTeoBudwell3"},
            {"ITEM.T219", "TextTruthGlassKarenShore"},
            {"ITEM.T220", "TextTruthGlassLeonShore"},
            {"ITEM.T221", "TextTruthGlassLeonShore2"},
            {"ITEM.T222", "TextTruthGlassAlHunt"},
            {"ITEM.T223", "TextTruthGlassHarrisCarvitto"},
            {"ITEM.T224", "TextTruthGlassFaiFadlin"},
            {"ITEM.T225", "TextTruthGlassCliffLore"},
            {"ITEM.T226", "TextTruthGlassRandFerrer"},
            {"ITEM.T227", "TextTruthGlassDavidTabler"},
            {"ITEM.T228", "TextTruthGlassDalfVice"},
            {"ITEM.T229", "TextTruthGlassRaddBilheim"},
            {"ITEM.T230", "TextTruthGlassKrolaAmgun"},
            {"ITEM.T231", "TextTruthGlassKrolaAmgun2"},
            {"ITEM.T232", "TextTruthGlassSandlerAmgun"},
            {"ITEM.T233", "TextTruthGlassSandlerAmgun2"},
            {"ITEM.T234", "TextTruthGlassMarkWozz"},
            {"ITEM.T235", "TextTruthGlassEarnestClyde"},
            {"ITEM.T236", "TextTruthGlassKehlHunt"},
            {"ITEM.T237", "TextTruthGlassKehlHunt2"},
            {"ITEM.T238", "TextTruthGlassKarenShore2"},
            {"ITEM.T239", "TextTruthGlassTheGraveOfASaint"},
            {"ITEM.T240", "TextTruthGlassEarnestClyde2"},
            {"ITEM.T241", "TextTruthGlassDragonGrass"},
            {"ITEM.T242", "TextTruthGlassMiria"},
            {"ITEM.T243", "TextMerylDagger"},
            {"ITEM.T244", "TextMerylShortSword"},
            {"ITEM.T245", "TextMerylKnightSword"},
            {"ITEM.T246", "TextMerylMorningStar"},
            {"ITEM.T247", "TextMerylBattleHammer"},
            {"ITEM.T248", "TextMerylBastardSword"},
            {"ITEM.T249", "TextMerylCrescentAxe"},
            {"ITEM.T250", "TextMerylFlameSword"},
            {"ITEM.T251", "TextMerylShiden"},
            {"ITEM.T252", "TextMerylSpider"},
            {"ITEM.T253", "TextMerylIceBlade"},
            {"ITEM.T254", "TextMerylSeathsSword"},
            {"ITEM.T255", "TextMerylMoonlightSword"},
            {"ITEM.T256", "TextMerylDarkSlayer"},
            {"ITEM.T257", "TextMerylBow"},
            {"ITEM.T258", "TextMerylArbalest"},
            {"ITEM.T259", "TextMerylIronMask"},
            {"ITEM.T260", "TextMerylKnightHelm"},
            {"ITEM.T261", "TextMerylGreatHelm"},
            {"ITEM.T262", "TextMerylBloodCrown"},
            {"ITEM.T263", "TextMerylLightningHelm"},
            {"ITEM.T264", "TextMerylSeathsHelm"},
            {"ITEM.T265", "TextMerylBreastPlate"},
            {"ITEM.T266", "TextMerylKnightPlate"},
            {"ITEM.T267", "TextMerylIceArmor"},
            {"ITEM.T268", "TextMerylDarkArmor"},
            {"ITEM.T269", "TextMerylSeathsArmor"},
            {"ITEM.T270", "TextMerylLeatherShield"},
            {"ITEM.T271", "TextMerylLargeShield"},
            {"ITEM.T272", "TextMerylMoonGuard"},
            {"ITEM.T273", "TextMerylCrystalGuard"},
            {"ITEM.T274", "TextMerylSkullShield"},
            {"ITEM.T275", "TextMerylSeathsShield"},
            {"ITEM.T276", "TextMerylIronGloves"},
            {"ITEM.T277", "TextMerylStoneHands"},
            {"ITEM.T278", "TextMerylSilverArms"},
            {"ITEM.T279", "TextMerylDemonsHands"},
            {"ITEM.T280", "TextMerylRuinousGloves"},
            {"ITEM.T281", "TextMerylIronBoots"},
            {"ITEM.T282", "TextMerylLegGuarders"},
            {"ITEM.T283", "TextMerylSilverBoots"},
            {"ITEM.T284", "TextMerylDeathWalkers"},
            {"ITEM.T285", "TextMerylRuinousBoots"},
            {"ITEM.T286", "TextMerylScorpionsBracelet"},
            {"ITEM.T287", "TextMerylSeathsTear"},
            {"ITEM.T288", "TextMerylSeathsBracelet"},
            {"ITEM.T289", "TextMerylEarthRing"},
            {"ITEM.T290", "TextMerylPsycprosCollar"},
            {"ITEM.T291", "TextMerylAmuletOfMist"},
            {"ITEM.T292", "TextMerylLightwaveRing"},
            {"ITEM.T293", "TextMerylPiratesMap"},
            {"ITEM.T294", "TextMerylMinersMap"},
            {"ITEM.T295", "TextMerylNecronsMap"},
            {"ITEM.T296", "TextMerylBloodStone"},
            {"ITEM.T297", "TextMerylMoonStone"},
            {"ITEM.T298", "TextMerylVerdite"},
            {"ITEM.T299", "TextMerylEarthHerb"},
            {"ITEM.T300", "TextMerylAntidote"},
            {"ITEM.T301", "TextMerylDragonCrystal"},
            {"ITEM.T302", "TextMerylBluePotion"},
            {"ITEM.T303", "TextMerylRedPotion"},
            {"ITEM.T304", "TextMerylGreenPotion"},
            {"ITEM.T305", "TextMerylGoldPotion"},
            {"ITEM.T306", "TextMerylCrystalFlask"},
            {"ITEM.T307", "TextMerylFigureOfSeath"},
            {"ITEM.T308", "TextMerylPhantomRod"},
            {"ITEM.T309", "TextMerylTruthGlass"},
            {"ITEM.T310", "TextMerylSeathsPlume"},
            {"ITEM.T311", "TextMerylDemonsPick"},
            {"ITEM.T312", "TextMerylHarvinesFlute"},
            {"ITEM.T313", "TextMerylGroundBell"},
            {"ITEM.T314", "TextMerylFireCrystal"},
            {"ITEM.T315", "TextMerylWaterCrystal"},
            {"ITEM.T316", "TextMerylEarthCrystal"},
            {"ITEM.T317", "TextMerylWindCrystal"},
            {"ITEM.T318", "TextMerylLightCrystal"},
            {"ITEM.T319", "TextMerylDarkCrystal"},
            {"ITEM.T320", "TextMerylCrystal"},
            {"ITEM.T321", "TextMerylCrystalShard"},
            {"ITEM.T322", "TextMerylElfsKey"},
            {"ITEM.T323", "TextMerylPiratesKey"},
            {"ITEM.T324", "TextMerylSkullKey"},
            {"ITEM.T325", "TextMerylJailKey"},
            {"ITEM.T326", "TextMerylRhombusKey"},
            {"ITEM.T327", "TextMerylHarvinesKey"},
            {"ITEM.T328", "TextMerylDragonStone"},
            {"ITEM.T329", "TextMerylMagiciansKey"},
            {"ITEM.T330", "TextMerylSilverKey"},
            {"ITEM.T331", "TextMerylGoldKey"},
            {"ITEM.T332", "TextMerylShrineKey"},
            {"ITEM.T333", "TextMerylMoonGate"},
            {"ITEM.T334", "TextMerylStarGate"},
            {"ITEM.T335", "TextMerylSunGate"},
            {"ITEM.T336", "TextMerylMoonKey"},
            {"ITEM.T337", "TextMerylStarKey"},
            {"ITEM.T338", "TextMerylSunKey"},
            {"ITEM.T339", "TextMerylArrowForTheBow"},
            {"ITEM.T340", "TextMerylElfsBolt"},
            {"ITEM.T365", "TextTruthGlassWestSeaside"},
            {"ITEM.T366", "TextTruthGlassThePiratesCave"},
            {"ITEM.T367", "TextTruthGlassCaveOfOldHand"},
            {"ITEM.T368", "TextTruthGlassTheMagesLighthouse"},
            {"ITEM.T369", "TextTruthGlassTheNorthVillage"},
            {"ITEM.T370", "TextTruthGlassTheSouthVillage"},
            {"ITEM.T371", "TextTruthGlassASmallMine"},
            {"ITEM.T372", "TextTruthGlassTheNorthGraveyard"},
            {"ITEM.T373", "TextTruthGlassBaseNo1"},
            {"ITEM.T374", "TextTruthGlassBaseNo2"},
            {"ITEM.T375", "TextTruthGlassBaseNo3"},
            {"ITEM.T376", "TextTruthGlassBaseNo4"},
            {"ITEM.T377", "TextTruthGlassBaseNo5"},
            {"ITEM.T378", "TextTruthGlassBaseNo6"},
            {"ITEM.T379", "TextTruthGlassTheRuinsOfKingHarvinesCastle"},
            {"ITEM.T380", "TextTruthGlassTheTermitesNest"},
            {"ITEM.T381", "TextTruthGlassTheCemetery"},
            {"ITEM.T382", "TextTruthGlassTheSoldiersCemetery"},
            {"ITEM.T383", "TextTruthGlassTheWindowOfHomesickness"},
            {"ITEM.T384", "TextTruthGlassTheElfGraveyard"},
            {"ITEM.T385", "TextTruthGlassTheEastVillage"},
            {"ITEM.T386", "TextTruthGlassTheElfShrine"},
            {"ITEM.T387", "TextTruthGlassSeathsFountain"},
            {"ITEM.T388", "TextTruthGlassTheMagicPalaceOfFire"},
            {"ITEM.T389", "TextTruthGlassTheMagicPalaceOfIce"},
            {"ITEM.T390", "TextTruthGlassTheDemonsGrave"},
            {"ITEM.T391", "TextTruthGlassTheSouthGraveyard"},
            {"ITEM.T392", "TextTruthGlassTheBigMine"},
            {"ITEM.T393", "TextTruthGlassThePoisonedCave"},
            {"ITEM.T394", "TextTruthGlassTheCaveOfTheDarkside"},
            {"ITEM.T395", "TextTruthGlassTheElfCave"},
            {"ITEM.T396", "TextTruthGlassTheCaveOfTheEarthSoul"},
            {"ITEM.T397", "TextTruthGlassTheLookout"},
            {"ITEM.T398", "TextTruthGlassNecronsColiseum"},
            {"ITEM.T399", "TextTruthGlassTheWarriorsGraveyard"},
            {"ITEM.T400", "TextTruthGlassTheResearchOffice"},
            {"ITEM.T401", "TextTruthGlassTheVillageOfTheWind"},
            {"ITEM.T402", "TextTruthGlassTheEastSeaside"},
            {"VAB.T1", "WaveformSoundEffects"},
            {"VAB.T112", "SequenceWesternShore"},
            {"VAB.T113", "SequenceGarrison"},
            {"VAB.T114", "SequenceCentralVillage"},
            {"VAB.T115", "SequenceEastVillage"},
            {"VAB.T116", "SequenceCathedral"},
            {"VAB.T117", "SequenceBigMine"},
            {"VAB.T118", "SequenceNecronsColiseum"},
            {"VAB.T119", "SequenceGuyrasLair"},
            {"VAB.T121", "SequenceCentralVillage2"},
        };
};

#endif // PRETTYNAMER_H
