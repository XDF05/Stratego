#ifndef BOARD_H
#define BOARD_H
#include <array>
#include <list>
#include <optional>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "piece.h"

/**
 * @brief The Board class
 * repesents a board containing pieces at given positions
 */
class Board
{
    /**
     * @brief SIZE_
     * Size for the board (10x10)
     * going from 1-10 and from A-J
     */
    static const unsigned int SIZE_ {10};

    std::array<std::array<std::optional<Piece>, SIZE_>, SIZE_> board_;

    std::optional<Piece> lastMovedPieceP1;
    Position lastInitialPositionP1;

    std::optional<Piece> lastMovedPieceP2;
    Position lastInitialPositionP2;

    unsigned cntBackForthP1;
    unsigned cntBackForthP2;
  public:
    /**
     * @brief Board contructor for the Board
     */
    Board();

    /**
     * @brief init initializes the board for a given player.
     * @param board player's board
     * @param player given player
     */
    void init(std::array<std::array<std::optional<Piece>, 10>, 4>  &
              board,
              int player);
    /**
     * @brief move
     * if possible, moves a piece to a given position
     * if a piece is present on the destination position, attacks it instead.
     * @param p given piece
     * @param nextPos given position
     */
    bool move(Position const & initialPos, Position const & nextPos,
              int player);
    /**
     * @brief swap swaps 2 pieces from the same player
     * used during the manual initialisation for the GUI version of the game
     * @param p1 pos of piece 1
     * @param p2 pos of piece 2
     * @param player current player's turn
     */
    void swap(Position const & p1, Position const & p2, int player);
    /**
     * @brief isGameOver verifies whether the game is over
     * @return true if game is over, false if not
     */
    bool isGameOver() const;
    /**
     * @brief getWinner get the winner from the current game
     * @return winner (player 0 = blue, player 1 = red)
     */
    int getWinner() const;

    /**
     * @brief isPlayerBoardFull
     * verifies wether the board of a given player is full.
     * @param player given player
     * @return whethre the board is full or not
     */
    bool isPlayerBoardFull(int player);

    /**
     * @brief addPiece places a piece at a given position.
     * @param piece given piece to place
     * @param pos given position to place the piece at
     */
    void addPiece(const Piece & piece, const Position & pos);

    /**
     * @brief isPiece verifies whether there's a piece at a given position or not
     * @param nextPos given position
     * @return true if a piece is located at the given position, false if not
     */
    bool isPiece(Position const & pos);

    /**
     * @brief getBoard
     * @return a constant reference to the board
     */
    const std::array<std::array<std::optional<Piece>, SIZE_>, SIZE_> &
    getBoard() const;

    std::optional<Piece> & at(const Position & pos)
    {
        return this->board_[pos.row_][pos.col_];
    }

  private:
    /**
     * @brief isInside verifies whether the given position is inside the Board
     * @param nextPos given position
     * @return true if position is inside, false if not
     */
    bool isInside(Position const & nextPos) const
    {
        return (nextPos.col_ <= 9 && nextPos.row_ <= 9);
    }

    /**
     * @brief canMovePiece
     * Verifies whether there are different pieces on the board than water, bombs or flags.
     * @return true if there is any other piece false if not.
     */
    bool canMovePiece() const
    {
        bool player0{};
        bool player1{};
        for (size_t row = 0; row < board_.size(); row ++) {
            for (size_t col = 0; col < board_[row].size(); col++) {
                std::optional<Piece> const & p = board_[row][col];
                if (p.has_value()) {
                    if ((p->getName() != Pieces::BOMBE) &&
                            (p->getName() != Pieces::DRAPEAU) &&
                            (p->getName() != Pieces::EAU)) {
                        p->getPlayer() == 0 ? player0 = true : player1 = true;
                    }
                }
            }
        }
        return (player0 && player1);
    }

    bool canMovePiece(int player)const
    {
        for (size_t row = 0; row < board_.size(); row ++) {
            for (size_t col = 0; col < board_[row].size(); col++) {
                std::optional<Piece> const & p = board_[row][col];
                if (p.has_value()) {
                    if ((p->getPlayer() == player) &&
                            (p->getName() != Pieces::BOMBE) &&
                            (p->getName() != Pieces::DRAPEAU)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /**
     * @brief Piece at initialPos fights the other piece, the loser gets removed & replaced by the winning piece
     * if both pieces are equal, both pieces get removed.
     * Sets both piece's visibility to visible during the fight
     * @param p1 moved piece
     * @param p2 other piece
     */
    bool fight(Position const & initialPos, Position const & nextPos)
    {

        std::optional<Piece> & p1 = board_[initialPos.row_][initialPos.col_];
        std::optional<Piece> & p2 = board_[nextPos.row_][nextPos.col_];

        if (isPiece(nextPos)) {
            p1->toggleRevealed();
            p2->toggleRevealed();
            if (p1->isStrongerThan(p2.value())) {

                p2.swap(p1);
                p1.reset();
            }
            else if (p1->getName() == p2->getName()) { //both pieces equal
                p2.reset();
                p1.reset();
            }
            else {
                p1.reset();
            }
            p1->toggleRevealed();
            p2->toggleRevealed();
            return true;
        }
        return false;
    }
    /**
     * @brief getFlagCount
     * @return amount of flags remaining in the game
     */
    int getFlagCount() const
    {
        int cnt{};
        for (size_t row = 0;  row < this->board_.size(); row++) {
            for (size_t col = 0; col < this->board_[row].size(); col++) {
                if (this->board_[row][col].has_value() &&
                        this->board_[row][col].value().getName() == Pieces::DRAPEAU) {
                    cnt++;
                }
            }
        }
        return cnt;
    }

    /**
         * @brief isPieceBetween Tells if there is a piece between 2 positions
         * @param initialPos The first position
         * @param nextPos The second position
         * @param colDiff The absolute distance in colums between 2 positions
         * @param rowDiff The absolute distance in rows between 2 positions
         * @return True if there's a piece in between
         *
         * This method will only work if the two positions are in the same row/col
         */
    bool isPieceBetween(Position const & initialPos,
                        Position const & nextPos,
                        int const & colDiff,
                        int const & rowDiff)
    {
        int direction{};

        if (rowDiff <= 1 && colDiff <= 1) {
            // if they are close there can't be any piece between.
            return false;
        }

        if (rowDiff == 0) {
            direction = (initialPos.col_ < nextPos.col_) ? 1 : -1;

            for (int i = 1; i <= colDiff - 1; i++) {
                if (this->board_[initialPos.row_][initialPos.col_ +
                                                  (i * direction)].has_value()) {
                    return true;
                }
            }

        }
        else {
            direction = (initialPos.row_ < nextPos.row_) ? 1 : -1;   
            for (int i = 1; i <= rowDiff - 1; i++) {
                if (this->board_[initialPos.row_ + (i *
                                                    direction)][initialPos.col_].has_value()) {
                    return true;
                }
            }
        }
        return false;
    }
};
#endif // BOARD_H
