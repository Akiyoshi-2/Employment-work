#pragma once
#include "DxLib.h"
#include "../../External/nlohmann/json.hpp"
#include <string>

// 敵からドロップするアイテム
enum DROP_ITEM
{
	DROP_ITEM_00,
	DROP_ITEM_01,
	DROP_ITEM_02,
};

// マップ内に生成されるアイテム
enum SPAWN_ITEM
{
	SPAWN_ITEM_00,	// 回復アイテム
	SPAWN_ITEM_01,	// 攻撃力アップアイテム
	SPAWN_ITEM_02,	// 無敵化アイテム
};