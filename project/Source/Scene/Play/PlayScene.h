#pragma once
#include "../SceneBase.h"

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

	// void DrawGravityChange();

private:
	
	/*int m_GravityUpHandle;
	int m_GravityDownHandle;
	int m_GravityLeftHandle;
	int m_GravityRightHandle;*/
};
