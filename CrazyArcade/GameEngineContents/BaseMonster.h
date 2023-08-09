#pragma once

#include "ActorEnum.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

#include <string>
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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
	void StateUpdate(float _Delta);
	void ChangeState(MonsterState _State);
	virtual void ChangeAnimationState(const std::string& _StateName);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void Update(float _Delta) override;

	void DirCheck();

	class GameEngineRenderer* MainRenderer = nullptr;

	MonsterState State = MonsterState::Idle;
	ActorDir Dir = ActorDir::Down;
	std::string CurState = "";

private:
};

