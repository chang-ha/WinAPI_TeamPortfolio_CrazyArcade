#pragma once

#define LEFTTOPCHECKPOS { -15.0f, -10.0f }
#define TOPCHECKPOS { 0.0f, -10.0f }
#define RIGHTTOPCHECKPOS { 15.0f, -10.0f }


#define LEFTMOVETOPCHECKPOS { -21.0f, -6.0f }
#define LEFTCHECKPOS { -21.0f, 12.0f }
#define LEFTMOVEBOTCHECKPOS { -21.0f, 26.0f }

#define RIGHTMOVETOPCHECKPOS { 21.0f, -6.0f }
#define RIGHTCHECKPOS { 21.0f, 12.0f }
#define RIGHTMOVEBOTCHECKPOS { 21.0f, 26.0f }

#define LEFTBOTCHECKPOS { -15.0f, 34.0f }
#define BOTCHECKPOS { 0.0f, 34.0f }
#define RIGHTBOTCHECKPOS { 15.0f, 34.0f }

#define CHARACTERCOLLISIONPOS { 0.0f, 5.0f }

#define SETBUBBLEPOS { 0.0f, 15.0f }

#define CHARACTERSHADOWPOS { 0.0f, 25.0f }

#define FOOTPOS { 0.0f, 25.0f }

#define SPEEDREFERENCEVALUE 35.0f

#define BODYCOLLISIONSCALE { 30.0f, 30.0f }

#include "ActorEnum.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

#include <string>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEnginePlatform/GameEngineSound.h>

class GameEngineRenderer;
class BaseCharacter : public GameEngineActor
{
	friend class PlayLevel;
	friend class BaseMonster;
public:
	// constrcuter destructer
	BaseCharacter();
	~BaseCharacter();

	// delete Function
	BaseCharacter(const BaseCharacter& _Other) = delete;
	BaseCharacter(BaseCharacter&& _Other) noexcept = delete;
	BaseCharacter& operator=(const BaseCharacter& _Other) = delete;
	BaseCharacter& operator=(BaseCharacter&& _Other) noexcept = delete;

	ActorDir GetDir()
	{
		return Dir;
	}

	CharacterState GetState() const
	{
		return State;
	}

	void GetItem(const ItemType& _ItemType);

	void SwitchChangeReadyToIdle()
	{
		ChangeReadyToIdle = !ChangeReadyToIdle;
	}

protected:
	void StateUpdate(float _Delta);
	void ChangeState(CharacterState _State);
	virtual void ChangeAnimationState(const std::string& _StateName);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void ReadyStart();
	void ReadyUpdate(float _Delta);

	void JumpStart();
	void JumpUpdate(float _Delta);

	void BubbleHitStart();
	void BubbleHitUpdate(float _Delta);

	void BubbleStart();
	void BubbleUpdate(float _Delta);

	void BubbleEndStart();
	void BubbleEndUpdate(float _Delta);

	void FlashLongStart();
	void FlashLongUpdate(float _Delta);

	void FlashShortStart();
	void FlashShortUpdate(float _Delta);

	void LiveStart();
	void LiveUpdate(float _Delta);

	void DieStart();
	void DieUpdate(float _Delta);

	void BossCheck();

protected:
	CharacterState State = CharacterState::Max;
	std::string CurState = "";
	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* ShadowRenderer = nullptr;

	GameEngineCollision* BodyCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void SwitchDebugData()
	{
		IsDebugData = !IsDebugData;
	}

	float GetSpeed()
	{
		return Speed * SPEEDREFERENCEVALUE;
	}

	int GetBombPower()
	{
		return BombPower;
	}

	int GetBombCount()
	{
		return BombCount;
	}

	void BombCountPlus()
	{
		if (BombCount < MaxBombCount)
		{
			++BombCount;
			return;
		}
		else
		{
			return;
		}
	}

	void BombCountMinus()
	{
		--BombCount;
	}

	void BombPowerPlus()
	{
		if (BombPower < MaxBombPower)
		{
			++BombPower;
			return;
		}
		else
		{
			return;
		}
	}

	void ChangeMaxBombPower()
	{
		BombPower = MaxBombPower;
	}

	void SpeedUp()
	{
		if (Speed < MaxSpeed)
		{
			++Speed;
			return;
		}
		else
		{
			return;
		}
	}

	void ChangeMaxSpeed()
	{
		Speed = MaxSpeed;
	}

	virtual bool GetPlayerDeath()
	{
		return PlayerDeath;
	}

	PlayerNum GetPlayerNumber() const
	{
		return PlayerNumber;
	}

	void SetPlayer2();

	void NeedlePlus()
	{
		if (NeedleCount < 1)
		{
			++NeedleCount;
		}
		else
		{
			return;
		}
	}

	int GetNeedle() const
	{
		return NeedleCount;
	}

	bool GetNoDamage() const
	{
		return NoDamage;
	}

	void AddKillCount()
	{
		++KillCount;
	}

	int GetKillCount() const
	{
		return KillCount;
	}

	void AddSaveCount()
	{
		++SaveCount;
	}

	int GetSaveCount() const
	{
		return SaveCount;
	}

protected:
	ActorDir Dir = ActorDir::Down;
	float PassSpeed = 160.0f;

	int NeedleCount = 0;

	int MinSpeed = 1;
	int MaxSpeed = 5;
	int Speed = MinSpeed;

	int MinBombPower = 1;
	int MaxBombPower = 5;
	int BombPower = MinBombPower;

	int MinBombCount = 1;
	int MaxBombCount = 5;
	int BombCount = MinBombCount;

	float BubbleTimer = 0.0f;

	int GetItemCount = 0;

	TileObjectOrder CurTile = TileObjectOrder::Empty;

	PlayerNum PlayerNumber = PlayerNum::P1;

	void DirCheck();

	std::vector<GameEngineCollision*> Col;

	GameEngineSoundPlayer EffectPlayer;

	int KillCount = 0;
	int SaveCount = 0;

	void NoDamageSwitch()
	{
		NoDamage = !NoDamage;
	}

private:
	bool IsDebugData = false;
	bool PlayerDeath = false;
	bool NoDamage = false;
	bool ChangeReadyToIdle = false;
};

