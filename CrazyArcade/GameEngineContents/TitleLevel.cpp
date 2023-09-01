#include "TitleLevel.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "GlobalUtils.h"

#include "FadeObject.h"
#include "Button.h"
#include "CommonTexture.h"


TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	FadeObject::CallFadeIn(this, GlobalValue::g_ChangeLevelFadeSpeed);

	// BGM
	BGMPlayer = GameEngineSound::SoundPlay("TitleBGM.wav", 10000);
	BGMPlayer.SetVolume(BGMVolume);
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
}

void TitleLevel::Start()
{
	ContentLevel::Start();

	Back = CreateActor<BackGround>(UpdateOrder::Map);
	Back->Init("Title2.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());

	// Sound
	GlobalUtils::SoundFileLoad("TitleBGM.wav", "Resources\\Sounds\\BGM");
	BGMVolume = 0.0f;


	CreateTitleUI();
}

void TitleLevel::CreateTitleUI()
{
	setupTitileButtonFrame();
	InitTitleButton();
}

void TitleLevel::setupTitileButtonFrame()
{
	m_ButtonFrame = CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_ButtonFrame)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_ButtonFrame->setRendererOrder(RenderOrder::FirstElementUI);
	m_ButtonFrame->loadTexture("Title_Button_Border.bmp", "Resources\\Textures\\UI\\Button");
	m_ButtonFrame->setTexture("Title_Button_Border.bmp");
	float4 FrameScale = m_ButtonFrame->getTextureScale();
	float4 FramePos = CONST_ButtonFrameStartPos + FrameScale.Half();

	m_ButtonFrame->SetPos(FramePos);
}

void TitleLevel::InitTitleButton()
{
	vecTitleButton.resize(static_cast<int>(TitleButtonActor::Max));

	setupTitleGameStartButton();
	setupTitleMapEditorButton();
}

void TitleLevel::setupTitleGameStartButton()
{
	Button* GameStartButton = CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == GameStartButton)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	GameStartButton->setRenderer(6);
	GameStartButton->setButtonTexture(ButtonState::Normal, "Title_GameStart_Button_Normal.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	GameStartButton->setButtonTexture(ButtonState::Hover, "Title_GameStart_Button_Hover.bmp", "Resources\\Textures\\UI\\Button", 1, 2);
	GameStartButton->setButtonTexture(ButtonState::Click, "Title_GameStart_Button_Click.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	GameStartButton->setCallback<TitleLevel>(ButtonEventState::Click, this, &TitleLevel::CallBackGameStartButtonFunc);
	GameStartButton->setButtonSound(ButtonEventState::Hover, "Hover.wav", "Resources\\Sounds\\Lobby");
	GameStartButton->setButtonSound(ButtonEventState::Click, "Select.wav", "Resources\\Sounds\\Lobby");

	float4 GameStartButtonScale = GameStartButton->getButtonScale();
	float4 GameStartButtonPos = CONST_ButtonFrameStartPos + CONST_GameStartButtonStartPosToFrame;
	GameStartButton->setButtonPos(GameStartButtonPos);

	vecTitleButton[static_cast<int>(TitleButtonActor::GameStart)] = GameStartButton;
}

void TitleLevel::CallBackGameStartButtonFunc()
{
	FadeObject::CallFadeOut(this, "RoomLevel", GlobalValue::g_ChangeLevelFadeSpeed);
}


void TitleLevel::setupTitleMapEditorButton()
{
	Button* MapEditorButton = CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == MapEditorButton)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	MapEditorButton->setRenderer(6);
	MapEditorButton->setButtonTexture(ButtonState::Normal, "Title_MapEditor_Button_Normal.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	MapEditorButton->setButtonTexture(ButtonState::Hover, "Title_MapEditor_Button_Hover.bmp", "Resources\\Textures\\UI\\Button", 1, 2);
	MapEditorButton->setButtonTexture(ButtonState::Click, "Title_MapEditor_Button_Click.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	MapEditorButton->setCallback<TitleLevel>(ButtonEventState::Click, this, &TitleLevel::CallBackMapEditorButtonFunc);
	MapEditorButton->setButtonSound(ButtonEventState::Hover, "Hover.wav", "Resources\\Sounds\\Lobby");
	MapEditorButton->setButtonSound(ButtonEventState::Click, "Select.wav", "Resources\\Sounds\\Lobby");

	float4 MapEditorButtonScale = MapEditorButton->getButtonScale();
	float4 MapEditorButtonPos = CONST_ButtonFrameStartPos + CONST_MapEditorButtonStartPosToFrame;
	MapEditorButton->setButtonPos(MapEditorButtonPos);

	vecTitleButton[static_cast<int>(TitleButtonActor::MapEditor)] = MapEditorButton;
}

void TitleLevel::CallBackMapEditorButtonFunc()
{
	FadeObject::CallFadeOut(this, "MapEditor", GlobalValue::g_ChangeLevelFadeSpeed);
}



void TitleLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void TitleLevel::Render(float _Delta)
{

}