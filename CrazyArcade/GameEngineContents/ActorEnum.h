#pragma once

enum class CharacterState
{
	Idle,
	Move,
	Ready,
	FlashLong,
	FlashShort,
	BubbleHit,
	Bubble,
	BubbleEnd,
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

enum class PlayerNum
{
	P1,
	P2
};

enum class MonsterState
{
	Idle,
	Move,
	Ready,
	Freeze,
	Anger,
	AngerIdle,
	AngerMove,
	EggSummon, // 소환
	EggIdle,
	EggMove,
	EggHatch, // 부화
	EggDeath,
	Die,
	// Boss State
	Hitten,
	Summon,
	Die_Ready,
	Die_Bubble,
};