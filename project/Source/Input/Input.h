#pragma once

namespace Input
{
	enum InputKey
	{
		KEY_UP = (1 << 0),
		KEY_DOWN = (1 << 1),
		KEY_LEFT = (1 << 2),
		KEY_RIGHT = (1 << 3),
		KEY_Z = (1 << 4),
		KEY_W = (1 << 5),
		KEY_A = (1 << 6),
		KEY_S = (1 << 7),
		KEY_D = (1 << 8),
		KEY_SPACE = (1 << 9),
	};

	void Init();
	void Update();
	void Draw();
	void Fin();

	bool IsInputKey(InputKey key);

	bool IsTriggerKey(InputKey key);
}