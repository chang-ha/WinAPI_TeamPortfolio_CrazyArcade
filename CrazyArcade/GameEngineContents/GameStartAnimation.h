#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <functional>
#include <string>
#include <vector>


enum class StageStartState
{
	UpperStringDown,
	DownStringAppear,
	GameStart,
	Max,
};


// 설명 :
class GameStartAnimation : public GameEngineActor
{
public:
	// constrcuter destructer
	GameStartAnimation();
	~GameStartAnimation();

	// delete Function
	GameStartAnimation(const GameStartAnimation& _Other) = delete;
	GameStartAnimation(GameStartAnimation&& _Other) noexcept = delete;
	GameStartAnimation& operator=(const GameStartAnimation& _Other) = delete;
	GameStartAnimation& operator=(GameStartAnimation&& _Other) noexcept = delete;

	void initStartAnimation(int _StageNumber);

	template<typename ActorType>
	void setGameStartCallBack(ActorType* _Actor, void(ActorType::* _Func)())
	{
		CallGameStart = std::bind(_Func, _Actor);
	}

protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;


	// this
	int m_StageNumber = 0;

	void loadStringTexture();

	void initUpperString();
	std::vector<class StageStartActor*> vecUpperString;
	const int CONST_UpperStringCount = 6;
	const float CONST_UpperStringXStartPos = 210.0f;
	const float CONST_UpperStringYStartPos = 21.0f;

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
	std::vector<class StageStartActor*> vecLowerString;
	const int CONST_LowerStringCount = 6;
	const float CONST_LowerAppearYPos = 310.0f;
	const float CONST_LowerStringXStartPos = 138.0f;

	const std::vector<float> CONST_vecLowerXPos =
	{
		32.0f,
		85.0f,
		139.0f,
		212.0f,
		279.0f,
		339.0f
	};


	StageStartState m_State = StageStartState::Max;

	void UpdateState(float _Delta);
	float CONST_StringSpeed = 2000.0f;

	void UpdateUpperStringDown(float _Delta);
	int m_MoveNumber = 0;
	float StateTime = 0.0f;

	const float CONST_NextMoveTime = 0.15f;
	const float CONST_UpperStopYPos = 248.0f;


	void UpdateDownStringAppear(float _Delta);
	bool AppearLowerStringValue = false;
	const float CONST_DownStringAppearStateDuration = 1.0f;

	void setDownStringAppear();
	const float CONST_StringYScale = 35.0f;

	void UpdateGameStart(float _Delta);
	std::function<void()> CallGameStart;
	bool GameStartCallValue = false;


	void Release();
};

