#pragma once

enum class CharacterState
{
	Idle,
	Move,
	Ready,
	FlashLong,
	FlashShort,
	Bubble,
	Live,
	Die,
	Jump,
	Max
};

enum class ActorDir
{
	Left,
	Right,
	Up,
	Down,
};