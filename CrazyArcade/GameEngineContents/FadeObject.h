#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <GameEngineCore/GameEngineLevel.h>


enum class CallFadeType
{
	FadeOut,
	FadeIn,
	Max,
};

// 설명 : FadeOut은 하나만 가능합니다.
class FadeObject : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeObject();
	~FadeObject();

	// delete Function
	FadeObject(const FadeObject& _Other) = delete;
	FadeObject(FadeObject&& _Other) noexcept = delete;
	FadeObject& operator=(const FadeObject& _Other) = delete;
	FadeObject& operator=(FadeObject&& _Other) noexcept = delete;

	
	static void CallFadeOut(GameEngineLevel* _Level, float _FadeOutDuration = 1.0f, int _Alpha = 0);
	static void CallFadeIn(GameEngineLevel* _Level, float _FadeOutDuration = 1.0f, int _Alpha = 255);

	static bool isDoneFadeOut()
	{
		if (g_FadeOutValue ==  true)
		{
			g_FadeOutValue = false;

			return true;
		}

		return false;
	}

protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Detla) override;



	// this
	GameEngineRenderer* Renderer = nullptr;

	CallFadeType m_FadeType = CallFadeType::Max;

	static bool g_FadeOutValue;

	int m_Alpha = 0;
	int m_RequestAlphaValue = 0;

	float m_FadeDuration = 1.0f;
	float m_FadeTime = 0.0f;


	const float MinAlphaValue = 0;
	const float MaxAlphaValue = 255;


	int m_DebugAlphaValue = 0;
};

