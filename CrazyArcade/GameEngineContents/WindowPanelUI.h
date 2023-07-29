#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineLevel.h>

#include <vector>


enum class WindowState
{
	Open,
	Close,
};


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


	void enableWindow(bool _Value)
	{
		On();

		_Value ? m_WindowState = WindowState::Open : m_WindowState = WindowState::Close;
	}


	bool isOpenWindow()
	{
		return m_OpenWindowValue;
	}


protected:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;

	// this
	// Renderer
	GameEngineRenderer* Renderer = nullptr;

	float4 m_WindowScale = float4::ZERO;

	std::vector<Button*> vecButton;


	WindowState m_WindowState = WindowState::Close;

	virtual void onPanel() {}
	virtual void offPanel() {}


private:
	bool m_OpenWindowValue = false;

};