#pragma once
#include "Person.h"

class Dealer : public Person
{
public:
	Dealer(Game& GmRef);
	~Dealer();
};

