#include "StringAnimation.h"
#include "ContentsEnum.h"


#include <GameEngineCore/GameEngineRenderer.h>


StringAnimation::StringAnimation() 
{
}

StringAnimation::~StringAnimation()
{
}


void StringAnimation::Start()
{
	Renderer = CreateRenderer(RenderOrder::SecondElementUI);
	if (nullptr == Renderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}
}


void StringAnimation::setTexture(const std::string& _FileName)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
		return;
	}

	Renderer->SetTexture(_FileName);
}


void StringAnimation::Update(float _Delta)
{
	updateState(_Delta);
}

void StringAnimation::updateState(float _Delta)
{
	switch (m_State)
	{
	case StringAniState::Up:
		updateUpState(_Delta);
		break;
	case StringAniState::Down:
		updateDownState(_Delta);
		break;
	default:
		break;
	}
}

void StringAnimation::updateUpState(float _Delta)
{
	AddPos(float4::UP * m_Speed * _Delta);
	if (GetPos().Y < m_StopYPos)
	{
		SetPos(float4{ GetPos().X , m_StopYPos });
		m_State = StringAniState::Max;
	}
}

void StringAnimation::updateDownState(float _Delta)
{
	AddPos(float4::DOWN * m_Speed * _Delta);
	if (GetPos().Y > m_StopYPos)
	{
		SetPos(float4{ GetPos().X , m_StopYPos });
		m_State = StringAniState::Max;
	}
}


void StringAnimation::ActorRelease()
{
	Death();
	if (Renderer)
	{
		Renderer = nullptr;
	}
}