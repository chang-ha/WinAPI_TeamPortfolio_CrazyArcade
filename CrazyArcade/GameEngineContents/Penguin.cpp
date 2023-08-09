#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Penguin.h"
#include "GlobalUtils.h"
#include "ActorEnum.h"
#include "ContentsEnum.h"
#include "PlayLevel.h"

// Debug
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
Penguin::Penguin()
{
}

Penguin::~Penguin()
{
}

void Penguin::Start()
{
	CurPlayLevel = dynamic_cast<PlayLevel*>(GetLevel());
	if (nullptr == CurPlayLevel)
	{
		MsgBoxAssert("PlayLevel이 아닌 곳에 보스몬스터를 생성할 수 없습니다.");
		return;
	}

	MainRenderer = CreateRenderer(RenderOrder::SelectTile);

	if (nullptr == ResourcesManager::GetInst().FindSprite("Penguin.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Textures\\Monster\\Boss\\");

		ResourcesManager::GetInst().CreateSpriteSheet("Down_Idle", FilePath.PlusFilePath("Idle_Penguin.bmp"), 10, 1);
		ResourcesManager::GetInst().CreateSpriteSheet("Down_Hit", FilePath.PlusFilePath("Hit_Penguin.bmp"), 3, 1);
	}

	MainRenderer->CreateAnimation("Down_Idle", "Down_Idle", 0, 9, 0.15f, true);
	MainRenderer->FindAnimation("Down_Idle")->Inters[9] = 5.0f;
	MainRenderer->ChangeAnimation("Down_Idle");

	MainRenderer->CreateAnimation("Down_Hit", "Down_Hit", 0, 2, 1.0f, false);

	MainRenderer->SetScaleRatio(1.5f);
}

void Penguin::Update(float _Delta)
{
	StateUpdate(_Delta);


}

void Penguin::Render(float _Delta)
{
	// Debug
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	Data.Pos = GetPos() + GlobalValue::MapTileSize.Half();
	Data.Scale = { 40, 40 };
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
}


void Penguin::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
	case MonsterState::Hitten:
		return HittenUpdate(_Delta);
	default:
		break;
	}
}

void Penguin::ChangeState(MonsterState _State)
{
	switch (_State)
	{
	case MonsterState::Idle:
		IdleStart();
		break;
	case MonsterState::Hitten:
		HittenStart();
		break;
	default:
		break;
	}

	State = _State;
}

void Penguin::IdleStart()
{
	MainRenderer->ChangeAnimation("Down_Idle");
}

void Penguin::IdleUpdate(float _Delta)
{
	TileObjectOrder CurTile = PlayLevel::CurPlayLevel->GetCurTileType(GetPos());

	if (CurTile == TileObjectOrder::PopRange)
	{
		ChangeState(MonsterState::Hitten);
	}
}

void Penguin::HittenStart()
{
	MainRenderer->ChangeAnimation("Down_Hit");
}

void Penguin::HittenUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeState(MonsterState::Idle);
	}
}