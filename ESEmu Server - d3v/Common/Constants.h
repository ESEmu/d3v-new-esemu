#pragma once
#include <utility>

typedef std::pair<int, int> ii;

namespace Constants {

	enum useType : unsigned short;				// ??? lol
	enum useCondition : unsigned short;			// item use condition: describes what character can use this item
	enum unitType : unsigned short;				// unit type: a unique identifier for each character
	enum unitClass : unsigned short;			// unit class: a unique identifier for each class of each character
	enum itemType : unsigned short;				// item type: describes which category this item falls under
	enum itemGrade : unsigned short;			// item grade: describes the grade of the item (eg. rare, unique)
	enum equipPos : unsigned short;				// equip position: describes where the item is equipped
	enum skillType : unsigned short;			// skill type: indicates the skill type (eg. special active)

	extern const std::pair<int, int> expTable[81];			// ExpTable: (Required Exp, Total Exp)

	enum useType : unsigned short {
		UT_NONE = 0,
		UT_SKIN = 1,
		UT_ATTACH_ANIM = 2,
		UT_ATTACH_NORMAL = 3
	};

	enum useCondition : unsigned short {
		UG_NONE = 0,
		UG_ANYONE = 1,
		UG_ONE_UNIT = 2,
		UG_ONE_CLASS = 3
	};

	enum unitType : unsigned short {
		UN_NONE = 0,
		UN_ELSWORD = 1,
		UN_AISHA = 2,
		UN_RENA = 3,
		UN_RAVEN = 4,
		UN_EVE = 5,
		UN_CHUNG = 6,
		UN_ARA = 7,
		UN_ELESIS = 8,
		UN_END = 9
	};

	enum unitClass : unsigned short {
		UC_NONE = 0,

		UC_ELSWORD_SWORDMAN = 1,
		UC_ELSWORD_KNIGHT = 10,
		UC_ELSWORD_MAGIC_KNIGHT = 11,
		UC_ELSWORD_SHEATH_KNIGHT = 22,
		UC_ELSWORD_SHIELD_KNIGHT = 32,
		UC_ELSWORD_LORD_KNIGHT = 100,
		UC_ELSWORD_RUNE_SLAYER = 101,
		UC_ELSWORD_INFINITY_SWORD = 112,

		UC_AISHA_VIOLET_MAGE = 2,
		UC_AISHA_HIGH_MAGICIAN = 14,
		UC_AISHA_DARK_MAGICIAN = 15,
		UC_AISHA_SWORD_MAGICIAN = 33,
		UC_AISHA_ELEMENTAL_MASTER = 104,
		UC_AISHA_VOID_PRINCESS = 105,
		UC_AISHA_DIMENSION_WITCH = 113,

		UC_RENA_ELVEN_RANGER = 3,
		UC_RENA_COMBAT_RANGER = 12,
		UC_RENA_SNIPING_RANGER = 13,
		UC_RENA_TRAPPING_RANGER = 24,
		UC_RENA_STRING_RANGER = 34,
		UC_RENA_WIND_SNEAKER = 102,
		UC_RENA_GRAND_ARCHER = 103,
		UC_RENA_NIGHT_WATCHER = 114,

		UC_RAVEN_FIGHTER = 4,
		UC_RAVEN_SOUL_TAKER = 16,
		UC_RAVEN_OVER_TAKER = 17,
		UC_RAVEN_WEAPON_TAKER = 25,
		UC_RAVEN_GLOBAL_1 = 35,
		UC_RAVEN_BLADE_MASTER = 106,
		UC_RAVEN_RECKLESS_FIST = 107,
		UC_RAVEN_VETERAN_COMMANDER = 115,

		UC_EVE_NASOD = 5,
		UC_EVE_EXOTIC_GEAR = 18,
		UC_EVE_ARCHITECTURE = 19,
		UC_EVE_ELECTRA = 26,
		UC_EVE_GLOBAL_1 = 36,
		UC_EVE_CODE_NEMESIS = 108,
		UC_EVE_CODE_EMPRESS = 109,
		UC_EVE_BATTLE_SERAPH = 116,

		UC_CHUNG_IRON_CANNON = 6,
		UC_CHUNG_FURY_GUARDIAN = 20,
		UC_CHUNG_SHOOTING_GUARDIAN = 21,
		UC_CHUNG_SHELLING_GUARDIAN = 27,
		UC_CHUNG_PRINCESS_GUARDIAN = 37,
		UC_CHUNG_IRON_PALADIN = 110,
		UC_CHUNG_DEADLY_CHASER = 111,
		UC_CHUNG_TACTICAL_TROOPER = 117,

		UC_ARA_MARTIAL_ARTIST = 7,
		UC_ARA_LITTLE_HSIEN = 28,
		UC_ARA_LITTLE_DEVIL = 31,
		UC_ARA_GLOBAL_1 = 38,
		UC_ARA_SAKRA_DEVANAM = 118,
		UC_ARA_YAMA_RAJA = 119,

		UC_ELESIS_KNIGHT = 8,
		UC_ELESIS_SABER_KNIGHT = 29,
		UC_ELESIS_PYRO_KNIGHT = 30,
		UC_ELESIS_GRAND_MASTER = 120,
		UC_ELESIS_BLAZING_HEART = 121

	};

	enum itemType : unsigned short {
		IT_NONE = 0,
		IT_WEAPON = 1,
		IT_DEFENCE = 2,
		IT_ACCESSORY = 3,
		IT_SKILL = 4,
		IT_QUICK_SLOT = 5,
		IT_MATERIAL = 6,
		IT_SPECIAL = 7,
		IT_QUEST = 8,
		IT_OUTLAY = 9,
		IT_ETC = 10,
		IT_SKILL_MEMO = 11,
		IT_PET = 12,
		IT_RIDING = 13,
		IT_END = 14
	};

	enum itemGrade : unsigned short {
		IG_NONE = 0,
		IG_UNIQUE = 1,
		IG_ELITE = 2,
		IG_RARE = 3,
		IG_NORMAL = 4,
		IG_LOW = 5
	};

	enum equipPos : unsigned short {
		EP_NONE = 0,
		EP_QUICK_SLOT = 1,
		EP_WEAPON_HAND = 2,
		EP_WEAPON_TEMP1 = 3,
		EP_WEAPON_TEMP2 = 4,
		EP_WEAPON_TEMP3 = 5,
		EP_DEFENCE_HAIR = 6,
		EP_DEFENCE_FACE = 7,
		EP_DEFENCE_BODY = 8,
		EP_DEFENCE_LEG = 9,
		EP_DEFENCE_HAND = 10,
		EP_DEFENCE_FOOT = 11,
		EP_DEFENCE_TEMP1 = 12,
		EP_DEFENCE_TEMP2 = 13,
		EP_DEFENCE_TEMP3 = 14,
		EP_AC_TITLE = 15,
		EP_AC_HAIR = 16,
		EP_AC_FACE1 = 17,
		EP_AC_FACE2 = 18,
		EP_AC_FACE3 = 19,
		EP_AC_BODY = 20,
		EP_AC_LEG = 21,
		EP_AC_ARM = 22,
		EP_AC_RING = 23,
		EP_AC_NECKLESS = 24,
		EP_AC_WEAPON = 25,
		EP_AC_TEMP2 = 26,
		EP_AC_TEMP3 = 27,
		EP_AC_TEMP4 = 28,
		EP_AC_TEMP5 = 29,
		EP_SKILL_1 = 30,
		EP_SKILL_2 = 31,
		EP_SKILL_3 = 32,
		EP_SKILL_TEMP1 = 33,
		EP_SKILL_TEMP2 = 34,
		EP_SKILL_TEMP3 = 35,
		EP_RAVEN_LEFT_ARM = 36,
		EP_WEAPON_SECOND = 37,
		EP_ONEPIECE_FASHION = 38,
		EP_END = 39
	};

	enum skillType : unsigned short {
		ST_NONE = 0,
		ST_PASSIVE_PHYSIC_ATTACK = 1,
		ST_PASSIVE_MAGIC_ATTACK = 2,
		ST_PASSIVE_MAGIC_DEFENCE = 3,
		ST_PASSIVE_PHYSIC_DEFENCE = 4,
		ST_BUFF = 5,
		ST_ACTIVE = 6,
		ST_SPECIAL_ACTIVE = 7,
		ST_PASSIVE = 8,
		ST_GUILD_PASSIVE_PHYSIC_ATTACK_MAGIC_DEFENCE = 9,
		ST_GUILD_PASSIVE_MAGIC_ATTCK_PHYSIC_DEFENCE = 10,
		ST_GUILD_PASSIVE = 11,
		ST_RELATIONSHIP_SKILL = 12,
		ST_HYPER_ACTIVE_SKILL = 13
	};

}