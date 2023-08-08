#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <vector>


enum class TimerType
{
	MinuteTensRenderer,
	MinuteUnitsRenderer,
	Colon,
	SecondTensRenderer,
	SecondUnitsRenderer,
	Max,
};


// Ό³Έν :
class PlayTimer : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayTimer();
	~PlayTimer();

	// delete Function
	PlayTimer(const PlayTimer& _Other) = delete;
	PlayTimer(PlayTimer&& _Other) noexcept = delete;
	PlayTimer& operator=(const PlayTimer& _Other) = delete;
	PlayTimer& operator=(PlayTimer&& _Other) noexcept = delete;


	void flowTimer()
	{
		m_TimeFlowValue = true;
	}

	void stopTimer()
	{
		m_TimeFlowValue = false;
	}

	bool getTimeFlowValue()
	{
		return m_TimeFlowValue;
	}

	void addTimer(float _Delta)
	{
		m_PlayTimerValue += _Delta;

		int TimerValue = static_cast<int>(m_PlayTimerValue);

		updateRendererTimer(TimerValue);
	}

	void setTimer(float _Delta)
	{
		m_PlayTimerValue = _Delta;

		int TimerValue = static_cast<int>(m_PlayTimerValue);

		updateRendererTimer(TimerValue);
	}

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// this
	void loadTexture();
	float4 NumberScale = float4::ZERO;


	struct TimerElement
	{
	public:
		GameEngineRenderer* m_Renderer = nullptr;
		int m_Value = 0;
	};

	void initRenderer();
	std::vector<TimerElement> vecTimerElemnet;

	void updateRendererTimer(int _Value);

	void updateTimer(float _Delta);

	bool m_TimeFlowValue = false;
	int m_RenderValue = 0;
	float m_PlayTimerValue = 0.0f;
	float m_PlayTimerRender = 0.0f;
};

