#include "GlobalLoad.h"
#include "GlobalUtils.h"
bool GlobalLoad::LoadTexture = false;

GlobalLoad::GlobalLoad()
{
}

GlobalLoad::~GlobalLoad()
{
}

void GlobalLoad::TileTextureLoad()
{
	// 타일 개수 변동이 많아서 클래스로 제작했음.
	if (false == LoadTexture)
	{
		LoadTexture = true;
		GlobalUtils::SpriteFileLoad("Grounds.bmp", "Resources\\Textures\\Tile", 10, 1);
		GlobalUtils::SpriteFileLoad("Structures.bmp", "Resources\\Textures\\Tile", 5, 1);
		GlobalUtils::SpriteFileLoad("ImMovableBlocks.bmp", "Resources\\Textures\\Tile", 3, 1);
		GlobalUtils::SpriteFileLoad("MovableBlocks.bmp", "Resources\\Textures\\Tile", 2, 1);
	}
}
