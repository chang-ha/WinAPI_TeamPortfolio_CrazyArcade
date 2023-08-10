#include "GameStartAnimation.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "StageStartActor.h"


GameStartAnimation::GameStartAnimation() 
{
}

GameStartAnimation::~GameStartAnimation() 
{
}


void GameStartAnimation::Start() 
{
	m_State = StageStartState::UpperStringDown;
}


void GameStartAnimation::initStartAnimation(int _StageNumber)
{
	if (_StageNumber < 1 || _StageNumber > 3)
	{
		MsgBoxAssert("스테이지 번호를 확인해주세요.");
		return;
	}

	m_StageNumber = _StageNumber;


	loadStringTexture();

	initUpperString();
	initLowerString();
}

void GameStartAnimation::loadStringTexture()
{
	static bool GameStartTextureLoadValue = false;

	if (false == GameStartTextureLoadValue)
	{
		GlobalUtils::TextureFileLoad("StageStart_Upper_1.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");
		GlobalUtils::TextureFileLoad("StageStart_Upper_2.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");
		GlobalUtils::TextureFileLoad("StageStart_Upper_3.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");
		GlobalUtils::TextureFileLoad("StageStart_Upper_S.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");
		GlobalUtils::TextureFileLoad("StageStart_Upper_T.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");
		GlobalUtils::TextureFileLoad("StageStart_Upper_A.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");
		GlobalUtils::TextureFileLoad("StageStart_Upper_G.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");
		GlobalUtils::TextureFileLoad("StageStart_Upper_E.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");
		GlobalUtils::TextureFileLoad("StageStart_Lower_S.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");
		GlobalUtils::TextureFileLoad("StageStart_Lower_T.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");
		GlobalUtils::TextureFileLoad("StageStart_Lower_A.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");
		GlobalUtils::TextureFileLoad("StageStart_Lower_R.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");
		GlobalUtils::TextureFileLoad("StageStart_Lower_!.bmp", "Resources\\Textures\\UI\\PlayStage\\StageStart");

		GameStartTextureLoadValue = true;
	}
}


void GameStartAnimation::initUpperString()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}


	vecUpperString.resize(CONST_UpperStringCount);

	std::string UpperString = "STAGE";
	switch (m_StageNumber)
	{
	case 1:
		UpperString += "1";
		break;
	case 2:
		UpperString += "2";
		break;
	case 3:
		UpperString += "3";
		break;
	default:
		break;
	}


	for (int UpperCount = 0; UpperCount < CONST_UpperStringCount; UpperCount++)
	{
		StageStartActor* StageStartActorPtr = CurLevel->CreateActor<StageStartActor>(UpdateOrder::UI);
		if (nullptr == StageStartActorPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		std::string FileName = "";
		FileName += "StageStart_Upper_";
		FileName += UpperString[UpperCount];
		FileName += ".bmp";

		StageStartActorPtr->setTexture(FileName);

		float4 StringPos = float4{ CONST_UpperStringXStartPos + CONST_vecUpperXPos[UpperCount] , -CONST_UpperStringYStartPos };
		StageStartActorPtr->SetPos(StringPos);
		StageStartActorPtr->setSpeed(CONST_StringSpeed);
		StageStartActorPtr->setStopYPos(CONST_UpperStopYPos);

		vecUpperString[UpperCount] = StageStartActorPtr;
	}
}


void GameStartAnimation::initLowerString()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	vecLowerString.resize(CONST_LowerStringCount);

	std::string LowerString = "START!";


	for (int LowerCount = 0; LowerCount < CONST_LowerStringCount; LowerCount++)
	{
		StageStartActor* StageStartActorPtr = CurLevel->CreateActor<StageStartActor>(UpdateOrder::UI);
		if (nullptr == StageStartActorPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		std::string FileName = "";
		FileName += "StageStart_Lower_";
		FileName += LowerString[LowerCount];
		FileName += ".bmp";

		StageStartActorPtr->setTexture(FileName);

		float4 StringPos = float4{ CONST_LowerStringXStartPos + CONST_vecLowerXPos[LowerCount] , CONST_LowerAppearYPos };
		StageStartActorPtr->SetPos(StringPos);
		StageStartActorPtr->setSpeed(CONST_StringSpeed);

		StageStartActorPtr->Off();

		vecLowerString[LowerCount] = StageStartActorPtr;
	}
}


void GameStartAnimation::Update(float _Delta) 
{
	UpdateState(_Delta);
}

void GameStartAnimation::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case StageStartState::UpperStringDown:		UpdateUpperStringDown(_Delta);		break;
	case StageStartState::DownStringAppear:		UpdateDownStringAppear(_Delta);		break;
	case StageStartState::GameStart:			UpdateGameStart(_Delta);			break;
	default:
		break;
	}
}



void GameStartAnimation::UpdateUpperStringDown(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > CONST_NextMoveTime)
	{
		if (m_MoveNumber > CONST_UpperStringCount)
		{
			m_MoveNumber = 0;
			m_State = StageStartState::DownStringAppear;
			return;
		}
		else if (m_MoveNumber <= CONST_UpperStringCount - 1)
		{
			StageStartActor* StringActor = vecUpperString[m_MoveNumber];
			if (nullptr == StringActor)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			StringActor->setState(StringAniState::Down);
		}


		StateTime = 0.0f;

		++m_MoveNumber;
	}
}


void GameStartAnimation::UpdateDownStringAppear(float _Delta)
{
	if (false == AppearLowerStringValue)
	{
		for (int LowerstringCount = 0; LowerstringCount < CONST_LowerStringCount; LowerstringCount++)
		{
			StageStartActor* LowerString = vecLowerString[LowerstringCount];
			if (nullptr == LowerString)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			LowerString->On();
		}

		AppearLowerStringValue = true;
	}
	else if (true == AppearLowerStringValue)
	{
		StateTime += _Delta;

		if (StateTime > CONST_DownStringAppearStateDuration)
		{
			setDownStringAppear();
			m_State = StageStartState::GameStart;

			StateTime = 0.0f;
		}
	}
}

void GameStartAnimation::setDownStringAppear()
{
	for (int UpperstringCount = 0; UpperstringCount < CONST_UpperStringCount; UpperstringCount++)
	{
		StageStartActor* UpperString = vecUpperString[UpperstringCount];
		if (nullptr == UpperString)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		UpperString->setStopYPos(-CONST_StringYScale);
	}

	for (int LowerstringCount = 0; LowerstringCount < CONST_LowerStringCount; LowerstringCount++)
	{
		StageStartActor* LowerString = vecLowerString[LowerstringCount];
		if (nullptr == LowerString)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		float4 WinScale = GlobalValue::WinScale;
		float StopYPos = WinScale.Y + CONST_StringYScale;

		LowerString->setStopYPos(StopYPos);
	}
}


void GameStartAnimation::UpdateGameStart(float _Delta)
{
	if (false == GameStartCallValue)
	{
		CallGameStart();

		GameStartCallValue = true;
	}

	StateTime += _Delta;

	if (StateTime > CONST_NextMoveTime)
	{
		if (m_MoveNumber > 8)
		{
			ActorRelease();

			m_State = StageStartState::Max;
			return;
		}
		else if (m_MoveNumber <= CONST_UpperStringCount - 1)
		{
			StageStartActor* UpperString= vecUpperString[m_MoveNumber];
			if (nullptr == UpperString)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			UpperString->setState(StringAniState::Up);


			StageStartActor* LowerString = vecLowerString[m_MoveNumber];
			if (nullptr == LowerString)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			LowerString->setState(StringAniState::Down);
		}


		StateTime = 0.0f;

		++m_MoveNumber;
	}
}


void GameStartAnimation::ActorRelease()
{
	for (int StringCount = 0; StringCount < CONST_UpperStringCount; StringCount++)
	{
		StageStartActor* UpperString = vecUpperString[StringCount];
		if (nullptr == UpperString)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		UpperString->ActorRelease();
		 
		StageStartActor* LowerString = vecLowerString[StringCount];
		if (nullptr == LowerString)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		LowerString->ActorRelease();
	}

	vecUpperString.clear();
	vecLowerString.clear();

	Death();
}