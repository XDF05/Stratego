#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <game.h>
#include "viewConsole.h"

/**
 * @brief The Controller class
 * Only useable for the console version of the game
 */
class Controller
{
    /**
     * @brief game_ instance of the game
     */
    Game & game_;
    /**
     * @brief view_ instance of the console view
     */
    ViewConsole & view_;

  public:
    /**
     * @brief Controller constructor for the controller
     * @param game given instance of the game
     * @param view given instance of the view
     */
    Controller(Game & game, ViewConsole & view);
    /**
     * @brief start starts the game
     */
    void start();
    /**
     * @brief initPlayerBoardManually
     * Asks the player to initialize its pieces manually
     * @param player
     */
    void initPlayerBoardManually(int player);
    /**
     * @brief initPlayerBoard
     * Asks the player to enter a file in order to initialize its board
     */
    void initPlayerBoard();
    /**
     * @brief movePiece
     * Asks the current player for a piece's position and moves it at a destination position given by the user.
     */
    void movePiece();
};

#endif // CONTROLLER_H
