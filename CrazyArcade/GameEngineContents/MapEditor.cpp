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

	if (nullptr == Tile)
	{
		if (false == ResourcesManager::GetInst().IsLoadTexture("DefaultTile.bmp"))
		{
			ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("DefaultTile.bmp"));
			ResourcesManager::GetInst().CreateSpriteSheet("DefaultTile.bmp", 1, 1);
		}
		
		Tile = CreateActor<TileMap>();
		Tile->CreateTileMap("DefaultTile.bmp", Index_X, Index_Y, Tile_Size, RenderOrder::BackGround);

		for (int Y = 0; Y < Index_Y; Y++)
		{
			for (int X = 0; X < Index_X; X++)
			{
				Tile->SetTile(X, Y, 0, Tile_StartPos);
			}
		}
	}

	if (LoadTileTexture == false)
	{
		// 임시 텍스처 로드
		LoadTileTexture = true;
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Grass01.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Grass01.bmp", 1, 1);

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Grass02.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Grass02.bmp", 1, 1);

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("GreenBlock01.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("GreenBlock01.bmp", 1, 1);

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Road01.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Road01.bmp", 1, 1);

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Road02.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Road02.bmp", 1, 1);

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Road03.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet("Road03.bmp", 1, 1);
	}

	for (int i = 0; i < Index_Y; i++)
	{
		std::vector<int> vec(Index_X);
		TilesInfo.push_back(vec);
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

		if (true == GameEngineInput::IsPress(VK_LBUTTON))
		{
			SetTileTexture();
			TilesInfo[CurTileIndex_Y][CurTileIndex_X] = CurSelectedTileType;
		}
	}
	else
	{
		SelectedTile->Off();
	}

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

void MapEditor::SetTileTexture()
{
	std::string _FileName;

	switch (CurSelectedTileType)
	{
	case 0:
		Tile->GetTile(CurTileIndex_X, CurTileIndex_Y)->SetTexture("DefaultTile.bmp");
		break;
	case 1:
		Tile->GetTile(CurTileIndex_X, CurTileIndex_Y)->SetTexture("Grass01.bmp");
		break;
	case 2:
		Tile->GetTile(CurTileIndex_X, CurTileIndex_Y)->SetTexture("Grass02.bmp");
		break;
	case 3:
		Tile->GetTile(CurTileIndex_X, CurTileIndex_Y)->SetTexture("GreenBlock01.bmp");
		break;
	case 4:
		Tile->GetTile(CurTileIndex_X, CurTileIndex_Y)->SetTexture("Road01.bmp");
		break;
	case 5:
		Tile->GetTile(CurTileIndex_X, CurTileIndex_Y)->SetTexture("Road02.bmp");
		break;
	case 6:
		Tile->GetTile(CurTileIndex_X, CurTileIndex_Y)->SetTexture("Road03.bmp");
		break;

	default:
		break;
	}
	
}