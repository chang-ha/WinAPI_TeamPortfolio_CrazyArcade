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


// �ؽ�ó �ε� ���ν���
GameEngineWindowTexture* GlobalUtils::TextureFileLoad(const std::string& _FileName, const std::string& _Path)
{
	GameEngineWindowTexture* Texture = nullptr;

	if (true == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		Texture = ResourcesManager::GetInst().FindTexture(_FileName);
		if (nullptr == Texture)
		{
			MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
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
		MsgBoxAssert("�ؽ�ó�� �ε����� ���߽��ϴ�.");
		return Texture;
	}

	return Texture;
}


// �������̵� ���ν���
GameEngineSprite* GlobalUtils::SpriteFileLoad(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount)
{
	GameEngineSprite* Sprite = nullptr;

	if (true == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		Sprite = ResourcesManager::GetInst().FindSprite(_FileName);
		if (nullptr == Sprite)
		{
			MsgBoxAssert("��������Ʈ�� �ҷ����� ���߽��ϴ�.");
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
		MsgBoxAssert("��������Ʈ�� �������� ���߽��ϴ�.");
		return Sprite;
	}

	return Sprite;
}


// ���� �ε� ���ν���
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
