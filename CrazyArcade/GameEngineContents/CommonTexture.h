#pragma once
#include <GameEngineCore/GameEngineActor.h>


// 설명 : 단순히 화면에 텍스처를 띄우기 위한 클래스입니다.
class CommonTexture : public GameEngineActor
{
public:
	// constrcuter destructer
	CommonTexture();
	~CommonTexture();

	// delete Function
	CommonTexture(const CommonTexture& _Other) = delete;
	CommonTexture(CommonTexture&& _Other) noexcept = delete;
	CommonTexture& operator=(const CommonTexture& _Other) = delete;
	CommonTexture& operator=(CommonTexture&& _Other) noexcept = delete;


	void loadTexture(const std::string& _FileName, const std::string& _Path);
	void setTexture(const std::string& _FileName);

	template<typename OrderType>
	void setRendererOrder(OrderType _Order)
	{
		return setRendererOrder(static_cast<int>(_Order));
	}

	void setRendererCopyPos(const float4& _Scale, int _XBoxNumber, int _YBoxNumber);
	void setRendererCopyAndRenderScale(int _XBoxNumber, int _YBoxNumber);
	void setRendererCopyPos(int _XBoxNumber, int _YBoxNumber);

	void setRendererOrder(int _Order);


	GameEngineRenderer* getRenderer()
	{
		return Renderer;
	}

	float4 getTextureScale() const
	{
		return m_TextureScale;
	}

	float4 getScale() const
	{
		return m_Scale;
	}



protected:

private:
	// GameEngineObject 상속
	void Start() override;

	// this
	GameEngineRenderer* Renderer = nullptr;

	float4 m_TextureScale = float4::ZERO;
	float4 m_Scale = float4::ZERO;
};

