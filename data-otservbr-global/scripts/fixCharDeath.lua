--[[
  _             _____ _  __
 | |    ___  __|_   _| |/ /
 | |   / _ \/ _ \| | | ' / 
 | |__|  __/ (_) | | | . \ 
 |_____\___|\___/|_| |_|\_\
                           
TKDev Community: https://discord.gg/phJZeHa2k4
]]

local config = {
    kv = "fixDeathKV",
    stepKv = "stepDeathKV",
    time = 3,
    templePos = {
        Position(32069, 31901, 6), -- Dawnport Tutorial
        Position(32064, 31894, 6), -- Dawnport
        Position(32097, 32219, 7), -- Rookgaard
        Position(32091, 32027, 7), -- Island of Destiny
        Position(32732, 31634, 7), -- Ab'Dendriel
        Position(32360, 31782, 7), -- Carlin
        Position(32649, 31925, 11), -- Kazordoon
        Position(32369, 32241, 7), -- Thais
        Position(32957, 32076, 7), -- Venore
        Position(33194, 32853, 8), -- Ankrahmun
        Position(33217, 31814, 8), -- Edron
        Position(33023, 31521, 11), -- Farmine
        Position(33213, 32454, 1), -- Darashia
        Position(32317, 32826, 7), -- Liberty Bay
        Position(32594, 32745, 7), -- Port Hope
        Position(32212, 31132, 7), -- Svargrond
        Position(32787, 31276, 7), -- Yalahar
        Position(33447, 31323, 9), -- Gray Beach
        Position(33657, 31665, 8), -- Krailos
        Position(33594, 31899, 6), -- Rathleton
        Position(33513, 32363, 6), -- Roshamuul
        Position(33921, 31477, 5), -- Issavi
    }
}

local charDeath = CreatureEvent("CharDeath")

function charDeath.onDeath(player, corpse, killer, mostDamageKiller, unjustified, mostDamageUnjustified)
    if not player then
        return true
    end
    local playerKV = player:kv()
    local deathTime = os.time()
    playerKV:set(config.kv, deathTime)
    playerKV:set(config.stepKv, 1)
    return true
end

charDeath:register()

local charLogin = CreatureEvent("CharLogin")

function charLogin.onLogin(player)
    player:registerEvent("CharDeath")
    local playerKV = player:kv()
    local deathTime = tonumber(playerKV:get(config.kv)) or 0
    local currentTime = os.time()
    if deathTime > 0 and (currentTime - deathTime) < config.time then
        local remainingTime = config.time - (currentTime - deathTime)
        return false
    end
    playerKV:set(config.kv, 0)
    return true
end

charLogin:register()

local charStepIn = MoveEvent()
function charStepIn.onStepIn(creature, item, position, fromPosition)
    local player = creature:getPlayer()
    if not player then
        return false
    end
    local playerKV = player:kv()
    local stepKv = tonumber(playerKV:get(config.stepKv)) or 0
    if stepKv > 0 then
        playerKV:set(config.stepKv, 0)
        addEvent(function()
            if not player then
                return true
            end
            player:remove()
        end, 500)
    end
    return true
end

charStepIn:type("stepin")
for _, pos in ipairs(config.templePos) do
    charStepIn:position(pos)
end

charStepIn:register()