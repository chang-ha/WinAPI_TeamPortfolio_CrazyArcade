#include "PlayLevel.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/TileMap.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>


#include "BackGround.h"
#include "Dao.h"
#include "Bazzi.h"
#include "Kephi.h"
#include "Marid.h"
#include "BaseMonster.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "GlobalUtils.h"
#include "GlobalLoad.h"
#include "GameMapInfo.h"
#include "FadeObject.h"
#include "FadeScreen.h"
#include "CommonTexture.h"
#include "PlayTimer.h"
#include "PlayPortrait.h"
#include "PlayCharacterPortrait.h"
#include "GameStartAnimation.h"
#include "PlayResultWindow.h"
#include "GameOverAnimation.h"
#include "StageStartBossBillBoard.h"
#include "Button.h"
#include "Item.h"
#include "ItemSoket.h"
#include "Penguin.h"

PlayLevel* PlayLevel::CurPlayLevel = nullptr;

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CurPlayLevel = this;

	CharacterSetting();
	if (nullptr != Player)
	{
		Player->SetPos(GlobalValue::WinScale.Half());
	}
	
	if (nullptr != Player2)
	{
		Player2->SetPos(GlobalValue::WinScale.Half());
		
	}

	if (nullptr != Player)
	{
		if (nullptr != Player2)
		{
			LevelPlayState = PlayState::Multi;
			Back->Init("PlayPanel_2P.bmp");

			ItemSoket* Multi_P1ItemSoket = CreateActor<ItemSoket>(UpdateOrder::UI);
			Multi_P1ItemSoket->SetPos(GlobalValue::ItemSoketPos_Multi_1P_Pos);
			Sokets.push_back(Multi_P1ItemSoket);
			Multi_P1ItemSoket = nullptr;

			ItemSoket* Multi_P2ItemSoket = CreateActor<ItemSoket>(UpdateOrder::UI);
			Multi_P2ItemSoket->SetPos(GlobalValue::ItemSoketPos_Multi_2P_Pos);
			Sokets.push_back(Multi_P2ItemSoket);
			Multi_P2ItemSoket = nullptr;
		}
		else
		{
			LevelPlayState = PlayState::Single;
			Back->Init("PlayPanel.bmp");

			ItemSoket* UseItemSoket = CreateActor<ItemSoket>(UpdateOrder::UI);
			UseItemSoket->SetPos(GlobalValue::ItemSoketPos_Single_Pos);
			Sokets.push_back(UseItemSoket);
			UseItemSoket = nullptr;
		}
	}

	UILevelStart();
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (Player != nullptr)
	{
		Player->Death();
		Player = nullptr;
	}

	if (Player2 != nullptr)
	{
		Player2->Death();
		Player2 = nullptr;
	}

	if (AllBubbleIndex.size() > 0)
	{
		AllBubbleIndex.clear();
	}

	StageMonstersDeath();

	SoketRelease();
	ItemRelease();

	UILevelEnd();

	BGMPlayer.Stop();
}

void PlayLevel::Start()
{
	Back = CreateActor<BackGround>(UpdateOrder::Map);
	if (nullptr == Back)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}
	Back->SetPos(GlobalValue::WinScale.Half());

	// Sound Load
	GlobalUtils::SoundFileLoad("Bubble_Install.wav", "Resources\\Sounds\\Character\\");
	GlobalUtils::SoundFileLoad("Bubble_Pop.wav", "Resources\\Sounds\\Character\\");
	GlobalUtils::SoundFileLoad("Game_Start.wav", "Resources\\Sounds\\GamePlay");
	GlobalUtils::SoundFileLoad("Next_Level_Ready.wav", "Resources\\Sounds\\GamePlay");

	// Object Texture Load
	GlobalLoad::TileTextureLoad();

	// TileInfo Initialize
	TileInfo.assign(GlobalValue::MapTileIndex_Y, (std::vector<GameMapInfo>(GlobalValue::MapTileIndex_X, GameMapInfo::DefaultInfo)));

	// Item Initialize
	Items.assign(GlobalValue::MapTileIndex_Y, (std::vector<Item*>(GlobalValue::MapTileIndex_X, nullptr)));

	GetMainCamera()->SetYSort(RenderOrder::MapObject, true);
}

void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('H'))
	{
		CollisionDebugRenderSwitch();
	}

	if (true == GameEngineInput::IsDown(VK_F5))
	{
		GameEngineCore::ChangeLevel("Penguin_Stage1");
	}
	if (true == GameEngineInput::IsDown(VK_F6))
	{
		GameEngineCore::ChangeLevel("Penguin_Stage2");
	}
	if (true == GameEngineInput::IsDown(VK_F7))
	{
		GameEngineCore::ChangeLevel("Penguin_Stage3");
	}

	updateGameOverResult(_Delta);

	ContentLevel::Update(_Delta);

	updateVictoryRoll();

	updateCharacterPortrait();

	ClearBossPattern();

	// 물폭탄의 타이머를 위한 for문
	if (AllBubbleIndex.size() > 0)
	{
		std::list<GameMapBubble>::iterator StartIter = AllBubbleIndex.begin();
		std::list<GameMapBubble>::iterator EndIter = AllBubbleIndex.end();

		for (; StartIter != EndIter;)
		{
			GameMapBubble CheckBubble = *StartIter;
			GameMapIndex CheckIndex = CheckBubble.Index;

			if (TileInfo[CheckIndex.Y][CheckIndex.X].PrevPop == false)
			{
				TileInfo[CheckIndex.Y][CheckIndex.X].Timer += _Delta;
			}

			if (TileInfo[CheckIndex.Y][CheckIndex.X].PrevPop == true)
			{
				AllBubbleIndex.erase(StartIter);
				TileInfo[CheckIndex.Y][CheckIndex.X].PrevPop = false;
				break;
			}
			else if (TileInfo[CheckIndex.Y][CheckIndex.X].Timer > 3.0f && nullptr == GameOverAnimationPtr)
			{
				BubblePop(CheckIndex.X, CheckIndex.Y);
				AllBubbleIndex.erase(StartIter);
				break;
			}
			else
			{
				++StartIter;
			}
		}
	}

	// 터진 부분의 Effect를 지워주기 위한 for문
	if (AllBubbleDeathIndex.size() > 0)
	{
		std::list<GameMapBubble>::iterator StartIter = AllBubbleDeathIndex.begin();
		std::list<GameMapBubble>::iterator EndIter = AllBubbleDeathIndex.end();

		for (; StartIter != EndIter;)
		{
			GameMapBubble CheckPopRange = *StartIter;
			GameMapIndex CheckIndex = CheckPopRange.Index;

			GameEngineRenderer* PopRenderer = ObjectTile->GetTile(CheckIndex.X, CheckIndex.Y);

			if (nullptr == PopRenderer)
			{
				AllBubbleDeathIndex.erase(StartIter);
				break;
			}

			// Pop 애니메이션이 끝난 후 해당 물폭탄 삭제
			if (true == PopRenderer->IsAnimationEnd())
			{
				TileInfo[CheckIndex.Y][CheckIndex.X].MapInfo = TileObjectOrder::Empty;
				TileInfo[CheckIndex.Y][CheckIndex.X].ObjectTextureInfo = 0;
				TileInfo[CheckIndex.Y][CheckIndex.X].BubblePower = 0;

				AllBubbleDeathIndex.erase(StartIter);
				ObjectTile->DeathTile(CheckIndex.X, CheckIndex.Y);
				break;
			}
			else
			{
				++StartIter;
			}
		}
		PlayBubblePopEffectSound = false;
	}

	// Item Debug
	if (true == GameEngineInput::IsDown('I'))
	{
		ItemDebugValue = !ItemDebugValue;
		for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
		{
			for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
			{
				if (nullptr != Items[Y][X])
				{
					if (true == ItemDebugValue)
					{
						if (true == Items[Y][X]->ItemInBlock())
						{
							Items[Y][X]->On();
						}
					}
					else
					{
						if (true == Items[Y][X]->ItemInBlock())
						{
							Items[Y][X]->Off();
						}
					}
				}
			}
		}
	}

	if (PlayState::Single == LevelPlayState)
	{

		switch (Player->GetNeedle())
		{
		case 0:
			if (nullptr != Sokets[0])
			{
				Sokets[0]->EmptyingSoket();
			}
			break;
		default:
			if (nullptr != Sokets[0])
			{
				Sokets[0]->HoldingItem(ItemType::Needle);
			}
			break;
		}
		
	}
	else if (PlayState::Multi == LevelPlayState)
	{

		switch (Player->GetNeedle())
		{
		case 0:
			if (nullptr != Sokets[0])
			{
				Sokets[0]->EmptyingSoket();
			}
			break;
		default:
			if (nullptr != Sokets[0])
			{
				Sokets[0]->HoldingItem(ItemType::Needle);
			}
			break;
		}

		switch (Player2->GetNeedle())
		{
		case 0:
			if (nullptr != Sokets[1])
			{
				Sokets[1]->EmptyingSoket();
			}
			break;
		default:
			if (nullptr != Sokets[1])
			{
				Sokets[1]->HoldingItem(ItemType::Needle);
			}
			break;
		}
	}

	// Cheet : All Monster Death
	if (true == GameEngineInput::IsDown(VK_F9))
	{
		StageMonstersDeath();
		return;
	}
}

void PlayLevel::Render(float _Delta)
{

}

void PlayLevel::MapFileLoad(const std::string& _FileName)
{
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("Resources");
	FilePath.MoveChild("Resources\\TileMap\\" + _FileName);

	
	FILE* File = nullptr;

	fopen_s(&File, FilePath.GetStringPath().c_str(), "rb"); // rb : Read Binary

	// Read Data
	for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
	{
		for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
		{
			fread(&TileInfo[Y][X], sizeof(TileInfo[Y][X]), 1, File);
		}
	}

	// File Close
	fclose(File);
}

void PlayLevel::TileSetting()
{
	// TileInfo에 저장된 정보를 이용하여 타일맵 생성합니다.

	if (nullptr == GroundTile)
	{
		GroundTile = CreateActor<TileMap>();
		if (nullptr == GroundTile)
		{
			MsgBoxAssert("타일을 생성하지 못했습니다.");
			return;
		}

		GroundTile->CreateTileMap("Grounds.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::Map);
	}

	if (nullptr == ObjectTile)
	{

		ObjectTile = CreateActor<TileMap>();
		if (nullptr == ObjectTile)
		{
			MsgBoxAssert("타일을 생성하지 못했습니다.");
			return;
		}

		ObjectTile->CreateTileMap("Structures.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::MapObject);
	}

	for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
	{
		for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
		{
			GroundTile->SetTile(X, Y, TileInfo[Y][X].GroundTextureInfo, GlobalValue::TileStartPos);
			switch (TileInfo[Y][X].MapInfo)
			{
			case TileObjectOrder::Structure:
				ObjectTile->SetTileToSprite(X, Y, "Structures.bmp", TileInfo[Y][X].ObjectTextureInfo, GlobalValue::TileStartPos - GlobalValue::StructureOverSize, true);
				break;
			case TileObjectOrder::ImmovableBlock:
				ObjectTile->SetTileToSprite(X, Y, "ImmovableBlocks.bmp", TileInfo[Y][X].ObjectTextureInfo, GlobalValue::TileStartPos - GlobalValue::BlockOverSize, true);
				break;
			case TileObjectOrder::MovableBlock:
				ObjectTile->SetTileToSprite(X, Y, "MovableBlocks.bmp", TileInfo[Y][X].ObjectTextureInfo, GlobalValue::TileStartPos - GlobalValue::BlockOverSize, true);
				break;
			default:
				break;
			}
		}
	}
}

void PlayLevel::ItemSetting()
{
	for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; Y++)
	{
		for (int X = 0; X < GlobalValue::MapTileIndex_X; X++)
		{
			int TileInfoInt = static_cast<int>(TileInfo[Y][X].MapInfo);

			// ImmovableBlock, MovableBlock일 때 아이템 생성
			if (TileInfoInt == 2 ||
				TileInfoInt == 3)
			{
				int RandomNumber = GameEngineRandom::MainRandom.RandomInt(0, 4); // 33.3% 확률로 아이템 생성
				if (1 >= RandomNumber)
				{
					CreateItemInBlockRandom(X, Y);
				}
			}
		}
	}
}

void PlayLevel::SetItemInBlock(int _X, int _Y, ItemType _Type)
{
	if (TileObjectOrder::ImmovableBlock == TileInfo[_Y][_X].MapInfo ||
		TileObjectOrder::MovableBlock == TileInfo[_Y][_X].MapInfo )
	{
		if (nullptr == Items[_Y][_X])
		{
			CreateItemInBlock(_X, _Y, _Type);
		}
		else
		{
			Items[_Y][_X]->SetItemType(_Type);
		}
	}
	else
	{
		const std::string Text = std::to_string(_X) + "x" + std::to_string(_Y) + "해당 타일에 블록이 없습니다.";
		MsgBoxAssert(Text);
	}
}

void PlayLevel::CreateItemInBlock(int _X, int _Y, ItemType _Type)
{
	ItemActor = CreateActor<Item>(UpdateOrder::Map);
	ItemActor->SetItemPos(_X, _Y);
	ItemActor->SetItemType(_Type);
	ItemActor->PutIteminBlock();
	Items[_Y][_X] = ItemActor;
	ItemActor = nullptr;
}

void PlayLevel::CreateItemInBlockRandom(int _X, int _Y)
{
	ItemActor = CreateActor<Item>(UpdateOrder::Map);
	ItemActor->SetItemPos(_X, _Y);
	ItemActor->SetItemTypeRandom();
	ItemActor->PutIteminBlock();
	Items[_Y][_X] = ItemActor;
	ItemActor = nullptr;
}


void PlayLevel::CreateItemInTile(int _X, int _Y, ItemType _Type)
{
	ItemActor = CreateActor<Item>(UpdateOrder::Map);
	ItemActor->SetItemType(_Type);
	ItemActor->SetItemPos(_X, _Y);
	Items[_Y][_X] = ItemActor;
	ItemActor = nullptr;
}


void PlayLevel::CheckItemInTile(int _X, int _Y)
{
	if (nullptr != Items[_Y][_X])
	{
		Items[_Y][_X]->Death();
		Items[_Y][_X] = nullptr;
	}
}

void PlayLevel::CheckItemInTile(float _X, float _Y)
{
	int X = static_cast<int>(_X);
	int Y = static_cast<int>(_Y);
	if (nullptr != Items[Y][X])
	{
		Items[Y][X]->Death();
		Items[Y][X] = nullptr;
	}
}

void PlayLevel::ItemRelease()
{
	for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; ++Y)
	{
		for (int X = 0; X < GlobalValue::MapTileIndex_X; ++X)
		{
			if (nullptr != Items[Y][X])
			{
				Items[Y][X]->Death();
				Items[Y][X] = nullptr;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 캐릭터
void PlayLevel::CharacterSetting()
{
	// Create Character
	if (GlobalValue::g_SelectAvailableCharacter1 == AvailableCharacterList::Bazzi)
	{
		Player = CreateActor<Bazzi>(UpdateOrder::Character);
	}
	else if (GlobalValue::g_SelectAvailableCharacter1 == AvailableCharacterList::Dao)
	{
		Player = CreateActor<Dao>(UpdateOrder::Character);
	}
	else if (GlobalValue::g_SelectAvailableCharacter1 == AvailableCharacterList::Kephi)
	{
		Player = CreateActor<Kephi>(UpdateOrder::Character);
	}
	else if (GlobalValue::g_SelectAvailableCharacter1 == AvailableCharacterList::Marid)
	{
		Player = CreateActor<Marid>(UpdateOrder::Character);
	}
	else
	{
		MsgBoxAssert("플레이어 1은 반드시 생성되어야 합니다.");
		return;
	}

	if (GlobalValue::g_ActiveRoomCount == 2)
	{
		if (GlobalValue::g_SelectAvailableCharacter2 == AvailableCharacterList::Bazzi)
		{
			Player2 = CreateActor<Bazzi>(UpdateOrder::Character);
		}
		else if (GlobalValue::g_SelectAvailableCharacter2 == AvailableCharacterList::Dao)
		{
			Player2 = CreateActor<Dao>(UpdateOrder::Character);
		}
		else if (GlobalValue::g_SelectAvailableCharacter2 == AvailableCharacterList::Kephi)
		{
			Player2 = CreateActor<Kephi>(UpdateOrder::Character);
		}
		else if (GlobalValue::g_SelectAvailableCharacter2 == AvailableCharacterList::Marid)
		{
			Player2 = CreateActor<Marid>(UpdateOrder::Character);
		}
		else
		{
			return;
		}
	}

	if (Player2 != nullptr)
	{
		Player2->SetPlayer2();
	}
}

bool PlayLevel::CheckTile(const float4& _Pos, float _Delta, const PlayerNum& _PlayerNum)
{
	float4 CheckPos = _Pos;
	CheckPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
	float4 CheckIndex = ObjectTile->PosToIndex(CheckPos);

	int CheckX = CheckIndex.iX() - 1;
	int CheckY = CheckIndex.iY() - 1;

	GameEngineRenderer* NextTile = ObjectTile->GetTile(CheckX, CheckY);

	static GameMapInfo* PrevTile = nullptr;

	if (true == ObjectTile->IsOver(CheckX, CheckY))
	{
		return true;
	}
	else
	{
		GameMapInfo& CurTile = TileInfo[CheckY][CheckX];

		if (nullptr == PrevTile)
		{
			PrevTile = &CurTile;
		}
		else
		{
			if (PrevTile != &CurTile)
			{
				PrevTile->LerpTimer = 0.0f;
				PrevTile = &CurTile;
			}
		}

		if (TileObjectOrder::Empty == TileInfo[CheckY][CheckX].MapInfo
			|| TileObjectOrder::PopRange == TileInfo[CheckY][CheckX].MapInfo)
		{
			return false;
		}

		if (TileObjectOrder::Structure == TileInfo[CheckY][CheckX].MapInfo)
		{
			return true;
		}

		if (TileObjectOrder::ImmovableBlock == TileInfo[CheckY][CheckX].MapInfo)
		{
			return true;
		}

		if (TileObjectOrder::MovableBlock == TileInfo[CheckY][CheckX].MapInfo)
		{
			TileInfo[CheckY][CheckX].LerpTimer += _Delta;

			if (LerpTime < TileInfo[CheckY][CheckX].LerpTimer)
			{
				MoveTile(NextTile, CheckX, CheckY, _PlayerNum);
				return false;
			}
			return true;
		}

		if (TileObjectOrder::Bubble == TileInfo[CheckY][CheckX].MapInfo)
		{
			float4 CheckPos = float4::ZERO;

			if (_PlayerNum == PlayerNum::P1)
			{
				CheckPos = Player->GetPos() + float4{ 0.0f, 15.0f };
			}
			else
			{
				CheckPos = Player2->GetPos() + float4{ 0.0f, 15.0f };
			}

			CheckPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
			float4 CheckIndex = ObjectTile->PosToIndex(CheckPos);

			int PlayerX = CheckIndex.iX() - 1;
			int PlayerY = CheckIndex.iY() - 1;

			if (TileObjectOrder::Bubble == TileInfo[PlayerY][PlayerX].MapInfo)
			{
				return false;
			}
			return true;
		}

		return false;
	}	
}

bool PlayLevel::CheckSidePos(const float4& _Pos, const PlayerNum& _PlayerNum)
{
	float4 CheckPos = _Pos;
	CheckPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
	float4 CheckIndex = ObjectTile->PosToIndex(CheckPos);

	int CheckX = CheckIndex.iX() - 1;
	int CheckY = CheckIndex.iY() - 1;

	GameEngineRenderer* NextTile = ObjectTile->GetTile(CheckX, CheckY);

	if (true == ObjectTile->IsOver(CheckX, CheckY))
	{
		return true;
	}
	else
	{
		if (TileObjectOrder::Empty == TileInfo[CheckY][CheckX].MapInfo
			|| TileObjectOrder::PopRange == TileInfo[CheckY][CheckX].MapInfo)
		{
			return false;
		}

		if (TileObjectOrder::Bubble == TileInfo[CheckY][CheckX].MapInfo)
		{
			float4 CheckPos = float4::ZERO;

			if (_PlayerNum == PlayerNum::P1)
			{
				CheckPos = Player->GetPos() + float4{ 0.0f, 15.0f };
			}
			else
			{
				CheckPos = Player2->GetPos() + float4{ 0.0f, 15.0f };
			}

			CheckPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
			float4 CheckIndex = ObjectTile->PosToIndex(CheckPos);

			int PlayerX = CheckIndex.iX() - 1;
			int PlayerY = CheckIndex.iY() - 1;

			if (TileObjectOrder::Bubble == TileInfo[PlayerY][PlayerX].MapInfo)
			{
				return false;
			}
			return true;
		}

		return true;
	}
}

void PlayLevel::MoveTile(GameEngineRenderer* _Renderer, int _X, int _Y, const PlayerNum& _PlayerNum)
{
	static bool MoveCheck = false;

	ActorDir PlayerDir = ActorDir::Max;

	if (PlayerNum::P1 == _PlayerNum)
	{
		PlayerDir = Player->GetDir();
	}
	else if(PlayerNum::P2 == _PlayerNum)
	{
		PlayerDir = Player2->GetDir();
	}
	
	MOVEDIR LerpDir = MOVEDIR::NONE;
	float4 ItemMoveDir = float4::ZERO;
	int NewX = _X;
	int NewY = _Y;

	switch (PlayerDir)
	{
	case ActorDir::Left:
		LerpDir = MOVEDIR::LEFT;
		ItemMoveDir = float4::LEFT;
		--NewX;
		break;
	case ActorDir::Right:
		LerpDir = MOVEDIR::RIGHT;
		ItemMoveDir = float4::RIGHT;
		++NewX;
		break;
	case ActorDir::Up:
		LerpDir = MOVEDIR::UP;
		ItemMoveDir = float4::UP;
		--NewY;
		break;
	case ActorDir::Down:
		LerpDir = MOVEDIR::DOWN;
		ItemMoveDir = float4::DOWN;
		++NewY;
		break;
	default:
		break;
	}

	if (nullptr != _Renderer)
	{
		if (true == ObjectTile->IsOver(NewX, NewY))
		{
			return;
		}

		if (TileObjectOrder::Empty != TileInfo[NewY][NewX].MapInfo)
		{
			return;
		}

		// TileInfo 수정
		GameMapInfo Temp = TileInfo[_Y][_X];
		TileInfo[_Y][_X] = TileInfo[NewY][NewX];
		TileInfo[NewY][NewX] = Temp;

		//MoveCheck = ObjectTile->LerpTile(_Renderer, LerpDir, GlobalValue::MapTileSize - GlobalValue::TileStartPos);
		MoveCheck = ObjectTile->LerpTile(_Renderer, LerpDir, GlobalValue::TileStartPos + float4(0, -20));
		TileInfo[NewY][NewX].LerpTimer = 0.0f;

		// Item 수정
		CheckItemInTile(NewX, NewY);
		if (nullptr != Items[_Y][_X])
		{
			Items[NewY][NewX] = Items[_Y][_X];
			Items[NewY][NewX]->SetItemPos(NewX, NewY);
			Items[_Y][_X] = nullptr;
		}
	}
}

TileObjectOrder PlayLevel::GetCurTileType(const float4& _Pos)
{
	float4 CharacterPos = _Pos;
	CharacterPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
	float4 ChangeIndex = ObjectTile->PosToIndex(CharacterPos);

	int CurIndexX = ChangeIndex.iX() - 1;
	int CurIndexY = ChangeIndex.iY() - 1;

	if (true == GroundTile->IsOver(CurIndexX, CurIndexY))
	{
		if (CurIndexX < 0)
		{
			CurIndexX = 0;
		}
		if(CurIndexX >= GlobalValue::MapTileIndex_X)
		{
			CurIndexX = GlobalValue::MapTileIndex_X - 1;
		}

		if (CurIndexY < 0)
		{
			CurIndexY = 0;
		}
		if (CurIndexY >= GlobalValue::MapTileIndex_Y)
		{
			CurIndexY = GlobalValue::MapTileIndex_Y - 1;
		}
	}

	GameMapInfo Temp = TileInfo[CurIndexY][CurIndexX];

	TileObjectOrder Result = Temp.MapInfo;
	return Result;
}

TileObjectOrder PlayLevel::GetCurTileType(int _X, int _Y)
{
	GameMapInfo Temp = TileInfo[_Y][_X];

	TileObjectOrder Result = Temp.MapInfo;
	return Result;
}

PlayerNum PlayLevel::GetCurTileMaster(const float4& _Pos)
{
	float4 CharacterPos = _Pos;
	CharacterPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
	float4 ChangeIndex = ObjectTile->PosToIndex(CharacterPos);

	int CurIndexX = ChangeIndex.iX() - 1;
	int CurIndexY = ChangeIndex.iY() - 1;

	for (const GameMapBubble& BubbleIter : AllBubbleDeathIndex)
	{
		if (CurIndexX == BubbleIter.Index.X && CurIndexY == BubbleIter.Index.Y && PlayerNum::P1 == BubbleIter.BubbleMaster)
		{
			return PlayerNum::P1;
		}
		else if (CurIndexX == BubbleIter.Index.X && CurIndexY == BubbleIter.Index.Y && PlayerNum::P2 == BubbleIter.BubbleMaster)
		{
			return PlayerNum::P2;
		}
	}

	return PlayerNum::None;
}

GameMapIndex PlayLevel::GetCurIndex(const float4& _Pos)
{
	float4 CharacterPos = _Pos;
	CharacterPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
	float4 ChangeIndex = ObjectTile->PosToIndex(CharacterPos);

	int CurIndexX = ChangeIndex.iX() - 1;
	int CurIndexY = ChangeIndex.iY() - 1;

	GameMapIndex Result = { CurIndexX, CurIndexY };

	return Result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 물폭탄
void PlayLevel::SetBubble(const float4& _Pos, int _BubblePower, const PlayerNum& _PlayerNum)
{
	if (nullptr != Player)
	{
		float4 CharacterPos = _Pos;
		CharacterPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
		float4 ChangeIndex = ObjectTile->PosToIndex(CharacterPos);

		int BubbleIndexX = ChangeIndex.iX() - 1;
		int BubbleIndexY = ChangeIndex.iY() - 1;

		GameEngineRenderer* BubbleRenderer = ObjectTile->GetTile(BubbleIndexX, BubbleIndexY);

		if (TileObjectOrder::Empty != TileInfo[BubbleIndexY][BubbleIndexX].MapInfo)
		{
			return;
		}

		if (PlayerNum::P1 == _PlayerNum)
		{
			Player->BombCountMinus();
		}
		else if (PlayerNum::P2 == _PlayerNum)
		{
			Player2->BombCountMinus();
		}
		else
		{
			MsgBoxAssert("폭탄을 설치하려는 플레이어가 1P인지 2P인지 알 수 없음");
			return;
		}


		AllBubbleIndex.push_back({ { BubbleIndexX, BubbleIndexY }, _PlayerNum });

		TileInfo[BubbleIndexY][BubbleIndexX].MapInfo = TileObjectOrder::Bubble;
		TileInfo[BubbleIndexY][BubbleIndexX].BubblePower = _BubblePower;

		BubbleRenderer = ObjectTile->SetTileToSprite(BubbleIndexX, BubbleIndexY, "Bubble.bmp",
			TileInfo[BubbleIndexY][BubbleIndexX].ObjectTextureInfo, GlobalValue::TileStartPos, true);

		if (nullptr == BubbleRenderer->FindAnimation("Bubble_Idle"))
		{
			BubbleRenderer->CreateAnimation("Bubble_Idle", "Bubble.bmp", 0, 2, 0.2f, true);
		}
		BubbleRenderer->ChangeAnimation("Bubble_Idle");

		EffectPlayer = GameEngineSound::SoundPlay("Bubble_Install.wav");
		EffectPlayer.SetVolume(2.0f);
		return;
	}

	MsgBoxAssert("Player가 nullptr입니다");
	return;
}

void PlayLevel::BubblePop(const int _X, const int _Y)
{
	PlayerNum PopBubbleMaster = PlayerNum::None;

	for (const GameMapBubble& BubbleIter : AllBubbleIndex)
	{
		if (_X == BubbleIter.Index.X && _Y == BubbleIter.Index.Y && PlayerNum::P1 == BubbleIter.BubbleMaster)
		{
			Player->BombCountPlus();
			PopBubbleMaster = PlayerNum::P1;
		}
		else if (_X == BubbleIter.Index.X && _Y == BubbleIter.Index.Y && PlayerNum::P2 == BubbleIter.BubbleMaster)
		{
			Player2->BombCountPlus();
			PopBubbleMaster = PlayerNum::P2;
		}
	}


	int BubblePower = TileInfo[_Y][_X].BubblePower;
	TileInfo[_Y][_X].Timer = 0.0f;
	TileInfo[_Y][_X].MapInfo = TileObjectOrder::PopRange;

	GameEngineRenderer* BubbleRenderer = ObjectTile->GetTile(_X, _Y);

	if (nullptr == BubbleRenderer)
	{
		return;
	}

	if (nullptr == BubbleRenderer->FindAnimation("Bubble_Pop"))
	{
		BubbleRenderer->CreateAnimation("Bubble_Pop", "Pop.bmp", 0, 5, 0.1f, false);
	}
	BubbleRenderer->ChangeAnimation("Bubble_Pop");

	AllBubbleDeathIndex.push_back({ { _X, _Y }, PopBubbleMaster });

	// 왼쪽 타일--------------------------------------------------------------
	for (int i = 1; i <= BubblePower; i++)
	{
		int X = _X - i;
		int Y = _Y;

		if (true == ObjectTile->IsOver(X, Y))
		{
			break;
		}

		if (TileObjectOrder::ImmovableBlock == TileInfo[Y][X].MapInfo
			|| TileObjectOrder::MovableBlock == TileInfo[Y][X].MapInfo)
		{
			PopTile(X, Y);
			break;
		}
		else if (TileObjectOrder::Structure == TileInfo[Y][X].MapInfo)
		{
			break;
		}
		else if (i == BubblePower)
		{
			SideBubblePop(X, Y, "Left_1.Bmp", "Bubble_Pop_Left", 0.05f, PopBubbleMaster);
		}
		else
		{
			SideBubblePop(X, Y, "Left_2.Bmp", "Bubble_Pop_Left_Middle", 0.05f, PopBubbleMaster);
		}

		CheckItemInTile(X, Y);
	}

	//오른쪽 타일--------------------------------------------------------------
	for (int i = 1; i <= BubblePower; i++)
	{
		int X = _X + i;
		int Y = _Y;

		if (true == ObjectTile->IsOver(X, Y))
		{
			break;
		}

		if (TileObjectOrder::ImmovableBlock == TileInfo[Y][X].MapInfo
			|| TileObjectOrder::MovableBlock == TileInfo[Y][X].MapInfo)
		{
			PopTile(X, Y);
			break;
		}
		else if (TileObjectOrder::Structure == TileInfo[Y][X].MapInfo)
		{
			break;
		}
		else if (i == BubblePower)
		{
			SideBubblePop(X, Y, "Right_1.Bmp", "Bubble_Pop_Right", 0.05f, PopBubbleMaster);
		}
		else
		{
			SideBubblePop(X, Y, "Right_2.Bmp", "Bubble_Pop_Right_Middle", 0.05f, PopBubbleMaster);
		}

		CheckItemInTile(X, Y);
	}

	//위쪽 타일--------------------------------------------------------------
	for (int i = 1; i <= BubblePower; i++)
	{
		int X = _X;
		int Y = _Y - i;

		if (true == ObjectTile->IsOver(X, Y))
		{
			break;
		}

		if (TileObjectOrder::ImmovableBlock == TileInfo[Y][X].MapInfo
			|| TileObjectOrder::MovableBlock == TileInfo[Y][X].MapInfo)
		{
			PopTile(X, Y);
			break;
		}
		else if (TileObjectOrder::Structure == TileInfo[Y][X].MapInfo)
		{
			break;
		}
		else if (i == BubblePower)
		{
			SideBubblePop(X, Y, "Up_1.Bmp", "Bubble_Pop_Up", 0.05f, PopBubbleMaster);
		}
		else
		{
			SideBubblePop(X, Y, "Up_2.Bmp", "Bubble_Pop_Up_Middle", 0.05f, PopBubbleMaster);
		}

		CheckItemInTile(X, Y);
	}

	//아래쪽 타일--------------------------------------------------------------
	for (int i = 1; i <= BubblePower; i++)
	{
		int X = _X;
		int Y = _Y + i;

		if (true == ObjectTile->IsOver(X, Y))
		{
			break;
		}

		if (TileObjectOrder::ImmovableBlock == TileInfo[Y][X].MapInfo
			|| TileObjectOrder::MovableBlock == TileInfo[Y][X].MapInfo)
		{
			PopTile(X, Y);
			break;
		}
		else if (TileObjectOrder::Structure == TileInfo[Y][X].MapInfo)
		{
			break;
		}
		else if (i == BubblePower)
		{
			SideBubblePop(X, Y, "Down_1.Bmp", "Bubble_Pop_Down", 0.05f, PopBubbleMaster);
		}
		else
		{
			SideBubblePop(X, Y, "Down_2.Bmp", "Bubble_Pop_Down_Middle", 0.05f, PopBubbleMaster);
		}

		CheckItemInTile(X, Y);
	}
	BubblePopPlay();
}

void PlayLevel::SideBubblePop(const int _X, const int _Y, const std::string& _SpriteName, const std::string& _AnimationName, float _Inter, PlayerNum _PopBubbleMaster)
{
	int DownIndexX = _X;
	int DownIndexY = _Y;

	if (false == ObjectTile->IsOver(DownIndexX, DownIndexY))
	{
		if (TileInfo[DownIndexY][DownIndexX].MapInfo == TileObjectOrder::Bubble)
		{
			PrevBubblePop(DownIndexX, DownIndexY);
		}
		else
		{
			TileChange(DownIndexX, DownIndexY, _SpriteName, _AnimationName, _Inter, _PopBubbleMaster);
		}
	}
}

void PlayLevel::PrevBubblePop(const int _X, const int _Y)
{
	BubblePop(_X, _Y);
	TileInfo[_Y][_X].PrevPop = true;
}

// 블록이 물풍선에 맞을 경우 터지는 함수
void PlayLevel::PopTile(const int _X, const int _Y)
{
	GameEngineRenderer* TileRenderer = ObjectTile->GetTile(_X, _Y);

	if (nullptr == TileRenderer->FindAnimation("Pop_Tile"))
	{
		TileRenderer->CreateAnimation("Pop_Tile", "Pop_Tile.Bmp", 0, 3, 0.1f, false);
	}

	TileRenderer->ChangeAnimation("Pop_Tile");

	AllBubbleDeathIndex.push_back({ _X, _Y });
	
	if (nullptr != Items[_Y][_X])
	{
		Items[_Y][_X]->OutItemInBlock();
	}
}

// 물풍선 상하좌우 타일 변경 함수
void PlayLevel::TileChange(const int _X, const int _Y, const std::string& _SpriteName, const std::string& _AnimationName, float _Inter, PlayerNum _PopBubbleMaster)
{
	if (TileObjectOrder::Empty == TileInfo[_Y][_X].MapInfo
		|| TileObjectOrder::PopRange == TileInfo[_Y][_X].MapInfo)
	{
		GameEngineRenderer* TileRenderer = ObjectTile->GetTile(_X, _Y);

		TileInfo[_Y][_X].MapInfo = TileObjectOrder::PopRange;

		TileRenderer = ObjectTile->SetTileToSprite(_X, _Y, _SpriteName,
			TileInfo[_Y][_X].ObjectTextureInfo, GlobalValue::TileStartPos, true);

		if (nullptr == TileRenderer->FindAnimation(_AnimationName))
		{
			TileRenderer->CreateAnimation(_AnimationName, _SpriteName, -1, -1, _Inter, false);
		}
		TileRenderer->ChangeAnimation(_AnimationName);

		AllBubbleDeathIndex.push_back({ { _X, _Y }, _PopBubbleMaster });
	}

	return;
}


/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */
// UI


void PlayLevel::UILevelStart()
{
	FadeObject::CallFadeIn(this, GlobalValue::g_ChangeLevelFadeSpeed);

	vecCharacterState.resize(GlobalValue::g_ActiveRoomCount);

	if (-1 != CurrentStage)
	{
		CreateGameStartAnimation();
		CreateBossImage();
		CreatePortrait();
		CreateGameResult();
	}

	if (m_FadeScreen)
	{
		m_FadeScreen->On();
	}

	if (m_PlayTimer)
	{
		m_PlayTimer->setTimer(CONST_TimeSetting);
		m_PlayTimer->stopTimer();
	}
}

void PlayLevel::CreateGameStartAnimation()
{
	m_GameStartAnimation = CreateActor<GameStartAnimation>(UpdateOrder::UI);
	if (nullptr == m_GameStartAnimation)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_GameStartAnimation->initStartAnimation(CurrentStage);
	m_GameStartAnimation->setGameStartCallBack(this, &PlayLevel::setGameStartCallBack);

	if (CurrentStage == 1)
	{
		EffectPlayer = GameEngineSound::SoundPlay("Game_Start.wav");
		EffectPlayer.SetVolume(0.7f);
	}

	if (CurrentStage >= 2 && CurrentStage <= 3)
	{
		m_GameStartAnimation->Off();
	}
}

void PlayLevel::OnGameStartAnimation()
{
	if (m_GameStartAnimation)
	{
		m_GameStartAnimation->On();
	}


	EffectPlayer = GameEngineSound::SoundPlay("Next_Level_Ready.wav");
	EffectPlayer.SetVolume(0.5f);
}

void PlayLevel::CreateBossImage()
{
	if (1 != CurrentStage)
	{
		StageStartBossBillBoard* BossBillbaord = CreateActor<StageStartBossBillBoard>(UpdateOrder::UI);
		if (nullptr == BossBillbaord)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		BossBillbaord->setCallbackStage<PlayLevel>(this, &PlayLevel::OnGameStartAnimation);
	}
}

void PlayLevel::setGameStartCallBack()
{
	if (m_FadeScreen)
	{
		m_FadeScreen->Off();
	}

	if (m_PlayTimer)
	{
		m_PlayTimer->flowTimer();
	}

	GameStartCheckValue = true;
}

void PlayLevel::CreatePortrait()
{
	vec_PlayPortrait.resize(static_cast<int>(GlobalValue::g_ActiveRoomCount));

	for (int RoomCount = 0; RoomCount < GlobalValue::g_ActiveRoomCount; RoomCount++)
	{
		PlayPortrait* PlayPortraitPtr = CreateActor<PlayPortrait>(UpdateOrder::UI);
		if (nullptr == PlayPortraitPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		float4 PortraitPos = CONST_PlayPortraitStartPos + float4::DOWN +
			float4{ CONST_PlayPortraitNextPos.X , CONST_PlayPortraitNextPos.Y * static_cast<float>(RoomCount) };

		PlayPortraitPtr->SetPos(PortraitPos);
		PlayPortraitPtr->CreatePlayPortrait(RoomCount);

		vec_PlayPortrait[RoomCount] = PlayPortraitPtr;
	}
}

void PlayLevel::CreateGameResult()
{
	SetUpResultWindow();
}

void PlayLevel::SetUpResultWindow()
{
	m_ResultWindow = CreateActor<PlayResultWindow>(UpdateOrder::UI);
	if (nullptr == m_ResultWindow)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_ResultWindow->SetPos(CONST_ResultWindowStartPos);
	m_ResultWindow->initResultWindow();

	VecPlayerResult.resize(GlobalValue::g_ActiveRoomCount);
}

void PlayLevel::SetUpResultBoardAnimation()
{
	GameOverAnimationPtr = CreateActor<GameOverAnimation>(UpdateOrder::UI);
	if (nullptr == GameOverAnimationPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	GameOverAnimationPtr->initStageResultAnimation(CurrentStage, WinCheckValue);
}


void PlayLevel::CreateUIElements()
{
	if (CurrentStage < 1 || CurrentStage > 3)
	{
		MsgBoxAssert("CurrentStage로 스테이지 UI를 만들 수 없습니다.");
		return;
	}

	SetUpUIStart();
}

void PlayLevel::BubblePopPlay()
{
	// 물풍선 터지는 효과음 중첩 방지
	if (false == PlayBubblePopEffectSound)
	{
		PlayBubblePopEffectSound = true;
		EffectPlayer = GameEngineSound::SoundPlay("Bubble_Pop.wav");
		EffectPlayer.SetVolume(2.0f);
	}
}

void PlayLevel::SetUpUIStart()
{
	SetUpStageInfo();
	SetUpFadeScreen();
	SetUpTimer();
	SetGoBackButton();
}

void PlayLevel::SetUpStageInfo()
{
	m_StageInfo = CreateActor<CommonTexture>(UpdateOrder::UI);
	if (nullptr == m_StageInfo)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_StageInfo->loadTexture("PenguinLevelStageInfo.bmp", "Resources\\Textures\\UI\\PlayStage");
	m_StageInfo->setTexture("PenguinLevelStageInfo.bmp");
	m_StageInfo->setRendererCopyAndRenderScale(0, 2);

	float4 StageInfoScale = m_StageInfo->getScale();
	float4 StageInfoRenderPos = float4{ 0.0f , StageInfoScale.Y * static_cast<float>(CurrentStage - 1) };
	m_StageInfo->setRendererCopyPos(0, CurrentStage - 1);

	float4 StageRenderPos = CONST_StageInfoStartPos + StageInfoScale.Half();
	m_StageInfo->SetPos(StageRenderPos);
}

void PlayLevel::SetUpFadeScreen()
{
	m_FadeScreen = CreateActor<FadeScreen>(UpdateOrder::UI);
	if (nullptr == m_FadeScreen)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	float4 WinScale = GlobalValue::WinScale;

	m_FadeScreen->setRenderScale(WinScale);
	m_FadeScreen->setAlpha(GlobalValue::g_FadeScreenAlphaValue);
	m_FadeScreen->SetPos(WinScale.Half());
	m_FadeScreen->Off();
}

void PlayLevel::SetUpTimer()
{
	m_PlayTimer = CreateActor<PlayTimer>(UpdateOrder::UI);
	if (nullptr == m_PlayTimer)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_PlayTimer->SetPos(CONST_TimerLocation);
}

void PlayLevel::SetGoBackButton()
{
	m_GoBackButton = CreateActor<Button>(UpdateOrder::UI);
	if (nullptr == m_GoBackButton)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	m_GoBackButton->setRenderer(RenderOrder::FirstElementUI);
	m_GoBackButton->setButtonTexture(ButtonState::Normal, "Play_Button_Exit_Normal.bmp", "Resources\\Textures\\UI\\PlayStage", 1, 1);
	m_GoBackButton->setButtonTexture(ButtonState::Hover, "Play_Button_Exit_Hover.bmp", "Resources\\Textures\\UI\\PlayStage", 1, 2);
	m_GoBackButton->setButtonTexture(ButtonState::Click, "Play_Button_Exit_Click.bmp", "Resources\\Textures\\UI\\PlayStage", 1, 1);
	m_GoBackButton->setCallback<PlayLevel>(ButtonEventState::Click, this, &PlayLevel::clickGoBackButton);
	m_GoBackButton->setButtonSound(ButtonEventState::Hover, "Game_Exit_Button_Hover.wav", "Resources\\Sounds\\GamePlay");

	float4 ButtonScale = m_GoBackButton->getButtonScale();
	float4 ButtonPos = CONST_GoBackButtonStartPos + ButtonScale.Half();

	m_GoBackButton->SetPos(ButtonPos);
}

void PlayLevel::clickGoBackButton()
{
	FadeObject::CallFadeOut(this, "RoomLevel", GlobalValue::g_ChangeLevelFadeSpeed);
}


void PlayLevel::StartGameOver()
{
	if (nullptr == m_ResultWindow)
	{
		MsgBoxAssert("액터를 생성하지 않았습니다.");
		return;
	}

	// Kill 수, Save 수 입력--------------------------------------
	VecPlayerResult[0].KillNUmber = Player->GetKillCount();
	VecPlayerResult[0].SaveNUmber = Player->GetSaveCount();

	if (nullptr != Player2)
	{
		VecPlayerResult[1].KillNUmber = Player2->GetKillCount();
		VecPlayerResult[1].SaveNUmber = Player2->GetSaveCount();
	}
	//------------------------------------------------------------

	m_ResultWindow->OnResultWindow(VecPlayerResult);

	SetUpResultBoardAnimation();


	static bool WinOrLoseSoundLoadValue = false;

	if (false == WinOrLoseSoundLoadValue)
	{
		GlobalUtils::SoundFileLoad("Lose.wav", "Resources\\Sounds\\GamePlay");
		GlobalUtils::SoundFileLoad("Win.wav", "Resources\\Sounds\\GamePlay");

		WinOrLoseSoundLoadValue = true;
	}

	WinCheckValue ? EffectPlayer = GameEngineSound::SoundPlay("Win.wav") : EffectPlayer = GameEngineSound::SoundPlay("Lose.wav");
	EffectPlayer.SetVolume(1.0f);
	GameOverCheckValue = true;

	BGMPlayer.Stop();
}

void PlayLevel::updateGameOverResult(float _Delta)
{
	if (true == GameOverCheckValue)
	{
		GameOverTime += _Delta;

		if (GameOverTime > GameOverDuration)
		{
			GameOverTime = 0.0f;

			std::string MoveLevel = WinCheckValue ? NextLevelName : "RoomLevel";
			GameEngineCore::ChangeLevel(MoveLevel);
		}
	}
}


void PlayLevel::updateVictoryRoll()
{
	if (-1 != CurrentStage && false == GameOverCheckValue)
	{
		if (nullptr == Player)
		{
			return;
		}

		if (true == detectAllMonsterKill())
		{
			return;
		}

		// 플레이어가 전부 사망했을때 Lose를 띄웁니다.
		if (1 == GlobalValue::g_ActiveRoomCount)
		{
			if ((false == m_PlayTimer->getTimeFlowValue() && true == GameStartCheckValue) || true == Player->GetPlayerDeath())
			{
				WinCheckValue = false;
	
				StartGameOver();
				return;
			}
		}
		else
		{
			if (Player2)
			{
				if ((false == m_PlayTimer->getTimeFlowValue() && true == GameStartCheckValue) || 
					true == Player->GetPlayerDeath() && true == Player2->GetPlayerDeath())
				{
					WinCheckValue = false;

					StartGameOver();
					return;
				}
			}
		}

		// 승리 숏컷
		if (true == GameEngineInput::IsPress('6'))
		{
			for (int PlayerCount = 0; PlayerCount < GlobalValue::g_ActiveRoomCount; PlayerCount++)
			{
				VecPlayerResult[PlayerCount].PlayerWinValue = true;
			}

			WinCheckValue = true;

			StartGameOver();
			return;
		}
	}
}

bool PlayLevel::detectAllMonsterKill()
{
	if (CurrentStage >= 1 && CurrentStage <= 2)
	{
		if (0 == StageMonsters.size())
		{
			WinCheckValue = true;

			// 승리 시 플레이어 점프 상태 변경
			if (Player != nullptr && Player->State != CharacterState::Die)
			{
				Player->ChangeState(CharacterState::Jump);
			}

			if (Player2 != nullptr && Player2->State != CharacterState::Die)
			{
				Player2->ChangeState(CharacterState::Jump);
			}

			StartGameOver();

			return true;
		}
	}
	else if (3 == CurrentStage)
	{
		// 3 스테이지에서는 펭귄 보스가 죽으면 승리하게 됩니다.

		if (nullptr != Penguin::BossMonster && MonsterState::Die == Penguin::BossMonster->GetState())
		{
			StageMonstersDeath();

			WinCheckValue = true;

			// 승리 시 플레이어 점프 상태 변경
			if (Player != nullptr && Player->State != CharacterState::Die)
			{
				Player->ChangeState(CharacterState::Jump);
			}

			if (Player2 != nullptr && Player2->State != CharacterState::Die)
			{
				Player2->ChangeState(CharacterState::Jump);
			}

			StartGameOver();

			return true;
		}
	}

	return false;
}

void PlayLevel::updateCharacterPortrait()
{
	if (CurrentStage < 1 || CurrentStage > 3)
	{
		return;
	}
	
	if (nullptr == Player)
	{
		return;
	}

	// 플레이어가 죽었는데 초상화가 업데이트 되지 않았다면 초상화를 바꿔줍니다.
	if (Player->GetPlayerDeath() && true == vecCharacterState[0].AliveState)
	{
		PlayPortrait* Portrait = vec_PlayPortrait[0];
		if (nullptr == Portrait)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		PlayCharacterPortrait* CharacterPortrait = Portrait->getPortrait();
		if (nullptr == CharacterPortrait)
		{
			MsgBoxAssert("생성되지 않은 액터를 참조하려고 했습니다.");
			return;
		}

		CharacterPortrait->changeState(PlayPortraitState::Lose);

		vecCharacterState[0].AliveState = false;
	}

	if (nullptr == Player2)
	{
		return;
	}


	// 플레이어가 죽었는데 초상화가 업데이트 되지 않았다면 초상화를 바꿔줍니다.
	if (Player2->GetPlayerDeath() && true == vecCharacterState[1].AliveState)
	{
		PlayPortrait* Portrait = vec_PlayPortrait[1];
		if (nullptr == Portrait)
		{
			MsgBoxAssert("액터를 불러오지 못했습니다.");
			return;
		}

		PlayCharacterPortrait* CharacterPortrait = Portrait->getPortrait();
		if (nullptr == CharacterPortrait)
		{
			MsgBoxAssert("생성되지 않은 액터를 참조하려고 했습니다.");
			return;
		}

		CharacterPortrait->changeState(PlayPortraitState::Lose);

		vecCharacterState[1].AliveState = false;
	}
}


void PlayLevel::UILevelEnd()
{
	if (-1 != CurrentStage)
	{
		ReleaseLevelComposition();
		ReleaseResultWindow();
	}

	if (nullptr != GameOverAnimationPtr)
	{
		GameOverAnimationPtr->Death();
		GameOverAnimationPtr = nullptr;
	}

	GameOverCheckValue = false;
	GameStartCheckValue = false;

	vecCharacterState.clear();
	VecPlayerResult.clear();
}

void PlayLevel::ReleaseLevelComposition()
{
	for (int VecCount = 0; VecCount < vec_PlayPortrait.size(); VecCount++)
	{
		PlayPortrait* PlayPortraitPtr = vec_PlayPortrait[VecCount];
		if (PlayPortraitPtr)
		{
			PlayPortraitPtr->ActorRelease();
		}
	}

	vec_PlayPortrait.clear();
}

void PlayLevel::ReleaseResultWindow()
{
	if (m_ResultWindow)
	{
		m_ResultWindow->ActorRelease();
		m_ResultWindow = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 몬스터
bool PlayLevel::MonsterCheckTile(const float4& _Pos, float _Delta)
{
	float4 CheckPos = { _Pos.X, _Pos.Y };
	CheckPos += GlobalValue::MapTileSize - GlobalValue::TileStartPos;
	float4 CheckIndex = ObjectTile->PosToIndex(CheckPos);

	int CheckX = CheckIndex.iX() - 1;
	int CheckY = CheckIndex.iY() - 1;

	GameEngineRenderer* NextTile = ObjectTile->GetTile(CheckX, CheckY);

	if (true == ObjectTile->IsOver(CheckX, CheckY))
	{
		return true;
	}
	else
	{
		if (TileObjectOrder::Empty == TileInfo[CheckY][CheckX].MapInfo)
		{
			return false;
		}

		if (TileObjectOrder::Structure == TileInfo[CheckY][CheckX].MapInfo)
		{
			return true;
		}

		if (TileObjectOrder::ImmovableBlock == TileInfo[CheckY][CheckX].MapInfo)
		{
			return true;
		}

		if (TileObjectOrder::MovableBlock == TileInfo[CheckY][CheckX].MapInfo)
		{
			return true;
		}

		if (TileObjectOrder::Bubble == TileInfo[CheckY][CheckX].MapInfo)
		{
			return true;
		}

		return false;
	}
}

void PlayLevel::StageMonstersDeath()
{
	std::list<BaseMonster*>::iterator StartIter = StageMonsters.begin();
	std::list<BaseMonster*>::iterator EndIter = StageMonsters.end();

	for (; StartIter != EndIter;)
	{
		BaseMonster* CurMonster = *StartIter;

		CurMonster->DeathSoundOff();
		CurMonster->SetState(MonsterState::Die);

		StartIter = StageMonsters.erase(StartIter);
	}
}

void PlayLevel::MonsterListDelete()
{
	std::list<BaseMonster*>::iterator StartIter = StageMonsters.begin();
	std::list<BaseMonster*>::iterator EndIter = StageMonsters.end();

	for (; StartIter != EndIter;)
	{
		BaseMonster* CurMonster = *StartIter;

		if (CurMonster->IsDeath() == true)
		{
			StartIter = StageMonsters.erase(StartIter);
		}
		else
		{
			++StartIter;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 보스 맵 패턴
void PlayLevel::BubblePattern(int BossIndex_X, int BossIndex_Y, const int _Range)
{
	if (nullptr == BossBubbleTile)
	{
		BossBubbleTile = CreateActor<TileMap>();
		if (nullptr == BossBubbleTile)
		{
			MsgBoxAssert("타일을 생성에 실패하였습니다.");
			return;
		}

		BossBubbleTile->CreateTileMap("Boss_Pop.bmp", GlobalValue::MapTileIndex_X, GlobalValue::MapTileIndex_Y, GlobalValue::MapTileSize, RenderOrder::MapObject);
	}

	for (int Y = BossIndex_Y - _Range; Y <= BossIndex_Y + _Range; Y++)
	{
		for (int X = BossIndex_X - _Range; X <= BossIndex_X + _Range; X++)
		{
			if (BossBubbleTile->IsOver(X, Y))
			{
				continue;
			}

			if (X != BossIndex_X - _Range && X != BossIndex_X + _Range && Y != BossIndex_Y - _Range && Y != BossIndex_Y + _Range)
			{
				continue;
			}

			GameEngineRenderer* PopRenderer = nullptr;
			if (TileObjectOrder::Bubble == TileInfo[Y][X].MapInfo)
			{
				PrevBubblePop(X, Y);
			}
			else if (TileObjectOrder::ImmovableBlock == TileInfo[Y][X].MapInfo || TileObjectOrder::MovableBlock == TileInfo[Y][X].MapInfo)
			{
				PopTile(X, Y);
			}
			else if (TileObjectOrder::Empty == CurPlayLevel->TileInfo[Y][X].MapInfo || TileObjectOrder::PopRange == CurPlayLevel->TileInfo[Y][X].MapInfo)
			{
				CurPlayLevel->TileInfo[Y][X].MapInfo = TileObjectOrder::PopRange;
				PopRenderer = CurPlayLevel->BossBubbleTile->GetTile(X, Y);
				CheckItemInTile(X, Y);
			}
			else
			{
				continue;
			}


			if (nullptr == PopRenderer)
			{
				PopRenderer = CurPlayLevel->BossBubbleTile->SetTile(X, Y, 0, GlobalValue::TileStartPos, true);
			}

			if (nullptr == PopRenderer->FindAnimation("Boss_Pop"))
			{
				PopRenderer->CreateAnimation("Boss_Pop", "Boss_Pop.bmp", 0, 4, 0.1f);	
			}
			PopRenderer->ChangeAnimation("Boss_Pop");
		}
	}

	EffectPlayer = GameEngineSound::SoundPlay("Bubble_Pop.wav");
	EffectPlayer.SetVolume(1.5f);
}

void PlayLevel::ClearBossPattern()
{
	if (nullptr == BossBubbleTile)
	{
		return;
	}

	for (int Y = 0; Y < BossBubbleTile->GetTileSize().iY(); Y++)
	{
		for (int X = 0; X < BossBubbleTile->GetTileSize().iX(); X++)
		{
			GameEngineRenderer* PopRenderer = CurPlayLevel->BossBubbleTile->GetTile(X, Y);

			if (nullptr == PopRenderer)
			{
				continue;
			}
			All_Null = false;

			if (true == PopRenderer->IsAnimationEnd())
			{
				CurPlayLevel->TileInfo[Y][X].MapInfo = TileObjectOrder::Empty;
				BossBubbleTile->DeathTile(X, Y);
				PatternAnimationEnd = true;
			}
		}
	}

	if (true == All_Null)
	{
		PatternAnimationEnd = true;
	}
	All_Null = true;
}

void PlayLevel::SoketRelease()
{
	for (int i = 0; i < Sokets.size(); i++)
	{
		if (nullptr != Sokets[i])
		{
			Sokets[i]->Death();
			Sokets[i] = nullptr;
		}
	}
	Sokets.clear();
}