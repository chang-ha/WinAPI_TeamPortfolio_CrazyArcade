#include "PlayResultWindow.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "CommonTexture.h"
#include "PlayResultLine.h"


PlayResultWindow::PlayResultWindow() 
{
}

PlayResultWindow::~PlayResultWindow() 
{
}


void PlayResultWindow::Start()
{

}

void PlayResultWindow::initResultWindow()
{
	m_ActiveRoomCount = GlobalValue::g_ActiveRoomCount;

	setupFadeWindow();
	setupResultSummary();
	setupResultLine();
}

void PlayResultWindow::setupFadeWindow()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	m_ResultFadeWindow = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_ResultFadeWindow)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_ResultFadeWindow->loadTexture("ResultWindow.bmp", "Resources\\Textures\\UI\\PlayStage");
	m_ResultFadeWindow->setTexture("ResultWindow.bmp");
	
	float4 ResultWindowScale = m_ResultFadeWindow->getTextureScale();
	float4 ResultWindowPos = GetPos() + ResultWindowScale.Half();

	m_ResultFadeWindow->SetPos(ResultWindowPos);
	m_ResultFadeWindow->setRendererOrder(RenderOrder::FirstElementUI);

	GameEngineRenderer* ResultWinRenderer = m_ResultFadeWindow->getRenderer();
	if (nullptr == ResultWinRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	ResultWinRenderer->SetAlpha(CONST_FadeWindowAlpha);

	m_ResultFadeWindow->Off();
}


void PlayResultWindow::setupResultSummary()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	m_ResultSummary = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_ResultSummary)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_ResultSummary->loadTexture("Result_Summary.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
	m_ResultSummary->setTexture("Result_Summary.bmp");

	float4 ResultSummaryScale = m_ResultSummary->getTextureScale();
	float4 ResultSummaryPos = GetPos() + CONST_ResultSummaryStartPos + ResultSummaryScale.Half();

	m_ResultSummary->SetPos(ResultSummaryPos);
	m_ResultSummary->setRendererOrder(6);

	m_ResultSummary->Off();
}


void PlayResultWindow::setupResultLine()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	vecPlayResultLine.resize(m_ActiveRoomCount);

	for (int LineCount = 0; LineCount < m_ActiveRoomCount; LineCount++)
	{
		PlayResultLine* PlayResultLinePtr = CurLevel->CreateActor<PlayResultLine>(UpdateOrder::UI);
		if (nullptr == PlayResultLinePtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		float4 LinePos = GetPos() + CONST_ResultLineStartPos +
			float4{ CONST_ResultLineNextPos.X , CONST_ResultLineNextPos.Y * static_cast<float>(LineCount) };

		PlayResultLinePtr->SetPos(LinePos);
		PlayResultLinePtr->initResultLine(LineCount);

		vecPlayResultLine[LineCount] = PlayResultLinePtr;
	}
}

void PlayResultWindow::OnResultWindow(const std::vector<PlayerResult>& _VecResult)
{
	if (m_ResultSummary)
	{
		m_ResultSummary->On();
	}

	if (m_ResultFadeWindow)
	{
		m_ResultFadeWindow->On();
	}

	for (int vecCount = 0; vecCount < vecPlayResultLine.size(); vecCount++)
	{
		PlayResultLine* LinePtr = vecPlayResultLine[vecCount];
		if (nullptr == LinePtr)
		{
			MsgBoxAssert("벡터 인수를 확인해주세요.");
			return;
		}

		LinePtr->onResultLine();
		
		LinePtr->changePlayerMatchValue(_VecResult[vecCount].PlayerWinValue);
		LinePtr->changeKillNumber(_VecResult[vecCount].KillNUmber);
		LinePtr->changeSaveNumber(_VecResult[vecCount].SaveNUmber);
	}
}


void PlayResultWindow::Update(float _Delta)
{

}


void PlayResultWindow::ActorRelease()
{
	if (m_ResultFadeWindow)
	{
		m_ResultFadeWindow->ActorRelease();
		m_ResultFadeWindow = nullptr;
	}

	if (m_ResultSummary)
	{
		m_ResultSummary->ActorRelease();
		m_ResultSummary = nullptr;
	}

	for (int LineCount = 0; LineCount < vecPlayResultLine.size(); LineCount++)
	{
		PlayResultLine* PlayResultLinePtr = vecPlayResultLine[LineCount];
		if (PlayResultLinePtr)
		{
			PlayResultLinePtr->ActorRelease();
		}
	}

	vecPlayResultLine.clear();
}
