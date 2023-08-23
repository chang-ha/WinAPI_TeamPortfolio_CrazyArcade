#include "TitleNexon.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "GlobalUtils.h"

TitleNexon::TitleNexon()
{

}

TitleNexon::~TitleNexon()
{

}

void TitleNexon::LevelStart(GameEngineLevel* _PrevLevel)
{
	LogoLevel::LevelStart(_PrevLevel);
}

void TitleNexon::LevelEnd(GameEngineLevel* _NextLevel)
{
	LogoLevel::LevelEnd(_NextLevel);
}

void TitleNexon::Start()
{
	LogoLevel::Start();

	GlobalUtils::TextureFileLoad("Title_NEXON_Logo.bmp", "Resources\\Textures\\BackGround");

	Back = CreateActor<BackGround>(UpdateOrder::Map);
	if (nullptr == Back)
	{
		MsgBoxAssert("배경을 만들지 않고 레벨을 생성할 수 없습니다.");
		return;
	}

	Back->Init("Title_NEXON_Logo.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());


	static bool LogoSoundFileLoadValue = false;
	if (false == LogoSoundFileLoadValue)
	{
		GlobalUtils::SoundFileLoad("Nexon_Logo.mp3", "Resources\\Sounds\\Logo");

		LogoSoundFileLoadValue = true;
	}

	setEffectSound("Nexon_Logo.mp3", 1.0f);
	setNextLevelString("TitleLodumani");
}

void TitleNexon::Update(float _Delta)
{
	LogoLevel::Update(_Delta);
}

void TitleNexon::Render(float _Delta)
{

}