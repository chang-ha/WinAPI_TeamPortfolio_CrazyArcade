#include "FadeObject.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>


bool FadeObject::g_FadeOutValue = false;
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
void FadeObject::CallFadeOut(GameEngineLevel* _Level, float _FadeOutDuration /*= 1.0f*/, int _Alpha /*= 0*/)
{
	FadeObject* FadeOut = _Level->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == FadeOut)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	FadeOut->m_Alpha = _Alpha;

	FadeOut->m_FadeDuration = _FadeOutDuration;
	FadeOut->m_RequestAlphaValue = _Alpha;

	FadeOut->m_FadeType = CallFadeType::FadeOut;

	if (FadeOut->Renderer)
	{
		FadeOut->Renderer->SetAlpha(_Alpha);
	}
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
			g_FadeOutValue = true;

			Death();
			if (Renderer)
			{
				Renderer = nullptr;
			}
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