#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <GameEngineCore/GameEngineLevel.h>

#include <string>


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

	
	static void CallFadeOut(GameEngineLevel* _Level, const std::string& _LevelName, float _FadeOutDuration = 1.0f, int _Alpha = 0);
	static void CallFadeIn(GameEngineLevel* _Level, float _FadeOutDuration = 1.0f, int _Alpha = 255);


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Detla) override;

	// GameEngineLevel 상속
	void LevelEnd() override;



	// this
	GameEngineRenderer* Renderer = nullptr;

	CallFadeType m_FadeType = CallFadeType::Max;

	std::string m_NextLevelName = "";


	int m_Alpha = 0;
	int m_RequestAlphaValue = 0;

	float m_FadeDuration = 1.0f;
	float m_FadeTime = 0.0f;


	const int MinAlphaValue = 0;
	const int MaxAlphaValue = 255;


	int m_DebugAlphaValue = 0;
};

