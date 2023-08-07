#include "PlayLevel.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/GameEngineCamera.h>


#include "BackGround.h"
#include "Dao.h"
#include "Bazzi.h"
#include "Cappi.h"
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
	Player = CreateActor<Bazzi>(UpdateOrder::Character);
	Player->SetPos(GlobalValue::WinScale.Half());

	AllBubbleIndex.reserve(10);

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

	for (int i = 0; i < AllBubbleIndex.size(); i++)
	{
		GameMapIndex CheckIndex = AllBubbleIndex[i];

		TileInfo[CheckIndex.Y][CheckIndex.X].Timer += _Delta;

		if (TileInfo[CheckIndex.Y][CheckIndex.X].Timer > 3.0f)
		{
			BubbleReset(CheckIndex.X, CheckIndex.Y);
			AllBubbleIndex.erase(AllBubbleIndex.begin() + i);
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

bool PlayLevel::CheckTile(const float4& _Pos)
{
	if (nullptr != Player)
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
				MoveTile(NextTile, CheckX, CheckY);
				return true;
			}

			if (TileObjectOrder::Bubble == TileInfo[CheckY][CheckX].MapInfo)
			{
				return true;
			}

			return false;
		}
	}

	MsgBoxAssert("캐릭터가 nullptr입니다");
	return false;
}

void PlayLevel::MoveTile(GameEngineRenderer* _Renderer, int _X, int _Y)
{
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
		ObjectTile->LerpTile(_Renderer, LerpDir, GlobalValue::TileStartPos + float4(0, -20));
	}
}

void PlayLevel::SetBubble(const float4& _Pos)
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

void PlayLevel::BubbleReset(const int _X, const int _Y)
{
	TileInfo[_Y][_X].Timer = 0.0f;
	TileInfo[_Y][_X].MapInfo = TileObjectOrder::Empty;

	GameEngineRenderer* BubbleRenderer = ObjectTile->GetTile(_X, _Y);

	if (nullptr == BubbleRenderer)
	{
		return;
	}

	BubbleRenderer = ObjectTile->SetTileToSprite(_X, _Y, "EraseTile.Bmp", 0, GlobalValue::TileStartPos, true);
	if (nullptr == BubbleRenderer->FindAnimation("EmptyTile"))
	{
		BubbleRenderer->CreateAnimation("EmptyTile", "EraseTile.Bmp");
	}
	BubbleRenderer->ChangeAnimation("EmptyTile");
}