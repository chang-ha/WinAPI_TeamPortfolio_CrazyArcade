#pragma once

#include "ActorEnum.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

#include <string>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineActor.h>

#define LEFTTOPPOS { -16.0f, 0.0f }
#define TOPPOS { 0.0f, 0.0f }
#define RIGHTTOPPOS { 16.0f, 0.0f }

#define TOPLEFTPOS { -20.0f, 4.0f }
#define LEFTPOS { -20.0f, 20.0f }
#define BOTLEFTPOS { -20.0f, 36.0f }

#define TOPRIGHTPOS { 20.0f, 4.0f }
#define RIGHTPOS { 20.0f, 20.0f }
#define BOTRIGHTPOS { 20.0f, 36.0f }

#define LEFTBOTPOS { -16.0f, 40.0f }
#define BOTPOS { 0.0f, 40.0f }
#define RIGHTBOTPOS { 16.0f, 40.0f }

#define CENTERPOS { 0.0f, 20.0f }

#define MONSTERCOLLISIONSCALE { 20.0f, 10.0f }

// Ό³Έν :
class BaseMonster : public GameEngineActor
{
	friend class PlayLevel;
public:
	// constrcuter destructer
	BaseMonster();
	~BaseMonster();

	// delete Function
	BaseMonster(const BaseMonster& _Other) = delete;
	BaseMonster(BaseMonster&& _Other) noexcept = delete;
	BaseMonster& operator=(const BaseMonster& _Other) = delete;
	BaseMonster& operator=(BaseMonster&& _Other) noexcept = delete;

	void RandomDir(const std::string& _StateName);

	void SetState(MonsterState _State)
	{
		ChangeState(_State);
	}

	void DeathSoundOff()
	{
		IsDeathSound = false;
	}

	inline MonsterState GetState()
	{
		return State;
	}

protected:
	virtual void StateUpdate(float _Delta);
	virtual void ChangeState(MonsterState _State);
	virtual void ChangeAnimationState(const std::string& _StateName);
	void MoveFix(const bool& _Point1, const bool& _Point2, float _Speed, float _Delta);

	class GameEngineRenderer* MainRenderer = nullptr;
	class GameEngineRenderer* ShadowRenderer = nullptr;

	class GameEngineCollision* MonsterCollision = nullptr;
	class GameEngineCollision* IceCollision = nullptr;

	class PlayLevel* CurPlayLevel = nullptr;
	const class TileMap* CurTile = nullptr;

	MonsterState State = MonsterState::Idle;
	ActorDir Dir = ActorDir::Down;
	std::string CurState = "";
	TileObjectOrder CurTileType = TileObjectOrder::Empty;

	TileMap* CurLevelTile = nullptr;
	std::vector<float4> TrackingTiles;

	void TrackingTileUpdate();
	void CheckPlayerTracking(const std::string& _State);

	void SwitchDebugData()
	{
		IsDebugData = !IsDebugData;
	}
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void CheckCollision();

	GameEngineSoundPlayer MonsterEffectSound;

	bool IsDebugData = false;
	bool IsDeathSound = true;

	void KillCountPlus();

private:
	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	virtual void MoveUpdate(float _Delta);

	void FreezeStart();
	void FreezeUpdate(float _Delta);

	virtual void DieStart();
	void DieUpdate(float _Delta);

	void AngerStart();
	void AngerUpdate(float _Delta);

	void AngerIdleStart();
	void AngerIdleUpdate(float _Delta);

	void AngerMoveStart();
	void AngerMoveUpdate(float _Delta);

	void EggSummonStart();
	void EggSummonUpdate(float _Delta);

	void EggIdleStart();
	void EggIdleUpdate(float _Delta);

	void EggMoveStart();
	void EggMoveUpdate(float _Delta);

	void EggHatchStart();
	void EggHatchUpdate(float _Delta);

	void EggDeathStart();
	void EggDeathUpdate(float _Delta);

	void CheckDeath();

	float MainTimer = 0.0f;
	float FreezeTimer = 0.0f;
	float MoveTimer = 0.0f;

	float4 EggSummonStartPos = float4::ZERO;
	float4 EggSummonEndPos = float4::ZERO;

	float checkplayerdur = 1.0f;
};

