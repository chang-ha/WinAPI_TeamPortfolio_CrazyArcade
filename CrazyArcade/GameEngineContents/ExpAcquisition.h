#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <vector>


// 설명 :
class ExpAcquisition : public GameEngineActor
{
public:
	// constrcuter destructer
	ExpAcquisition();
	~ExpAcquisition();

	// delete Function
	ExpAcquisition(const ExpAcquisition& _Other) = delete;
	ExpAcquisition(ExpAcquisition&& _Other) noexcept = delete;
	ExpAcquisition& operator=(const ExpAcquisition& _Other) = delete;
	ExpAcquisition& operator=(ExpAcquisition&& _Other) noexcept = delete;

	void initExpUI();

	void showExpUI();
	void OffExpUI();

	void setScoreRender(int _Score);

	void ActorRelease();


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineActor 상속
	void LevelEnd() override;

	// this
	void setBack();
	class CommonTexture* m_Back = nullptr;

	void setScore();
	const int CONST_ScoreNumberCount = 5;
	std::vector<class CommonTexture*> vecScore;
	const float4 CONST_ScoreStartPos = float4{ 15.0f, 2.0f };
};

