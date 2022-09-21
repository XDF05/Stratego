#include "piece.h"
#include "pieces.h"

Piece::Piece(Pieces name, int player, bool revealed) :
    name_{name},
    player_{player},
    revealed_{revealed}
{

}

/**
 * @brief Piece::isStrongerThan tells if a piece can win a fight against another piece
 * @param other the piece to be compared with
 * @return true if the other piece is weaker
 */
bool Piece::isStrongerThan(Piece & other)
{
    // water exceptions in move()

    switch (other.getName()) {
        case Pieces::DRAPEAU :
            return true;
            break;
        case Pieces::BOMBE :
            return this->getName() == Pieces::DEMINEUR;
            break;
        case Pieces::GENERAL :
            return this->getName() == Pieces::ESPIONNE;
        default:
            return this->getName() > other.getName();
    }
}

Pieces Piece::getName() const
{
    return this->name_;
}

int Piece::getPlayer() const
{
    return this->player_;
}

bool Piece::isRevealed() const
{
    return this->revealed_;
}

void Piece::toggleRevealed()
{
    this->revealed_  = !revealed_;
}
std::ostream & operator<<(std::ostream & os, const Piece & piece)
{
    return os << piece.getName();
}
