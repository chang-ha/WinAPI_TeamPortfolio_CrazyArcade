#include "ExpUI.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "CommonTexture.h"


ExpUI::ExpUI() 
{
}

ExpUI::~ExpUI() 
{
}



void ExpUI::changePercent(int _initScore, int _TargetScore, int _MaxScore)
{
	m_InitScore = _initScore;
	m_TargetScore = _TargetScore;
	m_MaxScore = _MaxScore;
	m_Volume = static_cast<float>(m_MaxScore) / static_cast<float>(CONST_GaugeCount);

	int Percentage = static_cast<int>((1.0f - static_cast<float>(m_MaxScore - m_InitScore) / static_cast<float>(m_MaxScore)) * 1000.0f);
	changePercent(Percentage);

	changeExpGauge(m_InitScore);
}

void ExpUI::changePercent(int _Percentage)
{
	if (_Percentage > 999)
	{
		_Percentage = 999;
	}


	int TenSpaceNumber = (_Percentage / 100) % 10;
	int OneSpaceNumber = (_Percentage / 10) % 10;
	int DemicalOneSpaceNumber = _Percentage % 10;

	changePercentNumber(PlaceType::Ten, TenSpaceNumber);
	changePercentNumber(PlaceType::One, OneSpaceNumber);
	changePercentNumber(PlaceType::DemicalOne, DemicalOneSpaceNumber);
}


void ExpUI::showExpUI()
{
	if (m_ExpUiInfo.Back)
	{
		m_ExpUiInfo.Back->On();
	}

	if (m_ExpUiInfo.TenSpace)
	{
		m_ExpUiInfo.TenSpace->On();
	}

	if (m_ExpUiInfo.OneSpace)
	{
		m_ExpUiInfo.OneSpace->On();
	}

	if (m_ExpUiInfo.DotSpace)
	{
		m_ExpUiInfo.DotSpace->On();
	}

	if (m_ExpUiInfo.DecimalOneSpace)
	{
		m_ExpUiInfo.DecimalOneSpace->On();
	}

	if (m_ExpUiInfo.Percent)
	{
		m_ExpUiInfo.Percent->On();
	}
}

void ExpUI::OffExpUI()
{
	if (m_ExpUiInfo.Back)
	{
		m_ExpUiInfo.Back->Off();
	}

	if (m_ExpUiInfo.TenSpace)
	{
		m_ExpUiInfo.TenSpace->Off();
	}

	if (m_ExpUiInfo.OneSpace)
	{
		m_ExpUiInfo.OneSpace->Off();
	}

	if (m_ExpUiInfo.DotSpace)
	{
		m_ExpUiInfo.DotSpace->Off();
	}

	if (m_ExpUiInfo.DecimalOneSpace)
	{
		m_ExpUiInfo.DecimalOneSpace->Off();
	}

	if (m_ExpUiInfo.Percent)
	{
		m_ExpUiInfo.Percent->Off();
	}
}

void ExpUI::Start()
{
	loadEXPUITexture();
}

void ExpUI::loadEXPUITexture()
{
	static bool EXPUITextureLoadValue = false;
	if (false == EXPUITextureLoadValue)
	{
		GlobalUtils::TextureFileLoad("Result_EXP_Bar.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
		GlobalUtils::TextureFileLoad("EXPUI_Gauge_Yellow.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
		GlobalUtils::TextureFileLoad("EXPUI_Gauge_Orange.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
		GlobalUtils::TextureFileLoad("EXPUI_Gauge_DarkOrange.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
		GlobalUtils::TextureFileLoad("EXPUI_Gauge_Red.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");

		EXPUITextureLoadValue = true;
	}
}


void ExpUI::initExpUI()
{
	setGauge();
	setupExpInfo();
}

void ExpUI::setGauge()
{
	vecGaugeRender.resize(CONST_GaugeCount);

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("EXPUI_Gauge_Yellow.bmp");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	float4 GaugeScale = Texture->GetScale();

	for (int GuageCount = 0; GuageCount < CONST_GaugeCount; GuageCount++)
	{
		GameEngineRenderer* GaugeRenderer = CreateRenderer(8);
		if (nullptr == GaugeRenderer)
		{
			MsgBoxAssert("렌더러를 생성하지 못했습니다.");
			return;
		}

		std::string FileName = "";

		if (GuageCount < CONST_ColorCountArr[0])
		{
			FileName += "EXPUI_Gauge_Yellow.bmp";
		}
		else if (GuageCount < CONST_ColorCountArr[1])
		{
			FileName += "EXPUI_Gauge_Orange.bmp";
		}
		else if (GuageCount < CONST_ColorCountArr[2])
		{
			FileName += "EXPUI_Gauge_DarkOrange.bmp";
		}
		else
		{
			FileName += "EXPUI_Gauge_Red.bmp";
		}

		GaugeRenderer->SetTexture(FileName);

		float4 GuageRenderPos = CONST_ExpUIGaugeStartPos + GaugeScale.Half() + float4::RIGHT * static_cast<float>(GuageCount);

		GaugeRenderer->SetRenderPos(GuageRenderPos);
		GaugeRenderer->Off();

		vecGaugeRender[GuageCount] = GaugeRenderer;
	}
}

void ExpUI::setupExpInfo()
{
	setupBack();
	setupTenSpace();
	setupOneSpace();
	setupDotSpace();
	setupDecimalOneSpace();
	setupPercent();
}


void ExpUI::setupBack()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CommonTexture* ExpBack = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == ExpBack)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	ExpBack->loadTexture("Result_EXP_Bar.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
	ExpBack->setTexture("Result_EXP_Bar.bmp");

	float4 ExpBackScale = ExpBack->getTextureScale();
	float4 ExpBackPos = GetPos() + ExpBackScale.Half();

	ExpBack->SetPos(ExpBackPos);
	ExpBack->setRendererOrder(7);
	ExpBack->Off();

	m_ExpUiInfo.Back = ExpBack;
}

void ExpUI::setupTenSpace()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CommonTexture* ExpTen = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == ExpTen)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	ExpTen->loadTexture("Result_Number.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
	ExpTen->setTexture("Result_Number.bmp");
	ExpTen->setRendererCopyAndRenderScale(9, 0);
	ExpTen->setRendererCopyPos(0, 0);

	float4 ExpTenScale = ExpTen->getScale();
	float4 ExpTenPos = GetPos() + CONST_TenSpaceStartPos + ExpTenScale.Half();

	ExpTen->SetPos(ExpTenPos);
	ExpTen->setRendererOrder(9);
	ExpTen->Off();

	m_ExpUiInfo.TenSpace = ExpTen;
}

void ExpUI::setupOneSpace()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CommonTexture* ExpOne = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == ExpOne)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	ExpOne->loadTexture("Result_Number.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
	ExpOne->setTexture("Result_Number.bmp");
	ExpOne->setRendererCopyAndRenderScale(9, 0);
	ExpOne->setRendererCopyPos(0, 0);

	float4 ExpOneScale = ExpOne->getScale();
	float4 ExpOnePos = GetPos() + CONST_OneSpaceStartPos + ExpOneScale.Half();

	ExpOne->SetPos(ExpOnePos);
	ExpOne->setRendererOrder(9);
	ExpOne->Off();

	m_ExpUiInfo.OneSpace = ExpOne;
}

void ExpUI::setupDotSpace()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CommonTexture* ExpDot = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == ExpDot)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	ExpDot->loadTexture("EXPUI_Dot.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
	ExpDot->setTexture("EXPUI_Dot.bmp");

	float4 ExpDotScale = ExpDot->getTextureScale();
	float4 ExpDotPos = GetPos() + CONST_DotSpaceStartPos + ExpDotScale.Half();

	ExpDot ->SetPos(ExpDotPos);
	ExpDot ->setRendererOrder(9);
	ExpDot ->Off();

	m_ExpUiInfo.DotSpace = ExpDot;
}

void ExpUI::setupDecimalOneSpace()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CommonTexture* ExpDecimalOne = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == ExpDecimalOne)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	ExpDecimalOne->loadTexture("Result_Number.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
	ExpDecimalOne->setTexture("Result_Number.bmp");
	ExpDecimalOne->setRendererCopyAndRenderScale(9, 0);
	ExpDecimalOne->setRendererCopyPos(0, 0);

	float4 ExpDecimalOneScale = ExpDecimalOne->getScale();
	float4 ExpDecimalOnePos = GetPos() + CONST_DecimalOneSpaceStartPos + ExpDecimalOneScale.Half();

	ExpDecimalOne->SetPos(ExpDecimalOnePos);
	ExpDecimalOne->setRendererOrder(9);
	ExpDecimalOne->Off();

	m_ExpUiInfo.DecimalOneSpace = ExpDecimalOne;
}

void ExpUI::setupPercent()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CommonTexture* ExpPercent = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == ExpPercent)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	ExpPercent->loadTexture("EXPUI_Div.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
	ExpPercent->setTexture("EXPUI_Div.bmp");

	float4 ExpPercentScale = ExpPercent->getTextureScale();
	float4 ExpPercentPos = GetPos() + CONST_PercentStartPos + ExpPercentScale.Half();

	ExpPercent->SetPos(ExpPercentPos);
	ExpPercent->setRendererOrder(9);
	ExpPercent->Off();

	m_ExpUiInfo.Percent = ExpPercent;
}

void ExpUI::changePercentNumber(PlaceType _Type, int _Number)
{
	int ExpRenderNumber = m_RenderScore;

	switch (_Type)
	{
	case PlaceType::Ten:
		ExpRenderNumber = (ExpRenderNumber / 100) % 10;
		break;
	case PlaceType::One:
		ExpRenderNumber = (ExpRenderNumber / 10) % 10;
		break;
	case PlaceType::DemicalOne:
		ExpRenderNumber = ExpRenderNumber % 10;
		break;
	default:
		break;
	}

	if (_Number == ExpRenderNumber)
	{
		return;
	}

	CommonTexture* PlaceType = nullptr;

	switch (_Type)
	{
	case PlaceType::Ten:
		PlaceType = m_ExpUiInfo.TenSpace;
		m_RenderScore += (_Number - ExpRenderNumber) * 100;
		break;
	case PlaceType::One:
		PlaceType = m_ExpUiInfo.OneSpace;
		m_RenderScore += (_Number - ExpRenderNumber) * 10;
		break;
	case PlaceType::DemicalOne:
		PlaceType = m_ExpUiInfo.DecimalOneSpace;
		m_RenderScore += _Number - ExpRenderNumber;
		break;
	default:
		break;
	}

	PlaceType->setRendererCopyPos(_Number, 0);
}

void ExpUI::changeExpGauge(int _Score)
{
	int CurGaugeCount = static_cast<int>(static_cast<float>(_Score) / m_Volume);

	if (CurGaugeCount >= CONST_GaugeCount)
	{
		CurGaugeCount = CONST_GaugeCount - 1;
	}

	if (m_ExpGaugeRenderCount == CurGaugeCount)
	{
		return;
	}

	for (int GaugeCount = m_ExpGaugeRenderCount; GaugeCount < CurGaugeCount; GaugeCount++)
	{
		vecGaugeRender[GaugeCount]->On();
	}

	m_ExpGaugeRenderCount = CurGaugeCount;
}


void ExpUI::Update(float _Delta)
{
	updateExpPercent(_Delta);
}

void ExpUI::updateExpPercent(float _Delta)
{
	UpdateTime += _Delta;
	
	if (UpdateTime > UpdateDuration)
	{
		return;
	}

	int Score = static_cast<int>(static_cast<float>(m_TargetScore - m_InitScore) * UpdateTime / UpdateDuration);
	Score += m_InitScore;

	if (Score > 1)
	{
		int a = 0;
	}

	int Percentage = static_cast<int>((1.0f - static_cast<float>(m_MaxScore - Score) / static_cast<float>(m_MaxScore)) * 1000.0f);
	changePercent(Percentage);
	changeExpGauge(Score);
}

void ExpUI::ActorRelease()
{
	if (m_ExpUiInfo.Back)
	{
		m_ExpUiInfo.Back->Death();
		m_ExpUiInfo.Back = nullptr;
	}

	if (m_ExpUiInfo.TenSpace)
	{
		m_ExpUiInfo.TenSpace->Death();
		m_ExpUiInfo.TenSpace = nullptr;
	}

	if (m_ExpUiInfo.OneSpace)
	{
		m_ExpUiInfo.OneSpace->Death();
		m_ExpUiInfo.OneSpace = nullptr;
	}

	if (m_ExpUiInfo.DotSpace)
	{
		m_ExpUiInfo.DotSpace->Death();
		m_ExpUiInfo.DotSpace = nullptr;
	}

	if (m_ExpUiInfo.DecimalOneSpace)
	{
		m_ExpUiInfo.DecimalOneSpace->Death();
		m_ExpUiInfo.DecimalOneSpace = nullptr;
	}

	if (m_ExpUiInfo.Percent)
	{
		m_ExpUiInfo.Percent->Death();
		m_ExpUiInfo.Percent = nullptr;
	}

	vecGaugeRender.clear();
	Death();
}

void ExpUI::LevelEnd()
{
	ActorRelease();
}