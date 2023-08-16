#pragma once
#include <vector>
#include "ContentsEnum.h"
#include "ActorEnum.h"

class GameMapInfo
{
public:
	static const GameMapInfo DefaultInfo;

	TileObjectOrder MapInfo = TileObjectOrder::Empty;
	int GroundTextureInfo = 0;
	int ObjectTextureInfo = 0;

	float LerpTimer = 0.0f;

	float Timer = 0.0f;
	int BubblePower = 0;
	bool PrevPop = false;
};

class GameMapIndex
{
public:
	int X = -1;
	int Y = -1;
};

class GameMapBubble
{
public:
	GameMapIndex Index = { -1, -1 };
	PlayerNum BubbleMaster = PlayerNum::P1;
};