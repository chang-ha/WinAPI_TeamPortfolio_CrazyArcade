#include "RoomLevel.h"
#include "GlobalValue.h"
#include "ContentsEnum.h"
#include "ActorEnum.h"


#include "BackGround.h"
#include "MapSelectWindow.h"
#include "Button.h"
#include "CharacterTraits.h"
#include "CommonTexture.h"


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
	loadAvailableCharacterButton();
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
	vecButton[static_cast<int>(ButtonActor::GameStart)] = GameExitButtonPtr;

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


	std::vector<std::string> CharacterArr =
	{
		"Bazzi",
		"Dao",
		"Marid",
		"Kephi",
		"Ethi",
		"Mos",
		"Uni",
		"Dizni",
		"Su",
		"HooU",
		"Ray",
		"Random",
	};

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
		FileName += CharacterArr[CharacterCount];

		CharacterButtonPtr->setButtonTexture(ButtonState::Normal, FileName + "_Normal.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect", 1, 1);
		CharacterButtonPtr->setButtonTexture(ButtonState::Hover, FileName + "_Hover.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect", 1, 1);
		CharacterButtonPtr->setButtonTexture(ButtonState::Click, FileName + "_Click.bmp", "Resources\\Textures\\UI\\MapSelect\\CharactorSelect", 1, 1);
		float4 ButtonScale = CharacterButtonPtr->getButtonScale();

		CharacterButtonPtr->setButtonPos(m_CharacterButtonStartPos +
			float4{ (m_SpacingBTWCharacterButton.X + ButtonScale.X) * static_cast<float>(CharacterCount % 4),
			(m_SpacingBTWCharacterButton.Y + ButtonScale.Y)* static_cast<float>(CharacterCount / 4)});


		vecCharacterButton[CharacterCount] = CharacterButtonPtr;
	}


	//ButtonPtr->setButtonSound(ButtonEventState::Click, )

	/*ButtonPtr->setCallback<RoomLevel>(ButtonEventState::Click, this, &RoomLevel::clickSelectButton);*/



	CharacterSelectButtonLoadValue = true;
}

void RoomLevel::loadAvailableCharacterButton()
{
	vecAvailableCharacterButton.resize(static_cast<int>(CharacterList::Max));


	std::vector<std::string> CharacterArr =
	{
		"Bazzi",
		"Dao",
		"Marid",
		"Kephi",
		"Ethi",
		"Mos",
		"Uni",
		"Dizni",
		"Su",
		"HooU",
		"Ray",
		"Random",
	};



	for (int AvailbleCharacterCount = 0; AvailbleCharacterCount < static_cast<int>(CharacterList::Max); AvailbleCharacterCount++)
	{
		if (AvailbleCharacterCount >= static_cast<int>(CharacterList::Ethi) && AvailbleCharacterCount < static_cast<int>(CharacterList::Random))
		{
			continue;
		}

		std::string Text = "";
		Text += "CharatorSelect_Button_";
		Text += CharacterArr[AvailbleCharacterCount];
		Text += "_Pick.bmp";

		CommonTexture* CharacterPortraitPtr = CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == CharacterPortraitPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		CharacterPortraitPtr->loadTexture(Text, "Resources\\Textures\\UI\\MapSelect\\CharactorSelect");
		CharacterPortraitPtr->setTexture(Text);
		CharacterPortraitPtr->SetPos(float4::ZERO);
		CharacterPortraitPtr->Off();

		vecAvailableCharacterButton[AvailbleCharacterCount] = CharacterPortraitPtr;
	}

	CurrentSelectCharacter = CharacterList::Bazzi;
	CommonTexture* SelectTexturePtr = vecAvailableCharacterButton[static_cast<int>(CurrentSelectCharacter)];
	if (nullptr == SelectTexturePtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	SelectTexturePtr->On();

	Button* CharacterButtonPtr = vecCharacterButton[static_cast<int>(CurrentSelectCharacter)];
	if (nullptr == CharacterButtonPtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	CharacterButtonPtr->Off();
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
	Button* BazziButtonPtr = vecCharacterButton[static_cast<int>(CharacterList::Bazzi)];
	if (nullptr == BazziButtonPtr)
	{
		MsgBoxAssert("액터를 불러오지 못했습니다.");
		return;
	}

	BazziButtonPtr->Off();


}

void RoomLevel::clickDaoCharacterButton()
{

}

void RoomLevel::clickMaridCharacterButton()
{

}

void RoomLevel::clickKephiCharacterButton()
{

}

void RoomLevel::clickEthiCharacterButton()
{

}

void RoomLevel::clickMosCharacterButton()
{

}

void RoomLevel::clickUniCharacterButton()
{

}

void RoomLevel::clickDizniCharacterButton()
{

}

void RoomLevel::clickSuCharacterButton()
{

}

void RoomLevel::clickHooUCharacterButton()
{

}

void RoomLevel::clickRayCharacterButton()
{

}

void RoomLevel::clickRandomCharacterButton()
{

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