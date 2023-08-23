#pragma once
#include "LogoLevel.h"

class TitleNexon : public LogoLevel
{
public:
	// constructer destructer
	TitleNexon();
	~TitleNexon();

	// delete function
	TitleNexon(const TitleNexon& _Ohter) = delete;
	TitleNexon(TitleNexon&& _Ohter) noexcept = delete;
	TitleNexon& operator=(const TitleNexon& _Other) = delete;
	TitleNexon& operator=(TitleNexon&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:

};