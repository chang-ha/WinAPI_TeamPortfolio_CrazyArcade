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

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("Resources");
	FilePath.MoveChild("Resources\\Textures\\Tile");

	if (false == ResourcesManager::GetInst().IsLoadTexture("DefaultTile.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("DefaultTile.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("DefaultTile.bmp", 1, 1);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Ground.bmp"))
	{
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Ground.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Ground.bmp", 8, 1);
	}

	if (nullptr == Tile)
	{
		Tile = CreateActor<TileMap>();
		Tile->CreateTileMap("Ground.bmp", Index_X, Index_Y, Tile_Size, RenderOrder::GroundTile);

		for (int Y = 0; Y < Index_Y; Y++)
		{
			for (int X = 0; X < Index_X; X++)
			{
				TileRenderer = Tile->SetTile(X, Y, 0, Tile_StartPos);
			}
		}
	}

	// 타일정보 벡터 초기화
	TilesInfo.assign(Index_Y, (std::vector<int>(Index_X, 0)));
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

		if (true == GameEngineInput::IsPress(VK_LBUTTON))
		{
			//SetTileTexture();
			Tile->SetTile(CurTileIndex_X, CurTileIndex_Y, CurSelectedTileType, Tile_StartPos);
			TilesInfo[CurTileIndex_Y][CurTileIndex_X] = CurSelectedTileType;
		}
	}
	else
	{
		SelectedTile->Off();
	}

	// 임시 타일 변경 기능
	if (true == GameEngineInput::IsDown('0'))
	{
		CurSelectedTileType = 0;
	}
	if (true == GameEngineInput::IsDown('1'))
	{
		CurSelectedTileType = 1;
	}
	if (true == GameEngineInput::IsDown('2'))
	{
		CurSelectedTileType = 2;
	}
	if (true == GameEngineInput::IsDown('3'))
	{
		CurSelectedTileType = 3;
	}
	if (true == GameEngineInput::IsDown('4'))
	{
		CurSelectedTileType = 4;
	}
	if (true == GameEngineInput::IsDown('5'))
	{
		CurSelectedTileType = 5;
	}
	if (true == GameEngineInput::IsDown('6'))
	{
		CurSelectedTileType = 6;
	}
	if (true == GameEngineInput::IsDown('7'))
	{
		CurSelectedTileType = 7;
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
