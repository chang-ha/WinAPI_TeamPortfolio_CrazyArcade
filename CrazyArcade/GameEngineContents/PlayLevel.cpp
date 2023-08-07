﻿#include "PlayLevel.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/GameEngineCamera.h>


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
#include "PlayTimer.h"

PlayLevel* PlayLevel::CurPlayLevel = nullptr;

PlayLevel::PlayLevel()
{
	CurPlayLevel = this;
}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

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

	// Create Character 
	Player = CreateActor<Dao>(UpdateOrder::Character);
	Player->SetPos(GlobalValue::WinScale.Half());

	GetMainCamera()->SetYSort(RenderOrder::MapObject, true);

	PlayTimerPtr = CreateActor<PlayTimer>(UpdateOrder::UI);
	if (nullptr == PlayTimerPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	PlayTimerPtr->SetPos(float4{ 711.0f , 78.0f });
	PlayTimerPtr->setTimer(66.0f);
	PlayTimerPtr->flowTimer();
}

void PlayLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

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
				continue;
			}

			// Pop 애니메이션이 끝난 후 해당 물폭탄 삭제
			if (true == PopRenderer->IsAnimationEnd())
			{
				TileInfo[CheckIndex.Y][CheckIndex.X].MapInfo = TileObjectOrder::Empty;
				TileInfo[CheckIndex.Y][CheckIndex.X].ObjectTextureInfo = 0;
				TileInfo[CheckIndex.Y][CheckIndex.X].BubblePower = 0;

				ObjectTile->DeathTile(CheckIndex.X, CheckIndex.Y);

				AllBubbleDeathIndex.erase(StartIter);
				break;
			}
			else
			{
				++StartIter;
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
			case TileObjectOrder::Item:
				break;
			default:
				break;
			}
		}
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 캐릭터 이동
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
		if (TileObjectOrder::Empty == TileInfo[CheckY][CheckX].MapInfo)
		{
			return false;
		}

		return true;
	}
}

void PlayLevel::MoveTile(GameEngineRenderer* _Renderer, int _X, int _Y)
{
	static bool MoveCheck = false;

	ActorDir PlayerDir = Player->GetDir();
	MOVEDIR LerpDir = MOVEDIR::NONE;

	int NewX = _X;
	int NewY = _Y;

	switch (PlayerDir)
	{
	case ActorDir::Left:
		LerpDir = MOVEDIR::LEFT;
		--NewX;
		break;
	case ActorDir::Right:
		LerpDir = MOVEDIR::RIGHT;
		++NewX;
		break;
	case ActorDir::Up:
		LerpDir = MOVEDIR::UP;
		--NewY;
		break;
	case ActorDir::Down:
		LerpDir = MOVEDIR::DOWN;
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


		GameMapInfo Temp = TileInfo[_Y][_X];
		TileInfo[_Y][_X] = TileInfo[NewY][NewX];
		TileInfo[NewY][NewX] = Temp;
		MoveCheck = ObjectTile->LerpTile(_Renderer, LerpDir, GlobalValue::TileStartPos + float4(0, -20));
		TileInfo[NewY][NewX].LerpTimer = 0.0f;
	}
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

	BubbleRenderer = ObjectTile->SetTileToSprite(_X, _Y, "Pop.bmp",
		TileInfo[_Y][_X].ObjectTextureInfo, GlobalValue::TileStartPos, true);

	if (nullptr == BubbleRenderer->FindAnimation("Bubble_Pop"))
	{
		BubbleRenderer->CreateAnimation("Bubble_Pop", "Pop.bmp", 0, 5, 0.1f, false);
	}
	BubbleRenderer->ChangeAnimation("Bubble_Pop");

	// 터진 후 사라져야하는 물폭탄 인덱스 저장
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
		else if (i == BubblePower)
		{
			SideBubblePop(X, Y, "Left_1.Bmp", "Bubble_Pop_Left", 0.05f);
		}
		else
		{
			SideBubblePop(X, Y, "Left_2.Bmp", "Bubble_Pop_Left_Middle", 0.05f);
		}
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
		else if (i == BubblePower)
		{
			SideBubblePop(X, Y, "Right_1.Bmp", "Bubble_Pop_Right", 0.05f);
		}
		else
		{
			SideBubblePop(X, Y, "Right_2.Bmp", "Bubble_Pop_Right_Middle", 0.05f);
		}
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
		else if (i == BubblePower)
		{
			SideBubblePop(X, Y, "Up_1.Bmp", "Bubble_Pop_Up", 0.05f);
		}
		else
		{
			SideBubblePop(X, Y, "Up_2.Bmp", "Bubble_Pop_Up_Middle", 0.05f);
		}
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
		else if (i == BubblePower)
		{
			SideBubblePop(X, Y, "Down_1.Bmp", "Bubble_Pop_Down", 0.05f);
		}
		else
		{
			SideBubblePop(X, Y, "Down_2.Bmp", "Bubble_Pop_Down_Middle", 0.05f);
		}
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

	TileRenderer = ObjectTile->SetTileToSprite(_X, _Y, "Pop_Tile.Bmp",
		TileInfo[_Y][_X].ObjectTextureInfo, GlobalValue::TileStartPos, true);

	if (nullptr == TileRenderer->FindAnimation("Pop_Tile"))
	{
		TileRenderer->CreateAnimation("Pop_Tile", "Pop_Tile.Bmp", -1, -1, 0.1f, false);
	}
	TileRenderer->ChangeAnimation("Pop_Tile");

	AllBubbleDeathIndex.push_back({ _X, _Y });
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

	// 터진 후 사라져야하는 물폭탄 인덱스 저장
	AllBubbleDeathIndex.push_back({ _X, _Y });
}