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
	
	const float4 CONST_CancleButtonStartPos = float4{ 278.0f, 447.0f };
	const float4 CONST_AcceptButtonStartPos = float4{ 161.0f, 447.0f };

	void clickCancleButton();
	void clickAcceptButton();



	void loadMapInfoButton();

	MapType CurSelectMap = MapType::Max;

	struct SelectButtonInfo
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

	std::vector<SelectButtonInfo> vecMapInfoButton;

	void changeMapCompart(MapType _Type);

	void clickSeal1Button();
	void clickSeal2Button();
	void clickPenguin1Button();
	void clickPenguin2Button();
	void clickRandomButton();




	// Map Info
	struct MapInfo
	{
	public:
		CommonTexture* Title = nullptr;
		CommonTexture* Img = nullptr;
		CommonTexture* Outline = nullptr;
		CommonTexture* Text = nullptr;
	};

	void loadSelectMapInfo();

	MapInfo m_MapInfo;

	float4 m_TitleScale = float4::ZERO;
	float4 m_TextScale = float4::ZERO;
	float4 m_ImgScale = float4::ZERO;

	const float4 SelectedMapTitleStartPos = float4{ 24.0f , 65.0f };
	const float4 SelectedMapImgStartPos = float4{ 26.0f , 91.0f };
	const float4 SelectedMapOutlineStartPos = float4{ 25.0f , 225.0f };
	const float4 SelectedMapTextStartPos = float4{ 25.0f , 302.0f };

	void changeMapInfo(MapType _Type);

};

