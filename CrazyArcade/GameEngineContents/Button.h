#pragma once
#include <GameEngineCore/GameEngineActor.h>




enum class ButtonState
{
	Normal,
	Hover,
	Click,
	Disable,
	Max,
};

enum class ButtonEventState
{
	Hover,
	Click,
	Max,
};




// 설명 : 
class Button : public GameEngineActor
{
public:
	// constrcuter destructer
	Button();
	~Button();

	// delete Function
	Button(const Button& _Other) = delete;
	Button(Button&& _Other) noexcept = delete;
	Button& operator=(const Button& _Other) = delete;
	Button& operator=(Button&& _Other) noexcept = delete;




	void InitDefaultButton(
		const std::string& _FileName, 
		const std::string& _Path,
		int _XCount, int _YCount,
		float _Inter = 0.1f, 
		bool _Loop = true, 
		float _RenderScaleRatio = 1.0f);

	void InitClickButton(
		const std::string& _FileName,
		const std::string& _Path,
		int _XCount, int _YCount,
		float _Inter = 0.1f,
		bool _Loop = true,
		float _RenderScaleRatio = 1.0f);

	void InitHoveredButton(
		const std::string& _FileName,
		const std::string& _Path,
		int _XCount, int _YCount,
		float _Inter = 0.1f,
		bool _Loop = true,
		float _RenderScaleRatio = 1.0f);

	ButtonState m_ButtonState = ButtonState::Max;


	void setButtonText(std::string _Text)
	{
		ButtonText = _Text;
	}

protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;



	// this
	struct ButtonEventInfo
	{
	public:
		

	};


	ButtonEventInfo m_ButtonEventInfo[static_cast<int>(ButtonEventState::Max)];
	float4 m_ButtonScale = float4::ZERO;


	bool checkHovered();

	virtual void execute() {}


	// Render
	GameEngineRenderer* Renderer = nullptr;



	// 버튼 텍스트
	std::string ButtonText = "";



};