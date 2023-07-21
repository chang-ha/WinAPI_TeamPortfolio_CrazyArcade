#pragma once
#include "ContentLevel.h"

class TileMap;
class MapEditor : public ContentLevel
{
public:
	// constructer destructer
	MapEditor();
	~MapEditor();

	// delete function
	MapEditor(const MapEditor& _Ohter) = delete;
	MapEditor(MapEditor&& _Ohter) noexcept = delete;
	MapEditor& operator=(const MapEditor& _Other) = delete;
	MapEditor& operator=(MapEditor&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	TileMap* Tile = nullptr;
};

