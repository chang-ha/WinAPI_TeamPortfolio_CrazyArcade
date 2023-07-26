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

	ButtonPtr->setButtonTexture(ButtonState::Normal, "MapSelect_Button.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	ButtonPtr->setButtonTexture(ButtonState::Click, "MapSelect_ClickedButton.bmp", "Resources\\Textures\\UI\\Button", 1, 1);
	ButtonPtr->setButtonTexture(ButtonState::Hover, "MapSelect_HoverButton.bmp", "Resources\\Textures\\UI\\Button", 1, 2);
	/*ButtonPtr->setCallback(ButtonEventState::Click, )*/
	//ButtonPtr->setButtonSound(ButtonEventState::Click, )

	ButtonPtr->SetPos(float4{ 646.0f, 428.0f } + float4{123.0f, 48.0f}.Half());

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