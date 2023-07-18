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

private:

};

