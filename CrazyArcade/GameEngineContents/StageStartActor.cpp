#include "StageStartActor.h"
#include "ContentsEnum.h"


#include <GameEngineCore/GameEngineRenderer.h>


StageStartActor::StageStartActor() 
{
}

StageStartActor::~StageStartActor()
{
}


void StageStartActor::Start()
{
	Renderer = CreateRenderer(RenderOrder::SecondElementUI);
	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}
}


void StageStartActor::setTexture(const std::string& _FileName)
{
	if (nullptr == Renderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	Renderer->SetTexture(_FileName);
}


void StageStartActor::Update(float _Delta)
{
	updateState(_Delta);
}

void StageStartActor::updateState(float _Delta)
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

void StageStartActor::updateUpState(float _Delta)
{
	AddPos(float4::UP * m_Speed * _Delta);
	if (GetPos().Y < m_StopYPos)
	{
		SetPos(float4{ GetPos().X , m_StopYPos });
		m_State = StringAniState::Max;
	}
}

void StageStartActor::updateDownState(float _Delta)
{
	AddPos(float4::DOWN * m_Speed * _Delta);
	if (GetPos().Y > m_StopYPos)
	{
		SetPos(float4{ GetPos().X , m_StopYPos });
		m_State = StringAniState::Max;
	}
}


void StageStartActor::ActorRelease()
{
	Death();
	if (Renderer)
	{
		Renderer = nullptr;
	}
}