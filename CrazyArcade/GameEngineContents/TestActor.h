#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineWindowTexture;
class TestActor : public GameEngineActor
{
public:
	// constructer destructer
	TestActor();
	~TestActor();

	// delete function
	TestActor(const TestActor& _Ohter) = delete;
	TestActor(TestActor&& _Ohter) noexcept = delete;
	TestActor& operator=(const TestActor& _Other) = delete;
	TestActor& operator=(TestActor&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
};

