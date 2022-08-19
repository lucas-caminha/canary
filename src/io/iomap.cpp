/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.org/
*/

#include "otpch.h"

#include "io/iomap.h"

#include "items/bed.h"
#include "game/movement/teleport.h"

#include "map/flatbuffer/kmap_generated.h"
#include "flatbuffers/flatbuffers.h"

#include <fstream>
#include <filesystem>

Tile* IOMap::createTile(Item* ground, Item* item, uint16_t x, uint16_t y, uint8_t z)
{
	if (!ground) {
		return new StaticTile(x, y, z);
	}

	Tile *tile;
	if ((item && item->isBlocking()) || ground->isBlocking()) {
		tile = new StaticTile(x, y, z);
	} else {
		tile = new DynamicTile(x, y, z);
	}

	tile->internalAddThing(ground);
	ground->startDecaying();
	ground = nullptr;
	return tile;
}

bool IOMap::loadMap(Map &serverMap, const std::string &fileName)
{
	int64_t start = OTSYS_TIME();
	std::fstream fileStream(fileName, std::ios:: in | std::ios::binary);
	if (!fileStream.is_open())
	{
		SPDLOG_ERROR("Unable to load {}, could not open file", fileName);
		return false;
	}

	if (!fileStream.good())
	{
		SPDLOG_ERROR("Unable to load {}, error for read file", fileName);
		return false;
	}

	// Read Binary data using streambuffer iterators
	std::vector<uint8_t> fileBuffer((std::istreambuf_iterator<char> (fileStream)), (std::istreambuf_iterator<char> ()));
	buffer = fileBuffer;
	fileBuffer.clear();
	fileStream.close();

	fileLoaded = true;

	// Get a pointer to the root object inside the buffer
	auto map = Kmap::GetMap(buffer.data());
	auto header = map->header();
	serverMap.width = header->width();
	serverMap.height = header->height();
	SPDLOG_INFO("Map size: {}x{}", serverMap.width, serverMap.height);

	std::string descriptionFile = header->description()->str();
	std::string monsterFile = header->monster_spawn_file()->str();
	std::string npcFile = header->npc_spawn_file()->str();
	std::string houseFile = header->house_file()->str();

	serverMap.monsterfile = fileName.substr(0, fileName.rfind('/') + 1);
	serverMap.monsterfile += monsterFile;

	serverMap.npcfile = fileName.substr(0, fileName.rfind('/') + 1);
	serverMap.npcfile += npcFile;

	serverMap.housefile = fileName.substr(0, fileName.rfind('/') + 1);
	serverMap.housefile += houseFile;

	auto mapData = map->data();
	// Areas vector
	for (auto area: *mapData->areas())
	{
		auto areaPosition = area->position();
		// Teleport vector
		static std::map<Position, Position> teleportMap;

		// Tiles vector reading
		for (auto tiles: *area->tiles())
		{
			const Position tilePosition(
				areaPosition->x() + tiles->x(),
				areaPosition->y() + tiles->y(),
				areaPosition->z()
			);

			// Parse tile flags
			uint32_t mapTileFlags = TILESTATE_NONE;
			if (const uint32_t flags = tiles->flags();
				(flags & OTBM_TILEFLAG_PROTECTIONZONE) != 0)
			{
				mapTileFlags |= TILESTATE_PROTECTIONZONE;
			}
			else if ((flags & OTBM_TILEFLAG_NOPVPZONE) != 0)
			{
				mapTileFlags |= TILESTATE_NOPVPZONE;
			}
			else if ((flags & OTBM_TILEFLAG_PVPZONE) != 0)
			{
				mapTileFlags |= TILESTATE_PVPZONE;
			}

			if ((mapTileFlags & OTBM_TILEFLAG_NOLOGOUT) != 0)
			{
				mapTileFlags |= TILESTATE_NOLOGOUT;
			}


			Tile *tile = nullptr;
			Item *groundItem = nullptr;
			House* house = nullptr;
	
			// Create house tiles
			auto houseInfo = tiles->house_info();
			if (houseInfo) {
				uint32_t houseId = 0;
				if (houseInfo) {
					houseId = houseInfo->id();
				}
				//SPDLOG_INFO("Found house id {}, on position {}", houseId, tilePosition.toString());
				house = serverMap.houses.addHouse(houseId);
				if (house == nullptr)
				{
					SPDLOG_ERROR("{} - Could not create house id: {}, on position: {}", __FUNCTION__, houseId, tilePosition.toString());
					continue;
				}

				tile = new HouseTile(tilePosition.x, tilePosition.y, tilePosition.z, house);
				if (tile == nullptr)
				{
					SPDLOG_ERROR("{} - Tile is nullptr, discarding house id: {}, on position: {}", __FUNCTION__, houseId, tilePosition.toString());
					continue;
				}

				house->addTile(static_cast<HouseTile*>(tile));
			}

			// Create tile items
			Item *itemTile = Item::createMapItem(tiles->tile_id());
			if (itemTile) {
				// Load house item tiles
				if (tile) {
					tile->internalAddThing(itemTile);
					itemTile->startDecaying();
					itemTile->setLoadedFromMap(true);
				// Load ground item tiles
				} else if (itemTile->isGroundTile()) {
					delete groundItem;
					groundItem = itemTile;
				// Create others item tiles
				} else {
					tile = createTile(groundItem, itemTile, tilePosition.x, tilePosition.y, tilePosition.z);
					tile->internalAddThing(itemTile);
					itemTile->startDecaying();
					itemTile->setLoadedFromMap(true);
				}
			}

			// Create map items
			for (auto items: *tiles->items())
			{
				Item *item = Item::createMapItem(items->id());
				if (item) {
					// Load house item tiles
					if (tile) {
						tile->internalAddThing(item);
						item->startDecaying();
						item->setLoadedFromMap(true);
					// Load ground item tiles
					} else if (item->isGroundTile()) {
						delete groundItem;
						groundItem = item;
					// Create others item tiles
					} else {
						tile = createTile(groundItem, item, tilePosition.x, tilePosition.y, tilePosition.z);
						tile->internalAddThing(item);
						item->startDecaying();
						item->setLoadedFromMap(true);
					}
				}
			}

			if (tile == nullptr) {
				tile = createTile(groundItem, nullptr, tilePosition.x, tilePosition.y, tilePosition.z);
			}

			tile->setFlag(static_cast<TileFlags_t>(mapTileFlags));

			serverMap.setTile(tilePosition, tile);
		}
	}

	for (auto towns: *mapData->towns())
	{
		Town *town = nullptr;
		// Sanity check, if the town id is wrong then we know where the problem is
		const uint32_t townId = towns->id();
		if (townId == 0)
		{
			SPDLOG_ERROR("{} - Invalid town id: {}", __FUNCTION__, townId);
			continue;
		}

		town = serverMap.towns.getTown(townId);
		if (town)
		{
			SPDLOG_ERROR("{} - Duplicate town with id: {}, discarding town", __FUNCTION__, townId);
			continue;
		}

		// Creating new town variable to avoid use of "new"
		town = new Town(townId);
		if (!serverMap.towns.addTown(townId, town))
		{
			SPDLOG_ERROR("{} - Cannot create town with id: {}, discarding town", __FUNCTION__, townId);
			delete town;
			continue;
		}

		// Sanity check, if the string is empty then we know where the problem is
		const std::string townName = towns->name()->str();
		if (townName.empty())
		{
			SPDLOG_ERROR("{} - Could not read town name for town id {}", __FUNCTION__, townId);
			continue;
		}

		town->setName(townName);

		Position townPosition;
		townPosition.x = towns->position()->x();
		townPosition.y = towns->position()->y();
		townPosition.z = towns->position()->z();
		// Sanity check, if there is an error in the get, we will know where the problem is
		if (townPosition.x == 0 || townPosition.y == 0 || townPosition.z == 0)
		{
			SPDLOG_ERROR("{} - Invalid town position", __FUNCTION__);
			continue;
		}

		// Set towns in the map
		town->setTemplePos(townPosition);
	}

	for (auto waypoints: *mapData->waypoints())
	{
		// Sanity check, if the string is empty then we know where the problem is
		const std::string waypointName = waypoints->name()->str();
		if (waypointName.empty())
		{
			SPDLOG_ERROR("{} - Could not read waypoint name", __FUNCTION__);
			continue;
		}

		Position waypointPosition;
		waypointPosition.x = waypoints->position()->x();
		waypointPosition.y = waypoints->position()->y();
		waypointPosition.z = waypoints->position()->z();
		// Sanity check, if there is an error in the get, we will know where the problem is
		if (waypointPosition.x == 0 || waypointPosition.y == 0 || waypointPosition.z == 0)
		{
			SPDLOG_ERROR("{} - Invalid waypoint position", __FUNCTION__);
			continue;
		}

		// Set waypoints in the map
		serverMap.waypoints[waypointName] = waypointPosition;
	}

	SPDLOG_INFO("Map loading time: {} seconds", (OTSYS_TIME() - start) / (1000.));
	return true;
}

bool IOMap::parseMapDataAttributes(BinaryNode &binaryNodeMapData, Map& map, const std::string& fileName) const
{
	if (binaryNodeMapData.getU8() != OTBM_MAP_DATA) {
		SPDLOG_ERROR("[IOMap::parseMapDataAttributes] - Could not read root data node");
		return false;
	}

	while (binaryNodeMapData.canRead()) {
		const uint8_t attribute = binaryNodeMapData.getU8();
		std::string mapDataString = binaryNodeMapData.getString();
		switch (attribute) {
			case OTBM_ATTR_DESCRIPTION:
				break;
			case OTBM_ATTR_EXT_SPAWN_MONSTER_FILE:
				map.monsterfile = fileName.substr(0, fileName.rfind('/') + 1);
				map.monsterfile += mapDataString;
				break;
			case OTBM_ATTR_EXT_HOUSE_FILE:
				map.housefile = fileName.substr(0, fileName.rfind('/') + 1);
				map.housefile += mapDataString;
				break;
			case OTBM_ATTR_EXT_SPAWN_NPC_FILE:
				map.npcfile = fileName.substr(0, fileName.rfind('/') + 1);
				map.npcfile += mapDataString;
				break;
			default:
				SPDLOG_ERROR("[IOMap::parseMapDataAttributes] - Could not get map data node. Invalid map data attribute: {}", attribute);
				return false;
		}
	}
	return true;
}

void IOMap::readAttributeTileFlags(BinaryNode &binaryNodeMapTile, uint32_t &tileflags) const
{
	if (const uint32_t flags = binaryNodeMapTile.getU32();
	(flags & OTBM_TILEFLAG_PROTECTIONZONE) != 0)
	{
		tileflags |= TILESTATE_PROTECTIONZONE;
	} else if ((flags & OTBM_TILEFLAG_NOPVPZONE) != 0) {
		tileflags |= TILESTATE_NOPVPZONE;
	} else if ((flags & OTBM_TILEFLAG_PVPZONE) != 0) {
		tileflags |= TILESTATE_PVPZONE;
	}

	if ((tileflags & OTBM_TILEFLAG_NOLOGOUT) != 0) {
		tileflags |= TILESTATE_NOLOGOUT;
	}
}

std::tuple<Tile*, Item*> IOMap::readAttributeTileItem(BinaryNode &binaryNodeMapTile, std::map<Position, Position> &teleportMap, bool isHouseTile, const House *house, Item *groundItem, Tile *tile, Position tilePosition) const
{
	/*Item* item = Item::createMapItem(binaryNodeMapTile);
	if (!item) {
		SPDLOG_ERROR("[IOMap::readAttributeTileItem] - Failed to create item on position: {}", tilePosition.toString());
		return std::make_tuple(nullptr, nullptr);
	}

	if (const Teleport* teleport = item->getTeleport()) {
		// Teleport position / teleport destination
		teleportMap.emplace(tilePosition, teleport->getDestination());
		if (teleportMap.contains(teleport->getDestination())) {
			SPDLOG_WARN("[IOMap::readAttributeTileItem] - "
						"Teleport in position: {} "
						"is leading to another teleport", tilePosition.toString());
			return std::make_tuple(nullptr, nullptr);
		}
		for (auto const& [mapTeleportPosition, mapDestinationPosition] : teleportMap) {
			if (mapDestinationPosition == tilePosition) {
				SPDLOG_WARN("IOMap::readAttributeTileItem] - "
							"Teleport in position: {} "
							"is leading to another teleport",
							mapDestinationPosition.toString());
				continue;
			}
		}
	}

	if (isHouseTile && house && item->isMoveable()) {
		SPDLOG_WARN("[IOMap::readAttributeTileItem] - "
					"Moveable item with ID: {}, in house: {}, "
					"at position: {}, discarding item",
					item->getID(), house->getId(), tilePosition.toString());
		delete item;
		return std::make_tuple(nullptr, nullptr);
	}

	// Check if is house items
	if (tile) {
		tile->internalAddThing(0, item);
		item->startDecaying();
		item->setLoadedFromMap(true);
	} else if (item->isGroundTile()) {
		delete groundItem;
		groundItem = item;
	} else {
		// Creating walls and others blocking items
		tile = createTile(groundItem, item, tilePosition.x, tilePosition.y, tilePosition.z);
		tile->internalAddThing(item);
		item->startDecaying();
		item->setLoadedFromMap(true);
	}*/
	return std::make_tuple(tile, groundItem);
}

std::tuple<Tile*, Item*> IOMap::parseCreateTileItem(BinaryNode &nodeItem, bool isHouseTile, const House *house, Item *groundItem, Tile *tile, Position tilePosition) const
{
	/*Item* item = Item::createMapItem(nodeItem);
	if (!item) {
		SPDLOG_ERROR("[IOMap::parseCreateTileItem] - Failed to create item on position {}", tilePosition.toString());
		return std::make_tuple(nullptr, nullptr);
	}

	if (!item->unserializeMapItem(nodeItem, tilePosition)) {
		SPDLOG_ERROR("[IOMap::parseCreateTileItem] - Failed to load item with id: {}, on position {}", item->getID(), tilePosition.toString());
		delete item;
		return std::make_tuple(nullptr, nullptr);
	}

	if (isHouseTile && house && item->isMoveable()) {
		SPDLOG_WARN("[IOMap::parseCreateTileItem] - "
					"Moveable item with ID: {}, in house: {}, "
					"at position: {}, discarding item",
					item->getID(), house->getId(), tilePosition.toString());
		delete item;
		return std::make_tuple(nullptr, nullptr);
	}

	if (tile) {
		tile->internalAddThing(item);
		item->startDecaying();
		item->setLoadedFromMap(true);
	} else if (item->isGroundTile()) {
		delete groundItem;
		groundItem = item;
	} else {
		tile = createTile(groundItem, item, tilePosition.x, tilePosition.y, tilePosition.z);
		tile->internalAddThing(item);
		item->startDecaying();
		item->setLoadedFromMap(true);
	}*/
	return std::make_tuple(tile, groundItem);
}

bool IOMap::parseTileArea(BinaryNode &binaryNodeMapData, Map& map) const
{
	Position baseMapPosition;
	baseMapPosition.x = binaryNodeMapData.getU16();
	baseMapPosition.y = binaryNodeMapData.getU16();
	baseMapPosition.z = binaryNodeMapData.getU8();

	static std::map<Position, Position> teleportMap;
	for (std::shared_ptr<BinaryNode> binaryNodeMapTile = binaryNodeMapData.getChild();
	binaryNodeMapTile != nullptr; binaryNodeMapTile = binaryNodeMapTile->advance()) {
		const uint8_t type = binaryNodeMapTile->getU8();
		if (type == 0) {
			SPDLOG_ERROR("[IOMap::parseTileArea] - Invalid node tile with type {}", type);
			break;
		}

		Position tilePosition;
		tilePosition.x = baseMapPosition.x + binaryNodeMapTile->getU8();
		tilePosition.y = baseMapPosition.y + binaryNodeMapTile->getU8();
		tilePosition.z = baseMapPosition.z;

		bool isHouseTile = false;
		House *house = nullptr;
		Tile *tile = nullptr;
		Item *groundItem = nullptr;
		uint32_t tileflags = TILESTATE_NONE;

		// Parsing houses load and creation
		if (type == OTBM_HOUSETILE) {
			const uint32_t houseId = binaryNodeMapTile->getU32();
			house = map.houses.addHouse(houseId);
			if (house == nullptr) {
				SPDLOG_ERROR("[IOMap::parseTileArea] - Could not create house id: {}, on position: {}", houseId, tilePosition.toString());
				continue;
			}

			tile = new HouseTile(tilePosition.x, tilePosition.y, tilePosition.z, house);
			if (tile == nullptr) {
				SPDLOG_ERROR("[IOMap::parseTileArea] - Tile is nullptr, discarding house id: {}, on position: {}", houseId, tilePosition.toString());
				continue;
			}

			house->addTile(static_cast<HouseTile*>(tile));
			isHouseTile = true;
		}

		while (binaryNodeMapTile->canRead()) {
			const uint8_t tileAttr = binaryNodeMapTile->getU8();
			switch (tileAttr) {
			case OTBM_ATTR_TILE_FLAGS:
				readAttributeTileFlags(*binaryNodeMapTile, tileflags);
				break;
			case OTBM_ATTR_ITEM:
				std::tie(tile, groundItem) = readAttributeTileItem(*binaryNodeMapTile, teleportMap, isHouseTile, house, groundItem, tile, tilePosition);
				break;
			default:
				SPDLOG_ERROR("[IOMap::parseTileArea] - Invalid tile attribute: {}, at position: {}", tileAttr, tilePosition.toString());
				return false;
			}

		}

		for (std::shared_ptr<BinaryNode> nodeItem = binaryNodeMapTile->getChild(); nodeItem != nullptr; nodeItem = nodeItem->advance()) {
			if (nodeItem->getU8() != OTBM_ITEM) {
				SPDLOG_ERROR("[IOMap::parseTileArea] - Unknown item node with type {}, at position {}", type, tilePosition.toString());
				continue;
			}

			std::tie(tile, groundItem) = parseCreateTileItem(*nodeItem, isHouseTile, house, groundItem, tile, tilePosition);
		}

		if (tile == nullptr) {
			tile = createTile(groundItem, nullptr, tilePosition.x, tilePosition.y, tilePosition.z);
		}

		// Sanity check, it will probably never happen, but it doesn't hurt to put this
		if (tile == nullptr) {
			SPDLOG_ERROR("[IOMap::parseTileArea] - Tile is nullptr");
			continue;
		}

		tile->setFlag(static_cast<TileFlags_t>(tileflags));
		map.setTile(tilePosition, tile);
	}
	return true;
}

// Parse towns information data
bool IOMap::parseTowns(BinaryNode &binaryNodeMapData, Map& map)
{
	Town *town = nullptr;
	for (std::shared_ptr<BinaryNode> binaryNodeTown = binaryNodeMapData.getChild();
	binaryNodeTown != nullptr; binaryNodeTown = binaryNodeTown->advance())
	{
		if (binaryNodeTown->getU8() != OTBM_TOWN) {
			SPDLOG_ERROR("[IOMap::parseTowns] - Invalid town node");
			continue;
		}

		// Sanity check, if the town id is wrong then we know where the problem is
		const uint32_t townId = binaryNodeTown->getU32();
		if (townId == 0) {
			SPDLOG_ERROR("[IOMap::parseTowns] - Invalid town id");
			continue;
		}

		town = map.towns.getTown(townId);
		if(town) {
			SPDLOG_ERROR("[IOMap::parseTowns] - Duplicate town with id: {}, discarding town", townId);
			continue;
		}

		// Creating new town variable to avoid use of "new"
		town = new Town(townId);
		if(!map.towns.addTown(townId, town)) {
			SPDLOG_ERROR("[IOMap::parseTowns] - Cannot create town with id: {}, discarding town", townId);
			delete town;
			continue;
		}

		// Sanity check, if the string is empty then we know where the problem is
		const std::string townName = binaryNodeTown->getString();
		if (townName.empty()) {
			SPDLOG_ERROR("[IOMap::parseTowns] - Could not read town name");
			continue;
		}
		town->setName(townName);

		uint16_t positionX = binaryNodeTown->getU16();
		uint16_t positionY = binaryNodeTown->getU16();
		uint8_t positionZ = binaryNodeTown->getU8();
		// Sanity check, if there is an error in the get, we will know where the problem is
		if(positionX == 0 || positionY == 0 || positionZ == 0) {
			SPDLOG_ERROR("[IOMap::parseTowns] - Invalid town position");
			continue;
		}

		town->setTemplePos(Position(positionX, positionY, positionZ));
	}
	return true;
}

// Parse waypoints information data
bool IOMap::parseWaypoints(BinaryNode & binaryNodeMapData, Map& map) const
{
	for(std::shared_ptr<BinaryNode> binaryNodeWaypoint = binaryNodeMapData.getChild();
	binaryNodeWaypoint != nullptr; binaryNodeWaypoint = binaryNodeWaypoint->advance())
	{
		if (binaryNodeWaypoint->getU8() != OTBM_WAYPOINT) {
			SPDLOG_ERROR("[IOMap::parseWaypoints] - Invalid waypoint node");
			continue;
		}

		// Sanity check, if the string is empty then we know where the problem is
		const std::string waypointName = binaryNodeWaypoint->getString();
		if (waypointName.empty()) {
			SPDLOG_ERROR("[IOMap::parseWaypoints] - Could not read waypoint name");
			continue;
		}

		uint16_t positionX = binaryNodeWaypoint->getU16();
		uint16_t positionY = binaryNodeWaypoint->getU16();
		uint8_t positionZ = binaryNodeWaypoint->getU8();
		// Sanity check, if there is an error in the get, we will know where the problem is
		if(positionX == 0 || positionY == 0 || positionZ == 0) {
			SPDLOG_ERROR("[IOMap::parseWaypoints] - Invalid waypoint position");
			continue;
		}

		map.waypoints[waypointName] = Position(positionX, positionY, positionZ);
	}
	return true;
}
