local raidSchedule = {
	["Monday"] = {
		["08:00"] = { raidName = "Necropharus" },
		["10:00"] = { raidName = "Mad Mage" },
		["12:00"] = { raidName = "Zulazza the Corruptor" },
		["14:00"] = { raidName = "Horned Fox" },
		["16:00"] = { raidName = "Zushuka" },
		["18:00"] = { raidName = "WaterBuffalo" },
		["20:00"] = { raidName = "Zushuka" },
		["23:00"] = { raidName = "Orc Backpack" },
	},
	["Tuesday"] = {
		["08:00"] = { raidName = "DeeplingsThais" },
		["12:00"] = { raidName = "Mawhawk" },
		["16:00"] = { raidName = "Midnight Panther" },
		["19:00"] = { raidName = "Orshabaal" },
		["22:00"] = { raidName = "Mawhawk" },
		["00:00"] = { raidName = "Midnight Panther" },
	},
	["Wednesday"] = {
		["07:00"] = { raidName = "Draptor" },
		["10:00"] = { raidName = "Demodras" },
		["12:00"] = { raidName = "Mawhawk" },
		["16:00"] = { raidName = "Draptor" },
		["19:00"] = { raidName = "Ghazbaran" },	
		["00:00"] = { raidName = "Draptor" },	
	},
	["Thursday"] = {
		["08:00"] = { raidName = "DeeplingsThais" },
		["10:00"] = { raidName = "Orc Backpack" },
		["12:00"] = { raidName = "Mawhawk" },
		["16:00"] = { raidName = "Undead Cavebear" },
		["19:00"] = { raidName = "Morgaroth" },
		["21:00"] = { raidName = "Ratmiral" },
		["00:00"] = { raidName = "Undead Cavebear" },
	},
	["Friday"] = {
		["07:00"] = { raidName = "Titanica" },
		["12:00"] = { raidName = "Mawhawk" },
		["15:00"] = { raidName = "Demodras" },
		["17:00"] = { raidName = "Titanica" },
		["19:00"] = { raidName = "Feroxa" },
		["21:00"] = { raidName = "DeeplingsThais" },
		["00:00"] = { raidName = "Ratmiral" },
	},
	["Saturday"] = {
		["07:00"] = { raidName = "Yeti" },
		["10:00"] = { raidName = "Demodras" },
		["12:00"] = { raidName = "Mawhawk" },
		["15:00"] = { raidName = "Omrafir" },
		["17:00"] = { raidName = "Mawhawk" },
		["19:00"] = { raidName = "Gaz" },
		["22:00"] = { raidName = "Yeti" },
	},
	["Sunday"] = {
		["06:00"] = { raidName = "Ratmiral" },
		["08:00"] = { raidName = "DeeplingsThais" },
		["10:00"] = { raidName = "Midnight Panther" },
		["12:00"] = { raidName = "The Welter" },
		["14:00"] = { raidName = "Mawhawk" },
		["15:00"] = { raidName = "Orc Backpack" },
		["16:00"] = { raidName = "Titanica" },
		["18:00"] = { raidName = "DeeplingsThais" },
		["19:00"] = { raidName = "Feroxa" },
		["20:00"] = { raidName = "Draptor" },
		["22:00"] = { raidName = "Mawhawk" },
	},
	["31/10"] = {
		["16:00"] = { raidName = "Halloween Hare" },
	},
}

local spawnRaidsEvent = GlobalEvent("SpawnRaidsEvent")

function spawnRaidsEvent.onThink(interval, lastExecution, thinkInterval)
	local currentDayOfWeek, currentDate = os.date("%A"), getRealDate()
	local raidsToSpawn = {}

	if raidSchedule[currentDayOfWeek] then
		raidsToSpawn[#raidsToSpawn + 1] = raidSchedule[currentDayOfWeek]
	end

	if raidSchedule[currentDate] then
		raidsToSpawn[#raidsToSpawn + 1] = raidSchedule[currentDate]
	end

	if #raidsToSpawn > 0 then
		for i = 1, #raidsToSpawn do
			local currentRaidSchedule = raidsToSpawn[i][getRealTime()]
			if currentRaidSchedule and not currentRaidSchedule.alreadyExecuted then
				Game.startRaid(currentRaidSchedule.raidName)
				currentRaidSchedule.alreadyExecuted = true
			end
		end
	end
	return true
end

spawnRaidsEvent:interval(60000)
spawnRaidsEvent:register()
