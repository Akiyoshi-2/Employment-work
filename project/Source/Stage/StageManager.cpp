#include "StageManager.h"
#include "StageParameter.h"
#include "../Player/PlayerManager.h"
#include "../StageObject/StageObjectManager.h"
#include "../Enemy/EnemyManager.h"
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

	json stageJson;
	file >> stageJson;

	m_Objects = stageJson[KEY_ITEMS].get<std::vector<GameObject>>();

	m_StageObjectManager = StageObjectManager::GetInstance();

	file.close();
}

void StageManager::Start()
{
	for (GameObject obj : m_Objects)
	{
		// ステージ
		if (obj.id >= BLOCK_00 && obj.id <= BLOCK_16)
		{
			int id = obj.id - BLOCK_00;

			StageObjectManager::GetInstance()->CreateOriginalBlock(id, obj.pos, obj.rot, obj.scale);
		}
		// ギミック

		// エネミー
		else if (obj.id >= MACHINE_ENEMY_00 && obj.id <= MACHINE_ENEMY_02)
		{
			int id = obj.id - MACHINE_ENEMY_00;

			// EnemyManager::GetInstance()->CreateEnemy(id, obj.pos, obj.rot, obj.scale);

			// デバッグ
			printfDx(
				"Enemy Create: JSON ID=%d, CreateEnemy ID=%d\n",
				obj.id, id
			);

			EnemyBase* enemy =
				EnemyManager::GetInstance()->CreateEnemy(
					id, obj.pos, obj.rot, obj.scale
				);

			if (enemy == nullptr)
			{
				printfDx("Enemy Create FAILED!\n");
			}
			else
			{
				printfDx("Enemy Create SUCCESS!\n");
			}
		}
	}
}

void StageManager::Draw()
{
}

void StageManager::Fin()
{

}
