#include "CharacterTraits.h"
#include "ContentsEnum.h"
#include "ActorEnum.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineRenderer.h>



CharacterTraits::CharacterTraits() 
{
}

CharacterTraits::~CharacterTraits() 
{
}


void CharacterTraits::Start()
{
	loadCharacterTraits();
}

void CharacterTraits::loadCharacterTraits()
{
	static bool CharacterTraitsLoadCheck = false;

	if (false == CharacterTraitsLoadCheck)
	{
		GameEngineWindowTexture* Texture = nullptr;

		Texture = GlobalUtils::TextureFileLoad("CharatorSelect_PopPanel.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect");
		if (nullptr == Texture)
		{
			MsgBoxAssert("텍스처를 불러오지 못했습니다.");
			return;
		}

		m_TraitPanelScale = Texture->GetScale();

		Texture = GlobalUtils::TextureFileLoad("CharatorSelect_UpperPanel.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect");
		if (nullptr == Texture)
		{
			MsgBoxAssert("텍스처를 불러오지 못했습니다.");
			return;
		}

		m_UpperPanelScale = Texture->GetScale();
		m_UpperPanelScale = float4{ m_UpperPanelScale.X , m_UpperPanelScale.Y / static_cast<float>(CharacterList::Max) };

		Texture = GlobalUtils::TextureFileLoad("CharatorSelect_TraitBar.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect");
		if (nullptr == Texture)
		{
			MsgBoxAssert("텍스처를 불러오지 못했습니다.");
			return;
		}

		m_TraitBarScale = Texture->GetScale();
		m_TraitBarScale = float4{ m_TraitBarScale.X * 0.5f , m_TraitBarScale.Y };

		CharacterTraitsLoadCheck = true;
	}


	TraitRenderer = CreateRenderer(RenderOrder::FirstElementUI);
	if (nullptr == TraitRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	TraitRenderer->SetTexture("CharatorSelect_PopPanel.bmp");
	TraitRenderer->SetRenderPos(m_TraitPanelScale.Half());


	UpperRenderer = CreateRenderer(RenderOrder::FirstElementUI);
	if (nullptr == UpperRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	UpperRenderer->SetTexture("CharatorSelect_UpperPanel.bmp");
	UpperRenderer->SetCopyScale(m_UpperPanelScale);
	UpperRenderer->SetRenderPos(float4{ m_UpperPanelScale.hX() , -m_UpperPanelScale.hY() });
	UpperRenderer->SetRenderScale(m_UpperPanelScale);



	vecTraitBarRenderer.resize(static_cast<int>(TraitType::Max));
	for (int TypeCount = 0; TypeCount < static_cast<int>(TraitType::Max); TypeCount++)
	{
		std::vector<GameEngineRenderer*>& vecTypeTraitBarRenderer = vecTraitBarRenderer[TypeCount];

		vecTypeTraitBarRenderer.resize(m_TraitMaxCount);

		for (int TraitCount = 0; TraitCount < m_TraitMaxCount; TraitCount++)
		{
			GameEngineRenderer* TraitBarRenderer = CreateRenderer(RenderOrder::FirstElementUI);
			if (nullptr == TraitBarRenderer)
			{
				MsgBoxAssert("렌더러를 생성하지 못했습니다.");
				return;
			}

			TraitBarRenderer->SetTexture("CharatorSelect_TraitBar.bmp");
			TraitBarRenderer->SetCopyScale(m_TraitBarScale);
			TraitBarRenderer->SetRenderPos(m_TraitBarStartPos + m_TraitBarScale.Half() + 
				float4{ m_TraitBarInterScale.X * static_cast<float>(TraitCount) , 
				m_TraitBarInterScale.Y * static_cast<float>(TypeCount) });
			TraitBarRenderer->SetRenderScale(m_TraitBarScale);
		}
	}
}