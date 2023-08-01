#include "FadeScreen.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"



#include <GameEngineCore/GameEngineRenderer.h>




FadeScreen::FadeScreen() 
{
}

FadeScreen::~FadeScreen() 
{
}


void FadeScreen::Start()
{
	Renderer = CreateUIRenderer(RenderOrder::FadeScreenUI);
	if (nullptr == Renderer)
	{
		MsgBoxAssert("생성한 렌더러가 NUll입니다.");
		return;
	}

	static bool LoadFadeFileValue = false;

	if (false == LoadFadeFileValue)
	{
		GlobalUtils::TextureFileLoad("FadeBlack.bmp", "Resources\\Textures\\UI\\Fade");
		GlobalUtils::TextureFileLoad("FadeWhite.bmp", "Resources\\Textures\\UI\\Fade");
	}

	Renderer->SetTexture("FadeBlack.bmp");
	Renderer->On();
}



void FadeScreen::setRenderScale(const float4& _Scale)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다.");
		return;
	}

	m_Scale = _Scale;
	Renderer->SetRenderScale(_Scale);
}

void FadeScreen::setAlpha(int _AlphaCount /*= 0*/)
{
	m_AlphaValue = _AlphaCount;

	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러가 Null 입니다.");
		return;
	}

	Renderer->SetAlpha(static_cast<unsigned char>(m_AlphaValue));
}


