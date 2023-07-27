#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCore.h>

#include "ContentLevel.h"

bool ContentLevel::DebugValue = false;

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

}

void ContentLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F1))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::IsDown(VK_F2))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
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
}