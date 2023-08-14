#include <GameEngineBase/GameEngineRandom.h>

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
#include "BaseCharacter.h"

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

	if (nullptr == ResourcesManager::GetInst().FindSprite("Down_Idle"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Monster\\Boss\\");

		// Down
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Idle", FilePath.PlusFilePath("Idle_Penguin.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Hitten", FilePath.PlusFilePath("Hitten_Penguin.bmp"), 5, 1);
		// Up

		// Right

		// Left


		ResourcesManager::GetInst().CreateSpriteSheet("Summon_Penguin", FilePath.PlusFilePath("Summon_Penguin.bmp"), 20, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Die_Ready", FilePath.PlusFilePath("Die_Ready_Penguin.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Die_Bubble", FilePath.PlusFilePath("Die_Bubble_Penguin.bmp"), 8, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Die", FilePath.PlusFilePath("Die_Penguin.bmp"), 12, 1);
	}

	{
		// Down
		{
			// Idle
			MainRenderer->CreateAnimation("Down_Idle", "Down_Idle", 0, 8, IDLE_ANI_SPEED);
			MainRenderer->FindAnimation("Down_Idle")->Inters[8] = 5.0f;

			// Move
			// MainRenderer->CreateAnimation("Down_Move", "Down_Move", 0, 4, IDLE_ANI_SPEED, false);

			// Hitten
			MainRenderer->CreateAnimation("Down_Hitten", "Down_Hitten", 0, 4, IDLE_ANI_SPEED, false);
		}

		// Up
		{

		}

		// Right
		{

		}

		// Left
		{

		}

		// Summon
		MainRenderer->CreateAnimation("Summon", "Summon_Penguin", 0, 19, IDLE_ANI_SPEED, false);

		// Death
		MainRenderer->CreateAnimation("Die_Ready", "Die_Ready", 0, 2, BUBBLE_ANI_SPEED, false);
		MainRenderer->CreateAnimation("Die_Bubble", "Die_Bubble", 0, 7, BUBBLE_ANI_SPEED);
		MainRenderer->CreateAnimation("Die", "Die", 0, 11, BUBBLE_ANI_SPEED, false);
	}

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
	StateUpdate(_Delta);

	if (MonsterState::Die_Ready == State || MonsterState::Die_Bubble == State || MonsterState::Die == State)
	{
		return;
	}

	PatternTimer += _Delta;

	if (true == GameEngineInput::IsDown('J'))
	{
		IsDebugMode = !IsDebugMode;
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		ChangeState(MonsterState::Summon);
	}

	if (PatternTimer >= PATTERN_TIME && false == PatternStart)
	{
		PatternCount = GameEngineRandom::MainRandom.RandomInt(2, 4);
		PatternStart = true;
	}

	if (true == GameEngineInput::IsDown('B'))
	{
		PatternCount = GameEngineRandom::MainRandom.RandomInt(2, 4);
		PatternStart = true;
		PatternTimer = PATTERN_TIME;
	}

	if (true == GameEngineInput::IsDown('O'))
	{
		ChangeState(MonsterState::Move);

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
	if (true == CurPlayLevel->PatternAnimationEnd)
	{
		PatternUpdate();
	}
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
	case MonsterState::Move:
		return MoveUpdate(_Delta);
	case MonsterState::Die:
		return DieUpdate(_Delta);
	case MonsterState::Hitten:
		return HittenUpdate(_Delta);
	case MonsterState::Summon:
		return SummonUpdate(_Delta);
	case MonsterState::Die_Ready:
		return DieReadyUpdate(_Delta);
	case MonsterState::Die_Bubble:
		return DieBubbleUpdate(_Delta);
	default:
		break;
	}
}

void Penguin::ChangeState(MonsterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case MonsterState::Idle:
			IdleStart();
			break;
		case MonsterState::Move:
			MoveStart();
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
		case MonsterState::Die_Ready:
			DieReadyStart();
			break;
		case MonsterState::Die_Bubble:
			DieBubbleStart();
			break;
		default:
			break;
		}
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

ActorDir Penguin::DirDecision(int _MoveRange)
{
	std::vector<ActorDir> MoveDir;
	ActorDir CheckDir;
	MoveDir.reserve(4);

	GameEngineRenderer* MoveTile = nullptr;

	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			MoveTile = CurLevelTile->GetTile(BossTile[0][0].iX() - _MoveRange, BossTile[0][0].iY());
			CheckDir = ActorDir::Left;
			break;
		case 1:
			MoveTile = CurLevelTile->GetTile(BossTile[0][1].iX(), BossTile[0][1].iY() - _MoveRange);
			CheckDir = ActorDir::Up;
			break;
		case 2:
			MoveTile = CurLevelTile->GetTile(BossTile[0][2].iX() + _MoveRange, BossTile[0][2].iY());
			CheckDir = ActorDir::Right;
			break;
		case 3:
			MoveTile = CurLevelTile->GetTile(BossTile[1][0].iX(), BossTile[1][0].iY() + _MoveRange);
			CheckDir = ActorDir::Down;
			break;
		default:
			break;
		}

		if (nullptr != MoveTile)
		{
			MoveDir.push_back(CheckDir);
		}
	}

	GameEngineRandom::MainRandom.SetSeed(time(NULL));
	int ReturnIndex = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(MoveDir.size()) - 1);

	return MoveDir[ReturnIndex];
}

void Penguin::MoveStart()
{
	GameEngineRandom::MainRandom.SetSeed(time(NULL));
	int MoveIndex = GameEngineRandom::MainRandom.RandomInt(1,2);
	Dir = DirDecision(MoveIndex);

	switch (Dir)
	{
	case ActorDir::Left:
		MoveRange = { -BOSSMOVERANGE * MoveIndex, 0 };
		break;
	case ActorDir::Right:
		MoveRange = { BOSSMOVERANGE * MoveIndex, 0 };
		break;
	case ActorDir::Up:
		MoveRange = { 0 , -BOSSMOVERANGE * MoveIndex };
		break;
	case ActorDir::Down:
		MoveRange = { 0 , BOSSMOVERANGE * MoveIndex };
		break;
	default:
		break;
	}
}

void Penguin::MoveUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	switch (Dir)
	{
	case ActorDir::Left:
		MoveRange += { BOSSMOVESPEED * _Delta, 0};
		MovePos += { - BOSSMOVESPEED* _Delta, 0};
		if (0.0f < MoveRange.X)
		{
			MoveRange.X = 0.0f;
		}
		break;
	case ActorDir::Right:
		MoveRange += { - BOSSMOVESPEED* _Delta, 0};
		MovePos += { BOSSMOVESPEED* _Delta, 0};
		if (0.0f > MoveRange.X)
		{
			MoveRange.X = 0.0f;
		}
		break;
	case ActorDir::Up:
		MoveRange += { 0, BOSSMOVESPEED* _Delta};
		MovePos += { 0, - BOSSMOVESPEED* _Delta};
		if (0.0f < MoveRange.Y)
		{
			MoveRange.Y = 0.0f;
		}
		break; 
	case ActorDir::Down:
		MoveRange += { 0, - BOSSMOVESPEED* _Delta};
		MovePos += { 0, BOSSMOVESPEED* _Delta};
		if (0.0f > MoveRange.Y)
		{
			MoveRange.Y = 0.0f;
		}
		break;
	default:
		break;
	}
	AddPos(MovePos);

	if (0.0f == MoveRange.X && 0.0f == MoveRange.Y)
	{
		ChangeState(MonsterState::Idle);
	}
}

void Penguin::DieReadyStart()
{
	MainRenderer->ChangeAnimation("Die_Ready");
}

void Penguin::DieReadyUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MonsterState::Die_Bubble);
	}
}

void Penguin::DieBubbleStart()
{
	MainRenderer->ChangeAnimation("Die_Bubble");

}

void Penguin::DieBubbleUpdate(float _Delta)
{
	float4 PlayerPos = CurPlayLevel->Player->GetPos();
	float4 Index = CurPlayLevel->GetGroundTile()->PosToIndex(PlayerPos - GlobalValue::TileStartPos);

	for (int Y = 0; Y < BossTile.size(); Y++)
	{
		for (int X = 0; X < BossTile[Y].size(); X++)
		{
			if (BossTile[Y][X].iX() == Index.iX() && BossTile[Y][X].iY() == Index.iY())
			{
				ChangeState(MonsterState::Die);
			}
		}
	}
}


void Penguin::DieStart()
{
	MainRenderer->ChangeAnimation("Die");
}

void Penguin::DieUpdate(float _Delta)
{
	if (0 >= DieAlpha)
	{
		Death();
	}

	if (true == MainRenderer->IsAnimationEnd())
	{
		DieAlpha -= _Delta * 255;
		MainRenderer->SetAlpha(static_cast<unsigned char>(DieAlpha));
	}
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
			TileObjectOrder CurTile = PlayLevel::CurPlayLevel->GetCurTileType(CurLevelTile->IndexToPos(BossTile[Y][X].iX(), BossTile[Y][X].iY() + 1) + GlobalValue::TileStartPos);
			if (CurTile == TileObjectOrder::PopRange)
			{
				--BossHP;
				IsHitten = true;
				if (0 == BossHP)
				{
					ChangeState(MonsterState::Die_Ready);
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

// Test Code
void Penguin::PatternUpdate()
{
	if (false == PatternStart || PATTERN_TIME > PatternTimer)
	{
		return;
	}
	static int CurPatternCount = 0;
	GameEngineRandom::MainRandom.SetSeed(time(NULL));
	int Range = 0;
	++CurPatternCount;
	switch (CurPatternCount)
	{
	case 1:
		Range = GameEngineRandom::MainRandom.RandomInt(CurPatternCount + 2, CurPatternCount + 3);
		break;
	case 2:
		Range = GameEngineRandom::MainRandom.RandomInt(CurPatternCount + 3, CurPatternCount + 4);
		break;
	case 3:
		Range = GameEngineRandom::MainRandom.RandomInt(CurPatternCount + 4, CurPatternCount + 5);
		break;
	case 4:
		Range = GameEngineRandom::MainRandom.RandomInt(CurPatternCount + 5, CurPatternCount + 6);
		break;
	default:
		break;
	}
	CurPlayLevel->PatternAnimationEnd = false;
	CurPlayLevel->BubblePattern(BossTile[1][1].iX(), BossTile[1][1].iY(), Range);

	if (CurPatternCount == PatternCount)
	{
		PatternCount = 0;
		CurPatternCount = 0;
		PatternStart = false;
		PatternTimer = 0.0f;
		CurPlayLevel->PatternAnimationEnd = true;
	}
}