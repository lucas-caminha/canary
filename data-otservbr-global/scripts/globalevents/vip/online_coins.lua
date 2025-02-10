local config = {
	enabled = true,
	storage = Storage.VipSystem.OnlineCoinsGain,
	checkDuplicateIps = false,

	interval = 60 * 1000,

	-- Coins ganhos por hora
	coinsPerHour = {
		free = 1,
		vip = 2,
	},

	-- Entrega os coins quando acumular pelo menos 1
	awardOn = 1,
}

local onlineCoinsEvent = GlobalEvent("GainCoinInterval")
local runsPerHour = 3600 / (config.interval / 1000)

local function coinsPerRun(coinsPerHour)
	return coinsPerHour / runsPerHour
end

function onlineCoinsEvent.onThink(interval)
	local players = Game.getPlayers()
	if #players == 0 then
		return true
	end

	local checkIp = {}
	for _, player in pairs(players) do
		-- Filtra jogadores que não devem receber coins
		if player:getGroup():getId() > GROUP_TYPE_SENIORTUTOR or (config.coinsPerHour.free < 1 and not player:isVip()) then
			goto continue
		end

		local ip = player:getIp()
		if ip ~= 0 and (not config.checkDuplicateIps or not checkIp[ip]) then
			checkIp[ip] = true

			-- Garantimos que o storage nunca seja -1
			local storedCoins = player:getStorageValue(config.storage)
			if storedCoins < 0 then storedCoins = 0 end

			-- Calcula os coins a serem adicionados por rodada
			local coins = coinsPerRun(player:isVip() and config.coinsPerHour.vip or config.coinsPerHour.free) + (storedCoins / 10000000)

			-- Salva o novo valor no storage
			player:setStorageValue(config.storage, coins * 10000000)

			-- Se acumulou pelo menos 1 coin, entrega
			if coins >= config.awardOn then
				local coinsToGive = math.floor(coins)
				player:addTibiaCoins(coinsToGive, true)
				player:sendTextMessage(MESSAGE_EVENT_ADVANCE, string.format("Congratulations %s! \z You have received %d tibia coins for being online.", player:getName(), coinsToGive))

				-- Guarda o resto que sobrou
				player:setStorageValue(config.storage, (coins - coinsToGive) * 10000000)
			end
		end

		::continue::
	end
	return true
end

if config.enabled then
	onlineCoinsEvent:interval(config.interval)
	onlineCoinsEvent:register()
end
