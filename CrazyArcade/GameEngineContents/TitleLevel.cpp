#include "TitleLevel.h"
#include "BackGround.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "GlobalUtils.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	// BGM
	BGMPlayer = GameEngineSound::SoundPlay("TitleBGM.wav", 10000);
	BGMPlayer.SetVolume(BGMVolume);

}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

void TitleLevel::Start()
{
	ContentLevel::Start();

	Back = CreateActor<BackGround>(UpdateOrder::Map);
	Back->Init("TitleLevel.bmp");
	Back->SetPos(GlobalValue::WinScale.Half());

	// Sound
	GlobalUtils::SoundFileLoad("TitleBGM.wav", "Resources\\Sounds\\BGM");
	BGMVolume = 1.2f;
}

void TitleLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void TitleLevel::Render(float _Delta)
{

}