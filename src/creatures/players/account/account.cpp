/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (C) 2021 OpenTibiaBR <opentibiabr@outlook.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "otpch.h"

#include "creatures/players/account/account.hpp"
#include "database/databasetasks.h"
#include "game/game.h"

#include <algorithm>
#include <limits>

namespace account {

Account::Account() {
	id_ = 0;
	email_.clear();
	password_.clear();
	premium_remaining_days_ = 0;
	premium_last_day_ = 0;
	coin_balance = 0;
	tournament_coin_balance = 0;
	account_type_ = ACCOUNT_TYPE_NORMAL;
	db_ = &Database::getInstance();
	db_tasks_ = &g_databaseTasks;
}

Account::Account(uint32_t id) {
	id_ = id;
	email_.clear();
	password_.clear();
	premium_remaining_days_ = 0;
	premium_last_day_ = 0;
	coin_balance = 0;
	tournament_coin_balance = 0;
	account_type_ = ACCOUNT_TYPE_NORMAL;
	db_ = &Database::getInstance();
	db_tasks_ = &g_databaseTasks;
}

Account::Account(const std::string &email) : email_(email) {
	id_ = 0;
	password_.clear();
	premium_remaining_days_ = 0;
	premium_last_day_ = 0;
	coin_balance = 0;
	tournament_coin_balance = 0;
	account_type_ = ACCOUNT_TYPE_NORMAL;
	db_ = &Database::getInstance();
	db_tasks_ = &g_databaseTasks;
}


/*******************************************************************************
 * Interfaces
 ******************************************************************************/

error_t Account::SetDatabaseInterface(Database *database) {
	if (database == nullptr) {
		return ERROR_NULLPTR;
	}

	db_ = database;
	return ERROR_NO;
}

error_t Account::SetDatabaseTasksInterface(DatabaseTasks *database_tasks) {
	if (database_tasks == nullptr) {
		return ERROR_NULLPTR;
	}

	db_tasks_ = database_tasks;
	return ERROR_NO;
}


/*******************************************************************************
 * Coins Methods
 ******************************************************************************/

error_t Account::GetCoins(CoinType_t coinType) {
	if (db_ == nullptr || id_ == 0) {
		return ERROR_NOT_INITIALIZED;
	}

	std::string coins = "coins";
	if (coinType == COIN_TYPE_DEFAULT || coinType == COIN_TYPE_TRANSFERABLE) {
		coins = "coins";
	} else if (coinType == COIN_TYPE_TOURNAMENT) {
		coins = "tournamentBalance";
	}

	std::ostringstream query;
	query << "SELECT `" << coins << "` FROM `accounts` WHERE `id` = " << id_;

	DBResult_ptr result = db_->storeQuery(query.str());
	if (!result) {
		return ERROR_DB;
	}

	return result->getNumber<uint32_t>(coins);
}

error_t Account::AddCoins(int32_t amount, CoinType_t coinType)
{
	std::string coins = "coins";
	if (coinType == COIN_TYPE_DEFAULT || coinType == COIN_TYPE_TRANSFERABLE) {
		coins = "coins";
	} else if (coinType == COIN_TYPE_TOURNAMENT) {
		coins = "tournamentBalance";
	}
	std::ostringstream query;
	query << "UPDATE `accounts` SET `" << coins << "` = `" << coins << "` + " << amount << " WHERE `id` = " << id_;

	db_tasks_->addTask(query.str());
	return ERROR_NO;
}

error_t Account::RemoveCoins(int32_t amount, CoinType_t coinType) {

	if (db_tasks_ == nullptr) {
		return ERROR_NULLPTR;
	}

	if (amount == 0)	{
		return ERROR_NO;
	}

	std::string coins = "`coins`";
	if (coinType == COIN_TYPE_DEFAULT || coinType == COIN_TYPE_TRANSFERABLE) {
		coins = "`coins`";
	} else if (coinType == COIN_TYPE_TOURNAMENT) {
		coins = "`tournamentBalance`";
	}
	std::ostringstream query;
	query << "UPDATE `accounts` SET " << coins << " = " << coins << " - " << amount << " WHERE `id` = " << id_;

	db_tasks_->addTask(query.str());
	return ERROR_NO;
}

error_t Account::RegisterCoinsTransaction(uint32_t time, uint8_t mode, uint32_t amount, uint8_t coinMode, std::string description, int32_t cust)
{
	if (db_ == nullptr) {
		return ERROR_NULLPTR;
	}

	std::ostringstream query;
	query << "INSERT INTO `store_history` (`account_id`, `time`, `mode`, `amount`, `coinMode`, `description`, `cust`) VALUES ("
		<< id_ << ","
		<< time << ","
		<< static_cast<uint16_t>(mode) << ","
		<< amount << "," << static_cast<uint16_t>(coinMode) << ","
		<< db_->escapeString(description) << ","
	<< cust << ")";

	if (!db_->executeQuery(query.str())) {
		return ERROR_DB;
	}

	StoreHistory historyOffer(time, mode, amount, coinMode, description, cust);
	g_game.addAccountHistory(id_, historyOffer);

	db_->executeQuery(query.str());
	return ERROR_NO;
}

/*******************************************************************************
 * Database
 ******************************************************************************/

error_t Account::LoadAccountDB() {
	if (id_ != 0) {
		return this->LoadAccountDB(id_);
	} else if (!email_.empty()) {
		return this->LoadAccountDB(email_);
	}

	return ERROR_NOT_INITIALIZED;
}

error_t Account::LoadAccountDB(std::string email) {
	std::ostringstream query;
	query << "SELECT * FROM `accounts` WHERE `email` = "
			<< db_->escapeString(email);
	return this->LoadAccountDB(query);
}

error_t Account::LoadAccountDB(uint32_t id) {
	std::ostringstream query;
	query << "SELECT * FROM `accounts` WHERE `id` = " << id;
	return this->LoadAccountDB(query);
}

error_t Account::LoadAccountDB(std::ostringstream &query) {
	if (db_ == nullptr) {
		return ERROR_NULLPTR;
	}

	DBResult_ptr result = db_->storeQuery(query.str());
	if (!result) {
		return false;
	}

	this->SetID(result->getNumber<uint32_t>("id"));
	this->SetEmail(result->getString("email"));
	this->SetAccountType(static_cast<AccountType>(result->getNumber<int32_t>("type")));
	this->SetPassword(result->getString("password"));
	this->SetPremiumRemaningDays(result->getNumber<uint16_t>("premdays"));
	this->SetPremiumLastDay(result->getNumber<time_t>("lastday"));
	this->SetStoreCoinBalance(result->getNumber<uint32_t>("coins"));
	this->SetTournamentCoinBalance(result->getNumber<uint32_t>("tournamentBalance"));

	return ERROR_NO;
}

error_t Account::LoadAccountPlayerDB(Player *player, std::string& characterName) {
	if (id_ == 0) {
		return ERROR_NOT_INITIALIZED;
	}

	std::ostringstream query;
	query << "SELECT `name`, `deletion` FROM `players` WHERE `account_id` = "
				<< id_ << " AND `name` = " << db_->escapeString(characterName)
	<< " ORDER BY `name` ASC";

	DBResult_ptr result = db_->storeQuery(query.str());
	if (!result || result->getNumber<uint64_t>("deletion") != 0) {
		return ERROR_PLAYER_NOT_FOUND;
	}

	player->name = result->getString("name");
	player->deletion = result->getNumber<uint64_t>("deletion");

	return ERROR_NO;
}

error_t Account::LoadAccountPlayersDB(std::vector<Player> *players) {
	if (id_ == 0) {
		return ERROR_NOT_INITIALIZED;
	}

	std::ostringstream query;
	query << "SELECT `name`, `deletion` FROM `players` WHERE `account_id` = "
				<< id_ << " ORDER BY `name` ASC";

	DBResult_ptr result = db_->storeQuery(query.str());
	if (!result) {
		return ERROR_DB;
	}

	do {
		if (result->getNumber<uint64_t>("deletion") == 0) {
			Player new_player;
			new_player.name = result->getString("name");
			new_player.deletion = result->getNumber<uint64_t>("deletion");
			players->push_back(new_player);
		}
	} while (result->next());
	return ERROR_NO;
}

error_t Account::SaveAccountDB() {
	std::ostringstream query;

	query << "UPDATE `accounts` SET "
				<< "`email` = " << db_->escapeString(email_) << " , "
				<< "`type` = " << account_type_ << " , "
				<< "`password` = " << db_->escapeString(password_) << " , "
				<< "`coins` = " << coin_balance << " , "
				<< "`tournamentBalance` = " << tournament_coin_balance << " , "
				<< "`premdays` = " << premium_remaining_days_ << " , "
	<< "`lastday` = " << premium_last_day_;

	if (id_ != 0) {
		query << " WHERE `id` = " << id_;
	} else if (!email_.empty()) {
		query << " WHERE `email` = " << email_;
	}

	if (!db_->executeQuery(query.str())) {
		return ERROR_DB;
	}

	return ERROR_NO;
}

/*******************************************************************************
 * Setters and Getters
 ******************************************************************************/

error_t Account::SetID(uint32_t id) {
	if (id == 0) {
		return ERROR_INVALID_ID;
	}
	id_ = id;
	return ERROR_NO;
}

error_t Account::GetID(uint32_t *id) {
	if (id == nullptr) {
		return ERROR_NULLPTR;
	}

	*id = id_;
	return ERROR_NO;
}

error_t Account::SetEmail(std::string email) {
	if (email.empty()) {
		return ERROR_INVALID_ACCOUNT_EMAIL;
	}
	email_ = email;
	return ERROR_NO;
}

error_t Account::GetEmail(std::string *email) {
	if (email == nullptr) {
		return ERROR_NULLPTR;
	}

	*email = email_;
	return ERROR_NO;
}

error_t Account::SetPassword(std::string password) {
	if (password.empty()) {
		return ERROR_INVALID_ACC_PASSWORD;
	}
	password_ = password;
	return ERROR_NO;
}

error_t Account::GetPassword(std::string *password) {
	if (password == nullptr) {
		return ERROR_NULLPTR;
	}

	*password = password_;
	return ERROR_NO;
}

error_t Account::SetPremiumRemaningDays(uint32_t days) {
	premium_remaining_days_ = days;
	return ERROR_NO;
}

error_t Account::GetPremiumRemaningDays(uint32_t *days) {
	if (days == nullptr) {
		return ERROR_NULLPTR;
	}

	*days = premium_remaining_days_;
	return ERROR_NO;
}

error_t Account::SetPremiumLastDay(time_t last_day) {
	if (last_day < 0) {
		return ERROR_INVALID_LAST_DAY;
	}
	premium_last_day_ = last_day;
	return ERROR_NO;
}

error_t Account::GetPremiumLastDay(time_t *last_day) {
	if (last_day == nullptr) {
		return ERROR_NULLPTR;
	}

	*last_day = premium_last_day_;
	return ERROR_NO;
}

error_t Account::SetStoreCoinBalance(uint32_t coins) {
	if (coins == 0) {
		return ERROR_INVALID_ID;
	}

	coin_balance = coins;
	return ERROR_NO;
}

error_t Account::GetStoreCoinBalance(uint32_t *coins) {
	if (coins == nullptr) {
		return ERROR_NULLPTR;
	}

	*coins = coin_balance;
	return ERROR_NO;
}

error_t Account::SetTournamentCoinBalance(uint32_t tournamentCoins) {
	if (tournamentCoins == 0) {
		return ERROR_INVALID_ID;
	}

	tournament_coin_balance = tournamentCoins;
	return ERROR_NO;
}

error_t Account::GetTournamentCoinBalance(uint32_t *tournamentCoins) {
	if (tournamentCoins == nullptr) {
		return ERROR_NULLPTR;
	}

	*tournamentCoins = tournament_coin_balance;
	return ERROR_NO;
}

error_t Account::SetAccountType(AccountType account_type) {
	if (account_type > 5) {
		return ERROR_INVALID_ACC_TYPE;
	}
	account_type_ = account_type;
	return ERROR_NO;
}

error_t Account::GetAccountType(AccountType *account_type) {
	if (account_type == nullptr) {
		return ERROR_NULLPTR;
	}

	*account_type = account_type_;
	return ERROR_NO;
}

error_t Account::GetAccountPlayer(Player *player, std::string& characterName) {
	if (player == nullptr) {
		return ERROR_NULLPTR;
	}

	return this->LoadAccountPlayerDB(player, characterName);
}

error_t Account::GetAccountPlayers(std::vector<Player> *players) {
	if (players == nullptr) {
		return ERROR_NULLPTR;
	}

	return this->LoadAccountPlayersDB(players);
}

}	// namespace account
