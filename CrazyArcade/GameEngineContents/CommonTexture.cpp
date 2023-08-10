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
	m_Scale = m_TextureScale;
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

	float4 Scale = _Scale;

	float4 CopyPos = float4{ Scale.X * static_cast<float>(_XBoxNumber) , Scale.Y * static_cast<float>(_YBoxNumber) };

	Renderer->SetCopyPos(CopyPos);
}

void CommonTexture::setRendererCopyPos(int _XBoxNumber, int _YBoxNumber)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러가 없습니다.");
		return;
	}

	float4 Scale = m_Scale;

	float4 CopyPos = float4{ Scale.X * static_cast<float>(_XBoxNumber) , Scale.Y * static_cast<float>(_YBoxNumber) };

	Renderer->SetCopyPos(CopyPos);
}

void CommonTexture::setRendererCopyAndRenderScale(int _XBoxNumber, int _YBoxNumber)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러가 없습니다.");
		return;
	}

	m_Scale = float4{ m_TextureScale.X / static_cast<float>(_XBoxNumber + 1) , m_TextureScale.Y / static_cast<float>(_YBoxNumber + 1) };

	Renderer->SetCopyScale(m_Scale);
	Renderer->SetRenderScale(m_Scale);
}


void CommonTexture::ActorRelease()
{
	Death();
	if (Renderer)
	{
		Renderer = nullptr;
	}
}