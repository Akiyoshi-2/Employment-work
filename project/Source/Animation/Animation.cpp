#include "DxLib.h"
#include "Animation.h"

void InitAnimation(AnimationData* animData)
{
	animData->active = false;
	
	for (int i = 0; i < ANIM_FRAME_MAX; i++)
	{
		animData->handle[i] = -1;
	}

	animData->nowFrame = 0;
	animData->frameNum = 0;
	animData->frameWidth = 0;
	animData->frameHeight = 0;
	animData->timer = 0;
}

void StartAnimation(AnimationData* animData,
	int interval, int frameNum, bool isLoop)
{
	animData->active = true;

	animData->interval = interval;

	animData->timer = interval;

	animData->nowFrame = 0;
	animData->frameNum = frameNum;

	animData->isLoop = isLoop;
	animData->isEnd = false;
}

void UpdateAnimation(AnimationData* animData)
{
	if (!animData->active) return;

	if (animData->timer <= 0)
	{
		animData->nowFrame++;

		animData->timer = animData->interval;

		if (animData->nowFrame >= animData->frameNum)
		{
			if (animData->isLoop)
			{
				animData->nowFrame = 0;
			}
			else
			{
				animData->active = false;
			}

			return;
		}
	}

	animData->timer--;
}

int GetAnimationHandle(AnimationData* animData)
{
	return animData->handle[animData->nowFrame];
}