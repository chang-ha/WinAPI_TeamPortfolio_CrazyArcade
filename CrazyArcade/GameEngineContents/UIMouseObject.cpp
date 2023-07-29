#include "UIMouseObject.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"


#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>


UIMouseObject::UIMouseObject() 
{
}

UIMouseObject::~UIMouseObject() 
{
}




void UIMouseObject::Start()
{
	Renderer = CreateRenderer(RenderOrder::MouseUI);
	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

}


void UIMouseObject::setTexture(
	MouseState _MouseType,
	const std::string& _FileName,
	const std::string& _Path,
	int _XCount, int _YCount,
	float _Inter /*= 0.1f*/,
	bool _Loop /*= true*/,
	float _RenderScaleRatio /*= 1.0f*/)
{
	GameEngineSprite* Sprite = GlobalUtils::SpriteFileLoad(_FileName, _Path, _XCount, _YCount);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("스프라이트를 로드하지 못했습니다.");
		return;
	}

	float4 RenderScale = Sprite->GetSprite(0).RenderScale;

	Renderer->CreateAnimation(std::to_string(static_cast<int>(_MouseType)), _FileName, -1, -1, _Inter);

	if (MouseState::Normal == _MouseType)
	{
		Renderer->SetRenderPos(RenderScale.Half());
	}
}


void UIMouseObject::Update(float _Delta)
{
	float4 CurMousePos = GameEngineWindow::MainWindow.GetMousePos();
	SetPos(CurMousePos);

	if (CurMousePos != MousePos || (true == GameEngineInput::IsPress(VK_LBUTTON)))
	{
		if (false == Renderer->IsUpdate())
		{
			Renderer->On();
		}

		MousePos = CurMousePos;
		MouseStateTime = 0.0f;
	}
	else
	{
		MouseStateTime += _Delta;

		if (MouseStateTime >= MouseDisappearTime)
		{
			if (true == Renderer->IsUpdate())
			{
				Renderer->Off();
			}
		}
	}

	if (true == GameEngineInput::IsPress(VK_LBUTTON))
	{
		if (MouseState::Click != m_MouseState)
		{
			if (nullptr == Renderer)
			{
				MsgBoxAssert("렌더러가 NULL입니다");
				return;
			}

			Renderer->ChangeAnimation(std::to_string(static_cast<int>(MouseState::Click)));
		}

		m_MouseState = MouseState::Click;
	}
	else
	{
		if (MouseState::Normal != m_MouseState)
		{
			if (nullptr == Renderer)
			{
				MsgBoxAssert("렌더러가 NULL입니다");
				return;
			}

			Renderer->ChangeAnimation(std::to_string(static_cast<int>(MouseState::Normal)));
		}

		m_MouseState = MouseState::Normal;
	}
}


void UIMouseObject::Render(float _Delta)
{

}