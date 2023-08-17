#include "GameOverAnimation.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include  "StageClearAnimation.h"
#include  "LoseAnimation.h"
#include "CommonTexture.h"


GameOverAnimation::GameOverAnimation() 
{
}

GameOverAnimation::~GameOverAnimation() 
{
}


void GameOverAnimation::Start()
{

}


void GameOverAnimation::initStageResultAnimation(int _Stage, bool _WinValue)
{
	_WinValue ? CreateStageClearAnimation(_Stage) : CreateLoseAnimation();
}

void GameOverAnimation::CreateStageClearAnimation(int _Stage)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	if (3 == _Stage)
	{
		m_AllStageBillboard = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == m_AllStageBillboard)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		m_AllStageBillboard->loadTexture("ALLClear.bmp", "Resources\\Textures\\UI\\PlayStage");
		m_AllStageBillboard->setTexture("ALLClear.bmp");

		float4 ALLClearScale = m_AllStageBillboard->getTextureScale();
		float4 ALLClearPos = ALLClearScale.Half() + CONST_ALLClearStartPos;
		m_AllStageBillboard->SetPos(ALLClearPos);
		m_AllStageBillboard->setRendererOrder(6);

	}
	else if (_Stage >= 1 && _Stage <= 2)
	{
		StageClearAnimation* StageClearAnimationPtr = CurLevel->CreateActor<StageClearAnimation>(UpdateOrder::UI);
		if (nullptr == StageClearAnimationPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		StageClearAnimationPtr->initStartAnimation(_Stage);
	}

	m_State = static_cast<CallAnimationType>(_Stage);
}

void GameOverAnimation::CreateLoseAnimation()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	LoseAnimation* LoseAnimationPtr = CurLevel->CreateActor<LoseAnimation>(UpdateOrder::UI);
	if (nullptr == LoseAnimationPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	LoseAnimationPtr->initLoseAnimation();

	m_State = CallAnimationType::Lose;
}


void GameOverAnimation::Update(float _Delta)
{

}

void GameOverAnimation::LevelEnd()
{
	if (m_AllStageBillboard)
	{
		m_AllStageBillboard->ActorRelease();
		m_AllStageBillboard = nullptr;
	}

	Death();
}