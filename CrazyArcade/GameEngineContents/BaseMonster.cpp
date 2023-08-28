#include "BaseMonster.h"
#include "GlobalUtils.h"
#include "PlayLevel.h"
#include "BaseCharacter.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/TileMap.h>

BaseMonster::BaseMonster()
{
}

BaseMonster::~BaseMonster()
{
}

void BaseMonster::Start() 
{
	{
		MonsterCollision = CreateCollision(CollisionOrder::MonsterBody);
		MonsterCollision->SetCollisionPos(GetPos() + float4 CENTERPOS);
		MonsterCollision->SetCollisionScale(MONSTERCOLLISIONSCALE);
		MonsterCollision->SetCollisionType(CollisionType::Rect);
	}

	{
		// Sound
		GlobalUtils::SoundFileLoad("Ice_Monster_Angry.wav", "Resources\\Sounds\\Monster\\");
		GlobalUtils::SoundFileLoad("Ice_Monster_Death.wav", "Resources\\Sounds\\Monster\\");
		GlobalUtils::SoundFileLoad("Ice_Monster_Freeze.wav", "Resources\\Sounds\\Monster\\");
		GlobalUtils::SoundFileLoad("Pirate_Monster_Death.wav", "Resources\\Sounds\\Monster\\");
		GlobalUtils::SoundFileLoad("Hatching_Egg2.wav", "Resources\\Sounds\\Boss\\");
	}

	{
		GlobalUtils::SpriteFileLoad("Shadow.Bmp", "Resources\\Textures\\Monster\\", 1, 1);
		ShadowRenderer = CreateRenderer("Shadow.bmp", RenderOrder::Shadow);
		ShadowRenderer->SetAlpha(GlobalValue::AllAlphaValue);
	}

	// 색적 타일 vector resize
	TrackingTiles.resize(8);
}

void BaseMonster::Update(float _Delta)
{
	StateUpdate(_Delta);

	if (true == GameEngineInput::IsDown('J'))
	{
		SwitchDebugData();
	}

	if (true == GameEngineInput::IsDown('F'))
	{
		ChangeState(MonsterState::Freeze);
		return;
	}

	if (!(State == MonsterState::Freeze || State == MonsterState::Anger || State == MonsterState::AngerIdle))
	{
		CheckCollision();
	}

	// 몬스터 색적 타일 업데이트
	TrackingTileUpdate();
}

void BaseMonster::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	if (true == IsDebugData)
	{
		CollisionData Data;

		Data.Pos = GetPos();
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


		Data.Pos = GetPos() + float4 LEFTTOPPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 TOPPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 RIGHTTOPPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


		Data.Pos = GetPos() + float4 LEFTBOTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 BOTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 RIGHTBOTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


		Data.Pos = GetPos() + float4 TOPLEFTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 LEFTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 BOTLEFTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


		Data.Pos = GetPos() + float4 TOPRIGHTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 RIGHTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 BOTRIGHTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());


		Data.Pos = GetPos() + float4 CENTERPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	}
}

void BaseMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
	case MonsterState::Move:
		return MoveUpdate(_Delta);
	case MonsterState::Freeze:
		return FreezeUpdate(_Delta);
	case MonsterState::Ready:
		return ReadyUpdate(_Delta);
	case MonsterState::Anger:
		return AngerUpdate(_Delta);
	case MonsterState::AngerIdle:
		return AngerIdleUpdate(_Delta);
	case MonsterState::AngerMove:
		return AngerMoveUpdate(_Delta);
	case MonsterState::EggSummon:
		return EggSummonUpdate(_Delta);
	case MonsterState::EggIdle:
		return EggIdleUpdate(_Delta);
	case MonsterState::EggMove:
		return EggMoveUpdate(_Delta);
	case MonsterState::EggHatch:
		return EggHatchUpdate(_Delta);
	case MonsterState::EggDeath:
		return EggDeathUpdate(_Delta);
	case MonsterState::Die:
		return DieUpdate(_Delta);
	default:
		break;
	}
}

void BaseMonster::ChangeState(MonsterState _State)
{
	switch (_State)
	{
	case MonsterState::Idle:
		IdleStart();
		break;
	case MonsterState::Move:
		MoveStart();
		break;
	case MonsterState::Freeze:
		FreezeStart();
		break;
	case MonsterState::Ready:
		ReadyStart();
		break;
	case MonsterState::Anger:
		AngerStart();
		break;
	case MonsterState::AngerIdle:
		AngerIdleStart();
		break;
	case MonsterState::AngerMove:
		AngerMoveStart();
		break;
	case MonsterState::EggSummon:
		EggSummonStart();
		break;
	case MonsterState::EggIdle:
		EggIdleStart();
		break;
	case MonsterState::EggMove:
		EggMoveStart();
		break;
	case MonsterState::EggHatch:
		EggHatchStart();
		break;
	case MonsterState::EggDeath:
		EggDeathStart();
		break;
	case MonsterState::Die:
		DieStart();
		break;
	default:
		break;
	}

	State = _State;
}

void BaseMonster::RandomDir(const std::string& _StateName)
{
	int Random = GameEngineRandom::MainRandom.RandomInt(1, 4);

	ActorDir CurDir = Dir;
	ActorDir NextDir = Dir;

	switch (Random)
	{
	case 1:
		NextDir = ActorDir::Down;
		break;
	case 2:
		NextDir = ActorDir::Up;
		break;
	case 3:
		NextDir = ActorDir::Left;
		break;
	case 4:
		NextDir = ActorDir::Right;
		break;
	default:
		break;
	}

	if (CurDir != NextDir)
	{
		Dir = NextDir;
		ChangeAnimationState(_StateName);
	}
}

void BaseMonster::PatternDir(const std::string& _StateName)
{
	if (false == MonsterMovePattern.empty())
	{
		Dir = MonsterMovePattern.front();
		ChangeAnimationState(_StateName);

		MonsterMovePattern.pop_front();
	}
}

void BaseMonster::CheckCollision()
{
	std::vector<GameEngineCollision*> Col;
	if (true == MonsterCollision->Collision(CollisionOrder::PlayerBody, Col, CollisionType::Rect, CollisionType::Rect)
		|| true == MonsterCollision->Collision(CollisionOrder::PlayerBody2, Col, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* _Col : Col)
		{
			BaseCharacter* ColPlayer = dynamic_cast<BaseCharacter*>(_Col->GetActor());

			if (true == ColPlayer->GetPlayerDeath()
				|| true == ColPlayer->GetNoDamage())
			{
				continue;
			}

			ColPlayer->ChangeState(CharacterState::Die);
		}
		return;
	}
}

void BaseMonster::CheckDeath()
{
	CurTile = PlayLevel::CurPlayLevel->GetGroundTile();
	CurTileType = PlayLevel::CurPlayLevel->GetCurTileType(GetPos() + float4 CENTERPOS);

	if (CurTileType == TileObjectOrder::PopRange
		&& State == MonsterState::EggMove)
	{
		KillCountPlus();
		ChangeState(MonsterState::EggDeath);
		return;
	}

	else if (CurTileType == TileObjectOrder::PopRange)
	{
		ChangeState(MonsterState::Freeze);
		return;
	}
}

void BaseMonster::ChangeAnimationState(const std::string& _StateName) {}

void BaseMonster::TrackingTileUpdate()
{
	CurLevelTile = PlayLevel::CurPlayLevel->GetObjectTile();

	float4 CurPos = GetPos() + float4 CENTERPOS - GlobalValue::TileStartPos;
	float4 Index = CurLevelTile->PosToIndex(CurPos);

	float4 Value;
	Value.X = static_cast<float>(Index.iX());
	Value.Y = static_cast<float>(Index.iY());

	float4 NewValue;
	NewValue.X = Value.X - 1;
	NewValue.Y = Value.Y;

	TrackingTiles[0] = NewValue;

	NewValue.X = Value.X - 2;
	NewValue.Y = Value.Y;

	TrackingTiles[1] = NewValue;

	NewValue.X = Value.X + 1;
	NewValue.Y = Value.Y;

	TrackingTiles[2] = NewValue;

	NewValue.X = Value.X + 2;
	NewValue.Y = Value.Y;

	TrackingTiles[3] = NewValue;

	NewValue.X = Value.X;
	NewValue.Y = Value.Y - 1;

	TrackingTiles[4] = NewValue;

	NewValue.X = Value.X;
	NewValue.Y = Value.Y - 2;

	TrackingTiles[5] = NewValue;

	NewValue.X = Value.X;
	NewValue.Y = Value.Y + 1;

	TrackingTiles[6] = NewValue;

	NewValue.X = Value.X;
	NewValue.Y = Value.Y + 2;

	TrackingTiles[7] = NewValue;
}

void BaseMonster::CheckPlayerTracking(const std::string& _State)
{
	if (PlayLevel::CurPlayLevel->GetPlayer()->State == CharacterState::Die)
	{
		return;
	}

	float4 PlayerPos = PlayLevel::CurPlayLevel->Player->GetPos() + float4{ 0.0f, 15.0f } - GlobalValue::TileStartPos;
	float4 PlayerIndex = CurLevelTile->PosToIndex(PlayerPos);

	float4 Value = float4::ZERO;
	Value.X = static_cast<float>(PlayerIndex.iX());
	Value.Y = static_cast<float>(PlayerIndex.iY());

	float4 MonsterTrackTile = TrackingTiles[0];
	if (false == CurLevelTile->IsOver(MonsterTrackTile.iX(), MonsterTrackTile.iY()))
	{
		if (Value.iX() == MonsterTrackTile.iX() && Value.iY() == MonsterTrackTile.iY())
		{
			TileObjectOrder CheckTile = PlayLevel::CurPlayLevel->GetCurTileType(Value.iX(), Value.iY());

			if (TileObjectOrder::Empty == CheckTile)
			{
				Dir = ActorDir::Left;

				ChangeAnimationState(_State);
				return;
			}
		}
	}

	MonsterTrackTile = TrackingTiles[1];
	if (false == CurLevelTile->IsOver(MonsterTrackTile.iX(), MonsterTrackTile.iY()))
	{
		if (Value.iX() == MonsterTrackTile.iX() && Value.iY() == MonsterTrackTile.iY())
		{
			TileObjectOrder CheckTile = PlayLevel::CurPlayLevel->GetCurTileType(Value.iX() + 1, Value.iY());

			if (TileObjectOrder::Empty == CheckTile)
			{
				Dir = ActorDir::Left;

				ChangeAnimationState(_State);
				return;
			}
		}
	}
	
	MonsterTrackTile = TrackingTiles[2];
	if (false == CurLevelTile->IsOver(MonsterTrackTile.iX(), MonsterTrackTile.iY()))
	{
		if (Value.iX() == MonsterTrackTile.iX() && Value.iY() == MonsterTrackTile.iY())
		{
			TileObjectOrder CheckTile = PlayLevel::CurPlayLevel->GetCurTileType(Value.iX(), Value.iY());

			if (TileObjectOrder::Empty == CheckTile)
			{
				Dir = ActorDir::Right;

				ChangeAnimationState(_State);
				return;
			}
		}
	}

	MonsterTrackTile = TrackingTiles[3];
	if (false == CurLevelTile->IsOver(MonsterTrackTile.iX(), MonsterTrackTile.iY()))
	{
		if (Value.iX() == MonsterTrackTile.iX() && Value.iY() == MonsterTrackTile.iY())
		{
			TileObjectOrder CheckTile = PlayLevel::CurPlayLevel->GetCurTileType(Value.iX() - 1, Value.iY());

			if (TileObjectOrder::Empty == CheckTile)
			{
				Dir = ActorDir::Right;

				ChangeAnimationState(_State);
				return;
			}
		}
	}

	MonsterTrackTile = TrackingTiles[4];
	if (false == CurLevelTile->IsOver(MonsterTrackTile.iX(), MonsterTrackTile.iY()))
	{
		if (Value.iX() == MonsterTrackTile.iX() && Value.iY() == MonsterTrackTile.iY())
		{
			TileObjectOrder CheckTile = PlayLevel::CurPlayLevel->GetCurTileType(Value.iX(), Value.iY());

			if (TileObjectOrder::Empty == CheckTile)
			{
				Dir = ActorDir::Up;

				ChangeAnimationState(_State);
				return;
			}
		}
	}

	MonsterTrackTile = TrackingTiles[5];
	if (false == CurLevelTile->IsOver(MonsterTrackTile.iX(), MonsterTrackTile.iY()))
	{
		if (Value.iX() == MonsterTrackTile.iX() && Value.iY() == MonsterTrackTile.iY())
		{
			TileObjectOrder CheckTile = PlayLevel::CurPlayLevel->GetCurTileType(Value.iX(), Value.iY() + 1);

			if (TileObjectOrder::Empty == CheckTile)
			{
				Dir = ActorDir::Up;

				ChangeAnimationState(_State);
				return;
			}
		}
	}

	MonsterTrackTile = TrackingTiles[6];
	if (false == CurLevelTile->IsOver(MonsterTrackTile.iX(), MonsterTrackTile.iY()))
	{
		if (Value.iX() == MonsterTrackTile.iX() && Value.iY() == MonsterTrackTile.iY())
		{
			TileObjectOrder CheckTile = PlayLevel::CurPlayLevel->GetCurTileType(Value.iX(), Value.iY());

			if (TileObjectOrder::Empty == CheckTile)
			{
				Dir = ActorDir::Down;

				ChangeAnimationState(_State);
				return;
			}
		}
	}

	MonsterTrackTile = TrackingTiles[7];
	if (false == CurLevelTile->IsOver(MonsterTrackTile.iX(), MonsterTrackTile.iY()))
	{
		if (Value.iX() == MonsterTrackTile.iX() && Value.iY() == MonsterTrackTile.iY())
		{
			TileObjectOrder CheckTile = PlayLevel::CurPlayLevel->GetCurTileType(Value.iX(), Value.iY() - 1);

			if (TileObjectOrder::Empty == CheckTile)
			{
				Dir = ActorDir::Down;

				ChangeAnimationState(_State);
				return;
			}
		}
	}

	return;
}

void BaseMonster::KillCountPlus()
{
	PlayerNum BubbleMaster = PlayLevel::CurPlayLevel->GetCurTileMaster(GetPos() + float4 CENTERPOS);

	if (BubbleMaster == PlayerNum::P1)
	{
		PlayLevel::CurPlayLevel->GetPlayer()->AddKillCount();
		return;
	}
	else if(BubbleMaster == PlayerNum::P2)
	{
		PlayLevel::CurPlayLevel->GetPlayer2()->AddKillCount();
		return;
	}
	else
	{
		return;
	}
}

void BaseMonster::MoveFix(const bool& _Check1, const bool& _Check2, float _Speed, float _Delta)
{
	if (false == _Check1 && false == _Check2)
	{
		return;
	}
	else if (ActorDir::Down == Dir && true == _Check1 && false == _Check2)
	{
		AddPos(float4::RIGHT * _Speed * _Delta);
	}
	else if (ActorDir::Down == Dir && false == _Check1 && true == _Check2)
	{
		AddPos(float4::LEFT * _Speed * _Delta);
	}

	else if (ActorDir::Up == Dir && true == _Check1 && false == _Check2)
	{
		AddPos(float4::RIGHT * _Speed * _Delta);
	}
	else if (ActorDir::Up == Dir && false == _Check1 && true == _Check2)
	{
		AddPos(float4::LEFT * _Speed * _Delta);
	}

	else if (ActorDir::Left == Dir && true == _Check1 && false == _Check2)
	{
		AddPos(float4::DOWN * _Speed * _Delta);
	}
	else if (ActorDir::Left == Dir && false == _Check1 && true == _Check2)
	{
		AddPos(float4::UP * _Speed * _Delta);
	}

	else if (ActorDir::Right == Dir && true == _Check1 && false == _Check2)
	{
		AddPos(float4::DOWN * _Speed * _Delta);
	}
	else if (ActorDir::Right == Dir && false == _Check1 && true == _Check2)
	{
		AddPos(float4::UP * _Speed * _Delta);
	}
	else
	{
		return;
	}
}

void BaseMonster::CheckMovePattern()
{
	if (true == MonsterMovePattern.empty())
	{
		IsMonsterMovePattern = false;
	}

	else
	{
		IsMonsterMovePattern = true;
	}
}