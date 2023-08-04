#pragma once
#include <vector>
#include "ContentsEnum.h"
class GameMapInfo
{
public:
	static const GameMapInfo DefaultInfo;

	TileObjectOrder MapInfo = TileObjectOrder::Empty;
	int GroundTextureInfo = 0;
	int ObjectTextureInfo = 0;

	float Timer = 0.0f;
	float LerpTimer = 0.0f;
	bool PrevPop = false;
};

class GameMapIndex
{
public:
	int X = -1;
	int Y = -1;
};