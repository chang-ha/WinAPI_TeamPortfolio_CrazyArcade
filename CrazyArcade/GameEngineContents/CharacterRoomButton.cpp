#include "CharacterRoomButton.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"
#include "ContentsEnum.h"
#include "ActorEnum.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "RoomLevel.h"
#include "Button.h"
#include "CommonTexture.h"


CharacterRoomButton::CharacterRoomButton() 
{
}

CharacterRoomButton::~CharacterRoomButton() 
{
}


void CharacterRoomButton::Start()
{
	
}

void CharacterRoomButton::initCharacterRoomButton(int _RommNumber)
{
	// 호스트는 단 1명
	static bool HostValue = false;
	if (false == HostValue)
	{
		m_HostValue = true;
		m_SpaceButtonState = SpaceButtonState::SpaceButton;

		HostValue = true;
	}

	m_RoomNumber = _RommNumber;

	loadSpaceButton();
	loadSpaceCharacterComposition();
}

void CharacterRoomButton::loadSpaceButton()
{
	if (true == m_HostValue)
	{
		return;
	}

	vecSpaceButton.resize(static_cast<int>(SpaceButtonState::Max));

	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	Button* SpaceButton = CurLevel->CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == SpaceButton)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	SpaceButton->setRenderer(RenderOrder::FirstElementUI);
	SpaceButton->setButtonTexture(ButtonState::Normal, "Space_Button_Normal.bmp", "Resources\\Textures\\UI\\Button\\CharacterRoom", 1, 1);
	SpaceButton->setButtonTexture(ButtonState::Hover, "Space_Button_Hover.bmp", "Resources\\Textures\\UI\\Button\\CharacterRoom", 1, 1);
	SpaceButton->setButtonTexture(ButtonState::Click, "Space_Button_Click.bmp", "Resources\\Textures\\UI\\Button\\CharacterRoom", 1, 1);
	SpaceButton->setCallback<CharacterRoomButton>(ButtonEventState::Click, this, &CharacterRoomButton::clickSpaceButton);
	SpaceButton->setButtonSound(ButtonEventState::Click, "Select.wav", "Resources\\Sounds\\Lobby");
	SpaceButton->setButtonSound(ButtonEventState::Hover, "Hover.wav", "Resources\\Sounds\\Lobby");

	//m_SpaceButton->setButtonSound();

	m_SpaceButtonScale = SpaceButton->getButtonScale();
	SpaceButton->SetPos(GetPos() + m_SpaceButtonScale.Half());

	vecSpaceButton[static_cast<int>(SpaceButtonState::SpaceButton)] = SpaceButton;


	Button* UnSpaceButton = CurLevel->CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == UnSpaceButton)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	UnSpaceButton->setRenderer(RenderOrder::FirstElementUI);
	UnSpaceButton->setButtonTexture(ButtonState::Normal, "UnSpace_Button_Normal.bmp", "Resources\\Textures\\UI\\Button\\CharacterRoom", 1, 1);
	UnSpaceButton->setButtonTexture(ButtonState::Hover, "UnSpace_Button_Hover.bmp", "Resources\\Textures\\UI\\Button\\CharacterRoom", 1, 1);
	UnSpaceButton->setButtonTexture(ButtonState::Click, "UnSpace_Button_Click.bmp", "Resources\\Textures\\UI\\Button\\CharacterRoom", 1, 1);
	UnSpaceButton->setCallback<CharacterRoomButton>(ButtonEventState::Click, this, &CharacterRoomButton::clickUnspaceButton);
	UnSpaceButton->setButtonSound(ButtonEventState::Click, "Select.wav", "Resources\\Sounds\\Lobby");
	UnSpaceButton->setButtonSound(ButtonEventState::Hover, "Hover.wav", "Resources\\Sounds\\Lobby");
	UnSpaceButton->SetPos(GetPos() + m_SpaceButtonScale.Half());

	UnSpaceButton->Off();

	vecSpaceButton[static_cast<int>(SpaceButtonState::UnspaceButton)] = UnSpaceButton;
}

void CharacterRoomButton::loadSpaceCharacterComposition()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	RoomLevel* RoomLevelPtr = dynamic_cast<RoomLevel*>(CurLevel);
	if (nullptr == RoomLevelPtr)
	{
		MsgBoxAssert("나이나믹 캐스팅에 실패했습니다.");
		return;
	}


	// 캐릭터 버튼 캐릭터 그림자
	m_CharacterShadow = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_CharacterShadow)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_CharacterShadow->SetOrder(5);
	m_CharacterShadow->loadTexture("Room_Charcater_Shadow.bmp", "Resources\\Textures\\UI\\Button\\CharacterRoom");
	m_CharacterShadow->setTexture("Room_Charcater_Shadow.bmp");

	float4 ShadowScale = m_CharacterShadow->getTextureScale();
	float4 ShadowPos = GetPos() + m_ShadowStartPosToRoomButton + ShadowScale.Half();

	m_CharacterShadow->SetPos(ShadowPos);



	// 캐릭터 버튼 로드
	int PushCount = 0;

	vecCharacterTexture.resize(static_cast<int>(AvailableCharacterList::Max));

	std::vector<std::string> vecCharacterString = RoomLevelPtr->getCharacterString();

	for (int CharacterCount = 0; CharacterCount < static_cast<int>(CharacterList::Max); CharacterCount++)
	{
		if (CharacterCount >= static_cast<int>(CharacterList::Ethi) && CharacterCount < static_cast<int>(CharacterList::Random))
		{
			continue;
		}

		CommonTexture* CharacterTexture = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == CharacterTexture)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		std::string Text = "";
		Text += "Room_Charcater_";
		Text += vecCharacterString[CharacterCount];
		Text += ".bmp";


		CharacterTexture->SetOrder(6);
		CharacterTexture->loadTexture(Text, "Resources\\Textures\\UI\\Button\\CharacterRoom");
		CharacterTexture->setTexture(Text);


		float4 CharacterTextureScale = CharacterTexture->getTextureScale();
		float4 CharacterTexturePos = ShadowPos + float4{ 0.0f , -CharacterTextureScale.hY() } + float4{ 0.0f , 2.0f };

		CharacterTexture->SetPos(CharacterTexturePos);
		CharacterTexture->Off();

		vecCharacterTexture[PushCount] = CharacterTexture;

		++PushCount;
	}


	if (false == m_HostValue)
	{
		m_ReadyBillboard = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
		if (nullptr == m_ReadyBillboard)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		GameEngineWindowTexture* Texture = GlobalUtils::TextureFileLoad("PlayerReady.bmp", "Resources\\Textures\\UI\\MapSelect\\Room");
		if (Texture)
		{
			m_ReadyBillboard->setTexture("PlayerReady.bmp");

			float4 BillboardScale = Texture->GetScale();

			float4 ReadyBillboardPos = GetPos() + m_BillBoardStartPosToEachRoom + BillboardScale.Half();

			m_ReadyBillboard->SetPos(ReadyBillboardPos);
		}


	}

	m_Flag = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_Flag)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}
		
	m_Flag->loadTexture("CharacterRoom_Flag.bmp", "Resources\\Textures\\UI\\Button\\CharacterRoom");
	m_Flag->setTexture("CharacterRoom_Flag.bmp");

	float4 BillboardScale = m_Flag->getScale();
	float4 ReadyBillboardPos = GetPos() + m_FlagStartPosToEachRoom + BillboardScale.Half();
	m_Flag->SetPos(ReadyBillboardPos);

	setCharacterRank();


	switch (m_RoomNumber)
	{
	case 0:
		m_CurrentSelectedCharaterTexture = GlobalValue::g_SelectAvailableCharacter1;
		break;
	case 1:
		m_CurrentSelectedCharaterTexture = GlobalValue::g_SelectAvailableCharacter2;
		break;
	default:
		break;
	}

	if (true == m_HostValue)
	{
		vecCharacterTexture[static_cast<int>(m_CurrentSelectedCharaterTexture)]->On();
	}
}

void CharacterRoomButton::setCharacterRank()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}

	m_Rank = CurLevel->CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_Rank)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_Rank->loadTexture("Player_Trophy_Level.bmp", "Resources\\Textures\\UI\\PlayStage");
	m_Rank->setTexture("Player_Trophy_Level.bmp");
	m_Rank->setRendererCopyAndRenderScale(0,3);

	int CharacterLevelEachRoom = GlobalValue::g_vecPlayerInfo[m_RoomNumber].PlayerLevel;
	m_Rank->setRendererCopyPos(0, CharacterLevelEachRoom - 1);
	m_RenderRank = CharacterLevelEachRoom;

	float4 RankScale = m_Rank->getScale();
	float4 ReadyBillboardPos = GetPos() + CONST_RankStartPos + RankScale.Half();
	m_Rank->SetPos(ReadyBillboardPos);
	m_Rank->setRendererOrder(6);

	if (false == m_HostValue)
	{
		m_Rank->Off();
	}
}


void CharacterRoomButton::clickSpaceButton()
{
	m_SpaceButtonState = SpaceButtonState::UnspaceButton;

	--GlobalValue::g_ActiveRoomCount;
}

void CharacterRoomButton::clickUnspaceButton()
{
	m_SpaceButtonState = SpaceButtonState::SpaceButton;

	++GlobalValue::g_ActiveRoomCount;
}


void CharacterRoomButton::Update(float _Delta)
{
	if (GlobalValue::g_vecPlayerInfo[m_RoomNumber].PlayerLevel != m_RenderRank)
	{
		if (m_Rank)
		{
			m_Rank->setRendererCopyPos(0, GlobalValue::g_vecPlayerInfo[m_RoomNumber].PlayerLevel - 1);
			m_RenderRank = GlobalValue::g_vecPlayerInfo[m_RoomNumber].PlayerLevel;
		}
	}


	if (SpaceButtonState::SpaceButton == m_SpaceButtonState)
	{
		// 캐릭터 선택
		if (m_RoomNumber == RoomLevel::g_SelectRoomNumber)
		{
			AvailableCharacterList SelectCharacter = AvailableCharacterList::Max;

			switch (m_RoomNumber)
			{
			case 0:
				SelectCharacter = GlobalValue::g_SelectAvailableCharacter1;
				break;
			case 1:
				SelectCharacter = GlobalValue::g_SelectAvailableCharacter2;
				break;
			default:
				break;
			}

			if (SelectCharacter != m_CurrentSelectedCharaterTexture)
			{
				vecCharacterTexture[static_cast<int>(m_CurrentSelectedCharaterTexture)]->Off();

				int SelectCharacterValue = static_cast<int>(SelectCharacter);
				vecCharacterTexture[SelectCharacterValue]->On();

				m_CurrentSelectedCharaterTexture = SelectCharacter;
			}
		}

		// 방장이 아니라면 업데이트 버튼 클릭이 가능합니다.
		if (false == m_HostValue)
		{
			if (false == m_ActiveSpaceButtonValue)
			{
				vecSpaceButton[static_cast<int>(SpaceButtonState::SpaceButton)]->On();
				vecSpaceButton[static_cast<int>(SpaceButtonState::UnspaceButton)]->Off();


				int SelectCharacterValue = static_cast<int>(GlobalValue::g_SelectAvailableCharacter2);

				if (CharacterList::Random == GlobalValue::g_SelectCharacter)
				{
					SelectCharacterValue = static_cast<int>(AvailableCharacterList::Random);
				}

				vecCharacterTexture[SelectCharacterValue]->On();
				m_CharacterShadow->On();

				m_ReadyBillboard->On();
				m_Flag->On();
				m_Rank->On();

				m_ActiveSpaceButtonValue = true;
			}
		}

		m_SpaceButtonState = SpaceButtonState::SpaceButton;
	}
	else
	{
		if (false == m_HostValue)
		{
			if (true == m_ActiveSpaceButtonValue)
			{
				vecSpaceButton[static_cast<int>(SpaceButtonState::SpaceButton)]->Off();
				vecSpaceButton[static_cast<int>(SpaceButtonState::UnspaceButton)]->On();


				int SelectCharacterValue = static_cast<int>(GlobalValue::g_SelectAvailableCharacter2);

				vecCharacterTexture[SelectCharacterValue]->Off();
				m_CharacterShadow->Off();

				m_ReadyBillboard->Off();
				m_Flag->Off();
				m_Rank->Off();


				m_ActiveSpaceButtonValue = false;
			}
		}

		m_SpaceButtonState = SpaceButtonState::UnspaceButton;
	}
}