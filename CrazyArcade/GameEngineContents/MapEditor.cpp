#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSprite.h>
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
#include "GameMapInfo.h"

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

	DrawingVlew_SelectedPlace = CreateActor<TileSelect>(UpdateOrder::Map);
	DrawingVlew_SelectedPlace->Off();

	SelectView_SelectedPlace = CreateActor<TileSelect>(UpdateOrder::Map);
	SelectView_SelectedPlace->Off();

	// Object Texture Load
	GlobalLoad::TileTextureLoad();

	// TileInfo Initialize
	TileInfo.assign(GlobalValue::MapTileIndex_Y, (std::vector<GameMapInfo>(GlobalValue::MapTileIndex_X, GameMapInfo::DefaultInfo)));

	// Tile Initialize
	TileInit();
	
	// Default Setting
	ChangeSelectViewInfo(TileObjectOrder::Empty);
	AllOffSelectVlew();
	SelectView_Grounds->On();
}

void MapEditor::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	CurMousePos = GameEngineWindow::MainWindow.GetMousePos();

	// Mouse In Drawing View 

	if (true == MouseInTileMap(GlobalValue::TileStartPos, GlobalValue::MapTileIndex))
	{
		DrawingVlew_SelectedPlace->On();
		CurTileIndex_X = int(CurMousePos.X - GlobalValue::TileStartPos.X) / 40;
		CurTileIndex_Y = int(CurMousePos.Y - GlobalValue::TileStartPos.Y) / 40;

		DrawingVlew_SelectedPlace->SetPos({
			GlobalValue::TileStartPos.X + (GlobalValue::MapTileSize.X * CurTileIndex_X) + GlobalValue::MapTileSize.hX(),
			GlobalValue::TileStartPos.Y + (GlobalValue::MapTileSize.Y * CurTileIndex_Y) + GlobalValue::MapTileSize.hY() });

		if (true == GameEngineInput::IsPress(VK_LBUTTON))
		{
			if (CurSelectedObjectType == TileObjectOrder::Empty)
			{
				DrawingView_Ground->SetTile(CurTileIndex_X, CurTileIndex_Y, ObjectTextureIndex, GlobalValue::TileStartPos);
				TileInfo[CurTileIndex_Y][CurTileIndex_X].GroundTextureInfo = ObjectTextureIndex;
			}
			else
			{
				DrawingView_Object->SetTileToSprite(CurTileIndex_X, CurTileIndex_Y, SelectedTextureName, ObjectTextureIndex,
					GlobalValue::TileStartPos - CurObjectOverSize, true);

				// 정보 저장
				if (0 == ObjectTextureIndex)
				{
					TileInfo[CurTileIndex_Y][CurTileIndex_X].MapInfo = TileObjectOrder::Empty;
				}
				else 
				{
					TileInfo[CurTileIndex_Y][CurTileIndex_X].MapInfo = CurSelectedObjectType;
				}

				if ( TileObjectOrder::Empty == CurSelectedObjectType)
				{
					TileInfo[CurTileIndex_Y][CurTileIndex_X].GroundTextureInfo = ObjectTextureIndex;
				}
				else
				{
					TileInfo[CurTileIndex_Y][CurTileIndex_X].ObjectTextureInfo = ObjectTextureIndex;
				}
			}
		}
	}
	else
	{
		DrawingVlew_SelectedPlace->Off();
	}

	// Mouse In Select View
	if (true == MouseInTileMap(SelectView_StartPos, SelectViewSize))
	{
		if (true == GameEngineInput::IsDown(VK_LBUTTON))
		{
			// 저장할 정보 지정
			CurTileIndex_X = int(CurMousePos.X - SelectView_StartPos.X) / 40;
			CurTileIndex_Y = int(CurMousePos.Y - SelectView_StartPos.Y) / 40;

			if (ObjectSpriteMaxIndex >= (CurTileIndex_Y * SelectViewSize_X) + CurTileIndex_X)
			{
				SelectView_SelectedPlace->On();
				SelectView_SelectedPlace->SetPos({
					   SelectView_StartPos.X + (GlobalValue::MapTileSize.X * CurTileIndex_X) + GlobalValue::MapTileSize.hX(),
					   SelectView_StartPos.Y + (GlobalValue::MapTileSize.Y * CurTileIndex_Y) + GlobalValue::MapTileSize.hY() });

				ObjectTextureIndex = (CurTileIndex_Y * SelectViewSize_X) + CurTileIndex_X;
			}
		}
	}

	// 임시 타일 변경 기능
	if (true == GameEngineInput::IsDown('1'))
	{
		ChangeSelectViewInfo(TileObjectOrder::Empty);
		AllOffSelectVlew();
		SelectView_Grounds->On();
		SelectView_SelectedPlace->Off();

		ObjectTextureIndex = 0;
	}
	if (true == GameEngineInput::IsDown('2'))
	{
		ChangeSelectViewInfo(TileObjectOrder::Structure);
		AllOffSelectVlew();
		SelectView_Structures->On();
		SelectView_SelectedPlace->Off();
		ObjectTextureIndex = 0;
	}
	if (true == GameEngineInput::IsDown('3'))
	{
		ChangeSelectViewInfo(TileObjectOrder::ImmovableBlock);
		AllOffSelectVlew();
		SelectView_ImmovableBlocks->On();
		SelectView_SelectedPlace->Off();
		ObjectTextureIndex = 0;
	}
	if (true == GameEngineInput::IsDown('4'))
	{
		ChangeSelectViewInfo(TileObjectOrder::MovableBlock);
		AllOffSelectVlew();
		SelectView_MovableBlocks->On();
		SelectView_SelectedPlace->Off();
		ObjectTextureIndex = 0;
	}

}

void MapEditor::Render(float _Delta)
{

}

void MapEditor::TileInit()
{
	if (nullptr == DrawingView_Ground)
	{
		DrawingView_Ground = CreateActor<TileMap>();
		DrawingView_Ground->CreateTileMap("Grounds.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y,
			GlobalValue::MapTileSize, RenderOrder::Map);

		for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
		{
			for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
			{
				DrawingView_Ground->SetTile(X, Y, 0, GlobalValue::TileStartPos);
			}
		}
	}

	if (nullptr == DrawingView_Object)
	{
		DrawingView_Object = CreateActor<TileMap>();
		DrawingView_Object->CreateTileMap("Structures.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y,
			GlobalValue::MapTileSize, RenderOrder::Map);
	}

	SelectView_Grounds = SelectViewInit(TileObjectOrder::Empty);
	SelectView_Structures = SelectViewInit(TileObjectOrder::Structure);
	SelectView_ImmovableBlocks = SelectViewInit(TileObjectOrder::ImmovableBlock);
	SelectView_MovableBlocks = SelectViewInit(TileObjectOrder::MovableBlock);
}



TileMap* MapEditor::SelectViewInit(TileObjectOrder _SelectedObjectType)
{
	TileMap* _Tile = nullptr;
	ChangeSelectViewInfo(_SelectedObjectType);
	
	if (nullptr == _Tile)
	{
		_Tile = CreateActor<TileMap>();
		_Tile->CreateTileMap(SelectedTextureName, SelectViewSize_X,
			(ObjectSpriteMaxIndex / SelectViewSize_X) + 1, GlobalValue::MapTileSize, RenderOrder::Map);
	}

	int IndexCount = 0;
	for (int Y = 0; Y <= SelectViewSize_Y; ++Y)
	{
		for (int X = 0; X < SelectViewSize_X; ++X)
		{
			if (ObjectSpriteMaxIndex < IndexCount)
			{
				return _Tile;
			}
			else
			{
				_Tile->SetTileToSprite(X, Y, SelectedTextureName, IndexCount, SelectView_StartPos - CurObjectOverSize, true);
				++IndexCount;
			}
		}
	}

	return nullptr;
}


void MapEditor::ChangeSelectViewInfo(TileObjectOrder _SelectedObjectType)
{
	CurSelectedObjectType = _SelectedObjectType;

	switch (_SelectedObjectType)
	{
	case TileObjectOrder::Empty:
		SelectedTextureName = "Grounds.bmp";
		CurObjectOverSize = float4::ZERO;
		ObjectSpriteMaxIndex = GlobalLoad::GroundMaxIndex;
		break;

	case TileObjectOrder::Structure:
		SelectedTextureName = "Structures.bmp";
		CurObjectOverSize = GlobalValue::StructureOverSize;
		ObjectSpriteMaxIndex = GlobalLoad::StructureMaxIndex;
		break;

	case TileObjectOrder::ImmovableBlock:
		SelectedTextureName = "ImmovableBlocks.bmp";
		CurObjectOverSize = GlobalValue::BlockOverSize;
		ObjectSpriteMaxIndex = GlobalLoad::ImmovableBlockMaxIndex;
		break;

	case TileObjectOrder::MovableBlock:
		SelectedTextureName = "MovableBlocks.bmp";
		CurObjectOverSize = GlobalValue::BlockOverSize;
		ObjectSpriteMaxIndex = GlobalLoad::MovableBlockMaxIndex;
		break;

	default:
		break;
	}
}

void MapEditor::AllOffSelectVlew()
{
	SelectView_Grounds->Off();
	SelectView_Structures->Off();
	SelectView_ImmovableBlocks->Off();
	SelectView_MovableBlocks->Off();
}

bool MapEditor::MouseInTileMap(float4& _ViewStartPos, float4& TileMaxIndex)
{
	if (CurMousePos.X > _ViewStartPos.X &&
		CurMousePos.Y > _ViewStartPos.Y &&
		CurMousePos.X < _ViewStartPos.X + (GlobalValue::MapTileSize.X * TileMaxIndex.X) &&
		CurMousePos.Y < _ViewStartPos.Y + (GlobalValue::MapTileSize.Y * TileMaxIndex.Y))
	{
		return true;
	}

	return false;
}

TileMap* MapEditor::GetCurSelectViewTile()
{
	switch (CurSelectedObjectType)
	{
	case TileObjectOrder::Empty:
		return SelectView_Grounds;
	case TileObjectOrder::Structure:
		return SelectView_Structures;
	case TileObjectOrder::ImmovableBlock:
		return SelectView_ImmovableBlocks;
	case TileObjectOrder::MovableBlock:
		return SelectView_MovableBlocks;
	default:
		return nullptr;
	}
}
