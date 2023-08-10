#pragma once

#include "ActorEnum.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

#include <string>
#include <GameEngineCore/GameEngineActor.h>

#define TOPCHECKPOS { 0.0f, -15.0f }
//#define LEFTTOPCHECKPOS { -16.0f, -15.0f }
//#define RIGHTTOPCHECKPOS { 16.0f, -15.0f }


#define LEFTCHECKPOS { -20.0f, 5.0f }
//#define LEFTMOVETOPCHECKPOS { -20.0f, -13.0f }
//#define LEFTMOVEBOTCHECKPOS { -20.0f, 23.0f }

#define RIGHTCHECKPOS { 20.0f, 5.0f }
//#define RIGHTMOVETOPCHECKPOS { 20.0f, -13.0f }
//#define RIGHTMOVEBOTCHECKPOS { 20.0f, 23.0f }

#define BOTCHECKPOS { 0.0f, 25.0f }
//#define LEFTBOTCHECKPOS { -16.0f, 25.0f }
//#define RIGHTBOTCHECKPOS { 16.0f, 25.0f }

// Ό³Έν :
class BaseMonster : public GameEngineActor
{
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

	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void DirCheck();

	class GameEngineRenderer* MainRenderer = nullptr;
	class GameEngineRenderer* ShadowRenderer = nullptr;

	MonsterState State = MonsterState::Idle;
	ActorDir Dir = ActorDir::Down;
	std::string CurState = "";

	float Speed = 30.0f;

	TileObjectOrder CurTile = TileObjectOrder::Empty;

private:
};

