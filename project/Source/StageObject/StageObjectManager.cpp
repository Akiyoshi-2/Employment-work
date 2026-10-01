#include "StageObjectManager.h"
#include "Block/Block.h"
#include "Block/BlockParameter.h"
#include "../Library/json/json.hpp"

using json = nlohmann::json;

StageObjectManager* StageObjectManager::m_Instance = nullptr;

StageObjectManager::StageObjectManager()
{
	m_StageObjects = {};
	m_OriginalBlock = nullptr;
}

StageObjectManager::~StageObjectManager()
{
	Fin();
}

void StageObjectManager::Init()
{
	m_OriginalBlock = new Block[BLOCK_MAX];

	m_StageType = StageType::MACHINE_PLANET;
}

void StageObjectManager::Load()
{
	if (m_StageType == StageType::MACHINE_PLANET)
	{
		m_OriginalBlock[BLOCK_00].Load("Data/Blender/Block_00/test_Block.x");
		m_OriginalBlock[BLOCK_01].Load("Data/Blender/Block_01/test_wall.x");
		m_OriginalBlock[BLOCK_02].Load("Data/Blender/Block_02/test_wall_Start(inside).x");
		m_OriginalBlock[BLOCK_03].Load("Data/Blender/Block_03/test_wall_Start(outside).x");
		m_OriginalBlock[BLOCK_04].Load("Data/Blender/Block_04/test_floor_start(inside).x");
		m_OriginalBlock[BLOCK_05].Load("Data/Blender/Block_05/test_floor_start(outside).x");
		m_OriginalBlock[BLOCK_06].Load("Data/Blender/Block_06/test_floor&seiling.x");
		m_OriginalBlock[BLOCK_07].Load("Data/Blender/Block_07/test_floor&seiling2.x");
		m_OriginalBlock[BLOCK_08].Load("Data/Blender/Block_08/test_floor&seiling3.x");
		m_OriginalBlock[BLOCK_09].Load("Data/Blender/Block_09/test_floor&seiling4.x");
		m_OriginalBlock[BLOCK_10].Load("Data/Blender/Block_10/test_floor&seiling5.x");
		m_OriginalBlock[BLOCK_11].Load("Data/Blender/Block_11/test_floor&seiling6.x");
		m_OriginalBlock[BLOCK_12].Load("Data/Blender/Block_12/test_floor&seiling7.x");
		m_OriginalBlock[BLOCK_13].Load("Data/Blender/Block_13/test_pillar.x");
		m_OriginalBlock[BLOCK_14].Load("Data/Blender/Block_14/test_pillar_start.x");
		m_OriginalBlock[BLOCK_15].Load("Data/Blender/Block_15/test_floor.x");

	}
	else if (m_StageType == StageType::JUNGLE_PLANET)
	{

	}
	else if (m_StageType == StageType::LAVA_PLANET)
	{

	}
	else if (m_StageType == StageType::POLLUTION_PLANET)
	{

	}
}

void StageObjectManager::Start()
{
	for (auto& obj : m_StageObjects)
	{
		obj->Start();
	}
}

void StageObjectManager::Update()
{
	for (auto& obj : m_StageObjects)
	{
		obj->Update();
	}
}

void StageObjectManager::Draw()
{
	for (auto& obj : m_StageObjects)
	{
		obj->Draw();
	}
}

void StageObjectManager::Fin()
{
	for (auto& obj : m_StageObjects)
	{
		obj->Fin();
		delete obj;
	}
	m_StageObjects.clear();
	if (m_OriginalBlock)
	{
		delete[] m_OriginalBlock;
		m_OriginalBlock = nullptr;
	}
}

Block* StageObjectManager::CreateBlock(int id)
{
	if (id < 0 || id >= BLOCK_MAX) return nullptr;
	
	StageObject* newBlock = m_OriginalBlock[id].Clone();
	m_StageObjects.push_back(newBlock);
	return static_cast<Block*>(newBlock);

}

Block* StageObjectManager::CreateOriginalBlock(int id, VECTOR pos, VECTOR rot, VECTOR scale)
{
	Block* block = CreateBlock(id);
	if (block)
	{
		block->SetTransform(pos, rot, scale);
	}
	return block;
}