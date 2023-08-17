#pragma once
#include "PlayLevel.h"

// Ό³Έν :
class UITestStage3 : public PlayLevel
{
public:
	// constrcuter destructer
	UITestStage3();
	~UITestStage3();

	// delete Function
	UITestStage3(const UITestStage3& _Other) = delete;
	UITestStage3(UITestStage3&& _Other) noexcept = delete;
	UITestStage3& operator=(const UITestStage3& _Other) = delete;
	UITestStage3& operator=(UITestStage3&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:

};

