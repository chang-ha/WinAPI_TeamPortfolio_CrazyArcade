#include "WindowPanelUI.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineRenderer.h>



WindowPanelUI::WindowPanelUI() 
{
}

WindowPanelUI::~WindowPanelUI() 
{
}




void WindowPanelUI::Start()
{
	Renderer = GameEngineActor::CreateRenderer(RenderOrder::WindowPanelUI);
	if (nullptr == Renderer)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	Off();
}


void WindowPanelUI::Init(const std::string& _FileName, const std::string& _Path)
{
	GameEngineWindowTexture* Texture = GlobalUtils::TextureFileLoad(_FileName, _Path);
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 로드하지 못했습니다.");
		return;
	}

	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	Renderer->SetTexture(_FileName);
	m_WindowScale = Texture->GetScale();
}


void WindowPanelUI::Update(float _Delta)
{

}

