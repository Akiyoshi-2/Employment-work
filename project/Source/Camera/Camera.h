#pragma once
#include "CameraBase.h"

class Camera : public CameraBase
{
public:
	Camera();
	~Camera();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

	void SetPosition(VECTOR pos);
	void SetTarget(VECTOR target);

private:

};

