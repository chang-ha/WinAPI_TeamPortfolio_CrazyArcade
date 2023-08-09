#include "BaseCharacter.h"
#include "PlayLevel.h"

void BaseCharacter::BubbleStart()
{
	ChangeAnimationState("Bubble");
}
void BaseCharacter::BubbleUpdate(float _Delta)
{

}

void BaseCharacter::FlashLongStart()
{
	ChangeAnimationState("FlashLong");
}
void BaseCharacter::FlashLongUpdate(float _Delta)
{

}

void BaseCharacter::FlashShortStart()
{
	ChangeAnimationState("FlashShort");
}
void BaseCharacter::FlashShortUpdate(float _Delta)
{

}

void BaseCharacter::LiveStart()
{
	ChangeAnimationState("Live");
}
void BaseCharacter::LiveUpdate(float _Delta)
{

}

void BaseCharacter::DieStart()
{
	ChangeAnimationState("Die");
}
void BaseCharacter::DieUpdate(float _Delta)
{

}