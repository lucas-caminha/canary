/**
 * The Forgotten Server - a free and open-source MMORPG server emulator
 * Copyright (C) 2019  Mark Samman <mark.samman@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef SRC_LUA_CREATURE_MOVEMENT_H_
#define SRC_LUA_CREATURE_MOVEMENT_H_

#include "declarations.hpp"
#include "items/item.h"
#include "lua/functions/events/move_event_functions.hpp"
#include "lua/scripts/scripts.h"
#include "creatures/players/vocations/vocation.h"

class MoveEvent;

struct MoveEventList {
	std::list<MoveEvent> moveEvent[MOVE_EVENT_LAST];
};

using VocEquipMap = std::map<uint16_t, bool>;

class MoveEvents final : public Scripts {
	public:
		MoveEvents() = default;
		~MoveEvents() = default;

		// non-copyable
		MoveEvents(const MoveEvents&) = delete;
		MoveEvents& operator=(const MoveEvents&) = delete;

		static MoveEvents& getInstance() {
			// Guaranteed to be destroyed
			static MoveEvents instance;
			// Instantiated on first use
			return instance;
		}

		uint32_t onCreatureMove(Creature& creature, Tile& tile, MoveEvent_t eventType);
		uint32_t onPlayerEquip(Player& player, Item& item, Slots_t slot, bool isCheck);
		uint32_t onPlayerDeEquip(Player& player, Item& item, Slots_t slot);
		uint32_t onItemMove(Item& item, Tile& tile, bool isAdd);

		std::map<Position, MoveEventList> getPositionsMap() const {
			return positionsMap;
		}

		bool hasPosition(Position position) const {
			if (auto it = positionsMap.find(position);
			it != positionsMap.end())
			{
				return true;
			}
			return false;
		}

		void setPosition(Position position, MoveEventList moveEventList) {
			positionsMap.try_emplace(position, moveEventList);
		}

		std::map<int32_t, MoveEventList> getItemIdMap() const {
			return itemIdMap;
		}

		bool hasItemId(int32_t itemId) const {
			if (auto it = itemIdMap.find(itemId);
			it != itemIdMap.end())
			{
				return true;
			}
			return false;
		}

		void setItemId(int32_t itemId, MoveEventList moveEventList) {
			itemIdMap.try_emplace(itemId, moveEventList);
		}

		std::map<int32_t, MoveEventList> getUniqueIdMap() const {
			return uniqueIdMap;
		}

		bool hasUniqueId(int32_t uniqueId) const {
			if (auto it = uniqueIdMap.find(uniqueId);
			it != uniqueIdMap.end())
			{
				return true;
			}
			return false;
		}

		void setUniqueId(int32_t uniqueId, MoveEventList moveEventList) {
			uniqueIdMap.try_emplace(uniqueId, moveEventList);
		}

		std::map<int32_t, MoveEventList> getActionIdMap() const {
			return actionIdMap;
		}

		bool hasActionId(int32_t actionId) const {
			if (auto it = actionIdMap.find(actionId);
			it != actionIdMap.end())
			{
				return true;
			}
			return false;
		}

		void setActionId(int32_t actionId, MoveEventList moveEventList) {
			actionIdMap.try_emplace(actionId, moveEventList);
		}

		MoveEvent* getEvent(Item& item, MoveEvent_t eventType);

		bool registerLuaItemEvent(MoveEvent& moveEvent);
		bool registerLuaActionEvent(MoveEvent& moveEvent);
		bool registerLuaUniqueEvent(MoveEvent& moveEvent);
		bool registerLuaPositionEvent(MoveEvent& moveEvent);
		bool registerLuaEvent(MoveEvent& moveEvent);
		void clear();

	private:
		void clearMap(std::map<int32_t, MoveEventList>& map) const;
		void clearPosMap(std::map<Position, MoveEventList>& map);

		void registerEvent(MoveEvent& moveEvent, int32_t id, std::map<int32_t, MoveEventList>& moveListMap) const;
		void registerEvent(MoveEvent& moveEvent, const Position& position, std::map<Position, MoveEventList>& moveListMap) const;
		MoveEvent* getEvent(Tile& tile, MoveEvent_t eventType);

		MoveEvent* getEvent(Item& item, MoveEvent_t eventType, Slots_t slot);

		std::map<int32_t, MoveEventList> uniqueIdMap;
		std::map<int32_t, MoveEventList> actionIdMap;
		std::map<int32_t, MoveEventList> itemIdMap;
		std::map<Position, MoveEventList> positionsMap;
};

constexpr auto g_moveEvents = &MoveEvents::getInstance;

class MoveEvent final : public Script {
	public:
		explicit MoveEvent(LuaScriptInterface* interface);

		MoveEvent_t getEventType() const;
		void setEventType(MoveEvent_t type);

		uint32_t fireStepEvent(Creature& creature, Item& item, const Position& pos);
		// No have item
		uint32_t fireStepEvent(Creature& creature, const Position& pos);
		uint32_t fireAddRemItem(Item& item, Item& tileItem, const Position& pos);
		uint32_t fireAddRemItem(Item& item, const Position& pos);
		uint32_t fireEquip(Player& player, Item& item, Slots_t slot, bool isCheck);

		uint32_t getSlot() const {
			return slot;
		}

		// Scripting to lua interface
		bool executeStep(Creature& creature, Item& item, const Position& pos);
		// No have item
		bool executeStep(Creature& creature, const Position& pos);
		bool executeEquip(Player& player, Item& item, Slots_t slot, bool isCheck);
		bool executeAddRemItem(Item& item, Item& tileItem, const Position& pos);
		// No have tile item
		bool executeAddRemItem(Item& item, const Position& pos);
		//

		//onEquip information
		uint32_t getReqLevel() const {
			return reqLevel;
		}
		uint32_t getReqMagLv() const {
			return reqMagLevel;
		}
		bool isPremium() const {
			return premium;
		}
		const std::string& getVocationString() const {
			return vocationString;
		}
		void setVocationString(const std::string& str) {
			vocationString = str;
		}
		uint32_t getWieldInfo() const {
			return wieldInfo;
		}
		const std::map<uint16_t, bool>& getVocEquipMap() const {
			return vocEquipMap;
		}
		void addVocEquipMap(std::string vocName) {
			int32_t vocationId = g_vocations().getVocationId(vocName);
			if (vocationId != -1) {
				vocEquipMap[vocationId] = true;
			}
		}
		bool getTileItem() const {
			return tileItem;
		}
		void setTileItem(bool b) {
			tileItem = b;
		}
		std::vector<uint32_t> getItemIdsVector() const {
			return itemIdVector;
		}
		void setItemId(uint32_t id) {
			itemIdVector.emplace_back(id);
		}
		std::vector<uint32_t> getActionIdsVector() const {
			return actionIdVector;
		}
		void setActionId(uint32_t id) {
			actionIdVector.emplace_back(id);
		}
		std::vector<uint32_t> getUniqueIdsVector() const {
			return uniqueIdVector;
		}
		void setUniqueId(uint32_t id) {
			uniqueIdVector.emplace_back(id);
		}
		std::vector<Position> getPositionsVector() const {
			return positionVector;
		}
		void setPosition(Position pos) {
			positionVector.emplace_back(pos);
		}
		const std::string& getFileName() const {
			return fileName;
		}
		void setFileName(const std::string& scriptName) {
			fileName = scriptName;
		}
		void setSlot(uint32_t s) {
			slot = s;
		}
		uint32_t getRequiredLevel() {
			return reqLevel;
		}
		void setRequiredLevel(uint32_t level) {
			reqLevel = level;
		}
		uint32_t getRequiredMagLevel() {
			return reqMagLevel;
		}
		void setRequiredMagLevel(uint32_t level) {
			reqMagLevel = level;
		}
		bool needPremium() {
			return premium;
		}
		void setNeedPremium(bool b) {
			premium = b;
		}
		uint32_t getWieldInfo() {
			return wieldInfo;
		}
		void setWieldInfo(WieldInfo_t info) {
			wieldInfo |= info;
		}

		static uint32_t StepInField(Creature* creature, Item* item, const Position& pos);
		static uint32_t StepOutField(Creature* creature, Item* item, const Position& pos);

		static uint32_t AddItemField(Item* item, Item* tileItem, const Position& pos);
		static uint32_t RemoveItemField(Item* item, Item* tileItem, const Position& pos);

		static uint32_t EquipItem(MoveEvent* moveEvent, Player* player, Item* item, Slots_t slot, bool boolean);
		static uint32_t DeEquipItem(MoveEvent* moveEvent, Player* player, Item* item, Slots_t slot, bool boolean);

	private:
		std::string getScriptTypeName() const override;

		std::string fileName;
		uint32_t slot = SLOTP_WHEREEVER;

		MoveEvent_t eventType = MOVE_EVENT_NONE;
		/// Step function
		std::function<uint32_t(
			Creature* creature,
			Item* item,
			const Position& pos
		)> stepFunction;
		// Move function
		std::function<uint32_t(
			Item* item,
			Item* tileItem,
			const Position& pos
		)> moveFunction;
		// equipFunction
		std::function<uint32_t(
			MoveEvent* moveEvent,
			Player* player,
			Item* item,
			Slots_t slot,
			bool boolean
		)> equipFunction;

		//onEquip information
		uint32_t reqLevel = 0;
		uint32_t reqMagLevel = 0;
		bool premium = false;
		std::string vocationString;
		uint32_t wieldInfo = 0;
		std::map<uint16_t, bool> vocEquipMap;
		bool tileItem = false;

		std::vector<uint32_t> itemIdVector;
		std::vector<uint32_t> actionIdVector;
		std::vector<uint32_t> uniqueIdVector;
		std::vector<Position> positionVector;

		friend class MoveEventFunctions;
};

#endif  // SRC_LUA_CREATURE_MOVEMENT_H_
