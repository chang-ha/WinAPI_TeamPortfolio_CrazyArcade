#pragma once
#include <vector>
#include "ContentsEnum.h"
class GameMapInfo
{
public:
	static const GameMapInfo DefaultInfo;

	TileObjectOrder MapInfo = TileObjectOrder::Empty;
	int GroundTextureInfo = 0;
	int TileObjectTextureInfo = 0;
};