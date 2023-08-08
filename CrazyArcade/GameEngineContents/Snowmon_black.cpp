#include "Snowmon_black.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>

Snowmon_black::Snowmon_black()
{
}

Snowmon_black::~Snowmon_black()
{
}

void Snowmon_black::Start()
{
	GlobalUtils::SpriteFileLoad("Snowmon_Black_Idle.Bmp", "Resources\\Textures\\Monster\\", 2, 1);

	MainRenderer = CreateRenderer(RenderOrder::MapObject);
	MainRenderer->CreateAnimation("Snowmon_Black_Idle", "Snowmon_Black_Idle.Bmp", 0, 1, 0.2f, true);
	MainRenderer->ChangeAnimation("Snowmon_Black_Idle");

	//ChangeState(MonsterState::Idle);
}