#include "RoomLevel.h"
#include "GlobalValue.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"
#include "ActorEnum.h"

#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineSprite.h>


#include "BackGround.h"
#include "MapSelectWindow.h"
#include "Button.h"
#include "CharacterRoomButton.h"
#include "CharacterTraits.h"
#include "CommonTexture.h"
#include "FadeScreen.h"



RoomLevel::RoomLevel()
{
}

RoomLevel::~RoomLevel()
{

}


void RoomLevel::Start()
{
	Back = CreateActor<BackGround>(UpdateOrder::Map);
	if (nullptr == Back)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	Back->Init("RoomLevelBackGround.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());


	loadWindowElement();
	loadButtonElement();
	loadFadeScreen();
}

void RoomLevel::loadWindowElement()
{
	vecWindowPanel.resize(static_cast<int>(WindowPanelActor::Max));


	MapSelectWindow* WindowPanelMapSelectPtr = CreateActor<MapSelectWindow>(UpdateOrder::UI);
	if (nullptr == WindowPanelMapSelectPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	WindowPanelMapSelectPtr->Init("SelectMap_Panel.bmp", "Resources\\Textures\\UI\\MapSelect");
	WindowPanelMapSelectPtr->SetPos(GlobalValue::WinScale.Half());
	WindowPanelMapSelectPtr->initButton();

	vecWindowPanel[static_cast<int>(WindowPanelActor::MapSelect)] = WindowPanelMapSelectPtr;
}



void RoomLevel::loadButtonElement()
{
	loadCharacterButton();
	loadSelectChecker();
	loadAvailableCharacterButton();
	loadRoomCharacterButton();
	loadCharacterTraits();


	vecButton.resize(static_cast<int>(ButtonActor::Max));


	Button* ButtonPtr = CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == ButtonPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	ButtonPtr->setRenderer(RenderOrder::FirstElementUI);
	ButtonPtr->setButtonTexture(ButtonState::Normal, "Button_MapSelect_Normal.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	ButtonPtr->setButtonTexture(ButtonState::Click, "Button_MapSelect_Click.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	ButtonPtr->setButtonTexture(ButtonState::Hover, "Button_MapSelect_Hover.bmp", "Resources\\Textures\\UI\\Button", 1, 2);

	//ButtonPtr->setButtonSound(ButtonEventState::Click, )

	WindowPanelUI* WindowPanelMapSelectPtr = vecWindowPanel[static_cast<int>(WindowPanelActor::MapSelect)];
	ButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickSelectButton);

	ButtonPtr->setButtonPos(float4{ 646.0f, 428.0f });
	vecButton[static_cast<int>(ButtonActor::MapSelect)] = ButtonPtr;




	Button* GameStartButtonPtr = CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == GameStartButtonPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	GameStartButtonPtr->setRenderer(RenderOrder::FirstElementUI);
	GameStartButtonPtr->setButtonTexture(ButtonState::Normal, "Button_GameStart_Normal.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	GameStartButtonPtr->setButtonTexture(ButtonState::Click, "Button_GameStart_Click.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	GameStartButtonPtr->setButtonTexture(ButtonState::Hover, "Button_GameStart_Hover.bmp", "Resources\\Textures\\UI\\Button", 1, 3);

	//ButtonPtr->setButtonSound(ButtonEventState::Click, )
	
	/*ButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickSelectButton);*/


	GameStartButtonPtr->setButtonPos(float4{ 512.0f, 494.0f });
	vecButton[static_cast<int>(ButtonActor::GameStart)] = GameStartButtonPtr;



	Button* GameExitButtonPtr = CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == GameExitButtonPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	GameExitButtonPtr->setRenderer(RenderOrder::FirstElementUI);
	GameExitButtonPtr->setButtonTexture(ButtonState::Normal, "Button_GameExit_Normal.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	GameExitButtonPtr->setButtonTexture(ButtonState::Click, "Button_GameExit_Click.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	GameExitButtonPtr->setButtonTexture(ButtonState::Hover, "Button_GameExit_Hover.bmp", "Resources\\Textures\\UI\\Button", 1, 2);

	//ButtonPtr->setButtonSound(ButtonEventState::Click, )

	/*ButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickSelectButton);*/


	GameExitButtonPtr->setButtonPos(m_GameExitButtonStartPos);
	vecButton[static_cast<int>(ButtonActor::GameExit)] = GameExitButtonPtr;

	m_ButtonUpdateValue = true;
}

void RoomLevel::loadCharacterButton()
{
	static bool CharacterSelectButtonLoadValue = false;

	if (true == CharacterSelectButtonLoadValue)
	{
		return;
	}

	vecCharacterButton.resize(static_cast<int>(CharacterList::Max));



	for (int CharacterCount = 0; CharacterCount < static_cast<int>(CharacterList::Max); CharacterCount++)
	{
		Button* CharacterButtonPtr = CreateActor<Button>(UpdateOrder::UI);
		if (nullptr == CharacterButtonPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		CharacterButtonPtr->setRenderer(RenderOrder::FirstElementUI);


		std::string FileName = "";
		FileName += "CharatorSelect_Button_";
		FileName += vecCharacterString[CharacterCount];

		CharacterButtonPtr->setButtonTexture(ButtonState::Normal, FileName + "_Normal.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect", 1, 1);
		CharacterButtonPtr->setButtonTexture(ButtonState::Hover, FileName + "_Hover.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect", 1, 1);
		CharacterButtonPtr->setButtonTexture(ButtonState::Click, FileName + "_Click.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect", 1, 1);
		m_CharacterButtonScale = CharacterButtonPtr->getButtonScale();

		CharacterButtonPtr->setButtonPos(m_CharacterButtonStartPos +
			float4{ (m_SpacingBTWCharacterButton.X + m_CharacterButtonScale.X) * static_cast<float>(CharacterCount % 4),
			(m_SpacingBTWCharacterButton.Y + m_CharacterButtonScale.Y)* static_cast<float>(CharacterCount / 4)});


		switch (CharacterCount)
		{
		case 0:
			CharacterButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickBazziCharacterButton);
			break;
		case 1:
			CharacterButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickDaoCharacterButton);
			break;
		case 2:
			CharacterButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickMaridCharacterButton);
			break;
		case 3:
			CharacterButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickKephiCharacterButton);
			break;
		case 4:
			CharacterButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickUnavailableCharacterButton);
			break;
		case 5:
			CharacterButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickUnavailableCharacterButton);
			break;
		case 6:
			CharacterButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickUnavailableCharacterButton);
			break;
		case 7:
			CharacterButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickUnavailableCharacterButton);
			break;
		case 8:
			CharacterButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickUnavailableCharacterButton);
			break;
		case 9:
			CharacterButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickUnavailableCharacterButton);
			break;
		case 10:
			CharacterButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickUnavailableCharacterButton);
			break;
		case 11:
			CharacterButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickRandomCharacterButton);
			break;
		default:
			break;
		}

		vecCharacterButton[CharacterCount] = CharacterButtonPtr;
	}

	
	//ButtonPtr->setButtonSound(ButtonEventState::Click, )


	CharacterSelectButtonLoadValue = true;
}


void RoomLevel::loadAvailableCharacterButton()
{
	vecCharacterSelectUI.resize(static_cast<int>(AvailableCharacterList::Max));


	int AvailableCharacterCount = 0;

	for (int CharacterCount = 0; CharacterCount < static_cast<int>(CharacterList::Max); CharacterCount++)
	{
		if (CharacterCount >= static_cast<int>(CharacterList::Ethi) && CharacterCount < static_cast<int>(CharacterList::Random))
		{
			continue;
		}

		{
			std::string ButtonText = "";
			ButtonText += "CharatorSelect_Button_";
			ButtonText += vecCharacterString[CharacterCount];
			ButtonText += "_Pick.bmp";

			CommonTexture* CharacterPortraitPtr = CreateActor<CommonTexture>(UpdateOrder::UI);
			if (nullptr == CharacterPortraitPtr)
			{
				MsgBoxAssert("액터를 생성하지 못했습니다.");
				return;
			}

			CharacterPortraitPtr->loadTexture(ButtonText, "Resources\\Textures\\UI\\MapSelect\\CharactorSelect");
			CharacterPortraitPtr->setTexture(ButtonText);

			float4 ButtonScale = CharacterPortraitPtr->getTextureScale();

			CharacterPortraitPtr->SetPos(m_SelectedCharacterButtonStartPos + ButtonScale.Half() +
				float4{ (m_SpacingBTWSelectedCharacterButton.X + ButtonScale.X) * static_cast<float>(CharacterCount % 4),
				(m_SpacingBTWSelectedCharacterButton.Y + ButtonScale.Y) * static_cast<float>(CharacterCount / 4) });
			CharacterPortraitPtr->Off();


			vecCharacterSelectUI[AvailableCharacterCount].SelectButton = CharacterPortraitPtr;
		}


		{
			std::string OutlineText = "";
			OutlineText += "CharatorSelect_Outline_";
			OutlineText += vecCharacterString[CharacterCount];
			OutlineText += ".bmp";

			CommonTexture* CharacterPortraitPtr = CreateActor<CommonTexture>(UpdateOrder::UI);
			if (nullptr == CharacterPortraitPtr)
			{
				MsgBoxAssert("액터를 생성하지 못했습니다.");
				return;
			}

			CharacterPortraitPtr->loadTexture(OutlineText, "Resources\\Textures\\UI\\MapSelect\\CharactorSelect");
			CharacterPortraitPtr->setTexture(OutlineText);
			float4 OutlineScale = CharacterPortraitPtr->getTextureScale();

			CharacterPortraitPtr->SetPos(m_CharacterOutlineStartPos + OutlineScale.Half());
			CharacterPortraitPtr->Off();


			vecCharacterSelectUI[AvailableCharacterCount].OutlineTexture = CharacterPortraitPtr;
		}

		++AvailableCharacterCount;
	}

	GlobalValue::g_SelectAvailableCharacter = AvailableCharacterList::Bazzi;
	GlobalValue::g_SelectCharacter = CharacterList::Bazzi;
	CommonTexture* SelectTexturePtr = vecCharacterSelectUI[static_cast<int>(GlobalValue::g_SelectAvailableCharacter)].SelectButton;
	if (nullptr == SelectTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	SelectTexturePtr->On();

	CommonTexture* OutlineTexturePtr = vecCharacterSelectUI[static_cast<int>(GlobalValue::g_SelectAvailableCharacter)].OutlineTexture;
	if (nullptr == OutlineTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	OutlineTexturePtr->On();


	Button* CharacterButtonPtr = vecCharacterButton[static_cast<int>(GlobalValue::g_SelectAvailableCharacter)];
	if (nullptr == CharacterButtonPtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	CharacterButtonPtr->Off();

	if (nullptr == m_SelectChecker)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	m_SelectCheckerPosToButton = float4{ m_CharacterButtonScale.Half().hX() , -m_CharacterButtonScale.hY()};

	m_SelectChecker->SetPos(m_SelectedCharacterButtonStartPos + m_CharacterButtonScale.Half() + m_SelectCheckerPosToButton);
	m_SelectChecker->setRendererOrder(5);
}

void RoomLevel::changeSelectedCharacterUI(CharacterList _Order)
{
	int CharacterOrder = static_cast<int>(_Order);

	if (CharacterOrder >= static_cast<int>(AvailableCharacterList::Max) && CharacterOrder != static_cast<int>(CharacterList::Random))
	{
		return;
	}


	CommonTexture* PrevSelectTexturePtr = vecCharacterSelectUI[static_cast<int>(GlobalValue::g_SelectAvailableCharacter)].SelectButton;
	if (nullptr == PrevSelectTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	PrevSelectTexturePtr->Off();

	CommonTexture* PrevOutlineTexturePtr = vecCharacterSelectUI[static_cast<int>(GlobalValue::g_SelectAvailableCharacter)].OutlineTexture;
	if (nullptr == PrevOutlineTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	PrevOutlineTexturePtr->Off();


	Button* PrevCharacterButtonPtr = vecCharacterButton[static_cast<int>(GlobalValue::g_SelectCharacter)];
	if (nullptr == PrevCharacterButtonPtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	PrevCharacterButtonPtr->On();



	GlobalValue::g_SelectCharacter = _Order;

	if (CharacterOrder == static_cast<int>(CharacterList::Random))
	{
		GlobalValue::g_SelectAvailableCharacter = AvailableCharacterList::Random;
	}
	else
	{
		GlobalValue::g_SelectAvailableCharacter = static_cast<AvailableCharacterList>(CharacterOrder);
	}

	CommonTexture* SelectTexturePtr = vecCharacterSelectUI[static_cast<int>(GlobalValue::g_SelectAvailableCharacter)].SelectButton;
	if (nullptr == SelectTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	SelectTexturePtr->On();

	CommonTexture* OutlineTexturePtr = vecCharacterSelectUI[static_cast<int>(GlobalValue::g_SelectAvailableCharacter)].OutlineTexture;
	if (nullptr == OutlineTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	OutlineTexturePtr->On();


	Button* CharacterButtonPtr = vecCharacterButton[static_cast<int>(_Order)];
	if (nullptr == CharacterButtonPtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	CharacterButtonPtr->Off();


	m_SelectChecker->SetPos(m_SelectedCharacterButtonStartPos + m_CharacterButtonScale.Half() + m_SelectCheckerPosToButton +
	float4{ (m_SpacingBTWCharacterButton.X + m_CharacterButtonScale.X) * static_cast<float>(CharacterOrder % 4),
			(m_SpacingBTWCharacterButton.Y + m_CharacterButtonScale.Y) * static_cast<float>(CharacterOrder / 4) });
}

void RoomLevel::loadSelectChecker()
{
	GlobalUtils::TextureFileLoad("Select_Image.bmp", "Resources\\Textures\\UI\\MapSelect");

	m_SelectChecker = CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_SelectChecker)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_SelectChecker->setTexture("Select_Image.bmp");
}


void RoomLevel::loadCharacterTraits()
{
	m_CharacterTraits = CreateActor<CharacterTraits>(UpdateOrder::UI);
	if (nullptr == m_CharacterTraits)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_CharacterTraits->SetPos(m_CharacterTraitsStartPos);
}

void RoomLevel::loadRoomCharacterButton()
{
	vecCharacterRoomButton.resize(m_AvailableRoomCount);

	for (int ButtonCount = 0; ButtonCount < m_AvailableRoomCount; ButtonCount++)
	{
		CharacterRoomButton* CharacterButton = CreateActor<CharacterRoomButton>(UpdateOrder::UI);
		if (nullptr == CharacterButton)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		// 코드가 꼬였습니다. 그래서 리소스를 따로 호출해 크기를 불러옵니다.
		// 코드 구조를 바꾸는데 힘들지 않지만 바꾸지 않은 이유는 버튼을 사용하는 사람이 있고 마감일이 있기 때문에
		// 버튼 내부 구조를 바꾸지 않겠습니다.
		GameEngineSprite* Sprite = GlobalUtils::SpriteFileLoad("Space_Button_Normal.bmp", "Resources\\Textures\\UI\\Button\\CharacterRoom", 1, 1);
		if (nullptr == Sprite)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}


		float4 SpaceButtonScale = Sprite->GetSprite(0).RenderScale;
		float4 ButtonPos = m_CharacterRoomButtonStartPos + 
			float4{ (SpaceButtonScale.X + m_DistanceBTWCharacterRoomButton.X) * static_cast<float>(ButtonCount) , 0.0f  };
		CharacterButton->SetPos(ButtonPos);

		CharacterButton->initCharacterRoomButton();

		vecCharacterRoomButton[ButtonCount] = CharacterButton;
	}



}


void RoomLevel::clickSelectButton()
{
	WindowPanelUI* WindowPanelMapSelectPtr = vecWindowPanel[static_cast<int>(WindowPanelActor::MapSelect)];
	if (nullptr == WindowPanelMapSelectPtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	WindowPanelMapSelectPtr->enableWindow(true);
}

void RoomLevel::clickBazziCharacterButton()
{
	changeSelectedCharacterUI(CharacterList::Bazzi);
}

void RoomLevel::clickDaoCharacterButton()
{
	changeSelectedCharacterUI(CharacterList::Dao);
}

void RoomLevel::clickMaridCharacterButton()
{
	changeSelectedCharacterUI(CharacterList::Marid);
}

void RoomLevel::clickKephiCharacterButton()
{
	changeSelectedCharacterUI(CharacterList::Kephi);
}

void RoomLevel::clickRandomCharacterButton()
{
	changeSelectedCharacterUI(CharacterList::Random);
}

void RoomLevel::clickUnavailableCharacterButton()
{
	changeSelectedCharacterUI(CharacterList::Max);
}


void RoomLevel::loadFadeScreen()
{
	m_FadeScreen = CreateActor<FadeScreen>(UpdateOrder::UI);
	if (nullptr == m_FadeScreen)
	{
		MsgBoxAssert("액터를 생성하지 못헀습니다.");
		return;
	}

	float4 WindowScale = GlobalValue::WinScale;
	float4 WinHalfScale = WindowScale.Half();

	m_FadeScreen->setRenderScale(WindowScale);
	m_FadeScreen->setAlpha(m_FadeScreenAlphaValue);
	m_FadeScreen->SetPos(WinHalfScale);
	m_FadeScreen->Off();
}











void RoomLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	updateFirstElementUIVisibility();
}


void RoomLevel::updateFirstElementUIVisibility()
{
	bool OpenWindowValue = false;

	for (size_t WindowPanelCount = 0; WindowPanelCount < static_cast<int>(WindowPanelActor::Max); WindowPanelCount++)
	{
		OpenWindowValue = vecWindowPanel[WindowPanelCount]->isOpenWindow();
	}

	if (true == OpenWindowValue)
	{
		if (true == m_ButtonUpdateValue)
		{
			for (size_t ButtonCount = 0; ButtonCount < static_cast<int>(ButtonActor::Max); ButtonCount++)
			{
				vecButton[ButtonCount]->enableButton(false);
			}


			for (size_t CharacterButtonCount = 0; CharacterButtonCount < static_cast<int>(CharacterList::Max); CharacterButtonCount++)
			{
				vecCharacterButton[CharacterButtonCount]->enableButton(false);
			}


			if (nullptr == m_FadeScreen)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			m_FadeScreen->On();

			if (nullptr == m_CharacterTraits)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			m_CharacterTraits->Off();


			m_ButtonUpdateValue = false;
		}
	}
	else
	{
		if (false == m_ButtonUpdateValue)
		{
			for (size_t ButtonCount = 0; ButtonCount < static_cast<int>(ButtonActor::Max); ButtonCount++)
			{
				vecButton[ButtonCount]->enableButton(true);
			}


			for (size_t CharacterButtonCount = 0; CharacterButtonCount < static_cast<int>(CharacterList::Max); CharacterButtonCount++)
			{
				vecCharacterButton[CharacterButtonCount]->enableButton(true);
			}


			if (nullptr == m_FadeScreen)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			m_FadeScreen->Off();


			if (nullptr == m_CharacterTraits)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			m_CharacterTraits->On();

			m_ButtonUpdateValue = true;
		}
	}
}







void RoomLevel::Render(float _Delta)
{

}




void RoomLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void RoomLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}