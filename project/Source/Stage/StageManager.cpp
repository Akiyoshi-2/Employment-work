#include "StageManager.h"
#include "StageParameter.h"
#include "../Player/PlayerManager.h"
#include "../StageObject/StageObjectManager.h"
#include <fstream>

using json = nlohmann::json;
constexpr const char* KEY_ITEMS = "item";

StageManager* StageManager::m_Instance = nullptr;


StageManager::StageManager()
{
	m_StageObjectManager = nullptr;
}

StageManager::~StageManager()
{
    Fin();
}

void StageManager::Load(const char* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return;
	}

	// JSON“Ç‚Ýž‚Ý
	json stageJson;
	file >> stageJson;

	m_Objects = stageJson[KEY_ITEMS].get<std::vector<GameObject>>();

	m_StageObjectManager = StageObjectManager::GetInstance();

	if (m_StageObjectManager == nullptr) return;
	
	for (const auto& obj : m_Objects)
	{
		m_StageObjectManager->CreateOriginalBlock(
			obj.id,
			obj.pos,
			obj.rot,
			obj.scale);
	}

	file.close();
}

void StageManager::Start()
{
}

void StageManager::Draw()
{
}

void StageManager::Fin()
{

}
