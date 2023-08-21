#pragma once
#include "PlayLevel.h"

class Penguin_Stage3 : public PlayLevel
{
public:
	// constructer destructer
	Penguin_Stage3();
	~Penguin_Stage3();

	// delete function
	Penguin_Stage3(const Penguin_Stage3& _Ohter) = delete;
	Penguin_Stage3(Penguin_Stage3&& _Ohter) noexcept = delete;
	Penguin_Stage3& operator=(const Penguin_Stage3& _Other) = delete;
	Penguin_Stage3& operator=(Penguin_Stage3&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
};

