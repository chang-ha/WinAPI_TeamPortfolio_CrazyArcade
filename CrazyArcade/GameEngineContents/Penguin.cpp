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
#include "Snowmon_black.h"

// Debug
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>

Penguin* Penguin::BossMonster = nullptr;

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

	MainRenderer = CreateRenderer(RenderOrder::MapObject);
	MainRenderer->SetYPivot(GlobalValue::MapTileSize.Y * 2 + 10);
	GameEngineRenderer* HPBar_Renderer = CreateRenderer(RenderOrder::FirstElementUI);
	HP_Renderer = CreateRenderer(RenderOrder::FirstElementUI);
	Shadow = CreateRenderer(RenderOrder::Shadow);

	// Texture Load
	if (nullptr == ResourcesManager::GetInst().FindSprite("Down_Idle"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Monster\\Boss\\");

		// Down
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Idle", FilePath.PlusFilePath("Idle_Penguin.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Move", FilePath.PlusFilePath("Down_Move.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Hitten", FilePath.PlusFilePath("Down_Hitten.bmp"), 5, 1);

		// Up
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Move", FilePath.PlusFilePath("Up_Move.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Up_Hitten", FilePath.PlusFilePath("Up_Hitten.bmp"), 5, 1);

		// Right
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Move", FilePath.PlusFilePath("Right_Move.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Right_Hitten", FilePath.PlusFilePath("Right_Hitten.bmp"), 5, 1);

		// Left
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Move", FilePath.PlusFilePath("Left_Move.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Left_Hitten", FilePath.PlusFilePath("Left_Hitten.bmp"), 5, 1);

		ResourcesManager::GetInst().CreateSpriteSheet("Anger_Penguin", FilePath.PlusFilePath("Anger_Penguin.bmp"), 12, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Summon_Penguin", FilePath.PlusFilePath("Summon_Penguin.bmp"), 20, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Die_Ready", FilePath.PlusFilePath("Die_Ready_Penguin.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Die_Bubble", FilePath.PlusFilePath("Die_Bubble_Penguin.bmp"), 8, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Die", FilePath.PlusFilePath("Die_Penguin.bmp"), 12, 1);

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HP_BLUE.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HP_RED.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Boss_Shadow.bmp"));
	}

	// Sound Load
	if (nullptr == GameEngineSound::FindSound("Locked_In_Bubble.wav"))
	{
		GlobalUtils::SoundFileLoad("Locked_In_Bubble.wav", "Resources\\Sounds\\Character\\");
		GlobalUtils::SoundFileLoad("Character_Death.wav", "Resources\\Sounds\\Character\\");
	}

	{
		// Down
		{
			// Idle
			MainRenderer->CreateAnimation("Down_Idle", "Down_Idle", 0, 8, IDLE_ANI_SPEED);
			MainRenderer->FindAnimation("Down_Idle")->Inters[8] = 5.0f;

			// Move
			MainRenderer->CreateAnimation("Down_Move", "Down_Move", 0, 5, MOVE_ANI_SPEED);

			// Hitten
			MainRenderer->CreateAnimation("Down_Hitten", "Down_Hitten", 0, 4, HITTEN_ANI_SPEED);
		}

		// Up
		{
			// Idle
			MainRenderer->CreateAnimation("Up_Idle", "Down_Idle", 0, 0);

			// Move
			MainRenderer->CreateAnimation("Up_Move", "Up_Move", 0, 4, MOVE_ANI_SPEED);

			// Hitten
			MainRenderer->CreateAnimation("Up_Hitten", "Up_Hitten", 0, 4, HITTEN_ANI_SPEED);
		}

		// Right
		{
			//Idle
			MainRenderer->CreateAnimation("Right_Idle", "Right_Move", 0, 0);

			// Move
			MainRenderer->CreateAnimation("Right_Move", "Right_Move", 0, 5, MOVE_ANI_SPEED);

			// Hitten 
			MainRenderer->CreateAnimation("Right_Hitten", "Right_Hitten", 0, 4, HITTEN_ANI_SPEED);
		}

		// Left
		{
			//Idle
			MainRenderer->CreateAnimation("Left_Idle", "Left_Move", 0, 0);
			
			// Move
			MainRenderer->CreateAnimation("Left_Move", "Left_Move", 0, 5, MOVE_ANI_SPEED);

			// Hitten
			MainRenderer->CreateAnimation("Left_Hitten", "Left_Hitten", 0, 4, HITTEN_ANI_SPEED);
		}

		// Anger 
		MainRenderer->CreateAnimation("Anger", "Anger_Penguin", 0, 11, ANGER_ANI_SPEED, false);

		// Summon
		MainRenderer->CreateAnimation("Summon", "Summon_Penguin", 0, 19, IDLE_ANI_SPEED, false);

		// Death
		MainRenderer->CreateAnimation("Die_Ready", "Die_Ready", 0, 2, BUBBLE_ANI_SPEED, false);
		MainRenderer->CreateAnimation("Die_Bubble", "Die_Bubble", 0, 7, BUBBLE_ANI_SPEED);
		MainRenderer->CreateAnimation("Die", "Die", 0, 11, BUBBLE_ANI_SPEED, false);
	}

	MainRenderer->ChangeAnimation("Down_Idle");
	MainRenderer->SetRenderPos({0, -70});

	HPBar_Renderer->SetTexture("HPBar.bmp");
	HPBar_Renderer->SetRenderPos(HPBARPOS);
	HP_Renderer->SetTexture("HP_BLUE.bmp");
	HP_Renderer->SetRenderPos(HPBARPOS - float4{42, 0});

	Shadow->SetTexture("Boss_Shadow.bmp");
	// BossTile Vector resize
	BossTile.resize(2);
	for (int Y = 0; Y < BossTile.size(); Y++)
	{
		BossTile[Y].resize(3);
	}

	BossMonster = this;
}

void Penguin::Update(float _Delta)
{
	StateUpdate(_Delta);

	// Debug
	if (true == GameEngineInput::IsDown('J'))
	{
		IsDebugMode = !IsDebugMode;
	}

	// Hp UI Update
	{
		HP_Renderer->SetRenderScale(float4{ 2.0f * 12.0f * BossHP , 7 });

		if (ANGERHP == BossHP)
		{
			HP_Renderer->SetTexture("HP_RED.bmp");
		}
	}
	
	// Bubble Pattern Update
	if (true == CurPlayLevel->PatternAnimationEnd && false == BubblePatternStart)
	{
		SequentialPatternUpdate();
	}

	if (true == CurPlayLevel->PatternAnimationEnd && false == SequentialPatternStart)
	{
		BubblePatternUpdate();
	}

	if (MonsterState::Die_Ready == State || MonsterState::Die_Bubble == State || MonsterState::Die == State || MonsterState::Anger == State)
	{
		return;
	}

	BubblePatternTimer += _Delta;
	SummonPatternTimer += _Delta;
	MovePatternTimer += _Delta;

	// Cheat
	{
		if (true == GameEngineInput::IsDown('1'))
		{
			BubblePatternReset();
			SequentialPatternStart = true;
			SequentialPatternInit(4, 4, 1);
		}

		if (true == GameEngineInput::IsDown('2'))
		{
			BubblePatternReset();
			SequentialPatternStart = true;
			SequentialPatternInit(6, 3, -1);
		}

		if (true == GameEngineInput::IsDown('3'))
		{
			SequentialPatternReset();
			BubblePatternStart = true;
			BubblePatternTimer = BUBBLEPATTERN_TIME;
			GameEngineRandom::MainRandom.SetSeed(time(NULL));
			MaxPatternCount = GameEngineRandom::MainRandom.RandomInt(2, 4);
		}

		if (true == GameEngineInput::IsDown('4'))
		{
		    ChangeState(MonsterState::Summon);
			IsHitten = false;
		}

		if (true == GameEngineInput::IsDown('5'))
		{
			ChangeState(MonsterState::Move);
			IsHitten = false;
		}

		if (true == GameEngineInput::IsDown('7'))
		{
			Invincibility = !Invincibility;
		}
	}

	if (false == OncePatternOn && 1 == BossHP && false == BubblePatternStart)
	{
		BubblePatternReset();
		OncePatternOn = true;
		SequentialPatternStart = true;
		SequentialPatternInit(6, 3, -1);
	}

	// Bubble Pattern Start
	if (BubblePatternTimer >= BUBBLEPATTERN_TIME && false == BubblePatternStart)
	{
		SequentialPatternReset();
		GameEngineRandom::MainRandom.SetSeed(time(NULL));
		MaxPatternCount = GameEngineRandom::MainRandom.RandomInt(2, 4);
		BubblePatternStart = true;
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
				CurPlayLevel->PrevBubblePop(Index_X , Index_Y);
			}
		}
	}

	// Hit Judge
	HitJudgement();

	// Summon Pattern
	SummonMonster();

	// Move Continuous
	if (MonsterState::Idle == State && (0.0f != MoveRange.X || 0.0f != MoveRange.Y))
	{
		ChangeState(MonsterState::Move);
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
	Data.Scale = GlobalValue::MapTileSize;
	for (int Y = 0; Y < BossTile.size(); Y++)
	{
		for (int X = 0; X < BossTile[Y].size(); X++)
		{
			Data.Pos = CurLevelTile->IndexToPos(BossTile[Y][X].iX() + 1, BossTile[Y][X].iY() + 2) + Data.Scale.Half() - GlobalValue::TileStartPos;
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
	case MonsterState::Anger:
		return AngerUpdate(_Delta);
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
		case MonsterState::Anger:
			AngerStart();
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
	ChangeAnimationState(MonsterState::Idle);
	IsHitten = false;
}

void Penguin::IdleUpdate(float _Delta)
{
	if (true == MovePatternOn && MOVEPATTERN_TIME <= MovePatternTimer)
	{
		ChangeState(MonsterState::Move);
	}

	if (SUMMONPATTERN_TIME <= SummonPatternTimer)
	{
		Dir = ActorDir::Down;
		ChangeState(MonsterState::Summon);
	}
}

void Penguin::ChangeAnimationState(MonsterState _State)
{
	std::string AnimationName = "";
	
	if (ActorDir::Right == Dir)
	{
		AnimationName = "Right_";
	}
	else if (ActorDir::Left == Dir)
	{
		AnimationName = "Left_";
	}
	else if (ActorDir::Up == Dir)
	{
		AnimationName = "Up_";
	}
	else if (ActorDir::Down == Dir)
	{
		AnimationName = "Down_";
	}

	switch (_State)
	{
	case MonsterState::Idle:
		AnimationName += "Idle";
		break;
	case MonsterState::Move:
		AnimationName += "Move";
		break;
	case MonsterState::Hitten:
		AnimationName += "Hitten";
		break;
	case MonsterState::Ready:
	case MonsterState::Freeze:
	case MonsterState::Anger:
	case MonsterState::AngerIdle:
	case MonsterState::AngerMove:
	case MonsterState::EggSummon:
	case MonsterState::EggIdle:
	case MonsterState::EggMove:
	case MonsterState::EggHatch:
	case MonsterState::EggDeath:
	case MonsterState::Die:
	case MonsterState::Summon:
	case MonsterState::Die_Ready:
	case MonsterState::Die_Bubble:
	default:
		MsgBoxAssert("방향애니메이션이 존재하지 않는 State값입니다.");
		break;
	}

	State = _State;
	MainRenderer->ChangeAnimation(AnimationName);
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

	Dir = MoveDir[ReturnIndex];
	return Dir;
}

void Penguin::MoveStart()
{
	if ((0.0f != MoveRange.X || 0.0f != MoveRange.Y))
	{
		ChangeAnimationState(MonsterState::Move);
		return;
	}

	GameEngineRandom::MainRandom.SetSeed(time(NULL));
	int MoveIndex = GameEngineRandom::MainRandom.RandomInt(1,3);
	DirDecision(MoveIndex);

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

	ChangeAnimationState(MonsterState::Move);
	MovePatternTimer = 0.0f;
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
		Dir = ActorDir::Down;
		ChangeState(MonsterState::Idle);
	}
}

void Penguin::AngerStart()
{
	MainRenderer->ChangeAnimation("Anger");
	IsHitten = false;
	MovePatternOn = true;

	CurPlayLevel->BGMPlayer.Stop();
	CurPlayLevel->BGMPlayer = GameEngineSound::SoundPlay("Boss_2_Phase_BGM.wav", 10000);
	CurPlayLevel->BGMPlayer.SetVolume(CurPlayLevel->BGMVolume);

	BubblePatternReset();
	SequentialPatternStart = true;
	SequentialPatternInit(4, 4, 1);
}

void Penguin::AngerUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		Dir = ActorDir::Down;
		ChangeState(MonsterState::Idle);
	}
}


void Penguin::DieReadyStart()
{
	MainRenderer->ChangeAnimation("Die_Ready");
	MonsterEffectSound = GameEngineSound::SoundPlay("Locked_In_Bubble.wav");
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
	float4 PlayerPos = {};
	for (int i = 0; i < 2; i++)
	{
		switch (i)
		{
		case 0:
			PlayerPos = CurPlayLevel->Player->GetPos();
			break;
		case 1:
			if (nullptr != CurPlayLevel->Player2)
			{
				PlayerPos = CurPlayLevel->Player2->GetPos();
			}
			break;
		default:
			break;
		}
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
}


void Penguin::DieStart()
{
	MainRenderer->ChangeAnimation("Die");
	MonsterEffectSound = GameEngineSound::SoundPlay("Character_Death.wav");
}

void Penguin::DieUpdate(float _Delta)
{
	if (0 >= DieAlpha)
	{
		Death();
		PlayLevel::CurPlayLevel->MonsterListDelete();
		BossMonster = nullptr;
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
			TileObjectOrder CurTile = PlayLevel::CurPlayLevel->GetCurTileType(CurLevelTile->IndexToPos(BossTile[Y][X].iX(), BossTile[Y][X].iY()) + GlobalValue::TileStartPos);
			if (CurTile == TileObjectOrder::PopRange)
			{
				if (false == Invincibility)
				{
					--BossHP;
				}
				IsHitten = true;
				if (0 == BossHP)
				{
					ChangeState(MonsterState::Die_Ready);
				}
				else if (0 < BossHP)
				{
					ChangeState(MonsterState::Hitten);
				}
				return;
			}
		}
	}
}

void Penguin::HittenStart()
{
	ChangeAnimationState(MonsterState::Hitten);
}

void Penguin::HittenUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		if (ANGERHP == BossHP)
		{
			ChangeState(MonsterState::Anger);
			return;
		}
		ChangeState(MonsterState::Idle);
	}
}

void Penguin::SummonStart()
{
	MainRenderer->ChangeAnimation("Summon");
	SummonPatternStart = true;
	SummonPatternTimer = 0.0f;
}

void Penguin::SummonUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MonsterState::Idle);
	}
}

void Penguin::SummonMonster()
{
	if (false == SummonPatternStart || SUMMON_TIME > SummonPatternTimer)
	{
		return;
	}
	
	std::vector<float4> EmptyPlace;
	EmptyPlace.reserve(15 * 13);

	for (int Y = 0; Y < 13; Y++)
	{
		for (int X = 0; X < 15; X++)
		{
			if (X >= BossTile[0][0].X && Y >= BossTile[0][0].Y && X <= BossTile[1][2].X && Y <= BossTile[1][2].Y)
			{
				continue;
			}

			if (TileObjectOrder::Empty == CurPlayLevel->TileInfo[Y][X].MapInfo)
			{
				float4 Index = { static_cast<float>(X), static_cast<float>(Y) };
				EmptyPlace.push_back(Index);
			}
		}
	}

	GameEngineRandom::MainRandom.SetSeed(time(NULL));
	int First = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(EmptyPlace.size()) / 2 - 1);
	int Second = GameEngineRandom::MainRandom.RandomInt(static_cast<int>(EmptyPlace.size()) / 2, static_cast<int>(EmptyPlace.size()) - 1);

	Snowmon_black* Snowmon = CurPlayLevel->CreateMonster<Snowmon_black>();
	Snowmon->SetPos(CurLevelTile->IndexToPos(EmptyPlace[First].iX() + 1, EmptyPlace[First].iY() + 1));
	Snowmon->SetState(MonsterState::EggSummon);

	Snowmon = CurPlayLevel->CreateMonster<Snowmon_black>();
	Snowmon->SetPos(CurLevelTile->IndexToPos(EmptyPlace[Second].iX() + 1, EmptyPlace[Second].iY() + 1));
	Snowmon->SetState(MonsterState::EggSummon);

	SummonPatternStart = false;
	SummonPatternTimer = 0.0f;
}
	
void Penguin::BubblePatternReset()
{
	CurPatternCount = 0;
	BubblePatternStart = false;
	BubblePatternTimer = 0.0f;
	CurPlayLevel->PatternAnimationEnd = true;
}

void Penguin::BubblePatternUpdate()
{
	if (false == BubblePatternStart || BUBBLEPATTERN_TIME > BubblePatternTimer)
	{
		return;
	}

	GameEngineRandom::MainRandom.SetSeed(time(NULL));
	int Range = 0;
	++CurPatternCount;
	switch (CurPatternCount)
	{
	case 1:
		Range = GameEngineRandom::MainRandom.RandomInt(CurPatternCount + 1, CurPatternCount + 2);
		break;
	case 2:
		Range = GameEngineRandom::MainRandom.RandomInt(CurPatternCount + 2, CurPatternCount + 3);
		break;
	case 3:
		Range = GameEngineRandom::MainRandom.RandomInt(CurPatternCount + 3, CurPatternCount + 4);
		break;
	case 4:
		Range = GameEngineRandom::MainRandom.RandomInt(CurPatternCount + 4, CurPatternCount + 5);
		break;
	default:
		break;
	}
	CurPlayLevel->PatternAnimationEnd = false;
	CurPlayLevel->BubblePattern(BossTile[1][1].iX(), BossTile[1][1].iY(), Range);

	if (CurPatternCount == MaxPatternCount)
	{
		BubblePatternReset();
	}
}

void Penguin::SequentialPatternReset()
{
	CurPatternCount = 0;
	SequentialPatternStart = false;
}

void Penguin::SequentialPatternInit(int _StartRange, int _PatternCount, int _PlusRange)
{
	StartRange = _StartRange;
	MaxPatternCount = _PatternCount;
	PlusRange = _PlusRange;
}


void Penguin::SequentialPatternUpdate()
{
	if (false == SequentialPatternStart)
	{
		return;
	}

	BubblePatternTimer = 0.0f;
	int Range = StartRange + CurPatternCount * PlusRange - 1;

	if (MaxPatternCount > CurPatternCount)
	{
		++CurPatternCount;
	}
	else
	{
		SequentialPatternReset();
		return;
	}

	CurPlayLevel->PatternAnimationEnd = false;
	CurPlayLevel->BubblePattern(BossTile[1][1].iX(), BossTile[1][1].iY(), Range);
}