#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ImmovableBlock : public GameEngineActor
{
public:
	// Constructor Destructor
	ImmovableBlock();
	~ImmovableBlock();

	// Delete Function
	ImmovableBlock(const ImmovableBlock& _Other) = delete;
	ImmovableBlock(ImmovableBlock&& _Other) noexcept = delete;
	ImmovableBlock& operator=(const ImmovableBlock& _Other) = delete;
	ImmovableBlock& operator=(ImmovableBlock&& _Other) noexcept = delete;

	void Init(int _Index);
protected:

private:
	void Start() override;

	int Index = 0;
	class GameEngineRenderer* Renderer = nullptr;
};