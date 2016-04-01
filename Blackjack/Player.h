#pragma once
#include "Person.h"

class Player : public Person
{
public:
	Player(Game& GmRef);
	~Player();
};

