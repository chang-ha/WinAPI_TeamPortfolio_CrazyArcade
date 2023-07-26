#include "Dao.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineRenderer.h>

Dao::Dao()
{
}

Dao::~Dao()
{
}

void Dao::Start()
{
	CreateSprite("Dao_Idle_Up.Bmp", 1);
	CreateSprite("Dao_Idle_Down.Bmp", 1);
	CreateSprite("Dao_Idle_Left.Bmp", 1);
	CreateSprite("Dao_Idle_Right.Bmp", 1);
	CreateSprite("Dao_Left.Bmp", 6);
	CreateSprite("Dao_Right.Bmp", 6);
	CreateSprite("Dao_Up.Bmp", 10);
	CreateSprite("Dao_Down.Bmp", 8);

	MainRenderer = CreateRenderer(RenderOrder::Character);
	MainRenderer->CreateAnimation("Dao_Idle_Up", "Dao_Idle_Up.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Down", "Dao_Idle_Down.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Left", "Dao_Idle_Left.Bmp");
	MainRenderer->CreateAnimation("Dao_Idle_Right", "Dao_Idle_Right.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Left", "Dao_Left.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Right", "Dao_Right.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Up", "Dao_Up.Bmp");
	MainRenderer->CreateAnimation("Dao_Move_Down", "Dao_Down.Bmp");

	ChangeState(CharacterState::Idle);
}

void Dao::Update(float _Delta)
{
	BaseCharacter::Update(_Delta);
}

void Dao::CreateSprite(const std::string& _TextureName, int _XCount, int _YCount /*= 1*/)
{
	if (ResourcesManager::GetInst().FindSprite(_TextureName) == nullptr)
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		FilePath.MoveChild("Resources\\Textures\\Character\\Dao\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath(_TextureName), _XCount, _YCount);
	}
}

void Dao::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = "Dao_";

	AnimationName += _StateName;

	if (_StateName == "Move" || _StateName == "Idle")
	{
		switch (Dir)
		{
		case ActorDir::Left:
			AnimationName += "_Left";
			break;
		case ActorDir::Right:
			AnimationName += "_Right";
			break;
		case ActorDir::Up:
			AnimationName += "_Up";
			break;
		case ActorDir::Down:
			AnimationName += "_Down";
			break;
		default:
			break;
		}
	}

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}