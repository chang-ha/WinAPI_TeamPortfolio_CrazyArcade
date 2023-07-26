#include "Button.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/ResourcesManager.h>


#include <functional>


Button::Button()
{
	for (size_t i = 0; i < static_cast<int>(ButtonState::Max); i++)
	{
		m_ButtonInfo[i] = {};
	}


	for (size_t i = 0; i < static_cast<int>(ButtonEventState::Max); i++)
	{
		m_ButtonEventInfo[i] = {};
	}
}

Button::~Button()
{

}



void Button::Start()
{
	Renderer = CreateRenderer(RenderOrder::UI);
	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	ButtonCollision = GameEngineActor::CreateCollision(CollisionOrder::Button);
	if (nullptr == ButtonCollision)
	{
		MsgBoxAssert("충돌체를 생성하지 못했습니다.");
		return;
	}

	m_ButtonState = ButtonState::Normal;
}


void Button::InitDefaultButton(
	const std::string& _FileName,
	const std::string& _Path,
	size_t _XCount /*= 0*/, size_t _YCount /*= 0*/,
	float _Inter /*= 0.1f*/,
	bool _Loop /*= true*/,
	float _RenderScaleRatio/* = 1.0f*/)
{


	GameEngineSprite* ButtonSprite = nullptr;
	ButtonSprite = GlobalUtils::SpriteFileLoad(_FileName, _Path, _XCount, _YCount);
	if (nullptr == ButtonSprite)
	{
		MsgBoxAssert("기본 버튼 텍스처를 불러오지 못했습니다.");
		return;
	}

	float4 ButtonRenderScale = ButtonSprite->GetSprite(0).RenderScale;
	m_ButtonScale = ButtonRenderScale;



	Renderer->CreateAnimation(std::to_string(DefaultButtonKey), _FileName, -1, -1, _Inter);
	Renderer->ChangeAnimation(std::to_string(DefaultButtonKey));

	Renderer->On();

	ButtonCollision->SetCollisionType(CollisionType::Rect);
	ButtonCollision->SetCollisionPos(float4::ZERO);
	ButtonCollision->SetCollisionScale(ButtonRenderScale * _RenderScaleRatio);
	ButtonCollision->On();
}


void Button::InitClickedButton(
	const std::string& _FileName,
	const std::string& _Path,
	size_t _XCount /*= 0*/, size_t _YCount /*= 0*/,
	float _Inter /*= 0.1f*/,
	bool _Loop /*= true*/,
	float _RenderScaleRatio/* = 1.0f*/)
{


	GameEngineSprite* ButtonSprite = nullptr;
	ButtonSprite = GlobalUtils::SpriteFileLoad(_FileName, _Path, _XCount, _YCount);
	if (nullptr == ButtonSprite)
	{
		MsgBoxAssert("기본 버튼 텍스처를 불러오지 못했습니다.");
		return;
	}

	float4 ButtonRenderScale = ButtonSprite->GetSprite(0).RenderScale;

	Renderer->CreateAnimation(std::to_string(ClickedButtonKey), _FileName, -1, -1, _Inter);
}


void Button::InitHoveredButton(
	const std::string& _FileName,
	const std::string& _Path,
	size_t _XCount /*= 0*/, size_t _YCount /*= 0*/,
	float _Inter /*= 0.1f*/,
	bool _Loop /*= true*/,
	float _RenderScaleRatio/* = 1.0f*/)
{


	GameEngineSprite* ButtonSprite = nullptr;
	ButtonSprite = GlobalUtils::SpriteFileLoad(_FileName, _Path, _XCount, _YCount);
	if (nullptr == ButtonSprite)
	{
		MsgBoxAssert("기본 버튼 텍스처를 불러오지 못했습니다.");
		return;
	}

	float4 ButtonRenderScale = ButtonSprite->GetSprite(0).RenderScale;

	Renderer->CreateAnimation(std::to_string(HoveredButtonKey), _FileName, -1, -1, _Inter);
}





void Button::Update(float _Delta)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("버튼 렌더러가 없습니다");
	}

	if (m_ButtonState != ButtonState::Disable)
	{
		if (true == checkHovered())
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
					execute();
				}

				m_ButtonState = ButtonState::Hover;
			}
		}
		else
		{
			if (ButtonState::Click == m_ButtonState)
			{
				if (true == GameEngineInput::IsUp(VK_LBUTTON))
				{
					Renderer->ChangeAnimation(std::to_string(static_cast<int>(ButtonState::Normal)));
				}

				m_ButtonState = ButtonState::Normal;
			}
			else
			{

			}
		}
	}
}


bool Button::checkHovered()
{
	bool MouseHoverd = true;
	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	float4 ButtonPos = GetPos();


	if (ButtonPos.X - m_ButtonScale.X > MousePos.X)
	{
		MouseHoverd = false;
	}
	else if (ButtonPos.Y - m_ButtonScale.Y > MousePos.Y)
	{
		MouseHoverd = false;
	}
	else if (ButtonPos.X + m_ButtonScale.X < MousePos.X)
	{
		MouseHoverd = false;
	}
	else if (ButtonPos.Y + m_ButtonScale.Y < MousePos.Y)
	{
		MouseHoverd = false;
	}

	return MouseHoverd;
}





void Button::Render(float _Delta)
{

}