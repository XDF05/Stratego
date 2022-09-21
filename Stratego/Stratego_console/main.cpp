#include <game.h>
#include "viewConsole.h"
#include "controller.h"
int main()
{
    ViewConsole view{};
    bool cheatMode = view.askCheatMode();

    Game game{cheatMode};
    Controller ctrl{game, view};
    ctrl.start();
}
