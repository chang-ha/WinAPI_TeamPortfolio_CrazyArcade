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
	class BaseMonster* Monster = nullptr;
	class Item* TestItem = nullptr;


private:
	void SetupGoBackButton();
	class Button* m_GoBackButton = nullptr;
	const float4 CONST_GoBackButtonStartPos = float4{ 647.0f , 561.0f };

	void clickGoBackButton();
};