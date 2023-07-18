#pragma once
#include <GameEngineCore/GameEngineCore.h>

class CrazyArcadeCore : public CoreProcess
{
public:
	// constructer destructer
	CrazyArcadeCore();
	~CrazyArcadeCore();

	// delete function
	CrazyArcadeCore(const CrazyArcadeCore& _Ohter) = delete;
	CrazyArcadeCore(CrazyArcadeCore&& _Ohter) noexcept = delete;
	CrazyArcadeCore& operator=(const CrazyArcadeCore& _Other) = delete;
	CrazyArcadeCore& operator=(CrazyArcadeCore&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release() override;
};

