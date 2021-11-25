/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (C) 2018-2021 OpenTibiaBR <opentibiabr@outlook.com>
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

#include "otpch.h"

#include "items/functions/item_parse.hpp"

void ItemParse::parseType(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "type") {
		stringValue = asLowerCaseString(valueAttribute.as_string());
		auto itemMap = ItemTypesMap.find(stringValue);
		if (itemMap != ItemTypesMap.end()) {
			itemType.type = itemMap->second;
			if (itemType.type == ITEM_TYPE_CONTAINER) {
				itemType.group = ITEM_GROUP_CONTAINER;
			}
		} else {
			SPDLOG_WARN("[Items::parseItemNode] - Unknown type: {}",
                        valueAttribute.as_string());
		}
	}
}

void ItemParse::parseDescription(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "description") {
		itemType.description = valueAttribute.as_string();
	}
}

void ItemParse::parseRuneSpellName(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "runespellname") {
		itemType.runeSpellName = valueAttribute.as_string();
	}
}

void ItemParse::parseWeight(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "weight") {
		itemType.weight = pugi::cast<uint32_t>(valueAttribute.value());
	}
}

void ItemParse::parseShowCount(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "showcount") {
		itemType.showCount = valueAttribute.as_bool();
	}
}

void ItemParse::parseArmor(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "armor") {
		itemType.armor = pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parseDefense(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "defense") {
		itemType.defense = pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parseExtraDefense(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "extradef") {
		itemType.extraDefense = pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parseAttack(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "attack") {
		itemType.attack = pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parseRotateTo(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "rotateto") {
		itemType.rotateTo = pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parseWrapContainer(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "wrapcontainer") {
		itemType.wrapContainer = valueAttribute.as_bool();
	}
}

void ItemParse::parseImbuingSlot(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "imbuingslot") {
		itemType.imbuingSlots = pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parseWrapableTo(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "wrapableto") {
		itemType.wrapableTo = pugi::cast<int32_t>(valueAttribute.value());
		itemType.wrapable = true;
	}
}

void ItemParse::parseMoveable(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "moveable") {
		itemType.moveable = valueAttribute.as_bool();
	}
}

void ItemParse::parsePodium(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "podium") {
		itemType.isPodium = valueAttribute.as_bool();
	}
}

void ItemParse::parseBlockProjectTile(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "blockprojectile") {
		itemType.blockProjectile = valueAttribute.as_bool();
	}
}

void ItemParse::parsePickupable(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "pickupable") {
		itemType.allowPickupable = valueAttribute.as_bool();
	}
}

void ItemParse::parseFloorChange(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "floorchange") {
		stringValue = asLowerCaseString(valueAttribute.as_string());
		auto itemMap = TileStatesMap.find(stringValue);
		if (itemMap != TileStatesMap.end()) {
			itemType.floorChange = itemMap->second;
		} else {
			SPDLOG_WARN("[ItemParse::parseFloorChange] - Unknown floorChange {}",
                        valueAttribute.as_string());
		}
	}
}

void ItemParse::parseCorpseType(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "corpsetype") {
		stringValue = asLowerCaseString(valueAttribute.as_string());
		auto itemMap = RaceTypesMap.find(stringValue);
		if (itemMap != RaceTypesMap.end()) {
			itemType.corpseType = itemMap->second;
		} else {
			SPDLOG_WARN("[ItemParse::parseCorpseType] - Unknown corpseType {}",
                        valueAttribute.as_string());
		}
	}
}

void ItemParse::parseContainerSize(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "containersize") {
		itemType.maxItems = pugi::cast<uint16_t>(valueAttribute.value());
	}
}

void ItemParse::parseFluidSource(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "fluidsource") {
		stringValue = asLowerCaseString(valueAttribute.as_string());
		auto itemMap = FluidTypesMap.find(stringValue);
		if (itemMap != FluidTypesMap.end()) {
			itemType.fluidSource = itemMap->second;
		} else {
			SPDLOG_WARN("[Items::parseItemNode] - Unknown fluidSource {}",
                        valueAttribute.as_string());
		}
	}
}

void ItemParse::parseWriteables(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "readable") {
		itemType.canReadText = valueAttribute.as_bool();
	} else if (stringValue == "writeable") {
		itemType.canWriteText = valueAttribute.as_bool();
		itemType.canReadText = itemType.canWriteText;
	} else if (stringValue == "maxtextlen") {
		itemType.maxTextLen = pugi::cast<uint16_t>(valueAttribute.value());
	} else if (stringValue == "writeonceitemid") {
		itemType.writeOnceItemId = pugi::cast<uint16_t>(valueAttribute.value());
	}
}

void ItemParse::parseWeaponType(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "weapontype") {
		stringValue = asLowerCaseString(valueAttribute.as_string());
		auto itemMap = WeaponTypesMap.find(stringValue);
		if (itemMap != WeaponTypesMap.end()) {
			itemType.weaponType = itemMap->second;
		} else {
			SPDLOG_WARN("[Items::parseItemNode] - Unknown weaponType {}",
                        valueAttribute.as_string());
		}
	}
}

void ItemParse::parseSlotType(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "slottype") {
		stringValue = asLowerCaseString(valueAttribute.as_string());
	if (stringValue == "head") {
			itemType.slotPosition |= SLOTP_HEAD;
		} else if (stringValue == "body") {
			itemType.slotPosition |= SLOTP_ARMOR;
		} else if (stringValue == "legs") {
			itemType.slotPosition |= SLOTP_LEGS;
		} else if (stringValue == "feet") {
			itemType.slotPosition |= SLOTP_FEET;
		} else if (stringValue == "backpack") {
			itemType.slotPosition |= SLOTP_BACKPACK;
		} else if (stringValue == "two-handed") {
			itemType.slotPosition |= SLOTP_TWO_HAND;
		} else if (stringValue == "right-hand") {
			itemType.slotPosition &= ~SLOTP_LEFT;
		} else if (stringValue == "left-hand") {
			itemType.slotPosition &= ~SLOTP_RIGHT;
		} else if (stringValue == "necklace") {
			itemType.slotPosition |= SLOTP_NECKLACE;
		} else if (stringValue == "ring") {
			itemType.slotPosition |= SLOTP_RING;
		} else if (stringValue == "ammo") {
			itemType.slotPosition |= SLOTP_AMMO;
		} else if (stringValue == "hand") {
			itemType.slotPosition |= SLOTP_HAND;
		} else {
			SPDLOG_WARN("[itemParseSlotType - Items::parseItemNode] - Unknown slotType {}",
                        valueAttribute.as_string());
		}
	}
}

void ItemParse::parseAmmoType(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "ammotype") {
		itemType.ammoType = getAmmoType(asLowerCaseString(valueAttribute.as_string()));
		if (itemType.ammoType == AMMO_NONE) {
			SPDLOG_WARN("[Items::parseItemNode] - Unknown ammoType {}",
                        valueAttribute.as_string());
		}
	}
}

void ItemParse::parseShootType(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "shoottype") {
		ShootType_t shoot = getShootType(asLowerCaseString(valueAttribute.as_string()));
		if (shoot != CONST_ANI_NONE) {
			itemType.shootType = shoot;
		} else {
			SPDLOG_WARN("[Items::parseItemNode] - Unknown shootType {}",
                        valueAttribute.as_string());
		}
	}
}

void ItemParse::parseMagicEffect(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "effect") {
		MagicEffectClasses effect = getMagicEffect(asLowerCaseString(valueAttribute.as_string()));
		if (effect != CONST_ME_NONE) {
			itemType.magicEffect = effect;
		} else {
			SPDLOG_WARN("[Items::parseItemNode] - Unknown effect {}",
                        valueAttribute.as_string());
		}
	}
}

void ItemParse::parseLootType(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "loottype") {
		itemType.type = Item::items.getLootType(valueAttribute.as_string());
	}
}

void ItemParse::parseRange(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "range") {
		itemType.shootRange = pugi::cast<uint16_t>(valueAttribute.value());
	}
}

void ItemParse::parseDuration(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "duration") {
		itemType.decayTime = pugi::cast<uint32_t>(valueAttribute.value());
	} else if (stringValue == "stopduration") {
		itemType.stopTime = valueAttribute.as_bool();
	} else if (stringValue == "showduration") {
		itemType.showDuration = valueAttribute.as_bool();
	}
}

void ItemParse::parseTransform(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "transformequipto") {
		itemType.transformEquipTo = pugi::cast<uint16_t>(valueAttribute.value());
	} else if (stringValue == "transformdeequipto") {
		itemType.transformDeEquipTo = pugi::cast<uint16_t>(valueAttribute.value());
	} else if (stringValue == "transformto") {
		itemType.transformToFree = pugi::cast<uint16_t>(valueAttribute.value());
	} else if (stringValue == "destroyto") {
		itemType.destroyTo = pugi::cast<uint16_t>(valueAttribute.value());
	}
}

void ItemParse::parseCharges(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "charges") {
		itemType.charges = pugi::cast<uint32_t>(valueAttribute.value());
	} else if (stringValue == "showcharges") {
		itemType.showCharges = valueAttribute.as_bool();
	}
}

void ItemParse::parseShowAttributes(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "showattributes") {
		itemType.showAttributes = valueAttribute.as_bool();
	}
}

void ItemParse::parseHitChance(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "hitchance") {
		itemType.hitChance = std::min<int8_t>(100, std::max<int8_t>(-100, pugi::cast<int16_t>(valueAttribute.value())));
	} else if (stringValue == "maxhitchance") {
		itemType.maxHitChance = std::min<uint32_t>(100, pugi::cast<uint32_t>(valueAttribute.value()));
	}
}

void ItemParse::parseInvisible(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "invisible") {
		itemType.getAbilities().invisible = valueAttribute.as_bool();
	}
}

void ItemParse::parseSpeed(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "speed") {
		itemType.getAbilities().speed = pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parseHealthAndMana(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "healthgain") {
		Abilities & abilities = itemType.getAbilities();
		abilities.regeneration = true;
		abilities.healthGain = pugi::cast<uint32_t>(valueAttribute.value());
	} else if (stringValue == "healthticks") {
		Abilities & abilities = itemType.getAbilities();
		abilities.regeneration = true;
		abilities.healthTicks = pugi::cast<uint32_t>(valueAttribute.value());
	} else if (stringValue == "managain") {
		Abilities & abilities = itemType.getAbilities();
		abilities.regeneration = true;
		abilities.manaGain = pugi::cast<uint32_t>(valueAttribute.value());
	} else if (stringValue == "manaticks") {
		Abilities & abilities = itemType.getAbilities();
		abilities.regeneration = true;
		abilities.manaTicks = pugi::cast<uint32_t>(valueAttribute.value());
	} else if (stringValue == "manashield") {
		itemType.getAbilities().manaShield = valueAttribute.as_bool();
	}
}

void ItemParse::parseSkills(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "skillsword") {
		itemType.getAbilities().skills[SKILL_SWORD] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "skillaxe") {
		itemType.getAbilities().skills[SKILL_AXE] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "skillclub") {
		itemType.getAbilities().skills[SKILL_CLUB] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "skilldist") {
		itemType.getAbilities().skills[SKILL_DISTANCE] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "skillfish") {
		itemType.getAbilities().skills[SKILL_FISHING] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "skillshield") {
		itemType.getAbilities().skills[SKILL_SHIELD] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "skillfist") {
		itemType.getAbilities().skills[SKILL_FIST] = pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parseCriticalHit(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "criticalhitchance") {
		itemType.getAbilities().skills[SKILL_CRITICAL_HIT_CHANCE] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "criticalhitdamage") {
		itemType.getAbilities().skills[SKILL_CRITICAL_HIT_DAMAGE] = pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parseLifeAndManaLeech(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "lifeleechchance") {
		itemType.getAbilities().skills[SKILL_LIFE_LEECH_CHANCE] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "lifeleechamount") {
		itemType.getAbilities().skills[SKILL_LIFE_LEECH_AMOUNT] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "manaleechchance") {
		itemType.getAbilities().skills[SKILL_MANA_LEECH_CHANCE] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "manaleechamount") {
		itemType.getAbilities().skills[SKILL_MANA_LEECH_AMOUNT] = pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parseMaxHitAndManaPoints(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "maxhitpoints") {
		itemType.getAbilities().stats[STAT_MAXHITPOINTS] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "maxhitpointspercent") {
		itemType.getAbilities().statsPercent[STAT_MAXHITPOINTS] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "maxmanapoints") {
		itemType.getAbilities().stats[STAT_MAXMANAPOINTS] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "maxmanapointspercent") {
		itemType.getAbilities().statsPercent[STAT_MAXMANAPOINTS] = pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parseMagicPoints(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "magiclevelpoints") {
		itemType.getAbilities().stats[STAT_MAGICPOINTS] = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "magiclevelpointspercent") {
		itemType.getAbilities().statsPercent[STAT_MAGICPOINTS] = pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parseFieldAbsorbPercent(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "fieldabsorbpercentenergy") {
		itemType.getAbilities().fieldAbsorbPercent[combatTypeToIndex(COMBAT_ENERGYDAMAGE)] += pugi::cast<int16_t>(valueAttribute.value());
	} else if (stringValue == "fieldabsorbpercentfire") {
		itemType.getAbilities().fieldAbsorbPercent[combatTypeToIndex(COMBAT_FIREDAMAGE)] += pugi::cast<int16_t>(valueAttribute.value());
	} else if (stringValue == "fieldabsorbpercentpoison") {
		itemType.getAbilities().fieldAbsorbPercent[combatTypeToIndex(COMBAT_EARTHDAMAGE)] += pugi::cast<int16_t>(valueAttribute.value());
	}
}

void ItemParse::parseAbsorbPercent(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "absorbpercentall") {
		int16_t value = pugi::cast<int16_t>(valueAttribute.value());
		Abilities & abilities = itemType.getAbilities();
		for (auto & i: abilities.absorbPercent) {
			i += value;
		}
	} else if (stringValue == "absorbpercentelements") {
		int16_t value = pugi::cast<int16_t>(valueAttribute.value());
		Abilities & abilities = itemType.getAbilities();
		abilities.absorbPercent[combatTypeToIndex(COMBAT_ENERGYDAMAGE)] += value;
		abilities.absorbPercent[combatTypeToIndex(COMBAT_FIREDAMAGE)] += value;
		abilities.absorbPercent[combatTypeToIndex(COMBAT_EARTHDAMAGE)] += value;
		abilities.absorbPercent[combatTypeToIndex(COMBAT_ICEDAMAGE)] += value;
	} else if (stringValue == "absorbpercentmagic") {
		int16_t value = pugi::cast<int16_t>(valueAttribute.value());
		Abilities & abilities = itemType.getAbilities();
		abilities.absorbPercent[combatTypeToIndex(COMBAT_ENERGYDAMAGE)] += value;
		abilities.absorbPercent[combatTypeToIndex(COMBAT_FIREDAMAGE)] += value;
		abilities.absorbPercent[combatTypeToIndex(COMBAT_EARTHDAMAGE)] += value;
		abilities.absorbPercent[combatTypeToIndex(COMBAT_ICEDAMAGE)] += value;
		abilities.absorbPercent[combatTypeToIndex(COMBAT_HOLYDAMAGE)] += value;
		abilities.absorbPercent[combatTypeToIndex(COMBAT_DEATHDAMAGE)] += value;
	} else if (stringValue == "absorbpercentenergy") {
		itemType.getAbilities().absorbPercent[combatTypeToIndex(COMBAT_ENERGYDAMAGE)] += pugi::cast<int16_t>(valueAttribute.value());
	} else if (stringValue == "absorbpercentfire") {
		itemType.getAbilities().absorbPercent[combatTypeToIndex(COMBAT_FIREDAMAGE)] += pugi::cast<int16_t>(valueAttribute.value());
	} else if (stringValue == "absorbpercentpoison") {
		itemType.getAbilities().absorbPercent[combatTypeToIndex(COMBAT_EARTHDAMAGE)] += pugi::cast<int16_t>(valueAttribute.value());
	} else if (stringValue == "absorbpercentice") {
		itemType.getAbilities().absorbPercent[combatTypeToIndex(COMBAT_ICEDAMAGE)] += pugi::cast<int16_t>(valueAttribute.value());
	} else if (stringValue == "absorbpercentholy") {
		itemType.getAbilities().absorbPercent[combatTypeToIndex(COMBAT_HOLYDAMAGE)] += pugi::cast<int16_t>(valueAttribute.value());
	} else if (stringValue == "absorbpercentdeath") {
		itemType.getAbilities().absorbPercent[combatTypeToIndex(COMBAT_DEATHDAMAGE)] += pugi::cast<int16_t>(valueAttribute.value());
	} else if (stringValue == "absorbpercentlifedrain") {
		itemType.getAbilities().absorbPercent[combatTypeToIndex(COMBAT_LIFEDRAIN)] += pugi::cast<int16_t>(valueAttribute.value());
	} else if (stringValue == "absorbpercentmanadrain") {
		itemType.getAbilities().absorbPercent[combatTypeToIndex(COMBAT_MANADRAIN)] += pugi::cast<int16_t>(valueAttribute.value());
	} else if (stringValue == "absorbpercentdrown") {
		itemType.getAbilities().absorbPercent[combatTypeToIndex(COMBAT_DROWNDAMAGE)] += pugi::cast<int16_t>(valueAttribute.value());
	} else if (stringValue == "absorbpercentphysical") {
		itemType.getAbilities().absorbPercent[combatTypeToIndex(COMBAT_PHYSICALDAMAGE)] += pugi::cast<int16_t>(valueAttribute.value());
	} else if (stringValue == "absorbpercenthealing") {
		itemType.getAbilities().absorbPercent[combatTypeToIndex(COMBAT_HEALING)] += pugi::cast<int16_t>(valueAttribute.value());
	}
}

void ItemParse::parseSupressDrunk(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (valueAttribute.as_bool()) {
		if (stringValue == "suppressdrunk") {
			itemType.getAbilities().conditionSuppressions |= CONDITION_DRUNK;
		} else if (stringValue == "suppressenergy") {
			itemType.getAbilities().conditionSuppressions |= CONDITION_ENERGY;
		} else if (stringValue == "suppressfire") {
			itemType.getAbilities().conditionSuppressions |= CONDITION_FIRE;
		} else if (stringValue == "suppresspoison") {
			itemType.getAbilities().conditionSuppressions |= CONDITION_POISON;
		} else if (stringValue == "suppressdrown") {
			itemType.getAbilities().conditionSuppressions |= CONDITION_DROWN;
		} else if (stringValue == "suppressphysical") {
			itemType.getAbilities().conditionSuppressions |= CONDITION_BLEEDING;
		} else if (stringValue == "suppressfreeze") {
			itemType.getAbilities().conditionSuppressions |= CONDITION_FREEZING;
		} else if (stringValue == "suppressdazzle") {
			itemType.getAbilities().conditionSuppressions |= CONDITION_DAZZLED;
		} else if (stringValue == "suppresscurse") {
			itemType.getAbilities().conditionSuppressions |= CONDITION_CURSED;
		}
	}
}

ConditionDamage* ItemParse::parseFieldConditions(ConditionDamage *conditionDamage, std::string lowerStringValue, pugi::xml_attribute valueAttribute) {
	lowerStringValue = asLowerCaseString(valueAttribute.as_string());
	if (lowerStringValue == "fire") {
		if (!conditionDamage) {
			return conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_FIRE);
		}
		delete conditionDamage;
	} else if (lowerStringValue == "energy") {
		if (!conditionDamage) {
			return conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_ENERGY);
		}
		delete conditionDamage;
	} else if (lowerStringValue == "poison") {
		if (!conditionDamage) {
			return conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_POISON);
		}
		delete conditionDamage;
	} else if (lowerStringValue == "drown") {
		if (!conditionDamage) {
			return conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_DROWN);
		}
		delete conditionDamage;
	} else if (lowerStringValue == "physical") {
		if (!conditionDamage) {
			return conditionDamage = new ConditionDamage(CONDITIONID_COMBAT, CONDITION_BLEEDING);
		}
		delete conditionDamage;
	} else {
		SPDLOG_WARN("[Items::parseItemNode] Unknown field value {}",
                    valueAttribute.as_string());
	}
}

CombatType_t ItemParse::parseFieldCombatType(CombatType_t combatType, std::string lowerStringValue, pugi::xml_attribute valueAttribute) {
	lowerStringValue = asLowerCaseString(valueAttribute.as_string());
	if (lowerStringValue == "fire") {
		return combatType = COMBAT_FIREDAMAGE;
	} else if (lowerStringValue == "energy") {
		return combatType = COMBAT_ENERGYDAMAGE;
	} else if (lowerStringValue == "poison") {
		return combatType = COMBAT_EARTHDAMAGE;
	} else if (lowerStringValue == "drown") {
		return combatType = COMBAT_DROWNDAMAGE;
	} else if (lowerStringValue == "physical") {
		return combatType = COMBAT_PHYSICALDAMAGE;
	} else {
		SPDLOG_WARN("[Items::parseItemNode] Unknown field value {}",
                    valueAttribute.as_string());
	}
}

void ItemParse::parseFieldCombatDamage(ConditionDamage *conditionDamage, std::string stringValue, pugi::xml_node attributeNode) {
	uint32_t combatTicks = 0;
	int32_t combatDamage = 0;
	int32_t combatStart = 0;
	int32_t combatCount = 1;

	for (auto subAttributeNode: attributeNode.children()) {
		pugi::xml_attribute subKeyAttribute = subAttributeNode.attribute("key");
		if (!subKeyAttribute) {
			continue;
		}

		pugi::xml_attribute subValueAttribute = subAttributeNode.attribute("value");
		if (!subValueAttribute) {
			continue;
		}

		stringValue = asLowerCaseString(subKeyAttribute.as_string());
		if (stringValue == "ticks") {
			combatTicks = pugi::cast<uint32_t>(subValueAttribute.value());
		} else if (stringValue == "count") {
			combatCount = std::max<int32_t>(1, pugi::cast<int32_t>(subValueAttribute.value()));
		} else if (stringValue == "start") {
			combatStart = std::max<int32_t>(0, pugi::cast<int32_t>(subValueAttribute.value()));
		} else if (stringValue == "damage") {
			combatDamage = -pugi::cast<int32_t>(subValueAttribute.value());
			if (combatStart > 0) {
				std::list<int32_t>damageList;
				ConditionDamage::generateDamageList(combatDamage, combatStart, damageList);
				for (int32_t damageValue: damageList) {
					conditionDamage->addDamage(1, combatTicks, -damageValue);
				}

				combatStart = 0;
			} else {
				conditionDamage->addDamage(combatCount, combatTicks, combatDamage);
			}
		}
	}
}

void ItemParse::parseField(const std::string& tmpStrValue, pugi::xml_node attributeNode, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "field") {
		CombatType_t combatType = COMBAT_NONE;
		ConditionDamage *conditionDamage = nullptr;

		// Parse fields conditions and combat type (fire/energy/poison/drown/physical)
		conditionDamage = parseFieldConditions(conditionDamage, stringValue, valueAttribute);
		combatType = parseFieldCombatType(combatType, stringValue, valueAttribute);
		if (combatType != COMBAT_NONE) {
			itemType.combatType = combatType;
			itemType.conditionDamage.reset(conditionDamage);
			
			parseFieldCombatDamage(conditionDamage, stringValue, attributeNode);

			conditionDamage->setParam(CONDITION_PARAM_FIELD, 1);

			if (conditionDamage->getTotalDamage() > 0) {
				conditionDamage->setParam(CONDITION_PARAM_FORCEUPDATE, 1);
			}
		}
	}
}

void ItemParse::parseReplaceable(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "replaceable") {
		itemType.replaceable = valueAttribute.as_bool();
	}
}

void ItemParse::parseLevelDoor(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "leveldoor") {
		itemType.levelDoor = pugi::cast<uint32_t>(valueAttribute.value());
	}
}

void ItemParse::parseBeds(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "partnerdirection") {
		itemType.bedPartnerDir = getDirection(valueAttribute.as_string());
	}
		
	uint16_t value = pugi::cast<uint16_t>(valueAttribute.value());
	ItemType & other = Item::items.getItemType(value);
	if (stringValue == "maletransformto") {
		itemType.transformToOnUse[PLAYERSEX_MALE] = value;
		if (other.transformToFree == 0) {
			other.transformToFree = itemType.id;
		}

		if (itemType.transformToOnUse[PLAYERSEX_FEMALE] == 0) {
			itemType.transformToOnUse[PLAYERSEX_FEMALE] = value;
		}
	} else if (stringValue == "femaletransformto") {
		itemType.transformToOnUse[PLAYERSEX_FEMALE] = value;

		if (other.transformToFree == 0) {
			other.transformToFree = itemType.id;
		}

		if (itemType.transformToOnUse[PLAYERSEX_MALE] == 0) {
			itemType.transformToOnUse[PLAYERSEX_MALE] = value;
		}
	}
}

void ItemParse::parseElement(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "elementice") {
		Abilities & abilities = itemType.getAbilities();
		abilities.elementDamage = pugi::cast<uint16_t>(valueAttribute.value());
		abilities.elementType = COMBAT_ICEDAMAGE;
	} else if (stringValue == "elementearth") {
		Abilities & abilities = itemType.getAbilities();
		abilities.elementDamage = pugi::cast<uint16_t>(valueAttribute.value());
		abilities.elementType = COMBAT_EARTHDAMAGE;
	} else if (stringValue == "elementfire") {
		Abilities & abilities = itemType.getAbilities();
		abilities.elementDamage = pugi::cast<uint16_t>(valueAttribute.value());
		abilities.elementType = COMBAT_FIREDAMAGE;
	} else if (stringValue == "elementenergy") {
		Abilities & abilities = itemType.getAbilities();
		abilities.elementDamage = pugi::cast<uint16_t>(valueAttribute.value());
		abilities.elementType = COMBAT_ENERGYDAMAGE;
	} else if (stringValue == "elementdeath") {
		Abilities & abilities = itemType.getAbilities();
		abilities.elementDamage = pugi::cast<uint16_t>(valueAttribute.value());
		abilities.elementType = COMBAT_DEATHDAMAGE;
	} else if (stringValue == "elementholy") {
		Abilities & abilities = itemType.getAbilities();
		abilities.elementDamage = pugi::cast<uint16_t>(valueAttribute.value());
		abilities.elementType = COMBAT_HOLYDAMAGE;
	}
}

void ItemParse::parseWalk(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "walkstack") {
		itemType.walkStack = valueAttribute.as_bool();
	} else if (stringValue == "block_solid") {
		itemType.blockSolid = valueAttribute.as_bool();
	}
}

void ItemParse::parseAllowDistanceRead(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	if (stringValue == "allowdistread") {
		itemType.allowDistRead = booleanString(valueAttribute.as_string());
	}
}

void ItemParse::parseMagicLevelPoint(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	Abilities & abilities = itemType.getAbilities();
	if (stringValue == "deathmagiclevelpoints") {
		abilities.specializedMagicLevel[combatTypeToIndex(COMBAT_DEATHDAMAGE)] += pugi::cast<int32_t>(valueAttribute.value());
		abilities.elementType = COMBAT_DEATHDAMAGE;
	} else if (stringValue == "energymagiclevelpoints") {
		abilities.specializedMagicLevel[combatTypeToIndex(COMBAT_ENERGYDAMAGE)] += pugi::cast<int32_t>(valueAttribute.value());
		abilities.elementType = COMBAT_ENERGYDAMAGE;
	} else if (stringValue == "earthmagiclevelpoints") {
		abilities.specializedMagicLevel[combatTypeToIndex(COMBAT_EARTHDAMAGE)] += pugi::cast<int32_t>(valueAttribute.value());
		abilities.elementType = COMBAT_EARTHDAMAGE;
	} else if (stringValue == "firemagiclevelpoints") {
		abilities.specializedMagicLevel[combatTypeToIndex(COMBAT_FIREDAMAGE)] += pugi::cast<int32_t>(valueAttribute.value());
		abilities.elementType = COMBAT_FIREDAMAGE;
	} else if (stringValue == "healingmagiclevelpoints") {
		abilities.specializedMagicLevel[combatTypeToIndex(COMBAT_HEALING)] += pugi::cast<int32_t>(valueAttribute.value());
		abilities.elementType = COMBAT_HEALING;
	} else if (stringValue == "holymagiclevelpoints") {
		abilities.specializedMagicLevel[combatTypeToIndex(COMBAT_HOLYDAMAGE)] += pugi::cast<int32_t>(valueAttribute.value());
		abilities.elementType = COMBAT_HOLYDAMAGE;
	} else if (stringValue == "icemagiclevelpoints") {
		abilities.specializedMagicLevel[combatTypeToIndex(COMBAT_ICEDAMAGE)] += pugi::cast<int32_t>(valueAttribute.value());
		abilities.elementType = COMBAT_ICEDAMAGE;
	} else if (stringValue == "physicalmagiclevelpoints") {
		abilities.specializedMagicLevel[combatTypeToIndex(COMBAT_PHYSICALDAMAGE)] += pugi::cast<int32_t>(valueAttribute.value());
		abilities.elementType = COMBAT_PHYSICALDAMAGE;
	}
}

void ItemParse::parseMagicShieldCapacity(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	Abilities & abilities = itemType.getAbilities();
	if (stringValue == "magicshieldcapacitypercent") {
		abilities.magicShieldCapacityPercent += pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "magicshieldcapacityflat") {
		abilities.magicShieldCapacityFlat += pugi::cast<int32_t>(valueAttribute.value());
	}
}

void ItemParse::parsePerfecShot(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	Abilities & abilities = itemType.getAbilities();
	if (stringValue == "perfectshotdamage") {
		abilities.perfectShotDamage = pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "perfectshotrange") {
		abilities.perfectShotRange = pugi::cast<int16_t>(valueAttribute.value());
	}
}

void ItemParse::parseCleavePercent(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	Abilities & abilities = itemType.getAbilities();
	if (stringValue == "cleavepercent") {
		abilities.cleavePercent += pugi::cast<inint32_tt16_t>(valueAttribute.value());
	}
}

void ItemParse::parseReflectDamage(const std::string& tmpStrValue, pugi::xml_attribute valueAttribute, ItemType& itemType) {
	std::string stringValue = tmpStrValue;
	Abilities & abilities = itemType.getAbilities();
	if (stringValue == "reflectdamage") {
		abilities.reflectFlat[combatTypeToIndex(COMBAT_PHYSICALDAMAGE)] += pugi::cast<int32_t>(valueAttribute.value());
	} else if (stringValue == "reflectpercentall") {
		int32_t value = pugi::cast<int32_t>(valueAttribute.value());
		for (auto& i : abilities.reflectPercent) {
			i += value;
		}
	}
}
