/**
 *	    ______  _____  _____   _____   _____  ___    __   _____
 *     / ____/ / _  / /    /  /    /  /    / / _ \  / /  /    /
 *	  / /_    / // / /  ^_/  /  ^_/  /  ^ / / // / / /  /  ^ /
 *	 / __/   / // / / . \   / . \   / // / / // / / /  / // /
 *	/_/     /____/ /_/ \_\ /_/ \_\ /_//_/ /____/ /_/  /_//_/
 *
**/
#include "CommonExternal.h"
#include "Implementation/CGameInstance.h"

/**
 * @brief Creates game instance and runs it.
 * @return Success result.
 */
int main()
{
    Forradia::CGameInstance GameInstance;
    GameInstance.StartGame();

    return 0;
}
