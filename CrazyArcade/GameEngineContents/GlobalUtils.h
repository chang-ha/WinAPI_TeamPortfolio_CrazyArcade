#pragma once
#include <string>

// 설명 : 텍스처나 스프라이트, 사운드 등 유용한 기능을 전역 함수로 제공해줍니다.
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

