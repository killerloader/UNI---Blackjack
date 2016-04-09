#include "Player.h"
#include <iostream>

//Player constructor, calls Person constructor to give it the main game class reference.
Player::Player(Game& GmRef) : Person(GmRef)
{

}

//Player deconstructor. Person deconstructor deletes everything necessary.
Player::~Player()
{

}