#include "RoomLevel.h"
#include "GlobalValue.h"
#include "ContentsEnum.h"


#include "BackGround.h"
#include "FadeScreen.h"
#include "MapSelectWindow.h"
#include "Button.h"


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

void RoomLevel::loadFadeScreen()
{
	m_FadeScreen = CreateActor<FadeScreen>(UpdateOrder::UI);
	if (nullptr == m_FadeScreen)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_FadeScreen->setAlpha(FadeAlpha);
	float4 WindowScale = GlobalValue::WinScale;
	m_FadeScreen->setRenderScale(WindowScale);
	m_FadeScreen->SetPos(WindowScale.Half());
	m_FadeScreen->Off();
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

	m_ButtonUpdateValue = true;
}






void RoomLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	updateButtonVisibility();
}



void RoomLevel::updateButtonVisibility()
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

			m_ButtonUpdateValue = true;
		}
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




void RoomLevel::Render(float _Delta)
{

}




void RoomLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void RoomLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}