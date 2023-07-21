#pragma once

enum class CharacterState
{
	Wait,
	Move,
	Ready,
	FlashLong,
	FlashShort,
	Trap,
	Live,
	Die,
	Jump
};

enum class ActorDir
{
	Left,
	Right,
	Up,
	Down,
};