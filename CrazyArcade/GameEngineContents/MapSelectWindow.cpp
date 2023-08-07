#include "MapSelectWindow.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "Button.h"
#include "CommonTexture.h"




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
	loadButton();

	loadMapInfoButton();

}

void MapSelectWindow::loadButton()
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

	CancleButtonPtr->setRenderer(RenderOrder::SecondElementUI);
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

	AcceptButtonPtr->setRenderer(RenderOrder::SecondElementUI);
	AcceptButtonPtr->setButtonTexture(ButtonState::Normal, "Button_MapSelect_Accept_Normal.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	AcceptButtonPtr->setButtonTexture(ButtonState::Click, "Button_MapSelect_Accept_Click.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	AcceptButtonPtr->setButtonTexture(ButtonState::Hover, "Button_MapSelect_Accept_Hover.bmp", "Resources\\Textures\\UI\\Button", 1, 2);
	AcceptButtonPtr->setButtonPos(GetPos() - m_WindowScale.Half() + float4{ 160.0f, 447.0f });
	//AcceptButtonPtr->setButtonSound(ButtonEventState::Click, )

	AcceptButtonPtr->setCallback<MapSelectWindow>(ButtonEventState::Click, this, &MapSelectWindow::clickAcceptButton);

	AcceptButtonPtr->Off();

	vecButton[static_cast<int>(MapSelectButton::Accept)] = AcceptButtonPtr;
}


void MapSelectWindow::loadMapInfoButton()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}


	vecMapInfoButton.resize(static_cast<int>(MapType::Max));

	for (int MapCount = 0; MapCount < static_cast<int>(MapType::Max); MapCount++)
	{
		Button* MapListButton = CurLevel->CreateActor<Button>(UpdateOrder::UI);
		if (nullptr == MapListButton)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		MapListButton->setRenderer(RenderOrder::SecondElementUI);
		MapListButton->setButtonTexture(ButtonState::Normal, "MapSelect_SelectImageBar_Normal.bmp", "Resources\\Textures\\UI\\MapSelect", 1, 1);
		MapListButton->setButtonTexture(ButtonState::Hover, "MapSelect_SelectImageBar_Hover.bmp", "Resources\\Textures\\UI\\MapSelect", 1, 1);
		MapListButton->setButtonTexture(ButtonState::Click, "MapSelect_SelectImageBar_Hover.bmp", "Resources\\Textures\\UI\\MapSelect", 1, 1);

		switch (MapCount)
		{
		case 0:
			MapListButton->setCallback(ButtonEventState::Click, this, &MapSelectWindow::clickSeal1Button);
			break;
		case 1:
			MapListButton->setCallback(ButtonEventState::Click, this, &MapSelectWindow::clickSeal2Button);
			break;
		case 2:
			MapListButton->setCallback(ButtonEventState::Click, this, &MapSelectWindow::clickPenguin1Button);
			break;
		case 3:
			MapListButton->setCallback(ButtonEventState::Click, this, &MapSelectWindow::clickPenguin2Button);
			break;
		default:
			break;
		}

		float4 MapButtonScale = MapListButton->getButtonScale();
		float4 MapCompartStartPos = GetPos() - m_WindowScale.Half() + MapListStartPos +
			float4{ 0.0f , MapButtonScale.Y * static_cast<float>(MapCount) };

		float4 MapCompartPos = MapCompartStartPos + MapButtonScale.Half();

		MapListButton->SetPos(MapCompartPos);
		MapListButton->Off();


		vecMapInfoButton[MapCount].MapCompart = MapListButton;



		CommonTexture* SelectMapPtr = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == SelectMapPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		SelectMapPtr->loadTexture("MapSelect_SelectImageBar_Active.bmp", "Resources\\Textures\\UI\\MapSelect");
		SelectMapPtr->setTexture("MapSelect_SelectImageBar_Active.bmp");

		SelectMapPtr->setRendererOrder(RenderOrder::SecondElementUI);
		SelectMapPtr->SetPos(MapCompartPos);
		
		SelectMapPtr->Off();

		vecMapInfoButton[MapCount].SelectMap = SelectMapPtr;



		CommonTexture* MapIconPtr = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == MapIconPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		std::string IconFileName = "";

		if (MapCount < static_cast<int>(MapType::Peng1))
		{
			IconFileName = "MapSelect_Seal_Icon.bmp";
		}
		else
		{
			IconFileName = "MapSelect_Penguin_Icon.bmp";
		}


		MapIconPtr->loadTexture(IconFileName, "Resources\\Textures\\UI\\MapSelect");
		MapIconPtr->setTexture(IconFileName);
		
		float4 MapIconScale = MapIconPtr->getTextureScale();

		float4 MapIconPos = MapCompartStartPos + MapIconStartPos + MapIconScale.Half();

		MapIconPtr->SetPos(MapIconPos);
		MapIconPtr->setRendererOrder(13);
		MapIconPtr->Off();


		vecMapInfoButton[MapCount].MapIcon = MapIconPtr;



		CommonTexture* MapTextPtr = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == MapTextPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		std::string TextFileName = "";

		if (MapCount < static_cast<int>(MapType::Peng1))
		{
			TextFileName = "MapSelect_Seal_Text.bmp";
		}
		else
		{
			TextFileName = "MapSelect_Penguin_Text.bmp";
		}

		MapTextPtr->loadTexture(TextFileName, "Resources\\Textures\\UI\\MapSelect");
		MapTextPtr->setTexture(TextFileName);

		float4 TextureScale = MapTextPtr->getTextureScale();
		m_MapNameScale = float4{ TextureScale.X , TextureScale.hY() };

		GameEngineRenderer* TextRenderer = MapTextPtr->getRenderer();
		if (nullptr == TextRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}

		TextRenderer->SetCopyScale(m_MapNameScale);
		TextRenderer->SetRenderScale(m_MapNameScale);

		float4 MapTextPos = MapCompartStartPos + MapNameStartPos + m_MapNameScale.Half();

		MapTextPtr->SetPos(MapTextPos);
		MapTextPtr->setRendererOrder(13);
		MapTextPtr->Off();

		vecMapInfoButton[MapCount].MapName = MapTextPtr;



		CommonTexture* MapNumberPtr = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == MapNumberPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		MapNumberPtr->loadTexture("MapSelect_Number.bmp", "Resources\\Textures\\UI\\MapSelect");
		MapNumberPtr->setTexture("MapSelect_Number.bmp");

		GameEngineRenderer* MapLevelRenderer = MapNumberPtr->getRenderer();
		if (MapLevelRenderer)
		{
			float4 TextureScale = MapNumberPtr->getTextureScale();
			m_MapNumberScale = TextureScale.Half();

			MapLevelRenderer->SetCopyScale(m_MapNumberScale);
			MapLevelRenderer->SetRenderScale(m_MapNumberScale);
		}

		float4 MapLevelPos = MapCompartStartPos + MapNumberStartPos + m_MapNumberScale.Half();

		MapNumberPtr->SetPos(MapLevelPos);
		MapNumberPtr->setRendererOrder(13);
		MapNumberPtr->Off();

		vecMapInfoButton[MapCount].MapNumber = MapNumberPtr;
	}

	GlobalValue::g_SelectMap = MapType::Seal1;
	CurSelectMap = MapType::Seal1;


	CommonTexture* NameTexture = vecMapInfoButton[static_cast<int>(CurSelectMap)].MapName;
	if (NameTexture)
	{
		GameEngineRenderer* NameRenderer = NameTexture->getRenderer();
		if (NameRenderer)
		{
			NameRenderer->SetCopyPos(float4{ 0.0f , m_MapNameScale.Y });
		}
	}

	CommonTexture* NumberTexture = vecMapInfoButton[static_cast<int>(CurSelectMap)].MapNumber;
	if (NumberTexture)
	{
		GameEngineRenderer* NumberRenderer = NumberTexture->getRenderer();
		if (NumberRenderer)
		{
			NumberRenderer->SetCopyPos(float4{ m_MapNumberScale.X , 0.0f });
		}
	}

	Button* InitialButtonPtr = vecMapInfoButton[static_cast<int>(MapType::Seal1)].MapCompart;
	if (InitialButtonPtr)
	{
		InitialButtonPtr->Off();
	}
}

void MapSelectWindow::changeMapCompart(MapType _Type)
{
	if (CurSelectMap == _Type)
	{
		return;
	}

	int SelectType = static_cast<int>(_Type);


	CommonTexture* PrevNameTexture = vecMapInfoButton[static_cast<int>(CurSelectMap)].MapName;
	if (PrevNameTexture)
	{
		GameEngineRenderer* NameRenderer = PrevNameTexture->getRenderer();
		if (NameRenderer)
		{
			NameRenderer->SetCopyPos(float4::ZERO);
		}
	}

	CommonTexture* PrevNumberTexture = vecMapInfoButton[static_cast<int>(CurSelectMap)].MapNumber;
	if (PrevNumberTexture)
	{
		GameEngineRenderer* NumberRenderer = PrevNumberTexture->getRenderer();
		if (NumberRenderer)
		{
			NumberRenderer->SetCopyPos(float4::ZERO);
		}
	}

	Button* PrevInitialButtonPtr = vecMapInfoButton[static_cast<int>(CurSelectMap)].MapCompart;
	if (PrevInitialButtonPtr)
	{
		PrevInitialButtonPtr->On();
	}

	CommonTexture* PrevSelectTexture = vecMapInfoButton[static_cast<int>(CurSelectMap)].SelectMap;
	if (PrevSelectTexture)
	{
		PrevSelectTexture->Off();
	}


	CurSelectMap = _Type;


	CommonTexture* NameTexture = vecMapInfoButton[static_cast<int>(_Type)].MapName;
	if (NameTexture)
	{
		GameEngineRenderer* NameRenderer = NameTexture->getRenderer();
		if (NameRenderer)
		{
			NameRenderer->SetCopyPos(float4{ 0.0f , m_MapNameScale.Y });
		}
	}

	CommonTexture* NumberTexture = vecMapInfoButton[static_cast<int>(_Type)].MapNumber;
	if (NumberTexture)
	{
		GameEngineRenderer* NumberRenderer = NumberTexture->getRenderer();
		if (NumberRenderer)
		{
			NumberRenderer->SetCopyPos(float4{ m_MapNumberScale.X , 0.0f });
		}
	}

	Button* InitialButtonPtr = vecMapInfoButton[static_cast<int>(_Type)].MapCompart;
	if (InitialButtonPtr)
	{
		InitialButtonPtr->Off();
	}

	CommonTexture* SelectTexture = vecMapInfoButton[static_cast<int>(_Type)].SelectMap;
	if (SelectTexture)
	{
		SelectTexture->On();
	}
}


void MapSelectWindow::clickSeal1Button()
{
	changeMapCompart(MapType::Seal1);
}

void MapSelectWindow::clickSeal2Button()
{
	changeMapCompart(MapType::Seal2);
}

void MapSelectWindow::clickPenguin1Button()
{
	changeMapCompart(MapType::Peng1);
}

void MapSelectWindow::clickPenguin2Button()
{
	changeMapCompart(MapType::Peng2);
}



void MapSelectWindow::Update(float _Delta)
{
	WindowPanelUI::Update(_Delta);
}



void MapSelectWindow::onPanel()
{
	for (int ButtonCount = 0; ButtonCount < static_cast<int>(MapSelectButton::Max); ButtonCount++)
	{
		Button* ButtonPtr = vecButton[ButtonCount];
		if (nullptr == ButtonPtr)
		{
			MsgBoxAssert("버튼을 불러오지 못했습니다.");
			return;
		}

		ButtonPtr->On();
	}

	for (int MapCount = 0; MapCount < static_cast<int>(MapType::Max); MapCount++)
	{
		Button* MapComPartButton = vecMapInfoButton[MapCount].MapCompart;
		if (MapComPartButton)
		{
			MapComPartButton->On();
		}

		CommonTexture* SelectMapComPartTexture = vecMapInfoButton[MapCount].SelectMap;
		if (SelectMapComPartTexture)
		{
			SelectMapComPartTexture->Off();
		}

		CommonTexture* IconTexture = vecMapInfoButton[MapCount].MapIcon;
		if (IconTexture)
		{
			IconTexture->On();
		}

		CommonTexture* NameTexture = vecMapInfoButton[MapCount].MapName;
		if (NameTexture)
		{
			NameTexture->On();
		}

		CommonTexture* NumberTexture = vecMapInfoButton[MapCount].MapNumber;
		if (NumberTexture)
		{
			NumberTexture->On();
		}
	}


	int SelectMapValue = static_cast<int>(GlobalValue::g_SelectMap);

	Button* MapComPartButton = vecMapInfoButton[SelectMapValue].MapCompart;
	if (MapComPartButton)
	{
		MapComPartButton->Off();
	}

	CommonTexture* SelectMapComPartTexture = vecMapInfoButton[SelectMapValue].SelectMap;
	if (SelectMapComPartTexture)
	{
		SelectMapComPartTexture->On();
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


	for (int MapCount = 0; MapCount < static_cast<int>(MapType::Max); MapCount++)
	{
		Button* MapComPartButton = vecMapInfoButton[MapCount].MapCompart;
		if (MapComPartButton)
		{
			MapComPartButton->Off();
		}

		CommonTexture* SelectMapComPartTexture = vecMapInfoButton[MapCount].SelectMap;
		if (SelectMapComPartTexture)
		{
			SelectMapComPartTexture->Off();
		}

		CommonTexture* IconTexture = vecMapInfoButton[MapCount].MapIcon;
		if (IconTexture)
		{
			IconTexture->Off();
		}

		CommonTexture* NameTexture = vecMapInfoButton[MapCount].MapName;
		if (NameTexture)
		{
			NameTexture->Off();
		}

		CommonTexture* NumberTexture = vecMapInfoButton[MapCount].MapNumber;
		if (NumberTexture)
		{
			NumberTexture->Off();
		}
	}
}



void MapSelectWindow::clickCancleButton()
{
	m_WindowState = WindowState::Close;


	CommonTexture* PrevNameTexture = vecMapInfoButton[static_cast<int>(CurSelectMap)].MapName;
	if (PrevNameTexture)
	{
		GameEngineRenderer* NameRenderer = PrevNameTexture->getRenderer();
		if (NameRenderer)
		{
			NameRenderer->SetCopyPos(float4::ZERO);
		}
	}

	CommonTexture* PrevNumberTexture = vecMapInfoButton[static_cast<int>(CurSelectMap)].MapNumber;
	if (PrevNumberTexture)
	{
		GameEngineRenderer* NumberRenderer = PrevNumberTexture->getRenderer();
		if (NumberRenderer)
		{
			NumberRenderer->SetCopyPos(float4::ZERO);
		}
	}

	CurSelectMap = GlobalValue::g_SelectMap;


	CommonTexture* NameTexture = vecMapInfoButton[static_cast<int>(GlobalValue::g_SelectMap)].MapName;
	if (NameTexture)
	{
		GameEngineRenderer* NameRenderer = NameTexture->getRenderer();
		if (NameRenderer)
		{
			NameRenderer->SetCopyPos(float4{ 0.0f , m_MapNameScale.Y });
		}
	}

	CommonTexture* NumberTexture = vecMapInfoButton[static_cast<int>(GlobalValue::g_SelectMap)].MapNumber;
	if (NumberTexture)
	{
		GameEngineRenderer* NumberRenderer = NumberTexture->getRenderer();
		if (NumberRenderer)
		{
			NumberRenderer->SetCopyPos(float4{ m_MapNumberScale.X , 0.0f });
		}
	}
}

void MapSelectWindow::clickAcceptButton()
{
	m_WindowState = WindowState::Close;

	GlobalValue::g_SelectMap = CurSelectMap;
}

