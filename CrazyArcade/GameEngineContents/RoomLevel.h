#pragma once
#include "ContentLevel.h"

#include <vector>


class Button;
class RoomLevel : public ContentLevel
{
public:
	// constructer destructer
	RoomLevel();
	~RoomLevel();

	// delete function
	RoomLevel(const RoomLevel& _Ohter) = delete;
	RoomLevel(RoomLevel&& _Ohter) noexcept = delete;
	RoomLevel& operator=(const RoomLevel& _Other) = delete;
	RoomLevel& operator=(RoomLevel&& _Other) noexcept = delete;

protected:

private:
	// GameEngineObject ���
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// GameEngineLevel ���
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


};

