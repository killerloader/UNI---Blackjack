//include iostream to give access to input and output functions apart of the std namespace.
#include <iostream>
#include "Game.h"



//Use the std namespace so that it does not have to be typed before every std function.
using namespace std;

//Run the main function so that the compiler knows where the program starts from.
int main()
{
	//Check for memory leaks when in debug mode.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Create the main game object.
	Game GameObj;

	//Run the function in the Game object which has the game loop in it.
	GameObj.Run();

	return 0;
}