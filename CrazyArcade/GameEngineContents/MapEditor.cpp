#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "MapEditor.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "BackGround.h"
#include "TileSelect.h"

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
	Back = CreateActor<BackGround>(UpdateOrder::Map);
	if (nullptr == Back)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	Back->Init("MapEditorBack.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());

	SelectedTile = CreateActor<TileSelect>(UpdateOrder::Map);
	SelectedTile->Off();

	if (nullptr == Tile)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Tile");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("DefaultTile.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("DefaultTile.bmp", 1, 1);

		Tile = CreateActor<TileMap>();
		Tile->CreateTileMap("DefaultTile.bmp", Index_X, Index_Y, Tile_Size, RenderOrder::BackGround);

		for (int Y = 0; Y < Index_Y; Y++)
		{
			for (int X = 0; X < Index_X; X++)
			{
				Tile->SetTile(X, Y, 0, Tile_StartPos);
			}
		}

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Grass01.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Grass01.bmp", 1, 1);
	}
}

void MapEditor::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	CurMousePos = GameEngineWindow::MainWindow.GetMousePos();

	if(true == MouseInTileMap())
	{
		SelectedTile->On();
		CurTileIndex_X = int(CurMousePos.X - Tile_StartPos.X) / 40;
		CurTileIndex_Y = int(CurMousePos.Y - Tile_StartPos.Y) / 40;

		SelectedTile->SetPos({ 
			Tile_StartPos.X + (Tile_Size.X * CurTileIndex_X) + Tile_Size.hX(), 
			Tile_StartPos.Y + (Tile_Size.Y * CurTileIndex_Y) + Tile_Size.hY() });
	}
	else
	{
		SelectedTile->Off();
	}
	
	if (true == GameEngineInput::IsPress(VK_LBUTTON))
	{
		Tile->GetTile(CurTileIndex_X, CurTileIndex_Y)->SetTexture("Grass01.bmp");
	}
}

void MapEditor::Render(float _Delta)
{

}

bool MapEditor::MouseInTileMap()
{
	if (CurMousePos.X > Tile_StartPos.X &&
		CurMousePos.Y > Tile_StartPos.Y &&
		CurMousePos.X < Tile_StartPos.X + (Tile_Size.X * Index_X) &&
		CurMousePos.Y < Tile_StartPos.Y + (Tile_Size.Y * Index_Y))
	{
		return true;
	}

	return false;
}
