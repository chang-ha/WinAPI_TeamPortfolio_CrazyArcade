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
	// 타일 개수 변동이 많아서 클래스로 제작했음.
	if (false == LoadTileTexture)
	{
		LoadTileTexture = true;
		GlobalUtils::SpriteFileLoad("Grounds.bmp", "Resources\\Textures\\Tile", GroundMaxIndex + 1, 1);
		GlobalUtils::SpriteFileLoad("Structures.bmp", "Resources\\Textures\\Tile", StructureMaxIndex + 1, 1);
		GlobalUtils::SpriteFileLoad("ImMovableBlocks.bmp", "Resources\\Textures\\Tile", ImmovableBlockMaxIndex + 1, 1);
		GlobalUtils::SpriteFileLoad("MovableBlocks.bmp", "Resources\\Textures\\Tile", MovableBlockMaxIndex + 1, 1);
		GlobalUtils::SpriteFileLoad("Pop_Tile.bmp", "Resources\\Textures\\Tile", 4, 1);
		GlobalUtils::SpriteFileLoad("Boss_Pop.bmp", "Resources\\Textures\\Tile", 6, 1);
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
		GlobalUtils::SpriteFileLoad("Item_Bubble.bmp", "Resources\\Textures\\Item\\", 3, 1);
		GlobalUtils::SpriteFileLoad("Item_Fluid.bmp", "Resources\\Textures\\Item\\", 3, 1);
		GlobalUtils::SpriteFileLoad("Item_Roller.bmp", "Resources\\Textures\\Item\\", 3, 1);
		GlobalUtils::SpriteFileLoad("Item_Ultra.bmp", "Resources\\Textures\\Item\\", 3, 1);
		GlobalUtils::SpriteFileLoad("Item_Red_Devil.bmp", "Resources\\Textures\\Item\\", 3, 1);
		GlobalUtils::SpriteFileLoad("Item_Needle.bmp", "Resources\\Textures\\Item\\", 3, 1);

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
