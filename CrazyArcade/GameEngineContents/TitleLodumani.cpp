#include "TitleLodumani.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "GlobalUtils.h"

TitleLodumani::TitleLodumani()
{

}

TitleLodumani::~TitleLodumani()
{

}

void TitleLodumani::LevelStart(GameEngineLevel* _PrevLevel)
{
	LogoLevel::LevelStart(_PrevLevel);
}

void TitleLodumani::LevelEnd(GameEngineLevel* _NextLevel)
{
}

void TitleLodumani::Start()
{
	LogoLevel::Start();

	GlobalUtils::TextureFileLoad("Title_Lodumani_Studios_Logo.bmp", "Resources\\Textures\\BackGround");


	Back = CreateActor<BackGround>(UpdateOrder::Map);
	Back->Init("Title_Lodumani_Studios_Logo.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());

	setNextLevelString("TitleLevel");
}

void TitleLodumani::Update(float _Delta)
{
	LogoLevel::Update(_Delta);
}

void TitleLodumani::Render(float _Delta)
{

}