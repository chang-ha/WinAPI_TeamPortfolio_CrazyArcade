#pragma once

#include "ActorEnum.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

#include <string>
#include <GameEngineCore/GameEngineActor.h>

#define TOPPOS { 0.0f, 0.0f }
//#define LEFTTOPCHECKPOS { -16.0f, -15.0f }
//#define RIGHTTOPCHECKPOS { 16.0f, -15.0f }


#define LEFTPOS { -20.0f, 20.0f }
//#define LEFTMOVETOPCHECKPOS { -20.0f, -13.0f }
//#define LEFTMOVEBOTCHECKPOS { -20.0f, 23.0f }

#define RIGHTPOS { 20.0f, 20.0f }
//#define RIGHTMOVETOPCHECKPOS { 20.0f, -13.0f }
//#define RIGHTMOVEBOTCHECKPOS { 20.0f, 23.0f }

#define BOTPOS { 0.0f, 40.0f }
//#define LEFTBOTCHECKPOS { -16.0f, 25.0f }
//#define RIGHTBOTCHECKPOS { 16.0f, 25.0f }

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

protected:
	virtual void StateUpdate(float _Delta);
	virtual void ChangeState(MonsterState _State);
	virtual void ChangeAnimationState(const std::string& _StateName);

	class GameEngineRenderer* MainRenderer = nullptr;
	class GameEngineRenderer* ShadowRenderer = nullptr;
	class PlayLevel* CurPlayLevel = nullptr;
	const class TileMap* CurTile = nullptr;

	float Speed = 50.0f;
	MonsterState State = MonsterState::Idle;
	ActorDir Dir = ActorDir::Down;
	std::string CurState = "";
	TileObjectOrder CurTileType = TileObjectOrder::Empty;

	void SwitchDebugData()
	{
		IsDebugData = !IsDebugData;
	}

private:
	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void DirCheck();

	bool IsDebugData = false;
};

