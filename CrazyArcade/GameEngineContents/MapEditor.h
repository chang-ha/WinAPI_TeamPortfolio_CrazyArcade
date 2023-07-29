#pragma once
#include "ContentLevel.h"
#include <vector>
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

	bool MouseInTileMap();

	// Const Value
	const float4 SelectView_StartPos = { 655.0f, 100.0f };
	float4 CurMousePos = float4::ZERO;
	int CurTileIndex_X = 0;
	int CurTileIndex_Y = 0;
	int CurSelectedTileType = 1;

	int SelectViewSize_X = 3;
	int SelectViewSize_Y = 10;

	// State Value
	bool LoadTileTexture = false;

	class TileSelect* SelectedTile = nullptr;
	class GameEngineRenderer* TileRenderer = nullptr;

	TileMap* DrawingVlew = nullptr;
	TileMap* SelectView = nullptr;

	std::vector<std::vector<int>>TilesInfo;
};

