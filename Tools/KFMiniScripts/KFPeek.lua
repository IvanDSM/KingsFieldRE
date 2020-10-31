--- KFPeek for use with psxjin
--- Use only with King's Field (USA)!
--- https://github.com/IvanDSM/KingsFieldRE

--- String maps
meshids = {
    [83] = "AlHunt",     [18] = "Archer",     [4] = "Baltail",     [5] = "BaltailTail",
    [42] = "Billent",     [50] = "Bitt",     [41] = "Cable?",     [64] = "CellfyFoss",
    [65] = "CellfyFoss2",     [86] = "CliffLore",     [34] = "CopperKnight",     [89] = "DalfVice",
    [88] = "DavidTabler",     [28] = "DemonLord",     [35] = "DiasBagil",     [107] = "DragonGrass",
    [96] = "EarnestClyde",     [106] = "EarnestClydeSitting",     [31] = "EarthElemental",     [85] = "FaiFadlin",
    [9] = "FireElemental",     [10] = "Ghost",     [25] = "GiantTermite",     [74] = "GigiBudwell",
    [76] = "GigiBudwellWatering",     [0] = "GreenSlime",     [12] = "GreenSlime2",     [13] = "GreenSlime3",
    [19] = "GreenSlime4",     [36] = "GreenSlimeDeath",     [37] = "GreenSlimeDeath2",     [38] = "GreenSlimeDeath3",
    [43] = "GreenSlimeDeath4",     [39] = "Guyra",     [84] = "HarrisCarvitto",     [14] = "HeadEater",
    [67] = "JoseHarven",     [104] = "JoseHarvenDeath",     [108] = "JoseHarvenDeath2",     [23] = "Kald",
    [80] = "KarenShore",     [99] = "KarenShoreChair",     [97] = "KehlHunt",     [98] = "KehlHunt2",
    [29] = "KrakenBody",     [30] = "KrakenHead",     [91] = "KrolaAmgun",     [92] = "KrolaAmgunCooking",
    [81] = "LeonShore",     [82] = "LeonShoreWatering",     [27] = "LogStalker",     [49] = "MagesCandlesticks",
    [95] = "MarkWozz",     [46] = "MechaDemonLord",     [48] = "MechaReik",     [47] = "MechaTermite",
    [73] = "Meryl",     [109] = "Miria",     [15] = "Mogle",     [70] = "NolaBagil",
    [255] = "None",     [1] = "PoisonSlime",     [24] = "Psythe",     [90] = "RaddBilheim",
    [66] = "RaffyFoss",     [87] = "RandFerrer",     [26] = "RedSpikeBall?",     [32] = "Refma",
    [51] = "Refma2",     [11] = "Reik",     [16] = "SKnight",     [105] = "SaintGrave",
    [40] = "Salamander",     [93] = "SandlerAmgun",     [94] = "SandlerAmgun2",     [2] = "Sigill",
    [21] = "Skeleton",     [44] = "SkeletonOfOneEyedGiant",     [17] = "Soldier",     [6] = "StingFly",
    [7] = "StingFlyTail",     [33] = "Tarn",     [77] = "TeoBudwell",     [79] = "TeoBudwellMowing",
    [78] = "TeoBudwellWithGigi",     [22] = "Termite",     [45] = "ThePictureOfAKing",     [128] = "Transparent",
    [3] = "Unused",     [58] = "Unused10",     [59] = "Unused11",     [60] = "Unused12",
    [61] = "Unused13",     [62] = "Unused14",     [63] = "Unused15",     [68] = "Unused16",
    [69] = "Unused17",     [71] = "Unused18",     [72] = "Unused19",     [8] = "Unused2",
    [75] = "Unused20",     [100] = "Unused21",     [101] = "Unused22",     [102] = "Unused23",
    [103] = "Unused24",     [20] = "Unused3",     [52] = "Unused4",     [53] = "Unused5",
    [54] = "Unused6", [55] = "Unused7", [56] = "Unused8", [57] = "Unused9"
}

messageids = {
	[24] = "ABrokenShovel", [8] = "ABrokenSword", [33] = "ACultureMedium", [12] = "ADeadCrystalMiner",
	[23] = "AGrave", [16] = "AGuidepost", [13] = "ASoldierOfVerdite", [14] = "ATree",
	[10] = "AWarriorsGrave", [9] = "Bones", [18] = "CantCarryAnyMore", [7] = "Dead",
	[15] = "DragonGrass", [22] = "DrewSomeWater", [6] = "Empty", [28] = "HarrissGrave",
	[0] = "LevelUp", [2] = "Locked", [34] = "LostTheEffect", [32] = "MagicGained",
	[1] = "MagicLearned", [255] = "None", [19] = "NotAccepted", [20] = "NothingHappens",
	[5] = "NothingThere", [3] = "Sealed", [31] = "StrengthGained", [11] = "TeosBody",
	[25] = "TheElfsGrave", [30] = "TheMagiciansLamp", [26] = "TheMinersGrave", [17] = "ThePillarOfWind",
	[29] = "TheSamuraisGrave", [27] = "TheSoldiersGrave", [4] = "WrongKey", [21] = "XGold"
}

objectids = {
    [264] = "ABrokenSword",     [141] = "ASoldierOfVerdite",     [46] = "ArmsA",     [44] = "ArmsDemonsHands",
    [41] = "ArmsIronGloves",     [45] = "ArmsRuinousGloves",     [43] = "ArmsSilverArms",     [42] = "ArmsStoneHands",
    [179] = "Barrel",     [282] = "Bed",     [128] = "BigGreyDoorLeft",     [127] = "BigGreyDoorRight",
    [129] = "BigRoughStoneDoor",     [135] = "BigStoneDoor",     [33] = "BodyA",     [28] = "BodyBreastPlate",
    [31] = "BodyDarkArmor",     [30] = "BodyIceArmor",     [29] = "BodyKnightPlate",     [32] = "BodySeathsArmor",
    [143] = "Bones",     [144] = "Bones2",     [180] = "Bucket",     [280] = "CeilingTorch",
    [259] = "Chair",     [140] = "ColosseumDoor",     [169] = "CopperKnightStatue",     [256] = "CrossFeetTable",
    [244] = "DaytimeSkybox",     [146] = "DeadCrystalMiner",     [147] = "DeadDudeRENAME_ME",     [275] = "DemonLordFromMadScientistTube",
    [170] = "DemonLordStatue",     [278] = "DragonGrass",     [187] = "DragonStoneSlot",     [210] = "DrawbridgeSwitch",
    [60] = "DummyItem1",     [61] = "DummyItem2",     [62] = "DummyItem3",     [63] = "DummyItem4",
    [64] = "DummyItem5",     [65] = "DummyItem6",     [66] = "DummyItem7",     [168] = "EarthElementalStatue",
    [153] = "ElfsGrave",     [58] = "EquipItemAmuletOfMist",     [56] = "EquipItemEarthRing",     [59] = "EquipItemLightwaveRing",
    [57] = "EquipItemPsycprosCollar",     [53] = "EquipItemScorpionsBracelet",     [55] = "EquipItemSeathsBracelet",     [54] = "EquipItemSeathsTear",
    [52] = "FeetA",     [50] = "FeetDeathWalkers",     [47] = "FeetIronBoots",     [48] = "FeetLegGuarders",
    [51] = "FeetRuinousBoots",     [49] = "FeetSilverBoots",     [265] = "GoldenThingRENAME_ME",     [206] = "GreenWallFloorTrap",
    [205] = "GreenWallSecretDoor",     [209] = "GreenWallWithSecret1",     [214] = "GreenWallWithSecret2",     [213] = "GreenWallWithSpikeTrap",
    [189] = "Guidepost",     [231] = "GuyraTeleportCube",     [159] = "HarvineCastleSign",     [194] = "HarvinesCastleDoor",
    [262] = "HarvinesThrone",     [27] = "HeadA",     [24] = "HeadBloodCrown",     [23] = "HeadGreatHelm",
    [21] = "HeadIronMask",     [22] = "HeadKnightHelm",     [25] = "HeadLightningHelm",     [26] = "HeadSeathsHelm",
    [183] = "InvisibleObject",     [110] = "ItemAHerb",     [119] = "ItemAHerb2",     [81] = "ItemAPotion",
    [98] = "ItemARing",     [75] = "ItemAntidote",     [117] = "ItemArrowForTheBow",     [71] = "ItemBloodStone",
    [77] = "ItemBluePotion",     [96] = "ItemCrystal",     [82] = "ItemCrystalFlask",     [97] = "ItemCrystalShard",
    [95] = "ItemDarkCrystal",     [87] = "ItemDemonsPick",     [76] = "ItemDragonCrystal",     [105] = "ItemDragonStone",
    [92] = "ItemEarthCrystal",     [74] = "ItemEarthHerb",     [118] = "ItemElfsBolt",     [99] = "ItemElfsKey",
    [83] = "ItemFigureOfSeath",     [90] = "ItemFireCrystal",     [70] = "ItemGoldCoin",     [108] = "ItemGoldKey",
    [80] = "ItemGoldPotion",     [79] = "ItemGreenPotion",     [89] = "ItemGroundBell",     [88] = "ItemHarvinesFlute",
    [104] = "ItemHarvinesKey",     [102] = "ItemJailKey",     [94] = "ItemLightCrystal",     [106] = "ItemMagiciansKey",
    [68] = "ItemMinersMap",     [111] = "ItemMoonGate",     [114] = "ItemMoonKey",     [72] = "ItemMoonStone",
    [69] = "ItemNecronsMap",     [84] = "ItemPhantomRod",     [100] = "ItemPiratesKey",     [67] = "ItemPiratesMap",
    [78] = "ItemRedPotion",     [103] = "ItemRhombusKey",     [86] = "ItemSeathsPlume",     [109] = "ItemShrineKey",
    [107] = "ItemSilverKey",     [101] = "ItemSkullKey",     [112] = "ItemStarGate",     [115] = "ItemStarKey",
    [113] = "ItemSunGate",     [116] = "ItemSunKey",     [85] = "ItemTruthGlass",     [73] = "ItemVerdite",
    [91] = "ItemWaterCrystal",     [93] = "ItemWindCrystal",     [132] = "JailDoor",     [126] = "KnockerDoorLeft",
    [125] = "KnockerDoorRight",     [277] = "Lantern",     [240] = "LoadArea",     [173] = "MadScientistBox",
    [145] = "MadScientistLightCrystalMachine",     [276] = "MadScientistTube",     [203] = "MarbleWallFloorTrap",     [165] = "MineSign",
    [177] = "Minecart",     [151] = "MinersGraveMaybe",     [248] = "Moon",     [245] = "MountainSkybox",
    [247] = "NighttimeSkybox",     [249] = "NighttimeSkybox2",     [255] = "None",     [157] = "PillarOfWind",
    [287] = "RedFlower",     [139] = "RhombusKeyDoor",     [184] = "RhombusKeySlot",     [149] = "SamuraisGrave",
    [230] = "Savepoint",     [133] = "SeathsFountainDoorLeft",     [134] = "SeathsFountainDoorRight",     [191] = "SeathsFountainPillar",
    [130] = "SecretDoor",     [285] = "Shelf",     [40] = "ShieldA",     [37] = "ShieldCrystalGuard",
    [35] = "ShieldLargeShield",     [34] = "ShieldLeatherShield",     [36] = "ShieldMoonGuard",     [39] = "ShieldSeathsShield",
    [38] = "ShieldSkullShield",     [263] = "ShovelAndHammer",     [188] = "ShrineKeySlot",     [158] = "Sign",
    [284] = "SimpleStoolMaybeRENAME_ME",     [185] = "SkullKeySlot",     [204] = "SkullKeyWaterObstacle",     [186] = "SlotForSomethingRENAME_ME",
    [283] = "SmallBed",     [286] = "SmallStackOfLogs",     [136] = "SmallTable",     [274] = "SmallWeirdPillarRENAME_ME",
    [155] = "SomeBrokenGrave",     [156] = "SomeBrokenGrave2",     [211] = "SomeDoorHandleRENAME_ME",     [154] = "SomeGrave",
    [124] = "SquareWell",     [123] = "StoneChestBody",     [122] = "StoneChestLid",     [272] = "StoneGobletWithLavaRENAME_ME",
    [172] = "StonePillar",     [267] = "StoneThing2RENAME_ME",     [268] = "StoneThing3RENAME_ME",     [266] = "StoneThingRENAME_ME",
    [261] = "Stool",     [200] = "SwingingScythe",     [201] = "SwingingSpikeBall",     [257] = "TableWithThingie",
    [171] = "TarnStatue",     [163] = "TheMagiciansLamp",     [152] = "TheSoldiersGrave",     [289] = "ThreeStones",
    [260] = "TinyXFeetTable",     [270] = "Tree",     [193] = "WHATTHEFUCKStatue",     [65535] = "WTF",
    [279] = "WallTorch",     [131] = "WallWithSecret",     [138] = "WallWithSecret2",     [202] = "WallWithSpikeTrap",
    [160] = "WallWriting",     [161] = "WallWriting2",     [162] = "WallWriting3",     [195] = "WaterWell",
    [7] = "WeaponA1",     [8] = "WeaponA2",     [18] = "WeaponA3",     [19] = "WeaponA4",
    [20] = "WeaponA5",     [17] = "WeaponArbalest",     [5] = "WeaponBastardSword",     [4] = "WeaponBattleHammer",
    [16] = "WeaponBow",     [6] = "WeaponCrescentAxe",     [0] = "WeaponDagger",     [15] = "WeaponDarkSlayer",
    [9] = "WeaponFlameSword",     [12] = "WeaponIceBlade",     [2] = "WeaponKnightSword",     [14] = "WeaponMoonlightSword",
    [3] = "WeaponMorningStar",     [13] = "WeaponSeathsSword",     [10] = "WeaponShiden",     [1] = "WeaponShortSword",
    [11] = "WeaponSpider",     [273] = "WeirdPillarRENAME_ME",     [288] = "WhitePinkFlower",     [121] = "WoodenChestBody",
    [120] = "WoodenChestLid",     [182] = "WoodenThingRENAME_ME",     [258] = "XFeetTable"
}

modes = {
    [0] = "Entity Peek", [1] = "Set Entity",
    [2] = "Object Peek", [3] = "Set Object"
}

cursor = { [0] = "", [1] = "_"}

--- Base values
entity_base_addr = 0x16c544
entity_struct_size = 0x7c
object_base_addr = 0x177714
object_struct_size = 0x44
tile_base_addr = 0x801c8484
tile_struct_size = 0xa

--- Global variables
cur_entity = 0
cur_object = 0
cur_mode = 2
draw_player_info = true
new_value_str = ""

--- Internal script stuff
limiter = 5
limit_curframe = 0
cursor_state = 0

function read_entity(address)
    local entity =  "Disabled: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    local meshid = memory.readbyte(address)
    local meshid_str = ""
    if meshids[meshid] == nil then
        meshid_str = "? (" .. meshid .. ")"
    else
        meshid_str = meshids[meshid]
    end

    entity = entity .. "MeshID: " .. meshid_str .. " "
    address = address + 1
    entity = entity .. "EntityClass: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x3: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x4: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x5: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x6: " .. tostring(memory.readbyte(address)) .. "\n"
    address = address + 1
    entity = entity .. "NSYTilePos: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "WEXTilePos: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "Alive: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "xa: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "DroppedItem: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "CurAnim: " .. tostring(memory.readbyte(address)) .. "\n"
    address = address + 1
    entity = entity .. "xd: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "CurrentState: " .. string.format("x%x", memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "CurrentStateDone: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "LastState: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x11: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x12: " .. tostring(memory.readbyte(address)) .. "\n"
    address = address + 1
    entity = entity .. "x13: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x14: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x15: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x16: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x17: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x18: " .. tostring(memory.readword(address)) .. " "
    address = address + 2
    entity = entity .. "HP: " .. tostring(memory.readword(address)) .. " "
    address = address + 2
    entity = entity .. "x1c: " .. tostring(memory.readword(address)) .. " "
    address = address + 2
    entity = entity .. "x1e: " .. tostring(memory.readword(address)) .. "\n"
    address = address + 2
    entity = entity .. "InstanceZRot?: " .. tostring(memory.readword(address)) .. " "
    address = address + 2
    entity = entity .. "ParentIndex: " .. tostring(memory.readword(address)) .. " "
    address = address + 2
    entity = entity .. "FineNSYPos: " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
    entity = entity .. "FineZPos: " .. tostring(memory.readwordsigned(address)) .. "\n"
    address = address + 2
    entity = entity .. "SomeWeirdFlags: " .. tostring(memory.readdword(address)) .. " "
    address = address + 4
    entity = entity .. "Pos:{ x " .. tostring(memory.readdwordsigned(address)) .. " "
    address = address + 4
    entity = entity .. "y " .. tostring(memory.readdwordsigned(address)) .. " "
    address = address + 4
    entity = entity .. "z " .. tostring(memory.readdwordsigned(address)) .. "} "
    address = address + 4
    ---entity = entity .. "Position.pad: " .. tostring(memory.readdwordsigned(address)) .. " "
    address = address + 4
    entity = entity .. "x3c: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x3d: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x3e: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x3f: " .. tostring(memory.readbyte(address)) .. "\n"
    address = address + 1
    entity = entity .. "Rot:{ x " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
    entity = entity .. "y " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
    entity = entity .. "z " .. tostring(memory.readwordsigned(address)) .. "} "
    address = address + 2
    ---entity = entity .. "Rotation.pad: " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
    entity = entity .. "Scale:{ x " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
    entity = entity .. "y " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
    entity = entity .. "z " .. tostring(memory.readwordsigned(address)) .. "}\n"
    address = address + 2
    ---entity = entity .. "Scale.pad: " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
    entity = entity .. "SomeShortVector:{ x " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
    entity = entity .. "y " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
    entity = entity .. "z " .. tostring(memory.readwordsigned(address)) .. "} "
    address = address + 2
    ---entity = entity .. "SomeShortVector.pad: " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
    entity = entity .. "CurrentTurnSpeed: " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
    entity = entity .. "x5a: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x5b: " .. tostring(memory.readbyte(address)) .. "\n"
    address = address + 1
    entity = entity .. "SomePointer: " .. string.format("x%x", memory.readdword(address)) .. " "
    address = address + 4;
    entity = entity .. "StatsPointer: " .. string.format("x%x", memory.readdword(address)) .. " "
    address = address + 4;
    entity = entity .. "x64: " .. tostring(memory.readword(address)) .. " "
    address = address + 2
    entity = entity .. "x66: " .. tostring(memory.readword(address)) .. "\n"
    address = address + 2
    entity = entity .. "x68: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x69: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x6a: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x6b: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x6c: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x6d: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x6e: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x6f: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x70: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x71: " .. tostring(memory.readbyte(address)) .. "\n"
    address = address + 1
    entity = entity .. "x72: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x73: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x74: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x75: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x76: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x77: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x78: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x79: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x7a: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    entity = entity .. "x7b: " .. tostring(memory.readbyte(address)) .. " "
    address = address + 1
    
    return entity
end

function read_object(address)
	local object = string.format("Visible: x%x ", memory.readbyte(address))
	address = address + 1
	object = object .. string.format("x1: x%x ", memory.readbyte(address))
	address = address + 1
	object = object .. string.format("x2: x%x ", memory.readbyte(address))
	address = address + 1
	object = object .. string.format("x3: x%x ", memory.readbyte(address))
	address = address + 1
	object = object .. string.format("x4: x%x ", memory.readbyte(address))
	address = address + 1
	object = object .. string.format("LightingType?: x%x\n", memory.readbyte(address))
	address = address + 1
	
	local objectid = memory.readword(address)
	if objectids[objectid] == nil then
		objectid_str = "? (" .. objectid .. ")"
	else
		objectid_str = objectids[objectid]
	end
	
	object = object .. string.format("ObjectID: %s ", objectid_str)
	address = address + 2
	object = object .. string.format("x8: %u ", memory.readword(address))
	address = address + 2
	object = object .. string.format("xa: %u ", memory.readword(address))
	address = address + 2
	object = object .. string.format("xc: %u ", memory.readword(address))
	address = address + 2
	object = object .. string.format("xe: %u ", memory.readword(address))
	address = address + 2
	object = object .. string.format("x10: %u ", memory.readword(address))
	address = address + 2
	object = object .. string.format("x12: x%x\n", memory.readbyte(address))
	address = address + 1
	object = object .. string.format("x13: x%x ", memory.readbyte(address))
	address = address + 1
    object = object .. string.format("Pos:{ x %d ", memory.readdwordsigned(address))
    address = address + 4
    object = object .. string.format("y %d ", memory.readdwordsigned(address))
    address = address + 4
    object = object .. string.format("z %d} ", memory.readdwordsigned(address))
    address = address + 4
    ---object = object .. "Position.pad: " .. tostring(memory.readdwordsigned(address)) .. " "
    address = address + 4
    object = object .. string.format("Rot:{ x %d ", memory.readwordsigned(address))
    address = address + 2
    object = object .. string.format("y %d ", memory.readwordsigned(address))
    address = address + 2
    object = object .. string.format("z %d}\n", memory.readwordsigned(address))
    address = address + 2
    ---object = object .. "Rotation.pad: " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
    object = object .. string.format("Scale:{ x %d ", memory.readwordsigned(address))
    address = address + 2
    object = object .. string.format("y %d ", memory.readwordsigned(address))
    address = address + 2
    object = object .. string.format("z %d} ", memory.readwordsigned(address))
    address = address + 2
    ---object = object .. "Scale.pad: " .. tostring(memory.readwordsigned(address)) .. " "
    address = address + 2
	object = object .. string.format("x34: x%x ", memory.readbyte(address))
	address = address + 1
	object = object .. string.format("x35: x%x ", memory.readbyte(address))
	address = address + 1
	object = object .. string.format("x36: x%x ", memory.readbyte(address))
	address = address + 1
	object = object .. string.format("x37: x%x\n", memory.readbyte(address))
	address = address + 1
	
	local keyid = memory.readbyte(address)
	if objectids[keyid] == nil then
		keyid_str = "?"
	else
		keyid_str = objectids[keyid]
	end
	
	object = object .. string.format("KeyID: x%x (%s) ", keyid, keyid_str)
	address = address + 1
	object = object .. string.format("x39: x%x ", memory.readbyte(address))
	address = address + 1
	object = object .. string.format("GoldAmount: %u ", memory.readword(address))
	address = address + 2
	object = object .. string.format("x3c: x%x\n", memory.readbyte(address))
	address = address + 1
	object = object .. string.format("x3d: x%x ", memory.readbyte(address))
	address = address + 1
	
	local messageid = memory.readbyte(address)
	if messageids[messageid] == nil then
		messageid_str = "? (" .. messageid .. ")"
	else
		messageid_str = messageids[messageid]
	end
	
	object = object .. string.format("MessageID: x%x ", memory.readbyte(address))
	address = address + 1
	object = object .. string.format("x3f: x%x ", memory.readbyte(address))
	address = address + 1
    object = object .. string.format("Something: x%x ", memory.readdword(address))
    address = address + 4
	
	return object
end

function get_cur_mode_str()
    return "Cur. Mode: " .. modes[cur_mode]
end

function get_player_info()
    local tile = (memory.readdword(0x001d9c84) - tile_base_addr) / tile_struct_size
    local tile_x = tile % 80
    local tile_y = tile / 80
    local player_info = string.format("Player Tile Pos:\nX: %d\nY: %d", tile_x, tile_y)
    return player_info
end

function read_input()
    inputtable = input.get()
    if inputtable["P"] then
        draw_player_info = not draw_player_info
    end
    
    if inputtable["M"] then
		cur_mode = (cur_mode + 2) % (table.getn(modes) + 1)
	end

    if cur_mode == 0 then
        if inputtable["J"] and cur_entity > 0 then
            cur_entity = cur_entity - 1
        elseif inputtable["K"] and cur_entity < 199 then
            cur_entity = cur_entity + 1
        end

        if inputtable["L"] then
            cur_mode = 1
        end
    elseif cur_mode == 1 then
        if inputtable["L"] then
            new_value_str = ""
            cur_mode = 0
        elseif inputtable["backspace"] then
            new_value_str = string.sub(new_value_str, 0, string.len(new_value_str) - 1)
        elseif inputtable["enter"] then
            if string.len(new_value_str) > 0 and tonumber(new_value_str) < 200 then
                cur_entity = tonumber(new_value_str)
            end
            cur_mode = 0
            new_value_str = ""
        elseif string.len(new_value_str) < 3 then
            if inputtable["0"] or inputtable["numpad0"] then
                new_value_str = new_value_str .. "0"
            elseif inputtable["1"] or inputtable["numpad1"] then
                    new_value_str = new_value_str .. "1"
            elseif inputtable["2"] or inputtable["numpad2"] then
                    new_value_str = new_value_str .. "2"
            elseif inputtable["3"] or inputtable["numpad3"] then
                    new_value_str = new_value_str .. "3"
            elseif inputtable["4"] or inputtable["numpad4"] then
                    new_value_str = new_value_str .. "4"
            elseif inputtable["5"] or inputtable["numpad5"] then
                    new_value_str = new_value_str .. "5"
            elseif inputtable["6"] or inputtable["numpad6"] then
                    new_value_str = new_value_str .. "6"
            elseif inputtable["7"] or inputtable["numpad7"] then
                    new_value_str = new_value_str .. "7"
            elseif inputtable["8"] or inputtable["numpad8"] then
                    new_value_str = new_value_str .. "8"
            elseif inputtable["9"] or inputtable["numpad9"] then
                    new_value_str = new_value_str .. "9"
            end
        end
    elseif cur_mode == 2 then
        if inputtable["J"] and cur_object > 0 then
            cur_object = cur_object - 1
        elseif inputtable["K"] and cur_object < 349 then
            cur_object = cur_object + 1
        end

        if inputtable["L"] then
            cur_mode = 3
        end
    elseif cur_mode == 3 then
        if inputtable["L"] then
            new_value_str = ""
            cur_mode = 2
        elseif inputtable["backspace"] then
            new_value_str = string.sub(new_value_str, 0, string.len(new_value_str) - 1)
        elseif inputtable["enter"] then
            if string.len(new_value_str) > 0 and tonumber(new_value_str) < 350 then
                cur_object = tonumber(new_value_str)
            end
            cur_mode = 2
            new_value_str = ""
        elseif string.len(new_value_str) < 3 then
            if inputtable["0"] or inputtable["numpad0"] then
                new_value_str = new_value_str .. "0"
            elseif inputtable["1"] or inputtable["numpad1"] then
                    new_value_str = new_value_str .. "1"
            elseif inputtable["2"] or inputtable["numpad2"] then
                    new_value_str = new_value_str .. "2"
            elseif inputtable["3"] or inputtable["numpad3"] then
                    new_value_str = new_value_str .. "3"
            elseif inputtable["4"] or inputtable["numpad4"] then
                    new_value_str = new_value_str .. "4"
            elseif inputtable["5"] or inputtable["numpad5"] then
                    new_value_str = new_value_str .. "5"
            elseif inputtable["6"] or inputtable["numpad6"] then
                    new_value_str = new_value_str .. "6"
            elseif inputtable["7"] or inputtable["numpad7"] then
                    new_value_str = new_value_str .. "7"
            elseif inputtable["8"] or inputtable["numpad8"] then
                    new_value_str = new_value_str .. "8"
            elseif inputtable["9"] or inputtable["numpad9"] then
                    new_value_str = new_value_str .. "9"
            end
        end
    end
end

function ui_kf()
    --- Check for input (if allowed)
    limit_curframe = (limit_curframe + 1) % limiter
    if limit_curframe == 0 then
        cursor_state = math.fmod(cursor_state + 1, 2)
        read_input()
    end

    if draw_player_info then
        gui.text(248, 240 - 32, get_player_info())
    end

    if cur_mode == 0 then
		cur_entity_addr = entity_base_addr + (cur_entity * entity_struct_size)
		local entity = read_entity(cur_entity_addr)
        gui.text(0, 0, "Entity " .. tostring(cur_entity) .. " (0x80" .. string.format("%x", cur_entity_addr) .. ")\n" .. entity)
    elseif cur_mode == 1 then
        gui.text(0, 0, "Set Entity: " .. new_value_str .. cursor[cursor_state])
    elseif cur_mode == 2 then
		cur_object_addr = object_base_addr + (cur_object * object_struct_size)
		local object = read_object(cur_object_addr)
        gui.text(0, 0, string.format("Object %d (0x%x)\n%s", cur_object, cur_object_addr, object))
    elseif cur_mode == 3 then
        gui.text(0, 0, "Set Object: " .. new_value_str .. cursor[cursor_state])
    end
    gui.text(0, 232, get_cur_mode_str())
end

gui.register(ui_kf)
