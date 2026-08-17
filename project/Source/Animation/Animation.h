#pragma once

#define ANIM_FRAME_MAX 20

struct AnimationData
{
	bool active;
	bool isLoop;
	int handle[ANIM_FRAME_MAX];
	int nowFrame;
	int frameNum;
	int frameWidth;
	int frameHeight;
	int timer;
	int interval;
	int isEnd;
};

void InitAnimation(AnimationData* animData);
void UpdateAnimation(AnimationData* animaData);

void StartAnimation(AnimationData* animData,
	int interval, int frameNum, bool isLoop);

int GetAnimationHandle(AnimationData* animData);