#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "MapEditor.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
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

	// 맵 스프라이트 로드
	GlobalUtils::SpriteFileLoad("Grounds.bmp", "Resources\\Textures\\Tile", GlobalValue::AllTextureIndex_X, GlobalValue::GroundTextureIndex_Y);
	GlobalUtils::SpriteFileLoad("Structures.bmp", "Resources\\Textures\\Tile", GlobalValue::AllTextureIndex_X, GlobalValue::StructureTextureIndex_Y);
	GlobalUtils::SpriteFileLoad("ImMovableBlocks.bmp", "Resources\\Textures\\Tile", GlobalValue::AllTextureIndex_X, GlobalValue::ImmovableBlockTextureIndex_Y);
	GlobalUtils::SpriteFileLoad("MovableBlocks.bmp", "Resources\\Textures\\Tile", GlobalValue::AllTextureIndex_X, GlobalValue::MovableBlockTextureIndex_Y);

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


	InitTiles();

	CurrentSelectTileType = SelectTileType::Ground;

	GameEngineWindowTexture* GroundsTexture = ResourcesManager::GetInst().FindTexture("Grounds.bmp");
	if (nullptr == GroundsTexture)
	{
		MsgBoxAssert("스프라이트를 불러오지 못했습니다.");
		return;
	}

 	float4 TextureScale = GroundsTexture->GetScale();
	int TilesXCount = static_cast<int>(TextureScale.X / GlobalValue::MapTileSize.X);
	int TilesYCount = static_cast<int>(TextureScale.Y / GlobalValue::MapTileSize.Y);
	CurSelectTilesCount  = TilesXCount * TilesYCount;

	for (int TilesTexture = 0; TilesTexture < CurSelectTilesCount ; TilesTexture++)
	{
		SelectView->SetTile(TilesTexture % SelectViewSize_X, TilesTexture / SelectViewSize_X, TilesTexture, SelectView_StartPos);
	}

	LoadButton();


	// 타일정보 벡터 초기화
	TilesInfo.assign(GlobalValue::MapTileIndex_Y, (std::vector<int>(GlobalValue::MapTileIndex_X, 0)));
}

void MapEditor::InitTiles()
{
	VecTileSpriteFileName.resize(static_cast<int>(SelectTileType::Max));

	VecTileSpriteFileName[static_cast<int>(SelectTileType::Ground)] = "Grounds.bmp";
	VecTileSpriteFileName[static_cast<int>(SelectTileType::ImmovableBlock)] = "ImmovableBlocks.bmp";
	VecTileSpriteFileName[static_cast<int>(SelectTileType::MovableBlock)] = "MovableBlocks.bmp";
	//VecTileSpriteFileName[static_cast<int>(SelectTileType::Structure)] = "Structures.bmp";
}


void MapEditor::LoadButton()
{
	VecButton.resize(static_cast<int>(MapEditorButtonState::Max));

	Button* NextButton = CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == NextButton)
	{
		MsgBoxAssert("Prev 버튼을 생성하지 못했습니다.");
		return;
	}

	NextButton->setRenderer(RenderOrder::FirstElementUI);
	NextButton->setButtonTexture(ButtonState::Normal, "Button_Next_Normal.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	NextButton->setButtonTexture(ButtonState::Click, "Button_Next_Click.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	NextButton->setButtonTexture(ButtonState::Hover, "Button_Next_Normal.bmp", "Resources\\Textures\\UI\\Button", 1, 1);

	//ButtonPtr->setButtonSound(ButtonEventState::Click, )

	NextButton->setCallback<MapEditor>(ButtonEventState::Click, this, &MapEditor::ClickNextButton);

	float4 SelectView_EndXPos = SelectView_StartPos + 
		float4{ 0.0f , static_cast<float>(SelectViewSize_Y) * GlobalValue::MapTileSize.Y };

	float4 NextButtonPos = SelectView_EndXPos + LocalNextButtonStartPos;

	NextButton->setButtonPos(NextButtonPos);
	VecButton[static_cast<int>(MapEditorButtonState::Next)] = NextButton;



	Button* PrevButton = CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == PrevButton)
	{
		MsgBoxAssert("Prev 버튼을 생성하지 못했습니다.");
		return;
	}

	PrevButton->setRenderer(RenderOrder::FirstElementUI);
	PrevButton->setButtonTexture(ButtonState::Normal, "Button_Prev_Normal.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	PrevButton->setButtonTexture(ButtonState::Click, "Button_Prev_Click.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	PrevButton->setButtonTexture(ButtonState::Hover, "Button_Prev_Normal.bmp", "Resources\\Textures\\UI\\Button", 1, 1);

	//ButtonPtr->setButtonSound(ButtonEventState::Click, )

	PrevButton->setCallback<MapEditor>(ButtonEventState::Click, this, &MapEditor::ClickPrevButton);

	GameEngineSprite* PrevButtonSprite = ResourcesManager::GetInst().FindSprite("Button_Prev_Normal.bmp");
	if (nullptr == PrevButtonSprite)
	{
		MsgBoxAssert("스프라이트를 불러오지 못했습니다.");
		return;
	}

	float4 ButtonRenderScale = PrevButtonSprite->GetSprite(0).RenderScale;


	float4 PrevButtonPos = SelectView_EndXPos + 
		float4{ static_cast<float>(SelectViewSize_X) * GlobalValue::MapTileSize.X - LocalNextButtonStartPos.X - ButtonRenderScale.X, LocalNextButtonStartPos.Y };

	PrevButton->setButtonPos(PrevButtonPos);
	VecButton[static_cast<int>(MapEditorButtonState::Prev)] = PrevButton;
}



void MapEditor::ClickPrevButton()
{
	ClearSelectViewTiles();

	int IntTileType = static_cast<int>(CurrentSelectTileType) - 1;
	if (-1 == IntTileType)
	{
		CurrentSelectTileType = SelectTileType::MovableBlock;
	}
	else
	{
		CurrentSelectTileType = static_cast<SelectTileType>(IntTileType);
	}

	ChangeSelectViewTile();

	for (int TilesTexture = 0; TilesTexture < CurSelectTilesCount; TilesTexture++)
	{
		SelectView->SetTileToSprite(
			TilesTexture % SelectViewSize_X, TilesTexture / SelectViewSize_X,
			VecTileSpriteFileName[static_cast<int>(CurrentSelectTileType)],
			TilesTexture, SelectView_StartPos);
	}
}

void MapEditor::ClickNextButton()
{
	ClearSelectViewTiles();

	int IntTileType = static_cast<int>(CurrentSelectTileType) + 1;
	CurrentSelectTileType = static_cast<SelectTileType>(IntTileType);
	if (SelectTileType::Max == CurrentSelectTileType)
	{
		CurrentSelectTileType = SelectTileType::Ground;
	}

	ChangeSelectViewTile();

	for (int TilesTexture = 0; TilesTexture < CurSelectTilesCount; TilesTexture++)
	{
		SelectView->SetTileToSprite(
			TilesTexture % SelectViewSize_X, TilesTexture / SelectViewSize_X,
			VecTileSpriteFileName[static_cast<int>(CurrentSelectTileType)], 
			TilesTexture, SelectView_StartPos);
	}
}

void MapEditor::ClearSelectViewTiles()
{
	for (int TilesTexture = 0; TilesTexture < SelectViewSize_X * SelectViewSize_Y; TilesTexture++)
	{
		SelectView->SetTile(TilesTexture % SelectViewSize_X, TilesTexture / SelectViewSize_X, 0, SelectView_StartPos);
	}
}

void MapEditor::ChangeSelectViewTile()
{
	GameEngineWindowTexture* GroundsTexture = 
		ResourcesManager::GetInst().FindTexture(VecTileSpriteFileName[static_cast<int>(CurrentSelectTileType)]);
	if (nullptr == GroundsTexture)
	{
		MsgBoxAssert("스프라이트를 불러오지 못했습니다.");
		return;
	}

	float4 TextureScale = GroundsTexture->GetScale();
	int TilesXCount = static_cast<int>(TextureScale.X / GlobalValue::MapTileSize.X);
	int TilesYCount = static_cast<int>(TextureScale.Y / GlobalValue::MapTileSize.Y);
	CurSelectTilesCount  = TilesXCount * TilesYCount;
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


	UpdateDrawingTileUI();



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
	if (true == GameEngineInput::IsDown('8'))
	{
		CurSelectedTileType = 8;
	}
	if (true == GameEngineInput::IsDown('9'))
	{
		CurSelectedTileType = 9;
	}
}

void MapEditor::UpdateDrawingTileUI()
{
	if (true == MouseInDrawingTileMap())
	{
		SelectedTile->On();
		int CurDrawingTileIndex_X = int(CurMousePos.X - SelectView_StartPos.X) / 40;
		int CurDrawingTileIndex_Y = int(CurMousePos.Y - SelectView_StartPos.Y) / 40;

		SelectedTile->SetPos({
			SelectView_StartPos.X + (GlobalValue::MapTileSize.X * CurDrawingTileIndex_X) + GlobalValue::MapTileSize.hX(),
			SelectView_StartPos.Y + (GlobalValue::MapTileSize.Y * CurDrawingTileIndex_Y) + GlobalValue::MapTileSize.hY() });

		if (true == GameEngineInput::IsDown(VK_LBUTTON))
		{
			int TemporaryCurSelectedTileType = CurDrawingTileIndex_Y * 3 + CurDrawingTileIndex_X;

			if (TemporaryCurSelectedTileType < CurSelectTilesCount )
			{
				CurSelectedTileType = TemporaryCurSelectedTileType;
			}
		}
	}
	else
	{
		SelectedTile->Off();
	}
}



void MapEditor::Render(float _Delta)
{
	if (false == ContentLevel::DebugValue)
	{
		return;
	}

	GameEngineWindowTexture* BackBufferPtr = GameEngineWindow::MainWindow.GetBackBuffer();
	if (nullptr == BackBufferPtr)
	{
		MsgBoxAssert("버퍼를 불러오지 못했습니다.");
		return;
	}

	HDC dc = BackBufferPtr->GetImageDC();
	if (nullptr == dc)
	{
		MsgBoxAssert("HDC를 불러오지 못했습니다.");
		return;
	}



	{
		std::string Text = "";

		TextOutA(dc, 0, 0, Text.c_str(), static_cast<int>(Text.size()));
	}
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

bool MapEditor::MouseInDrawingTileMap()
{
	if (CurMousePos.X > SelectView_StartPos.X &&
		CurMousePos.Y > SelectView_StartPos.Y &&
		CurMousePos.X < SelectView_StartPos.X + (GlobalValue::MapTileSize.X * SelectViewSize_X) &&
		CurMousePos.Y < SelectView_StartPos.Y + (GlobalValue::MapTileSize.Y * SelectViewSize_Y))
	{
		return true;
	}

	return false;
}