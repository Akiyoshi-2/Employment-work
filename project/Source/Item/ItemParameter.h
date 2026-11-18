#pragma once
#include "DxLib.h"
#include "../../External/nlohmann/json.hpp"
#include <string>

enum ITEM_ID
{
	// 配置型
	ITEM_HEAL,
	ITEM_SPEED_UP,
	ITEM_DAMAGE_UP,
	ITEM_INVINCIBLE,

	// ドロップ型
	ITEM_DROP_HEAL,
	ITEM_DROP_GEAR,

	ITEM_MAX
};

enum ITEM_CREATE_TYPE
{
	ITEM_CREATE_MAP,
	ITEM_CREATE_DROP,
};

enum CURRENCY_ID
{
	CURRENCY_GEAR,		// 機械惑星の通貨
	CURRENCY_MAX
};