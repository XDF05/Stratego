#include <algorithm>
#include <iostream>
#include <cmath>

#include "board.h"
#include "pieces.h"

using std::cerr;
using std::endl;
Board::Board()
{
    this->cntBackForthP1 = 0;
    this->cntBackForthP2 = 0;
    //sets water on the board
    for (size_t row = 4; row < 6; row++) {
        for (size_t col = 2; col < 4; col ++) {
            this->board_[row][col] = Piece(Pieces::EAU, -1, true);
            this->board_[row][col + 4] = Piece(Pieces::EAU, -1, true);
        }
    }

}

void Board::init(std::array<std::array<std::optional<Piece>, 10>, 4>
                 & playerBoard,
                 int player)
{
    int rowOffset{0};
    if (player == 1) {
        rowOffset = 6;
        std::reverse(playerBoard.begin(),
                     playerBoard.end()); //mirrors the playerBoard if player 2
    }
    for (size_t row = 0; row < playerBoard.size(); row++) {
        for (size_t col = 0; col < playerBoard[row].size(); col++) {
            if (this->board_[row + rowOffset][col].has_value()) {
                throw std::invalid_argument("Board not empty before initialization!");
            }
            this->board_[row + rowOffset][col] = playerBoard[row][col];
        }
    }
}

bool Board::move(Position const & initialPos,
                 Position const & nextPos, int player)
{
    int rowDiff = initialPos.row_ - nextPos.row_;
    int colDiff = initialPos.col_ - nextPos.col_;
    rowDiff = abs(rowDiff);
    colDiff = abs(colDiff);

    std::optional<Piece> & p1 = board_[initialPos.row_][initialPos.col_];
    std::optional<Piece> & p2 = board_[nextPos.row_][nextPos.col_];

    if (initialPos.row_ == nextPos.row_ &&
            initialPos.col_ == nextPos.col_) {
        throw std::invalid_argument("Initial position and destination must be different!");
    }

    if (p1->getPlayer() != player) {
        throw std::invalid_argument("Can't move another player's pieces!");
    }

    if (!isInside(initialPos)) {
        throw std::invalid_argument("The initial position is not in the board: "
                                    +
                                    std::to_string(initialPos.row_) + " " + std::to_string(
                                        initialPos.col_ ));
    }
    if (!isInside(nextPos)) {
        throw std::invalid_argument("The position to move to is not in the board: "
                                    +
                                    std::to_string(initialPos.row_) + " " + std::to_string(
                                        initialPos.col_ ));
    }

    if (!isPiece(initialPos)) {
        throw std::invalid_argument("There is no piece in the initial position!");
    }

    if (p2->getName() == Pieces::EAU) {
        throw std::invalid_argument("A piece cannot go on water!");
    }
    if (p1->getName() == Pieces::EAU) {
        throw std::invalid_argument("water cannot be moved!");
    }
    if (p1->getName() == Pieces::DRAPEAU) {
        throw std::invalid_argument("flag cannot be moved!");
    }
    if (p1->getName() == Pieces::BOMBE) {
        throw std::invalid_argument("bombs cannot be moved!");
    }

    if (isPiece(nextPos)) {
        if (p1->getPlayer() == p2->getPlayer()) {
            throw std::invalid_argument("You may not attack one of your pieces!");
        }

        if (p1->getName() == Pieces::ECLAIREUR){

            if ((colDiff > 0) && (rowDiff > 0)) {
                throw std::invalid_argument("Pieces may only move on a row or column");
            }
            else if (isPieceBetween(initialPos, nextPos, colDiff, rowDiff)) {
                throw std::invalid_argument("There is a piece in between the original position and the desired position!");
            }
            return fight(initialPos, nextPos);
        } else {
            if (rowDiff > 1 || colDiff > 1 || (rowDiff == colDiff)) {
                throw std::invalid_argument("Only the scout can move more than one case!");
            }
            if (p2->getPlayer() == p1->getPlayer()) {
                throw std::invalid_argument("Can't fight a friendly piece!");
            }
            return fight(initialPos, nextPos);
        }
    }
    else if (p1->getName() == Pieces::BOMBE ||
             p1->getName() == Pieces::DRAPEAU
             || p1->getName() == Pieces::EAU) {
        throw std::invalid_argument("Bombs, Flags or Water cannot move!");
    }
    else if (p1->getName() != Pieces::ECLAIREUR) {
        if (rowDiff > 1 || colDiff > 1 || (rowDiff == colDiff)) {
            throw std::invalid_argument("Only the scout can move more than one case!");
        }
    }
    else {
        if ((colDiff > 0) && (rowDiff > 0)) {
            throw std::invalid_argument("Pieces may only move on a row or column");
        }
        else if (isPieceBetween(initialPos, nextPos, colDiff, rowDiff)) {
            throw std::invalid_argument("There is a piece in between the original position and the desired position!");
        }
    }

    switch (player) {
        case 0:
            if ((p1->getName() == this->lastMovedPieceP1->getName()) &&
                    (nextPos.col_ == this->lastInitialPositionP1.col_ &&
                     nextPos.row_ == this->lastInitialPositionP1.row_)) {
                this->cntBackForthP1++;

            }
            else {
                this->cntBackForthP1 = 0;
            }
            break;
        case 1:
            if ((p1->getName() == this->lastMovedPieceP2->getName()) &&
                    (nextPos.col_ == this->lastInitialPositionP2.col_ &&
                     nextPos.row_ == this->lastInitialPositionP2.row_)) {
                this->cntBackForthP2++;

            }
            else {
                this->cntBackForthP2 = 0;
            }
            break;
    }
    if (this->cntBackForthP1 >= 4 || this->cntBackForthP2 >= 4) {
        throw std::invalid_argument("Cannot move the same piece back and forth more than 3 times!");
    }

    p1.swap(p2);
    switch (p1->getPlayer()) {
        case 0:
            this->lastMovedPieceP1 = p1;
            this->lastInitialPositionP1 = initialPos;
            break;
        case 1:
            this->lastMovedPieceP2 = p1;
            this->lastInitialPositionP2 = initialPos;
            break;
    }

    return true;
}

void Board::swap(const Position & p1, const Position & p2, int player)
{
    if ((player == 0 && (p1.row_ > 3 || p2.row_ > 3)) ||
            (player == 1 && (p1.row_ < 6 || p2.row_ < 6))) {
        throw std::invalid_argument("SWAP : invalid row player : " +
                                    std::to_string(player));
    }

    std::optional<Piece> piece1 = this->board_[p1.row_][p1.col_];
    std::optional<Piece> piece2 = this->board_[p2.row_][p2.col_];

    if ((player == piece1->getPlayer()) &&
            (piece1->getPlayer() == piece2->getPlayer())) {

        std::optional<Piece> temp = piece1;
        this->board_[p1.row_][p1.col_] = piece2;
        this->board_[p2.row_][p2.col_] = temp;
    }
}

bool Board::isPiece(const Position & pos)
{
    return this->board_[pos.row_][pos.col_].has_value();
}
void Board::addPiece(const Piece & piece, const Position & pos)
{
    this->board_[pos.row_][pos.col_] = std::optional<Piece> {piece};
}

const std::array<std::array<std::optional<Piece>, 10>, 10> &
Board::getBoard() const
{
    return this->board_;
}

bool Board::isPlayerBoardFull(int player)
{
    int rowOffset{0};
    int rowMax = this->board_.size();
    (player == 1) ? rowOffset = 6 : rowMax = 6;
    for (int row = rowOffset; row < rowMax; row++) {
        for (size_t col = 0; col < this->board_.size(); col++) {
            if (!this->board_[row][col].has_value()) {
                return false;
            }
        }
    }
    return true;
}


bool Board::isGameOver() const
{
    unsigned cnt = getFlagCount();

    switch (cnt) {
        case 1:
            return true;
        case 2: {
                return !canMovePiece();
            }
        default:
            throw std::invalid_argument("Invalid amount of DRAPEAU pieces remaining! "
                                        + std::to_string(cnt));
    }
}

int Board::getWinner() const
{
    if (getFlagCount() == 1) {
        for (size_t row = 0;  row < this->board_.size(); row++) {
            for (size_t col = 0; col < this->board_[row].size(); col++) {
                if (this->board_[row][col].has_value() &&
                        this->board_[row][col]->getName() == Pieces::DRAPEAU) {
                    return this->board_[row][col]->getPlayer();
                }
            }
        }
    }
    if (!canMovePiece(0) && canMovePiece(1)) {
        return 1;
    }
    if (canMovePiece(0) && !canMovePiece(1)) {
        return 0;
    }
    return -1; //game tied
}

