#pragma once

class Controllable
{
public:
	virtual void reactToInput(bool *keys) = 0;
};