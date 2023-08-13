#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <vector>
#include <string>

enum class PlaceType
{
	Ten,
	One,
	DemicalOne,
	Max,
};



// 설명 :
class ExpUI : public GameEngineActor
{
public:
	// constrcuter destructer
	ExpUI();
	~ExpUI();

	// delete Function
	ExpUI(const ExpUI& _Other) = delete;
	ExpUI(ExpUI&& _Other) noexcept = delete;
	ExpUI& operator=(const ExpUI& _Other) = delete;
	ExpUI& operator=(ExpUI&& _Other) noexcept = delete;


	void initExpUI();

	void showExpUI();
	void OffExpUI();

	void changePercent(int _Percentage);
	void changePercent(int _initScore, int _TargetScore, int _MaxScore);

	void ActorRelease();



protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;


	void LevelEnd() override;

	// this
	void loadEXPUITexture();

	void setGauge();
	std::vector<GameEngineRenderer*> vecGaugeRender;
	const int CONST_GaugeCount = 60;
	const int CONST_ColorCountArr[4] = { 30, 45, 55, 60};
	const float4 CONST_ExpUIGaugeStartPos = float4{ 1.0f, 1.0f };

	
	struct ExpUiInfo
	{
	public:
		class CommonTexture* Back = nullptr;
		class CommonTexture* TenSpace = nullptr;
		class CommonTexture* OneSpace = nullptr;
		class CommonTexture* DotSpace = nullptr;
		class CommonTexture* DecimalOneSpace = nullptr;
		class CommonTexture* Percent = nullptr;
	};

	void setupExpInfo();
	ExpUiInfo m_ExpUiInfo;
	int m_RenderScore = 0;
	int m_InitScore = 0;
	int m_TargetScore = 0;
	int m_MaxScore = 0;
	float m_Volume = 0;
	float UpdateTime = 0.0f;
	const float UpdateDuration = 3.0f;

	int m_ExpGaugeRenderCount = 0;

	void setupBack();

	void setupTenSpace();
	const float4 CONST_TenSpaceStartPos = float4{ 10.0f , 2.0f };

	void setupOneSpace();
	const float4 CONST_OneSpaceStartPos = float4{ 19.0f , 2.0f };

	void setupDotSpace();
	const float4 CONST_DotSpaceStartPos = float4{ 29.0f , 2.0f };

	void setupDecimalOneSpace();
	const float4 CONST_DecimalOneSpaceStartPos = float4{ 34.0f , 2.0f };

	void setupPercent();
	const float4 CONST_PercentStartPos = float4{ 43.0f , 2.0f };

	void changePercentNumber(PlaceType _Type, int _Number);
	void changeExpGauge(int _Score);

	void updateExpPercent(float _Delta);
};