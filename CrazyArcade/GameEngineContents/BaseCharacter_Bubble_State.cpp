#include "BaseCharacter.h"
#include "PlayLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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
	EffectPlayer = GameEngineSound::SoundPlay("Locked_In_Bubble2.wav");
	EffectPlayer.SetVolume(1.0f);
}
void BaseCharacter::BubbleUpdate(float _Delta)
{
	static float BubbleTimer = 0.0f;

	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody, Col, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineActor* CurActor = Col[Col.size() - 1]->GetActor();
		BaseCharacter* ColCharacter = dynamic_cast<BaseCharacter*>(CurActor);

		PlayerNum ColPlayerNumber = ColCharacter->GetPlayerNumber();

		if (ColPlayerNumber != PlayerNumber)
		{
			ChangeState(CharacterState::Live);
			return;
		}
		
	}

	if (true == GameEngineInput::IsDown(VK_CONTROL) && NeedleCount > 0)
	{
		BubbleTimer = 0.0f;
		--NeedleCount;
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
	BodyCollision->Off();
	ChangeAnimationState("Live");
}
void BaseCharacter::LiveUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		BodyCollision->On();
		ChangeState(CharacterState::Idle);
		return;
	}
}


void BaseCharacter::DieStart()
{
	BodyCollision->Off();
	ChangeAnimationState("Die");
	EffectPlayer = GameEngineSound::SoundPlay("Character_Death.wav");
	EffectPlayer.SetVolume(1.0f);
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
			BodyCollision->On();
			PlayerDeath = false;
			ChangeState(CharacterState::Ready);
			return;
		}
	}
}