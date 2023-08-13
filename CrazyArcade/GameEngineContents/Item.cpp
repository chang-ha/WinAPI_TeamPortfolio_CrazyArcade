#include "Item.h"
#include "BaseCharacter.h"

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
	GlobalUtils::SoundFileLoad("Get_Item.wav", "Resources\\Sounds\\Character\\");

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

	// Position Initialize
	SetItemPos(TileIndexX, TileIndexY);
}


void Item::Update(float _Delta)
{
	std::vector<GameEngineCollision*> Col;
	if (true == ItemCollision->Collision(CollisionOrder::PlayerBody,
		Col,
		CollisionType::Rect,
		CollisionType::Rect))
	{
		EffectPlayer = GameEngineSound::SoundPlay("Get_Item.wav");
		EffectPlayer.SetVolume(0.5f);

		PlayLevel* Level = dynamic_cast<PlayLevel*>(GetLevel());

		GameEngineActor* ColActor = Col[Col.size() - 1]->GetActor();
		BaseCharacter* ColCharacter = dynamic_cast<BaseCharacter*>(ColActor);
		ColCharacter->GetItem(GetItemType());

		Level->CheckItemInTile(TileIndexX, TileIndexY);
		return;
	}

	Levitation(_Delta);
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