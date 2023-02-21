/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.org/
 */

#include "pch.hpp"

#include "game/game.h"
#include "io/functions/iologindata_save_player.hpp"

bool IOLoginDataSave::saveItems(const Player* player, const ItemBlockList &itemList, DBInsert &query_insert, PropWriteStream &propWriteStream) {
	Database &db = Database::getInstance();
	std::ostringstream ss;
	using ContainerBlock = std::pair<Container*, int32_t>;
	std::list<ContainerBlock> queue;
	int32_t runningId = 100;
	const auto &openContainers = player->getOpenContainers();
	for (const auto &it : itemList) {
		int32_t pid = it.first;
		Item* item = it.second;
		++runningId;
		if (Container* container = item->getContainer()) {
			if (container->getAttribute<int64_t>(ItemAttribute_t::OPENCONTAINER) > 0) {
				container->setAttribute(ItemAttribute_t::OPENCONTAINER, 0);
			}
			if (!openContainers.empty()) {
				for (const auto &its : openContainers) {
					auto openContainer = its.second;
					auto opcontainer = openContainer.container;
					if (opcontainer == container) {
						container->setAttribute(ItemAttribute_t::OPENCONTAINER, ((int)its.first) + 1);
						break;
					}
				}
			}
			queue.emplace_back(container, runningId);
		}
		propWriteStream.clear();
		item->serializeAttr(propWriteStream);
		size_t attributesSize;
		const char* attributes = propWriteStream.getStream(attributesSize);
		ss << player->getGUID() << ',' << pid << ',' << runningId << ',' << item->getID() << ',' << item->getSubType() << ',' << db.escapeBlob(attributes, attributesSize);
		if (!query_insert.addRow(ss)) {
			return false;
		}
	}
	while (!queue.empty()) {
		const ContainerBlock &cb = queue.front();
		Container* container = cb.first;
		int32_t parentId = cb.second;
		queue.pop_front();
		for (Item* item : container->getItemList()) {
			++runningId;
			Container* subContainer = item->getContainer();
			if (subContainer) {
				queue.emplace_back(subContainer, runningId);
				if (subContainer->getAttribute<int64_t>(ItemAttribute_t::OPENCONTAINER) > 0) {
					subContainer->setAttribute(ItemAttribute_t::OPENCONTAINER, 0);
				}
				if (!openContainers.empty()) {
					for (const auto &it : openContainers) {
						auto openContainer = it.second;
						auto opcontainer = openContainer.container;
						if (opcontainer == subContainer) {
							subContainer->setAttribute(ItemAttribute_t::OPENCONTAINER, (it.first) + 1);
							break;
						}
					}
				}
			}
			propWriteStream.clear();
			item->serializeAttr(propWriteStream);
			size_t attributesSize;
			const char* attributes = propWriteStream.getStream(attributesSize);
			ss << player->getGUID() << ',' << parentId << ',' << runningId << ',' << item->getID() << ',' << item->getSubType() << ',' << db.escapeBlob(attributes, attributesSize);
			if (!query_insert.addRow(ss)) {
				return false;
			}
		}
	}
	return query_insert.execute();
}

bool IOLoginDataSave::savePlayerFirst(Player* player) {
	Database &db = Database::getInstance();
	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	if (player->getHealth() <= 0) {
		player->changeHealth(1);
	}

	std::ostringstream query;
	query << "SELECT `save` FROM `players` WHERE `id` = " << player->getGUID();
	DBResult_ptr result = db.storeQuery(query.str());
	if (!result) {
		SPDLOG_WARN("[IOLoginData::savePlayer] - Error for select result query from player: {}", player->getName());
		return false;
	}

	if (result->getNumber<uint16_t>("save") == 0) {
		query.str("");
		query << "UPDATE `players` SET `lastlogin` = " << player->lastLoginSaved << ", `lastip` = " << player->lastIP << " WHERE `id` = " << player->getGUID();
		return db.executeQuery(query.str());
	}

	// First, an UPDATE query to write the player itself
	query.str("");
	query << "UPDATE `players` SET ";
	query << "`level` = " << player->level << ",";
	query << "`group_id` = " << player->group->id << ",";
	query << "`vocation` = " << player->getVocationId() << ",";
	query << "`health` = " << player->health << ",";
	query << "`healthmax` = " << player->healthMax << ",";
	query << "`experience` = " << player->experience << ",";
	query << "`lookbody` = " << static_cast<uint32_t>(player->defaultOutfit.lookBody) << ",";
	query << "`lookfeet` = " << static_cast<uint32_t>(player->defaultOutfit.lookFeet) << ",";
	query << "`lookhead` = " << static_cast<uint32_t>(player->defaultOutfit.lookHead) << ",";
	query << "`looklegs` = " << static_cast<uint32_t>(player->defaultOutfit.lookLegs) << ",";
	query << "`looktype` = " << player->defaultOutfit.lookType << ",";
	query << "`lookaddons` = " << static_cast<uint32_t>(player->defaultOutfit.lookAddons) << ",";
	query << "`lookmountbody` = " << static_cast<uint32_t>(player->defaultOutfit.lookMountBody) << ",";
	query << "`lookmountfeet` = " << static_cast<uint32_t>(player->defaultOutfit.lookMountFeet) << ",";
	query << "`lookmounthead` = " << static_cast<uint32_t>(player->defaultOutfit.lookMountHead) << ",";
	query << "`lookmountlegs` = " << static_cast<uint32_t>(player->defaultOutfit.lookMountLegs) << ",";
	query << "`lookfamiliarstype` = " << player->defaultOutfit.lookFamiliarsType << ",";
	query << "`isreward` = " << static_cast<uint16_t>(player->isDailyReward) << ",";
	query << "`maglevel` = " << player->magLevel << ",";
	query << "`mana` = " << player->mana << ",";
	query << "`manamax` = " << player->manaMax << ",";
	query << "`manaspent` = " << player->manaSpent << ",";
	query << "`soul` = " << static_cast<uint16_t>(player->soul) << ",";
	query << "`town_id` = " << player->town->getID() << ",";

	const Position &loginPosition = player->getLoginPosition();
	query << "`posx` = " << loginPosition.getX() << ",";
	query << "`posy` = " << loginPosition.getY() << ",";
	query << "`posz` = " << loginPosition.getZ() << ",";

	query << "`prey_wildcard` = " << player->getPreyCards() << ",";
	query << "`task_points` = " << player->getTaskHuntingPoints() << ",";
	query << "`forge_dusts` = " << player->getForgeDusts() << ",";
	query << "`forge_dust_level` = " << player->getForgeDustLevel() << ",";
	query << "`randomize_mount` = " << static_cast<uint16_t>(player->isRandomMounted()) << ",";

	query << "`cap` = " << (player->capacity / 100) << ",";
	query << "`sex` = " << static_cast<uint16_t>(player->sex) << ",";

	if (player->lastLoginSaved != 0) {
		query << "`lastlogin` = " << player->lastLoginSaved << ",";
	}

	if (player->lastIP != 0) {
		query << "`lastip` = " << player->lastIP << ",";
	}

	// serialize conditions
	PropWriteStream propWriteStream;
	for (Condition* condition : player->conditions) {
		if (condition->isPersistent()) {
			condition->serialize(propWriteStream);
			propWriteStream.write<uint8_t>(CONDITIONATTR_END);
		}
	}

	size_t attributesSize;
	const char* attributes = propWriteStream.getStream(attributesSize);

	query << "`conditions` = " << db.escapeBlob(attributes, attributesSize) << ",";

	if (g_game().getWorldType() != WORLD_TYPE_PVP_ENFORCED) {
		int64_t skullTime = 0;

		if (player->skullTicks > 0) {
			skullTime = time(nullptr) + player->skullTicks;
		}

		query << "`skulltime` = " << skullTime << ",";

		Skulls_t skull = SKULL_NONE;
		if (player->skull == SKULL_RED) {
			skull = SKULL_RED;
		} else if (player->skull == SKULL_BLACK) {
			skull = SKULL_BLACK;
		}
		query << "`skull` = " << static_cast<int64_t>(skull) << ",";
	}

	query << "`lastlogout` = " << player->getLastLogout() << ",";
	query << "`balance` = " << player->bankBalance << ",";
	query << "`offlinetraining_time` = " << player->getOfflineTrainingTime() / 1000 << ",";
	query << "`offlinetraining_skill` = " << std::to_string(player->getOfflineTrainingSkill()) << ",";
	query << "`stamina` = " << player->getStaminaMinutes() << ",";
	query << "`skill_fist` = " << player->skills[SKILL_FIST].level << ",";
	query << "`skill_fist_tries` = " << player->skills[SKILL_FIST].tries << ",";
	query << "`skill_club` = " << player->skills[SKILL_CLUB].level << ",";
	query << "`skill_club_tries` = " << player->skills[SKILL_CLUB].tries << ",";
	query << "`skill_sword` = " << player->skills[SKILL_SWORD].level << ",";
	query << "`skill_sword_tries` = " << player->skills[SKILL_SWORD].tries << ",";
	query << "`skill_axe` = " << player->skills[SKILL_AXE].level << ",";
	query << "`skill_axe_tries` = " << player->skills[SKILL_AXE].tries << ",";
	query << "`skill_dist` = " << player->skills[SKILL_DISTANCE].level << ",";
	query << "`skill_dist_tries` = " << player->skills[SKILL_DISTANCE].tries << ",";
	query << "`skill_shielding` = " << player->skills[SKILL_SHIELD].level << ",";
	query << "`skill_shielding_tries` = " << player->skills[SKILL_SHIELD].tries << ",";
	query << "`skill_fishing` = " << player->skills[SKILL_FISHING].level << ",";
	query << "`skill_fishing_tries` = " << player->skills[SKILL_FISHING].tries << ",";
	query << "`skill_critical_hit_chance` = " << player->skills[SKILL_CRITICAL_HIT_CHANCE].level << ",";
	query << "`skill_critical_hit_chance_tries` = " << player->skills[SKILL_CRITICAL_HIT_CHANCE].tries << ",";
	query << "`skill_critical_hit_damage` = " << player->skills[SKILL_CRITICAL_HIT_DAMAGE].level << ",";
	query << "`skill_critical_hit_damage_tries` = " << player->skills[SKILL_CRITICAL_HIT_DAMAGE].tries << ",";
	query << "`skill_life_leech_chance` = " << player->skills[SKILL_LIFE_LEECH_CHANCE].level << ",";
	query << "`skill_life_leech_chance_tries` = " << player->skills[SKILL_LIFE_LEECH_CHANCE].tries << ",";
	query << "`skill_life_leech_amount` = " << player->skills[SKILL_LIFE_LEECH_AMOUNT].level << ",";
	query << "`skill_life_leech_amount_tries` = " << player->skills[SKILL_LIFE_LEECH_AMOUNT].tries << ",";
	query << "`skill_mana_leech_chance` = " << player->skills[SKILL_MANA_LEECH_CHANCE].level << ",";
	query << "`skill_mana_leech_chance_tries` = " << player->skills[SKILL_MANA_LEECH_CHANCE].tries << ",";
	query << "`skill_mana_leech_amount` = " << player->skills[SKILL_MANA_LEECH_AMOUNT].level << ",";
	query << "`skill_mana_leech_amount_tries` = " << player->skills[SKILL_MANA_LEECH_AMOUNT].tries << ",";
	query << "`manashield` = " << player->getManaShield() << ",";
	query << "`max_manashield` = " << player->getMaxManaShield() << ",";
	query << "`xpboost_value` = " << player->getStoreXpBoost() << ",";
	query << "`xpboost_stamina` = " << player->getExpBoostStamina() << ",";
	query << "`quickloot_fallback` = " << (player->quickLootFallbackToMainContainer ? 1 : 0) << ",";

	if (!player->isOffline()) {
		query << "`onlinetime` = `onlinetime` + " << (time(nullptr) - player->lastLoginSaved) << ",";
	}
	for (int i = 1; i <= 8; i++) {
		query << "`blessings" << i << "`"
			  << " = " << static_cast<uint32_t>(player->getBlessingCount(i)) << ((i == 8) ? " " : ",");
	}
	query << " WHERE `id` = " << player->getGUID();

	if (!db.executeQuery(query.str())) {
		return false;
	}
	return transaction.commit();
}

bool IOLoginDataSave::savePlayerStash(Player* player) {
	Database &db = Database::getInstance();
	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	std::ostringstream query;
	query << "DELETE FROM `player_stash` WHERE `player_id` = " << player->getGUID();
	if (!db.executeQuery(query.str())) {
		return false;
	}

	for (auto it : player->getStashItems()) {
		query.str("");
		query << "INSERT INTO `player_stash` (`player_id`,`item_id`,`item_count`) VALUES (";
		query << player->getGUID() << ", ";
		query << it.first << ", ";
		query << it.second << ")";
		if (!db.executeQuery(query.str())) {
			return false;
		}
	}
	return transaction.commit();
}

bool IOLoginDataSave::savePlayerSpells(Player* player) {
	Database &db = Database::getInstance();

	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	std::ostringstream query;
	query << "DELETE FROM `player_spells` WHERE `player_id` = " << player->getGUID();
	if (!db.executeQuery(query.str())) {
		return false;
	}

	query.str("");

	DBInsert spellsQuery("INSERT INTO `player_spells` (`player_id`, `name` ) VALUES ");
	for (const std::string &spellName : player->learnedInstantSpellList) {
		query << player->getGUID() << ',' << db.escapeString(spellName);
		if (!spellsQuery.addRow(query)) {
			return false;
		}
	}

	if (!spellsQuery.execute()) {
		return false;
	}
	return transaction.commit();
}

bool IOLoginDataSave::savePlayerKills(Player* player) {
	Database &db = Database::getInstance();

	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	std::ostringstream query;
	query << "DELETE FROM `player_kills` WHERE `player_id` = " << player->getGUID();
	if (!db.executeQuery(query.str())) {
		return false;
	}

	query.str("");

	DBInsert killsQuery("INSERT INTO `player_kills` (`player_id`, `target`, `time`, `unavenged`) VALUES");
	for (const auto &kill : player->unjustifiedKills) {
		query << player->getGUID() << ',' << kill.target << ',' << kill.time << ',' << kill.unavenged;
		if (!killsQuery.addRow(query)) {
			return false;
		}
	}

	if (!killsQuery.execute()) {
		return false;
	}
	return transaction.commit();
}

bool IOLoginDataSave::savePlayerBestiarySystem(Player* player) {
	Database &db = Database::getInstance();

	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	std::ostringstream query;
	query << "UPDATE `player_charms` SET ";

	query << "`charm_points` = " << player->charmPoints << ",";
	query << "`charm_expansion` = " << ((player->charmExpansion) ? 1 : 0) << ",";
	query << "`rune_wound` = " << player->charmRuneWound << ",";
	query << "`rune_enflame` = " << player->charmRuneEnflame << ",";
	query << "`rune_poison` = " << player->charmRunePoison << ",";
	query << "`rune_freeze` = " << player->charmRuneFreeze << ",";
	query << "`rune_zap` = " << player->charmRuneZap << ",";
	query << "`rune_curse` = " << player->charmRuneCurse << ",";
	query << "`rune_cripple` = " << player->charmRuneCripple << ",";
	query << "`rune_parry` = " << player->charmRuneParry << ",";
	query << "`rune_dodge` = " << player->charmRuneDodge << ",";
	query << "`rune_adrenaline` = " << player->charmRuneAdrenaline << ",";
	query << "`rune_numb` = " << player->charmRuneNumb << ",";
	query << "`rune_cleanse` = " << player->charmRuneCleanse << ",";
	query << "`rune_bless` = " << player->charmRuneBless << ",";
	query << "`rune_scavenge` = " << player->charmRuneScavenge << ",";
	query << "`rune_gut` = " << player->charmRuneGut << ",";
	query << "`rune_low_blow` = " << player->charmRuneLowBlow << ",";
	query << "`rune_divine` = " << player->charmRuneDivine << ",";
	query << "`rune_vamp` = " << player->charmRuneVamp << ",";
	query << "`rune_void` = " << player->charmRuneVoid << ",";
	query << "`UsedRunesBit` = " << player->UsedRunesBit << ",";
	query << "`UnlockedRunesBit` = " << player->UnlockedRunesBit << ",";

	PropWriteStream propBestiaryStream;
	for (MonsterType* trackedType : player->getBestiaryTrackerList()) {
		propBestiaryStream.write<uint16_t>(trackedType->info.raceid);
	}
	size_t trackerSize;
	const char* trackerList = propBestiaryStream.getStream(trackerSize);
	query << " `tracker list` = " << db.escapeBlob(trackerList, trackerSize);
	query << " WHERE `player_guid` = " << player->getGUID();

	if (!db.executeQuery(query.str())) {
		SPDLOG_WARN("[IOLoginData::savePlayer] - Error saving bestiary data from player: {}", player->getName());
		return false;
	}
	return transaction.commit();
}

bool IOLoginDataSave::savePlayerItem(Player* player) {
	Database &db = Database::getInstance();

	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	PropWriteStream propWriteStream;

	std::ostringstream query;
	query << "DELETE FROM `player_items` WHERE `player_id` = " << player->getGUID();
	if (!db.executeQuery(query.str())) {
		SPDLOG_WARN("[IOLoginData::savePlayer] - Error delete query 'player_items' from player: {}", player->getName());
		return false;
	}

	query.str("");

	DBInsert itemsQuery("INSERT INTO `player_items` (`player_id`, `pid`, `sid`, `itemtype`, `count`, `attributes`) VALUES ");

	ItemBlockList itemList;
	for (int32_t slotId = CONST_SLOT_FIRST; slotId <= CONST_SLOT_LAST; ++slotId) {
		Item* item = player->inventory[slotId];
		if (item) {
			itemList.emplace_back(slotId, item);
		}
	}

	if (!saveItems(player, itemList, itemsQuery, propWriteStream)) {
		SPDLOG_WARN("[IOLoginData::savePlayer] - Failed for save items from player: {}", player->getName());
		return false;
	}
	return transaction.commit();
}

bool IOLoginDataSave::savePlayerDepotItems(Player* player) {
	Database &db = Database::getInstance();

	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	PropWriteStream propWriteStream;

	ItemDepotList depotList;
	if (player->lastDepotId != -1) {
		std::ostringstream query;
		query << "DELETE FROM `player_depotitems` WHERE `player_id` = " << player->getGUID();

		if (!db.executeQuery(query.str())) {
			return false;
		}

		query.str("");

		DBInsert depotQuery("INSERT INTO `player_depotitems` (`player_id`, `pid`, `sid`, `itemtype`, `count`, `attributes`) VALUES ");

		for (const auto &it : player->depotChests) {
			DepotChest* depotChest = it.second;
			for (Item* item : depotChest->getItemList()) {
				depotList.emplace_back(it.first, item);
			}
		}

		if (!saveItems(player, depotList, depotQuery, propWriteStream)) {
			return false;
		}
		return transaction.commit();
	}
}

bool IOLoginDataSave::saveRewardItems(Player* player) {
	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	std::ostringstream query;
	query << "DELETE FROM `player_rewards` WHERE `player_id` = " << player->getGUID();

	if (!Database::getInstance().executeQuery(query.str())) {
		return false;
	}

	std::vector<uint64_t> rewardList;
	player->getRewardList(rewardList);

	ItemRewardList rewardListItems;
	if (!rewardList.empty()) {
		for (const auto &rewardId : rewardList) {
			auto reward = player->getReward(rewardId, false);
			if (!reward->empty() && (getTimeMsNow() - rewardId <= 1000 * 60 * 60 * 24 * 7)) {
				rewardListItems.emplace_back(0, reward);
			}
		}

		DBInsert rewardQuery("INSERT INTO `player_rewards` (`player_id`, `pid`, `sid`, `itemtype`, `count`, `attributes`) VALUES ");
		PropWriteStream propWriteStream;
		if (!saveItems(player, rewardListItems, rewardQuery, propWriteStream)) {
			return false;
		}
	}
	return transaction.commit();
}

bool IOLoginDataSave::savePlayerInbox(Player* player) {
	Database &db = Database::getInstance();

	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	PropWriteStream propWriteStream;
	ItemInboxList inboxList;

	std::ostringstream query;
	query << "DELETE FROM `player_inboxitems` WHERE `player_id` = " << player->getGUID();
	if (!db.executeQuery(query.str())) {
		return false;
	}

	query.str("");
	DBInsert inboxQuery("INSERT INTO `player_inboxitems` (`player_id`, `pid`, `sid`, `itemtype`, `count`, `attributes`) VALUES ");

	for (Item* item : player->getInbox()->getItemList()) {
		inboxList.emplace_back(0, item);
	}

	if (!saveItems(player, inboxList, inboxQuery, propWriteStream)) {
		return false;
	}
	return transaction.commit();
}

bool IOLoginDataSave::savePlayerPreyClass(Player* player) {
	Database &db = Database::getInstance();

	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	if (g_configManager().getBoolean(PREY_ENABLED)) {
		std::ostringstream query;
		query << "DELETE FROM `player_prey` WHERE `player_id` = " << player->getGUID();
		if (!db.executeQuery(query.str())) {
			return false;
		}

		for (uint8_t slotId = PreySlot_First; slotId <= PreySlot_Last; slotId++) {
			PreySlot* slot = player->getPreySlotById(static_cast<PreySlot_t>(slotId));
			if (slot) {
				query.str("");
				query << "INSERT INTO `player_prey` (`player_id`, `slot`, `state`, `raceid`, `option`, `bonus_type`, `bonus_rarity`, `bonus_percentage`, `bonus_time`, `free_reroll`, `monster_list`) VALUES (";
				query << player->getGUID() << ", ";
				query << static_cast<uint16_t>(slot->id) << ", ";
				query << static_cast<uint16_t>(slot->state) << ", ";
				query << slot->selectedRaceId << ", ";
				query << static_cast<uint16_t>(slot->option) << ", ";
				query << static_cast<uint16_t>(slot->bonus) << ", ";
				query << static_cast<uint16_t>(slot->bonusRarity) << ", ";
				query << slot->bonusPercentage << ", ";
				query << slot->bonusTimeLeft << ", ";
				query << slot->freeRerollTimeStamp << ", ";

				PropWriteStream propPreyStream;
				std::for_each(slot->raceIdList.begin(), slot->raceIdList.end(), [&propPreyStream](uint16_t raceId) {
					propPreyStream.write<uint16_t>(raceId);
				});

				size_t preySize;
				const char* preyList = propPreyStream.getStream(preySize);
				query << db.escapeBlob(preyList, static_cast<uint32_t>(preySize)) << ")";

				if (!db.executeQuery(query.str())) {
					SPDLOG_WARN("[IOLoginData::savePlayer] - Error saving prey slot data from player: {}", player->getName());
					return false;
				}
			}
		}
	}
	return transaction.commit();
}

bool IOLoginDataSave::savePlayerTaskHuntingClass(Player* player) {
	Database &db = Database::getInstance();

	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	if (g_configManager().getBoolean(TASK_HUNTING_ENABLED)) {
		std::ostringstream query;
		query << "DELETE FROM `player_taskhunt` WHERE `player_id` = " << player->getGUID();
		if (!db.executeQuery(query.str())) {
			return false;
		}

		for (uint8_t slotId = PreySlot_First; slotId <= PreySlot_Last; slotId++) {
			TaskHuntingSlot* slot = player->getTaskHuntingSlotById(static_cast<PreySlot_t>(slotId));
			if (slot) {
				query.str("");
				query << "INSERT INTO `player_taskhunt` (`player_id`, `slot`, `state`, `raceid`, `upgrade`, `rarity`, `kills`, `disabled_time`, `free_reroll`, `monster_list`) VALUES (";
				query << player->getGUID() << ", ";
				query << static_cast<uint16_t>(slot->id) << ", ";
				query << static_cast<uint16_t>(slot->state) << ", ";
				query << slot->selectedRaceId << ", ";
				query << (slot->upgrade ? 1 : 0) << ", ";
				query << static_cast<uint16_t>(slot->rarity) << ", ";
				query << slot->currentKills << ", ";
				query << slot->disabledUntilTimeStamp << ", ";
				query << slot->freeRerollTimeStamp << ", ";

				PropWriteStream propTaskHuntingStream;
				std::for_each(slot->raceIdList.begin(), slot->raceIdList.end(), [&propTaskHuntingStream](uint16_t raceId) {
					propTaskHuntingStream.write<uint16_t>(raceId);
				});

				size_t taskHuntingSize;
				const char* taskHuntingList = propTaskHuntingStream.getStream(taskHuntingSize);
				query << db.escapeBlob(taskHuntingList, static_cast<uint32_t>(taskHuntingSize)) << ")";

				if (!db.executeQuery(query.str())) {
					SPDLOG_WARN("[IOLoginData::savePlayer] - Error saving task hunting slot data from player: {}", player->getName());
					return false;
				}
			}
		}
	}
	return transaction.commit();
}

bool IOLoginDataSave::savePlayerForgeHistory(Player* player) {
	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	std::ostringstream query;
	query << "DELETE FROM `forge_history` WHERE `player_id` = " << player->getGUID();
	if (!Database::getInstance().executeQuery(query.str())) {
		return false;
	}

	query.str("");
	DBInsert insertQuery("INSERT INTO `forge_history` (`player_id`, `action_type`, `description`, `done_at`, `is_success`) VALUES");
	for (const auto &history : player->getForgeHistory()) {
		const auto stringDescription = Database::getInstance().escapeString(history.description);
		auto actionString = magic_enum::enum_integer(history.actionType);
		// Append query informations
		query << player->getGUID() << ','
			  << std::to_string(actionString) << ','
			  << stringDescription << ','
			  << history.createdAt << ','
			  << history.success;

		if (!insertQuery.addRow(query)) {
			return false;
		}
	}
	if (!insertQuery.execute()) {
		return false;
	}
	return transaction.commit();
}

bool IOLoginDataSave::savePlayerBosstiary(const Player* player) {
	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	std::ostringstream query;
	query << "DELETE FROM `player_bosstiary` WHERE `player_id` = " << player->getGUID();
	if (!Database::getInstance().executeQuery(query.str())) {
		return false;
	}

	query.str("");
	DBInsert insertQuery("INSERT INTO `player_bosstiary` (`player_id`, `bossIdSlotOne`, `bossIdSlotTwo`, `removeTimes`) VALUES");
	// Append query informations
	query << player->getGUID() << ','
		  << player->getSlotBossId(1) << ','
		  << player->getSlotBossId(2) << ','
		  << std::to_string(player->getRemoveTimes());

	if (!insertQuery.addRow(query)) {
		return false;
	}

	if (!insertQuery.execute()) {
		return false;
	}

	return transaction.commit();
}

bool IOLoginDataSave::savePlayerStorage(Player* player) {
	Database &db = Database::getInstance();
	DBTransaction transaction;
	if (!transaction.begin()) {
		return false;
	}

	std::ostringstream query;
	query << "DELETE FROM `player_storage` WHERE `player_id` = " << player->getGUID();
	if (!db.executeQuery(query.str())) {
		return false;
	}

	query.str("");

	DBInsert storageQuery("INSERT INTO `player_storage` (`player_id`, `key`, `value`) VALUES ");
	player->genReservedStorageRange();

	for (const auto &it : player->storageMap) {
		query << player->getGUID() << ',' << it.first << ',' << it.second;
		if (!storageQuery.addRow(query)) {
			return false;
		}
	}

	if (!storageQuery.execute()) {
		return false;
	}
	return transaction.commit();
}
