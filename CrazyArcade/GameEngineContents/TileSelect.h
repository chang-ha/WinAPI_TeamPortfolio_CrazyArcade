#pragma once
#include <GameEngineCore/GameEngineActor.h>
class TileSelect : public GameEngineActor
{
public:
	// Constructor Destructor
	TileSelect();
	~TileSelect();

	// Delete Function
	TileSelect(const TileSelect& _Other) = delete;
	TileSelect(TileSelect&& _Other) noexcept = delete;
	TileSelect& operator=(const TileSelect& _Other) = delete;
	TileSelect& operator=(TileSelect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	class GameEngineRenderer* Renderer = nullptr;
};