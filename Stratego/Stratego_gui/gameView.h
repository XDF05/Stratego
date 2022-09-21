#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsTextItem>

#include "guiboard.h"

class Game;
class GuiBoard;
/**
 * @brief The GameView class Graphical view for the game
 */
class GameView: public QGraphicsView
{
    Q_OBJECT
  public:
    // public methods

    /**
     * @brief GameView constructor for the game view
     * @param parent game page
     */
    GameView(Game & game, QWidget * parent = nullptr);
    /**
     * @brief start starts the game view, draws the board and places pieces
     */
    void start();
    /**
     * @brief defaultInit calls default from the board
     * @param player given player
     */
    void defaultInit(int player);

    /**
     * @brief addToScene adds items to the scene
     * @param item given item
     */
    void addToScene(QGraphicsItem * item);

    /**
     * @brief removeFromScene removes items from the scene
     * @param item given item
     */
    void removeFromScene(QGraphicsItem * item);
    /**
     * @brief showGameOver show the game over label with the winner of the game
     */
    void showGameOver();
    /**
     * @brief showError shows the error message whenever the swap or move a player tried to do failed.
     */
    void showError(QString errorMsg);

    void setErrorMsgText(QString errorMsg);
  private:
    // private attributes

    /**
     * @brief game instance of the game, required to add the board as an observer
     */
    Game & game;
    /**
     * @brief scene Graphical scene required for the view
     */
    QGraphicsScene * scene;
    /**
     * @brief board Graphical representation of the board
     */
    GuiBoard * board;
    /**
     * @brief btnConfirmP1 confirm button for the player 1's pieces placement
     */
    QPushButton * btnConfirmP1;
    /**
     * @brief btnConfirmP2 confirm button for the player 2's pieces placement
     */
    QPushButton * btnConfirmP2;
    /**
     * @brief btnStart game start button
     */
    QPushButton * btnStart;
    /**
     * @brief lGameOver gameOver label
     */
    QGraphicsTextItem * lGameOver;
    /**
     * @brief lErrorMessage lErrorMessage error message label
     */
    QGraphicsTextItem * lErrorMessage;

  private:
    // private methods

    /**
     * @brief connectAll connects all the buttons with the according slots
     */
    void connectAll();

  private slots :
    /**
     * @brief startGame once both btnConfirmP1 and btnConfirmP2 have been pressed, allow the players the start the game
     */
    void startGame();
    /**
     * @brief confirmP1 allows player 1 to confirm his piece placement and lets the next player place his pieces.
     */
    void confirmP1();
    /**
     * @brief confirmP2 allows player 2 to confirm his piece placement and lets the next player place his pieces.
     */
    void confirmP2();
};

#endif // GAMEVIEW_H
