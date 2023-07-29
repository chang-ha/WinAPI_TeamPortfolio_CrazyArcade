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

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (ActorDir::Up == Dir && GameEngineInput::IsDown('W')
		|| ActorDir::Up == Dir && GameEngineInput::IsPress('W'))
	{
		MovePos = float4::UP * Speed * _Delta;
		CheckPos = TOPCHECKPOS;
	}
	else if (ActorDir::Down == Dir && GameEngineInput::IsDown('S')
		|| ActorDir::Down == Dir && GameEngineInput::IsPress('S'))
	{
		MovePos = float4::DOWN * Speed * _Delta;
		CheckPos = BOTCHECKPOS;
	}
	else if (ActorDir::Left == Dir && GameEngineInput::IsDown('A')
		|| ActorDir::Left == Dir && GameEngineInput::IsPress('A'))
	{
		MovePos = float4::LEFT * Speed * _Delta;
		CheckPos = LEFTCHECKPOS;
	}
	else if (ActorDir::Right == Dir && GameEngineInput::IsDown('D')
		|| ActorDir::Right == Dir && GameEngineInput::IsPress('D'))
	{
		MovePos = float4::RIGHT * Speed * _Delta;
		CheckPos = RIGHTCHECKPOS;
	}

	CheckPos += GetPos();

	if (false == PlayLevel::CurPlayLevel->CheckTile(CheckPos))
	{
		AddPos(MovePos);
	}

	if (float4::ZERO == MovePos)
	{
		ChangeState(CharacterState::Idle);
		return;
	}
}