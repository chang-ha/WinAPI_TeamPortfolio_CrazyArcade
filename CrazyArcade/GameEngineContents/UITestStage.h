#pragma once
#include "PlayLevel.h"

class UITestStage : public PlayLevel
{
public:
	// Constructor Destructor
	UITestStage();
	~UITestStage();

	// Delete Function
	UITestStage(const UITestStage& _Other) = delete;
	UITestStage(UITestStage&& _Other) noexcept = delete;
	UITestStage& operator=(const UITestStage& _Other) = delete;
	UITestStage& operator=(UITestStage&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:

};