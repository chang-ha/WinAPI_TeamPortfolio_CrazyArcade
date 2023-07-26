#include "Button.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"


#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/ResourcesManager.h>


#include "ContentLevel.h"


Button::Button()
{
}

Button::~Button()
{

}



void Button::Start()
{
	Renderer = CreateRenderer(RenderOrder::UI);
	if (nullptr == Renderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	m_ButtonState = ButtonState::Normal;
}


void Button::InitDefaultButton(
	const std::string& _FileName,
	const std::string& _Path,
	int _XCount /*= 0*/, int _YCount /*= 0*/,
	float _Inter /*= 0.1f*/,
	bool _Loop /*= true*/,
	float _RenderScaleRatio/* = 1.0f*/)
{


	GameEngineSprite* ButtonSprite = nullptr;
	ButtonSprite = GlobalUtils::SpriteFileLoad(_FileName, _Path, _XCount, _YCount);
	if (nullptr == ButtonSprite)
	{
		MsgBoxAssert("�⺻ ��ư �ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	float4 ButtonRenderScale = ButtonSprite->GetSprite(0).RenderScale;
	m_ButtonScale = ButtonRenderScale;


	Renderer->CreateAnimation(std::to_string(static_cast<int>(ButtonState::Normal)), _FileName, -1, -1, _Inter);
	Renderer->ChangeAnimation(std::to_string(static_cast<int>(ButtonState::Normal)));

	
	Renderer->On();
}


void Button::InitClickButton(
	const std::string& _FileName,
	const std::string& _Path,
	int _XCount , int _YCount ,
	float _Inter /*= 0.1f*/,
	bool _Loop /*= true*/,
	float _RenderScaleRatio/* = 1.0f*/)
{


	GameEngineSprite* ButtonSprite = nullptr;
	ButtonSprite = GlobalUtils::SpriteFileLoad(_FileName, _Path, _XCount, _YCount);
	if (nullptr == ButtonSprite)
	{
		MsgBoxAssert("�⺻ ��ư �ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	float4 ButtonRenderScale = ButtonSprite->GetSprite(0).RenderScale;

	Renderer->CreateAnimation(std::to_string(static_cast<int>(ButtonState::Click)), _FileName, -1, -1, _Inter);
}


void Button::InitHoveredButton(
	const std::string& _FileName,
	const std::string& _Path,
	int _XCount, int _YCount,
	float _Inter /*= 0.1f*/,
	bool _Loop /*= true*/,
	float _RenderScaleRatio/* = 1.0f*/)
{


	GameEngineSprite* ButtonSprite = nullptr;
	ButtonSprite = GlobalUtils::SpriteFileLoad(_FileName, _Path, _XCount, _YCount);
	if (nullptr == ButtonSprite)
	{
		MsgBoxAssert("�⺻ ��ư �ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	float4 ButtonRenderScale = ButtonSprite->GetSprite(0).RenderScale;

	Renderer->CreateAnimation(std::to_string(static_cast<int>(ButtonState::Hover)), _FileName, -1, -1, _Inter);
}





void Button::Update(float _Delta)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("��ư �������� �����ϴ�");
	}

	if (m_ButtonState != ButtonState::Disable)
	{
		bool HoverValue = checkHovered();

		if (true == HoverValue)
		{
			if (true == GameEngineInput::IsDown(VK_LBUTTON))
			{
				if (ButtonState::Click != m_ButtonState)
				{
					Renderer->ChangeAnimation(std::to_string(static_cast<int>(ButtonState::Click)));
				}

				m_ButtonState = ButtonState::Click;
			}
			else if (ButtonState::Click == m_ButtonState && true == GameEngineInput::IsUp(VK_LBUTTON))
			{
				if (ButtonState::Hover != m_ButtonState)
				{
					Renderer->ChangeAnimation(std::to_string(static_cast<int>(ButtonState::Hover)));
					m_ButtonEventCallBack[static_cast<int>(ButtonEventState::Click)];
				}

				m_ButtonState = ButtonState::Hover;
			}
			else if (ButtonState::Click == m_ButtonState && true == GameEngineInput::IsPress(VK_LBUTTON))
			{
				m_ButtonState = ButtonState::Click;
			}
			else
			{
				if (m_ButtonHoverValue != HoverValue)
				{
					// Sound
				}

				if (ButtonState::Hover != m_ButtonState)
				{
					Renderer->ChangeAnimation(std::to_string(static_cast<int>(ButtonState::Hover)));
				}

				m_ButtonState = ButtonState::Hover;
			}

			m_ButtonHoverValue = true;
		}
		else
		{
			m_ButtonHoverValue = false;

			if (ButtonState::Normal != m_ButtonState)
			{
				Renderer->ChangeAnimation(std::to_string(static_cast<int>(ButtonState::Normal)));
			}

			m_ButtonState = ButtonState::Normal;
		}
	}
}


bool Button::checkHovered()
{
	bool MouseHoverd = true;
	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	float4 ButtonPos = GetPos();


	if (ButtonPos.X - m_ButtonScale.Half().X > MousePos.X)
	{
		MouseHoverd = false;
	}
	else if (ButtonPos.Y - m_ButtonScale.Half().Y > MousePos.Y)
	{
		MouseHoverd = false;
	}
	else if (ButtonPos.X + m_ButtonScale.Half().X < MousePos.X)
	{
		MouseHoverd = false;
	}
	else if (ButtonPos.Y + m_ButtonScale.Half().Y < MousePos.Y)
	{
		MouseHoverd = false;
	}

	return MouseHoverd;
}





void Button::Render(float _Delta)
{
	if (false == ContentLevel::DebugValue)
	{
		return;
	}

	GameEngineWindowTexture* BackBufferPtr = GameEngineWindow::MainWindow.GetBackBuffer();
	if (nullptr == BackBufferPtr)
	{
		MsgBoxAssert("���۸� �ҷ����� ���߽��ϴ�.");
		return;
	}

	HDC dc = BackBufferPtr->GetImageDC();
	if (nullptr == dc)
	{
		MsgBoxAssert("HDC�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	float4 ButtonPos = GetPos();
	ButtonPos.iX();


	{
		std::string Text = "";

		switch (m_ButtonState)
		{
		case ButtonState::Normal:
			Text += "Normal";
			break;
		case ButtonState::Hover:
			Text += "Hover";
			break;
		case ButtonState::Click:
			Text += "Click";
			break;
		case ButtonState::Disable:
			Text += "Disable";
			break;
		case ButtonState::Max:
			break;
		default:
			break;
		}
		
		TextOutA(dc, ButtonPos.iX(), ButtonPos.iY(), Text.c_str(), static_cast<int>(Text.size()));

	}
}