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

	// ���� Ÿ�� ���� : �ӽ� ������ ���� ���Ϸ� �ε��Ͽ� ����� ����
	// MapInfo�� Ÿ�� �� ������Ʈ�� ������ �����ϰ� �ֽ��ϴ�.
	// MapInfo�� �Ʒ��� ���� �ٲ㼭 ��ġ�ϰ� ���� ó���� ����� �� �ֽ��ϴ�.
	{
		for (int Y = 0; Y < GlobalValue::MapTileIndex_Y; ++Y)
		{
			for (int X = 0; X < GlobalValue::MapTileIndex_X; ++X)
			{
				TileInfo[Y][X].GroundTextureInfo = 0;
			}
		}

		// ������
		TileInfo[0][0].MapInfo = TileObjectOrder::Structure;
		TileInfo[0][0].ObjectTextureInfo = 1;

		TileInfo[2][0].MapInfo = TileObjectOrder::Structure;
		TileInfo[2][0].ObjectTextureInfo = 2;

		TileInfo[2][1].MapInfo = TileObjectOrder::Structure;
		TileInfo[2][1].ObjectTextureInfo = 3;

		TileInfo[5][2].MapInfo = TileObjectOrder::Structure;
		TileInfo[5][2].ObjectTextureInfo = 0;


		// ���� ���ϴ� ���
		TileInfo[5][5].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[5][5].ObjectTextureInfo = 0;

		TileInfo[5][8].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[5][8].ObjectTextureInfo = 1;

		TileInfo[5][11].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[5][11].ObjectTextureInfo = 0;


		// �� �� �ִ� ���
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