#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <vector>

enum class TraitType
{
	Count,
	Power,
	Speed,
	Max,
};


// 설명 :
class CharacterTraits : public GameEngineActor
{
public:
	// constrcuter destructer
	CharacterTraits();
	~CharacterTraits();

	// delete Function
	CharacterTraits(const CharacterTraits& _Other) = delete;
	CharacterTraits(CharacterTraits&& _Other) noexcept = delete;
	CharacterTraits& operator=(const CharacterTraits& _Other) = delete;
	CharacterTraits& operator=(CharacterTraits&& _Other) noexcept = delete;

protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;


	// this
	void loadCharacterTraits();


	GameEngineRenderer* TraitRenderer = nullptr;
	float4 m_TraitPanelScale = float4::ZERO;

	GameEngineRenderer* UpperRenderer = nullptr;
	float4 m_UpperPanelScale = float4::ZERO;


	std::vector<std::vector<GameEngineRenderer*>> vecTraitBarRenderer;
	float4 m_TraitBarScale = float4::ZERO;

	const float4 m_TraitBarStartPos = float4{ 95.0f , 11.0f };
	const float4 m_TraitBarInterScale = float4{ 1.0f , 7.0f };
	const int m_TraitMaxCount = 10;

	
	void updateCharacterTraits();

	bool isHoverOn();
	bool TraitPanelOnValue = false;

	int m_PrevTraitPopCharacter = -1;

	const float4 m_TraitPopHoverRangeStartPos = float4{ 486.0f , 81.0f };
	const float4 m_TraitPopHoverRangeRangeScale = float4{ 287.0f , 141.0f };
	const float4 m_TraitPopHoverUnitScale = float4{ 71.0f , 47.0f };

	void updateUpperTrait(int& _TraitCount);
	void updateWaterBombTraitBar(int& _TraitCount);
	void updateBombPowerTraitBar(int& _TraitCount);
	void updateSpeedTraitBar(int& _TraitCount);

};

