#include "LogoLevel.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "GlobalUtils.h"

#include <GameEnginePlatform/GameEngineSound.h>


#include "FadeObject.h"
#include "BackGround.h"


LogoLevel::LogoLevel()
{

}

LogoLevel::~LogoLevel()
{

}

void LogoLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	FadeObject::CallFadeIn(this, CONST_FadeInTime);

	if (LogoState::Max == m_State)
	{
		m_State = LogoState::FadeIn;
	}
}

void LogoLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
}

void LogoLevel::Start()
{
	ContentLevel::Start();

	m_State = LogoState::FadeIn;
}


void LogoLevel::setEffectSound(const std::string& _FileName, float _SoundVolume /*= 1.0f*/)
{
	m_stringEffectSoundName = _FileName;
	m_LogoEffectSoundVolume = _SoundVolume;
}

void LogoLevel::setNextLevelString(const std::string& _NextLevelName)
{
	m_stringNextLevel = _NextLevelName;
}



void LogoLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	updateLogoTransition(_Delta);
}

void LogoLevel::updateLogoTransition(float _Delta)
{
	updateLogoState(_Delta);
}

void LogoLevel::updateLogoState(float _Delta)
{
	switch (m_State)
	{
	case LogoState::None:
	{
		MsgBoxAssert("초기 행동을 지정해주지 않았습니다.");
		return;
	}
		break;
	case LogoState::FadeIn:
		updateFadeInState(_Delta);
		break;
	case LogoState::ShowLogo:
		updateShowLogoState(_Delta);
		break;
	case LogoState::FadeOut:
		updateFadeOutState(_Delta);
		break;
	default:
		break;
	}
}

void LogoLevel::updateFadeInState(float _Delta)
{
	if (false == m_EffectSoundValue)
	{
		if ("" != m_stringEffectSoundName)
		{
			BGMPlayer = GameEngineSound::SoundPlay(m_stringEffectSoundName);
			BGMPlayer.SetVolume(m_LogoEffectSoundVolume);
		}

		m_EffectSoundValue = true;
	}

	m_StateTime += _Delta;

	if (m_StateTime > CONST_FadeInTime)
	{
		m_StateTime = 0.0f;

		m_State = LogoState::ShowLogo;
		m_EffectSoundValue = false;
	}
}

void LogoLevel::updateShowLogoState(float _Delta)
{
	m_StateTime += _Delta;

	if (m_StateTime > CONST_LOGODurction)
	{
		m_StateTime = 0.0f;

		m_State = LogoState::FadeOut;

		FadeObject::CallFadeOut(this, m_stringNextLevel, CONST_FadeOutTIme);
	}
}

void LogoLevel::updateFadeOutState(float _Delta)
{
	m_State = LogoState::Max;
}

void LogoLevel::Render(float _Delta)
{

}