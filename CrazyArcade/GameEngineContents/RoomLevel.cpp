#include "PlayLevel.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}


void PlayLevel::Start()
{
	Back = CreateActor<BackGround>(UpdateOrder::Map);
	if (nullptr == Back)
	{
		MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
		return;
	}

	Back->Init("PlayPanel.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());

	
}

void PlayLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}



void PlayLevel::Render(float _Delta)
{

}




void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}