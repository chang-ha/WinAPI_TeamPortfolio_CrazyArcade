#include "Item.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <cmath>
#include "GlobalLoad.h"
#include "GlobalValue.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Start()
{
	GlobalLoad::ItemTextureLoad();
	
	// Item MainRenderer
	ItemRenderer = CreateRenderer(RenderOrder::MapObject);
	ItemRenderer->SetRenderPos(StartPos);

	// Item Shadow Renderer
	ShadowRenderer = CreateRenderer(RenderOrder::Shadow);
	ShadowRenderer->SetTexture("ItemShadow2.bmp");
	ShadowRenderer->SetRenderPos({0, 20});
	ShadowRenderer->SetAlpha(static_cast<unsigned char>(AlphaValue));

	// Item Collision
	ItemCollision = CreateCollision(CollisionOrder::Item);
	ItemCollision->SetCollisionType(CollisionType::Rect);
	ItemCollision->SetCollisionScale({1, 1});
	ItemPosInit();
}

void Item::Update(float _Delta)
{
	std::vector<GameEngineCollision*> Col;
	if (true == ItemCollision->Collision(CollisionOrder::PlayerBody,
		Col,
		CollisionType::Rect,
		CollisionType::Rect))
	{
		Death();
		return;
	}

	Levitation(_Delta);
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

void Item::SetTexture(ItemType _Type)
{
	switch (_Type)
	{
	case ItemType::Bubble:
		ItemRenderer->SetTexture("Item_Bubble.bmp");
		break;
	case ItemType::Fluid:
		ItemRenderer->SetTexture("Item_Fluid.bmp");
		break;
	case ItemType::Roller:
		ItemRenderer->SetTexture("Item_Roller.bmp");
		break;
	case ItemType::Ultra:
		ItemRenderer->SetTexture("Item_Ultra.bmp");
		break;
	case ItemType::Red_Devil:
		ItemRenderer->SetTexture("Item_Red_Devil.bmp");
		break;
	case ItemType::Needle:
		ItemRenderer->SetTexture("Item_Needle.bmp");
		break;
	default:
		break;
	}
}