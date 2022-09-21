#ifndef P_H
#define P_H
#include <ostream>

#include "position.h"
#include "pieces.h"

/**
 * @brief The Piece class
 * std::optional is used to create the pieces, this way they can easily be removed from the board.
 */
class Piece
{
    /**
     * @brief name_ name of the piece
     */
    Pieces name_;
    /**
     * @brief player_ player which owns the piece
     * -1 = Water (sentinel value used to represent water on the board)
     * 0 = Blue
     * 1 = Red
     */
    int player_;
    /**
     * @brief revealed_ describes whether a piece is revealed or not
     * a piece gets revealed when it's engaged in a fight
     */
    bool revealed_;

    //Position pos_;

  public:
    /**
     * @brief Piece constructor for the Piece
     * @param symbol given symbol for the piece
     * @param player owner of the piece (-1 for water)
     * @param revealed initially unrevealed
     * could be revelead at creation for testing purposes.
     */
    Piece(Pieces name, int player, bool revealed = false);
    /**
     * @brief isStrongerThan verifies whether the current piece is beats the opposing piece
     * @param other opposing piece (attacked piece)
     * @return whether the attacker is stronger than the attacked piece
     */
    bool isStrongerThan(Piece & other);
    /**
     * @brief getSymbol getter for the symbol
     * @return symbol
     */
    Pieces getName() const;
    /**
     * @brief getPlayer getter for the player
     * @return player owning the piece
     */
    int getPlayer() const;
    /**
     * @brief getRevealed getter for the revealed attribute
     * @return whether the piece is revealed or not
     */
    bool isRevealed() const;

    /**
     * @brief setRevealed reveals a piece
     */
    void toggleRevealed();
};
std::ostream & operator<<(std::ostream & os, const Piece & piece);

#endif // P_H
