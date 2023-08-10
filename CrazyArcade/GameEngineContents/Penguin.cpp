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

		// ResourcesManager::GetInst().CreateSpriteSheet("Down_Idle", FilePath.PlusFilePath("Idle_Penguin.bmp"), 10, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Hitten", FilePath.PlusFilePath("Hitten_Penguin.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Summon_Penguin", FilePath.PlusFilePath("Summon_Penguin.bmp"), 20, 1);
	}

	//MainRenderer->CreateAnimation("Down_Idle", "Down_Idle", 0, 9, 0.15f, true);
	//MainRenderer->FindAnimation("Down_Idle")->Inters[9] = 5.0f;
	//MainRenderer->ChangeAnimation("Down_Idle");

	MainRenderer->CreateAnimation("Down_Hitten", "Down_Hitten", 0, 4, ANIMATION_SPEED, true);

	MainRenderer->CreateAnimation("Summon", "Summon_Penguin", 0, 19, ANIMATION_SPEED, true);
	MainRenderer->ChangeAnimation("Down_Hitten");
	State = MonsterState::Hitten;
	MainRenderer->SetRenderPos({0, -60});

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

	// BossTile Update
	CurLevelTile = CurPlayLevel->GetGroundTile();
	float4 CurPos = GetPos();
	float4 Index = CurLevelTile->PosToIndex(CurPos);

	for (int Y = 0; Y < BossTile.size(); Y++)
	{
		for (int X = 0; X < BossTile[Y].size(); X++)
		{
			BossTile[Y][X] = float4{ Index.X - 1 + X, Index.Y + Y};
		}
	}

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
			Data.Pos = CurLevelTile->IndexToPos(BossTile[Y][X].iX(), BossTile[Y][X].iY()) + GlobalValue::MapTileSize.Half() - GlobalValue::TileStartPos;
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
	// MainRenderer->ChangeAnimation("Down_Idle");
	// MainRenderer->ChangeAnimation("Summon");
}

void Penguin::IdleUpdate(float _Delta)
{
	for (int Y = 0; Y < BossTile.size(); Y++)
	{
		for (int X = 0; X < BossTile[Y].size(); X++)
		{
			TileObjectOrder CurTile = PlayLevel::CurPlayLevel->GetCurTileType(CurLevelTile->IndexToPos(BossTile[Y][X].iX(), BossTile[Y][X].iY()));
			if (CurTile == TileObjectOrder::PopRange)
			{
				--BossHP;
				if (0 == BossHP)
				{
					// ChangeState(MonsterState::Die);
				}
				else if (0 < BossHP)
				{
					ChangeState(MonsterState::Hitten);
				}
			}
		}
	}
}

void Penguin::DieStart()
{

}

void Penguin::DieUpdate(float _Delta)
{
	ChangeState(MonsterState::Idle);
}


void Penguin::HittenStart()
{
	MainRenderer->ChangeAnimation("Down_Hitten");
}

void Penguin::HittenUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MonsterState::Summon);
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
		ChangeState(MonsterState::Hitten);
	}
}