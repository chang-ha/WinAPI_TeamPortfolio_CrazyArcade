#include "ExpAcquisition.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "CommonTexture.h"
#include <cmath>




ExpAcquisition::ExpAcquisition() 
{
}

ExpAcquisition::~ExpAcquisition() 
{
}


void ExpAcquisition::initExpUI()
{
	setBack();
	setScore();
}

void ExpAcquisition::showExpUI()
{
	if (m_Back)
	{
		m_Back->On();
	}

	for (int NumberCount = 0; NumberCount < vecScore.size(); NumberCount++)
	{
		CommonTexture* Number = vecScore[NumberCount];
		if (Number)
		{
			Number->On();
		}
	}
}

void ExpAcquisition::OffExpUI()
{
	if (m_Back)
	{
		m_Back->Off();
	}

	for (int NumberCount = 0; NumberCount < vecScore.size(); NumberCount++)
	{
		CommonTexture* Number = vecScore[NumberCount];
		if (Number)
		{
			Number->Off();
		}
	}
}

void ExpAcquisition::setScoreRender(int _Score)
{
	std::vector<int> ArrNumber;
	ArrNumber.reserve(CONST_ScoreNumberCount);

	int LoopCount = CONST_ScoreNumberCount;
	bool FindNotZERO = false;

	for (int NumberCount = CONST_ScoreNumberCount; NumberCount > 0; --NumberCount)
	{
		int Value = (_Score / static_cast<int>(pow(10, NumberCount - 1))) % 10;
		ArrNumber.push_back(Value);

		if (false == FindNotZERO)
		{

			if (0 != Value)
			{
				FindNotZERO = true;
				continue;
			}

			--LoopCount;
		}
	}

	for (int NumberCount = LoopCount - 1; NumberCount < CONST_ScoreNumberCount; NumberCount++)
	{
		CommonTexture* Number = vecScore[NumberCount];
		if (nullptr == Number)
		{
			MsgBoxAssert("NULL인 벡터배열을 사용했습니다.");
			return;
		}

		int NumberOfDigit = ArrNumber[NumberCount];

		Number->setRendererCopyPos(NumberOfDigit, 0);
	}
}


void ExpAcquisition::Start()
{
}

void ExpAcquisition::setBack()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	m_Back = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_Back)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_Back->loadTexture("Result_EXP_Bill.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
	m_Back->setTexture("Result_EXP_Bill.bmp");
	m_Back->setRendererOrder(7);

	float4 BackScale = m_Back->getTextureScale();
	float4 BackPos = GetPos() + BackScale.Half();

	m_Back->SetPos(BackPos);
	m_Back->Off();
}

void ExpAcquisition::setScore()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}


	vecScore.resize(CONST_ScoreNumberCount);

	for (int NumberCount = 0; NumberCount < CONST_ScoreNumberCount; NumberCount++)
	{
		CommonTexture* Number = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == Number)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		Number->loadTexture("Result_Number.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
		Number->setTexture("Result_Number.bmp");
		Number->setRendererCopyAndRenderScale(9, 0);
		Number->setRendererCopyPos(0, 1);

		float4 NumberScale = Number->getScale();
		float4 NumberPos = GetPos() + CONST_ScoreStartPos + NumberScale.Half() + float4{ NumberScale.X * NumberCount , 0.0f };
		Number->SetPos(NumberPos);
		Number->setRendererOrder(8);
		Number->Off();

		vecScore[NumberCount] = Number;
	}
}


void ExpAcquisition::Update(float _Delta)
{

}

void ExpAcquisition::ActorRelease()
{
	if (m_Back)
	{
		m_Back->ActorRelease();
		m_Back = nullptr;
	}

	for (int NumberCount = 0; NumberCount < vecScore.size(); NumberCount++)
	{
		CommonTexture* Number = vecScore[NumberCount];
		if (Number)
		{
			Number->ActorRelease();
		}
	}

	vecScore.clear();
	Death();
}


void ExpAcquisition::LevelEnd()
{
	ActorRelease();
}