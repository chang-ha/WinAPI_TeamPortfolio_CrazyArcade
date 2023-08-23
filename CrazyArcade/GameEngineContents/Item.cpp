#include "Item.h"
#include "BaseCharacter.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <cmath>

#include "GlobalLoad.h"
#include "GlobalUtils.h"
#include "GlobalValue.h"
#include "PlayLevel.h"

Item::Item()
{
}

Item::~Item()
{
}


void Item::Start()
{
	GlobalLoad::ItemTextureLoad();
	
	// Item Sound
	GlobalUtils::SoundFileLoad("Get_Item.wav", "Resources\\Sounds\\Item\\");
	GlobalUtils::SoundFileLoad("Item_Out.wav", "Resources\\Sounds\\Item\\");

	// Item MainRenderer
	ItemRenderer = CreateRenderer(RenderOrder::MapObject);
	ItemRenderer->SetRenderPos(StartPos);

	// Item Shadow Renderer
	ShadowRenderer = CreateRenderer(RenderOrder::Shadow);
	ShadowRenderer->SetTexture("ItemShadow2.bmp");
	ShadowRenderer->SetRenderPos({0, 20});
	ShadowRenderer->SetAlpha(static_cast<unsigned char>(GlobalValue::AllAlphaValue));

	// Item Collision
	ItemCollision = CreateCollision(CollisionOrder::Item);
	ItemCollision->SetCollisionType(CollisionType::Rect);
	ItemCollision->SetCollisionScale({10, 10});

	// Position Initialize
	SetItemPos(TileIndexX, TileIndexY);
}


void Item::Update(float _Delta)
{
	std::vector<GameEngineCollision*> Col;
	if (true == ItemCollision->Collision(CollisionOrder::PlayerBody, Col, CollisionType::Rect, CollisionType::Rect)
		|| true == ItemCollision->Collision(CollisionOrder::PlayerBody2, Col, CollisionType::Rect, CollisionType::Rect))
	{
		PlayLevel* Level = dynamic_cast<PlayLevel*>(GetLevel());

		GameEngineActor* ColActor = Col[Col.size() - 1]->GetActor();
		BaseCharacter* ColCharacter = dynamic_cast<BaseCharacter*>(ColActor);

		if (CharacterState::Idle == ColCharacter->GetState()
			|| CharacterState::Move == ColCharacter->GetState())
		{
			EffectPlayer = GameEngineSound::SoundPlay("Get_Item.wav");
			EffectPlayer.SetVolume(0.8f);

			ColCharacter->GetItem(GetItemType());

			Level->CheckItemInTile(TileIndexX, TileIndexY);
		}
		return;
	}

	Levitation(_Delta);
}


void Item::SetItemTypeRandom()
{
	// < 아이템 번호 >
	// 0 : Bubble
	// 1 : Fluid
	// 2 : Roller
	// 3 : Ultra
	// 4 : Red_Devil
	// 5 : Needle

	int RandomNumber = GameEngineRandom::MainRandom.RandomInt(0, 4);
	if (0 == RandomNumber)
	{
		// 20.0% 확률로 Ultra, Red_Devil, Needle중 하나 생성
		RandomNumber = GameEngineRandom::MainRandom.RandomInt(3, 5);
	}
	else
	{
		// 80.0% 확률로 Bubble, Fluid, Roller 중 하나 생성
		RandomNumber = GameEngineRandom::MainRandom.RandomInt(0, 2);
	}

	SetItemTypeInt(RandomNumber);
}

void Item::SetItemPos(int _X, int _Y)
{
	float4 Pos = { GlobalValue::MapTileSize.X * _X, GlobalValue::MapTileSize.Y * _Y };
	SetPos(GlobalValue::ItemPosNormalize + GlobalValue::TileStartPos + Pos);

	TileIndexX = _X;
	TileIndexY = _Y;
}


void Item::Levitation(float _Delta)
{
	CurRadian += Speed * _Delta;

	if (CurRadian >= GameEngineMath::PI2)
	{
		CurRadian = 0.0f;
		ItemRenderer->SetRenderPos(StartPos);
		ShadowRenderer->SetTexture("ItemShadow2.bmp");
	}

	if (CurRadian >= GameEngineMath::PI)
	{
		ShadowRenderer->SetTexture("ItemShadow1.bmp");
	}

	float4 AddPosY = { 0.0f, cosf(CurRadian) * MovingHeight };
	ItemRenderer->AddRenderPos(AddPosY * _Delta);
}

void Item::SetItemTexture(ItemType _Type)
{
	switch (_Type)
	{
	case ItemType::Bubble:
		if (nullptr == ItemRenderer->FindAnimation("Bubble"))
		{
			ItemRenderer->CreateAnimation("Bubble", "Item_Bubble.bmp", 0, 2, 0.1f, true);
		}
		ItemRenderer->ChangeAnimation("Bubble");
		break;
	case ItemType::Fluid:
		if (nullptr == ItemRenderer->FindAnimation("Fluid"))
		{
			ItemRenderer->CreateAnimation("Fluid", "Item_Fluid.bmp", 0, 2, 0.1f, true);
		}
		ItemRenderer->ChangeAnimation("Fluid");
		break;
	case ItemType::Roller:
		if (nullptr == ItemRenderer->FindAnimation("Roller"))
		{
			ItemRenderer->CreateAnimation("Roller", "Item_Roller.bmp", 0, 2, 0.1f, true);
		}
		ItemRenderer->ChangeAnimation("Roller");
		break;
	case ItemType::Ultra:
		if (nullptr == ItemRenderer->FindAnimation("Item_Ultra"))
		{
			ItemRenderer->CreateAnimation("Item_Ultra", "Item_Ultra.bmp", 0, 2, 0.1f, true);
		}
		ItemRenderer->ChangeAnimation("Item_Ultra");
		break;
	case ItemType::Red_Devil:
		if (nullptr == ItemRenderer->FindAnimation("Red_Devil"))
		{
			ItemRenderer->CreateAnimation("Red_Devil", "Item_Red_Devil.bmp", 0, 2, 0.1f, true);
		}
		ItemRenderer->ChangeAnimation("Red_Devil");
		break;
	case ItemType::Needle:
		if (nullptr == ItemRenderer->FindAnimation("Needle"))
		{
			ItemRenderer->CreateAnimation("Needle", "Item_Needle.bmp", 0, 2, 0.1f, true);
		}
		ItemRenderer->ChangeAnimation("Needle");
		break;
	default:
		break;
	}
}