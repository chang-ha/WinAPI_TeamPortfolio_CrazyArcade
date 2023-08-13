#include "BaseMonster.h"
#include "PlayLevel.h"

#include <GameEngineCore/GameEngineRenderer.h>

void BaseMonster::IdleStart()
{
	ChangeAnimationState("Idle");
	IdleTimer = 0.0f;
}

void BaseMonster::IdleUpdate(float _Delta)
{
	if (IdleTimer > 2.0f)
	{
		ChangeState(MonsterState::Move);
		return;
	}

	IdleTimer += _Delta;
}

void BaseMonster::MoveStart()
{
	ChangeAnimationState("Move");
	MoveTimer = 0.0f;
}

void BaseMonster::MoveUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;


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

	MoveTimer += _Delta;
}

void BaseMonster::FreezeStart()
{
	ChangeAnimationState("Freeze");
	FreezeTimer = 0.0f;
}

void BaseMonster::FreezeUpdate(float _Delta)
{
	//ChangeState(MonsterState::Freeze);

	if (FreezeTimer > 3.0f)
	{
		FreezeTimer = 0.0f;
		ChangeState(MonsterState::Anger);
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
	AngerIdleTimer = 0.0f;
}

void BaseMonster::AngerIdleUpdate(float _Delta)
{
	if (AngerIdleTimer > 1.0f)
	{
		ChangeState(MonsterState::AngerMove);
		return;
	}

	AngerIdleTimer += _Delta;
}

void BaseMonster::AngerMoveStart()
{
	ChangeAnimationState("AngerMove");
}

void BaseMonster::AngerMoveUpdate(float _Delta)
{
	static float MoveTimer = 0.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

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

	MoveTimer += _Delta;
}

void BaseMonster::EggIdleStart()
{
	ChangeAnimationState("EggIdle");
}

void BaseMonster::EggIdleUpdate(float _Delta)
{

}

void BaseMonster::EggMoveStart()
{
	ChangeAnimationState("EggMove");
}

void BaseMonster::EggMoveUpdate(float _Delta)
{

}

void BaseMonster::EggSummonStart()
{
	ChangeAnimationState("EggSummon");
}

void BaseMonster::EggSummonUpdate(float _Delta)
{

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
	ChangeState(MonsterState::Die);
}