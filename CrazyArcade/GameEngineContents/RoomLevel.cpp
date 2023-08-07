#include "RoomLevel.h"
#include "GlobalValue.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"
#include "ActorEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineSprite.h>


#include "BackGround.h"
#include "MapSelectWindow.h"
#include "Button.h"
#include "CharacterRoomButton.h"
#include "CharacterTraits.h"
#include "CommonTexture.h"
#include "FadeScreen.h"
#include "FadeObject.h"



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
	//ButtonPtr->setButtonSound(ButtonEventState::Click, )

	//ButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickGameStartButton);


	GameExitButtonPtr->setButtonPos(m_GameExitButtonStartPos);
	vecButton[static_cast<int>(ButtonActor::GameExit)] = GameExitButtonPtr;

	m_ButtonUpdateValue = true;
}

void RoomLevel::clickGameStartButton()
{
	FadeObject::CallFadeOut(this, "UITestStage", 0.4f);
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

	GlobalValue::g_SelectAvailableCharacter1 = AvailableCharacterList::Bazzi;
	GlobalValue::g_SelectCharacter = CharacterList::Bazzi;
	CommonTexture* SelectTexturePtr = vecCharacterSelectUI[static_cast<int>(GlobalValue::g_SelectAvailableCharacter1)].SelectButton;
	if (nullptr == SelectTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	SelectTexturePtr->On();

	CommonTexture* OutlineTexturePtr = vecCharacterSelectUI[static_cast<int>(GlobalValue::g_SelectAvailableCharacter1)].OutlineTexture;
	if (nullptr == OutlineTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	OutlineTexturePtr->On();


	Button* CharacterButtonPtr = vecCharacterButton[static_cast<int>(GlobalValue::g_SelectAvailableCharacter1)];
	if (nullptr == CharacterButtonPtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	CharacterButtonPtr->Off();

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

	m_SelectChecker2PosToButton = float4 { -m_CharacterButtonScale.Half().hX() , -m_CharacterButtonScale.hY() };

	m_SelectChecker2->SetPos(m_SelectedCharacterButtonStartPos + m_CharacterButtonScale.Half() + m_SelectChecker2PosToButton);
	m_SelectChecker2->setRendererOrder(5);
	m_SelectChecker2->Off();
}

void RoomLevel::changeSelectedCharacterUI(CharacterList _Order)
{
	int CharacterOrder = static_cast<int>(_Order);

	if (CharacterOrder >= static_cast<int>(AvailableCharacterList::Max) && CharacterOrder != static_cast<int>(CharacterList::Random))
	{
		return;
	}



	CommonTexture* PrevSelectTexturePtr = vecCharacterSelectUI[static_cast<int>(GlobalValue::g_SelectAvailableCharacter1)].SelectButton;
	if (nullptr == PrevSelectTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	PrevSelectTexturePtr->Off();

	CommonTexture* PrevOutlineTexturePtr = vecCharacterSelectUI[static_cast<int>(GlobalValue::g_SelectAvailableCharacter1)].OutlineTexture;
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
		GlobalValue::g_SelectAvailableCharacter1 = AvailableCharacterList::Random;
	}
	else
	{
		GlobalValue::g_SelectAvailableCharacter1 = static_cast<AvailableCharacterList>(CharacterOrder);
	}

	CommonTexture* SelectTexturePtr = vecCharacterSelectUI[static_cast<int>(GlobalValue::g_SelectAvailableCharacter1)].SelectButton;
	if (nullptr == SelectTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	SelectTexturePtr->On();

	CommonTexture* OutlineTexturePtr = vecCharacterSelectUI[static_cast<int>(GlobalValue::g_SelectAvailableCharacter1)].OutlineTexture;
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


	float4 SelectButtonPos = float4{ (m_SpacingBTWCharacterButton.X + m_CharacterButtonScale.X) * static_cast<float>(CharacterOrder % 4),
				(m_SpacingBTWCharacterButton.Y + m_CharacterButtonScale.Y) * static_cast<float>(CharacterOrder / 4) };

	float4 CharacterButtonPos = m_SelectedCharacterButtonStartPos + m_CharacterButtonScale.Half();

	if (0 == m_SelectRoomNumber)
	{
		m_SelectChecker1->SetPos(CharacterButtonPos + SelectButtonPos + m_SelectChecker1PosToButton);
	}
	else
	{
		m_SelectChecker2->SetPos(CharacterButtonPos + SelectButtonPos + m_SelectChecker2PosToButton);
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

	m_SelectChecker2->setTexture("Select_Character1_Checker.bmp");
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

		vecSelectRoomBorder[m_SelectRoomNumber]->On();
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
			int ChangeValue = m_SelectRoomNumber - 1;
			changeBorder(ChangeValue);
		}
	}
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


void RoomLevel::updateCharacterRoomBorder()
{
	if (true == GameEngineInput::IsPress(VK_RBUTTON))
	{
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

		if (false == SelectButtonPtr->isSpaceButtonState())
		{
			return;
		}

		if (m_SelectRoomNumber != RoomNumber)
		{
			changeBorder(RoomNumber);
			m_SelectChecker2->Off();
		}
	}
}

void RoomLevel::changeBorder(int _Value)
{
	CommonTexture* PrevBorderPtr = vecSelectRoomBorder[m_SelectRoomNumber];
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

	m_SelectRoomNumber = _Value;
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
		float4{ m_DistanceBTWCharacterRoomButton.X + m_SelectRoomScale.X , 0.0f } * static_cast<float>(_Value);

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

}

void RoomLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	FadeObject::g_FadeObject->ReleaseFadeObject();
}