local config = {
    actionId = 18562, -- on lever
    lever = {
        left = 2772,
        right = 2773
    },
    playItem = {
        itemId = 22722, -- item required to pull lever
        count = 1
    },
    rouletteOptions = {
        rareItemChance_broadcastThreshold = 500,
        ignoredItems = {1617}, -- if you have tables/counters/other items on the roulette tiles, add them here
        winEffects = {CONST_ANI_FIRE, CONST_ME_SOUND_YELLOW, CONST_ME_SOUND_PURPLE, CONST_ME_SOUND_BLUE, CONST_ME_SOUND_WHITE}, -- first effect needs to be distance effect
        effectDelay = 333,
        spinTime = {min = 8, max = 12}, -- seconds
        spinSlowdownRamping = 5,
        rouletteStorage = 48550 -- required storage to avoid player abuse (if they logout/die before roulette finishes.. they can spin again for free)
    },
    prizePool = {
        {itemId = 3043, count = {25, 50},   chance = 2000}, -- {itemId = itemid, count = {min, max}, chance = chance/10000} (crystal coins)
        {itemId = 22722, count = {1, 1},    chance = 2000 }, -- tigrinho token
        {itemId = 36725, count = {1, 1},    chance = 2000 }, -- stamina extension
 	{itemId = 43946, count = {1, 1},    chance = 2000 }, -- abridged promotion scroll
        {itemId = 20271, count = {1, 1},    chance = 1000 }, -- copper prison key
        {itemId = 20270, count = {1, 1},   chance = 1000}, -- silver prison key
        {itemId = 20272, count = {1, 1},   chance = 1000}, -- bronze prison key
        {itemId = 20273, count = {1, 1},    chance = 1000 }, -- golden prison key
	{itemId = 43947, count = {1, 1},    chance = 1000 }, -- basic promotion scroll
        {itemId = 28484, count = {2, 5},    chance = 900 }, -- blueberry cupcake
        {itemId = 28485, count = {2, 5},    chance = 900 }, -- strawberry cupcake
        {itemId = 16244, count = {1, 1},   chance = 900 }, -- music box
        {itemId = 43948, count = {1, 1},   chance = 900 }, -- revised promotion scroll
        {itemId = 3555, count = {1, 1},    chance = 750 },  -- golden boots
        {itemId = 28571, count = {1, 1}, chance = 750 },  -- book backpack
        {itemId = 39693, count = {1, 1}, chance = 750 },  -- 25 years backpack
        {itemId = 14674, count = {1, 1}, chance = 750 },  -- aniversary backpack
        {itemId = 23685, count = {1, 1},    chance = 500  }, -- menacing egg 
        {itemId = 28791, count = {1, 1},    chance = 500  },  -- library ticket
        {itemId = 37745, count = {1, 1},    chance = 500  },  -- draptor doll
        {itemId = 43950, count = {1, 1},    chance = 500  },  -- advanced promotion scroll
        {itemId = 39546, count = {1, 1},    chance = 300 }, -- primal bag
        {itemId = 43895, count = {1, 1},    chance = 300  },  -- sanguine bag
        {itemId = 23684, count = {1, 1},    chance = 300  },  -- crackling egg
        {itemId = 43949, count = {1, 1},    chance = 300  },  -- extended promotion scroll
        {itemId = 34109, count = {1, 1},    chance = 300 }, -- bag you desire
        {itemId = 3365, count = {1, 1},    chance = 200  },  -- golden helmet 
        {itemId = 5903, count = {1, 1},    chance = 100  },  -- ferumbras hat   
        {itemId = 22865, count = {1, 1},    chance = 100  },  -- mysterious scroll
    },
    roulettePositions = { -- hard-coded to 7 positions.
        Position(1102, 1062, 3),
        Position(1103, 1062, 3),
        Position(1104, 1062, 3),
        Position(1105, 1062, 3), -- position 4 in this list is hard-coded to be the reward location, which is the item given to the player
        Position(1106, 1062, 3),
        Position(1107, 1062, 3),
        Position(1108, 1062, 3),
        Position(1109, 1062, 3),
        Position(1110, 1062, 3),
    }
}

local chancedItems = {} -- used for broadcast. don't edit

local function resetLever(position)
    local lever = Tile(position):getItemById(config.lever.right)
    lever:transform(config.lever.left)
end

local function updateRoulette(newItemInfo)
    local positions = config.roulettePositions
    for i = #positions, 1, -1 do
        local item = Tile(positions[i]):getTopVisibleThing()
        if item and item:getId() ~= Tile(positions[i]):getGround():getId() and not table.contains(config.rouletteOptions.ignoredItems, item:getId()) then
            if i ~= 9 then
                item:moveTo(positions[i + 1])
            else
                item:remove()
            end
        end
    end
    if ItemType(newItemInfo.itemId):getCharges() then
        local item = Game.createItem(newItemInfo.itemId, 1, positions[1])
        item:setAttribute("charges", newItemInfo.count)
    else
        Game.createItem(newItemInfo.itemId, newItemInfo.count, positions[1])
    end
end

local function clearRoulette(newItemInfo)
    local positions = config.roulettePositions
    for i = #positions, 1, -1 do
        local item = Tile(positions[i]):getTopVisibleThing()
        if item and item:getId() ~= Tile(positions[i]):getGround():getId() and not table.contains(config.rouletteOptions.ignoredItems, item:getId()) then
            item:remove()
        end
        if newItemInfo == nil then
            positions[i]:sendMagicEffect(CONST_ME_POFF)
        else
            if ItemType(newItemInfo.itemId):getCharges() then
                local item = Game.createItem(newItemInfo.itemId, 1, positions[i])
                item:setAttribute("charges", newItemInfo.count)
            else
                Game.createItem(newItemInfo.itemId, newItemInfo.count, positions[i])
            end
        end
    end
end

local function chanceNewReward()
    local newItemInfo = {itemId = 0, count = 0}
    
    local rewardTable = {}
    while #rewardTable < 1 do
        for i = 1, #config.prizePool do
            if config.prizePool[i].chance >= math.random(10000) then
                rewardTable[#rewardTable + 1] = i
            end
        end
    end
    
    local rand = math.random(#rewardTable)
    newItemInfo.itemId = config.prizePool[rewardTable[rand]].itemId
    newItemInfo.count = math.random(config.prizePool[rewardTable[rand]].count[1], config.prizePool[rewardTable[rand]].count[2])
    chancedItems[#chancedItems + 1] = config.prizePool[rewardTable[rand]].chance
    
    return newItemInfo
end

local function initiateReward(leverPosition, effectCounter)
    if effectCounter < #config.rouletteOptions.winEffects then
        effectCounter = effectCounter + 1
        if effectCounter == 1 then
            config.roulettePositions[1]:sendDistanceEffect(config.roulettePositions[4], config.rouletteOptions.winEffects[1])
            config.roulettePositions[7]:sendDistanceEffect(config.roulettePositions[4], config.rouletteOptions.winEffects[1])
        else
            for i = 1, #config.roulettePositions do
                config.roulettePositions[i]:sendMagicEffect(config.rouletteOptions.winEffects[effectCounter])
            end
        end
        if effectCounter == 2 then
            local item = Tile(config.roulettePositions[4]):getTopVisibleThing()
            local newItemInfo = {itemId = item:getId(), count = item:getCount()}
            clearRoulette(newItemInfo)
        end
        addEvent(initiateReward, config.rouletteOptions.effectDelay, leverPosition, effectCounter)
        return
    end
    resetLever(leverPosition)
end

local function rewardPlayer(playerId, leverPosition)
    local player = Player(playerId)
    if not player then
        return
    end
    
    local item = Tile(config.roulettePositions[4]):getTopVisibleThing()
    
    if ItemType(item:getId()):getCharges() then
        local addedItem = player:addItem(item:getId(), 1, true)
        addedItem:setAttribute("charges", item:getCharges())
    else
        player:addItem(item:getId(), item:getCount(), true)
    end

    player:setStorageValue(config.rouletteOptions.rouletteStorage, -1)
    if chancedItems[#chancedItems - 5] <= config.rouletteOptions.rareItemChance_broadcastThreshold then
        Game.broadcastMessage("The player " .. player:getName() .. " has won " .. item:getName() .. " from the roulette!", MESSAGE_EVENT_ADVANCE)
    end
end

local function roulette(playerId, leverPosition, spinTimeRemaining, spinDelay)
    local player = Player(playerId)
    if not player then
        resetLever(leverPosition)
        return
    end
    
    local newItemInfo = chanceNewReward()
    updateRoulette(newItemInfo)
    
    if spinTimeRemaining > 0 then
        spinDelay = spinDelay + config.rouletteOptions.spinSlowdownRamping
        addEvent(roulette, spinDelay, playerId, leverPosition, spinTimeRemaining - (spinDelay - config.rouletteOptions.spinSlowdownRamping), spinDelay)
        return
    end
    
    initiateReward(leverPosition, 0)
    rewardPlayer(playerId, leverPosition)
end

local casinoRoulette = Action()

function casinoRoulette.onUse(player, item, fromPosition, target, toPosition, isHotkey)
    if item:getId() == config.lever.right then
        player:sendTextMessage(MESSAGE_FAILURE, "Casino Roulette is currently in progress. Please wait.")
        return true
    end
    
    if player:getItemCount(config.playItem.itemId) < config.playItem.count then
        if player:getStorageValue(config.rouletteOptions.rouletteStorage) < 1 then
            player:sendTextMessage(MESSAGE_FAILURE, "Casino Roulette requires " .. config.playItem.count .. " " .. (ItemType(config.playItem.itemId):getName()) .. " to use.")
            return true
        end
        -- player:sendTextMessage(MESSAGE_STATUS_SMALL, "Free Spin being used due to a previous unforeseen error.")
    end
    
    item:transform(config.lever.right)
    clearRoulette()
    chancedItems = {}
    
    player:removeItem(config.playItem.itemId, config.playItem.count)
    player:setStorageValue(config.rouletteOptions.rouletteStorage, 1)
    
    local spinTimeRemaining = math.random((config.rouletteOptions.spinTime.min * 1000), (config.rouletteOptions.spinTime.max * 1000))
    roulette(player:getId(), toPosition, spinTimeRemaining, 100)
    return true
end

casinoRoulette:aid(config.actionId)
casinoRoulette:register()


local disableMovingItemsToRoulettePositions = MoveEvent()

disableMovingItemsToRoulettePositions.onAddItem = function(moveitem, tileitem, position, item, count, fromPosition, toPosition)
    for v, k in pairs(config.roulettePositions) do
        if toPosition == k then
            return false
        end
    end
    return true
end

disableMovingItemsToRoulettePositions:position(config.roulettePositions)
disableMovingItemsToRoulettePositions:register()