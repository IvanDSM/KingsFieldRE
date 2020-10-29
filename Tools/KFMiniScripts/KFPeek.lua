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

modes = {
    [0] = "Entity Peek", [1] = "Set Entity"
}

cursor = { [0] = "", [1] = "_"}

--- Base values
entity_struct_size = 0x7c
entity_base_addr = 0x16c544
tile_struct_size = 0xa
tile_base_addr = 0x801c8484

--- Global variables
cur_entity = 0
cur_mode = 0
draw_player_info = true
new_value_str = ""

--- Internal script stuff
limiter = 5
limit_curframe = 0
cursor_state = 0

function read_entity(address)
    local entity = ""
    entity = entity .. "Disabled: " .. tostring(memory.readbyte(address)) .. " "
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
    end
end

function ui_kf()
    --- Check for input (if allowed)
    limit_curframe = (limit_curframe + 1) % limiter
    if limit_curframe == 0 then
        cursor_state = math.fmod(cursor_state + 1, 2)
        read_input()
    end

    --- Entity part

    cur_entity_addr = entity_base_addr + (cur_entity * entity_struct_size)

    local entity = read_entity(cur_entity_addr)

    if draw_player_info then
        gui.text(248, 240 - 32, get_player_info())
    end

    if cur_mode == 0 then
        gui.text(0, 0, "Entity " .. tostring(cur_entity) .. " (0x80" .. string.format("%x", cur_entity_addr) .. ")\n" .. entity)
    elseif cur_mode == 1 then
        gui.text(0, 0, "Set Entity: " .. new_value_str .. cursor[cursor_state])
    end
    gui.text(0, 232, get_cur_mode_str())
end

gui.register(ui_kf)