#pragma once

#include "ActorEnum.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

#include <string>
#include <GameEngineCore/GameEngineActor.h>

#define TOPPOS { 0.0f, 0.0f }
#define LEFTPOS { -20.0f, 20.0f }
#define RIGHTPOS { 20.0f, 20.0f }
#define BOTPOS { 0.0f, 40.0f }

#define MONSTERCOLLISIONSCALE { 30.0f, 30.0f }

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

protected:
	virtual void StateUpdate(float _Delta);
	virtual void ChangeState(MonsterState _State);
	virtual void ChangeAnimationState(const std::string& _StateName);

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

	void SwitchDebugData()
	{
		IsDebugData = !IsDebugData;
	}
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void CheckCollision();

private:
	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void FreezeStart();
	void FreezeUpdate(float _Delta);

	void DieStart();
	void DieUpdate(float _Delta);

	void AngerStart();
	void AngerUpdate(float _Delta);

	void AngerIdleStart();
	void AngerIdleUpdate(float _Delta);

	void AngerMoveStart();
	void AngerMoveUpdate(float _Delta);

	void EggIdleStart();
	void EggIdleUpdate(float _Delta);

	void EggMoveStart();
	void EggMoveUpdate(float _Delta);

	void EggSummonStart();
	void EggSummonUpdate(float _Delta);

	void EggDeathStart();
	void EggDeathUpdate(float _Delta);

	bool IsDebugData = false;

	float Speed = 50.0f;
	float AngerSpeed = 100.0f;

	float IdleTimer = 0.0f;
	float MoveTimer = 0.0f;
	float FreezeTimer = 0.0f;
	float AngerIdleTimer = 0.0f;
};

