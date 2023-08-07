#pragma once
#include "WindowPanelUI.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"


#include <GameEngineCore/GameEngineLevel.h>


#include <vector>


enum class MapSelectButton
{
	Accept,
	Cancel,
	Max,
};


// 설명 :
class Button;
class MapSelectWindow : public WindowPanelUI
{
public:
	// constrcuter destructer
	MapSelectWindow();
	~MapSelectWindow();

	// delete Function
	MapSelectWindow(const MapSelectWindow& _Other) = delete;
	MapSelectWindow(MapSelectWindow&& _Other) noexcept = delete;
	MapSelectWindow& operator=(const MapSelectWindow& _Other) = delete;
	MapSelectWindow& operator=(MapSelectWindow&& _Other) noexcept = delete;

	void initButton();




protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;


	// Button 상속
	void onPanel() override;
	void offPanel() override;


	// this 
	void loadButton();

	void clickCancleButton();
	void clickAcceptButton();



	void loadMapInfoButton();

	MapType CurSelectMap = MapType::Max;

	struct MapInfo
	{
	public:
		class Button* MapCompart = nullptr;
		class CommonTexture* SelectMap = nullptr;
		class CommonTexture* MapIcon = nullptr;
		class CommonTexture* MapName = nullptr;
		class CommonTexture* MapNumber = nullptr;
	};

	const float4 MapListStartPos = float4{ 195.0f , 91.0f };
	const float4 MapIconStartPos = float4{ 17.0f , 1.0f };
	const float4 MapNameStartPos = float4{ 35.0f , 0.0f };
	const float4 MapNumberStartPos = float4{ 100.0f , 1.0f };

	float4 m_MapNameScale = float4::ZERO;
	float4 m_MapNumberScale = float4::ZERO;

	std::vector<MapInfo> vecMapInfoButton;

	void changeMapCompart(MapType _Type);

	void clickSeal1Button();
	void clickSeal2Button();
	void clickPenguin1Button();
	void clickPenguin2Button();



};

