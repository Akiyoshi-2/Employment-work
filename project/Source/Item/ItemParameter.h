#pragma once
#include "DxLib.h"
#include "../../External/nlohmann/json.hpp"
#include <string>

enum ITEM_ID
{
	ITEM_HEAL,
	ITEM_SPEED_UP,
	ITEM_DAMAGE_UP,
	ITEM_INVINCIBLE,
	ITEM_MAX
};

enum ITEM_CREATE_TYPE
{
	ITEM_CREATE_MAP,
	ITEM_CREATE_DROP,
};