#include "DummyStage.h"

#include "GlobalValue.h"
#include "GameMapInfo.h"

DummyStage::DummyStage()
{
}

DummyStage::~DummyStage()
{
}

void DummyStage::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void DummyStage::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void DummyStage::Start()
{
	PlayLevel::Start();

	// 더미 타일 정보
	{
		// 구조물
		{
			TileInfo[0][0].MapInfo = TileObjectOrder::Structure;;
			TileInfo[0][0].TileObjectTextureInfo = 1;

			TileInfo[2][0].MapInfo = TileObjectOrder::Structure;;
			TileInfo[2][0].TileObjectTextureInfo = 2;

			TileInfo[2][1].MapInfo = TileObjectOrder::Structure;;
			TileInfo[2][1].TileObjectTextureInfo = 3;

			TileInfo[5][2].MapInfo = TileObjectOrder::Structure;;
			TileInfo[5][2].TileObjectTextureInfo = 0;

		}

		// 밀지 못하는 블록
		{
			TileInfo[5][5].MapInfo = TileObjectOrder::ImmovableBlock;
			TileInfo[5][5].TileObjectTextureInfo = 0;

			TileInfo[5][8].MapInfo = TileObjectOrder::ImmovableBlock;
			TileInfo[5][8].TileObjectTextureInfo = 1;

			TileInfo[5][11].MapInfo = TileObjectOrder::ImmovableBlock;
			TileInfo[5][11].TileObjectTextureInfo = 0;
		}

		// 밀 수 있는 블록
		{
			TileInfo[6][5].MapInfo = TileObjectOrder::MovableBlock;
			TileInfo[6][5].TileObjectTextureInfo = 0;
		}
	}
	TileSetting();
}

void DummyStage::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void DummyStage::Render(float _Delta)
{

}