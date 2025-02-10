local outfits = {
    ["Citizen"] = {136, 128},
    ["Hunter"] = {137, 129},
    ["Knight"] = {139, 131},
    ["Noblewoman"] = {140, 132},
    ["Warrior"] = {142, 134},
    ["Barbarian"] = {147, 143},
    ["Druid"] = {148, 144},
    ["Wizard"] = {149, 145},
    ["Assassin"] = {156, 152},
    ["Oriental"] = {150, 146},
    ["Pirate"] = {155, 151},
    ["Beggar"] = {157, 153},
    ["Shaman"] = {158, 154},
    ["Nightmare"] = {269, 268},
    ["Jester"] = {270, 273},
    ["Brotherhood"] = {279, 278},
    ["Elementalist"] = {433, 432},
    ["Deepling"] = {464, 463},
    ["Insectoid"] = {466, 465},
}

local storage = 32943

local addonDollCoin = Action()
function addonDollCoin.onUse(player, item, fromPosition, itemEx, toPosition, isHotkey)
    if player:getStorageValue(storage) > 0 then
        player:sendCancelMessage("Voce ja tem todos os addons.")
		player:getPosition():sendMagicEffect(CONST_ME_POFF)
        return true
    end

    for a, b in pairs(outfits) do
        player:addOutfitAddon(b[1], 3)
        player:addOutfitAddon(b[2], 3)
    end
    
	player:addOutfitAddon(130, 1)
	player:addOutfitAddon(138, 1)
    player:sendCancelMessage("Voce recebeu os addons basicos.")
    player:getPosition():sendMagicEffect(CONST_ME_GIFT_WRAPS)
	player:setStorageValue(storage, 1)
	item:remove(1)
    return true
end

addonDollCoin:id(8778)
addonDollCoin:register()