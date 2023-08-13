#include "BaseCharacter.h"
#include "PlayLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>

// 물풍선에 맞았을 경우
void BaseCharacter::BubbleHitStart()
{
	ChangeAnimationState("BubbleHit");
}
void BaseCharacter::BubbleHitUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(CharacterState::Bubble);
		return;
	}
}

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

	if (5.0f < BubbleTimer)
	{
		BubbleTimer = 0.0f;
		ChangeState(CharacterState::BubbleEnd);
		return;
	}

	BubbleTimer += _Delta;
}

// 버블이 된 후 시간이 경과했을경우
void BaseCharacter::BubbleEndStart()
{
	ChangeAnimationState("BubbleEnd");
}
void BaseCharacter::BubbleEndUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(CharacterState::Die);
		return;
	}
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
		ShadowRenderer->Off();
		PlayerDeath = true;

		if (true == GameEngineInput::IsDown('R'))
		{
			ShadowRenderer->On();
			PlayerDeath = false;
			ChangeState(CharacterState::Ready);
			return;
		}
	}
}