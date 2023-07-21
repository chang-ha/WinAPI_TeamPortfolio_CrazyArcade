#define TILESIZE float4{24 , 24}

#include <GameEngineBase/GameEnginePath.h>

#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>

#include "MapEditor.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

MapEditor::MapEditor()
{

}

MapEditor::~MapEditor()
{

}

void MapEditor::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void MapEditor::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void MapEditor::Start()
{
	if (nullptr == Tile)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\BackGround\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TileMap.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("TileMap.bmp", 1, 1);

		int Index_X = GlobalValue::WinScale.iX() / TILESIZE.iX();
		int Index_Y = GlobalValue::WinScale.iY() / TILESIZE.iY();

		Tile = CreateActor<TileMap>();
		Tile->CreateTileMap("TileMap.bmp", Index_X, Index_Y, TILESIZE, RenderOrder::BackGround);

		for (int Y = 0; Y < Index_Y; Y++)
		{
			for (int X = 0; X < Index_X; X++)
			{
				Tile->SetTile(X, Y, 0);
			}
		}
	}
}

void MapEditor::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void MapEditor::Render(float _Delta)
{

}