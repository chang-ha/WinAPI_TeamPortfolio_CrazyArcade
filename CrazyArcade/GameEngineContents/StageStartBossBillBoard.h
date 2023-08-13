#pragma once
#include <GameEngineCore/GameEngineActor.h>


#include <functional>

enum class BillBoardState
{
	Appear,
	CallbackStage,
	Disappear,
	Max,
};


// 설명 :
class StageStartBossBillBoard : public GameEngineActor
{
public:
	// constrcuter destructer
	StageStartBossBillBoard();
	~StageStartBossBillBoard();

	// delete Function
	StageStartBossBillBoard(const StageStartBossBillBoard& _Other) = delete;
	StageStartBossBillBoard(StageStartBossBillBoard&& _Other) noexcept = delete;
	StageStartBossBillBoard& operator=(const StageStartBossBillBoard& _Other) = delete;
	StageStartBossBillBoard& operator=(StageStartBossBillBoard&& _Other) noexcept = delete;


	void ActorRelease();

	template<typename ActorType>
	void setCallbackStage(ActorType* _Actor, void(ActorType::* _Func)())
	{
		Func = std::bind(_Func, _Actor);
	}


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;

	// GameEngineActor 상속
	void LevelEnd() override;


	// this
	class CommonTexture* m_BossBillBoard = nullptr;
	float4 m_BillBoardScale = float4::ZERO;
	const float4 CONST_BillBoardStartPos = float4{ 100.0f , 200.0f };
	

	BillBoardState m_State = BillBoardState::Max;

	void StateUpdate(float _Delta);
	float m_StateTime = 0.0f;



	void updateAppearState(float _Delta);
	const float CONST_AppearStateDuration = 3.0f;

	void updateCallbackStageState(float _Delta);
	std::function<void()> Func;
	bool CallbackCheckValue = false;
	const float CONST_ChangeDisappearTime = 1.4f;

	void updatedisappearState(float _Delta);
	float m_Speed = 1000.0f;
};

