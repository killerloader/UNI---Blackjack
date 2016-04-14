#include "Player.h"
#include <iostream>

//Player constructor, calls Person constructor to give it the main game class reference.
Player::Player(Game& gameRef) : Person(gameRef)
{

}