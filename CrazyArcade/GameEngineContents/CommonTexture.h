#pragma once
#include <GameEngineCore/GameEngineActor.h>


// ���� : �ܼ��� ȭ�鿡 �ؽ�ó�� ���� ���� Ŭ�����Դϴ�.
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

	float4 getTextureScale() const
	{
		return m_TextureScale;
	}

protected:

private:
	// GameEngineObject ���
	void Start() override;

	// this
	GameEngineRenderer* Renderer = nullptr;

	float4 m_TextureScale = float4::ZERO;
};

