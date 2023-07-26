#pragma once
#include "PlayLevel.h"

class Stage : public PlayLevel
{
public:
	// Constructor Destructor
	Stage();
	~Stage();

	// Delete Function
	Stage(const Stage& _Other) = delete;
	Stage(Stage&& _Other) noexcept = delete;
	Stage& operator=(const Stage& _Other) = delete;
	Stage& operator=(Stage&& _Other) noexcept = delete;

protected:

private:

};