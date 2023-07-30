#pragma once
#include "ContentLevel.h"
#include <vector>


enum class MapEditorButtonState
{
	Prev,
	Next,
	Max,
};

enum class SelectTileType
{
	Ground,
	ImmovableBlock,
	MovableBlock,
	//Structure,
	//Item,
	//Unit,
	Max,
};



class TileMap;
class Button;
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
	bool MouseInDrawingTileMap();

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


private:
	std::vector<std::string> VecTileSpriteFileName;


	int CurSelectTilesCount = 0;

	void UpdateDrawingTileUI();
	
	void InitTiles();
	void LoadButton();
	std::vector<Button*> VecButton;

	float4 LocalNextButtonStartPos = float4{ 10.0f , 30.0f };

	SelectTileType CurrentSelectTileType = SelectTileType::Max;

	void ClickPrevButton();
	void ClickNextButton();

	void ClearSelectViewTiles();
	void ChangeSelectViewTile();

};

