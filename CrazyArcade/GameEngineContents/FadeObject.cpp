#include "FadeObject.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>


FadeObject* FadeObject::g_FadeObject = nullptr;
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
	if (nullptr != g_FadeObject)
	{
		MsgBoxAssert("초기화가 이뤄지지 않았습니다.");
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


	g_FadeObject = FadeOut;
}

void FadeObject::CallFadeIn(GameEngineLevel* _Level, float _FadeOutDuration /*= 1.0f*/, int _Alpha /*= 255*/)
{
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

void FadeObject::ReleaseFadeObject()
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

	g_FadeObject = nullptr;
}



void FadeObject::Update(float _Delta)
{
	m_FadeTime += _Delta;

	if (CallFadeType::FadeOut == m_FadeType)
	{
		m_Alpha += static_cast<int>(static_cast<float>(MaxAlphaValue - m_RequestAlphaValue) / m_FadeDuration * _Delta);
		m_DebugAlphaValue = m_Alpha;

		Renderer->SetAlpha(m_Alpha);

		if (m_Alpha > MaxAlphaValue)
		{
			GameEngineCore::ChangeLevel(m_NextLevelName);
			return;
		}
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