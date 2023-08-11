#include "LoseAnimation.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/ResourcesManager.h>



LoseAnimation::LoseAnimation() 
{
}

LoseAnimation::~LoseAnimation() 
{
}




void LoseAnimation::Start()
{
	m_State = StageLoseState::AppearString;
}


void LoseAnimation::initLoseAnimation()
{
	loadStringSprite();
	initLoseString();
}

void LoseAnimation::loadStringSprite()
{
	static bool GameStartTextureLoadValue = false;

	if (false == GameStartTextureLoadValue)
	{
		GlobalUtils::SpriteFileLoad("Lose_L.bmp", "Resources\\Textures\\UI\\PlayStage\\Lose", 2, 1);
		GlobalUtils::SpriteFileLoad("Lose_O.bmp", "Resources\\Textures\\UI\\PlayStage\\Lose", 2, 1);
		GlobalUtils::SpriteFileLoad("Lose_S.bmp", "Resources\\Textures\\UI\\PlayStage\\Lose", 2, 1);
		GlobalUtils::SpriteFileLoad("Lose_E.bmp", "Resources\\Textures\\UI\\PlayStage\\Lose", 2, 1);
		GlobalUtils::SpriteFileLoad("Lose_!.bmp", "Resources\\Textures\\UI\\PlayStage\\Lose", 2, 1);

		GameStartTextureLoadValue = true;
	}
}


void LoseAnimation::initLoseString()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	std::string LoseString = "LOSE!";

	vecLoseRenderer.resize(CONST_LoseStringCount);

	for (int StringCount = 0; StringCount < CONST_LoseStringCount; StringCount++)
	{
		GameEngineRenderer* StringRenderer = CreateRenderer(6);
		if (nullptr == StringRenderer)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		std::string FileName = "";
		FileName += "Lose_";
		FileName += LoseString[StringCount];
		FileName += ".bmp";

		StringRenderer->CreateAnimation("None", FileName, 0, 0, 0.1f, false);
		StringRenderer->CreateAnimationToFrame("Sparkle", FileName, { 1, 0, 1, 0, 1, 0, 1, 0, }, 0.08f, false);
		StringRenderer->FindAnimation("Sparkle")->Inters = { 0.08f, 0.08f, 0.08f, 0.08f, 0.08f, 0.08f, 0.08f, 0.08f };
		StringRenderer->ChangeAnimation("None");

		GameEngineSprite* Sprite = ResourcesManager::GetInst().FindSprite(FileName);
		if (nullptr == Sprite)
		{
			MsgBoxAssert("스프라이트를 불러오지 못했습니다.");
			return;
		}

		float4 StringScale = Sprite->GetSprite(0).RenderScale;

		float4 StringPos = float4{ CONST_LoseStringXStartPos + CONST_vecLoseXPos[StringCount] , CONST_LoseStringYStartPos + StringScale.hY()};
		StringRenderer->SetRenderPos(StringPos);
		StringRenderer->Off();

		vecLoseRenderer[StringCount] = StringRenderer;
	}
}


void LoseAnimation::Update(float _Delta)
{
	UpdateState(_Delta);
}

void LoseAnimation::UpdateState(float _Delta)
{
	switch (m_State)
	{
	case StageLoseState::AppearString	:	UpdateAppearString(_Delta);		break;
	case StageLoseState::SparkleString	:	UpdateFrinkleString(_Delta);	break;
	default:
		break;
	}
}



void LoseAnimation::UpdateAppearString(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > CONST_NextAppearString)
	{
		if (m_AppearNumber >= CONST_LoseStringCount)
		{
			m_State = StageLoseState::SparkleString;
			return;
		}

		vecLoseRenderer[m_AppearNumber]->On();

		StateTime = 0.0f;

		++m_AppearNumber;
	}
}


void LoseAnimation::UpdateFrinkleString(float _Delta)
{
	if (false == FrinkleStringCheckValue)
	{
		for (int LowerstringCount = 0; LowerstringCount < CONST_LoseStringCount; LowerstringCount++)
		{
			GameEngineRenderer* LoseString = vecLoseRenderer[LowerstringCount];
			if (nullptr == LoseString)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			LoseString->ChangeAnimation("Sparkle");
			LoseString->SetRenderScaleToTexture();
		}

		FrinkleStringCheckValue = true;
	}
}


void LoseAnimation::LevelEnd()
{
	ActorRelease();
}

void LoseAnimation::ActorRelease()
{
	for (int VecCount = 0; VecCount < vecLoseRenderer.size(); VecCount++)
	{
		GameEngineRenderer* Renderer = vecLoseRenderer[VecCount];
		if (Renderer)
		{
			Renderer->Death();
		}
	}

	vecLoseRenderer.clear();

	Death();
}