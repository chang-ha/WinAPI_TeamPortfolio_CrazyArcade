#include "RoomLevel.h"
#include "GlobalValue.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"
#include "ActorEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSprite.h>


#include "BackGround.h"
#include "MapSelectWindow.h"
#include "Button.h"
#include "CharacterRoomButton.h"
#include "CharacterTraits.h"
#include "CommonTexture.h"
#include "FadeScreen.h"
#include "FadeObject.h"


int RoomLevel::g_SelectRoomNumber = 0;
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
	loadSelectedMapComposition();
	loadButtonElement();
	loadFadeScreen();

	GlobalValue::g_ActiveRoomCount = 1;
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

void RoomLevel::loadSelectedMapComposition()
{
	CommonTexture* SelectedMapImg = CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == SelectedMapImg)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	SelectedMapImg->loadTexture("MapSelect_Map.bmp", "Resources\\Textures\\UI\\MapSelect");

	SelectedMapImg->setTexture("MapSelect_Map.bmp");
	SelectedMapImg->setRendererCopyAndRenderScale(0, 3);

	float4 MapImgScale = SelectedMapImg->getScale();

	SelectedMapImg->setRendererCopyPos(MapImgScale, 0, static_cast<int>(GlobalValue::g_SelectMap));
	SelectedMapImg->SetPos(m_SelectedMapImgStarPos + MapImgScale.Half());

	m_SelectedMapInfo.Img = SelectedMapImg;


	CommonTexture* SelectedMapOutline = CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == SelectedMapOutline)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	SelectedMapOutline->loadTexture("SelectedMap_Outline.bmp", "Resources\\Textures\\UI\\MapSelect");

	SelectedMapOutline->setTexture("SelectedMap_Outline.bmp");
	SelectedMapOutline->setRendererCopyAndRenderScale(0, 3);

	float4 MapOutlineScale = SelectedMapOutline->getScale();

	SelectedMapOutline->setRendererCopyPos(MapOutlineScale, 0, static_cast<int>(GlobalValue::g_SelectMap));
	SelectedMapOutline->SetPos(m_SelectedMapOutlineStarPos + MapOutlineScale.Half());


	m_SelectedMapInfo.Outline = SelectedMapOutline;;


	m_CurMapType = GlobalValue::g_SelectMap;
}



void RoomLevel::loadButtonElement()
{
	loadCharacterButton();
	loadSelectChecker();
	loadAvailableCharacterButton();
	loadRoomCharacterButton();
	loadSelectRoomBorder();
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
	ButtonPtr->setButtonSound(ButtonEventState::Click, "Map_Button_Click.wav", "Resources\\Sounds\\Lobby");
	ButtonPtr->setButtonSound(ButtonEventState::Hover, "Select.wav", "Resources\\Sounds\\Lobby");


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
	GameStartButtonPtr->setButtonSound(ButtonEventState::Hover, "Select.wav", "Resources\\Sounds\\Lobby");
	GameStartButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickGameStartButton);

	//ButtonPtr->setButtonSound(ButtonEventState::Click, )
	
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
	GameExitButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickExitButton);
	GameExitButtonPtr->setButtonSound(ButtonEventState::Click, "Game_Exit.wav", "Resources\\Sounds\\Lobby");
	GameExitButtonPtr->setButtonSound(ButtonEventState::Hover, "Select.wav", "Resources\\Sounds\\Lobby");



	GameExitButtonPtr->setButtonPos(m_GameExitButtonStartPos);
	vecButton[static_cast<int>(ButtonActor::GameExit)] = GameExitButtonPtr;

	m_ButtonUpdateValue = true;
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

void RoomLevel::clickGameStartButton()
{
	FadeObject::CallFadeOut(this, "UITestStage", GlobalValue::g_ChangeLevelFadeSpeed);
}

void RoomLevel::clickExitButton()
{
	FadeObject::CallFadeOut(this, "Quit", 2.5f);
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
		CharacterButtonPtr->setButtonSound(ButtonEventState::Hover, "Character_Hover.wav", "Resources\\Sounds\\Lobby");
		CharacterButtonPtr->setButtonSound(ButtonEventState::Click, "Select.wav", "Resources\\Sounds\\Lobby");

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
	vecSelectButton.resize(static_cast<int>(AvailableCharacterList::Max));

	int AvailableCharacterCount = static_cast<int>(AvailableCharacterList::Max);

	for (int LoopCount = 0; LoopCount < static_cast<int>(AvailableCharacterList::Max); LoopCount++)
	{
		{
			CommonTexture* CharacterPortraitPtr = CreateActor<CommonTexture>(UpdateOrder::UI);
			if (nullptr == CharacterPortraitPtr)
			{
				MsgBoxAssert("액터를 생성하지 못했습니다.");
				return;
			}

			CharacterPortraitPtr->loadTexture("CharatorSelect_Button_Pick.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect");
			CharacterPortraitPtr->setTexture("CharatorSelect_Button_Pick.bmp");
			CharacterPortraitPtr->setRendererCopyAndRenderScale(0, static_cast<int>(AvailableCharacterList::Max) - 1);

			CharacterPortraitPtr->setRendererCopyPos(0, LoopCount);

			int CharacterCount = LoopCount;

			if (LoopCount >= static_cast<int>(AvailableCharacterList::Random))
			{
				CharacterCount = static_cast<int>(CharacterList::Random);
			}

			float4 ButtonScale = CharacterPortraitPtr->getScale();
			float4 ButtonPos = m_SelectedCharacterButtonStartPos + ButtonScale.Half() +
				float4{ (m_SpacingBTWSelectedCharacterButton.X + ButtonScale.X) * static_cast<float>(CharacterCount % 4),
				(m_SpacingBTWSelectedCharacterButton.Y + ButtonScale.Y) * static_cast<float>(CharacterCount / 4) };

			CharacterPortraitPtr->SetPos(ButtonPos);
			CharacterPortraitPtr->Off();

			vecSelectButton[LoopCount] = CharacterPortraitPtr;
		}
	}

	CommonTexture* CharacterPortraitPtr = CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == CharacterPortraitPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	CharacterPortraitPtr->loadTexture("CharatorSelect_Outline.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect");
	CharacterPortraitPtr->setTexture("CharatorSelect_Outline.bmp");
	CharacterPortraitPtr->setRendererCopyAndRenderScale(0, static_cast<int>(AvailableCharacterList::Random));
	CharacterPortraitPtr->setRendererCopyPos(0, static_cast<int>(GlobalValue::g_SelectAvailableCharacter1));

	float4 OutlineScale = CharacterPortraitPtr->getScale();
	float4 OutlinePos = m_CharacterOutlineStartPos + OutlineScale.Half();
	CharacterPortraitPtr->SetPos(OutlinePos);

	CharacterPortraitPtr->Off();

	OutlineTexture = CharacterPortraitPtr;



	GlobalValue::g_SelectAvailableCharacter1 = AvailableCharacterList::Bazzi;
	GlobalValue::g_SelectAvailableCharacter2 = AvailableCharacterList::Dao;
	GlobalValue::g_SelectCharacter = CharacterList::Bazzi;

	if (vecSelectButton[static_cast<int>(GlobalValue::g_SelectAvailableCharacter1)])
	{
		vecSelectButton[static_cast<int>(GlobalValue::g_SelectAvailableCharacter1)]->On();
	}

	if (vecSelectButton[static_cast<int>(GlobalValue::g_SelectAvailableCharacter2)])
	{
		vecSelectButton[static_cast<int>(GlobalValue::g_SelectAvailableCharacter2)]->On();
	}
	

	if (OutlineTexture)
	{
		OutlineTexture->setRendererCopyPos(0, static_cast<int>(GlobalValue::g_SelectAvailableCharacter1));
		OutlineTexture->On();
	}

	Button* Character1ButtonPtr = vecCharacterButton[static_cast<int>(GlobalValue::g_SelectAvailableCharacter1)];
	if (nullptr == Character1ButtonPtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	Character1ButtonPtr->Off();


	Button* Character2ButtonPtr = vecCharacterButton[static_cast<int>(GlobalValue::g_SelectAvailableCharacter2)];
	if (nullptr == Character2ButtonPtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	Character2ButtonPtr->Off();



	if (nullptr == m_SelectChecker1)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	m_SelectChecker1PosToButton = float4{ m_CharacterButtonScale.Half().hX() , -m_CharacterButtonScale.hY()};

	m_SelectChecker1->SetPos(m_SelectedCharacterButtonStartPos + m_CharacterButtonScale.Half() + m_SelectChecker1PosToButton);
	m_SelectChecker1->setRendererOrder(5);

	if (nullptr == m_SelectChecker2)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	m_SelectChecker2PosToButton = float4 { 0.0f, -m_CharacterButtonScale.hY() };

	float4 Checker2Pos = m_SelectedCharacterButtonStartPos + m_CharacterButtonScale.Half() + m_SelectChecker2PosToButton +
		float4{ m_CharacterButtonScale.X , 0.0f };
	m_SelectChecker2->SetPos(Checker2Pos);
	m_SelectChecker2->setRendererOrder(5);
}

void RoomLevel::changeSelectedCharacterUI(CharacterList _Order)
{
	int CharacterOrder = static_cast<int>(_Order);

	if (CharacterOrder >= static_cast<int>(AvailableCharacterList::Max) && CharacterOrder != static_cast<int>(CharacterList::Random))
	{
		return;
	}

	changeOutline(_Order);


	AvailableCharacterList PlayerSelectCharacter = AvailableCharacterList::Max;

	switch (g_SelectRoomNumber)
	{
	case 0:
		PlayerSelectCharacter = GlobalValue::g_SelectAvailableCharacter1;
		break;
	case 1:
		PlayerSelectCharacter = GlobalValue::g_SelectAvailableCharacter2;
		break;
	default:
		break;
	}

	CommonTexture* PrevSelectTexturePtr = vecSelectButton[static_cast<int>(PlayerSelectCharacter)];
	if (nullptr == PrevSelectTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	PrevSelectTexturePtr->Off();

	if (AvailableCharacterList::Random == PlayerSelectCharacter)
	{
		Button* PrevCharacterButtonPtr = vecCharacterButton[static_cast<int>(CharacterList::Random)];
		if (nullptr == PrevCharacterButtonPtr)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		PrevCharacterButtonPtr->On();
	}
	else
	{
		Button* PrevCharacterButtonPtr = vecCharacterButton[static_cast<int>(PlayerSelectCharacter)];
		if (nullptr == PrevCharacterButtonPtr)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		PrevCharacterButtonPtr->On();
	}


	if (static_cast<int>(CharacterList::Random) == CharacterOrder)
	{
		PlayerSelectCharacter = AvailableCharacterList::Random;
	}
	else
	{
		PlayerSelectCharacter = static_cast<AvailableCharacterList>(CharacterOrder);
	}

	


	CommonTexture* SelectTexturePtr = vecSelectButton[static_cast<int>(PlayerSelectCharacter)];
	if (nullptr == SelectTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	SelectTexturePtr->On();


	Button* CharacterButtonPtr = vecCharacterButton[static_cast<int>(_Order)];
	if (nullptr == CharacterButtonPtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	CharacterButtonPtr->Off();

	switch (g_SelectRoomNumber)
	{
	case 0:
		GlobalValue::g_SelectAvailableCharacter1 = PlayerSelectCharacter;
		break;
	case 1:
		GlobalValue::g_SelectAvailableCharacter2 = PlayerSelectCharacter;
		break;
	default:
		break;
	}



	float4 SelectButtonPos = float4{ (m_SpacingBTWCharacterButton.X + m_CharacterButtonScale.X) * static_cast<float>(CharacterOrder % 4),
				(m_SpacingBTWCharacterButton.Y + m_CharacterButtonScale.Y) * static_cast<float>(CharacterOrder / 4) };

	float4 CharacterButtonPos = m_SelectedCharacterButtonStartPos + m_CharacterButtonScale.Half();

	if (0 == g_SelectRoomNumber)
	{
		m_SelectChecker1->SetPos(CharacterButtonPos + SelectButtonPos + m_SelectChecker1PosToButton);
	}
	else
	{
		m_SelectChecker2->SetPos(CharacterButtonPos + SelectButtonPos + m_SelectChecker2PosToButton);
	}
}

void RoomLevel::changeOutline(CharacterList _Order)
{
	if (nullptr == OutlineTexture)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	if (CharacterList::Random == _Order)
	{
		OutlineTexture->setRendererCopyPos(0, static_cast<int>(AvailableCharacterList::Random));
	}
	else
	{
		OutlineTexture->setRendererCopyPos(0, static_cast<int>(_Order));
	}
}



void RoomLevel::loadSelectChecker()
{
	GlobalUtils::TextureFileLoad("Select_Character1_Checker.bmp", "Resources\\Textures\\UI\\MapSelect");
	GlobalUtils::TextureFileLoad("Select_Character2_Checker.bmp", "Resources\\Textures\\UI\\MapSelect");

	m_SelectChecker1 = CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_SelectChecker1)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_SelectChecker1->setTexture("Select_Character1_Checker.bmp");


	m_SelectChecker2 = CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_SelectChecker2)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_SelectChecker2->setTexture("Select_Character2_Checker.bmp");
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

		CharacterButton->initCharacterRoomButton(ButtonCount);

		vecCharacterRoomButton[ButtonCount] = CharacterButton;
	}

}


void RoomLevel::loadSelectRoomBorder()
{
	GameEngineWindowTexture* Texture = GlobalUtils::TextureFileLoad("Select_Space_Button.bmp", "Resources\\Textures\\UI\\Button\\CharacterRoom");
	if (Texture)
	{
		vecSelectRoomBorder.resize(m_AvailableRoomCount);

		for (int SelectRoomCount = 0; SelectRoomCount < m_AvailableRoomCount; SelectRoomCount++)
		{
			CommonTexture* SelectRoomBorder = CreateActor<CommonTexture>(UpdateOrder::UI);
			if (SelectRoomBorder)
			{
				SelectRoomBorder->setTexture("Select_Space_Button.bmp");

				m_SelectRoomScale = Texture->GetScale();
				float4 SelectRoomPos = m_CharacterRoomButtonStartPos + m_SelectRoomScale.Half() +
					float4{ (m_SelectRoomScale.X + m_DistanceBTWCharacterRoomButton.X) * static_cast<float>(SelectRoomCount) , 0.0f };

				SelectRoomBorder->SetPos(SelectRoomPos);
				SelectRoomBorder->SetOrder(5);
				SelectRoomBorder->Off();

				vecSelectRoomBorder[SelectRoomCount] = SelectRoomBorder;
			}
		}

		vecSelectRoomBorder[g_SelectRoomNumber]->On();
	}
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
	m_FadeScreen->setAlpha(GlobalValue::g_FadeScreenAlphaValue);
	m_FadeScreen->SetPos(WinHalfScale);
	m_FadeScreen->Off();
}






void RoomLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	updateRoomDetectionChange();
	updateSelectedMapDetectionChange();
	updateFirstElementUIVisibility();
}



void RoomLevel::updateRoomDetectionChange()
{
	updateCharacterRoomBorder();

	for (int EnableRoomCount = 0; EnableRoomCount < m_AvailableRoomCount; EnableRoomCount++)
	{
		CommonTexture* SelectRoomBorderPtr = vecSelectRoomBorder[EnableRoomCount];
		if (nullptr == SelectRoomBorderPtr)
		{
			MsgBoxAssert("경계선을 불러오지 못했습니다.");
			return;
		}

		CharacterRoomButton* RoomButtonPtr = vecCharacterRoomButton[EnableRoomCount];
		if (nullptr == RoomButtonPtr)
		{
			MsgBoxAssert("방 버튼을 불러오지 못했습니다.");
			return;
		}

		if (true == SelectRoomBorderPtr->IsUpdate() && false == RoomButtonPtr->isSpaceButtonState())
		{
			int ChangeValue = g_SelectRoomNumber - 1;
			changeBorder(ChangeValue);
		}
	}
}

void RoomLevel::updateCharacterRoomBorder()
{
	if (true == GameEngineInput::IsPress(VK_RBUTTON))
	{
		// 플레이 룸 번호 확인
		int ReturnValue = returnCharacterRoomNumber();

		static int RoomNumber = -1;
		if (-1 == ReturnValue)
		{
			return;
		}
		else
		{
			RoomNumber = ReturnValue;
		}

		CharacterRoomButton* SelectButtonPtr = vecCharacterRoomButton[RoomNumber];
		if (nullptr == SelectButtonPtr)
		{
			MsgBoxAssert("버튼을 불러오지 못했습니다.");
			return;
		}

		// 활성화 여부
		if (false == SelectButtonPtr->isSpaceButtonState())
		{
			return;
		}

		if (g_SelectRoomNumber != RoomNumber)
		{
			changeBorder(RoomNumber);
		}
	}
}


int RoomLevel::returnCharacterRoomNumber()
{
	for (int ButtonCount = 0; ButtonCount < m_AvailableRoomCount; ButtonCount++)
	{
		if (true == checkCharacterRoomOverMouse(ButtonCount))
		{
			return ButtonCount;
		}
	}

	int ReturnValue = -1;

	return ReturnValue;
}

bool RoomLevel::checkCharacterRoomOverMouse(int _Value)
{
	bool MouseHoverValue = true;

	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();

	float4 LeftTopPos = m_CharacterRoomButtonStartPos +
		float4{ m_DistanceBTWCharacterRoomButton.X + m_SelectRoomScale.X , 0.0f } *static_cast<float>(_Value);

	float4 RightBottomPos = m_CharacterRoomButtonStartPos + m_SelectRoomScale +
		float4{ m_DistanceBTWCharacterRoomButton.X + m_SelectRoomScale.X , 0.0f } *static_cast<float>(_Value);

	if (MousePos.X < LeftTopPos.X)
	{
		MouseHoverValue = false;
	}

	if (MousePos.Y < LeftTopPos.Y)
	{
		MouseHoverValue = false;
	}

	if (MousePos.X > RightBottomPos.X)
	{
		MouseHoverValue = false;
	}

	if (MousePos.Y > RightBottomPos.Y)
	{
		MouseHoverValue = false;
	}

	return MouseHoverValue;
}

void RoomLevel::changeBorder(int _Value)
{
	CommonTexture* PrevBorderPtr = vecSelectRoomBorder[g_SelectRoomNumber];
	if (nullptr == PrevBorderPtr)
	{
		MsgBoxAssert("경계선을 불러오지 못했습니다.");
		return;
	}

	PrevBorderPtr->Off();

	CommonTexture* CurBorderPtr = vecSelectRoomBorder[_Value];
	if (nullptr == CurBorderPtr)
	{
		MsgBoxAssert("경계선을 불러오지 못했습니다.");
		return;
	}

	CurBorderPtr->On();

	g_SelectRoomNumber = _Value;
}

void RoomLevel::updateSelectedMapDetectionChange()
{
	if (GlobalValue::g_SelectMap == m_CurMapType)
	{
		return;
	}

	CommonTexture* MapImg = m_SelectedMapInfo.Img;
	if (nullptr == MapImg)
	{
		MsgBoxAssert("맵의 이미지가 없습니다.");
		return;
	}

	MapImg->setRendererCopyPos(0, static_cast<int>(GlobalValue::g_SelectMap));

	CommonTexture* MapOutline = m_SelectedMapInfo.Outline;
	if (nullptr == MapOutline)
	{
		MsgBoxAssert("맵의 이미지가 없습니다.");
		return;
	}

	MapOutline->setRendererCopyPos(0, static_cast<int>(GlobalValue::g_SelectMap));
}



void RoomLevel::updateFirstElementUIVisibility()
{
	bool OpenWindowValue = false;

	for (int WindowPanelCount = 0; WindowPanelCount < static_cast<int>(WindowPanelActor::Max); WindowPanelCount++)
	{
		OpenWindowValue = vecWindowPanel[WindowPanelCount]->isOpenWindow();
	}

	if (true == OpenWindowValue)
	{
		if (true == m_ButtonUpdateValue)
		{
			for (int ButtonCount = 0; ButtonCount < static_cast<int>(ButtonActor::Max); ButtonCount++)
			{
				vecButton[ButtonCount]->enableButton(false);
			}


			for (int CharacterButtonCount = 0; CharacterButtonCount < static_cast<int>(CharacterList::Max); CharacterButtonCount++)
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
			for (int ButtonCount = 0; ButtonCount < static_cast<int>(ButtonActor::Max); ButtonCount++)
			{
				vecButton[ButtonCount]->enableButton(true);
			}


			for (int CharacterButtonCount = 0; CharacterButtonCount < static_cast<int>(CharacterList::Max); CharacterButtonCount++)
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
	FadeObject::CallFadeIn(this, GlobalValue::g_ChangeLevelFadeSpeed);
}

void RoomLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}