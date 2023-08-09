#include "Item.h"

#include <GameEngineCore/GameEngineRenderer.h>
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
	
	ItemRenderer = CreateRenderer(RenderOrder::MapObject);
	ShadowRenderer = CreateRenderer(RenderOrder::Shadow);
	ShadowRenderer->SetTexture("ItemShadow2.bmp");

	ItemRenderer->SetRenderPos(StartPos);
	ShadowRenderer->SetRenderPos({0, 20});

	SetPos(GlobalValue::ItemPosNormalize + GlobalValue::TileStartPos);
}

void Item::Update(float _Delta)
{
	
	Levitation(_Delta);

	//AlphaValue -= 100 * _Delta;
	ShadowRenderer->SetAlpha(static_cast<unsigned char>(AlphaValue));
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
		break;
	case ItemType::Fluid:
		ItemRenderer->SetTexture("Fluid.bmp");
		break;
	case ItemType::Ultra:
		break;
	case ItemType::Roller:
		break;
	case ItemType::Red_Devil:
		break;
	default:
		break;
	}
}