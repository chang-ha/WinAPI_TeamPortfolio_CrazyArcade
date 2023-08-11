#include "StageClearAnimation.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "StringAnimation.h"

StageClearAnimation::StageClearAnimation() 
{
}

StageClearAnimation::~StageClearAnimation() 
{
}


void StageClearAnimation::Start()
{
	m_State = StageClearState::UpperStringDown;
}


void StageClearAnimation::initStartAnimation(int _StageNumber)
{
	if (_StageNumber < 1 || _StageNumber > 2)
	{
		MsgBoxAssert("스테이지 번호를 확인해주세요.");
		return;
	}

	m_StageNumber = _StageNumber;


	loadStringTexture();

	initUpperString();
	initLowerString();
}

void StageClearAnimation::loadStringTexture()
{
	static bool GameStartTextureLoadValue = false;

	if (false == GameStartTextureLoadValue)
	{
		GlobalUtils::TextureFileLoad("StageClear_Upper_1.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");
		GlobalUtils::TextureFileLoad("StageClear_Upper_2.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");
		GlobalUtils::TextureFileLoad("StageClear_Upper_S.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");
		GlobalUtils::TextureFileLoad("StageClear_Upper_T.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");
		GlobalUtils::TextureFileLoad("StageClear_Upper_A.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");
		GlobalUtils::TextureFileLoad("StageClear_Upper_G.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");
		GlobalUtils::TextureFileLoad("StageClear_Upper_E.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");
		GlobalUtils::TextureFileLoad("StageClear_Lower_C.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");
		GlobalUtils::TextureFileLoad("StageClear_Lower_L.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");
		GlobalUtils::TextureFileLoad("StageClear_Lower_E.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");
		GlobalUtils::TextureFileLoad("StageClear_Lower_A.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");
		GlobalUtils::TextureFileLoad("StageClear_Lower_R.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");
		GlobalUtils::TextureFileLoad("StageClear_Lower_!.bmp", "Resources\\Textures\\UI\\PlayStage\\StageClear");

		GameStartTextureLoadValue = true;
	}
}


void StageClearAnimation::initUpperString()
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
	default:
		break;
	}


	for (int UpperCount = 0; UpperCount < CONST_UpperStringCount; UpperCount++)
	{
		StringAnimation* StringAnimationPtr = CurLevel->CreateActor<StringAnimation>(UpdateOrder::UI);
		if (nullptr == StringAnimationPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		std::string FileName = "";
		FileName += "StageClear_Upper_";
		FileName += UpperString[UpperCount];
		FileName += ".bmp";

		StringAnimationPtr->setTexture(FileName);

		float4 StringPos = float4{ CONST_UpperStringXStartPos + CONST_vecUpperXPos[UpperCount] , -CONST_UpperStringYStartPos };
		StringAnimationPtr->SetPos(StringPos);
		StringAnimationPtr->setSpeed(CONST_StringSpeed);
		StringAnimationPtr->setStopYPos(CONST_UpperStopYPos);

		vecUpperString[UpperCount] = StringAnimationPtr;
	}
}


void StageClearAnimation::initLowerString()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	vecLowerString.resize(CONST_LowerStringCount);

	std::string LowerString = "CLEAR!";


	for (int LowerCount = 0; LowerCount < CONST_LowerStringCount; LowerCount++)
	{
		StringAnimation* StringAnimationPtr = CurLevel->CreateActor<StringAnimation>(UpdateOrder::UI);
		if (nullptr == StringAnimationPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		std::string FileName = "";
		FileName += "StageClear_Lower_";
		FileName += LowerString[LowerCount];
		FileName += ".bmp";

		StringAnimationPtr->setTexture(FileName);

		float4 StringPos = float4{ CONST_LowerStringXStartPos + CONST_vecLowerXPos[LowerCount] , CONST_LowerAppearYPos };
		StringAnimationPtr->SetPos(StringPos);
		StringAnimationPtr->setSpeed(CONST_StringSpeed);

		StringAnimationPtr->Off();

		vecLowerString[LowerCount] = StringAnimationPtr;
	}
}


void StageClearAnimation::Update(float _Delta)
{
	UpdateState(_Delta);
}

void StageClearAnimation::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case StageClearState::UpperStringDown:		UpdateUpperStringDown(_Delta);		break;
	case StageClearState::DownStringAppear:		UpdateLowerStringAppear(_Delta);	break;
	default:
		break;
	}
}



void StageClearAnimation::UpdateUpperStringDown(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > CONST_NextMoveTime)
	{
		if (m_MoveNumber > CONST_UpperStringCount)
		{
			m_MoveNumber = 0;
			m_State = StageClearState::DownStringAppear;
			return;
		}
		else if (m_MoveNumber <= CONST_UpperStringCount - 1)
		{
			StringAnimation* StringActor = vecUpperString[m_MoveNumber];
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


void StageClearAnimation::UpdateLowerStringAppear(float _Delta)
{
	if (false == AppearLowerStringValue)
	{
		for (int LowerstringCount = 0; LowerstringCount < CONST_LowerStringCount; LowerstringCount++)
		{
			StringAnimation* LowerString = vecLowerString[LowerstringCount];
			if (nullptr == LowerString)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			LowerString->On();
		}

		AppearLowerStringValue = true;
	}
}

void StageClearAnimation::ActorRelease()
{
	for (int StringCount = 0; StringCount < CONST_UpperStringCount; StringCount++)
	{
		StringAnimation* UpperString = vecUpperString[StringCount];
		if (nullptr == UpperString)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		UpperString->ActorRelease();

		StringAnimation* LowerString = vecLowerString[StringCount];
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


void StageClearAnimation::LevelEnd()
{
	ActorRelease();
}