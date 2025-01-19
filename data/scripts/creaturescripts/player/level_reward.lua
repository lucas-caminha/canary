local table = 
{
	-- [level] = type = "item", id = {ITEM_ID, QUANTITY}, msg = "MESSAGE"},
	-- [level] = type = "bank", id = {QUANTITY, 0}, msg = "MESSAGE"},
	-- [level] = type = "addon", id = {ID_ADDON_FEMALE, ID_ADDON_MALE}, msg = "MESSAGE"},
	-- [level] = type = "coin", id = {QUANTITY, 0}, msg = "MESSAGE"},
	-- [level] = type = "mount", id = {ID_MOUNT, 0}, msg = "MESSAGE"},

	[20] = {type = "item", id = {3043, 3}, msg = "Receba 3 crystal coins por atingir o level 20!"},
	[50] = {type = "bank", id = {50000, 0}, msg = "Depositamos 50000 gold coins em sua conta por atingir o level 50!"},
	[75] = {type = "bank", id = {100000, 0}, msg = "Depositamos 100000 gold coins em sua conta por atingir o level 75!"},
	[100] = {type = "addon", id = {136, 128}, msg = "Receba o Citizen addon completo por atingir o level 100!"},
	[125] = {type = "bank", id = {100000, 0}, msg = "Depositamos 100000 gold coins em sua conta por atingir o level 125!"},
	[150] = {type = "mount", id = {170, 0}, msg = "Receba uma montaria por atingir o level 150!"},
	[175] = {type = "bank", id = {100000, 0}, msg = "Depositamos 100000 gold coins em sua conta por atingir o level 175!"},
        [200] = {type = "item", id = {36728, 2}, msg = "Receba 2 Bestiary betterment por atingir o level 200!"},
        [250] = {type = "item", id = {22722, 1}, msg = "Receba 1 Tigrinho Token por atingir o level 250!"},
        [300] = {type = "item", id = {36727, 2}, msg = "Receba 2 Wealth duplex por atingir o level 300!"},
        [350] = {type = "mount", id = {1092, 0}, msg = "Receba uma montaria por atingir o level 350!"},
        [400] = {type = "addon", id = {1777, 1776}, msg = "Receba o Beekeeper addon completo por atingir o level 400!"},
        [500] = {type = "mount", id = {1778, 0}, msg = "Receba a montaria Bumblebee por atingir o level 500!"},
}

local storage = 15000

local levelReward = CreatureEvent("Level Reward")
function levelReward.onAdvance(player, skill, oldLevel, newLevel)

	if skill ~= SKILL_LEVEL or newLevel <= oldLevel then
		return true
	end

	for level, _ in pairs(table) do
		if newLevel >= level and player:getStorageValue(storage) < level then
			if table[level].type == "item" then	
				player:addItem(table[level].id[1], table[level].id[2])
			elseif table[level].type == "bank" then
				player:setBankBalance(player:getBankBalance() + table[level].id[1])
			elseif table[level].type == "addon" then
				player:addOutfitAddon(table[level].id[1], 3)
				player:addOutfitAddon(table[level].id[2], 3)
			elseif table[level].type == "coin" then
				player:addTibiaCoins(table[level].id[1])
			elseif table[level].type == "mount" then
				player:addMount(table[level].id[1])
			else
				return false
			end

			player:sendTextMessage(MESSAGE_EVENT_ADVANCE, table[level].msg)
			player:setStorageValue(storage, level)
		end
	end

	player:save()

	return true
end

levelReward:register()