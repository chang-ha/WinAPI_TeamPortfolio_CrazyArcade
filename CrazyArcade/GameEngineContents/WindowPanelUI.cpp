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
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	Off();
}


void WindowPanelUI::Init(const std::string& _FileName, const std::string& _Path)
{
	GameEngineWindowTexture* Texture = GlobalUtils::TextureFileLoad(_FileName, _Path);
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ε����� ���߽��ϴ�.");
		return;
	}

	if (nullptr == Renderer)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
		return;
	}

	Renderer->SetTexture(_FileName);
	m_WindowScale = Texture->GetScale();
}


void WindowPanelUI::Update(float _Delta)
{

}

