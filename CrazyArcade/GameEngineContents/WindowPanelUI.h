#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <vector>

// 설명 : 
class Button;
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


	virtual void onPanel() {}

	virtual void offPanel() {}

protected:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;

	// this
	// Renderer
	GameEngineRenderer* Renderer = nullptr;

	float4 m_WindowScale = float4::ZERO;


	std::vector<Button*> vecButton;

	

private:





};