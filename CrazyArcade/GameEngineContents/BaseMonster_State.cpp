#include "BaseMonster.h"
#include "PlayLevel.h"
#include "BaseCharacter.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/TileMap.h>

void BaseMonster::IdleStart()
{
	ChangeAnimationState("Idle");
	MainTimer = 0.0f;
}

void BaseMonster::IdleUpdate(float _Delta)
{
	if (MainTimer > 1.0f)
	{
		ChangeState(MonsterState::Move);
		return;
	}

	MainTimer += _Delta;
}

void BaseMonster::MoveStart()
{
	ChangeAnimationState("Move");
	MainTimer = 0.0f;

	CheckMovePattern();
}

void BaseMonster::MoveUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	float4 CheckPos1 = float4::ZERO;
	float4 CheckPos2 = float4::ZERO;
	float Speed = 50.0f;

	CheckDeath();

	CheckPlayerTracking("Move");


	if (Dir == ActorDir::Down)
	{
		MovePos = { 0.0f, Speed * _Delta };
		CheckPos = BOTPOS;
		CheckPos1 = LEFTBOTPOS;
		CheckPos2 = RIGHTBOTPOS;
	}

	if (Dir == ActorDir::Up)
	{
		MovePos = { 0.0f, -Speed * _Delta };
		CheckPos = TOPPOS;
		CheckPos1 = LEFTTOPPOS;
		CheckPos2 = RIGHTTOPPOS;
	}

	if (Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = LEFTPOS;
		CheckPos1 = TOPLEFTPOS;
		CheckPos2 = BOTLEFTPOS;
	}

	if (Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		CheckPos = RIGHTPOS;
		CheckPos1 = TOPRIGHTPOS;
		CheckPos2 = BOTRIGHTPOS;
	}

	CheckPos += GetPos();
	CheckPos1 += GetPos();
	CheckPos2 += GetPos();

	
	bool CheckTile = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos, _Delta);
	bool CheckTile1 = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos1, _Delta);
	bool CheckTile2 = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos2, _Delta);
	

	if (false == CheckTile && false == CheckTile1 && false == CheckTile2)
	{
		AddPos(MovePos);
	}

	// 방향 전환
	else if (true == CheckTile)
	{
		if (true == IsMonsterMovePattern)
		{
			PatternDir("Move");
		}

		else
		{
			RandomDir("Move");
		}
	}

	else
	{
		MoveFix(CheckTile1, CheckTile2, Speed, _Delta);
	}

	// 일정시간 이후 방향 자동전환
	if (MoveTimer > 4.0f)
	{
		MoveTimer = 0.0f;
		RandomDir("Move");
	}

	CheckDeath();
	MoveTimer += _Delta;
}

void BaseMonster::FreezeStart()
{
	ChangeAnimationState("Freeze");
	FreezeTimer = 0.0f;
	MonsterEffectSound = GameEngineSound::SoundPlay("Ice_Monster_Freeze.wav");
	MonsterEffectSound.SetVolume(0.6f);
}

void BaseMonster::FreezeUpdate(float _Delta)
{
	if (FreezeTimer > 3.0f)
	{
		FreezeTimer = 0.0f;
		ChangeState(MonsterState::Anger);
		return;
	}

	std::vector<GameEngineCollision*> Col;
	if (true == MonsterCollision->Collision(CollisionOrder::PlayerBody, Col, CollisionType::Rect, CollisionType::Rect)
		|| true == MonsterCollision->Collision(CollisionOrder::PlayerBody2, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineActor* CurActor = Col[Col.size() - 1]->GetActor();

		BaseCharacter* ColPlayer = dynamic_cast<BaseCharacter*>(CurActor);

		if (CharacterState::Idle == ColPlayer->State
			|| CharacterState::Move == ColPlayer->State)
		{
			ColPlayer->AddKillCount();
			ChangeState(MonsterState::Die);
			MonsterCollision->Off();
			return;
		}
	}

	FreezeTimer += _Delta;
}

void BaseMonster::ReadyStart()
{
	ChangeAnimationState("Ready");
}

void BaseMonster::ReadyUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MonsterState::Idle);
	}
}

void BaseMonster::AngerStart()
{
	ChangeAnimationState("Anger");
	MonsterEffectSound = GameEngineSound::SoundPlay("Ice_Monster_Angry.wav");
	MonsterEffectSound.SetVolume(1.0f);
}

void BaseMonster::AngerUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MonsterState::AngerIdle);
	}
}

void BaseMonster::AngerIdleStart()
{
	ChangeAnimationState("AngerIdle");
	MainTimer = 0.0f;
}

void BaseMonster::AngerIdleUpdate(float _Delta)
{
	if (MainTimer > 0.05f)
	{
		ChangeState(MonsterState::AngerMove);
		return;
	}

	MainTimer += _Delta;
}

void BaseMonster::AngerMoveStart()
{
	ChangeAnimationState("AngerMove");
}

void BaseMonster::AngerMoveUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	float4 CheckPos1 = float4::ZERO;
	float4 CheckPos2 = float4::ZERO;
	float AngerSpeed = 100.0f;

	CheckDeath();

	CheckPlayerTracking("AngerMove");

	// 이동 체크
	if (Dir == ActorDir::Down)
	{
		MovePos = { 0.0f, AngerSpeed * _Delta };
		CheckPos = BOTPOS;
		CheckPos1 = LEFTBOTPOS;
		CheckPos2 = RIGHTBOTPOS;
	}

	if (Dir == ActorDir::Up)
	{
		MovePos = { 0.0f, -AngerSpeed * _Delta };
		CheckPos = TOPPOS;
		CheckPos1 = LEFTTOPPOS;
		CheckPos2 = RIGHTTOPPOS;
	}

	if (Dir == ActorDir::Left)
	{
		MovePos = { -AngerSpeed * _Delta, 0.0f };
		CheckPos = LEFTPOS;
		CheckPos1 = TOPLEFTPOS;
		CheckPos2 = BOTLEFTPOS;
	}

	if (Dir == ActorDir::Right)
	{
		MovePos = { AngerSpeed * _Delta, 0.0f };
		CheckPos = RIGHTPOS;
		CheckPos1 = TOPRIGHTPOS;
		CheckPos2 = BOTRIGHTPOS;
	}

	CheckPos += GetPos();
	CheckPos1 += GetPos();
	CheckPos2 += GetPos();

	bool CheckTile = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos, _Delta);
	bool CheckTile1 = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos1, _Delta);
	bool CheckTile2 = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos2, _Delta);

	if (false == CheckTile && false == CheckTile1 && false == CheckTile2)
	{
		AddPos(MovePos);
	}

	else if (true == CheckTile)
	{
		RandomDir("AngerMove");
	}

	else
	{
		MoveFix(CheckTile1, CheckTile2, AngerSpeed, _Delta);
	}
	
	if (MoveTimer > 4.0f)
	{
		RandomDir("AngerMove");
		MoveTimer = 0.0f;
	}

	MoveTimer += _Delta;
}

void BaseMonster::EggSummonStart()
{
	ChangeAnimationState("EggSummon");

	EggSummonStartPos = { GetPos().X, GetPos().Y - 200.0f };
	EggSummonEndPos = GetPos();

	MainTimer = 0.0f;
}

void BaseMonster::EggSummonUpdate(float _Delta)
{
	if (MainTimer < 1.0f)
	{
		MainTimer += _Delta * 2.0f;
		SetPos(float4::ZERO.LerpClimp(EggSummonStartPos, EggSummonEndPos, MainTimer));
	}

	else
	{
		ChangeState(MonsterState::EggIdle);
	}
}

void BaseMonster::EggIdleStart()
{
	ChangeAnimationState("EggIdle");
}

void BaseMonster::EggIdleUpdate(float _Delta)
{
	if (MainTimer > 2.0f)
	{
		ChangeState(MonsterState::EggMove);
		return;
	}

	MainTimer += _Delta;
}

void BaseMonster::EggMoveStart()
{
	ChangeAnimationState("EggMove");
	MainTimer = 0.0f;
}

void BaseMonster::EggMoveUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	float4 CheckPos1 = float4::ZERO;
	float4 CheckPos2 = float4::ZERO;
	float EggSpeed = 30.0f;

	CheckDeath();

	CheckPlayerTracking("EggMove");

	if (Dir == ActorDir::Down)
	{
		MovePos = { 0.0f, EggSpeed * _Delta };
		CheckPos = BOTPOS;
		CheckPos1 = LEFTBOTPOS;
		CheckPos2 = RIGHTBOTPOS;

	}

	if (Dir == ActorDir::Up)
	{
		MovePos = { 0.0f, -EggSpeed * _Delta };
		CheckPos = TOPPOS;
		CheckPos1 = LEFTTOPPOS;
		CheckPos2 = RIGHTTOPPOS;
	}

	if (Dir == ActorDir::Left)
	{
		MovePos = { -EggSpeed * _Delta, 0.0f };
		CheckPos = LEFTPOS;
		CheckPos1 = TOPLEFTPOS;
		CheckPos2 = BOTLEFTPOS;
	}

	if (Dir == ActorDir::Right)
	{
		MovePos = { EggSpeed * _Delta, 0.0f };
		CheckPos = RIGHTPOS;
		CheckPos1 = TOPRIGHTPOS;
		CheckPos2 = BOTRIGHTPOS;
	}

	CheckPos += GetPos();
	CheckPos1 += GetPos();
	CheckPos2 += GetPos();

	bool CheckTile = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos, _Delta);
	bool CheckTile1 = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos1, _Delta);
	bool CheckTile2 = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos2, _Delta);

	if (false == CheckTile && false == CheckTile1 && false == CheckTile2)
	{
		AddPos(MovePos);
	}

	// 방향 전환
	else if (true == CheckTile)
	{
		RandomDir("EggMove");
	}

	else
	{
		MoveFix(CheckTile1, CheckTile2, EggSpeed, _Delta);
	}

	// Egg Hatch
	if (MainTimer > 5.0f)
	{
		ChangeState(MonsterState::EggHatch);
	}

	MainTimer += _Delta;
}

void BaseMonster::EggHatchStart()
{
	ChangeAnimationState("EggHatch");
	MonsterEffectSound = GameEngineSound::SoundPlay("Hatching_Egg2.wav");
	MonsterEffectSound.SetVolume(1.0f);
}

void BaseMonster::EggHatchUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MonsterState::Idle);
	}
}

void BaseMonster::EggDeathStart()
{
	ChangeAnimationState("EggDeath");
	MonsterEffectSound = GameEngineSound::SoundPlay("Pirate_Monster_Death.wav");
	MonsterEffectSound.SetVolume(1.0f);
}

void BaseMonster::EggDeathUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		Death();
		PlayLevel::CurPlayLevel->MonsterListDelete();
		return;
	}
}

void BaseMonster::DieStart()
{
	ChangeAnimationState("Die");
	MonsterEffectSound = GameEngineSound::SoundPlay("Ice_Monster_Death.wav");
	if (true == IsDeathSound)
	{
		MonsterEffectSound.SetVolume(0.6f);
	}
	else
	{
		MonsterEffectSound.SetVolume(0.0f);
	}
}

void BaseMonster::DieUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		Death();
		PlayLevel::CurPlayLevel->MonsterListDelete();
		return;
	}
}