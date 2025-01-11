-- Minlevel and multiplier are MANDATORY
-- Maxlevel is OPTIONAL, but is considered infinite by default
-- Create a stage with minlevel 1 and no maxlevel to disable stages
experienceStages = {
	{
		minlevel = 1,
		maxlevel = 8,
		multiplier = 200,
	},
	{
		minlevel = 9,
		maxlevel = 100,
		multiplier = 200,
	},
	{
		minlevel = 101,
		maxlevel = 200,
		multiplier = 150,
	},
	{
		minlevel = 201,
		maxlevel = 250,
		multiplier = 100,
	},
	{
		minlevel = 251,
		maxlevel = 300,
		multiplier = 75,
	},
	{
		minlevel = 301,
		maxlevel = 350,
		multiplier = 50,
	},
	{
		minlevel = 351,
		maxlevel = 400,
		multiplier = 25,
	},
	{
		minlevel = 401,
		maxlevel = 450,
		multiplier = 15,
	},
	{
		minlevel = 451,
		maxlevel = 500,
		multiplier = 7,
	},
	{
		minlevel = 501,
		multiplier = 3,
	},
}

skillsStages = {
	{
		minlevel = 10,
		maxlevel = 60,
		multiplier = 20,
	},
	{
		minlevel = 61,
		maxlevel = 80,
		multiplier = 10,
	},
	{
		minlevel = 81,
		maxlevel = 110,
		multiplier = 6,
	},
	{
		minlevel = 111,
		maxlevel = 125,
		multiplier = 4,
	},
	{
		minlevel = 126,
		multiplier = 2,
	},
}

magicLevelStages = {
	{
		minlevel = 0,
		maxlevel = 60,
		multiplier = 20,
	},
	{
		minlevel = 61,
		maxlevel = 80,
		multiplier = 10,
	},
	{
		minlevel = 81,
		maxlevel = 100,
		multiplier = 5,
	},
	{
		minlevel = 101,
		maxlevel = 110,
		multiplier = 4,
	},
	{
		minlevel = 111,
		maxlevel = 125,
		multiplier = 3,
	},
	{
		minlevel = 126,
		multiplier = 2,
	},
}
