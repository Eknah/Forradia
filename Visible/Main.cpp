#include "Pch.h"
#include "Implementation/CGameInstance.h"
//extern std::unordered_map<std::string, int> test_function();
//#pragma comment(lib, "../Release/LibTest.lib")
/**
 *	    ______  _____  _____   _____   _____  ___    __   _____
 *                 / ____/ / _  / /    /  /    /  /    / / _ \  / /  /    /
 *	  / /_    / // / /  ^_/  /  ^_/  /  ^ / / // / / /  /  ^ /
 *	 / __/   / // / / . \   / . \   / // / / // / / /  / // /
 *	/_/     /____/ /_/ \_\ /_/ \_\ /_//_/ /____/ /_/  /_//_/
 *
 *	Forradia is a magical world with roaming creatures. You was sent here
 *	in your search for answers to questions you have been asking. Such as
 *	who and where is your lost sister? And, what are the butterflies of Forradia?
 *
/



/**
 * @brief Entry point for the game.
 * @param argc 
 * @param args 
 * @return 
*/
int main(int argc, char* args[])
{
	//printf((std::string("Hej " + std::to_string(test_function().at("A"))).c_str()));
	Forradia::CGameInstance gameInstance;
	gameInstance.StartGame();
	return 0;
}
