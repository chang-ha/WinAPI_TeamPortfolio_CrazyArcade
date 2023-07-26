#include "TestStage.h"

#include "GlobalValue.h"
#include "GameMapInfo.h"

TestStage::TestStage()
{
}

TestStage::~TestStage()
{
}

void TestStage::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void TestStage::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TestStage::Start()
{
	PlayLevel::Start();

	// 더미 타일 정보 : 임시 정보로 추후 파일로 로드하여 사용할 것임
	{
		// 구조물
		TileInfo[0][0].MapInfo = TileObjectOrder::Structure;;
		TileInfo[0][0].TileObjectTextureInfo = 1;

		TileInfo[2][0].MapInfo = TileObjectOrder::Structure;;
		TileInfo[2][0].TileObjectTextureInfo = 2;

		TileInfo[2][1].MapInfo = TileObjectOrder::Structure;;
		TileInfo[2][1].TileObjectTextureInfo = 3;

		TileInfo[5][2].MapInfo = TileObjectOrder::Structure;;
		TileInfo[5][2].TileObjectTextureInfo = 0;


		// 밀지 못하는 블록
		TileInfo[5][5].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[5][5].TileObjectTextureInfo = 0;

		TileInfo[5][8].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[5][8].TileObjectTextureInfo = 1;

		TileInfo[5][11].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[5][11].TileObjectTextureInfo = 0;


		// 밀 수 있는 블록
		TileInfo[6][5].MapInfo = TileObjectOrder::MovableBlock;
		TileInfo[6][5].TileObjectTextureInfo = 0;
	}

	TileSetting();
}

void TestStage::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void TestStage::Render(float _Delta)
{

}