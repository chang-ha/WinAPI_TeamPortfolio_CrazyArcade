#include "RoomLevel.h"
#include "GlobalValue.h"
#include "ContentsEnum.h"



#include "BackGround.h"
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

	Button* ButtonPtr = CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == ButtonPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	ButtonPtr->InitDefaultButton("MapSelect_Button.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	ButtonPtr->InitClickButton("MapSelect_ClickedButton.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	ButtonPtr->InitHoveredButton("MapSelect_HoverButton.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	ButtonPtr->SetPos(float4{ 646.0f, 428.0f } + float4{123.0f, 48.0f}.Half());

	vecButtons.push_back(ButtonPtr);
}

void RoomLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);


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