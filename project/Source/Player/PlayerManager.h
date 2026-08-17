#pragma once

class Player;

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new PlayerManager; }
	static PlayerManager* GetInstance() { return m_Instance; }
	static void DeleteInstace() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	void CreatePlayer();

	Player* GetPlayer() { return m_Player; }

private:
	static PlayerManager* m_Instance;

	Player* m_Player;
};

