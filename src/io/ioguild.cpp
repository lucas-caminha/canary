/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.org/
*/

#include "otpch.h"

#include "database/database.h"
#include "creatures/players/grouping/guild.h"
#include "io/ioguild.h"

Guild* IOGuild::loadGuild(uint32_t guildId)
{
	Database& db = Database::getInstance();
	std::ostringstream query;
	query << "SELECT `name`, `balance` FROM `guilds` WHERE `id` = " << guildId;
	if (DBResult_ptr result = db.storeQuery(query.str())) {
		Guild* guild = new Guild(guildId, result->getString("name"));
    guild->setBankBalance(result->getU64("balance"));
		query.str(std::string());
		query << "SELECT `id`, `name`, `level` FROM `guild_ranks` WHERE `guild_id` = " << guildId;

		if ((result = db.storeQuery(query.str()))) {
			do {
				guild->addRank(result->getU32("id"), result->getString("name"), result->getU8("level"));
			} while (result->next());
		}
		return guild;
	}
	return nullptr;
}

void IOGuild::saveGuild(Guild* guild) {
  if (!guild)
    return;
  Database& db = Database::getInstance();
  std::ostringstream updateQuery;
  updateQuery << "UPDATE `guilds` SET ";
  updateQuery << "`balance` = " << guild->getBankBalance();
  updateQuery << " WHERE `id` = " << guild->getId();
  db.executeQuery(updateQuery.str());
}

uint32_t IOGuild::getGuildIdByName(const std::string& name)
{
	Database& db = Database::getInstance();

	std::ostringstream query;
	query << "SELECT `id` FROM `guilds` WHERE `name` = " << db.escapeString(name);

	DBResult_ptr result = db.storeQuery(query.str());
	if (!result) {
		return 0;
	}
	return result->getU32("id");
}

void IOGuild::getWarList(uint32_t guildId, GuildWarVector& guildWarVector)
{
	std::ostringstream query;
	query << "SELECT `guild1`, `guild2` FROM `guild_wars` WHERE (`guild1` = " << guildId << " OR `guild2` = " << guildId << ") AND `ended` = 0 AND `status` = 1";

	DBResult_ptr result = Database::getInstance().storeQuery(query.str());
	if (!result) {
		return;
	}

	do {
		uint32_t guild1 = result->getU32("guild1");
		if (guildId != guild1) {
			guildWarVector.push_back(guild1);
		} else {
			guildWarVector.push_back(result->getU32("guild2"));
		}
	} while (result->next());
}
