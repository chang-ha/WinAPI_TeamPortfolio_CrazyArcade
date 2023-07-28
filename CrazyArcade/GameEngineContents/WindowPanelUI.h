#pragma once
#include <GameEngineCore/GameEngineActor.h>


// 설명 : 
class WindowPanelUI : public GameEngineActor
{
public:
	// constrcuter destructer
	WindowPanelUI();
	~WindowPanelUI();

	// delete Function
	WindowPanelUI(const WindowPanelUI& _Other) = delete;
	WindowPanelUI(WindowPanelUI&& _Other) noexcept = delete;
	WindowPanelUI& operator=(const WindowPanelUI& _Other) = delete;
	WindowPanelUI& operator=(WindowPanelUI&& _Other) noexcept = delete;


	void Init(const std::string& _FileName, const std::string& _Path);


	void onPanel()
	{
		On();
	}

	void offPanel()
	{
		Off();
	}

protected:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;

private:



	// this
	// Renderer
	GameEngineRenderer* Renderer = nullptr;


};