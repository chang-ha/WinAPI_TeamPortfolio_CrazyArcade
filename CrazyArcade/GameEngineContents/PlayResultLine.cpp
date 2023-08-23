#include "PlayResultLine.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "CommonTexture.h"
#include "ExpAcquisition.h"
#include "ExpUI.h"



PlayResultLine::PlayResultLine() 
{
}

PlayResultLine::~PlayResultLine() 
{
}



void PlayResultLine::Start()
{

}

void PlayResultLine::initResultLine(int _LineNumber)
{
	m_LineNumber = _LineNumber;

	setupLineBack();
	setupLineNubmer();
	setupWinOrLose();
	setupLineRank();
	setupPlayerID();
	setupKillNumber();
	setupSaveNumber();
	setupExp();
	setupLevelUp();
}

void PlayResultLine::setupLineBack()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CommonTexture* LineBack = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == LineBack)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	LineBack->loadTexture("Result_Line.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
	LineBack->setTexture("Result_Line.bmp");

	float4 LineScale = LineBack->getTextureScale();
	float4 LinePos = GetPos() + LineScale.Half();

	LineBack->SetPos(LinePos);
	LineBack->setRendererOrder(6);
	LineBack->Off();

	ResultLine.Back = LineBack;
}

void PlayResultLine::setupLineNubmer()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CommonTexture* LineNumber = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == LineNumber)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	LineNumber->loadTexture("TimeNumber.bmp", "Resources\\Textures\\UI\\Timer");
	LineNumber->setTexture("TimeNumber.bmp");
	LineNumber->setRendererCopyAndRenderScale(9, 0);
	LineNumber->setRendererCopyPos(m_LineNumber + 1, 0);

	float4 LineScale = LineNumber->getScale();
	float4 LinePos = GetPos() + CONST_LineNumberStartPos + LineScale.Half();

	LineNumber->SetPos(LinePos);
	LineNumber->setRendererOrder(7);
	LineNumber->Off();

	ResultLine.LineNumber = LineNumber;
}

void PlayResultLine::setupWinOrLose()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CommonTexture* LineWinOrLose = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == LineWinOrLose)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	LineWinOrLose->loadTexture("Result_WinOrLose.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
	LineWinOrLose->setTexture("Result_WinOrLose.bmp");
	LineWinOrLose->setRendererCopyAndRenderScale(0, 1);

	float4 WinOrLoseScale = LineWinOrLose->getScale();
	float4 WinOrLosePos = GetPos() + CONST_PlayerWinOrLoseStartPos + WinOrLoseScale.Half();

	LineWinOrLose->SetPos(WinOrLosePos);
	LineWinOrLose->setRendererOrder(7);
	LineWinOrLose->Off();

	ResultLine.PlayerWinOrLose = LineWinOrLose;

	changePlayerMatchValue(false);
}

void PlayResultLine::changePlayerMatchValue(const bool _Win)
{
	if (nullptr == ResultLine.PlayerWinOrLose)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	m_GameMatchWinValue = _Win;

	int Result = _Win ? 0 : 1;

	ResultLine.PlayerWinOrLose->setRendererCopyPos(0, Result);
}

void PlayResultLine::setupLineRank()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CommonTexture* LineRank = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == LineRank)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	LineRank->loadTexture("Player_Trophy_Level.bmp", "Resources\\Textures\\UI\\PlayStage");
	LineRank->setTexture("Player_Trophy_Level.bmp");
	LineRank->setRendererCopyAndRenderScale(0, 3);

	float4 PlayerRankScale = LineRank->getScale();
	float4 PlayerRankPos = GetPos() + CONST_PlayerRankStartPos + PlayerRankScale.Half();

	LineRank->SetPos(PlayerRankPos);
	LineRank->setRendererOrder(7);
	LineRank->Off();

	ResultLine.PlayerRank = LineRank;

	int Rank = GlobalValue::g_vecPlayerInfo[m_LineNumber].PlayerLevel;

	changePlayerLevel(Rank);
}

void PlayResultLine::changePlayerLevel(const int _PlayerLevel)
{
	if (nullptr == ResultLine.PlayerRank)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	int Result = _PlayerLevel - 1;

	ResultLine.PlayerRank->setRendererCopyPos(0, Result);

	m_Rank = _PlayerLevel;
}

void PlayResultLine::setupPlayerID()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CommonTexture* PlayerName = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == PlayerName)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	std::string FileName = "";

	switch (m_LineNumber)
	{
	case 0:
		FileName += "Name_Player1.bmp";
		break;
	case 1:
		FileName += "Name_Player2.bmp";
		break;
	default:
		break;
	}

	PlayerName->loadTexture(FileName, "Resources\\Textures\\UI\\PlayStage");
	PlayerName->setTexture(FileName);

	float4 PlayerIDScale = PlayerName->getScale();
	float4 PlayerIdPos = GetPos() + CONST_PlayerIDStartPos + PlayerIDScale.Half();

	PlayerName->SetPos(PlayerIdPos);
	PlayerName->setRendererOrder(7);
	PlayerName->Off();

	ResultLine.PlayerID = PlayerName;
}

void PlayResultLine::setupKillNumber()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	ResultLine.KillNumber.resize(m_KillNumberSlot);

	for (int NumberCount = 0; NumberCount < m_KillNumberSlot; NumberCount++)
	{
		CommonTexture* KillNumber = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == KillNumber)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		KillNumber->loadTexture("Result_Number.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
		KillNumber->setTexture("Result_Number.bmp");
		KillNumber->setRendererCopyAndRenderScale(9, 0);

		float4 NumberScale = KillNumber->getScale();
		float4 NumberPos = GetPos() + CONST_KillNumberStartPos + NumberScale.Half() + 
			float4{ NumberScale.X * static_cast<float>(NumberCount) , 0.0f};

		KillNumber->SetPos(NumberPos);
		KillNumber->setRendererOrder(7);
		KillNumber->Off();

		ResultLine.KillNumber[NumberCount] = KillNumber;
	}
}

void PlayResultLine::changeKillNumber(const int _KillNumber)
{
	if (0 == ResultLine.KillNumber.size())
	{
		return;
	}

	m_killNumber = _KillNumber;

	for (int NumberCount = 0; NumberCount < m_KillNumberSlot; NumberCount++)
	{
		CommonTexture* KillNumber = ResultLine.KillNumber[NumberCount];
		if (nullptr == KillNumber)
		{
			MsgBoxAssert("벡터에 액터가 존재하지 않습니다.");
			return;
		}

		int BoxNumber = m_killNumber;

		switch (NumberCount)
		{
		case 0:
			BoxNumber = _KillNumber / 10;
			break;
		case 1:
			BoxNumber = _KillNumber % 10;
			break;
		default:
			break;
		}

		KillNumber->setRendererCopyPos(BoxNumber, 0);
	}
}


void PlayResultLine::setupSaveNumber()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	ResultLine.SaveNumber.resize(m_SaveNumberSlot);

	for (int NumberCount = 0; NumberCount < m_SaveNumberSlot; NumberCount++)
	{
		CommonTexture* SaveNumber = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == SaveNumber)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		SaveNumber->loadTexture("Result_Number.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
		SaveNumber->setTexture("Result_Number.bmp");
		SaveNumber->setRendererCopyAndRenderScale(9, 0);

		float4 NumberScale = SaveNumber->getScale();
		float4 NumberPos = GetPos() + CONST_SaveNumberStartPos + NumberScale.Half() +
			float4{ NumberScale.X * static_cast<float>(NumberCount) , 0.0f };

		SaveNumber->SetPos(NumberPos);
		SaveNumber->setRendererOrder(7);
		SaveNumber->Off();

		ResultLine.SaveNumber[NumberCount] = SaveNumber;
	}
}

void PlayResultLine::changeSaveNumber(const int _SaveNumber)
{
	if (0 == ResultLine.KillNumber.size())
	{
		return;
	}

	m_SaveNumber = _SaveNumber;

	for (int NumberCount = 0; NumberCount < m_SaveNumberSlot; NumberCount++)
	{
		CommonTexture* KillNumber = ResultLine.KillNumber[NumberCount];
		if (nullptr == KillNumber)
		{
			MsgBoxAssert("벡터에 액터가 존재하지 않습니다.");
			return;
		}

		int BoxNumber = 0;

		switch (NumberCount)
		{
		case 0:
			BoxNumber = _SaveNumber / 10;
			break;
		case 1:
			BoxNumber = _SaveNumber % 10;
			break;
		default:
			break;
		}

		KillNumber->setRendererCopyPos(BoxNumber, 0);
	}
}

void PlayResultLine::setupExp()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	ExpAcquisition* ExpAcquisitionPtr = CurLevel->CreateActor<ExpAcquisition>(UpdateOrder::UI);
	if (nullptr == ExpAcquisitionPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}


	float4 ExpPanelPos = GetPos() + CONST_ExpPanelStartPos;
	ExpAcquisitionPtr->SetPos(ExpPanelPos);
	ExpAcquisitionPtr->initExpUI();

	ExpAcquisitionPtr->Off();

	ResultLine.ExpAcquisition = ExpAcquisitionPtr;


	ExpUI* ExpUIPtr = CurLevel->CreateActor<ExpUI>(UpdateOrder::UI);
	if (nullptr == ExpUIPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	float4 ExpUIPos = GetPos() + CONST_ExpPanelStartPos;

	ExpUIPtr->SetPos(ExpUIPos);
	ExpUIPtr->initExpUI();
	ExpUIPtr->Off();

	ResultLine.ExpUI = ExpUIPtr;
}

void PlayResultLine::setupLevelUp()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	CommonTexture* LevelUp = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == LevelUp)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	LevelUp->loadTexture("Play_LevelUp.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
	LevelUp->setTexture("Play_LevelUp.bmp");

	float4 LevelUpScale = LevelUp->getScale();
	float4 LevelUpPos = GetPos() + CONST_LevelUpStartPos + LevelUpScale.Half();

	LevelUp->SetPos(LevelUpPos);
	LevelUp->setRendererOrder(7);
	LevelUp->Off();

	ResultLine.LevelUp = LevelUp;
}

void PlayResultLine::onResultLine()
{
	m_ShowLineValue = true;

	if (ResultLine.Back)
	{
		ResultLine.Back->On();
	}

	if (ResultLine.LineNumber)
	{
		ResultLine.LineNumber->On();
	}

	if (ResultLine.PlayerWinOrLose)
	{
		ResultLine.PlayerWinOrLose->On();
	}

	if (ResultLine.PlayerRank)
	{
		ResultLine.PlayerRank->On();
	}

	if (ResultLine.PlayerID)
	{
		ResultLine.PlayerID->On();
	}

	for (int NumberCount = 0; NumberCount < m_KillNumberSlot; NumberCount++)
	{
		if (ResultLine.KillNumber[NumberCount])
		{
			ResultLine.KillNumber[NumberCount]->On();
		}
	}

	for (int NumberCount = 0; NumberCount < m_SaveNumberSlot; NumberCount++)
	{
		if (ResultLine.SaveNumber[NumberCount])
		{
			ResultLine.SaveNumber[NumberCount]->On();
		}
	}

	if (ResultLine.ExpAcquisition)
	{
		ResultLine.ExpAcquisition->Off();
	}

	if (ResultLine.ExpUI)
	{
		ResultLine.ExpUI->Off();
	}
}

void PlayResultLine::Update(float _Delta)
{
	if (true == m_ShowLineValue)
	{
		updateEXP();
		updateRank();
		updateState(_Delta);
	}

}

void PlayResultLine::updateEXP()
{
	if (false == m_updateExpCheckValue)
	{
		int Rank = GlobalValue::g_vecPlayerInfo[m_LineNumber].PlayerLevel;

		if (Rank >= MAX_PLAYER_LEVEL)
		{
			return;
		}

		int EXPIncreseAmount = m_GameMatchWinValue ? CONST_WinEXPIncreaseAmount : 0;
		EXPIncreseAmount += m_killNumber* CONST_KillEXPAmount + m_SaveNumber * CONST_SaveEXPAmount;

		if (ResultLine.ExpAcquisition)
		{
			ResultLine.ExpAcquisition->setScoreRender(EXPIncreseAmount);
		}
		

		m_ExpIncreaseValue = EXPIncreseAmount;

		int CurrentExp = GlobalValue::g_vecPlayerInfo[m_LineNumber].CurrentExp;

		while (true)
		{
			int SumEXP = CurrentExp + EXPIncreseAmount;
			int ExpNumber = Rank - 1;
			int LevelEXPAmount = GlobalValue::g_ExpArr[ExpNumber];

			int EXPCalculatedValue = 0;

			if (SumEXP >= LevelEXPAmount)
			{
				if (false == m_ExpUpdateCheckValue)
				{
					if (ResultLine.ExpUI)
					{
						ResultLine.ExpUI->changePercent(CurrentExp, LevelEXPAmount, LevelEXPAmount);
					}

					m_ExpUpdateCheckValue = true;
				}

				EXPIncreseAmount = SumEXP - LevelEXPAmount;
				CurrentExp = 0;

				++Rank;
				++GlobalValue::g_vecPlayerInfo[m_LineNumber].PlayerLevel;
				if (GlobalValue::g_vecPlayerInfo[m_LineNumber].PlayerLevel >= MAX_PLAYER_LEVEL)
				{
					break;
				}
			}
			else if (SumEXP < LevelEXPAmount)
			{
				if (false == m_ExpUpdateCheckValue)
				{
					if (ResultLine.ExpUI)
					{
						ResultLine.ExpUI->changePercent(CurrentExp, SumEXP, LevelEXPAmount);
					}

					m_ExpUpdateCheckValue = true;
				}

				CurrentExp = SumEXP;
				break;
			}
		}

		GlobalValue::g_vecPlayerInfo[m_LineNumber].CurrentExp = CurrentExp;

		m_updateExpCheckValue = true;
	}
}

void PlayResultLine::updateRank()
{
	if (true == m_RankUpdateValue)
	{
		return;
	}

	int Rank = GlobalValue::g_vecPlayerInfo[m_LineNumber].PlayerLevel;

	if (m_Rank != Rank)
	{
		changePlayerLevel(Rank);

		if (ResultLine.LevelUp)
		{
			ResultLine.LevelUp->On();
		}

		m_Rank = Rank;
	}

	m_RankUpdateValue = true;
}

void PlayResultLine::updateState(float _Delta)
{
	if (ExpState::Max == m_State)
	{
		changeState(ExpState::ExpAcquisition);
	}

	StateTime += _Delta;

	if (StateTime > CONST_EachStateDuration)
	{
		switch (m_State)
		{
		case ExpState::ExpUI:
			changeState(ExpState::ExpAcquisition);
			break;
		case ExpState::ExpAcquisition:
			changeState(ExpState::ExpUI);
			break;
		default:
			break;
		}
	}
}

void PlayResultLine::changeState(ExpState _State)
{
	if (_State != m_State)
	{
		switch (_State)
		{
		case ExpState::ExpUI:
			startExpUI();
			break;
		case ExpState::ExpAcquisition:
			startExpAcquisition();
			break;
		default:
			break;
		}

		m_State = _State;
	}
}

void PlayResultLine::startExpUI()
{
	StateTime = 0.0f;

	if (ResultLine.ExpAcquisition)
	{
		ResultLine.ExpAcquisition->Off();
		ResultLine.ExpAcquisition->OffExpUI();
	}

	if (ResultLine.ExpUI)
	{
		ResultLine.ExpUI->On();
		ResultLine.ExpUI->showExpUI();
	}
}


void PlayResultLine::startExpAcquisition()
{
	StateTime = 0.0f;

	if (ResultLine.ExpAcquisition)
	{
		ResultLine.ExpAcquisition->On();
		ResultLine.ExpAcquisition->showExpUI();
	}

	if (ResultLine.ExpUI)
	{
		ResultLine.ExpUI->Off();
		ResultLine.ExpUI->OffExpUI();
	}
}


void PlayResultLine::ActorRelease()
{
	if (ResultLine.Back)
	{
		ResultLine.Back->ActorRelease();
		ResultLine.Back = nullptr;
	}

	if (ResultLine.LineNumber)
	{
		ResultLine.LineNumber->ActorRelease();
		ResultLine.LineNumber = nullptr;
	}

	if (ResultLine.PlayerWinOrLose)
	{
		ResultLine.PlayerWinOrLose->ActorRelease();
		ResultLine.PlayerWinOrLose = nullptr;
	}

	if (ResultLine.PlayerRank)
	{
		ResultLine.PlayerRank->ActorRelease();
		ResultLine.PlayerRank = nullptr;
	}

	if (ResultLine.PlayerID)
	{
		ResultLine.PlayerID->ActorRelease();
		ResultLine.PlayerID = nullptr;
	}

	for (int vecCount = 0; vecCount < ResultLine.KillNumber.size(); vecCount++)
	{
		CommonTexture* Number = ResultLine.KillNumber[vecCount];
		if (Number)
		{
			Number->ActorRelease();
		}
	}

	ResultLine.KillNumber.clear();


	for (int vecCount = 0; vecCount < ResultLine.SaveNumber.size(); vecCount++)
	{
		CommonTexture* Number = ResultLine.SaveNumber[vecCount];
		if (Number)
		{
			Number->ActorRelease();
		}
	}

	ResultLine.SaveNumber.clear();

	if (ResultLine.ExpAcquisition)
	{
		ResultLine.ExpAcquisition->ActorRelease();
		ResultLine.ExpAcquisition = nullptr;
	}

	if (ResultLine.ExpUI)
	{
		ResultLine.ExpUI->ActorRelease();
		ResultLine.ExpUI = nullptr;
	}

	if (ResultLine.LevelUp)
	{
		ResultLine.LevelUp->ActorRelease();
		ResultLine.LevelUp = nullptr;
	}

	Death();
}

void PlayResultLine::LevelEnd()
{
	ActorRelease();
}

