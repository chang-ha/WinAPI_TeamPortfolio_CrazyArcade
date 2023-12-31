#pragma once
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineActor.h>

#include <functional>




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

	
	void setRenderer(RenderOrder _Order)
	{
		return setRenderer(static_cast<int>(_Order));
	}

	void setRenderer(int _Order);

	void setButtonPos(const float4& _Pos);

	float4 getButtonScale()
	{
		return m_ButtonScale;
	}


	void setButtonTexture(
		ButtonState _ButtonType,
		const std::string& _FileName, 
		const std::string& _Path,
		int _XCount, int _YCount,
		float _Inter = 0.1f, 
		bool _Loop = true, 
		float _RenderScaleRatio = 1.0f);



	void setButtonSound(
		ButtonEventState _ButtonType,
		const std::string& _FileName,
		const std::string& _Path);



	void enableButton(bool Enable)
	{
		m_ButtonState = Enable ? ButtonState::Normal : ButtonState::Disable;

		if (ButtonState::Disable == m_ButtonState)
		{
			EnableRenderValue = true;
		}
	}

	template<typename ActorType>
	void setCallback(ButtonEventState _ButtonState, ActorType* _Actor, void(ActorType::* _Func)())
	{
		m_ButtonEventCallBack[static_cast<int>(_ButtonState)] = std::bind(_Func, _Actor);
	}

	void setButtonVolume(ButtonEventState _ButtonState, float _Volume)
	{
		vecButtonVolume[static_cast<int>(_ButtonState)] = _Volume;
	}

	void setButtonText(std::string _Text)
	{
		ButtonText = _Text;
	}


protected:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:



	// this
	// Renderer
	GameEngineRenderer* Renderer = nullptr;

	float4 m_ButtonStartPos = float4::ZERO;
	float4 m_ButtonScale = float4::ZERO;


	ButtonState m_ButtonState = ButtonState::Max;
	std::function<void()> m_ButtonEventCallBack[static_cast<int>(ButtonEventState::Max)];
	std::string m_ButtonSoundEvent[static_cast<int>(ButtonEventState::Max)];
	std::vector<float> vecButtonVolume;

	bool checkHovered();
	bool m_ButtonHoverValue = false;

	bool EnableRenderValue = false;

	// 버튼 텍스트
	std::string ButtonText = "";

};