#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <string>
#include <vector>



enum class StageLoseState
{
	AppearString,
	SparkleString,
	Max,
};


// 설명 :
class LoseAnimation : public GameEngineActor
{
public:
	// constrcuter destructer
	LoseAnimation();
	~LoseAnimation();

	// delete Function
	LoseAnimation(const LoseAnimation& _Other) = delete;
	LoseAnimation(LoseAnimation&& _Other) noexcept = delete;
	LoseAnimation& operator=(const LoseAnimation& _Other) = delete;
	LoseAnimation& operator=(LoseAnimation&& _Other) noexcept = delete;


	void initLoseAnimation();

	void ActorRelease();


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;

	// GameEngineActor 상속
	void LevelEnd() override;


	// this
	void loadStringSprite();

	void initLoseString();
	std::vector<GameEngineRenderer*> vecLoseRenderer;
	const int CONST_LoseStringCount = 5;
	const float CONST_LoseStringXStartPos = 173.0f;
	const float CONST_LoseStringYStartPos = 74.0f;

	const std::vector<float> CONST_vecLoseXPos =
	{
		32.0f,
		103.0f,
		174.0f,
		243.0f,
		308.0f,
	};

	StageLoseState m_State = StageLoseState::Max;

	void UpdateState(float _Delta);
	float StateTime = 0.0f;

	void UpdateAppearString(float _Delta);
	int m_AppearNumber = 0;

	const float CONST_NextAppearString = 0.18f;

	void UpdateFrinkleString(float _Delta);
	bool FrinkleStringCheckValue = false;

};