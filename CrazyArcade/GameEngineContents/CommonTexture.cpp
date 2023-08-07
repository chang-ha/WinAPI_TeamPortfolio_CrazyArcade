#include "CommonTexture.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineRenderer.h>



CommonTexture::CommonTexture() 
{
}

CommonTexture::~CommonTexture() 
{
}


void CommonTexture::Start()
{
	Renderer = CreateRenderer(RenderOrder::FirstElementUI);
	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}
}

void CommonTexture::loadTexture(const std::string& _FileName, const std::string& _Path)
{
	GameEngineWindowTexture* Texture = GlobalUtils::TextureFileLoad(_FileName, _Path);
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	m_TextureScale = Texture->GetScale();
}

void CommonTexture::setTexture(const std::string& _FileName)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	Renderer->SetTexture(_FileName);
}


void CommonTexture::setRendererOrder(int _Order)
{
	if (Renderer)
	{
		Renderer->SetOrder(_Order);
	}
}

void CommonTexture::setRendererCopyPos(const float4& _Scale, int _XBoxNumber, int _YBoxNumber)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러가 없습니다.");
		return;
	}

	float4 CopyPos = float4{ _Scale.X * static_cast<float>(_XBoxNumber) , _Scale.Y * static_cast<float>(_YBoxNumber) };

	Renderer->SetCopyPos(CopyPos);
}