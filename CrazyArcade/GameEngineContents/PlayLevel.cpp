#include "PlayLevel.h"
#include "BackGround.h"
#include "BaseCharacter.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void PlayLevel::Start()
{
	Back = CreateActor<BackGround>(UpdateOrder::Map);
	if (nullptr == Back)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	Back->Init("PlayPanel.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());

	BaseCharacter* Check = CreateActor<BaseCharacter>(UpdateOrder::Character);
	Check->SetPos(GlobalValue::WinScale.Half());
}

void PlayLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void PlayLevel::Render(float _Delta)
{

}