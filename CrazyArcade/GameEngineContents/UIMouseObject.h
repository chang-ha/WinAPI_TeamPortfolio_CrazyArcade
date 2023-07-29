#pragma once
#include <GameEngineCore/GameEngineActor.h>


enum class MouseState
{
	Normal,
	Click,
	Max,
};



// 설명 :
class UIMouseObject : public GameEngineActor
{
public:
	// constrcuter destructer
	UIMouseObject();
	~UIMouseObject();

	// delete Function
	UIMouseObject(const UIMouseObject& _Other) = delete;
	UIMouseObject(UIMouseObject&& _Other) noexcept = delete;
	UIMouseObject& operator=(const UIMouseObject& _Other) = delete;
	UIMouseObject& operator=(UIMouseObject&& _Other) noexcept = delete;


	void setTexture(
		MouseState _MouseType,
		const std::string& _FileName,
		const std::string& _Path,
		int _XCount, int _YCount,
		float _Inter = 0.1f,
		bool _Loop = true,
		float _RenderScaleRatio = 1.0f);


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// this
	class GameEngineRenderer* Renderer = nullptr;

	MouseState m_MouseState = MouseState::Max;

	float4 MousePos = float4::ZERO;

	const float MouseDisappearTime = 1.0f;
	float MouseStateTime = 0.0f;


};

