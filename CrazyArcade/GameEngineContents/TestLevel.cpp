#include "TestLevel.h"
#include "TestActor.h"
TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}

void TestLevel::LevelStart(GameEngineLevel* _PrevLevel) 
{

}

void TestLevel::LevelEnd(GameEngineLevel* _NextLevel) 
{

}

void TestLevel::Start() 
{
	GameEngineActor* BackGround = CreateActor<TestActor>();
}

void TestLevel::Update(float _Delta) 
{

}

void TestLevel::Release()
{

}