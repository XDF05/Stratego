#ifndef GUIBOARD_H
#define GUIBOARD_H
#include <array>
#include <QObject>

#include "game.h"
#include "observer.h"
#include "position.h"
class PieceBox;
class GuiPiece;
class GameView;
/**
 * @brief The GuiBoard class
 * Component used to hold the graphical representation of the board and its pieces
 */
class GuiBoard : public QObject, public Observer
{
    Q_OBJECT
  public:
    //public methods

    /**
     * @brief GuiBoard contructor for the Graphical board
     */
    GuiBoard(GameView * view, int x, int y, Game * subject);

    /**
     * @brief update updates the board after a move has occured
     * @param subject observed subject, verifies if it's the same instance as the one saved
     * @param propertyName
     */
    void update(const Subject * subject,
                const std::string & propertyName) override;

    /**
     * @brief defaultInit default piece placement for a given player
     * @param player given player
     */
    void defaultInit(int player);
    /**
     * @brief redrawBoard deletes and recreates pieces & boxes in order to re draw the board after a move has been done
     */
    void redrawBoard();
    /**
     * @brief disablePlayerPieces disable the events on a every piece of a given player during the initialisation phase
     * @param player given player
     */
    void disablePlayerPieces(int player);
    /**
     * @brief reEnablePieces re enables events on every piece on the board once the game has started
     */
    void reEnablePieces();


  private:
    //private attributes

    /**
     * @brief x x position of the board (top left corner)
     */
    int x;
    /**
     * @brief y y position of the board (top left corner)
     */
    int y;
    /**
     * @brief beforeMove Position of a piece before it has been moved
     */
    Position beforeMove;
    /**
     * @brief afterMove Position of the latest moved piece (after it has been moved)
     */
    Position afterMove;
    /**
     * @brief boxes boxes repesenting the board
     */
    std::array<std::array<PieceBox *, 10>, 10> boxes;
    /**
     * @brief subject observered subject
     */
    Game * subject;
    /**
     * @brief view GameView
     */
    GameView * view;

    bool started;

  private:
    // private methods

    /**
     * @brief drawBoxes draws boxes to create a board representation
     */
    void drawBoxes();
    /**
     * @brief createPieces creates the graphical pieces for a given player
     * according the the board inside the model
     * @param player given player
     */
    void initPieces(int player);
    /**
     * @brief initWater creates and places water on the board
     */
    void initWater();
    /**
     * @brief reCreatePieces refreshes the board after a move has occured
     */
    void reCreatePieces();
    /**
     * @brief resetPiecePosition resets a given's piece position according to its initial position
     * @param p given piece
     */
    void resetPiecePosition(GuiPiece * p);
    /**
     * @brief disablePieces disabled pieces once the game is over
     */
    void disablePieces();
    /**
     * @brief hideOpponentPieces hides the pieces of the opponent
     */
    void hideOpponentPieces();
    /**
     * @brief addBoardToScene places every boxes from the board inside the view
     */
    void addBoardToScene();

  private slots:
    /**
     * @brief onPieceDrop saves the position of a piece before the move has occured
     * @param box box in which the moved piece is
     */
    void onPieceDrag(PieceBox * box);

    /**
     * @brief onPieceDrop changes the box in which a piece is according to the position where the piece is dropped
     * @param pos position at which the piece is dropped
     */
    void onPieceDrop(QPoint & pos);
};

#endif // GUIBOARD_H
