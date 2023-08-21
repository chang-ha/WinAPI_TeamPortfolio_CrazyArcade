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
}

void BaseMonster::MoveUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	float Speed = 50.0f;

	CheckDeath();

	//if (nullptr != PlayLevel::CurPlayLevel->Player)
	//{
	//	// 플레이어 위치 체크
	//	float4 PlayerPos = PlayLevel::CurPlayLevel->Player->GetPos();
	//	float4 PlayerIndex = PlayLevel::CurPlayLevel->GetGroundTile()->PosToIndex(PlayerPos - GlobalValue::TileStartPos);

	//	float4 MonsterPos = GetPos() - float4{0,30.0f};
	//	float4 MonsterIndex = PlayLevel::CurPlayLevel->GetGroundTile()->PosToIndex(MonsterPos - GlobalValue::TileStartPos - GlobalValue::MapTileSize.Half());
	//	checkplayerdur -= _Delta;
	//	if (5.0f< (PlayerPos - MonsterPos).Size() && (PlayerPos - MonsterPos).Size() < 120.0f && checkplayerdur<0)
	//	{
	//		// 따라와야함
	//		float4 TmpDir = PlayerPos - MonsterPos;
	//		if (abs(TmpDir.X) > abs(TmpDir.Y))
	//		{
	//			if (TmpDir.X > 0)
	//			{
	//				Dir = ActorDir::Right;
	//			}
	//			else
	//			{
	//				Dir = ActorDir::Left;
	//			}
	//		}
	//		else
	//		{
	//			if (TmpDir.Y > 0)
	//			{
	//				Dir = ActorDir::Down;
	//			}
	//			else
	//			{
	//				Dir = ActorDir::Up;
	//			}
	//		}
	//		ChangeAnimationState("Move");
	//		checkplayerdur = 0.2f;
	//	}
	//}

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
}

void BaseMonster::FreezeStart()
{
	ChangeAnimationState("Freeze");
	FreezeTimer = 0.0f;
	MonsterEffectSound = GameEngineSound::SoundPlay("Ice_Monster_Freeze.wav");
	MonsterEffectSound.SetVolume(1.0f);
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
			ChangeState(MonsterState::Die);
			MonsterCollision->Off();
			return;
		}
	}

	FreezeTimer += _Delta;
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
	MainTimer = 0.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;
	float AngerSpeed = 100.0f;

	CheckDeath();

	// 이동 체크
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
	float EggSpeed = 30.0f;

	CheckDeath();

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
		MonsterEffectSound.SetVolume(1.0f);
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