#pragma once

/*
	Dealer.h/ Dealer.cpp
		A derived class of "Person".
		Nothing is actually different here, it is just for differentiating from the player.
*/

#include "Person.h"

//Derived from person.
class Dealer : public Person
{
public:
	Dealer(Game& GmRef);	//Constructor
	~Dealer();				//Destructor
};

