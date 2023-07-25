#include "GlobalUtils.h"


#include <GameEnginePlatform/GameEngineSound.h>


#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/ResourcesManager.h>



GlobalUtils::GlobalUtils() 
{
}

GlobalUtils::~GlobalUtils() 
{
}


// 텍스처 로드 프로시저
GameEngineWindowTexture* GlobalUtils::TextureFileLoad(const std::string& _FileName, const std::string& _Path)
{
	GameEngineWindowTexture* Texture = nullptr;

	if (true == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		Texture = ResourcesManager::GetInst().FindTexture(_FileName);
		if (nullptr == Texture)
		{
			MsgBoxAssert("텍스처를 불러오지 못했습니다.");
			return Texture;
		}

		return Texture;
	}

	GameEnginePath FilePath;

	std::string ParentPath = GameEnginePath::GetParentString(_Path);
	FilePath.MoveParentToExistsChild(ParentPath);
	FilePath.MoveChild(_Path);
	Texture = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath(_FileName));
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 로드하지 못했습니다.");
		return Texture;
	}

	return Texture;
}


// 스프라이드 프로시져
GameEngineSprite* GlobalUtils::SpriteFileLoad(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount)
{
	GameEngineSprite* Sprite = nullptr;

	if (true == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		Sprite = ResourcesManager::GetInst().FindSprite(_FileName);
		if (nullptr == Sprite)
		{
			MsgBoxAssert("스프라이트를 불러오지 못했습니다.");
			return Sprite;
		}

		return Sprite;
	}

	GameEnginePath FilePath;

	std::string ParentPath = GameEnginePath::GetParentString(_Path);
	FilePath.MoveParentToExistsChild(ParentPath);
	FilePath.MoveChild(_Path);

	Sprite = ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath(_FileName), _XCount, _YCount);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("스프라이트를 생성하지 못했습니다.");
		return Sprite;
	}

	return Sprite;
}


// 사운드 로드 프로시저
void GlobalUtils::SoundFileLoad(const std::string& _FileName, const std::string& _Path)
{
	if (nullptr != GameEngineSound::FindSound(_FileName))
	{
		return;
	}

	GameEnginePath FilePath;

	std::string ParentPath = GameEnginePath::GetParentString(_Path);
	FilePath.MoveParentToExistsChild(ParentPath);
	FilePath.MoveChild(_Path);

	GameEngineSound::SoundLoad(FilePath.PlusFilePath(_FileName));
}
