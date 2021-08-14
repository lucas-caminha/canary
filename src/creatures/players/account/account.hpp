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

#ifndef SRC_CREATURES_PLAYERS_ACCOUNT_ACCOUNT_HPP_
#define SRC_CREATURES_PLAYERS_ACCOUNT_ACCOUNT_HPP_

#include <string>
#include <vector>
#include <limits.h>

#include "database/database.h"
#include "database/databasetasks.h"
#include "utils/definitions.h"

namespace account {

enum Errors : uint8_t {
	ERROR_NO = 0,
	ERROR_DB,
	ERROR_INVALID_ACCOUNT_EMAIL,
	ERROR_INVALID_ACC_PASSWORD,
	ERROR_INVALID_ACC_TYPE,
	ERROR_INVALID_ID,
	ERROR_INVALID_LAST_DAY,
	ERROR_LOADING_ACCOUNT_PLAYERS,
	ERROR_NOT_INITIALIZED,
	ERROR_NULLPTR,
	ERROR_VALUE_NOT_ENOUGH_COINS,
	ERROR_VALUE_OVERFLOW,
	ERROR_PLAYER_NOT_FOUND
};

enum AccountType : uint8_t {
	ACCOUNT_TYPE_NORMAL = 1,
	ACCOUNT_TYPE_TUTOR = 2,
	ACCOUNT_TYPE_SENIORTUTOR = 3,
	ACCOUNT_TYPE_GAMEMASTER = 4,
	ACCOUNT_TYPE_GOD = 5
};

enum GroupType : uint8_t {
	GROUP_TYPE_NORMAL = 1,
	GROUP_TYPE_TUTOR = 2,
	GROUP_TYPE_SENIORTUTOR = 3,
	GROUP_TYPE_GAMEMASTER = 4,
	GROUP_TYPE_COMMUNITYMANAGER = 5,
	GROUP_TYPE_GOD = 6
};

enum CoinTransactionType : uint8_t {
	COIN_ADD = 1,
	COIN_REMOVE = 2
};

typedef struct {
	std::string name;
	uint64_t deletion;
} Player;

/**
 * @brief Account class to handle account information
 *
 */
class Account {
 public:
	/**
		* @brief Construct a new Account object
		*
		*/
	Account();

	/**
		* @brief Construct a new Account object
		*
		* @param id Set Account ID to be used by LoadAccountDB
		*/
	explicit Account(uint32_t id);

	/**
		* @brief Construct a new Account object
		*
		* @param name Set Account Name to be used by LoadAccountDB
		*/
	explicit Account(const std::string &name);

	/***************************************************************************
		* Interfaces
		**************************************************************************/

	/**
		* @brief Set the Database Interface used to get and set information from
		* the database
		*
		* @param database Database Interface pointer to be used
		* @return error_t ERROR_NO(0) Success, otherwise Fail.
		*/
	error_t SetDatabaseInterface(Database *database);

	/**
		* @brief Set the Database Tasks Interface used to schedule db update
		*
		* @param database Database Interface pointer to be used
		* @return error_t ERROR_NO(0) Success, otherwise Fail.
		*/
	error_t SetDatabaseTasksInterface(DatabaseTasks *db_tasks);


	/***************************************************************************
		* Coins Methods
		**************************************************************************/

	/**
		* @brief Get the amount of coins that the account has from database.
		*
		* @param accountId Account ID to get the coins.
		* @param coins Pointer to return the number of coins
		* @return error_t ERROR_NO(0) Success, otherwise Fail.
		*/
	error_t GetCoins(CoinType_t coinType = COIN_TYPE_DEFAULT);

	/**
		* @brief Add coins to the account and update database.
		*
		* @param amount Amount of coins to be added
		* @return error_t ERROR_NO(0) Success, otherwise Fail.
		*/
	error_t AddCoins(int32_t amount, CoinType_t coinType = COIN_TYPE_DEFAULT);

	/**
		* @brief Removes coins from the account and update database.
		*
		* @param amount Amount of coins to be removed
		* @return error_t ERROR_NO(0) Success, otherwise Fail.
		*/
	error_t RemoveCoins(int32_t amount, CoinType_t coinType = COIN_TYPE_DEFAULT);

	/**
		* @brief Register account coins transactions in database.
		*
		* @param type Type of the transaction(Add/Remove).
		* @param coins Amount of coins
		* @param description Description of the transaction
		* @return error_t ERROR_NO(0) Success, otherwise Fail.
		*/
	error_t RegisterCoinsTransaction(uint32_t time, uint8_t mode, uint32_t amount, uint8_t coinMode, std::string description, int32_t cust);

	/***************************************************************************
		* Database
		**************************************************************************/

	/**
		* @brief Try to load account from DB using Account ID or Name if they were
		* initialized.
		*
		* @return error_t ERROR_NO(0) Success, otherwise Fail.
		*/
	error_t LoadAccountDB();

	/**
		* @brief Try to
		*
		* @param name
		* @return error_t ERROR_NO(0) Success, otherwise Fail.
		*/
	error_t LoadAccountDB(std::string name);

	/**
		* @brief
		*
		* @param id
		* @return error_t ERROR_NO(0) Success, otherwise Fail.
		*/
	error_t LoadAccountDB(uint32_t id);

	/**
		* @brief
		*
		* @return error_t ERROR_NO(0) Success, otherwise Fail.
		*/
	error_t SaveAccountDB();


	/***************************************************************************
		* Setters and Getters
		**************************************************************************/

	error_t GetID(uint32_t *id);

	error_t SetEmail(std::string	name);
	error_t GetEmail(std::string *name);

	error_t SetPassword(std::string	password);
	error_t GetPassword(std::string *password);

	error_t SetPremiumRemaningDays(uint32_t	days);
	error_t GetPremiumRemaningDays(uint32_t *days);

	error_t SetStoreCoinBalance(uint32_t coins);
	error_t GetStoreCoinBalance(uint32_t *coins);

	error_t SetTournamentCoinBalance(uint32_t tournamentCoins);
	error_t GetTournamentCoinBalance(uint32_t *tournamentCoins);

	error_t SetPremiumLastDay(time_t	last_day);
	error_t GetPremiumLastDay(time_t *last_day);

	error_t SetAccountType(AccountType	account_type);
	error_t GetAccountType(AccountType *account_type);

	error_t GetAccountPlayer(Player *player, std::string& characterName);
	error_t GetAccountPlayers(std::vector<Player> *players);

 private:
	error_t SetID(uint32_t id);
	error_t LoadAccountDB(std::ostringstream &query);
	error_t LoadAccountPlayersDB(std::vector<Player> *players);
	error_t LoadAccountPlayerDB(Player *player, std::string& characterName);

	Database *db_;
	DatabaseTasks *db_tasks_;

	uint32_t id_;
	std::string email_;
	std::string password_;
	uint32_t premium_remaining_days_;
	time_t premium_last_day_;
	uint32_t coin_balance;
	uint32_t tournament_coin_balance;
	AccountType account_type_;
};

} // namespace account

#endif // SRC_CREATURES_PLAYERS_ACCOUNT_ACCOUNT_HPP_
