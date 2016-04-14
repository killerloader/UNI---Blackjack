#pragma once

/*
	Player.h/ Player.cpp
		A derived class of "Person".
		Nothing is actually different here, it is just for differentiating from the dealer.
*/

#include "Person.h"

//Derived from Person class
class Player : public Person
{
public:
	Player(Game& gameRef);	//Constructor
};

