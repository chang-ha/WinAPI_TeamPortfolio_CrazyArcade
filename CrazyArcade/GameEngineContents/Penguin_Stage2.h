#pragma once
#include "PlayLevel.h"

class Penguin_Stage2 : public PlayLevel
{
public:
	// constructer destructer
	Penguin_Stage2();
	~Penguin_Stage2();

	// delete function
	Penguin_Stage2(const Penguin_Stage2& _Ohter) = delete;
	Penguin_Stage2(Penguin_Stage2&& _Ohter) noexcept = delete;
	Penguin_Stage2& operator=(const Penguin_Stage2& _Other) = delete;
	Penguin_Stage2& operator=(Penguin_Stage2&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	class Snowmon_black* Snowmon_Black = nullptr;
	class Snowmon_red* Snowmon_Red = nullptr;
};

