#pragma once

class Structure
{
public:
	// Constructor Destructor
	Structure();
	~Structure();

	// Delete Function
	Structure(const Structure& _Other) = delete;
	Structure(Structure&& _Other) noexcept = delete;
	Structure& operator=(const Structure& _Other) = delete;
	Structure& operator=(Structure&& _Other) noexcept = delete;

protected:

private:

};