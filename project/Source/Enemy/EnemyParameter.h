#pragma once
#include "DxLib.h"
#include "../../External/nlohmann/json.hpp"
#include <string>

//機械惑星の敵
enum MACHINE_ENEMY
{
	M_ENEMY_00,
	M_ENEMY_01,
	M_ENEMY_02,
	MACHINE_ENEMY_MAX,
};

// ジャングル惑星の敵
enum JUNGLE_ENEMY
{
	J_ENEMY_00,
	J_ENEMY_01,
	J_ENEMY_02,
	JUNGLE_ENEMY_MAX,
};

// 溶岩惑星の敵
enum LAVA_ENEMY
{
	L_ENEMY_00,
	L_ENEMY_01,
	L_ENEMY_02,
	LAVA_ENEMY_MAX,
};

// 汚染惑星の敵
enum POLLUTION_ENEMY
{
	P_ENEMY_00,
	PN_ENEMY_01,
	P_ENEMY_02,
	POLLUTION_ENEMY_MAX,
};

// ボスエネミー
enum BOSS_ENEMY_TYPE
{
	BOSS_MACHINE,
	BOSS_JUNGLE,
	BOSS_LAVA,
	BOSS_POLLUTION,
};