#include "BaseCharacter.h"
#include "PlayLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

// 물풍선에 맞았을 경우
void BaseCharacter::BubbleHitStart()
{
	ChangeAnimationState("BubbleHit");
	EffectPlayer = GameEngineSound::SoundPlay("Locked_In_Bubble.wav");
	EffectPlayer.SetVolume(1.0f);
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
	DirCheck();

	//버블상태에서 움직임
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	float MoveSpeed = SPEEDREFERENCEVALUE;

	if (PlayerNumber == PlayerNum::P1)
	{
		if (ActorDir::Up == Dir && GameEngineInput::IsDown('W')
			|| ActorDir::Up == Dir && GameEngineInput::IsPress('W'))
		{
			MovePos = float4::UP * MoveSpeed * _Delta;
			CheckPos = TOPCHECKPOS;
		}
		else if (ActorDir::Down == Dir && GameEngineInput::IsDown('S')
			|| ActorDir::Down == Dir && GameEngineInput::IsPress('S'))
		{
			MovePos = float4::DOWN * MoveSpeed * _Delta;
			CheckPos = BOTCHECKPOS;
		}
		else if (ActorDir::Left == Dir && GameEngineInput::IsDown('A')
			|| ActorDir::Left == Dir && GameEngineInput::IsPress('A'))
		{
			MovePos = float4::LEFT * MoveSpeed * _Delta;
			CheckPos = LEFTCHECKPOS;
		}
		else if (ActorDir::Right == Dir && GameEngineInput::IsDown('D')
			|| ActorDir::Right == Dir && GameEngineInput::IsPress('D'))
		{
			MovePos = float4::RIGHT * MoveSpeed * _Delta;
			CheckPos = RIGHTCHECKPOS;
		}
	}

	if (PlayerNumber == PlayerNum::P2)
	{
		if (ActorDir::Up == Dir && GameEngineInput::IsDown(VK_UP)
			|| ActorDir::Up == Dir && GameEngineInput::IsPress(VK_UP))
		{
			MovePos = float4::UP * MoveSpeed * _Delta;
			CheckPos = TOPCHECKPOS;
		}
		else if (ActorDir::Down == Dir && GameEngineInput::IsDown(VK_DOWN)
			|| ActorDir::Down == Dir && GameEngineInput::IsPress(VK_DOWN))
		{
			MovePos = float4::DOWN * MoveSpeed * _Delta;
			CheckPos = BOTCHECKPOS;
		}
		else if (ActorDir::Left == Dir && GameEngineInput::IsDown(VK_LEFT)
			|| ActorDir::Left == Dir && GameEngineInput::IsPress(VK_LEFT))
		{
			MovePos = float4::LEFT * MoveSpeed * _Delta;
			CheckPos = LEFTCHECKPOS;
		}
		else if (ActorDir::Right == Dir && GameEngineInput::IsDown(VK_RIGHT)
			|| ActorDir::Right == Dir && GameEngineInput::IsPress(VK_RIGHT))
		{
			MovePos = float4::RIGHT * MoveSpeed * _Delta;
			CheckPos = RIGHTCHECKPOS;
		}
	}

	CheckPos += GetPos();

	bool MoveCheck = PlayLevel::CurPlayLevel->CheckSidePos(CheckPos, PlayerNumber);

	if (false == MoveCheck)
	{
		AddPos(MovePos);
	}

	// 아군이 살려줄 경우
	if (PlayerNumber == PlayerNum::P1)
	{
		if (true == BodyCollision->Collision(CollisionOrder::PlayerBody2, Col, CollisionType::Rect, CollisionType::Rect))
		{
			GameEngineActor* ColActor = Col[Col.size() - 1]->GetActor();
			
			BaseCharacter* ColCharacter = dynamic_cast<BaseCharacter*>(ColActor);

			if (nullptr == ColCharacter)
			{
				return;
			}

			std::string ColState = ColCharacter->CurState;

			if ("Idle" == ColState || "Move" == ColState)
			{
				BubbleTimer = 0.0f;
				ColCharacter->AddSaveCount();
				ChangeState(CharacterState::Live);
				return;
			}
		}
	}
	else if (PlayerNumber == PlayerNum::P2)
	{
		if (true == BodyCollision->Collision(CollisionOrder::PlayerBody, Col, CollisionType::Rect, CollisionType::Rect))
		{
			GameEngineActor* ColActor = Col[Col.size() - 1]->GetActor();

			BaseCharacter* ColCharacter = dynamic_cast<BaseCharacter*>(ColActor);

			if (nullptr == ColCharacter)
			{
				return;
			}

			std::string ColState = ColCharacter->CurState;

			if ("Idle" == ColState || "Move" == ColState)
			{
				BubbleTimer = 0.0f;
				ColCharacter->AddSaveCount();
				ChangeState(CharacterState::Live);
				return;
			}
		}
	}

	// 바늘아이템을 먹었을 경우
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
	EffectPlayer = GameEngineSound::SoundPlay("Live.wav");
	EffectPlayer.SetVolume(1.0f);
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
	EffectPlayer.SetVolume(2.0f);
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