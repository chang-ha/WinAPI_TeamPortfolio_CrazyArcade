#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"
#include "GlobalValue.h"
class Item : public GameEngineActor
{
public:
	// Constructor Destructor
	Item();
	~Item();

	// Delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	// 아이템의 Type 반환
	inline ItemType GetItemType()
	{
		return Type;
	}

	// int로 아이템의 Type 반환
	inline int GetItemTypeIntInt() const
	{
		return static_cast<int>(Type);

	}

	// Type 세팅
	inline void SetItemType(ItemType _Type)
	{
		Type = _Type;
		SetTexture(Type);
	}

	// int를 인자로 받아서 Type 세팅
	inline void SetItemTypeInt(int _Type)
	{
		Type = static_cast<ItemType>(_Type);
		SetTexture(Type);
	}

	inline void SetTileInfo(TileObjectOrder _Info)
	{
		TileInfo = _Info;
	}

	inline void SetTileIndexInfo(float4 _Index)
	{
		TileIndex = _Index;
	}

	inline void SetTileIndexInfo(float _X, float _Y)
	{
		TileIndex.X = _X;
		TileIndex.Y = _Y;
	}

	inline void ItemPosInit()
	{
		SetPos(GlobalValue::ItemPosNormalize + GlobalValue::TileStartPos);
	}
	

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void SetTexture(ItemType _Type);

	void Levitation(float _Delta);

	// Item 상태변수
	ItemType Type;
	TileObjectOrder TileInfo = TileObjectOrder::Empty;
	float4 TileIndex = float4::ZERO;

	// Item 물리변수
	float Speed = 3.5f;
	float CurRadian = 0.0f;
	float MovingHeight = 10.0f;
	float4 StartPos = {0, -3};

	float AlphaValue = 200.0f;
	class GameEngineRenderer* ItemRenderer = nullptr;
	class GameEngineRenderer* ShadowRenderer = nullptr;
	class GameEngineCollision* ItemCollision = nullptr;
};