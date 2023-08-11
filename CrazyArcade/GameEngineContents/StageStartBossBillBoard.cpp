#include "StageStartBossBillBoard.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "CommonTexture.h"


StageStartBossBillBoard::StageStartBossBillBoard() 
{
}

StageStartBossBillBoard::~StageStartBossBillBoard() 
{
}



void StageStartBossBillBoard::Start()
{
	m_State = BillBoardState::Appear;

	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	m_BossBillBoard = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_BossBillBoard)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_BossBillBoard->loadTexture("Logo_Peng.bmp", "Resources\\Textures\\UI\\PlayStage");
	m_BossBillBoard->setTexture("Logo_Peng.bmp");

	m_BillBoardScale = m_BossBillBoard->getTextureScale();
	float4 BillBoardPos = CONST_BillBoardStartPos + m_BillBoardScale.Half();
	m_BossBillBoard->SetPos(BillBoardPos);
}


void StageStartBossBillBoard::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void StageStartBossBillBoard::StateUpdate(float _Delta)
{
	switch (m_State)
	{
	case BillBoardState::Appear:
		updateAppearState(_Delta);
		break;
	case BillBoardState::CallbackStage :
		updateCallbackStageState(_Delta);
		break;
	case BillBoardState::Disappear:
		updatedisappearState(_Delta);
		break;
	default:
		break;
	}
}

void StageStartBossBillBoard::updateAppearState(float _Delta)
{
	m_StateTime += _Delta;

	if (m_StateTime > CONST_AppearStateDuration)
	{
		m_State = BillBoardState::CallbackStage;

		m_StateTime = 0.0f;
	}
}

void StageStartBossBillBoard::updateCallbackStageState(float _Delta)
{
	if (false == CallbackCheckValue)
	{

		Func();

		CallbackCheckValue = true;
	}
	
	if (true == CallbackCheckValue)
	{
		m_StateTime += _Delta;

		if (m_StateTime > CONST_ChangeDisappearTime)
		{
			m_State = BillBoardState::Disappear;
		}
	}
}

void StageStartBossBillBoard::updatedisappearState(float _Delta)
{
	if (nullptr == m_BossBillBoard)
	{
		MsgBoxAssert("액터를 생성하지 않았습니다.");
		return;
	}

	m_BossBillBoard->AddPos(float4::LEFT * m_Speed * _Delta);

	if (m_BossBillBoard->GetPos().X < -m_BillBoardScale.hX())
	{
		ActorRelease();
	}
}

void StageStartBossBillBoard::ActorRelease()
{
	if (m_BossBillBoard)
	{
		m_BossBillBoard->ActorRelease();
		m_BossBillBoard = nullptr;
	}

	Death();
}

void StageStartBossBillBoard::LevelEnd()
{
	ActorRelease();
}