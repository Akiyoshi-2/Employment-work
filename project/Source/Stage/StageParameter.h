#pragma once
#include "DxLib.h"
#include "../../External/nlohmann/json.hpp"
#include <string>

struct GameObject
{
	int id = -1;
	VECTOR pos = {};
	VECTOR rot = {};
	VECTOR scale = {};
	std::string name = "";
};

enum LcateObjectID
{
	// Block
	BLOCK_00,
	BLOCK_01,
	BLOCK_02,
	BLOCK_03,
	BLOCK_04,
	BLOCK_05,
	BLOCK_06,
	BLOCK_07,
	BLOCK_08,
	BLOCK_09,
	BLOCK_10,
	BLOCK_11,
	BLOCK_12,
	BLOCK_13,
	BLOCK_14,
	BLOCK_15,
	// Trap
	TRAP_00,
};

inline void jsonConvXYZ(const nlohmann::json& j, VECTOR& v)
{
	v.x = j.at("x").get<float>();
	v.y = j.at("y").get<float>();
	v.z = j.at("z").get<float>();
}

inline void from_json(const nlohmann::json& j, GameObject& obj)
{
	obj.id = j.value("m_StageID", 0);
	obj.name = j.value("name", "");
	jsonConvXYZ(j.at("position"), obj.pos);
	jsonConvXYZ(j.at("rotation"), obj.rot);

	obj.rot.x = obj.rot.x * DX_PI_F / 180.0f;
	obj.rot.y = obj.rot.y * DX_PI_F / 180.0f;
	obj.rot.z = obj.rot.z * DX_PI_F / 180.0f;

	jsonConvXYZ(j.at("scale"), obj.scale);
}