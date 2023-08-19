#include "ItemSoket.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include "GlobalUtils.h"

ItemSoket::ItemSoket()
{
}

ItemSoket::~ItemSoket()
{
}

void ItemSoket::Start()
{
	GlobalUtils::TextureFileLoad("ItemUI_Needle.bmp", "Resources\\Textures\\Item\\");
	Off();
}

void ItemSoket::HoldingItem(ItemType _Type)
{
	if (nullptr != Renderer)
	{
		EmptyingSoket();
	}

	switch (_Type)
	{
	case ItemType::Needle:
		Renderer = CreateRenderer(RenderOrder::BackGround);
		Renderer->SetTexture("ItemUI_Needle.bmp");
		break;
	default:
		break;
	}
	On();
}

void ItemSoket::EmptyingSoket()
{
	Off();
	if (nullptr == Renderer)
	{
		return;
	}
	Renderer->Death();
	Renderer = nullptr;
}
