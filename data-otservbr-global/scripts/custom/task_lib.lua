taskOptions = {
	bonusReward = 65001, -- storage bonus reward
	bonusRate = 2, -- rate bonus reward
	taskBoardPositions = {
        {x = 32341, y = 32229, z = 7},
        {x = 31469, y = 31764, z = 7},
    },
	selectLanguage = 1, -- options: 1 = pt_br or 2 = english
	uniqueTask = false, -- do one task at a time
	uniqueTaskStorage = 65002
}

task_pt_br = {
	exitButton = "Sair",
	confirmButton = "Confirmar",
	cancelButton = "Cancelar",
	returnButton = "Retornar",
	title = "Quadro de Tasks",
	missionError = "A task esta em andamento ou ja foi concluida.",
	uniqueMissionError = "Voce so pode fazer uma task por vez.",
	missionErrorTwo = "Voce completou a task",
	missionErrorTwoo = "\nAqui estao suas recompensas:",
	choiceText = "- Experiencia: ",
	messageAcceptedText = "Voce aceitou esta task!",
	messageDetailsText = "Detalhes da task:",
	choiceMonsterName = "Nome: ",
	choiceMonsterKill = "Kills: ",
	choiceEveryDay = "Repete: Todos os dias",
	choiceRepeatable = "Repete: Sempre",
	choiceOnce = "Repete: Apenas uma vez",
	choiceReward = "Recompensas:",
	messageAlreadyCompleteTask = "Voce ja completou esta task.",
	choiceCancelTask = "Voce cancelou esta task",
	choiceCancelTaskError = "Voce nao pode cancelar esta task porque ela ja foi conclui�da ou nao foi iniciada.",
	choiceBoardText = "Escolha uma task e use os botoes abaixo:",
	choiceRewardOnHold = "Resgatar recompensa",
	choiceDailyConclued = "Diaria Concluida",
	choiceConclued = "Concluida",
	messageTaskBoardError = "Este nao eh o quadro de task correto.",
	messageCompleteTask = "Voce terminou esta task! \nRetorne ao quadro de task(!task) e colete sua recompensa.",
}

taskConfiguration = {
	{name = "Beginner - Rotworm, Rat, Carrion Worm, White Pale, Rotworm Queen", color = 40, total = 100, type = "once", storage = 190006, storagecount = 190007, 
	rewards = {
		{3043, 10},
		{"exp", 100000},
	},
	races = {
		"Rotworm",
		"Carrion Worm",
		"White Pale",
		"Rotworm Queen",
		"Rat",
	},
},
{name = "Beginner - Minotaur, Minotaur Archer, Minotaur Mage, Minotaur Guard", color = 40, total = 250, type = "once", storage = 190000, storagecount = 190001, 
	rewards = {
		{5804, 1},
		{3043, 20},
		{"exp", 1000000},
	},
	races = {
		"Minotaur",
		"Minotaur Archer",
		"Minotaur Mage",
		"Minotaur Guard",
	},
},

{name = "Beginner - Cyclops, Cyclops Drone, Cyclops Smith", color = 40, total = 500, type = "once", storage = 190022, storagecount = 190023, 
	rewards = { 
		{3043, 20},
		{"exp", 800000},
	},
	races = {
		"Cyclops",
		"Cyclops Drone",
		"Cyclops Smith",
	},
},

{name = "Beginner - Amazon, Valkyrie, Witch", color = 40, total = 500, type = "once", storage = 190008, storagecount = 190009, 
	rewards = { 
		{3043, 30},
		{"exp", 1500000},
	},
	races = {
		"Amazon",
		"Valkyrie",
		"Witch",
	},
},

{name = "Dragons - Dragon, Dragon Lord, Dragon Hatchling, Dragon Lord Hatchling, Frost Dragon, Frost Dragon Hatchling, Dragon Warden, Dragonling, Ghastly Dragon, Undead Dragon", color = 40, total = 450, type = "repeatable", storage = 190002, storagecount = 190003, 
	rewards = {
		{3043, 40},
		{5908, 1},
		{"exp", 1500000},
	},
	races = {
		"Dragon",
		"Dragon Lord",
		"Dragon Hatchling",
		"Dragon Lord Hatchling",
		"Frost Dragon",
		"Frost Dragon Hatchling",
		"Dragon Warden",
		"Dragonling",
		"Ghastly Dragon",
		"Undead Dragon",
	},
},

{name = "Hero Fortress - Hero, Renegade Knight, Vile grandmaster, Vicious Squire", color = 40, total = 1500, type = "repeatable", storage = 190024, storagecount = 190025, 
	rewards = { 
		{3043, 100},
		{"exp", 1000000},
	},
	races = {
		"Hero",
		"Vile grandmaster",
		"Vicious Squire",
		"Renegade Knight",
	},
},

{name = "Deeplings - Deepling Guard, Deepling Warrior, Deepling Scount", color = 40, total = 1500, type = "repeatable", storage = 190016, storagecount = 190017, 
	rewards = { 
		{14142, 1},
		{3043, 60},
		{"exp", 10000000},
	},
	races = {
		"Deepling Guard",
		"Deepling Warrior",
		"Deepling Scout",
	},
},

{name = "Krailos - Ogre Sage, Ogre Ruffian, Ogre Rowdy, Ogre Shaman", color = 40, total = 1500, type = "once", storage = 190026, storagecount = 190027, 
	rewards = { 
		{3043, 50},
		{22722, 2},
		{"exp", 10000000},
	},
	races = {
		"Ogre Sage",
		"Ogre Ruffian",
		"Ogre Rowdy",
		"Ogre Shaman",
	},
},

{name = "Banuta - Medusa, Serpent Spawn, Hydra, Behemoth, Nightmare, Phantasm", color = 40, total = 5000, type = "repeatable", storage = 190020, storagecount = 190021, 
	rewards = { 
		{3043, 200},
		{23680, 1},
		{"exp", 20000000},
	},
	races = {
		"Medusa",
		"Serpent Spawn",
		"Hydra",
		"Giant Spider",
		"Behemoth",
		"Nightmare",
		"Phantasm",
	},
},

{name = "Pirat - Pirat Mate, Pirat Cutthroat, Pirat Scoundrel, Pirat Bombardier", color = 40, total = 1500, type = "repeatable", storage = 190028, storagecount = 190029, 
	rewards = { 
		{3043, 100},
		{"exp", 20000000},
	},
	races = {
		"Pirat Mate",
		"Pirat Cutthroat",
		"Pirat Scoundrel",
		"Pirat Bombardier",
	},
},

{name = "Zao - Lizard Chosen, Lizard High Guard, Lizard Legionnaire, Lizard Dragon Priest, Ghastly Dragon, Draken Elite, Draken Abomination, Draken Warmaster, Draken Spellweaver, Lizard Zaogun", color = 40, total = 2500, type = "repeatable", storage = 190044, storagecount = 190045, 
	rewards = { 
		{3043, 150},
		{"exp", 8000000},
	},
	races = {
		"Lizard Chosen",
		"Lizard High Guard",
		"Lizard Legionnaire",
		"Lizard Dragon Priest",
		"Ghastly Dragon",
		"Draken Elite",
		"Draken Abomination",
		"Draken Warmaster",
		"Draken Spellweaver",
		"Lizard Zaogun",
	},
},

{name = "Lower Roshamuul - Weakened Frazzlemaw, Frazzlemaw, Memory of Frazzlemaw, Guzzlemaw, Mawhawk, Silencer, Shock Head, Sight of Surrender", color = 40, total = 1500, type = "repeatable", storage = 190012, storagecount = 190013, 
	rewards = { 
		{22516, 10},
		{20270, 1},
		{20272, 1},
		{20062, 50},
		{3043, 70},
		{"exp", 3500000},
	},
	races = {
		"Weakened Frazzlemaw",
		"Frazzlemaw",
		"Memory Of A Frazzlemaw",
		"Guzzlemaw",
		"Mawhawk",
		"Sight of Surrender",
		"Silencer",
	},
},


{name = "Falcon Bastion - Falcon Knight, Falcon Paladin, Monk, Preceptor Lazare, Grand Canon Dominus, Grand Chaplain Gaunder", color = 40, total = 1500, type = "repeatable", storage = 190018, storagecount = 190019, 
	rewards = { 
		{3043, 300},
		{22722, 1},
		{"exp", 30000000},
	},
	races = {
		"Falcon Knight",
		"Falcon Paladin",
		"Monk",
		"Preceptor Lazare",
		"Grand Canon Dominus",
		"Grand Chaplain Gaunder",
	},
},

{name = "Asura Palace - Dawnfire Asura, Frost Flower Asura, Hellspawn, Midnight Asura, Destroyer", color = 40, total = 2000, type = "repeatable", storage = 190030, storagecount = 190031, 
	rewards = { 
		{3043, 100},
		{22722, 1},
		{"exp", 40000000},
	},
	races = {
		"Dawnfire Asura",
		"Frost Flower Asura",
		"Hellspawn",
		"Midnight Asura",
		"Destroyer",
	},
},

{name = "Marapur Turtles - Two-Headed Turtle, Foam Stalker", color = 40, total = 2000, type = "repeatable", storage = 190059, storagecount = 190060, 
	rewards = { 
		{3043, 200},
		{22722, 1},
		{"exp", 8000000},
	},
	races = {
		"Two-Headed Turtle",
		"Foam Stalker",
	},
},
{name = "Bashmu - Bashmu, Juvenile Bashmu", color = 40, total = 2500, type = "repeatable", storage = 197059, storagecount = 197060, 
	rewards = { 
		{3043, 200},
		{22722, 1},
		{"exp", 8000000},
	},
	races = {
		"Bashmu",
		"Juvenile Bashmu",
	},
},

{name = "Asura Vaults - True Dawnfire Asura, True Midnight Asura, True Frost Flower Asura", color = 40, total = 2500, type = "repeatable", storage = 190032, storagecount = 190033, 
	rewards = { 
		{3043, 300},
		{22722, 2},
		{"exp", 70000000},
	},
	races = {
		"True Dawnfire Asura",
		"True Midnight Asura",
		"True Frost Flower Asura",
	},
},

{name = "Summer Dream Court - Crazed Summer Rearguard, Crazed Summer Vanguard, Insane Siren, Arachnophobica, Thanatursus, Lacewing Moth", color = 40, total = 2500, type = "repeatable", storage = 190034, storagecount = 190035, 
	rewards = { 
		{3043, 100},
		{22722, 2},
		{"exp", 90000000},
	},
	races = {
		"Crazed Summer Rearguard",
		"Crazed Summer Vanguard",
		"Insane Siren",
		"Arachnophobica",
		"Thanatursus",
		"Lacewing Moth",
	},
},

{name = "Court of Winter - Crazed Winter Vanguard, Crazed Winter Rearguard, Soul-Broken Harbinger, Hibernal Moth, Arachnophobica, Thanatursus", color = 40, total = 2500, type = "repeatable", storage = 190036, storagecount = 190037, 
	rewards = { 
		{3043, 100},
		{22722, 2},
		{"exp", 90000000},
	},
	races = {
		"Crazed Winter Vanguard",
		"Crazed Winter Rearguard",
		"Soul-Broken Harbinger",
		"Hibernal Moth",
		"Arachnophobica",
		"Thanatursus",
	},
},

{name = "Lion Sanctum - White Lion, Werelion, Werelioness", color = 40, total = 2500, type = "repeatable", storage = 190038, storagecount = 190039, 
	rewards = { 
		{3043, 100},
		{22722, 2},
		{"exp", 70000000},
	},
	races = {
		"White Lion",
		"Werelion",
		"Werelioness",
	},
},

{name = "Warzone 3 - Ironblight, Orewalker, Cliff Strider, Lost Berserker", color = 40, total = 1500, type = "repeatable", storage = 190061, storagecount = 190062, 
	rewards = { 
		{3043, 150},
		{22722, 1},
		{"exp", 8000000},
	},
	races = {
		"Ironblight",
		"Orewalker",
		"Cliff Strider",
		"Lost Berserker",
	},
},
{name = "Warzone 5 - Drillworm, Chasm Spawn, Mole, Elder Wyrm", color = 40, total = 1500, type = "repeatable", storage = 190063, storagecount = 190064, 
	rewards = { 
		{3043, 150},
		{22722, 1},
		{"exp", 8000000},
	},
	races = {
		"Drillworm",
		"Chasm Spawn",
		"Mole",
		"Elder Wyrm",
	},
},


{name = "Issavi / Kilmaresh step - Priestess of the Wild Sun, Black Sphinx Acolyte, Burning Gladiator, Sphinx, Crypt Warden, Gryphon, Young Goanna, Adult goanna, Feral Sphinx, Manticore, Lamassu", color = 40, total = 2500, type = "repeatable", storage = 190046, storagecount = 190047, 
	rewards = { 
		{3043, 200},
		{22722, 1},
		{"exp", 8000000},
	},
	races = {
		"Priestess of the Wild Sun",
		"Black Sphinx Acolyte",
		"Burning Gladiator",
		"Sphinx",
		"Crypt Warden",
		"Gryphon",
		"Young Goanna",
		"Adult Goanna",
		"Feral Sphinx",
		"Manticore",
		"Lamassu",
	},
},

{name = "Cobra Bastion - Cobra Assassin, Cobra Vizier, Cobra Scout", color = 40, total = 4000, type = "repeatable", storage = 190048, storagecount = 190049, 
	rewards = { 
		{3043, 200},
		{31631, 1},
		{22722, 2},
		{"exp", 8000000},
	},
	races = {
		"Cobra Assassin",
		"Cobra Vizier",
		"Cobra Scout",
	},
},

{name = "Buried Cathedral - Burster Spectre, Ripper Spectre, Gazer Spectre", color = 40, total = 2000, type = "repeatable", storage = 190065, storagecount = 190066, 
	rewards = { 
		{3043, 200},
		{22722, 4},
		{"exp", 8000000},
	},
	races = {
		"Burster Spectre",
		"Ripper Spectre",
		"Gazer Spectre",
	},
},
{name = "Oskayaat - Cunning Werepanther, Feral Werecrocodile, Werecrocodile, Werepanther, Weretiger, White Tiger, White Weretiger", color = 40, total = 3000, type = "repeatable", storage = 190067, storagecount = 190068, 
	rewards = { 
		{3043, 150},		
		{43740, 1},
		{43863, 1},
		{"exp", 8000000},
	},
	races = {
		"Cunning Werepanther",
		"Feral Werecrocodile",
		"Werecrocodile",
		"Werepanther",
		"Weretiger",
		"White Tiger",
		"White Weretiger",
	},
},

{name = "Library - Cursed Book, Biting Book, Animated Feather, Icecold Book, Dark Knowledge, Energetic Book, Energuardian of Tales, Brain Squid, Flying Book, Guardian of Tales, Ghulosh' Deathgaze, Knowledge elemental, The Book of Death, Rage Squid, Squid Warden", color = 40, total = 3000, type = "repeatable", storage = 190069, storagecount = 190070, 
	rewards = { 
		{3043, 250},	
		{22722, 4},
		{"exp", 8000000},
	},
	races = {
		"Cursed Book",
		"Biting Book",
		"Animated Feather",
		"Dark Knowledge",
		"Energetic Book",
		"Energuardian of Tales",
		"Brain Squid",
		"Flying Book",
		"Guardian of Tales",
		"Ghulosh' Deathgaze",
		"Knowledge elemental",
		"The Book of Death",
		"Rage Squid",
		"Squid Warden",
		"Burning Book",
		"Icecold Book",
		
	},
},

{name = " Grim Reaper, Lich, Gravedigger, Spectre", color = 40, total = 2000, type = "repeatable", storage = 190077, storagecount = 190078, 
	rewards = { 
		{3043, 120},
		{22722, 1},
		{"exp", 1000000},
	},
	races = {
		"Grim Reaper",
		"Lich",
		"Gravedigger",
		"Spectre",
	},
},

{name = "Nagas - Naga Warrior, Naga Archer, Makara", color = 40, total = 2000, type = "repeatable", storage = 190083, storagecount = 190084, 
	rewards = { 
		{3043, 180},
		{22722, 2},
		{"exp", 5000000},
	},
	races = {
		"Naga Warrior",
		"Naga Archer",
		"Makara",
	},
},
{name = "Ingol - Boar Man, Carnivostrich, Crape Man, Harpy, Liodile, Rhindeer", color = 40, total = 2500, type = "repeatable", storage = 190085, storagecount = 190086, 
	rewards = { 
		{3043, 320},	
		{22722, 2},
		{"exp", 5000000},
	},
	races = {
		"Boar Man",
		"Carnivostrich",
		"Crape Man",
		"Harpy",
		"Liodile",
		"Rhindeer",
	},
},
{name = "Deathlings - Deathling Scout, Deathling Spellsinger", color = 40, total = 1500, type = "repeatable", storage = 190087, storagecount = 190088, 
	rewards = { 
		{3043, 220},		
		{22722, 2},
		{"exp", 5000000},
	},
	races = {
		"Deathling Scout",
		"Deathling Spellsinger",
	},
},

{name = "Flimsy - Flimsy Lost Soul, Mean Lost Soul, Freakish Lost Soul", color = 40, total = 2000, type = "repeatable", storage = 190089, storagecount = 190090, 
	rewards = { 
		{3043, 260},		
		{"exp", 5000000},
	},
	races = {
		"Flimsy Lost Soul",
		"Mean Lost Soul",
		"Freakish Lost Soul",
	},
},

{name = "Bulltaur - Bulltaur Alchemist, Bulltaur Brute, Bulltaur Forgepriest", color = 40, total = 2500, type = "repeatable", storage = 190096, storagecount = 190097, 
	rewards = { 
		{3043, 300},		
		{"exp", 15000000},
	},
	races = {
		"Bulltaur Alchemist",
		"Bulltaur Brute",
		"Bulltaur Forgepriest",
	},
},

{name = "Nimmersatts - Wardragon, Dragolisk, Mega Dragon", color = 40, total = 2500, type = "repeatable", storage = 190094, storagecount = 190095, 
	rewards = { 
		{3043, 150},		
		{"exp", 20000000},
	},
	races = {
		"Wardragon",
		"Dragolisk",
		"Mega Dragon",
	},
},


{name = "Soul War - Bony Sea Devil, Turbulent elemental, Brachiodemon, Capricious Phantom, Cloak of Terror, Distorted Phantom, Courage Leech, Infernal Phantom, Infernal Demon, Hazardous Phantom, Many Faces, Mean Maw, Mould Phantom, Rotten Golem, Spiteful Spitter, Vibrant Phantom, Branchy Crawler", color = 40, total = 5000, type = "once", storage = 190042, storagecount = 190043, 
	rewards = {  
		{36727, 2},
		{22722, 5},
		{34109, 1},
		{"exp", 100000000},
	},
	races = {
		"Bony Sea Devil",
		"Brachiodemon",
		"Capricious Phantom",
		"Cloak of Terror",
		"Distorted Phantom",
		"Courage Leech",
		"Infernal Phantom",
		"Hazardous Phantom",
		"Many Faces",
		"Mean Maw",
		"Mould Phantom",
		"Rotten Golem",
		"Spiteful Spitter",
		"Turbulent Elemental",
		"Vibrant Phantom",
		"Branchy Crawler",
		"Infernal Demon",
	},
},

{name = "Gnomprona - Hulking Prehemoth, Gore Horn, Gorerilla, Sulphur Spouter, Undertaker,Sulphider, Nighthunter, Stalking Stalk, Emerald Tortoise, Mantosaurus, Noxious Ripptor, Fungosaurus", color = 40, total = 5000, type = "once", storage = 190079, storagecount = 190080, 
	rewards = { 
		{3043, 250},		
		{39546, 1},
		{22722, 5},
		{"exp", 100000000},
	},
	races = {
		"Hulking Prehemoth",
		"Gore Horn",
		"Gorerilla",
		"Emerald Tortoise",
		"Mantosaurus",
		"Noxious Ripptor",
		"Fungosaurus",
		"Sulphider",
		"Nighthunter",
		"Stalking Stalk",
		"Sulphur Spouter",
		"Undertaker",
	},
},

{name = "Rotten Blood - Bloated Man-Maggot, Converter, Darklight Construct, Darklight Emitter, Darklight Matter, Darklight Source, Darklight Striker, Mycobiontic Beetle, Oozing Carcass, Oozing Corpus, Rotten Man-Maggot, Sopping Carcass, Sopping Corpus, Walking Pillar, Wandering Pilar", color = 40, total = 5000, type = "once", storage = 190054, storagecount = 190055, 
	rewards = { 
		{3043, 350},
		{43895, 1},
		{22722, 5},
		{"exp", 100000000},
	},
	races = {
		"Bloated Man-Maggot",
		"Converter",
		"Darklight Construct",
		"Darklight Emitter",
		"Darklight Source",
		"Darklight Striker",
		"Darklight Matter",
		"Mycobiontic Beetle",
		"Oozing Carcass",
		"Oozing Corpus",
		"Rotten Man-Maggot",
		"Sopping Carcass",
		"Walking Pillar",
		"Wandering Pillar",
		
	},
},

}

squareWaitTime = 5000
taskQuestLog = 65000 -- A storage so you get the quest log
dailyTaskWaitTime = 6 * 60 * 60 

function Player.getCustomActiveTasksName(self)
local player = self
	if not player then
		return false
	end
local tasks = {}
	for i, data in pairs(taskConfiguration) do
		if player:getStorageValue(data.storagecount) ~= -1 then
		tasks[#tasks + 1] = data.name
		end
	end
	return #tasks > 0 and tasks or false
end


function getTaskByStorage(storage)
	for i, data in pairs(taskConfiguration) do
		if data.storage == tonumber(storage) then
			return data
		end
	end
	return false
end

function getTaskByMonsterName(name)
	for i, data in pairs(taskConfiguration) do
		for _, dataList in ipairs(data.races) do
		if dataList:lower() == name:lower() then
			return data
		end
		end
	end
	return false
end

function Player.startTask(self, storage)
local player = self
	if not player then
		return false
	end
local data = getTaskByStorage(storage)
	if data == false then
		return false
	end
	if player:getStorageValue(taskQuestLog) == -1 then
		player:setStorageValue(taskQuestLog, 1)
	end
	player:setStorageValue(storage, player:getStorageValue(storage) + 1)
	player:setStorageValue(data.storagecount, 0)
	return true
end

function Player.canStartCustomTask(self, storage)
local player = self
	if not player then
		return false
	end
local data = getTaskByStorage(storage)
	if data == false then
		return false
	end
	if data.type == "daily" then
		return os.time() >= player:getStorageValue(storage)
	elseif data.type == "once" then
		return player:getStorageValue(storage) == -1
	elseif data.type[1] == "repeatable" and data.type[2] ~= -1 then
		return player:getStorageValue(storage) < (data.type[2] - 1)
	else
		return true
	end
end

function Player.endTask(self, storage, prematurely)
local player = self
	if not player then
		return false
	end
local data = getTaskByStorage(storage)
	if data == false then
		return false
end
	if prematurely then
		if data.type == "daily" then
			player:setStorageValue(storage, -1)
		else
			player:setStorageValue(storage, player:getStorageValue(storage) - 1)
	end
	else
		if data.type == "daily" then
			player:setStorageValue(storage, os.time() + dailyTaskWaitTime)
		end
	end
	player:setStorageValue(data.storagecount, -1)
	return true
end

function Player.hasStartedTask(self, storage)
local player = self
	if not player then
		return false
	end
local data = getTaskByStorage(storage)
	if data == false then
		return false
	end
	return player:getStorageValue(data.storagecount) ~= -1
end


function Player.getTaskKills(self, storage)
local player = self
	if not player then
		return false
	end
	return player:getStorageValue(storage)
end

function Player.addTaskKill(self, storage, count)
local player = self
	if not player then
		return false
	end
local data = getTaskByStorage(storage)
	if data == false then
		return false
	end
	local kills = player:getTaskKills(data.storagecount)
	if kills >= data.total then
		return false
	end
	if kills + count >= data.total then
		if taskOptions.selectLanguage == 1 then
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, task_pt_br.messageCompleteTask)
		else
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "[Task System] You have finished this task! To claim your rewards, return to the quest board and claim your reward.")
		end
		return player:setStorageValue(data.storagecount, data.total)
	end
		player:say(' ['.. kills + count .. '/'.. data.total ..']', TALKTYPE_MONSTER_SAY)
		return player:setStorageValue(data.storagecount, kills + count)
end
