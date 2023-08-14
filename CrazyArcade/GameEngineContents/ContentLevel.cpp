#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineCore.h>

#include "ContentLevel.h"
#include "ContentsEnum.h"
#include "UIMouseObject.h"

bool ContentLevel::DebugValue = false;
float ContentLevel::GlobalVolume = 1.0f;
ContentLevel::ContentLevel()
{

}

ContentLevel::~ContentLevel()
{

}

void ContentLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void ContentLevel::Start()
{
	if (nullptr == MouseObject)
	{
		MouseObject = CreateActor<UIMouseObject>(UpdateOrder::UI);
		if (nullptr == MouseObject)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		MouseObject->setTexture(MouseState::Normal, "Mouse_Normal.bmp", "Resources\\Textures\\UI\\Mouse", 1, 1);
		MouseObject->setTexture(MouseState::Click, "Mouse_Click.bmp", "Resources\\Textures\\UI\\Mouse", 1, 1);
		MouseObject->OverOn();

		GameEngineWindow::MainWindow.CursorOff();
	}
}

void ContentLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F1))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::IsDown(VK_F2))
	{
		GameEngineCore::ChangeLevel("TestStage");
	}

	if (true == GameEngineInput::IsDown(VK_F3))
	{
		GameEngineCore::ChangeLevel("MapEditor");
	}

	if (true == GameEngineInput::IsDown(VK_F4))
	{
		GameEngineCore::ChangeLevel("RoomLevel");
	}

	if (true == GameEngineInput::IsDown('P'))
	{
		DebugValue = !DebugValue;
	}

	// GlobalVolume
	if (true == GameEngineInput::IsDown('N'))
	{
		GlobalVolume += 0.2f;
		if (2.0f < GlobalVolume)
		{
			GlobalVolume = 2.0f;
		}

		GameEngineSound::SetGlobalVolume(GlobalVolume);
		BGMPlayer.SetVolume(BGMVolume);
	}

	if (true == GameEngineInput::IsDown('M'))
	{
		GlobalVolume -= 0.2f;
		if (0.0f > GlobalVolume)
		{
			GlobalVolume = 0.0f;
		}

		GameEngineSound::SetGlobalVolume(GlobalVolume);
		BGMPlayer.SetVolume(BGMVolume);
	}
}