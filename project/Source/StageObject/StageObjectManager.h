#pragma once
#include "DxLib.h"
#include <vector>

class StageObject;
class Block;
// class Trap;

class StageObjectManager
{
public:

	enum class StageType
	{
		MACHINE_PLANET,
		JUNGLE_PLANET,
		LAVA_PLANET,
		POLLUTION_PLANET,
	};

	StageObjectManager();
	~StageObjectManager();

	static void CreateInstance() { if (!m_Instance) m_Instance = new StageObjectManager; }
	static StageObjectManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

	void Init();
	void Load();
	void Start();
	void Update();
	void Draw();
	void Fin();

	// Blockê∂ê¨
	Block* CreateBlock(int id);
	Block* CreateOriginalBlock(int id, VECTOR pos, VECTOR rot, VECTOR scale);

	std::vector<StageObject*>& GetStageObjects() { return m_StageObjects; }

private:
	static StageObjectManager* m_Instance;
	std::vector<StageObject*> m_StageObjects;
	Block* m_OriginalBlock;

	StageType m_StageType;
};

