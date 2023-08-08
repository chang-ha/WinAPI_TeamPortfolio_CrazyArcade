#include "BaseCharacter.h"
#include "PlayLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>

void BaseCharacter::IdleStart()
{
	ChangeAnimationState("Idle");
}

void BaseCharacter::IdleUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('W') || true == GameEngineInput::IsPress('W')
		|| true == GameEngineInput::IsDown('S') || true == GameEngineInput::IsPress('S')
		|| true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsPress('A')
		|| true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsPress('D'))
	{
		DirCheck();
		ChangeState(CharacterState::Move);
		return;
	}
}

void BaseCharacter::MoveStart()
{
	ChangeAnimationState("Move");
}

void BaseCharacter::MoveUpdate(float _Delta)
{
	DirCheck();

	float MoveSpeed = GetSpeed();

	float4 MovePos = float4::ZERO;
	float4 CheckPos1 = float4::ZERO;
	float4 CheckPos2 = float4::ZERO;
	float4 CheckPos3 = float4::ZERO;

	if (ActorDir::Up == Dir && GameEngineInput::IsDown('W')
		|| ActorDir::Up == Dir && GameEngineInput::IsPress('W'))
	{
		MovePos = float4::UP * MoveSpeed * _Delta;
		CheckPos1 = LEFTTOPCHECKPOS;
		CheckPos2 = TOPCHECKPOS;
		CheckPos3 = RIGHTTOPCHECKPOS;
	}
	else if (ActorDir::Down == Dir && GameEngineInput::IsDown('S')
		|| ActorDir::Down == Dir && GameEngineInput::IsPress('S'))
	{
		MovePos = float4::DOWN * MoveSpeed * _Delta;
		CheckPos1 = LEFTBOTCHECKPOS;
		CheckPos2 = BOTCHECKPOS;
		CheckPos3 = RIGHTBOTCHECKPOS;
	}
	else if (ActorDir::Left == Dir && GameEngineInput::IsDown('A')
		|| ActorDir::Left == Dir && GameEngineInput::IsPress('A'))
	{
		MovePos = float4::LEFT * MoveSpeed * _Delta;
		CheckPos1 = LEFTMOVETOPCHECKPOS;
		CheckPos2 = LEFTCHECKPOS;
		CheckPos3 = LEFTMOVEBOTCHECKPOS;
	}
	else if (ActorDir::Right == Dir && GameEngineInput::IsDown('D')
		|| ActorDir::Right == Dir && GameEngineInput::IsPress('D'))
	{
		MovePos = float4::RIGHT * MoveSpeed * _Delta;
		CheckPos1 = RIGHTMOVETOPCHECKPOS;
		CheckPos2 = RIGHTCHECKPOS;
		CheckPos3 = RIGHTMOVEBOTCHECKPOS;
	}

	CheckPos1 += GetPos();
	CheckPos2 += GetPos();
	CheckPos3 += GetPos();

	bool FirstCheck = PlayLevel::CurPlayLevel->CheckSidePos(CheckPos1);
	bool SecondCheck = PlayLevel::CurPlayLevel->CheckTile(CheckPos2, _Delta);
	bool ThirdCheck = PlayLevel::CurPlayLevel->CheckSidePos(CheckPos3);

	if (false == FirstCheck && false == SecondCheck && false == ThirdCheck)
	{
		AddPos(MovePos);
	}

	else if (ActorDir::Left == Dir && true == FirstCheck && false == SecondCheck && false == ThirdCheck)
	{
		AddPos(float4::DOWN);
	}
	else if (ActorDir::Left == Dir && false == FirstCheck && false == SecondCheck && true == ThirdCheck)
	{
		AddPos(float4::UP);
	}

	else if (ActorDir::Right == Dir && true == FirstCheck && false == SecondCheck && false == ThirdCheck)
	{
		AddPos(float4::DOWN);
	}
	else if (ActorDir::Right == Dir && false == FirstCheck && false == SecondCheck && true == ThirdCheck)
	{
		AddPos(float4::UP);
	}

	else if (ActorDir::Up == Dir && true == FirstCheck && false == SecondCheck && false == ThirdCheck)
	{
		AddPos(float4::RIGHT);
	}
	else if (ActorDir::Up == Dir && false == FirstCheck && false == SecondCheck && true == ThirdCheck)
	{
		AddPos(float4::LEFT);
	}

	else if (ActorDir::Down == Dir && true == FirstCheck && false == SecondCheck && false == ThirdCheck)
	{
		AddPos(float4::RIGHT);
	}
	else if (ActorDir::Down == Dir && false == FirstCheck && false == SecondCheck && true == ThirdCheck)
	{
		AddPos(float4::LEFT);
	}

	if (float4::ZERO == MovePos)
	{
		ChangeState(CharacterState::Idle);
		return;
	}
}