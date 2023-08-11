#pragma once
#include "PlayLevel.h"

class Penguin_Stage1 : public PlayLevel
{
public:
	// constructer destructer
	Penguin_Stage1();
	~Penguin_Stage1();

	// delete function
	Penguin_Stage1(const Penguin_Stage1& _Ohter) = delete;
	Penguin_Stage1(Penguin_Stage1&& _Ohter) noexcept = delete;
	Penguin_Stage1& operator=(const Penguin_Stage1& _Other) = delete;
	Penguin_Stage1& operator=(Penguin_Stage1&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	class Snowmon_black* Snowmon = nullptr;
};

