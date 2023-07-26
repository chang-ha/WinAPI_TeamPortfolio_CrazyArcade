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
	{
		// ������
		TileInfo[0][0].MapInfo = TileObjectOrder::Structure;;
		TileInfo[0][0].TileObjectTextureInfo = 1;

		TileInfo[2][0].MapInfo = TileObjectOrder::Structure;;
		TileInfo[2][0].TileObjectTextureInfo = 2;

		TileInfo[2][1].MapInfo = TileObjectOrder::Structure;;
		TileInfo[2][1].TileObjectTextureInfo = 3;

		TileInfo[5][2].MapInfo = TileObjectOrder::Structure;;
		TileInfo[5][2].TileObjectTextureInfo = 0;


		// ���� ���ϴ� ���
		TileInfo[5][5].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[5][5].TileObjectTextureInfo = 0;

		TileInfo[5][8].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[5][8].TileObjectTextureInfo = 1;

		TileInfo[5][11].MapInfo = TileObjectOrder::ImmovableBlock;
		TileInfo[5][11].TileObjectTextureInfo = 0;


		// �� �� �ִ� ���
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