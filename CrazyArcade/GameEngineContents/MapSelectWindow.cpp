#include "MapSelectWindow.h"
#include "ContentsEnum.h"



#include "Button.h"




MapSelectWindow::MapSelectWindow() 
{
}

MapSelectWindow::~MapSelectWindow() 
{
}





void MapSelectWindow::Start()
{
	WindowPanelUI::Start();
}



void MapSelectWindow::initButton()
{
	vecButton.resize(static_cast<int>(MapSelectButton::Max));

	// 취소버튼

	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	Button* CancleButtonPtr = CurLevelPtr->CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == CancleButtonPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	CancleButtonPtr->setRenderer(RenderOrder::SecondButtonUI);
	CancleButtonPtr->setButtonTexture(ButtonState::Normal, "Button_MapSelect_Cancel_Normal.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	CancleButtonPtr->setButtonTexture(ButtonState::Click, "Button_MapSelect_Cancel_Click.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	CancleButtonPtr->setButtonTexture(ButtonState::Hover, "Button_MapSelect_Cancel_Hover.bmp", "Resources\\Textures\\UI\\Button", 1, 2);
	CancleButtonPtr->setButtonPos(GetPos() - m_WindowScale.Half() + float4{ 277.0f, 447.0f });
	//ButtonPtr->setButtonSound(ButtonEventState::Click, )

	CancleButtonPtr->setCallback<MapSelectWindow>(ButtonEventState::Click, this, &MapSelectWindow::clickCancleButton);

	CancleButtonPtr->Off();

	vecButton[static_cast<int>(MapSelectButton::Cancel)] = CancleButtonPtr;



	Button* AcceptButtonPtr = CurLevelPtr->CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == AcceptButtonPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	AcceptButtonPtr->setRenderer(RenderOrder::SecondButtonUI);
	AcceptButtonPtr->setButtonTexture(ButtonState::Normal, "Button_MapSelect_Accept_Normal.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	AcceptButtonPtr->setButtonTexture(ButtonState::Click, "Button_MapSelect_Accept_Click.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	AcceptButtonPtr->setButtonTexture(ButtonState::Hover, "Button_MapSelect_Accept_Hover.bmp", "Resources\\Textures\\UI\\Button", 1, 2);
	AcceptButtonPtr->setButtonPos(GetPos() - m_WindowScale.Half() + float4{ 160.0f, 447.0f });
	//AcceptButtonPtr->setButtonSound(ButtonEventState::Click, )

	AcceptButtonPtr->setCallback<MapSelectWindow>(ButtonEventState::Click, this, &MapSelectWindow::clickCancleButton);

	AcceptButtonPtr->Off();

	vecButton[static_cast<int>(MapSelectButton::Accept)] = AcceptButtonPtr;
}



void MapSelectWindow::Update(float _Delta)
{
	
}



void MapSelectWindow::onPanel()
{
	On();

	for (size_t ButtonCount = 0; ButtonCount < static_cast<int>(MapSelectButton::Max); ButtonCount++)
	{
		Button* ButtonPtr = vecButton[ButtonCount];
		if (nullptr == ButtonPtr)
		{
			MsgBoxAssert("버튼을 불러오지 못했습니다.");
			return;
		}

		ButtonPtr->On();
	}
}

void MapSelectWindow::offPanel()
{
	Off();

	for (size_t ButtonCount = 0; ButtonCount < static_cast<int>(MapSelectButton::Max); ButtonCount++)
	{
		Button* ButtonPtr = vecButton[ButtonCount];
		if (nullptr == ButtonPtr)
		{
			MsgBoxAssert("버튼을 불러오지 못했습니다.");
			return;
		}

		ButtonPtr->Off();
	}
}



void MapSelectWindow::clickCancleButton()
{
	offPanel();
}

void MapSelectWindow::clickAcceptButton()
{
	offPanel();
}