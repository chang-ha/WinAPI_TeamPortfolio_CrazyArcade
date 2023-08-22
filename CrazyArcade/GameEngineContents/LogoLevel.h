#pragma once
#include "ContentLevel.h"

enum class LogoState
{
	None,
	FadeIn,
	ShowLogo,
	FadeOut,
	Max,
};


class LogoLevel : public ContentLevel
{
public:
	// constructer destructer
	LogoLevel();
	~LogoLevel();

	// delete function
	LogoLevel(const LogoLevel& _Ohter) = delete;
	LogoLevel(LogoLevel&& _Ohter) noexcept = delete;
	LogoLevel& operator=(const LogoLevel& _Other) = delete;
	LogoLevel& operator=(LogoLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void setEffectSound(const std::string& _FileName, float _SoundVolume = 1.0f);
	void setNextLevelString(const std::string& _NextLevelName);

private:
	const float CONST_FadeInTime = 0.4f;
	const float CONST_FadeOutTIme = 0.4f;


	void updateLogoTransition(float _Delta);
	void updateLogoState(float _Delta);
	float m_StateTime = 0.0f;
	LogoState m_State = LogoState::None;

	void updateFadeInState(float _Delta);
	bool m_EffectSoundValue = false;
	std::string m_stringEffectSoundName = "";
	float m_LogoEffectSoundVolume = 0.0f;

	void updateShowLogoState(float _Delta);
	const float CONST_LOGODurction = 3.0f;
	void updateFadeOutState(float _Delta);

	std::string m_stringNextLevel = "";

};

