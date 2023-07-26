#pragma once
#include "PlayLevel.h"

class TestStage : public PlayLevel
{
public:
	// Constructor Destructor
	TestStage();
	~TestStage();

	// Delete Function
	TestStage(const TestStage& _Other) = delete;
	TestStage(TestStage&& _Other) noexcept = delete;
	TestStage& operator=(const TestStage& _Other) = delete;
	TestStage& operator=(TestStage&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:

};