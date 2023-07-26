#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Structure : public GameEngineActor
{
public:
	// Constructor Destructor
	Structure();
	~Structure();

	// Delete Function
	Structure(const Structure& _Other) = delete;
	Structure(Structure&& _Other) noexcept = delete;
	Structure& operator=(const Structure& _Other) = delete;
	Structure& operator=(Structure&& _Other) noexcept = delete;

	void Init(int _Index);
protected:

private:
	void Start() override;

	int Index = 0;
	class GameEngineRenderer* Renderer = nullptr;
};