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
	// Ÿ�� ���� ������ ���Ƽ� Ŭ������ ��������.
	if (false == LoadTexture)
	{
		LoadTexture = true;
		GlobalUtils::SpriteFileLoad("Grounds.bmp", "Resources\\Textures\\Tile", GroundMaxIndex + 1, 1);
		GlobalUtils::SpriteFileLoad("Structures.bmp", "Resources\\Textures\\Tile", StructureMaxIndex + 1, 1);
		GlobalUtils::SpriteFileLoad("ImMovableBlocks.bmp", "Resources\\Textures\\Tile", ImmovableBlockMaxIndex + 1, 1);
		GlobalUtils::SpriteFileLoad("MovableBlocks.bmp", "Resources\\Textures\\Tile", MovableBlockMaxIndex + 1, 1);
		GlobalUtils::SpriteFileLoad("Bubble.bmp", "Resources\\Textures\\Tile", 4, 1);
	}
}
