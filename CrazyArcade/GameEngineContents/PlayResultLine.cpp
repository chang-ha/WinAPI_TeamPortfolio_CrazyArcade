#include "PlayResultLine.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "CommonTexture.h"



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
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	CommonTexture* LineBack = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == LineBack)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	CommonTexture* LineNumber = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == LineNumber)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	CommonTexture* LineWinOrLose = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == LineWinOrLose)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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
		MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
		return;
	}

	int Result = _Win ? 0 : 1;

	ResultLine.PlayerWinOrLose->setRendererCopyPos(0, Result);
}

void PlayResultLine::setupLineRank()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	CommonTexture* LineRank = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == LineRank)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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

	int Rank = 0;

	switch (m_LineNumber)
	{
	case 0:
		Rank += GlobalValue::g_Player1Level;
		break;
	case 1:
		Rank += GlobalValue::g_Player2Level;
		break;
	default:
		break;
	}

	changePlayerLevel(Rank);
}

void PlayResultLine::changePlayerLevel(const int _PlayerLevel)
{
	if (nullptr == ResultLine.PlayerRank)
	{
		MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
		return;
	}

	int Result = _PlayerLevel - 1;

	ResultLine.PlayerRank->setRendererCopyPos(0, Result);
}

void PlayResultLine::setupPlayerID()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	CommonTexture* PlayerName = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == PlayerName)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	ResultLine.KillNumber.resize(m_KillNumberSlot);

	for (int NumberCount = 0; NumberCount < m_KillNumberSlot; NumberCount++)
	{
		CommonTexture* KillNumber = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == KillNumber)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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

	for (int NumberCount = 0; NumberCount < m_KillNumberSlot; NumberCount++)
	{
		CommonTexture* KillNumber = ResultLine.KillNumber[NumberCount];
		if (nullptr == KillNumber)
		{
			MsgBoxAssert("���Ϳ� ���Ͱ� �������� �ʽ��ϴ�.");
			return;
		}

		int BoxNumber = 0;

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
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	ResultLine.SaveNumber.resize(m_SaveNumberSlot);

	for (int NumberCount = 0; NumberCount < m_SaveNumberSlot; NumberCount++)
	{
		CommonTexture* SaveNumber = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == SaveNumber)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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

void PlayResultLine::changeSaveNumber(const int _KillNumber)
{
	if (0 == ResultLine.KillNumber.size())
	{
		return;
	}

	for (int NumberCount = 0; NumberCount < m_SaveNumberSlot; NumberCount++)
	{
		CommonTexture* KillNumber = ResultLine.KillNumber[NumberCount];
		if (nullptr == KillNumber)
		{
			MsgBoxAssert("���Ϳ� ���Ͱ� �������� �ʽ��ϴ�.");
			return;
		}

		int BoxNumber = 0;

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

void PlayResultLine::setupExp()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	CommonTexture* Exp = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == Exp)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	Exp->loadTexture("Result_EXP_Bar.bmp", "Resources\\Textures\\UI\\PlayStage\\Result");
	Exp->setTexture("Result_EXP_Bar.bmp");

	float4 ExpPanelScale = Exp->getScale();
	float4 ExpPanelPos = GetPos() + CONST_ExpPanelStartPos + ExpPanelScale.Half();

	Exp->SetPos(ExpPanelPos);
	Exp->setRendererOrder(7);
	Exp->Off();

	ResultLine.Exp = Exp;
}

void PlayResultLine::setupLevelUp()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	CommonTexture* LevelUp = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == LevelUp)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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

	if (ResultLine.Exp)
	{
		ResultLine.Exp->On();
	}

	if (ResultLine.LevelUp)
	{
		ResultLine.LevelUp->On();
	}
}

void PlayResultLine::Update(float _Delta)
{

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

	if (ResultLine.Exp)
	{
		ResultLine.Exp->ActorRelease();
		ResultLine.Exp = nullptr;
	}

	if (ResultLine.LevelUp)
	{
		ResultLine.LevelUp->ActorRelease();
		ResultLine.LevelUp = nullptr;
	}
}