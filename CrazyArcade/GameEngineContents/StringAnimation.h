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
class StringAnimation : public GameEngineActor
{
public:
	// constrcuter destructer
	StringAnimation();
	~StringAnimation();

	// delete Function
	StringAnimation(const StringAnimation& _Other) = delete;
	StringAnimation(StringAnimation&& _Other) noexcept = delete;
	StringAnimation& operator=(const StringAnimation& _Other) = delete;
	StringAnimation& operator=(StringAnimation&& _Other) noexcept = delete;


	void setTexture(const std::string& _FileName);
	GameEngineRenderer* getRenderer() const
	{
		return Renderer;
	}

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

	void ActorRelease();

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
