#include "FadeObject.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>


FadeObject::FadeObject() 
{
}

FadeObject::~FadeObject() 
{
}


void FadeObject::Start()
{
	static bool FadeOutTextureLoad = false;

	GameEngineWindowTexture* Texure = nullptr;

	if (false == FadeOutTextureLoad)
	{
		Texure = GlobalUtils::TextureFileLoad("FadeBlack.bmp", "Resources\\Textures\\UI\\Fade");

		FadeOutTextureLoad = true;
	}

	Renderer = CreateRenderer(RenderOrder::FadeOutUI);
	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	float4 WinScale = GlobalValue::WinScale;

	Renderer->SetTexture("FadeBlack.bmp");
	Renderer->SetRenderScale(WinScale);


	SetPos(WinScale.Half());
}

// 
void FadeObject::CallFadeOut(GameEngineLevel* _Level, const std::string& _LevelName, float _FadeOutDuration /*= 1.0f*/, int _Alpha /*= 0*/)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("Level을 불러오지 못했습니다.");
		return;
	}

	FadeObject* FadeOut = _Level->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == FadeOut)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}


	FadeOut->m_FadeType = CallFadeType::FadeOut;
	FadeOut->m_NextLevelName = _LevelName;

	FadeOut->m_Alpha = _Alpha;

	FadeOut->m_FadeDuration = _FadeOutDuration;
	FadeOut->m_RequestAlphaValue = _Alpha;


	if (FadeOut->Renderer)
	{
		FadeOut->Renderer->SetAlpha(_Alpha);
	}
}

void FadeObject::CallFadeIn(GameEngineLevel* _Level, float _FadeOutDuration /*= 1.0f*/, int _Alpha /*= 255*/)
{
	if (nullptr == _Level)
	{
		MsgBoxAssert("Level을 불러오지 못했습니다.");
		return;
	}

	FadeObject* FadeIn = _Level->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == FadeIn)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	FadeIn->m_Alpha = _Alpha;

	FadeIn->m_FadeDuration = _FadeOutDuration;
	FadeIn->m_RequestAlphaValue = _Alpha;

	FadeIn->m_FadeType = CallFadeType::FadeIn;

	if (FadeIn->Renderer)
	{
		FadeIn->Renderer->SetAlpha(_Alpha);
	}
}


void FadeObject::Update(float _Delta)
{
	m_FadeTime += _Delta;

	if (CallFadeType::FadeOut == m_FadeType)
	{
		m_Alpha += static_cast<int>(static_cast<float>(MaxAlphaValue - m_RequestAlphaValue) / m_FadeDuration * _Delta);
		m_DebugAlphaValue = m_Alpha;

		if (m_Alpha > MaxAlphaValue)
		{
			m_Alpha = MaxAlphaValue;
			GameEngineCore::ChangeLevel(m_NextLevelName);
		}

		Renderer->SetAlpha(m_Alpha);

	}
	else if (CallFadeType::FadeIn == m_FadeType)
	{
		m_Alpha -= static_cast<int>(static_cast<float>(m_RequestAlphaValue - MinAlphaValue) / m_FadeDuration * _Delta);
		m_DebugAlphaValue = m_Alpha;

		Renderer->SetAlpha(m_Alpha);

		if (m_Alpha < MinAlphaValue)
		{
			Death();
			if (Renderer)
			{
				Renderer = nullptr;
			}
		}
	}
}


void FadeObject::LevelEnd()
{
	if (CallFadeType::FadeOut != m_FadeType)
	{
		return;
	}

	Death();
	if (Renderer)
	{
		Renderer = nullptr;
	}
}