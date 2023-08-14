#include "Piratemon_black.h"
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

Piratemon_black::Piratemon_black()
{
}

Piratemon_black::~Piratemon_black()
{
}

void Piratemon_black::Start()
{
	BaseMonster::Start();
}

void Piratemon_black::ChangeAnimationState(const std::string& _StateName)
{

}