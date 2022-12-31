/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2022 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.org/
*/

#include "pch.hpp"

#include "creatures/players/grouping/familiars.h"
#include "config/configmanager.h"
#include "utils/tools.h"

bool Familiars::loadFromXml() {
	pugi::xml_document doc;
	auto folder = g_configManager().getString(CORE_DIRECTORY) + "/XML/familiars.xml";
	pugi::xml_parse_result result = doc.load_file(folder.c_str());
	if (!result) {
		SPDLOG_ERROR("Failed to load Familiars");
		printXMLError(__FUNCTION__, folder, result);
		return false;
	}

	for (auto familiarsNode : doc.child("familiars").children()) {
		pugi::xml_attribute attr;
		if ((attr = familiarsNode.attribute("enabled")) && !attr.as_bool()) {
			continue;
		}

		if (!(attr = familiarsNode.attribute("vocation"))) {
			SPDLOG_WARN("[Familiars::loadFromXml] - Missing familiar vocation.");
			continue;
		}

		auto vocationId = static_cast<uint16_t>(attr.as_uint());
		if (vocationId > VOCATION_LAST) {
			SPDLOG_WARN("[Familiars::loadFromXml] - Invalid familiar vocation {}", vocationId);
			continue;
		}

		pugi::xml_attribute lookTypeAttribute = familiarsNode.attribute("lookType");
		auto lookType = static_cast<uint16_t>(lookTypeAttribute.as_uint());
		const std::string familiarName = familiarsNode.attribute("name").as_string();
		if (!lookTypeAttribute.empty()) {
			const std::string lookTypeString = lookTypeAttribute.as_string();
			if (lookTypeString.empty() || lookType == 0) {
				SPDLOG_WARN("[Familiars::loadFromXml] - Empty looktype on outfit with name {}", familiarName);
				continue;
			}

			if (!isNumber(lookTypeString)) {
				SPDLOG_WARN("[Familiars::loadFromXml] - Invalid looktype {} with name {}", lookTypeString, familiarName);
				continue;
			}

			if (pugi::xml_attribute nameAttribute = familiarsNode.attribute("name");
			!nameAttribute || familiarName.empty())
			{
				SPDLOG_WARN("[Familiars::loadFromXml] - Missing or empty name on outfit with looktype {}", lookTypeString);
				continue;
			}
			familiars[vocationId].emplace_back(
				familiarName,
				lookType,
				familiarsNode.attribute("premium").as_bool(),
				familiarsNode.attribute("unlocked").as_bool(true),
				familiarsNode.attribute("type").as_string()
			);
		} else {
			SPDLOG_WARN("[Familiars::loadFromXml] - "
						"Missing looktype id for outfit name: {}", familiarName);
		}
	}
	for (uint16_t vocationId = VOCATION_NONE; vocationId <= VOCATION_LAST; ++vocationId) {
		familiars[vocationId].shrink_to_fit();
	}
	return true;
}

const Familiar* Familiars::getFamiliarByLookType(uint16_t vocationId, uint16_t lookType) const {
	for (const Familiar& familiar : familiars[vocationId]) {
		if (familiar.lookType == lookType) {
			return &familiar;
		}
	}
	return nullptr;
}
