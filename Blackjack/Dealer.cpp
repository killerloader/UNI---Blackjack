#include "Dealer.h"

//Dealer constructor, calls Person constructor to give it the main game class reference.
Dealer::Dealer(Game& gameRef) : Person(GmRef)
{

}

//Dealer deconstructor. Person deconstructor deletes everything necessary.
Dealer::~Dealer()
{

}