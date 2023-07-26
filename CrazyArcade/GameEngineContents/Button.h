#pragma once
#include <GameEngineCore/GameEngineActor.h>


#define DefaultButtonKey 1
#define ClickedButtonKey 2
#define HoveredButtonKey 4


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
		size_t _XCount = 0, size_t _YCount = 0,
		float _Inter = 0.1f, 
		bool _Loop = true, 
		float _RenderScaleRatio = 1.0f);

	void InitClickedButton(
		const std::string& _FileName,
		const std::string& _Path,
		size_t _XCount = 0, size_t _YCount = 0,
		float _Inter = 0.1f,
		bool _Loop = true,
		float _RenderScaleRatio = 1.0f);


	void InitHoveredButton(
		const std::string& _FileName,
		const std::string& _Path,
		size_t _XCount = 0, size_t _YCount = 0,
		float _Inter = 0.1f,
		bool _Loop = true,
		float _RenderScaleRatio = 1.0f);

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
	ButtonState m_ButtonState = ButtonState::Max;

	struct ButtonInfo
	{
	public:

	};

	ButtonInfo m_ButtonInfo[static_cast<int>(ButtonState::Max)];


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


	// Coliision
	GameEngineCollision* ButtonCollision = nullptr;


	// 버튼 텍스트
	std::string ButtonText = "";



};