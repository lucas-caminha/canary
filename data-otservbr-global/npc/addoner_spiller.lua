local internalNpcName = "Moyen"
local npcType = Game.createNpcType(internalNpcName)
local npcConfig = {}

npcConfig.name = internalNpcName
npcConfig.description = internalNpcName

npcConfig.health = 100
npcConfig.maxHealth = npcConfig.health
npcConfig.walkInterval = 2000
npcConfig.walkRadius = 2

npcConfig.outfit = {
	lookType = 130,
	lookHead = 10,
	lookBody = 70,
	lookLegs = 87,
	lookFeet = 95,
	lookAddons = 3,
}

npcConfig.flags = {
	floorchange = false
}

npcConfig.voices = {
	interval = 15000,
	chance = 50,
	{text = 'Come see my Addons bro!'}
}

local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)

npcType.onThink = function(npc, interval)
	npcHandler:onThink(npc, interval)
end

npcType.onAppear = function(npc, creature)
	npcHandler:onAppear(npc, creature)
end

npcType.onDisappear = function(npc, creature)
	npcHandler:onDisappear(npc, creature)
end

npcType.onMove = function(npc, creature, fromPosition, toPosition)
	npcHandler:onMove(npc, creature, fromPosition, toPosition)
end

npcType.onSay = function(npc, creature, type, message)
	npcHandler:onSay(npc, creature, type, message)
end

npcType.onCloseChannel = function(npc, creature)
	npcHandler:onCloseChannel(npc, creature)
end

addonreq = {

['first citizen addon'] = {cost = 0, items = {{5878,100}}, outfit_female = 136, outfit_male = 128, addon = 1},
['second citizen addon'] = {cost = 0, items = {{5890,50}, {5902,25}, {3374,1}}, outfit_female = 136, outfit_male = 128, addon = 2},
['first hunter addon'] = {cost = 0, items = {{5876,100}, {5948,100}, {5891,5}, {5887,1}, {5889,1}, {5888,1}}, outfit_female = 137, outfit_male = 129, addon = 1},
['second hunter addon'] = {cost = 0, items = {{5875,1}}, outfit_female = 137, outfit_male = 129, addon = 2},
['first knight addon'] = {cost = 0, items = {{5880,100}, {5892,1}}, outfit_female = 139, outfit_male = 131, addon = 1},
['second knight addon'] = {cost = 0, items = {{5893,100}, {5924,1}, {5885,1}, {5887,1}}, outfit_female = 139, outfit_male = 131, addon = 2},
['first mage addon'] = {cost = 0, items = {{3074,1}, {3075,1}, {3072,1}, {3073,1}, {3071,1}, {3066,1}, {3070,1}, {3069,1}, {3065,1}, {3067,1}, {5904,10}, {3077,20}, {5809,1}}, outfit_female = 138, outfit_male = 130, addon = 1},
['second mage male addon'] = {cost = 0, items = {{5903,1}}, outfit_female = 130, outfit_male = 130, addon = 2},
['second mage female addon'] = {cost = 0, items = {{5894,70}, {5911,20}, {5883,40}, {5922,35}, {5879,10}, {5881,60}, {5882,40}, {5904,15}, {5905,30}}, outfit_female = 138, outfit_male = 138, addon = 2},
['first summoner addon'] = {cost = 0, items = {{5958,1}}, outfit_female = 141, outfit_male = 133, addon = 1},
['second summoner male addon'] = {cost = 0, items = {{5894,70}, {5911,20}, {5883,40}, {5922,35}, {5879,10}, {5881,60}, {5882,40}, {5904,15}, {5905,30}}, outfit_female = 133, outfit_male = 133, addon = 2},
['second summoner female addon'] = {cost = 0, items = {{5903,1}}, outfit_female = 141, outfit_male = 141, addon = 2},
['first barbarian addon'] = {cost = 0, items = {{5880,100}, {5892,1}, {5893,50}, {5876,50}}, outfit_female = 147, outfit_male = 143, addon = 1, storageID = 51032},
['second barbarian addon'] = {cost = 0, items = {{5884,1}, {5885,1}, {5910,50}, {5911,50}, {5879,10}}, outfit_female = 147, outfit_male = 143, addon = 2},
['first druid addon'] = {cost = 0, items = {{5896,50}, {5897,50}}, outfit_female = 148, outfit_male = 144, addon = 1},
['second druid addon'] = {cost = 0, items = {{5906,100}}, outfit_female = 148, outfit_male = 144, addon = 2},
['first nobleman addon'] = {cost = 150000, items = {}, outfit_female = 140, outfit_male = 132, addon = 1},
['second nobleman addon'] = {cost = 150000, items = {}, outfit_female = 140, outfit_male = 132, addon = 2},
['first oriental addon'] = {cost = 0, items = {{5945,1}}, outfit_female = 150, outfit_male = 146, addon = 1},
['second oriental addon'] = {cost = 0, items = {{5883,100}, {5895,100}, {5891,2}, {5912,100}}, outfit_female = 150, outfit_male = 146, addon = 2},
['first warrior addon'] = {cost = 0, items = {{5925,100}, {5899,100}, {5884,1}, {5919,1}}, outfit_female = 142, outfit_male = 134, addon = 1},
['second warrior addon'] = {cost = 0, items = {{5880,100}, {5887,1}}, outfit_female = 142, outfit_male = 134, addon = 2},
['first wizard addon'] = {cost = 0, items = {{5922,50}}, outfit_female = 149, outfit_male = 145, addon = 1},
['second wizard addon'] = {cost = 0, items = {{3436,1}, {3386,1}, {3382,1}, {3006,1}}, outfit_female = 149, outfit_male = 145, addon = 2},
['first assassin addon'] = {cost = 0, items = {{5912,50}, {5910,50}, {5911,50}, {5913,50}, {5914,50}, {5909,50}, {5879,10}}, outfit_female = 156, outfit_male = 152, addon = 1},
['second assassin addon'] = {cost = 0, items = {{5804,1}, {5930,1}}, outfit_female = 156, outfit_male = 152, addon = 2},
['first beggar addon'] = {cost = 0, items = {{5878,50}, {5921,30}, {5913,20}, {5894,10}, {5883,100}}, outfit_female = 157, outfit_male = 153, addon = 1},
['second beggar addon'] = {cost = 0, items = {{6107,1}}, outfit_female = 157, outfit_male = 153, addon = 2},
['first pirate addon'] = {cost = 0, items = {{6098,100}, {6126,100}, {6097,100}}, outfit_female = 155, outfit_male = 151, addon = 1},
['second pirate addon'] = {cost = 0, items = {{6101,1}, {6102,1}, {6100,1}, {6099,1}}, outfit_female = 155, outfit_male = 151, addon = 2},
['first shaman addon'] = {cost = 0, items = {{3348,5}, {3403,5}}, outfit_female = 158, outfit_male = 154, addon = 1},
['second shaman addon'] = {cost = 0, items = {{5014,1}, {3002,5}}, outfit_female = 158, outfit_male = 154, addon = 2},
['first norseman addon'] = {cost = 0, items = {{7290,5}}, outfit_female = 252, outfit_male = 251, addon = 1},
['second norseman addon'] = {cost = 0, items = {{7290,10}}, outfit_female = 252, outfit_male = 251, addon = 2},
['first nightmare addon'] = {cost = 0, items = {{6499,500}}, outfit_female = 269, outfit_male = 268, addon = 1},
['second nightmare addon'] = {cost = 0, items = {{6499,1000}}, outfit_female = 269, outfit_male = 268, addon = 2},
['first brotherhood addon'] = {cost = 0, items = {{6499,500}}, outfit_female = 279, outfit_male = 278, addon = 1},
['second brotherhood addon'] = {cost = 0, items = {{6499,1000}}, outfit_female = 279, outfit_male = 278, addon = 2},
['first rootwalker addon'] = {cost = 0, items = {{20198,100}, {48250,100}, {48254,100}, {48256,100}}, outfit_female = 1775, outfit_male = 1774, addon = 1},
['second rootwalker addon'] = {cost = 0, items = {{45639,1}, {48116,100}, {6393,100}}, outfit_female = 1775, outfit_male = 1774, addon = 2},
['first draccoon addon'] = {cost = 0, items = {{44754,1}}, outfit_female = 1723, outfit_male = 1722, addon = 1},
['second draccoon addon'] = {cost = 0, items = {{44753,1}}, outfit_female = 1723, outfit_male = 1722, addon = 2},
['first deepling addon'] = {cost = 0, items = {{14174,1}, {14173,1}, {14175,1}}, outfit_female = 464, outfit_male = 463, addon = 1},
['second deepling addon'] = {cost = 0, items = {{14021,1}, {14022,1}, {14023,1}, {14019,1}}, outfit_female = 464, outfit_male = 463, addon = 2}

}
local o = {'citizen', 'hunter', 'knight', 'mage', 'nobleman', 'summoner', 'warrior', 'barbarian', 'druid', 'wizard', 'oriental', 'pirate', 'assassin', 'beggar', 'shaman', 'norseman', 'nightmare', 'brotherhood', 'rootwalker', 'draccoon', 'deepling'}
local rtnt = {}
local function creatureSayCallback(npc, creature, type, message)
local talkUser = creature
local player = Player(creature)
local playerId = player:getId()

local talkState = {}
    if not npcHandler:checkInteraction(npc, creature) then
		return false
	end

    if addonreq[message] ~= nil then
        local itemsTable = addonreq[message].items
        local items_list = ''
       if table.maxn(itemsTable) > 0 then
            for i = 1, table.maxn(itemsTable) do
                local item = itemsTable[i]
                items_list = items_list .. item[2] .. ' ' .. ItemType(item[1]):getName()
                if i ~= table.maxn(itemsTable) then
                    items_list = items_list .. ', '
                end
            end
        end
        local text = ''
        if (addonreq[message].cost > 0) then
            text = addonreq[message].cost .. ' gp'
        elseif table.maxn(addonreq[message].items) then
            text = items_list
        elseif (addonreq[message].cost > 0) and table.maxn(addonreq[message].items) then
            text = items_list .. ' and ' .. addonreq[message].cost .. ' gp'
        end
        npcHandler:say('For ' .. message .. ' you will need ' .. text .. '. Do you have it all with you?', npc, creature)
        rtnt = message
        talkState[talkUser] = addonreq[message].storageID
        npcHandler:setTopic(playerId, 2)
        return true
    elseif npcHandler:getTopic(playerId) == 2 then
        if MsgContains(message, "yes") then
            local items_number = 0
            if table.maxn(addonreq[rtnt].items) > 0 then
                for i = 1, table.maxn(addonreq[rtnt].items) do
                    local item = addonreq[rtnt].items[i]
                    if (getPlayerItemCount(creature,item[1]) >= item[2]) then
                        items_number = items_number + 1
                    end
                end
            end
            if(getPlayerMoney(creature) >= addonreq[rtnt].cost) and (items_number == table.maxn(addonreq[rtnt].items)) then
                doPlayerRemoveMoney(creature, addonreq[rtnt].cost)
                if table.maxn(addonreq[rtnt].items) > 0 then
                    for i = 1, table.maxn(addonreq[rtnt].items) do
                        local item = addonreq[rtnt].items[i]
                        doPlayerRemoveItem(creature,item[1],item[2])
                    end
                end
                doPlayerAddOutfit(creature, addonreq[rtnt].outfit_male, addonreq[rtnt].addon)
                doPlayerAddOutfit(creature, addonreq[rtnt].outfit_female, addonreq[rtnt].addon)
                npcHandler:say('Here you are.', npc, creature)
            else
                npcHandler:say('You do not have needed items!', npc, creature)
            end
            rtnt = nil
            talkState[talkUser] = 0
            npcHandler:resetNpc(creature)
            return true
        end
    elseif MsgContains(message, "addon") then
        npcHandler:say('I can give you {first} or {second} addons for {' .. table.concat(o, "}, {") .. '} outfits.', npc, creature)
        rtnt = nil
        talkState[talkUser] = 0
        npcHandler:resetNpc(creature)
        return true
    elseif MsgContains(message, "help") then
        npcHandler:say('You must say \'first NAME addon\', for the first addon or \'second NAME addon\' for the second.', npc, creature)
        rtnt = nil
        talkState[talkUser] = 0
        npcHandler:resetNpc(creature)
        return true
    else
        if talkState[talkUser] ~= nil then
            if talkState[talkUser] > 0 then
            npcHandler:say('Come back when you get these items.', npc, creature)
            rtnt = nil
            talkState[talkUser] = 0
            npcHandler:resetNpc(creature)
            return true
            end
        end
    end
    return true
end

npcHandler:setMessage(MESSAGE_GREET, 'Welcome |PLAYERNAME|! If you want some addons, just ask me! Do you want to see my {addons}, or are you decided? If you are decided, just ask me like this: {first citizen addon}')
npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new(), npcConfig.name, true, true, true)
npcType:register(npcConfig)
