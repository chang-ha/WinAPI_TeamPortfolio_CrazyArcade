#pragma once
#include "PlayLevel.h"

class UITestStage2 : public PlayLevel
{
public:
	// Constructor Destructor
	UITestStage2();
	~UITestStage2();

	// Delete Function
	UITestStage2(const UITestStage2& _Other) = delete;
	UITestStage2(UITestStage2&& _Other) noexcept = delete;
	UITestStage2& operator=(const UITestStage2& _Other) = delete;
	UITestStage2& operator=(UITestStage2&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:

};