#pragma once

#define TOPCHECKPOS { 0.0f, -10.0f }
#define LEFTTOPCHECKPOS { -16.0f, -10.0f }
#define RIGHTTOPCHECKPOS { 16.0f, -10.0f }


#define LEFTCHECKPOS { -20.0f, 10.0f }
#define LEFTMOVETOPCHECKPOS { -20.0f, -8.0f }
#define LEFTMOVEBOTCHECKPOS { -20.0f, 28.0f }

#define RIGHTCHECKPOS { 20.0f, 10.0f }
#define RIGHTMOVETOPCHECKPOS { 20.0f, -8.0f }
#define RIGHTMOVEBOTCHECKPOS { 20.0f, 28.0f }

#define BOTCHECKPOS { 0.0f, 30.0f }
#define LEFTBOTCHECKPOS { -16.0f, 30.0f }
#define RIGHTBOTCHECKPOS { 16.0f, 30.0f }

#define CHARACTERCOLLISIONPOS { 0.0f, 5.0f }

#define SETBUBBLEPOS { 0.0f, 15.0f }

#define CHARACTERSHADOWPOS { 0.0f, 15.0f }

#define FOOTPOS { 0.0f, 25.0f }

#define SPEEDREFERENCEVALUE 40.0f

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

	void GetItem(const ItemType& _ItemType);

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

	virtual float GetSpeed()
	{
		return Speed;
	}

	virtual int GetBombPower()
	{
		return BombPower;
	}

	virtual int GetBombCount()
	{
		return BombCount;
	}

	virtual void BombCountPlus() {}
	virtual void BombCountMinus() {}

	virtual void BombPowerPlus() {}
	virtual void ChangeMaxBombPower() {}

	virtual void SpeedUp() {}
	virtual void ChangeMaxSpeed() {}

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
		++NeedleCount;
	}

	int GetNeedle() const
	{
		return NeedleCount;
	}

	bool GetNoDamage() const
	{
		return NoDamage;
	}

protected:
	ActorDir Dir = ActorDir::Down;
	float Speed = 0.0f;
	int BombPower = 1;
	int BombCount = 1;
	int NeedleCount = 0;

	float BubbleTimer = 0.0f;

	int GetItemCount = 0;

	TileObjectOrder CurTile = TileObjectOrder::Empty;

	PlayerNum PlayerNumber = PlayerNum::P1;

	void DirCheck();

	std::vector<GameEngineCollision*> Col;

	GameEngineSoundPlayer EffectPlayer;

	void NoDamageSwitch()
	{
		NoDamage = !NoDamage;
	}

private:
	bool IsDebugData = false;
	bool PlayerDeath = false;
	bool NoDamage = false;
};

