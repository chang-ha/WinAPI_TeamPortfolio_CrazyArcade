#include "PlayTimer.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"

#include <GameEnginePlatform/GameEngineWindowTexture.h>\

#include <GameEngineCore/GameEngineRenderer.h>


PlayTimer::PlayTimer() 
{
}

PlayTimer::~PlayTimer() 
{
}


void PlayTimer::Start()
{
	loadTexture();
	initRenderer();


	m_TimeFlowValue = false;
}


void PlayTimer::loadTexture()
{
	GameEngineWindowTexture* Texure = GlobalUtils::TextureFileLoad("TimeNumber.bmp", "Resources\\Textures\\UI\\Timer");
	if (nullptr == Texure)
	{
		MsgBoxAssert("텍스처를 로드하지 못했습니다.");
		return;
	}

	float4 TextureScale = Texure->GetScale();
	NumberScale = float4{ TextureScale.X * 0.1f , TextureScale.Y };

	GlobalUtils::TextureFileLoad("TimeCenterPoint.bmp", "Resources\\Textures\\UI\\Timer");
}


void PlayTimer::initRenderer()
{
	vecTimerElemnet.resize(static_cast<int>(TimerType::Max));

	GameEngineRenderer* MinuteTensRenderer = CreateRenderer(RenderOrder::FirstElementUI);
	if (nullptr == MinuteTensRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	MinuteTensRenderer->SetTexture("TimeNumber.bmp");
	MinuteTensRenderer->SetCopyPos(float4::ZERO);
	MinuteTensRenderer->SetCopyScale(NumberScale);
	MinuteTensRenderer->SetRenderPos(NumberScale.Half());
	MinuteTensRenderer->SetRenderScale(NumberScale);

	vecTimerElemnet[static_cast<int>(TimerType::MinuteTensRenderer)].m_Renderer = MinuteTensRenderer;



	GameEngineRenderer* MinuteUnitsRenderer = CreateRenderer(RenderOrder::FirstElementUI);
	if (nullptr == MinuteUnitsRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	MinuteUnitsRenderer->SetTexture("TimeNumber.bmp");
	MinuteUnitsRenderer->SetCopyPos(float4::ZERO);
	MinuteUnitsRenderer->SetCopyScale(NumberScale);
	MinuteUnitsRenderer->SetRenderPos(NumberScale.Half() + float4{ 14.0f , 0.0f });
	MinuteUnitsRenderer->SetRenderScale(NumberScale);

	vecTimerElemnet[static_cast<int>(TimerType::MinuteUnitsRenderer)].m_Renderer = MinuteUnitsRenderer;



	GameEngineRenderer* ColonRenderer = CreateRenderer(RenderOrder::FirstElementUI);
	if (nullptr == ColonRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	ColonRenderer->SetTexture("TimeCenterPoint.bmp");
	ColonRenderer->SetRenderPos(NumberScale.Half() + float4{ 23.0f , 0.0f });

	vecTimerElemnet[static_cast<int>(TimerType::Colon)].m_Renderer = ColonRenderer;



	GameEngineRenderer* SecondTensRenderer = CreateRenderer(RenderOrder::FirstElementUI);
	if (nullptr == SecondTensRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	SecondTensRenderer->SetTexture("TimeNumber.bmp");
	SecondTensRenderer->SetCopyPos(float4::ZERO);
	SecondTensRenderer->SetCopyScale(NumberScale);
	SecondTensRenderer->SetRenderPos(NumberScale.Half() + float4{ 32.0f , 0.0f });
	SecondTensRenderer->SetRenderScale(NumberScale);

	vecTimerElemnet[static_cast<int>(TimerType::SecondTensRenderer)].m_Renderer = SecondTensRenderer;



	GameEngineRenderer* SecondUnitsRenderer = CreateRenderer(RenderOrder::FirstElementUI);
	if (nullptr == SecondUnitsRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	SecondUnitsRenderer->SetTexture("TimeNumber.bmp");
	SecondUnitsRenderer->SetCopyPos(float4::ZERO);
	SecondUnitsRenderer->SetCopyScale(NumberScale);
	SecondUnitsRenderer->SetRenderPos(NumberScale.Half() + float4{ 46.0f , 0.0f });
	SecondUnitsRenderer->SetRenderScale(NumberScale);

	vecTimerElemnet[static_cast<int>(TimerType::SecondUnitsRenderer)].m_Renderer = SecondUnitsRenderer;
}




void PlayTimer::Update(float _Delta)
{
	updateTimer(_Delta);
}

void PlayTimer::updateTimer(float _Delta)
{
	if (false == m_TimeFlowValue)
	{
		return;
	}

	m_PlayTimerValue -= _Delta;

	if (m_PlayTimerValue < 0.0f)
	{
		m_TimeFlowValue = false;
	}


	int TimerValue = static_cast<int>(m_PlayTimerValue);
	int MinuteValue = TimerValue / 60;
	int MinuteTensValue = MinuteValue / 10;
	int MinuteUnitsValue = MinuteValue % 10;
	int SecondValue = TimerValue % 60;
	int SecondTensValue = SecondValue / 10;
	int SecondUnitsValue = SecondValue % 10;


	if (MinuteTensValue != vecTimerElemnet[static_cast<int>(TimerType::MinuteTensRenderer)].m_Value)
	{
		if (nullptr != vecTimerElemnet[static_cast<int>(TimerType::MinuteTensRenderer)].m_Renderer)
		{
			vecTimerElemnet[static_cast<int>(TimerType::MinuteTensRenderer)].m_Renderer->
				SetCopyPos(float4{ NumberScale.X * MinuteTensValue , 0.0f });

			vecTimerElemnet[static_cast<int>(TimerType::MinuteTensRenderer)].m_Value = MinuteTensValue;
		}
	}

	if (MinuteUnitsValue != vecTimerElemnet[static_cast<int>(TimerType::MinuteUnitsRenderer)].m_Value)
	{
		if (nullptr != vecTimerElemnet[static_cast<int>(TimerType::MinuteUnitsRenderer)].m_Renderer)
		{
			vecTimerElemnet[static_cast<int>(TimerType::MinuteUnitsRenderer)].m_Renderer->
				SetCopyPos(float4{ NumberScale.X * MinuteUnitsValue , 0.0f });

			vecTimerElemnet[static_cast<int>(TimerType::MinuteUnitsRenderer)].m_Value = MinuteUnitsValue;
		}
	}

	if (SecondTensValue != vecTimerElemnet[static_cast<int>(TimerType::SecondTensRenderer)].m_Value)
	{
		if (nullptr != vecTimerElemnet[static_cast<int>(TimerType::SecondTensRenderer)].m_Renderer)
		{
			vecTimerElemnet[static_cast<int>(TimerType::SecondTensRenderer)].m_Renderer->
				SetCopyPos(float4{ NumberScale.X * SecondTensValue , 0.0f });

			vecTimerElemnet[static_cast<int>(TimerType::SecondTensRenderer)].m_Value = SecondTensValue;
		}
	}

	if (SecondUnitsValue != vecTimerElemnet[static_cast<int>(TimerType::SecondUnitsRenderer)].m_Value)
	{
		if (nullptr != vecTimerElemnet[static_cast<int>(TimerType::SecondUnitsRenderer)].m_Renderer)
		{
			vecTimerElemnet[static_cast<int>(TimerType::SecondUnitsRenderer)].m_Renderer->
				SetCopyPos(float4{ NumberScale.X * SecondUnitsValue , 0.0f });

			vecTimerElemnet[static_cast<int>(TimerType::SecondUnitsRenderer)].m_Value = SecondUnitsValue;
		}
	}
}


void PlayTimer::Render(float _Delta)
{

}