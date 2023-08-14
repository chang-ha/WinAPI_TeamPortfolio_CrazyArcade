#include "BaseMonster.h"
#include "PlayLevel.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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
}

void BaseMonster::MoveUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	float Speed = 50.0f;

	if (Dir == ActorDir::Down)
	{
		MovePos = { 0.0f, Speed * _Delta };
		CheckPos = BOTPOS;
	}

	if (Dir == ActorDir::Up)
	{
		MovePos = { 0.0f, -Speed * _Delta };
		CheckPos = TOPPOS;
	}

	if (Dir == ActorDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		CheckPos = LEFTPOS;
	}

	if (Dir == ActorDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		CheckPos = RIGHTPOS;
	}

	CheckPos += GetPos();

	bool CheckTile = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos, _Delta);

	if (false == CheckTile)
	{
		AddPos(MovePos);
	}

	// 방향 전환
	else if (true == CheckTile)
	{
		RandomDir("Move");
	}

	MainTimer += _Delta;
}

void BaseMonster::FreezeStart()
{
	ChangeAnimationState("Freeze");
	FreezeTimer = 0.0f;
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
	if (true == MonsterCollision->Collision(CollisionOrder::PlayerBody, Col, CollisionType::Rect, CollisionType::Rect))
	{
		ChangeState(MonsterState::Die);
		MonsterCollision->Off();
		return;
	}

	FreezeTimer += _Delta;
}

void BaseMonster::AngerStart()
{
	ChangeAnimationState("Anger");
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
	MainTimer = 0.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	float AngerSpeed = 100.0f;

	if (Dir == ActorDir::Down)
	{
		MovePos = { 0.0f, AngerSpeed * _Delta };
		CheckPos = BOTPOS;
	}

	if (Dir == ActorDir::Up)
	{
		MovePos = { 0.0f, -AngerSpeed * _Delta };
		CheckPos = TOPPOS;
	}

	if (Dir == ActorDir::Left)
	{
		MovePos = { -AngerSpeed * _Delta, 0.0f };
		CheckPos = LEFTPOS;
	}

	if (Dir == ActorDir::Right)
	{
		MovePos = { AngerSpeed * _Delta, 0.0f };
		CheckPos = RIGHTPOS;
	}

	CheckPos += GetPos();

	bool CheckTile = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos, _Delta);

	if (false == CheckTile)
	{
		AddPos(MovePos);
	}

	else if (true == CheckTile)
	{
		RandomDir("AngerMove");
	}

	MainTimer += _Delta;
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
	float EggSpeed = 30.0f;

	if (Dir == ActorDir::Down)
	{
		MovePos = { 0.0f, EggSpeed * _Delta };
		CheckPos = BOTPOS;
	}

	if (Dir == ActorDir::Up)
	{
		MovePos = { 0.0f, -EggSpeed * _Delta };
		CheckPos = TOPPOS;
	}

	if (Dir == ActorDir::Left)
	{
		MovePos = { -EggSpeed * _Delta, 0.0f };
		CheckPos = LEFTPOS;
	}

	if (Dir == ActorDir::Right)
	{
		MovePos = { EggSpeed * _Delta, 0.0f };
		CheckPos = RIGHTPOS;
	}

	CheckPos += GetPos();

	bool CheckTile = PlayLevel::CurPlayLevel->MonsterCheckTile(CheckPos, _Delta);

	if (false == CheckTile)
	{
		AddPos(MovePos);
	}

	// 방향 전환
	else if (true == CheckTile)
	{
		RandomDir("EggMove");
	}

	// Egg Summon
	if (MainTimer > 5.0f)
	{
		ChangeState(MonsterState::EggSummon);
	}

	MainTimer += _Delta;
}

void BaseMonster::EggSummonStart()
{
	ChangeAnimationState("EggSummon");
}

void BaseMonster::EggSummonUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MonsterState::Idle);
	}
}

void BaseMonster::EggDeathStart()
{
	ChangeAnimationState("EggDeath");
}

void BaseMonster::EggDeathUpdate(float _Delta)
{

}

void BaseMonster::DieStart()
{
	ChangeAnimationState("Die");
}

void BaseMonster::DieUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		Death();
		return;
	}
}