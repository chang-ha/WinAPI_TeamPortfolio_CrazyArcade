#include "PlayLevel.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>


#include "BackGround.h"
#include "Dao.h"
#include "Bazzi.h"
#include "Kephi.h"
#include "Marid.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "GlobalUtils.h"
#include "GlobalLoad.h"
#include "GameMapInfo.h"
#include "FadeObject.h"
#include "FadeScreen.h"
#include "CommonTexture.h"
#include "PlayTimer.h"
#include "PlayPortrait.h"
#include "GameStartAnimation.h"
#include "PlayResultWindow.h"
#include "GameOverAnimation.h"
#include "Button.h"
#include "Item.h"

PlayLevel* PlayLevel::CurPlayLevel = nullptr;

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CurPlayLevel = this;

	UILevelStart();
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	UILevelEnd();
}

void PlayLevel::Start()
{
	Back = CreateActor<BackGround>(UpdateOrder::Map);
	if (nullptr == Back)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	Back->Init("PlayPanel.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());

	// Object Texture Load
	GlobalLoad::TileTextureLoad();

	// TileInfo Initialize
	TileInfo.assign(GlobalValue::MapTileIndex_Y, (std::vector<GameMapInfo>(GlobalValue::MapTileIndex_X, GameMapInfo::DefaultInfo)));

	// Item Initialize
	Items.assign(GlobalValue::MapTileIndex_Y, (std::vector<Item*>(GlobalValue::MapTileIndex_X, nullptr)));

	// Create Character 
	Player = CreateActor<Dao>(UpdateOrder::Character);
	Player->SetPos(GlobalValue::WinScale.Half());

	GetMainCamera()->SetYSort(RenderOrder::MapObject, true);
}

void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('H'))
	{
		CollisionDebugRenderSwitch();
	}

	if (true == GameOverCheckValue)
	{
		GameOverTime += _Delta;

		if (GameOverTime > GameOverDuration)
		{
			GameOverTime = 0.0f;

			std::string MoveLevel = WinCheckValue ? NextLevelName : "RoomLevel";
			GameEngineCore::ChangeLevel(MoveLevel);
		}
	}

	ContentLevel::Update(_Delta);

	if (-1 != CurrentStage && false == GameOverCheckValue)
	{
		if (nullptr == Player)
		{
			return;
		}

		if ((false == m_PlayTimer->getTimeFlowValue() && true == GameStartCheckValue) || true == Player->GetPlayerDeath())
		{
			WinCheckValue = false;

			StartGameOver();
		}

		if (true == GameEngineInput::IsPress('6'))
		{
			for (int PlayerCount = 0; PlayerCount < GlobalValue::g_ActiveRoomCount; PlayerCount++)
			{
				VecPlayerResult[PlayerCount].PlayerWinValue = true;
			}

			WinCheckValue = true;

			StartGameOver();
		}
	}


	// 물폭탄의 타이머를 위한 for문
	if (AllBubbleIndex.size() > 0)
	{
		std::list<GameMapIndex>::iterator StartIter = AllBubbleIndex.begin();
		std::list<GameMapIndex>::iterator EndIter = AllBubbleIndex.end();

		for (; StartIter != EndIter;)
		{
			GameMapIndex CheckIndex = *StartIter;

			if (TileInfo[CheckIndex.Y][CheckIndex.X].PrevPop == false)
			{
				TileInfo[CheckIndex.Y][CheckIndex.X].Timer += _Delta;
			}

			if (TileInfo[CheckIndex.Y][CheckIndex.X].PrevPop == true)
			{
				AllBubbleIndex.erase(StartIter);
				TileInfo[CheckIndex.Y][CheckIndex.X].PrevPop = false;
				break;
			}
			else if (TileInfo[CheckIndex.Y][CheckIndex.X].Timer > 2.0f)
			{
				BubblePop(CheckIndex.X, CheckIndex.Y);
				AllBubbleIndex.erase(StartIter);
				break;
			}
			else
			{
				++StartIter;
			}
		}
	}

	// 터진 부분의 Effect를 지워주기 위한 for문
	if (AllBubbleDeathIndex.size() > 0)
	{
		std::list<GameMapIndex>::iterator StartIter = AllBubbleDeathIndex.begin();
		std::list<GameMapIndex>::iterator EndIter = AllBubbleDeathIndex.end();

		for (; StartIter != EndIter;)
		{
			GameMapIndex CheckIndex = *StartIter;

			GameEngineRenderer* PopRenderer = ObjectTile->GetTile(CheckIndex.X, CheckIndex.Y);

			if (nullptr == PopRenderer)
			{
				AllBubbleDeathIndex.erase(StartIter);
				break;
			}

			// Pop 애니메이션이 끝난 후 해당 물폭탄 삭제
			if (true == PopRenderer->IsAnimationEnd())
			{
				TileInfo[CheckIndex.Y][CheckIndex.X].MapInfo = TileObjectOrder::Empty;
				TileInfo[CheckIndex.Y][CheckIndex.X].ObjectTextureInfo = 0;
				TileInfo[CheckIndex.Y][CheckIndex.X].BubblePower = 0;

				AllBubbleDeathIndex.erase(StartIter);
				ObjectTile->DeathTile(CheckIndex.X, CheckIndex.Y);
				break;
			}
			else
			{
				++StartIter;
			}
		}
	}

	// Item Debug
	if (true == GameEngineInput::IsDown('I'))
	{
		ItemDebugValue = !ItemDebugValue;
		for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
		{
			for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
			{
				if (nullptr != Items[Y][X])
				{
					if (true == ItemDebugValue)
					{
						if (true == Items[Y][X]->ItemInBlock())
						{
							Items[Y][X]->On();
						}
					}
					else
					{
						if (true == Items[Y][X]->ItemInBlock())
						{
							Items[Y][X]->Off();
						}
					}
				}
			}
		}
	}
}

void PlayLevel::Render(float _Delta)
{

}

void PlayLevel::MapFileLoad(const std::string& _FileName)
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("Resources");
	FilePath.MoveChild("Resources\\TileMap\\" + _FileName);

	
	FILE* File = nullptr;

	fopen_s(&File, FilePath.GetStringPath().c_str(), "rb"); // rb : Read Binary

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
}

void PlayLevel::TileSetting()
{
	// TileInfo에 저장된 정보를 이용하여 타일맵 생성합니다.

	if (nullptr == GroundTile)
	{
		GroundTile = CreateActor<TileMap>();
		if (nullptr == GroundTile)
		{
			MsgBoxAssert("타일을 생성하지 못했습니다.");
			return;
		}

		GroundTile->CreateTileMap("Grounds.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::Map);
	}

	if (nullptr == ObjectTile)
	{

		ObjectTile = CreateActor<TileMap>();
		if (nullptr == ObjectTile)
		{
			MsgBoxAssert("타일을 생성하지 못했습니다.");
			return;
		}

		ObjectTile->CreateTileMap("Structures.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::MapObject);
	}

	for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
	{
		for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
		{
			GroundTile->SetTile(X, Y, TileInfo[Y][X].GroundTextureInfo, GlobalValue::TileStartPos);
			switch (TileInfo[Y][X].MapInfo)
			{
			case TileObjectOrder::Structure:
				ObjectTile->SetTileToSprite(X, Y, "Structures.bmp", TileInfo[Y][X].ObjectTextureInfo, GlobalValue::TileStartPos - GlobalValue::StructureOverSize, true);
				break;
			case TileObjectOrder::ImmovableBlock:
				ObjectTile->SetTileToSprite(X, Y, "ImmovableBlocks.bmp", TileInfo[Y][X].ObjectTextureInfo, GlobalValue::TileStartPos - GlobalValue::BlockOverSize, true);
				break;
			case TileObjectOrder::MovableBlock:
				ObjectTile->SetTileToSprite(X, Y, "MovableBlocks.bmp", TileInfo[Y][X].ObjectTextureInfo, GlobalValue::TileStartPos - GlobalValue::BlockOverSize, true);
				break;
			default:
				break;
			}
		}
	}
}

void PlayLevel::ItemSetting()
{
	for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
	{
		for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
		{
			int TileInfoInt = static_cast<int>(TileInfo[Y][X].MapInfo);

			// ImmovableBlock, MovableBlock일 때 아이템 생성
			if (TileInfoInt == 2 ||
				TileInfoInt == 3)
			{
				int RandomNumber = GameEngineRandom::MainRandom.RandomInt(0, 2); // 33.3% 확률로 아이템 생성
				if (0 == RandomNumber)
				{
					CreateItemInBlock(X, Y);
				}
			}
		}
	}
}

void PlayLevel::CreateItemInBlock(int _X, int _Y)
{
	// < 아이템 번호 >
	// 0 : Bubble
	// 1 : Fluid
	// 2 : Roller
	// 3 : Ultra
	// 4 : Red_Devil
	// 5 : Needle -> 블럭에서 안나옴
	
	int RandomNumber = GameEngineRandom::MainRandom.RandomInt(0, 3); 
	if (RandomNumber == 0)
	{
		// 25% 확률로 Ultra, Red_Devil 중 하나 생성
		RandomNumber = GameEngineRandom::MainRandom.RandomInt(3, 4);
	}
	else
	{
		// 75% 확률로 Bubble, Fluid, Roller 중 하나 생성
		RandomNumber = GameEngineRandom::MainRandom.RandomInt(0, 2);
	}

	ItemActor = CreateActor<Item>(UpdateOrder::Map);
	ItemActor->SetItemTypeInt(RandomNumber);
	ItemActor->SetItemPos(_X, _Y);
	ItemActor->PutIteminBlock();
	Items[_Y][_X] = ItemActor;
	ItemActor = nullptr;
}

void PlayLevel::CreateItemInTile(int _X, int _Y, ItemType _Type)
{
	ItemActor = CreateActor<Item>(UpdateOrder::Map);
	ItemActor->SetItemType(_Type);
	ItemActor->SetItemPos(_X, _Y);
	Items[_Y][_X] = ItemActor;
	ItemActor = nullptr;
}

void PlayLevel::CheckItemInTile(int _X, int _Y)
{
	if (nullptr != Items[_Y][_X])
	{
		Items[_Y][_X]->Death();
		Items[_Y][_X] = nullptr;
	}
}

void PlayLevel::CheckItemInTile(float _X, float _Y)
{
	int X = static_cast<int>(_X);
	int Y = static_cast<int>(_Y);
	if (nullptr != Items[Y][X])
	{
		Items[Y][X]->Death();
		Items[Y][X] = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 캐릭터
bool PlayLevel::CheckTile(const float4& _Pos, float _Delta)
{
	float4 CheckPos = { _Pos.X, _Pos.Y };
	CheckPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
	float4 CheckIndex = ObjectTile->PosToIndex(CheckPos);

	int CheckX = CheckIndex.iX() - 1;
	int CheckY = CheckIndex.iY() - 1;

	GameEngineRenderer* NextTile = ObjectTile->GetTile(CheckX, CheckY);

	// LerpTimer 기능 수정 필요
	static GameMapInfo* PrevTile = nullptr;

	if (true == ObjectTile->IsOver(CheckX, CheckY))
	{
		return true;
	}
	else
	{
		GameMapInfo& CurTile = TileInfo[CheckY][CheckX];

		if (nullptr == PrevTile)
		{
			PrevTile = &CurTile;
		}
		else
		{
			if (PrevTile != &CurTile)
			{
				PrevTile->LerpTimer = 0.0f;
				PrevTile = &CurTile;
			}
		}

		if (TileObjectOrder::Empty == TileInfo[CheckY][CheckX].MapInfo
			|| TileObjectOrder::PopRange == TileInfo[CheckY][CheckX].MapInfo)
		{
			return false;
		}

		if (TileObjectOrder::Structure == TileInfo[CheckY][CheckX].MapInfo)
		{
			return true;
		}

		if (TileObjectOrder::ImmovableBlock == TileInfo[CheckY][CheckX].MapInfo)
		{
			return true;
		}

		if (TileObjectOrder::MovableBlock == TileInfo[CheckY][CheckX].MapInfo)
		{
			TileInfo[CheckY][CheckX].LerpTimer += _Delta;

			if (LerpTime < TileInfo[CheckY][CheckX].LerpTimer)
			{
				MoveTile(NextTile, CheckX, CheckY);
				return false;
			}
			return true;
		}

		if (TileObjectOrder::Bubble == TileInfo[CheckY][CheckX].MapInfo)
		{
			float4 CheckPos = Player->GetPos();
			CheckPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
			float4 CheckIndex = ObjectTile->PosToIndex(CheckPos);

			int PlayerX = CheckIndex.iX() - 1;
			int PlayerY = CheckIndex.iY() - 1;

			if (TileObjectOrder::Bubble == TileInfo[PlayerY][PlayerX].MapInfo)
			{
				return false;
			}
			return true;
		}

		return false;
	}	
}

bool PlayLevel::CheckSidePos(const float4& _Pos)
{
	float4 CheckPos = { _Pos.X, _Pos.Y };
	CheckPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
	float4 CheckIndex = ObjectTile->PosToIndex(CheckPos);

	int CheckX = CheckIndex.iX() - 1;
	int CheckY = CheckIndex.iY() - 1;

	GameEngineRenderer* NextTile = ObjectTile->GetTile(CheckX, CheckY);

	if (true == ObjectTile->IsOver(CheckX, CheckY))
	{
		return true;
	}
	else
	{
		if (TileObjectOrder::Empty == TileInfo[CheckY][CheckX].MapInfo
			|| TileObjectOrder::PopRange == TileInfo[CheckY][CheckX].MapInfo)
		{
			return false;
		}

		if (TileObjectOrder::Bubble == TileInfo[CheckY][CheckX].MapInfo)
		{
			float4 CheckPos = Player->GetPos();
			CheckPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
			float4 CheckIndex = ObjectTile->PosToIndex(CheckPos);

			int PlayerX = CheckIndex.iX() - 1;
			int PlayerY = CheckIndex.iY() - 1;

			if (TileObjectOrder::Bubble == TileInfo[PlayerY][PlayerX].MapInfo)
			{
				return false;
			}
			return true;
		}

		return true;
	}
}

void PlayLevel::MoveTile(GameEngineRenderer* _Renderer, int _X, int _Y)
{
	static bool MoveCheck = false;

	ActorDir PlayerDir = Player->GetDir();
	MOVEDIR LerpDir = MOVEDIR::NONE;
	float4 ItemMoveDir = float4::ZERO;
	int NewX = _X;
	int NewY = _Y;

	switch (PlayerDir)
	{
	case ActorDir::Left:
		LerpDir = MOVEDIR::LEFT;
		ItemMoveDir = float4::LEFT;
		--NewX;
		break;
	case ActorDir::Right:
		LerpDir = MOVEDIR::RIGHT;
		ItemMoveDir = float4::RIGHT;
		++NewX;
		break;
	case ActorDir::Up:
		LerpDir = MOVEDIR::UP;
		ItemMoveDir = float4::UP;
		--NewY;
		break;
	case ActorDir::Down:
		LerpDir = MOVEDIR::DOWN;
		ItemMoveDir = float4::DOWN;
		++NewY;
		break;
	default:
		break;
	}

	if (nullptr != _Renderer)
	{
		if (true == ObjectTile->IsOver(NewX, NewY))
		{
			return;
		}

		if (TileObjectOrder::Empty != TileInfo[NewY][NewX].MapInfo)
		{
			return;
		}

		// TileInfo 수정
		GameMapInfo Temp = TileInfo[_Y][_X];
		TileInfo[_Y][_X] = TileInfo[NewY][NewX];
		TileInfo[NewY][NewX] = Temp;

		//MoveCheck = ObjectTile->LerpTile(_Renderer, LerpDir, GlobalValue::MapTileSize - GlobalValue::TileStartPos);
		MoveCheck = ObjectTile->LerpTile(_Renderer, LerpDir, GlobalValue::TileStartPos + float4(0, -20));
		TileInfo[NewY][NewX].LerpTimer = 0.0f;

		// Item 수정
		CheckItemInTile(NewX, NewY);
		if (nullptr != Items[_Y][_X])
		{
			Items[NewY][NewX] = Items[_Y][_X];
			Items[NewY][NewX]->AddPos(GlobalValue::MapTileSize * ItemMoveDir);
			Items[_Y][_X] = nullptr;
		}
	}
}

TileObjectOrder PlayLevel::GetCurTileType(const float4& _Pos)
{
	float4 CharacterPos = _Pos;
	CharacterPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
	float4 ChangeIndex = ObjectTile->PosToIndex(CharacterPos);

	int CurIndexX = ChangeIndex.iX() - 1;
	int CurIndexY = ChangeIndex.iY() - 1;

	if (true == GroundTile->IsOver(CurIndexX, CurIndexY))
	{
		if (CurIndexX < 0)
		{
			CurIndexX = 0;
		}
		if(CurIndexX >= GlobalValue::MapTileIndex_X)
		{
			CurIndexX = GlobalValue::MapTileIndex_X - 1;
		}

		if (CurIndexY < 0)
		{
			CurIndexY = 0;
		}
		if (CurIndexY >= GlobalValue::MapTileIndex_Y)
		{
			CurIndexY = GlobalValue::MapTileIndex_Y - 1;
		}
	}

	GameMapInfo Temp = TileInfo[CurIndexY][CurIndexX];

	TileObjectOrder Result = Temp.MapInfo;
	return Result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 물폭탄
void PlayLevel::SetBubble(const float4& _Pos, int _BubblePower)
{
	if (nullptr != Player)
	{
		float4 CharacterPos = _Pos;
		CharacterPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
		float4 ChangeIndex = ObjectTile->PosToIndex(CharacterPos);

		int BubbleIndexX = ChangeIndex.iX() - 1;
		int BubbleIndexY = ChangeIndex.iY() - 1;

		GameEngineRenderer* BubbleRenderer = ObjectTile->GetTile(BubbleIndexX, BubbleIndexY);

		if (TileObjectOrder::Empty != TileInfo[BubbleIndexY][BubbleIndexX].MapInfo)
		{
			return;
		}

		Player->BombCountMinus();

		AllBubbleIndex.push_back({ BubbleIndexX, BubbleIndexY });

		TileInfo[BubbleIndexY][BubbleIndexX].MapInfo = TileObjectOrder::Bubble;
		TileInfo[BubbleIndexY][BubbleIndexX].BubblePower = _BubblePower;

		BubbleRenderer = ObjectTile->SetTileToSprite(BubbleIndexX, BubbleIndexY, "Bubble.bmp",
			TileInfo[BubbleIndexY][BubbleIndexX].ObjectTextureInfo, GlobalValue::TileStartPos, true);

		if (nullptr == BubbleRenderer->FindAnimation("Bubble_Idle"))
		{
			BubbleRenderer->CreateAnimation("Bubble_Idle", "Bubble.bmp", 0, 2, 0.2f, true);
		}
		BubbleRenderer->ChangeAnimation("Bubble_Idle");

		return;
	}

	MsgBoxAssert("Player가 nullptr입니다");
	return;
}

void PlayLevel::BubblePop(const int _X, const int _Y)
{
	Player->BombCountPlus();
	int BubblePower = TileInfo[_Y][_X].BubblePower;
	TileInfo[_Y][_X].Timer = 0.0f;
	TileInfo[_Y][_X].MapInfo = TileObjectOrder::PopRange;

	GameEngineRenderer* BubbleRenderer = ObjectTile->GetTile(_X, _Y);

	if (nullptr == BubbleRenderer)
	{
		return;
	}

	if (nullptr == BubbleRenderer->FindAnimation("Bubble_Pop"))
	{
		BubbleRenderer->CreateAnimation("Bubble_Pop", "Pop.bmp", 0, 5, 0.1f, false);
	}
	BubbleRenderer->ChangeAnimation("Bubble_Pop");

	AllBubbleDeathIndex.push_back({ _X, _Y });

	// 왼쪽 타일--------------------------------------------------------------
	for (int i = 1; i <= BubblePower; i++)
	{
		int X = _X - i;
		int Y = _Y;

		if (true == ObjectTile->IsOver(X, Y))
		{
			break;
		}

		if (TileObjectOrder::ImmovableBlock == TileInfo[Y][X].MapInfo
			|| TileObjectOrder::MovableBlock == TileInfo[Y][X].MapInfo)
		{
			PopTile(X, Y);
			break;
		}
		else if (TileObjectOrder::Structure == TileInfo[Y][X].MapInfo
			|| TileObjectOrder::PopRange == TileInfo[Y][X].MapInfo)
		{
			break;
		}
		else if (i == BubblePower)
		{
			SideBubblePop(X, Y, "Left_1.Bmp", "Bubble_Pop_Left", 0.05f);
		}
		else
		{
			SideBubblePop(X, Y, "Left_2.Bmp", "Bubble_Pop_Left_Middle", 0.05f);
		}

		CheckItemInTile(X, Y);
	}

	//오른쪽 타일--------------------------------------------------------------
	for (int i = 1; i <= BubblePower; i++)
	{
		int X = _X + i;
		int Y = _Y;

		if (true == ObjectTile->IsOver(X, Y))
		{
			break;
		}

		if (TileObjectOrder::ImmovableBlock == TileInfo[Y][X].MapInfo
			|| TileObjectOrder::MovableBlock == TileInfo[Y][X].MapInfo)
		{
			PopTile(X, Y);
			break;
		}
		else if (TileObjectOrder::Structure == TileInfo[Y][X].MapInfo
			|| TileObjectOrder::PopRange == TileInfo[Y][X].MapInfo)
		{
			break;
		}
		else if (i == BubblePower)
		{
			SideBubblePop(X, Y, "Right_1.Bmp", "Bubble_Pop_Right", 0.05f);
		}
		else
		{
			SideBubblePop(X, Y, "Right_2.Bmp", "Bubble_Pop_Right_Middle", 0.05f);
		}

		CheckItemInTile(X, Y);
	}

	//위쪽 타일--------------------------------------------------------------
	for (int i = 1; i <= BubblePower; i++)
	{
		int X = _X;
		int Y = _Y - i;

		if (true == ObjectTile->IsOver(X, Y))
		{
			break;
		}

		if (TileObjectOrder::ImmovableBlock == TileInfo[Y][X].MapInfo
			|| TileObjectOrder::MovableBlock == TileInfo[Y][X].MapInfo)
		{
			PopTile(X, Y);
			break;
		}
		else if (TileObjectOrder::Structure == TileInfo[Y][X].MapInfo
			|| TileObjectOrder::PopRange == TileInfo[Y][X].MapInfo)
		{
			break;
		}
		else if (i == BubblePower)
		{
			SideBubblePop(X, Y, "Up_1.Bmp", "Bubble_Pop_Up", 0.05f);
		}
		else
		{
			SideBubblePop(X, Y, "Up_2.Bmp", "Bubble_Pop_Up_Middle", 0.05f);
		}

		CheckItemInTile(X, Y);
	}

	//아래쪽 타일--------------------------------------------------------------
	for (int i = 1; i <= BubblePower; i++)
	{
		int X = _X;
		int Y = _Y + i;

		if (true == ObjectTile->IsOver(X, Y))
		{
			break;
		}

		if (TileObjectOrder::ImmovableBlock == TileInfo[Y][X].MapInfo
			|| TileObjectOrder::MovableBlock == TileInfo[Y][X].MapInfo)
		{
			PopTile(X, Y);
			break;
		}
		else if (TileObjectOrder::Structure == TileInfo[Y][X].MapInfo
			|| TileObjectOrder::PopRange == TileInfo[Y][X].MapInfo)
		{
			break;
		}
		else if (i == BubblePower)
		{
			SideBubblePop(X, Y, "Down_1.Bmp", "Bubble_Pop_Down", 0.05f);
		}
		else
		{
			SideBubblePop(X, Y, "Down_2.Bmp", "Bubble_Pop_Down_Middle", 0.05f);
		}

		CheckItemInTile(X, Y);
	}
}

void PlayLevel::SideBubblePop(const int _X, const int _Y, const std::string& _SpriteName, const std::string& _AnimationName, float _Inter)
{
	int DownIndexX = _X;
	int DownIndexY = _Y;

	if (false == ObjectTile->IsOver(DownIndexX, DownIndexY))
	{
		if (TileInfo[DownIndexY][DownIndexX].MapInfo == TileObjectOrder::Bubble)
		{
			BubblePop(DownIndexX, DownIndexY);
			TileInfo[DownIndexY][DownIndexX].PrevPop = true;
		}
		else
		{
			TileChange(DownIndexX, DownIndexY, _SpriteName, _AnimationName, _Inter);
		}
	}
}

// 블록이 물풍선에 맞을 경우 터지는 함수
void PlayLevel::PopTile(const int _X, const int _Y)
{
	GameEngineRenderer* TileRenderer = ObjectTile->GetTile(_X, _Y);

	if (nullptr == TileRenderer->FindAnimation("Pop_Tile"))
	{
		TileRenderer->CreateAnimation("Pop_Tile", "Pop_Tile.Bmp", 0, 3, 0.1f, false);
	}

	TileInfo[_Y][_X].MapInfo = TileObjectOrder::Empty;

	TileRenderer->ChangeAnimation("Pop_Tile");

	AllBubbleDeathIndex.push_back({ _X, _Y });
	
	if (nullptr != Items[_Y][_X])
	{
		Items[_Y][_X]->OutItemInBlock();
	}
}

// 물풍선 상하좌우 타일 변경 함수
void PlayLevel::TileChange(const int _X, const int _Y, const std::string& _SpriteName, const std::string& _AnimationName, float _Inter)
{
	if (TileObjectOrder::Empty != TileInfo[_Y][_X].MapInfo)
	{
		return;
	}

	GameEngineRenderer* TileRenderer = ObjectTile->GetTile(_X, _Y);

	TileInfo[_Y][_X].MapInfo = TileObjectOrder::PopRange;

	TileRenderer = ObjectTile->SetTileToSprite(_X, _Y, _SpriteName,
		TileInfo[_Y][_X].ObjectTextureInfo, GlobalValue::TileStartPos, true);

	if (nullptr == TileRenderer->FindAnimation(_AnimationName))
	{
		TileRenderer->CreateAnimation(_AnimationName, _SpriteName, -1, -1, _Inter, false);
	}
	TileRenderer->ChangeAnimation(_AnimationName);

	AllBubbleDeathIndex.push_back({ _X, _Y });
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */
// UI


void PlayLevel::UILevelStart()
{
	FadeObject::CallFadeIn(this, GlobalValue::g_ChangeLevelFadeSpeed);

	if (-1 != CurrentStage)
	{
		CreateGameStartAnimation();
		CreatePortrait();
		CreateGameResult();
	}

	if (m_FadeScreen)
	{
		m_FadeScreen->On();
	}

	if (m_PlayTimer)
	{
		m_PlayTimer->setTimer(CONST_TimeSetting);
		m_PlayTimer->stopTimer();
	}
}

void PlayLevel::CreateGameStartAnimation()
{
	GameStartAnimation* GameStartAnimationPtr = CreateActor<GameStartAnimation>(UpdateOrder::UI);
	if (nullptr == GameStartAnimationPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	GameStartAnimationPtr->initStartAnimation(CurrentStage);
	GameStartAnimationPtr->setGameStartCallBack(this, &PlayLevel::setGameStartCallBack);
}

void PlayLevel::setGameStartCallBack()
{
	if (m_FadeScreen)
	{
		m_FadeScreen->Off();
	}

	if (m_PlayTimer)
	{
		m_PlayTimer->flowTimer();
	}

	GameStartCheckValue = true;
}

void PlayLevel::CreatePortrait()
{
	vec_PlayPortrait.resize(static_cast<int>(GlobalValue::g_ActiveRoomCount));

	for (int RoomCount = 0; RoomCount < GlobalValue::g_ActiveRoomCount; RoomCount++)
	{
		PlayPortrait* PlayPortraitPtr = CreateActor<PlayPortrait>(UpdateOrder::UI);
		if (nullptr == PlayPortraitPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		float4 PortraitPos = CONST_PlayPortraitStartPos + float4::DOWN +
			float4{ CONST_PlayPortraitNextPos.X , CONST_PlayPortraitNextPos.Y * static_cast<float>(RoomCount) };

		PlayPortraitPtr->SetPos(PortraitPos);
		PlayPortraitPtr->CreatePlayPortrait(RoomCount);

		vec_PlayPortrait[RoomCount] = PlayPortraitPtr;
	}
}

void PlayLevel::CreateGameResult()
{
	SetUpResultWindow();
}

void PlayLevel::SetUpResultWindow()
{
	m_ResultWindow = CreateActor<PlayResultWindow>(UpdateOrder::UI);
	if (nullptr == m_ResultWindow)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_ResultWindow->SetPos(CONST_ResultWindowStartPos);
	m_ResultWindow->initResultWindow();

	VecPlayerResult.resize(GlobalValue::g_ActiveRoomCount);
}

void PlayLevel::SetUpResultBoardAnimation()
{
	GameOverAnimation* GameOverAnimationPtr = CreateActor<GameOverAnimation>(UpdateOrder::UI);
	if (nullptr == GameOverAnimationPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	GameOverAnimationPtr->initStageResultAnimation(CurrentStage, WinCheckValue);
}


void PlayLevel::CreateUIElements()
{
	if (CurrentStage < 1 || CurrentStage > 3)
	{
		MsgBoxAssert("CurrentStage로 스테이지 UI를 만들 수 없습니다.");
		return;
	}

	SetUpUIStart();
}

void PlayLevel::SetUpUIStart()
{
	SetUpStageInfo();
	SetUpFadeScreen();
	SetUpTimer();
	SetGoBackButton();
}

void PlayLevel::SetUpStageInfo()
{
	m_StageInfo = CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_StageInfo)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_StageInfo->loadTexture("PenguinLevelStageInfo.bmp", "Resources\\Textures\\UI\\PlayStage");
	m_StageInfo->setTexture("PenguinLevelStageInfo.bmp");
	m_StageInfo->setRendererCopyAndRenderScale(0, 2);

	float4 StageInfoScale = m_StageInfo->getScale();
	float4 StageInfoRenderPos = float4{ 0.0f , StageInfoScale.Y * static_cast<float>(CurrentStage - 1) };
	m_StageInfo->setRendererCopyPos(0, CurrentStage - 1);

	float4 StageRenderPos = CONST_StageInfoStartPos + StageInfoScale.Half();
	m_StageInfo->SetPos(StageRenderPos);
}

void PlayLevel::SetUpFadeScreen()
{
	m_FadeScreen = CreateActor<FadeScreen>(UpdateOrder::UI);
	if (nullptr == m_FadeScreen)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	float4 WinScale = GlobalValue::WinScale;

	m_FadeScreen->setRenderScale(WinScale);
	m_FadeScreen->setAlpha(GlobalValue::g_FadeScreenAlphaValue);
	m_FadeScreen->SetPos(WinScale.Half());
	m_FadeScreen->Off();
}

void PlayLevel::SetUpTimer()
{
	m_PlayTimer = CreateActor<PlayTimer>(UpdateOrder::UI);
	if (nullptr == m_PlayTimer)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_PlayTimer->SetPos(CONST_TimerLocation);
}

void PlayLevel::SetGoBackButton()
{
	m_GoBackButton = CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == m_GoBackButton)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_GoBackButton->setRenderer(RenderOrder::FirstElementUI);
	m_GoBackButton->setButtonTexture(ButtonState::Normal, "Play_Button_Exit_Normal.bmp", "Resources\\Textures\\UI\\PlayStage", 1, 1);
	m_GoBackButton->setButtonTexture(ButtonState::Hover, "Play_Button_Exit_Hover.bmp", "Resources\\Textures\\UI\\PlayStage", 1, 2);
	m_GoBackButton->setButtonTexture(ButtonState::Click, "Play_Button_Exit_Click.bmp", "Resources\\Textures\\UI\\PlayStage", 1, 1);
	m_GoBackButton->setCallback<PlayLevel>(ButtonEventState::Click, this, &PlayLevel::clickGoBackButton);

	float4 ButtonScale = m_GoBackButton->getButtonScale();
	float4 ButtonPos = CONST_GoBackButtonStartPos + ButtonScale.Half();

	m_GoBackButton->SetPos(ButtonPos);
}

void PlayLevel::clickGoBackButton()
{
	FadeObject::CallFadeOut(this, "RoomLevel", GlobalValue::g_ChangeLevelFadeSpeed);
}


void PlayLevel::StartGameOver()
{
	if (nullptr == m_ResultWindow)
	{
		MsgBoxAssert("액터를 생성하지 않았습니다.");
		return;
	}

	m_ResultWindow->OnResultWindow(VecPlayerResult);

	SetUpResultBoardAnimation();

	GameOverCheckValue = true;
}


void PlayLevel::UILevelEnd()
{
	if (-1 != CurrentStage)
	{
		ReleaseLevelComposition();
		ReleaseResultWindow();
	}

	if (Player)
	{
		Player->Death();
		Player = nullptr;
	}

	GameOverCheckValue = false;
	GameStartCheckValue = false;
}

void PlayLevel::ReleaseLevelComposition()
{
	for (int VecCount = 0; VecCount < vec_PlayPortrait.size(); VecCount++)
	{
		PlayPortrait* PlayPortraitPtr = vec_PlayPortrait[VecCount];
		if (PlayPortraitPtr)
		{
			PlayPortraitPtr->ActorRelease();
		}
	}

	vec_PlayPortrait.clear();
}

void PlayLevel::ReleaseResultWindow()
{
	if (m_ResultWindow)
	{
		m_ResultWindow->ActorRelease();
		m_ResultWindow = nullptr;
	}

}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 몬스터
bool PlayLevel::MonsterCheckTile(const float4& _Pos, float _Delta)
{
	float4 CheckPos = { _Pos.X, _Pos.Y };
	CheckPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
	float4 CheckIndex = ObjectTile->PosToIndex(CheckPos);

	int CheckX = CheckIndex.iX() - 1;
	int CheckY = CheckIndex.iY() - 1;

	GameEngineRenderer* NextTile = ObjectTile->GetTile(CheckX, CheckY);

	if (true == ObjectTile->IsOver(CheckX, CheckY))
	{
		return true;
	}
	else
	{
		if (TileObjectOrder::Empty == TileInfo[CheckY][CheckX].MapInfo)
		{
			return false;
		}

		if (TileObjectOrder::Structure == TileInfo[CheckY][CheckX].MapInfo)
		{
			return true;
		}

		if (TileObjectOrder::ImmovableBlock == TileInfo[CheckY][CheckX].MapInfo)
		{
			return true;
		}

		if (TileObjectOrder::MovableBlock == TileInfo[CheckY][CheckX].MapInfo)
		{
			return true;
		}

		if (TileObjectOrder::Bubble == TileInfo[CheckY][CheckX].MapInfo)
		{
			return true;
		}

		return false;
	}
}
