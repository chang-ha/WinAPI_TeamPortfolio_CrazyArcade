#include "BaseCharacter.h"
#include "PlayLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>

void BaseCharacter::BubbleStart()
{
	ChangeAnimationState("Bubble");
}
void BaseCharacter::BubbleUpdate(float _Delta)
{
	static float BubbleTimer = 0.0f;

	if (true == GameEngineInput::IsDown(VK_CONTROL))
	{
		BubbleTimer = 0.0f;
		ChangeState(CharacterState::Live);
		return;
	}

	if (3.0f < BubbleTimer)
	{
		BubbleTimer = 0.0f;
		ChangeState(CharacterState::Die);
		return;
	}

	BubbleTimer += _Delta;
}


void BaseCharacter::FlashLongStart()
{
	ChangeAnimationState("FlashLong");
}
void BaseCharacter::FlashLongUpdate(float _Delta)
{
	static float FlashLongTimer = 0.0f;

	if (FlashLongTimer > 1.0f)
	{
		FlashLongTimer = 0.0f;
		Dir = ActorDir::Down;
		ChangeState(CharacterState::Idle);
		return;
	}

	FlashLongTimer += _Delta;
}


void BaseCharacter::FlashShortStart()
{
	ChangeAnimationState("FlashShort");
}
void BaseCharacter::FlashShortUpdate(float _Delta)
{
	static float FlashShortTimer = 0.0f;

	if (FlashShortTimer > 1.0f)
	{
		FlashShortTimer = 0.0f;
		Dir = ActorDir::Down;
		ChangeState(CharacterState::Idle);
		return;
	}

	FlashShortTimer += _Delta;
}


void BaseCharacter::LiveStart()
{
	ChangeAnimationState("Live");
}
void BaseCharacter::LiveUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(CharacterState::FlashShort);
		return;
	}
}


void BaseCharacter::DieStart()
{
	ChangeAnimationState("Die");
}
void BaseCharacter::DieUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(CharacterState::Max);
		return;
	}
}