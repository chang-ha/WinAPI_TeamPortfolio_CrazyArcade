#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include "ContentsEnum.h"
#include "ActorEnum.h"

class ItemSoket : public GameEngineActor
{
public:
	// Constructor Destructor
	ItemSoket();
	~ItemSoket();

	// Delete Function
	ItemSoket(const ItemSoket& _Other) = delete;
	ItemSoket(ItemSoket&& _Other) noexcept = delete;
	ItemSoket& operator=(const ItemSoket& _Other) = delete;
	ItemSoket& operator=(ItemSoket&& _Other) noexcept = delete;
	void HoldingItem(ItemType _Type);

	void EmptyingSoket();
protected:

private:
	void Start() override;

	class GameEngineRenderer* Renderer;


};