#pragma once
#include "PlayLevel.h"

class DummyStage : public PlayLevel
{
public:
	// Constructor Destructor
	DummyStage();
	~DummyStage();

	// Delete Function
	DummyStage(const DummyStage& _Other) = delete;
	DummyStage(DummyStage&& _Other) noexcept = delete;
	DummyStage& operator=(const DummyStage& _Other) = delete;
	DummyStage& operator=(DummyStage&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:

};