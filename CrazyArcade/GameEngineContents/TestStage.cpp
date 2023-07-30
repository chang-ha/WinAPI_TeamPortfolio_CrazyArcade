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
	// MapInfo는 타일 위 오브젝트의 종류룰 저장하고 있습니다.
	// MapInfo를 아래와 같이 바꿔서 배치하고 조건 처리에 사용할 수 있습니다.
	{
		for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; ++Y)
		{
			for (int X = 0; X < GlobalValue::MapTileIndex_X; ++X)
			{
				TileInfo[Y][X].GroundTextureInfo = 0;
			}
		}

		// 구조물
		TileInfo[0][0].MapInfo = TileObjectOrder::Structure;
		TileInfo[0][0].ObjectTextureInfo = 1;

		TileInfo[2][0].MapInfo = TileObjectOrder::Structure;
		TileInfo[2][0].ObjectTextureInfo = 2;

		TileInfo[2][1].MapInfo = TileObjectOrder::Structure;
		TileInfo[2][1].ObjectTextureInfo = 3;

		TileInfo[5][2].MapInfo = TileObjectOrder::Structure;
		TileInfo[5][2].ObjectTextureInfo = 0;


		// 밀지 못하는 블록
		TileInfo[5][5].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[5][5].ObjectTextureInfo = 0;

		TileInfo[5][8].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[5][8].ObjectTextureInfo = 1;

		TileInfo[5][11].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[5][11].ObjectTextureInfo = 0;


		// 밀 수 있는 블록
		TileInfo[6][5].MapInfo = TileObjectOrder::MovableBlock;
		TileInfo[6][5].ObjectTextureInfo = 0;

		TileInfo[3][8].MapInfo = TileObjectOrder::MovableBlock;
		TileInfo[3][8].ObjectTextureInfo = 0;
	}

	TileSetting();
}

void TestStage::Update(float _Delta)
{
	PlayLevel::Update(_Delta);
}

void TestStage::Render(float _Delta)
{
	PlayLevel::Render(_Delta);
}