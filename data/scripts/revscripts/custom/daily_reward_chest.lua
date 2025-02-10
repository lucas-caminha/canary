local config = {
	storage = 60060, -- Storage para verificar se o jogador pode pegar novamente.
	actionId = 12345, -- action id do baú.
	timeToReward = 24, -- Tempo em horas pra pegar o bau novamente.
	itemsList = {	
		{id = 3043, count = 20, chance = 10}, -- crystal coin
		{id = 29425, count = 1, chance = 10}, -- energized limb
		{id = 32616, count = 1, chance = 10}, -- phantasmal axe
		{id = 31580, count = 1, chance = 10}, -- mortal mace 
		{id = 31614, count = 1, chance = 10}, -- tagralt blade 
		{id = 27651, count = 1, chance = 10}, -- gnome sword
		{id = 28825, count = 1, chance = 10}, -- deepling ceremonial dagger
		{id = 28826, count = 1, chance = 10}, -- deepling fork
		{id = 30393, count = 1, chance = 10}, -- cobra crossbow
		{id = 30395, count = 1, chance = 10}, -- cobra club
		{id = 30396, count = 1, chance = 10}, -- cobra axe
		{id = 30398, count = 1, chance = 10}, -- cobra sword
		{id = 30399, count = 1, chance = 10}, -- cobra wand
		{id = 30400, count = 1, chance = 10}, -- cobra rod
		{id = 39159, count = 1, chance = 10}, -- naga crossbow
		{id = 39157, count = 1, chance = 10}, -- naga club
		{id = 39156, count = 1, chance = 10}, -- naga axe
		{id = 39155, count = 1, chance = 10}, -- naga sword
		{id = 39162, count = 1, chance = 10}, -- naga wand
		{id = 39163, count = 1, chance = 10}, -- naga rod
		{id = 34150, count = 1, chance = 10}, -- lion longbow
		{id = 34254, count = 1, chance = 10}, -- lion hammer
		{id = 34253, count = 1, chance = 10}, -- lion axe
		{id = 34155, count = 1, chance = 10}, -- lion sword
		{id = 34152, count = 1, chance = 10}, -- lion wand
		{id = 34151, count = 1, chance = 10}, -- lion rod
	},
}

local function generateItemList()
	local finalList = {}
	for _, item in ipairs(config.itemsList) do
		local itemRand = math.random(100) -- random chance for each individual item listed in the list
		if itemRand <= item.chance then
			finalList[#finalList + 1] = item -- insert item into a new index of finalList
		end
	end
	return finalList
end

local function getMinutes(seconds)
	return math.floor(seconds/60)
end

local rewardChest = Action()

function rewardChest.onUse(player, item, fromPosition, target, toPosition, isHotkey)
	local generateList = generateItemList()
	while #generateList == 0 do
		generateList = generateItemList()
	end

	if player:getLevel() < 150 then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, string.format('Voce precisa ser level 150 ou superior para pegar sua recompensa'))
		return false;
	end

	if player:getStorageValue(config.storage) > os.time() then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, string.format("Voce precisa esperar %d horas para pegar sua recompensa!", (getMinutes(player:getStorageValue(config.storage) - os.time()) / 60)))
		return false
	end

	for _, item in ipairs(generateList) do
		if player:addItem(item.id, item.count) then
			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, string.format('Parabens, voce recebeu um(a) %d %s(s).', item.count, ItemType(item.id):getName()))
			player:setStorageValue(config.storage, os.time() + config.timeToReward * 60 * 60)
			return true
		end
	end

	return true
end

rewardChest:aid(config.actionId)
rewardChest:register()
