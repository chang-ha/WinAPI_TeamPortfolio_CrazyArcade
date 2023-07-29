#pragma once
#include "WindowPanelUI.h"
#include "ContentsEnum.h"


#include <GameEngineCore/GameEngineLevel.h>


#include <vector>


enum class MapSelectButton
{
	Accept,
	Cancel,
	Max,
};



// ���� :
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
	// GameEngineObject ���
	void Start() override;
	void Update(float _Delta) override;


	void onPanel() override;
	void offPanel() override;


	void clickCancleButton();
	void clickAcceptButton();

};

