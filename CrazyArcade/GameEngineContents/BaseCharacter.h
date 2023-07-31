#pragma once

#define TOPCHECKPOS { 0.0f, -15.0f }
#define LEFTCHECKPOS { -20.0f, 10.0f }
#define RIGHTCHECKPOS { 20.0f, 10.0f }
#define LEFTBOTCHECKPOS { -20.0f, 25.0f }
#define BOTCHECKPOS { 0.0f, 25.0f }
#define RIGHTBOTCHECKPOS { -20.0f, 25.0f }

#include "ActorEnum.h"

#include <string>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class BaseCharacter : public GameEngineActor
{
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

protected:
	void StateUpdate(float _Delta);
	void ChangeState(CharacterState _State);
	virtual void ChangeAnimationState(const std::string& _StateName);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	CharacterState State = CharacterState::Max;
	std::string CurState = "";
	GameEngineRenderer* MainRenderer = nullptr;

	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void SwitchDebugData()
	{
		IsDebugData = !IsDebugData;
	}


protected:
	ActorDir Dir = ActorDir::Down;
	float Speed = 300.0f;

	void DirCheck();
	void SetBubble();

private:
	bool IsDebugData = false;
};

