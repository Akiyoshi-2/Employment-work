#pragma once
#include "../SceneBase.h"

class GameOver : public SceneBase
{
public:
	GameOver();
	~GameOver();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

private:

};

