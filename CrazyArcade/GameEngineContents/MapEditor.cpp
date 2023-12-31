﻿#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineBase/GameEngineString.h>

#include "MapEditor.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"
#include "BackGround.h"
#include "TileSelect.h"
#include "GlobalLoad.h"
#include "GameMapInfo.h"
#include "Button.h"

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

	// TileInfo Initialization
	TileInfo.assign(GlobalValue::MapTileIndex_Y, (std::vector<GameMapInfo>(GlobalValue::MapTileIndex_X, GameMapInfo::DefaultInfo)));

	// Tile Initialization
	TileInit();

	// Default Setting
	ChangeSelectViewInfo(TileObjectOrder::Empty);
	SelectTilesMapNum = 0;
	AllOffSelectVlew();
	SelectView_Grounds->On();

	{
		LoadButton();
	}

	GetMainCamera()->SetYSort(RenderOrder::MapObject, true);
}

void MapEditor::LoadButton()
{
	VecButton.resize(static_cast<int>(MapEditorButtonState::Max));

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
	PrevButton->setCallback<MapEditor>(ButtonEventState::Click, this, &MapEditor::ClickPrevButton);
	PrevButton->setButtonSound(ButtonEventState::Click, "Select.wav", "Resources\\Sounds\\Lobby");


	GameEngineSprite* PrevButtonSprite = ResourcesManager::GetInst().FindSprite("Button_Prev_Normal.bmp");
	if (nullptr == PrevButtonSprite)
	{
		MsgBoxAssert("스프라이트를 불러오지 못했습니다.");
		return;
	}

	float4 ButtonRenderScale = PrevButtonSprite->GetSprite(0).RenderScale;

	float4 SelectView_EndXPos = SelectView_StartPos +
		float4{ 0.0f, static_cast<float>(SelectViewSize_Y)* GlobalValue::MapTileSize.Y };

	float4 PrevButtonPos = SelectView_EndXPos + LocalPrevButtonStartPos;

	PrevButton->setButtonPos(PrevButtonPos);
	VecButton[static_cast<int>(MapEditorButtonState::Prev)] = PrevButton;

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
	NextButton->setButtonSound(ButtonEventState::Click, "Select.wav", "Resources\\Sounds\\Lobby");

	//ButtonPtr->setButtonSound(ButtonEventState::Click, )

	NextButton->setCallback<MapEditor>(ButtonEventState::Click, this, &MapEditor::ClickNextButton);

	float4 NextButtonPos = SelectView_EndXPos +
		float4{ static_cast<float>(SelectViewSize_X)* GlobalValue::MapTileSize.X - LocalPrevButtonStartPos.X - ButtonRenderScale.X, LocalPrevButtonStartPos.Y };

	NextButton->setButtonPos(NextButtonPos);
	VecButton[static_cast<int>(MapEditorButtonState::Next)] = NextButton;
}

void MapEditor::ClickPrevButton()
{
	SelectTilesMapNum -= 1;
	if (SelectTilesMapNum < 0)
	{
		SelectTilesMapNum = static_cast<int>(TileObjectOrder::MovableBlock);
	}

	ChangeSelectViewInfo(static_cast<TileObjectOrder>(SelectTilesMapNum));
	AllOffSelectVlew();

	switch (SelectTilesMapNum)
	{
	case 0:
		SelectView_Grounds->On();
		break;
	case 1:
		SelectView_Structures->On();
		break;
	case 2:
		SelectView_ImmovableBlocks->On();
		break;
	case 3:
		SelectView_MovableBlocks->On();
		break;
	default:
		break;
	}

	SelectView_SelectedPlace->Off();
	ObjectTextureIndex = 0;
}

void MapEditor::ClickNextButton()
{
	SelectTilesMapNum += 1;
	if (SelectTilesMapNum > static_cast<int>(TileObjectOrder::MovableBlock))
	{
		SelectTilesMapNum = 0;
	}

	ChangeSelectViewInfo(static_cast<TileObjectOrder>(SelectTilesMapNum));
	AllOffSelectVlew();

	switch (SelectTilesMapNum)
	{
	case 0:
		SelectView_Grounds->On();
		break;
	case 1:
		SelectView_Structures->On();
		break;
	case 2:
		SelectView_ImmovableBlocks->On();
		break;
	case 3:
		SelectView_MovableBlocks->On();
		break;
	default:
		break;
	}

	SelectView_SelectedPlace->Off();
	ObjectTextureIndex = 0;
}

void MapEditor::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	CurMousePos = GameEngineWindow::MainWindow.GetMousePos();

	// Mouse In Drawing View 

	if (true == MouseInTileMap(GlobalValue::TileStartPos, GlobalValue::MapTileIndex))
	{
		DrawingVlew_SelectedPlace->On();
		CurTileIndex_X = int(CurMousePos.X - DrawingView_StartPos.X) / 40;
		CurTileIndex_Y = int(CurMousePos.Y - DrawingView_StartPos.Y) / 40;

		DrawingVlew_SelectedPlace->SetPos({
			DrawingView_StartPos.X + (GlobalValue::MapTileSize.X * CurTileIndex_X) + GlobalValue::MapTileSize.hX(),
			DrawingView_StartPos.Y + (GlobalValue::MapTileSize.Y * CurTileIndex_Y) + GlobalValue::MapTileSize.hY() });

		if (true == GameEngineInput::IsPress(VK_LBUTTON))
		{
			DrawingTile();
		}
		else if (true == GameEngineInput::IsPress(VK_RBUTTON))
		{
			DeleteTile();
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
			SelectObject();
		}
	}

	if (true == GameEngineInput::IsPress(VK_CONTROL))
	{
		// Draw All Tile
		if (true == GameEngineInput::IsDown('A'))
		{
			
			if (CurSelectedObjectType == TileObjectOrder::Empty)
			{
				// Ground
				for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
				{
					for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
					{
						DrawingView_Ground->SetTile(X, Y, ObjectTextureIndex, DrawingView_StartPos);

						// 바닥 텍스처 정보 저장
						TileInfo[Y][X].GroundTextureInfo = ObjectTextureIndex;
					}
				}
			}
			else 
			{
				// Object
				for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
				{
					for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
					{
						DrawingView_Object->SetTileToSprite(X, Y, SelectedTextureName, ObjectTextureIndex,
							DrawingView_StartPos - CurObjectOverSize, true);

						// 맵 정보 저장
						if (0 == ObjectTextureIndex)
						{
							TileInfo[Y][X].MapInfo = TileObjectOrder::Empty;
						}
						else
						{
							TileInfo[Y][X].MapInfo = CurSelectedObjectType;
						}

						// 오브젝트 텍스처 정보 저장
						TileInfo[Y][X].ObjectTextureInfo = ObjectTextureIndex;
					}
				}
			}
		}
		else if (true == GameEngineInput::IsDown('C')) 
		{
			// All Clear
			if (CurSelectedObjectType == TileObjectOrder::Empty)
			{
				TileGroundInfoReset();
			}
			else
			{
				TileObjectInfoReset();
			}

			TileSetting();
			//GameEngineWindow::MainWindow.CursorOn();
			//if (1 == MessageBox(GameEngineWindow::MainWindow.GetHWND(), L"타일을 전부 지우시겠습니까?", L"", MB_OKCANCEL))
			//{
			//	TileInfoReset();
			//	TileSetting();
			//}
			//GameEngineWindow::MainWindow.CursorOff();
		}
		else if (true == GameEngineInput::IsDown('O'))
		{
			// Open File
			OpenFileDialog();
		}
		else if (true == GameEngineInput::IsDown('S'))
		{
			// Save File
			SaveFileDialog();
		}
	}

	if (true == GameEngineInput::IsDown(VK_DELETE))
	{
		TileInfoReset();
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
				DrawingView_Ground->SetTile(X, Y, 0, DrawingView_StartPos);
			}
		}
	}

	if (nullptr == DrawingView_Object)
	{
		DrawingView_Object = CreateActor<TileMap>();
		DrawingView_Object->CreateTileMap("Structures.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y,
			GlobalValue::MapTileSize, RenderOrder::MapObject);
	}

	SelectView_Grounds = SelectViewInit(TileObjectOrder::Empty);
	SelectView_Structures = SelectViewInit(TileObjectOrder::Structure);
	SelectView_ImmovableBlocks = SelectViewInit(TileObjectOrder::ImmovableBlock);
	SelectView_MovableBlocks = SelectViewInit(TileObjectOrder::MovableBlock);
}




TileMap* MapEditor::SelectViewInit(TileObjectOrder _SelectedObjectType)
{
	TileMap* Tile = nullptr;
	ChangeSelectViewInfo(_SelectedObjectType);

	if (nullptr == Tile)
	{
		Tile = CreateActor<TileMap>();
		Tile->CreateTileMap(SelectedTextureName, SelectViewSize_X,
			(ObjectSpriteMaxIndex / SelectViewSize_X) + 1, GlobalValue::MapTileSize, RenderOrder::MapObject);
	}

	int IndexCount = 0;
	int YCount = (ObjectSpriteMaxIndex / SelectViewSize_X) + 1;

	for (int Y = 0; Y <= YCount; ++Y)
	{
		for (int X = 0; X < SelectViewSize_X; ++X)
		{
			if (ObjectSpriteMaxIndex < IndexCount)
			{
				return Tile;
			}
			else
			{
				Tile->SetTileToSprite(X, Y, SelectedTextureName, IndexCount, SelectView_StartPos - CurObjectOverSize, true);
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

void MapEditor::DrawingTile()
{
	// Ground와 Object 구분
	if (CurSelectedObjectType == TileObjectOrder::Empty)
	{
		DrawingView_Ground->SetTile(CurTileIndex_X, CurTileIndex_Y, ObjectTextureIndex, DrawingView_StartPos);

		// 바닥 텍스처 정보 저장
		TileInfo[CurTileIndex_Y][CurTileIndex_X].GroundTextureInfo = ObjectTextureIndex;
	}
	else
	{
		DrawingView_Object->SetTileToSprite(CurTileIndex_X, CurTileIndex_Y, SelectedTextureName, ObjectTextureIndex,
			DrawingView_StartPos - CurObjectOverSize, true);

		// 맵 정보 저장
		if (0 == ObjectTextureIndex)
		{
			TileInfo[CurTileIndex_Y][CurTileIndex_X].MapInfo = TileObjectOrder::Empty;
		}
		else
		{
			TileInfo[CurTileIndex_Y][CurTileIndex_X].MapInfo = CurSelectedObjectType;
		}

		// 오브젝트 텍스처 정보 저장
		TileInfo[CurTileIndex_Y][CurTileIndex_X].ObjectTextureInfo = ObjectTextureIndex;
	}
}

void MapEditor::DeleteTile()
{
	// Ground와 Object 구분
	if (CurSelectedObjectType == TileObjectOrder::Empty)
	{
		DrawingView_Ground->SetTile(CurTileIndex_X, CurTileIndex_Y, 0, DrawingView_StartPos);

		// 바닥 텍스처 정보 저장
		TileInfo[CurTileIndex_Y][CurTileIndex_X].GroundTextureInfo = 0;
	}
	else
	{
		DrawingView_Object->SetTileToSprite(CurTileIndex_X, CurTileIndex_Y, SelectedTextureName, 0,
			DrawingView_StartPos - CurObjectOverSize, true);

		// 맵 정보 저장
		TileInfo[CurTileIndex_Y][CurTileIndex_X].MapInfo = TileObjectOrder::Empty;

		// 오브젝트 텍스처 정보 저장
		TileInfo[CurTileIndex_Y][CurTileIndex_X].ObjectTextureInfo = 0;
	}
}

void MapEditor::SelectObject()
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

void MapEditor::TileSetting()
{
	for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
	{
		for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
		{
			DrawingView_Ground->SetTile(X, Y, TileInfo[Y][X].GroundTextureInfo, DrawingView_StartPos);
			switch (TileInfo[Y][X].MapInfo)
			{
			case TileObjectOrder::Empty:
			case TileObjectOrder::Structure:
				DrawingView_Object->SetTileToSprite(X, Y, "Structures.bmp", TileInfo[Y][X].ObjectTextureInfo, DrawingView_StartPos - GlobalValue::StructureOverSize, true);
				break;
			case TileObjectOrder::ImmovableBlock:
				DrawingView_Object->SetTileToSprite(X, Y, "ImmovableBlocks.bmp", TileInfo[Y][X].ObjectTextureInfo, DrawingView_StartPos - GlobalValue::BlockOverSize, true);
				break;
			case TileObjectOrder::MovableBlock:
				DrawingView_Object->SetTileToSprite(X, Y, "MovableBlocks.bmp", TileInfo[Y][X].ObjectTextureInfo, DrawingView_StartPos - GlobalValue::BlockOverSize, true);
				break;
			default:
				break;
			}
		}
	}
}

void MapEditor::TileInfoReset()
{
	for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
	{
		for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
		{
			TileInfo[Y][X] = GameMapInfo::DefaultInfo;
		}
	}
}

void MapEditor::TileGroundInfoReset()
{
	for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
	{
		for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
		{
			TileInfo[Y][X].GroundTextureInfo = 0;
		}
	}
}

void MapEditor::TileObjectInfoReset()
{
	for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
	{
		for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
		{
			TileInfo[Y][X].ObjectTextureInfo = 0;
		}
	}
}

void MapEditor::OpenFileDialog()
{
	TileInfoReset();
	std::string FilePath = "";

	OPENFILENAME OFN;
	TCHAR FilePathName[200] = L"";
	TCHAR lpstrFile[200] = L"";
	static TCHAR filter[] = L"모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = GameEngineWindow::MainWindow.GetHWND();
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 100;
	OFN.lpstrInitialDir = L".";

	GameEngineWindow::MainWindow.CursorOn();
	if (GetOpenFileName(&OFN) != 0)
	{
		wsprintf(FilePathName, L"%s 파일을 열겠습니까?", OFN.lpstrFile);
		FilePath = GameEngineString::UnicodeToAnsi(OFN.lpstrFile);

		// File Open
		FILE* File = nullptr;
		fopen_s(&File, FilePath.c_str(), "rb"); // rb : Read Binary

		// Read Data
		for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
		{
			for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
			{
				fread(&TileInfo[Y][X], sizeof(TileInfo[Y][X]), 1, File);
			}
		}

		// File Close
		fclose(File);

		TileSetting();
	}
	GameEngineWindow::MainWindow.CursorOff();
}

void MapEditor::SaveFileDialog()
{
	std::string FilePath = "";

	OPENFILENAME OFN;
	TCHAR FilePathName[200] = L"";
	TCHAR lpstrFile[200] = L"";
	static TCHAR filter[] = L"모든 파일\0*.*\0텍스트 파일\0*.txt\0fbx 파일\0*.fbx";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = GameEngineWindow::MainWindow.GetHWND();
	OFN.lpstrFilter = filter;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 100;
	OFN.lpstrInitialDir = L".";

	GameEngineWindow::MainWindow.CursorOn();
	if (GetSaveFileName(&OFN) != 0)
	{
		wsprintf(FilePathName, L"%s 파일을 저장하시겠습니까?", OFN.lpstrFile);
		FilePath = GameEngineString::UnicodeToAnsi(OFN.lpstrFile);

		// File Create
		FILE* File = nullptr;
		fopen_s(&File, FilePath.c_str(), "wb"); // wb : Write Binary

		// Write Data
		for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
		{
			for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
			{
				fwrite(&TileInfo[Y][X], sizeof(TileInfo[Y][X]), 1, File);
			}
		}

		// File Close
		fclose(File);
	}
	GameEngineWindow::MainWindow.CursorOff();
}
