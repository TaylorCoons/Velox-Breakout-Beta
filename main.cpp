/* CSCI 261 Section C: Brick Breaker final project
*
* Desc: Brick breaker arrow keys to play space to pause, press a to autopilot
*
*
*Author: Taylor Coons
*/

#include <iostream>
#include "GameClass.h"

// Entry Point //
int main() {
	GameClass myGame;
	myGame.Init();
	myGame.Run();
    return 0;
}