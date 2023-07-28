#pragma once
#include "WindowPanelUI.h"

// 설명 :
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




protected:

private:
// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;

};

