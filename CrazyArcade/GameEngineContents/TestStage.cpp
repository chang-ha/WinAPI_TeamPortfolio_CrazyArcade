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
				TileInfo[Y][X].GroundTextureInfo = 4;
			}
		}

		// 구조물
		TileInfo[2][0].MapInfo = TileObjectOrder::Structure;
		TileInfo[2][0].ObjectTextureInfo = 1;

		TileInfo[4][0].MapInfo = TileObjectOrder::Structure;
		TileInfo[4][0].ObjectTextureInfo = 1;

		TileInfo[5][1].MapInfo = TileObjectOrder::Structure;
		TileInfo[5][1].ObjectTextureInfo = 2;

		TileInfo[6][2].MapInfo = TileObjectOrder::Structure;
		TileInfo[6][2].ObjectTextureInfo = 3;


		// 밀지 못하는 블록
		TileInfo[2][3].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[2][3].ObjectTextureInfo = 1;

		TileInfo[2][9].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[2][9].ObjectTextureInfo = 2;

		TileInfo[1][9].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[1][9].ObjectTextureInfo = 2;

		TileInfo[2][12].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[2][12].ObjectTextureInfo = 3;


		// 밀 수 있는 블록
		TileInfo[2][6].MapInfo = TileObjectOrder::MovableBlock;
		TileInfo[2][6].ObjectTextureInfo = 1;

		TileInfo[8][8].MapInfo = TileObjectOrder::MovableBlock;
		TileInfo[8][8].ObjectTextureInfo = 2;

		TileInfo[8][9].MapInfo = TileObjectOrder::MovableBlock;
		TileInfo[8][9].ObjectTextureInfo = 2;

		TileInfo[8][10].MapInfo = TileObjectOrder::MovableBlock;
		TileInfo[8][10].ObjectTextureInfo = 2;
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