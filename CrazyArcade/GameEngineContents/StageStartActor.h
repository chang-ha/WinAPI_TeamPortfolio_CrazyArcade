#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <string>


enum class StringAniState
{
	Up,
	Down,
	Max,
};


// 설명 :
class StageStartActor : public GameEngineActor
{
public:
	// constrcuter destructer
	StageStartActor();
	~StageStartActor();

	// delete Function
	StageStartActor(const StageStartActor& _Other) = delete;
	StageStartActor(StageStartActor&& _Other) noexcept = delete;
	StageStartActor& operator=(const StageStartActor& _Other) = delete;
	StageStartActor& operator=(StageStartActor&& _Other) noexcept = delete;

	void ActorRelease();

	void setTexture(const std::string& _FileName);
	void setState(StringAniState _State)
	{
		m_State = _State;
	}

	void setSpeed(float _Speed)
	{
		m_Speed = _Speed;
	}

	void setStopYPos(float _YPos)
	{
		m_StopYPos = _YPos;
	}


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;

	
	// this
	GameEngineRenderer* Renderer = nullptr;

	StringAniState m_State = StringAniState::Max;

	float m_Speed = 0.0f;
	float m_StopYPos = 0.0f;
	
	void updateState(float _Delta);
	void updateUpState(float _Delta);

	void updateDownState(float _Delta);

};

