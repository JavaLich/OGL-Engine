#pragma once
class Component
{
public:
	Component();
	~Component();
	void update(double delta);
	bool ticks = false;
};

