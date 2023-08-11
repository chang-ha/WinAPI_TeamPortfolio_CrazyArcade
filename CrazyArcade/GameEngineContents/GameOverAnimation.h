#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <vector>


enum class CallAnimationType
{
	Lose,
	StageClear1,
	StageClear2,
	ALLClear,
	Max,
};

// 설명 :
class GameOverAnimation : public GameEngineActor
{
public:
	// constrcuter destructer
	GameOverAnimation();
	~GameOverAnimation();

	// delete Function
	GameOverAnimation(const GameOverAnimation& _Other) = delete;
	GameOverAnimation(GameOverAnimation&& _Other) noexcept = delete;
	GameOverAnimation& operator=(const GameOverAnimation& _Other) = delete;
	GameOverAnimation& operator=(GameOverAnimation&& _Other) noexcept = delete;

	void initStageResultAnimation(int _Stage, bool _WinValue);

protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineActor 상속
	void LevelEnd() override;


	// this
	CallAnimationType m_State = CallAnimationType::Max;

	void CreateStageClearAnimation(int _Stage);
	void CreateALLStage();
	class CommonTexture* m_AllStageBillboard = nullptr;
	const float4 CONST_ALLClearStartPos = float4{ 138.0f , 32.0f };

	void CreateLoseAnimation();
};

