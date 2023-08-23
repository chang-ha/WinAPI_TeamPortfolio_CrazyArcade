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

		Data.Pos = GetPos() + float4 TOPPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 BOTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 LEFTPOS;
		Data.Scale = { 3, 3 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = GetPos() + float4 RIGHTPOS;
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
	}

	else if (CurTileType == TileObjectOrder::PopRange)
	{
		ChangeState(MonsterState::Freeze);
	}
}

void BaseMonster::ChangeAnimationState(const std::string& _StateName) 
{

}

void BaseMonster::KillCountPlus()
{
	PlayerNum BubbleMaster = PlayLevel::CurPlayLevel->GetCurTileMaster(GetPos() + float4 CENTERPOS);

	if (BubbleMaster == PlayerNum::P1)
	{
		PlayLevel::CurPlayLevel->GetPlayer()->AddKillCount();
	}
	else
	{
		PlayLevel::CurPlayLevel->GetPlayer2()->AddKillCount();
	}
}