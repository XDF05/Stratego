#include <array>
#include <iomanip>

#include "game.h"
using std::array;
Game::Game(bool cheatMode):
    cheatMode_{cheatMode},
    board_{Board()}
{}

void Game::init(std::array<std::array<std::optional<Piece>, 10>, 4>
                & playerBoard)
{
    this->board_.init(playerBoard, currentPlayer_);
    notify("INIT");
}

void Game::start()
{
    notify("START");
}

bool Game::move(Position const & initialPos, Position const & nextPos)
{
    bool success = this->board_.move(initialPos, nextPos,
                                     this->getCurrentPlayer());
    if (success) {
        nextPlayer();
    }
    notify("MOVE");

    return success;

}

void Game::swap(const Position & p1, const Position & p2)
{
    this->board_.swap(p1, p2, currentPlayer_);
    notify("SWAP");
}

bool Game::isPlayerBoardFull(int player)
{
    return this->board_.isPlayerBoardFull(player);
}

bool Game::isGameOver() const
{
    return this->board_.isGameOver();
}

int Game::getWinner() const
{
    return this->board_.getWinner();
}
const std::array<std::array<std::optional<Piece>, 10>, 10> &
Game::getBoard()
const
{
    return this->board_.getBoard();
}

int Game::getCurrentPlayer() const
{
    return this->currentPlayer_;
}

void Game::nextPlayer()
{
    this->currentPlayer_++;
    this->currentPlayer_ = this->currentPlayer_ % 2;
}

void Game::addPiece(const Piece & piece, const Position & pos)
{
    this->board_.addPiece(piece, pos);
}

bool Game::isPiece(const Position & pos)
{
    return this->board_.isPiece(pos);
}

bool Game::isCheatModeOn() const
{
    return this->cheatMode_;
}

std::ostream & operator<<(std::ostream & os, const Game & game)
{
    const int currentPlayer = game.getCurrentPlayer();
    for (auto const & arr : game.getBoard()) {
        for (auto const & elem : arr) {
            if (elem.has_value()) {
                if (game.isCheatModeOn() ||
                        (elem.value().getPlayer() == currentPlayer ||
                         elem.value().getPlayer() == -1)) {
                    switch (elem.value().getName()) {
                        case 11:
                            os << std::setw(2) << "D" << " ";
                            break;
                        case 12:
                            os << std::setw(2) << "B" << " ";
                            break;
                        case -1:
                            os << std::setw(2) << "W" << " ";
                            break;
                        default:
                            os << std::setw(2) << elem.value().getName() << " ";
                            break;
                    }
                }
                else {
                    os << std::setw(2) << "X" << " ";
                }

            }
            else {
                os << std::setw(2) << "." << " ";
            }
        }
        os << std::endl;
    }
    return os;
}


