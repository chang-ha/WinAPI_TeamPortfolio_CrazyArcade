#include "PlayCharacterPortrait.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"


#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>



PlayCharacterPortrait::PlayCharacterPortrait() 
{
}

PlayCharacterPortrait::~PlayCharacterPortrait() 
{
}



void PlayCharacterPortrait::Start()
{
	Renderer = CreateRenderer();
	if (nullptr == Renderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	loadPortrait();
}

void PlayCharacterPortrait::loadPortrait()
{
	static bool PlayPortraitTextureLoadValue = false;
	if (false == PlayPortraitTextureLoadValue)
	{
		GlobalUtils::SpriteFileLoad("Play_Portrait_Bazzi_Normal.bmp", "Resources\\Textures\\UI\\PlayStage\\Portrait", 1, 2);
		GlobalUtils::SpriteFileLoad("Play_Portrait_Bazzi_Lose.bmp", "Resources\\Textures\\UI\\PlayStage\\Portrait", 1, 4);
		GlobalUtils::SpriteFileLoad("Play_Portrait_Dao_Normal.bmp", "Resources\\Textures\\UI\\PlayStage\\Portrait", 1, 2);
		GlobalUtils::SpriteFileLoad("Play_Portrait_Dao_Lose.bmp", "Resources\\Textures\\UI\\PlayStage\\Portrait", 1, 4);
		GlobalUtils::SpriteFileLoad("Play_Portrait_Marid_Normal.bmp", "Resources\\Textures\\UI\\PlayStage\\Portrait", 1, 2);
		GlobalUtils::SpriteFileLoad("Play_Portrait_Marid_Lose.bmp", "Resources\\Textures\\UI\\PlayStage\\Portrait", 1, 4);
		GlobalUtils::SpriteFileLoad("Play_Portrait_Kephi_Normal.bmp", "Resources\\Textures\\UI\\PlayStage\\Portrait", 1, 2);
		GlobalUtils::SpriteFileLoad("Play_Portrait_Kephi_Lose.bmp", "Resources\\Textures\\UI\\PlayStage\\Portrait", 1, 4);

		PlayPortraitTextureLoadValue = true;
	}

	GameEngineSprite* Sprite = ResourcesManager::GetInst().FindSprite("Play_Portrait_Bazzi_Normal.bmp");
	if (nullptr == Sprite)
	{
		MsgBoxAssert("��������Ʈ�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	m_PortraitScale = Sprite->GetSprite(0).RenderScale;
}


void PlayCharacterPortrait::initPortrait(int _Value)
{
	if (_Value >= static_cast<int>(AvailableCharacterList::Random))
	{
		MsgBoxAssert("�ش� ĳ������ �ʻ�ȭ�� �������� �ʽ��ϴ�.");
		return;
	}

	if (nullptr == Renderer)
	{
		MsgBoxAssert("�������� �ҷ����� ���߽��ϴ�.");
		return;
	}

	std::string StringArr[static_cast<int>(AvailableCharacterList::Random)] =
	{
		"Bazzi",
		"Dao",
		"Marid",
		"Kephi"
	};

	std::string FileName = "";
	FileName += "Play_Portrait_";
	FileName += StringArr[_Value];


	std::string NormalFileName = FileName;
	NormalFileName += "_Normal.bmp";
	Renderer->CreateAnimationToFrame("Idle", NormalFileName, { 1, 0, 1, 0, 1, 0 }, 0.1f, true);
	Renderer->FindAnimation("Idle")->Inters = { 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 5.0f };


	std::string LoseFileName = FileName;
	LoseFileName += "_Lose.bmp";

	Renderer->CreateAnimationToFrame("Lose", LoseFileName, { 0, 1, 2, 3, 1, 2, 3, 1, 2, 3 }, 0.1f, true);
}



void PlayCharacterPortrait::changeState(PlayPortraitState _State)
{
	if (_State == m_State)
	{
		return;
	}

	m_State = _State;

	if (Renderer)
	{
		switch (m_State)
		{
		case PlayPortraitState::Idle:
			Renderer->ChangeAnimation("Idle");
			break;
		case PlayPortraitState::Lose:
			Renderer->ChangeAnimation("Lose");
			break;
		default:
			break;
		}

		Renderer->SetRenderScaleToTexture();
	}
}

void PlayCharacterPortrait::ActorRelease()
{
	Death();
	if (Renderer)
	{
		Renderer = nullptr;
	}
}