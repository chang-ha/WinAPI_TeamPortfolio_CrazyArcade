#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "MapEditor.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"
#include "BackGround.h"
#include "TileSelect.h"
#include "GlobalLoad.h"

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

	// 맵 스프라이트 로드
	GlobalLoad::TileTextureLoad();

	if (nullptr == DrawingVlew)
	{
		DrawingVlew = CreateActor<TileMap>();
		DrawingVlew->CreateTileMap("Grounds.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::Map);

		for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
		{
			for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
			{
				TileRenderer = DrawingVlew->SetTile(X, Y, 0, GlobalValue::TileStartPos);
			}
		}
	}

	if (nullptr == SelectView)
	{
		SelectView = CreateActor<TileMap>();
		SelectView->CreateTileMap("Grounds.bmp", SelectViewSize_X, SelectViewSize_Y, GlobalValue::MapTileSize, RenderOrder::Map);

		for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
		{
			for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
			{
				TileRenderer = SelectView->SetTile(X, Y, 0, SelectView_StartPos);
			}
		}
	}

	// 타일정보 벡터 초기화
	TilesInfo.assign(GlobalValue::MapTileIndex_Y, (std::vector<int>(GlobalValue::MapTileIndex_X, 0)));
}

void MapEditor::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	CurMousePos = GameEngineWindow::MainWindow.GetMousePos();

	if(true == MouseInTileMap())
	{
		SelectedTile->On();
		CurTileIndex_X = int(CurMousePos.X - GlobalValue::TileStartPos.X) / 40;
		CurTileIndex_Y = int(CurMousePos.Y - GlobalValue::TileStartPos.Y) / 40;

		SelectedTile->SetPos({ 
			GlobalValue::TileStartPos.X + (GlobalValue::MapTileSize.X * CurTileIndex_X) + GlobalValue::MapTileSize.hX(),
			GlobalValue::TileStartPos.Y + (GlobalValue::MapTileSize.Y * CurTileIndex_Y) + GlobalValue::MapTileSize.hY() });

		if (true == GameEngineInput::IsPress(VK_LBUTTON))
		{
			DrawingVlew->SetTile(CurTileIndex_X, CurTileIndex_Y, CurSelectedTileType, GlobalValue::TileStartPos);
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
}

void MapEditor::Render(float _Delta)
{

}

bool MapEditor::MouseInTileMap()
{
	if (CurMousePos.X > GlobalValue::TileStartPos.X &&
		CurMousePos.Y > GlobalValue::TileStartPos.Y &&
		CurMousePos.X < GlobalValue::TileStartPos.X + (GlobalValue::MapTileSize.X * GlobalValue::MapTileIndex_X) &&
		CurMousePos.Y < GlobalValue::TileStartPos.Y + (GlobalValue::MapTileSize.Y * GlobalValue::MapTileIndex_Y))
	{
		return true;
	}

	return false;
}
