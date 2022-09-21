#ifndef GAME_H
#define GAME_H
#include "state.h"
#include "board.h"
#include "subject.h"
#include "observer.h"
#include <list>
/**
 * @brief The Game class used as a facade for the Stratego game
 */
class Game : public Subject
{
    /**
     * @brief currentPlayer_
     * 0 = Blue
     * 1 = Red
     */
    int currentPlayer_{0};
    /**
     * @brief state_ state in which the game is
     */
    State state_;
    /**
     * @brief cheatMode_ cheat mode that displays every piece
     */
    const bool cheatMode_;
    /**
     * @brief board_ playing Board containing pieces
     */
    Board board_;

    std::list<Observer *> observers_;

  public:
    /**
     * @brief Game constructor for stratego game
     */
    Game(bool cheatMode = false);
    /**
     * @brief init
     * Takes player 1 and player 2 boards and adds them toghether
     * 2 rows are added in the middle to separate each player's side
    //     * (with water at in pos (C5,C6,D5,D6) and in pos (G5,G6,H5,H6)
     * @param player1 player 1's board with his pieces
     * @param player2 player 2's board with his pieces
     */
    void init(std::array<std::array<std::optional<Piece>, 10>, 4>
              & playerBoard);
    /**
     * @brief start starts the game
     */
    void start();
    /**
     * @brief move asks to moves a piece to a given place to the Board
     * @param p given piece
     * @param nextPos given pos
     */
    bool move(Position const & firstPos, Position const & nextPos);
    /**
     * @brief swap swaps 2 pieces from the same player
     * used during the manual initialisation for the GUI version of the game
     * @param p1 pos of piece 1
     * @param p2 pos of piece 2
     */
    void swap(Position const & p1, Position const & p2);
    /**
     * @brief isPlayerBoardFull asks the board if the player board is full
     * @param player given player
     * @return whether the game is full or not
     */
    bool isPlayerBoardFull(int player);

    /**
     * @brief isGameOver asks the board whether the game is over or not
     * @return whether the game is over or not.
     */
    bool isGameOver() const;
    /**
     * @brief getWinner asks the Board who the winner is
     * @return winner (0=Blue, 1=Red)
     */
    int getWinner() const;
    /**
     * @brief getBoard
     * retrieves the board
     *
     * Only used to display the game.
     * @return board
     */
    const std::array<std::array<std::optional<Piece>, 10>, 10> &
    getBoard() const;
    /**
     * @brief getCurrentPlayer getter for the current player
     * @return current player
     */
    int getCurrentPlayer() const;
    /**
     * @brief addPiece asks the board to place a piece at a given position
     * @param piece given piece to place
     * @param pos given position to place the piece at
     */
    void addPiece(const Piece & piece, const Position & pos);
    /**
     * @brief nextPlayer sets current player to the next player.
     * used after a player's turn is over
     */
    void nextPlayer();

    /**
     * @brief isPiece verifies whether a piece is present at a given position
     * @param pos given position
     * @return whether a piece is present
     */
    bool isPiece(const Position & pos);
    bool isCheatModeOn() const;

    // Subject interface
  public:
    void addObserver(Observer * o)override
    {
        observers_.push_back(o);
    }
    void removeObserver(Observer * o)override
    {
        observers_.remove(o);
    }
    void notify(const std::string &propertyName)override
    {
        for (auto const & o : observers_) {
            o->update(this, propertyName);
        }
    }
};
/**
 * @brief operator <<
 * overloads the << operator in order to print the board
 * @param os ostream
 * @param game game to display
 * @return overloaded <<
 */
std::ostream & operator<<(std::ostream & os, const Game & game);


#endif // GAME_H
