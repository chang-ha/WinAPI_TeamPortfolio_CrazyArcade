#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class TestLevel : public GameEngineLevel
{
public:
	// constructer destructer
	TestLevel();
	~TestLevel();

	// delete function
	TestLevel(const TestLevel& _Ohter) = delete;
	TestLevel(TestLevel&& _Ohter) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(TestLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
};

