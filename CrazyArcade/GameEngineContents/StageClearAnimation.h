#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <string>
#include <vector>


enum class StageClearState
{
	UpperStringDown,
	DownStringAppear,
	Max,
};



// 설명 :
class StageClearAnimation : public GameEngineActor
{
public:
	// constrcuter destructer
	StageClearAnimation();
	~StageClearAnimation();

	// delete Function
	StageClearAnimation(const StageClearAnimation& _Other) = delete;
	StageClearAnimation(StageClearAnimation&& _Other) noexcept = delete;
	StageClearAnimation& operator=(const StageClearAnimation& _Other) = delete;
	StageClearAnimation& operator=(StageClearAnimation&& _Other) noexcept = delete;


	void initStartAnimation(int _StageNumber);

	void ActorRelease();


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;

	// GameEngineActor 상속
	void LevelEnd() override;


	// this
	int m_StageNumber = 0;

	void loadStringTexture();

	void initUpperString();
	std::vector<class StringAnimation*> vecUpperString;
	const int CONST_UpperStringCount = 6;
	const float CONST_UpperStringXStartPos = 210.0f;
	const float CONST_UpperStringYStartPos = 32.0f;

	const std::vector<float> CONST_vecUpperXPos =
	{
		19.0f,
		58.0f,
		97.0f,
		141.0f,
		182.0f,
		240.0f
	};

	void initLowerString();
	std::vector<class StringAnimation*> vecLowerString;
	const int CONST_LowerStringCount = 6;
	const float CONST_LowerStringXStartPos = 138.0f;
	const float CONST_LowerAppearYPos = 114.0f;

	const std::vector<float> CONST_vecLowerXPos =
	{
		32.0f,
		85.0f,
		139.0f,
		212.0f,
		279.0f,
		339.0f
	};


	StageClearState m_State = StageClearState::Max;

	void UpdateState(float _Delta);
	float CONST_StringSpeed = 2000.0f;

	void UpdateUpperStringDown(float _Delta);
	int m_MoveNumber = 0;
	float StateTime = 0.0f;

	const float CONST_NextMoveTime = 0.18f;
	const float CONST_UpperStopYPos = 53.0f;


	void UpdateLowerStringAppear(float _Delta);
	bool AppearLowerStringValue = false;
};

