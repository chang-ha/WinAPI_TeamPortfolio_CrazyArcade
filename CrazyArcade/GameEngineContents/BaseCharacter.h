#pragma once

#define TOPCHECKPOS { 0.0f, -15.0f }
#define LEFTTOPCHECKPOS { -16.0f, -15.0f }
#define RIGHTTOPCHECKPOS { 16.0f, -15.0f }


#define LEFTCHECKPOS { -20.0f, 5.0f }
#define LEFTMOVETOPCHECKPOS { -20.0f, -13.0f }
#define LEFTMOVEBOTCHECKPOS { -20.0f, 23.0f }

#define RIGHTCHECKPOS { 20.0f, 5.0f }
#define RIGHTMOVETOPCHECKPOS { 20.0f, -13.0f }
#define RIGHTMOVEBOTCHECKPOS { 20.0f, 23.0f }

#define BOTCHECKPOS { 0.0f, 25.0f }
#define LEFTBOTCHECKPOS { -16.0f, 25.0f }
#define RIGHTBOTCHECKPOS { 16.0f, 25.0f }

#include "ActorEnum.h"
#include "ContentsEnum.h"

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

	virtual int GetBubblePower()
	{
		return BubblePower;
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
	float Speed = 200.0f;
	int BubblePower = 1;

	void DirCheck();
	void SetBubble();

private:
	bool IsDebugData = false;
};

