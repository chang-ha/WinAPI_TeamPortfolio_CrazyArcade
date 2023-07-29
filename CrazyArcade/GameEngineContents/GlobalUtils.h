#pragma once
#include <string>

// ���� : �ؽ�ó�� ��������Ʈ, ���� �� ������ ����� ���� �Լ��� �������ݴϴ�.
class GlobalUtils
{
public:

	static class GameEngineWindowTexture* TextureFileLoad(const std::string& _FileName, const std::string& _Path);
	static class GameEngineSprite* SpriteFileLoad(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount);

	static void SoundFileLoad(const std::string& _FileName, const std::string& _Path);



protected:

private:
	// constrcuter destructer
	GlobalUtils();
	~GlobalUtils();

	// delete Function
	GlobalUtils(const GlobalUtils& _Other) = delete;
	GlobalUtils(GlobalUtils&& _Other) noexcept = delete;
	GlobalUtils& operator=(const GlobalUtils& _Other) = delete;
	GlobalUtils& operator=(GlobalUtils&& _Other) noexcept = delete;
};

