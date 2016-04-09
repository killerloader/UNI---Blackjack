#pragma once
#include "Person.h"

/*
	Dealer.h/ Dealer.cpp
		A derived class of "Person".
		Nothing is actually different here, it is just for differentiating from the player.
*/

//Derived from person.
class Dealer : public Person
{
public:
	Dealer(Game& GmRef);	//Constructor
	~Dealer();				//Destructor
};

