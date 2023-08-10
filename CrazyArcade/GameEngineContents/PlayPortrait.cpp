#include "PlayPortrait.h"
#include "ContentsEnum.h"
#include "GlobalUtils.h"

#include <GameEnginePlatform/GameEngineWindowTexture.h>


#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "PlayCharacterPortrait.h"
#include "CommonTexture.h"


PlayPortrait::PlayPortrait() 
{
}

PlayPortrait::~PlayPortrait() 
{
}


void PlayPortrait::Start()
{
	static bool PlayPortraitResourceLoadValue = false;
	if (false == PlayPortraitResourceLoadValue)
	{
		GlobalUtils::TextureFileLoad("Name_Player1.bmp", "Resources\\Textures\\UI\\PlayStage");
		GlobalUtils::TextureFileLoad("Name_Player2.bmp", "Resources\\Textures\\UI\\PlayStage");
		GlobalUtils::TextureFileLoad("Player_Trophy_Level.bmp", "Resources\\Textures\\UI\\PlayStage");

		PlayPortraitResourceLoadValue = true;
	}
}


void PlayPortrait::CreatePlayPortrait(int _PortraitNumber)
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	int SelectCharacterNumber = -1;

	switch (_PortraitNumber)
	{
	case 0:
		SelectCharacterNumber = static_cast<int>(GlobalValue::g_SelectAvailableCharacter1);
		break;
	case 1:
		SelectCharacterNumber = static_cast<int>(GlobalValue::g_SelectAvailableCharacter2);
		break;
	default:
		MsgBoxAssert("선택된 자리는 구현되어 있지 않습니다.");
		return;
		break;
	}


	PlayCharacterPortrait* CharacterPortrait = CurLevel->CreateActor<PlayCharacterPortrait>(UpdateOrder::UI);
	if (nullptr == CharacterPortrait)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	CharacterPortrait->initPortrait(SelectCharacterNumber);
	CharacterPortrait->changeState(PlayPortraitState::Idle);

	float4 PortraitScale = CharacterPortrait->getPortraitScale();
	float4 PortraitPos = GetPos() + CONST_PortraitStartPos + PortraitScale.Half();
	CharacterPortrait->SetPos(PortraitPos);

	m_PortraitInfo.Portrait = CharacterPortrait;


	CommonTexture* CharacterName = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == CharacterName)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	std::string FileName = "";

	switch (_PortraitNumber)
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

	CharacterName->loadTexture(FileName, "Resources\\Textures\\UI\\PlayStage");
	CharacterName->setTexture(FileName);

	float4 NameScale = CharacterName->getTextureScale();
	float4 NamePos = GetPos() + CONST_NameStartPos + NameScale.Half();
	
	CharacterName->SetPos(NamePos);

	m_PortraitInfo.Name = CharacterName;



	CommonTexture* CharacterRank = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == CharacterRank)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	CharacterRank->loadTexture("Player_Trophy_Level.bmp", "Resources\\Textures\\UI\\PlayStage");
	CharacterRank->setTexture("Player_Trophy_Level.bmp");
	CharacterRank->setRendererCopyAndRenderScale(0, 3);

	int Rank = 0;

	switch (_PortraitNumber)
	{
	case 0:
		Rank += static_cast<int>(GlobalValue::g_Player1Level);
		break;
	case 1:
		Rank += static_cast<int>(GlobalValue::g_Player2Level);
		break;
	default:
		break;
	}


	CharacterRank->setRendererCopyPos(0, Rank - 1);

	float4 RankScale = CharacterRank->getScale();
	float4 RankPos = GetPos() + CONST_RankStartPos + RankScale.Half();

	CharacterRank->SetPos(RankPos);

	m_PortraitInfo.Rank = CharacterRank;
}


void PlayPortrait::ActorRelease()
{
	if (m_PortraitInfo.Portrait)
	{
		m_PortraitInfo.Portrait->ActorRelease();
		m_PortraitInfo.Portrait = nullptr;
	}

	if (m_PortraitInfo.Name)
	{
		m_PortraitInfo.Name->ActorRelease();
		m_PortraitInfo.Name = nullptr;
	}

	if (m_PortraitInfo.Rank)
	{
		m_PortraitInfo.Rank->ActorRelease();
		m_PortraitInfo.Rank = nullptr;
	}

	Death();
}