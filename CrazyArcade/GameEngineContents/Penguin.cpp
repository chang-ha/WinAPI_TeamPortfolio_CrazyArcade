#define ANIMATION_SPEED 0.15f

#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/TileMap.h>

#include "Penguin.h"
#include "GlobalUtils.h"
#include "ActorEnum.h"
#include "ContentsEnum.h"
#include "PlayLevel.h"
#include "GameMapInfo.h"

// Debug
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
Penguin::Penguin()
{
}

Penguin::~Penguin()
{
}

void Penguin::Start()
{
	CurPlayLevel = dynamic_cast<PlayLevel*>(GetLevel());
	if (nullptr == CurPlayLevel)
	{
		MsgBoxAssert("PlayLevel이 아닌 곳에 보스몬스터를 생성할 수 없습니다.");
		return;
	}

	MainRenderer = CreateRenderer(RenderOrder::SelectTile);

	if (nullptr == ResourcesManager::GetInst().FindSprite("Penguin.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Monster\\Boss\\");

		ResourcesManager::GetInst().CreateSpriteSheet("Down_Idle", FilePath.PlusFilePath("Idle_Penguin.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Hitten", FilePath.PlusFilePath("Hitten_Penguin.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Summon_Penguin", FilePath.PlusFilePath("Summon_Penguin.bmp"), 20, 1);
	}

	MainRenderer->CreateAnimation("Down_Idle", "Down_Idle", 0, 8, ANIMATION_SPEED, true);
	MainRenderer->FindAnimation("Down_Idle")->Inters[8] = 5.0f;
	MainRenderer->ChangeAnimation("Down_Idle");

	MainRenderer->CreateAnimation("Down_Hitten", "Down_Hitten", 0, 4, ANIMATION_SPEED, true);

	MainRenderer->CreateAnimation("Summon", "Summon_Penguin", 0, 19, ANIMATION_SPEED, true);
	MainRenderer->ChangeAnimation("Down_Idle");
	MainRenderer->SetRenderPos({0, -70});

	// BossTile Vector resize
	BossTile.resize(2);
	for (int Y = 0; Y < BossTile.size(); Y++)
	{
		BossTile[Y].resize(3);
	}
}

void Penguin::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('J'))
	{
		IsDebugMode = !IsDebugMode;
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		ChangeState(MonsterState::Summon);
	}

	// BossTile Update
	CurLevelTile = CurPlayLevel->GetGroundTile();
	float4 CurPos = GetPos() - GlobalValue::TileStartPos;
	float4 Index = CurLevelTile->PosToIndex(CurPos);

	for (int Y = 0; Y < BossTile.size(); Y++)
	{
		for (int X = 0; X < BossTile[Y].size(); X++)
		{
			float4 Value;
			Value.X = static_cast<float>(Index.iX() + X - 1);
			Value.Y = static_cast<float>(Index.iY() + Y);
			BossTile[Y][X] = Value;
		}
	}

	for (int Y = 0; Y < BossTile.size(); Y++)
	{
		for (int X = 0; X < BossTile[Y].size(); X++)
		{
			int Index_X = BossTile[Y][X].iX();
			int Index_Y = BossTile[Y][X].iY();
			if (CurPlayLevel->TileInfo[Index_Y][Index_X].MapInfo == TileObjectOrder::Bubble)
			{
				CurPlayLevel->BubblePop(Index_X , Index_Y);
			}
		}
	}

	HitJudgement();

	// State Update
	StateUpdate(_Delta);
}

void Penguin::Render(float _Delta)
{
	if (false == IsDebugMode)
	{
		return;
	}

	// Debug
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	CollisionData Data;
	Data.Scale = { 40, 40 };
	for (int Y = 0; Y < BossTile.size(); Y++)
	{
		for (int X = 0; X < BossTile[Y].size(); X++)
		{
			Data.Pos = CurLevelTile->IndexToPos(BossTile[Y][X].iX() + 1, BossTile[Y][X].iY() + 2) + GlobalValue::MapTileSize.Half() - GlobalValue::TileStartPos;
			Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
		}
	}
}


void Penguin::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
	case MonsterState::Die:
		return DieUpdate(_Delta);
	case MonsterState::Hitten:
		return HittenUpdate(_Delta);
	case MonsterState::Summon:
		return SummonUpdate(_Delta);
	default:
		break;
	}
}

void Penguin::ChangeState(MonsterState _State)
{
	switch (_State)
	{
	case MonsterState::Idle:
		IdleStart();
		break;
	case MonsterState::Die:
		DieStart();
		break;
	case MonsterState::Hitten:
		HittenStart();
		break;
	case MonsterState::Summon:
		SummonStart();
		break;
	default:
		break;
	}

	State = _State;
}

void Penguin::IdleStart()
{
	MainRenderer->ChangeAnimation("Down_Idle");
}

void Penguin::IdleUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MonsterState::Summon);
	}
}

void Penguin::DieStart()
{

}

void Penguin::DieUpdate(float _Delta)
{
	ChangeState(MonsterState::Idle);
}

void Penguin::HitJudgement()
{
	if (true == IsHitten)
	{
		return;
	}

	for (int Y = 0; Y < BossTile.size(); Y++)
	{
		for (int X = 0; X < BossTile[Y].size(); X++)
		{
			TileObjectOrder CurTile = PlayLevel::CurPlayLevel->GetCurTileType(CurLevelTile->IndexToPos(BossTile[Y][X].iX(), BossTile[Y][X].iY()));
			if (CurTile == TileObjectOrder::PopRange)
			{
				--BossHP;
				IsHitten = true;
				if (0 == BossHP)
				{
					// ChangeState(MonsterState::Die);
				}
				else if (0 < BossHP)
				{
					ChangeState(MonsterState::Hitten);
				}
				break;
			}
		}
	}
}

void Penguin::HittenStart()
{
	MainRenderer->ChangeAnimation("Down_Hitten");
}

void Penguin::HittenUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MonsterState::Idle);
		IsHitten = false;
	}
}

void Penguin::SummonStart()
{
	MainRenderer->ChangeAnimation("Summon");
}

void Penguin::SummonUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MonsterState::Idle);
	}
}