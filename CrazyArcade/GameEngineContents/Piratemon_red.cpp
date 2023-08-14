#include "Piratemon_red.h"
#include "GlobalUtils.h"
#include "ContentsEnum.h"
#include "ActorEnum.h"
#include "PlayLevel.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/TileMap.h>

Piratemon_red::Piratemon_red()
{
}

Piratemon_red::~Piratemon_red()
{
}

void Piratemon_red::Start()
{
	BaseMonster::Start();
}

void Piratemon_red::ChangeAnimationState(const std::string& _StateName)
{

}