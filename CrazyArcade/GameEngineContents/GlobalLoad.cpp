#include "GlobalLoad.h"
#include "GlobalUtils.h"
bool GlobalLoad::LoadTileTexture = false;
bool GlobalLoad::LoadItemTexture = false;

GlobalLoad::GlobalLoad()
{
}

GlobalLoad::~GlobalLoad()
{
}

void GlobalLoad::TileTextureLoad()
{
	// Ÿ�� ���� ������ ���Ƽ� Ŭ������ ��������.
	if (false == LoadTileTexture)
	{
		LoadTileTexture = true;
		GlobalUtils::SpriteFileLoad("Grounds.bmp", "Resources\\Textures\\Tile", GroundMaxIndex + 1, 1);
		GlobalUtils::SpriteFileLoad("Structures.bmp", "Resources\\Textures\\Tile", StructureMaxIndex + 1, 1);
		GlobalUtils::SpriteFileLoad("ImMovableBlocks.bmp", "Resources\\Textures\\Tile", ImmovableBlockMaxIndex + 1, 1);
		GlobalUtils::SpriteFileLoad("MovableBlocks.bmp", "Resources\\Textures\\Tile", MovableBlockMaxIndex + 1, 1);
		GlobalUtils::SpriteFileLoad("Pop_Tile.bmp", "Resources\\Textures\\Tile", 4, 1);
		GlobalUtils::SpriteFileLoad("Bubble.bmp", "Resources\\Textures\\Tile\\Bubble", 3, 1);
		GlobalUtils::SpriteFileLoad("Pop.bmp", "Resources\\Textures\\Tile\\Bubble", 6, 1);
		GlobalUtils::SpriteFileLoad("Left_1.bmp", "Resources\\Textures\\Tile\\Bubble", 11, 1);
		GlobalUtils::SpriteFileLoad("Right_1.bmp", "Resources\\Textures\\Tile\\Bubble", 11, 1);
		GlobalUtils::SpriteFileLoad("Up_1.bmp", "Resources\\Textures\\Tile\\Bubble", 11, 1);
		GlobalUtils::SpriteFileLoad("Down_1.bmp", "Resources\\Textures\\Tile\\Bubble", 11, 1);
		GlobalUtils::SpriteFileLoad("Left_2.bmp", "Resources\\Textures\\Tile\\Bubble", 11, 1);
		GlobalUtils::SpriteFileLoad("Right_2.bmp", "Resources\\Textures\\Tile\\Bubble", 11, 1);
		GlobalUtils::SpriteFileLoad("Up_2.bmp", "Resources\\Textures\\Tile\\Bubble", 11, 1);
		GlobalUtils::SpriteFileLoad("Down_2.bmp", "Resources\\Textures\\Tile\\Bubble", 11, 1);
	}
}

void GlobalLoad::ItemTextureLoad()
{
	if (false == LoadItemTexture)
	{
		LoadItemTexture = true;

		// Item
		GlobalUtils::TextureFileLoad("Fluid.bmp", "Resources\\Textures\\Item\\");

		// Shadow
		GlobalUtils::TextureFileLoad("ItemShadow1.bmp", "Resources\\Textures\\Item\\");
		GlobalUtils::TextureFileLoad("ItemShadow2.bmp", "Resources\\Textures\\Item\\");
	}
}

void GlobalLoad::LoadMapInfoTexture()
{
	GlobalUtils::TextureFileLoad("MapSelect_SelectImageBar_Active.bmp", "Resources\\Textures\\UI\\MapSelect");

	GlobalUtils::TextureFileLoad("MapSelect_SelectImageBar_Active.bmp", "Resources\\Textures\\UI\\MapSelect");
}
