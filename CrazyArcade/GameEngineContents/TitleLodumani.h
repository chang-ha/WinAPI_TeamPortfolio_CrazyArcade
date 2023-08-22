#pragma once
#include "LogoLevel.h"

class TitleLodumani : public LogoLevel
{
public:
	// constructer destructer
	TitleLodumani();
	~TitleLodumani();

	// delete function
	TitleLodumani(const TitleLodumani& _Ohter) = delete;
	TitleLodumani(TitleLodumani&& _Ohter) noexcept = delete;
	TitleLodumani& operator=(const TitleLodumani& _Other) = delete;
	TitleLodumani& operator=(TitleLodumani&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:

};

