#pragma once
#include "ContentLevel.h"
#include "ContentsEnum.h"
 
#include <string>
#include <vector>


enum class MapEditorButtonState
{
	Prev,
	Next,
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

	bool MouseInTileMap(float4& _ViewStartPos, float4& TileMaxIndex);

	// Setting Function
	void TileInit();
	void TileSetting();
	void TileInfoReset();

	class TileMap* SelectViewInit(TileObjectOrder _SelectedObjectType);

	void ChangeSelectViewInfo(TileObjectOrder _SelectedObjectType);
	void AllOffSelectVlew();
	
	TileMap* GetCurSelectViewTile();

	void DrawingTile();
	void SelectObject();

	// File Save Function
	void OpenFileDialog();
	void SaveFileDialog();

	// View Position
	float4 DrawingView_StartPos = { 20.0f, 50.0f };
	float4 SelectView_StartPos = { 655.0f, 120.0f };


	// Currunt Index Value
	float4 CurMousePos = float4::ZERO;
	int CurTileIndex_X = 0;
	int CurTileIndex_Y = 0;


	// SelectView Index Setting Value
	float4 SelectViewSize = { 3, 10 };
	int SelectViewSize_X = 3;
	int SelectViewSize_Y = 10;


	// Selected Object Type
	// "TileObjectOrder::Empty" 값은 "Ground"로 대체하여 사용
	TileObjectOrder CurSelectedObjectType = TileObjectOrder::Empty;
	std::string SelectedTextureName = "Grounds.bmp";
	float4 CurObjectOverSize = float4::ZERO;
	int ObjectSpriteMaxIndex = 0;

	// Texture State Value
	int GroundTextureIndex = 0;
	int ObjectTextureIndex = 0;

	// Tiles
	TileMap* DrawingView_Ground = nullptr;
	TileMap* DrawingView_Object= nullptr;

	// SelectView Tiles
	TileMap* SelectView_Grounds = nullptr;
	TileMap* SelectView_Structures = nullptr;
	TileMap* SelectView_ImmovableBlocks = nullptr;
	TileMap* SelectView_MovableBlocks = nullptr;

	// TileSelect Object
	class TileSelect* DrawingVlew_SelectedPlace = nullptr;
	class TileSelect* SelectView_SelectedPlace = nullptr;

	std::vector<std::vector<class GameMapInfo>> TileInfo;

private:
	std::vector<std::string> VecTileSpriteFileName;


	int SelectTilesMapNum = 0;

	void LoadButton();
	float4 LocalPrevButtonStartPos = float4{ 10.0f , 20.0f };
	std::vector<Button*> VecButton;

	void ClickPrevButton();
	void ClickNextButton();
};

