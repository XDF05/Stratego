#include <map>

#include <utils.h>
#include <pieces.h>
#include <piece.h>
#include "keyboard.h"
#include "controller.h"

Controller::Controller(Game & game, ViewConsole & view) :
    game_{game},
    view_{view}
{}

void Controller::start()
{
    view_.printGame(game_);
    (view_.askUseFile(game_.getCurrentPlayer())) ? initPlayerBoard() :
    initPlayerBoardManually(game_.getCurrentPlayer());
    view_.printGame(game_);
    view_.askNextPlayer();
    (view_.askUseFile(game_.getCurrentPlayer())) ? initPlayerBoard() :
    initPlayerBoardManually(game_.getCurrentPlayer());
    view_.printGame(game_);

    while (!game_.isGameOver()) {
        movePiece();
        view_.printGame(game_);
        view_.askNextPlayer();
        view_.printGame(game_);
    }
    view_.printWinner(game_);
}

void Controller::movePiece()
{
    Position initPos;
    Position nextPos;
    bool moved = false;
    do {
        initPos =
            view_.askPosition("please enter the position of the piece you wish to move");
        nextPos =
            view_.askPosition("please enter the position where you'd like to move your piece to");
        try{
        moved = game_.move(initPos, nextPos);}catch(std::invalid_argument const & ex){
            std::cerr <<ex.what();
        }
    }
    while (!moved);
}

void Controller::initPlayerBoard()
{
    std::string path;
    path = "../../Stratego/templates/" +
           view_.askFile("Please enter the file you wish to open");
    while (!readFile(path, game_, game_.getCurrentPlayer())) {
        path = "../../Stratego/templates/" +
               view_.askFile("File not found, please retry!");
    }
}
void Controller::initPlayerBoardManually(int player)
{
    const std::map<Pieces, int> piecesCount{
        {Pieces::MARECHAL, 1},
        {Pieces::GENERAL, 1},
        {Pieces::COLONEL, 2},
        {Pieces::MAJOR, 3},
        {Pieces::COMMANDANT, 4},
        {Pieces::LIEUTENANT, 4},
        {Pieces::SERGENT, 4},
        {Pieces::DEMINEUR, 5},
        {Pieces::ECLAIREUR, 8},
        {Pieces::ESPIONNE, 1},
        {Pieces::DRAPEAU, 1},
        {Pieces::BOMBE, 6}
    };

    while (!this->game_.isPlayerBoardFull(
                player)) {
        for (auto const & piece : piecesCount) {
            for (size_t cnt {0}; cnt < piece.second; cnt++) {
                Position pos =
                    view_.askPosition("Please enter a position for piece with value: " +
                                      std::to_string(piece.first));
                if (this->game_.isPiece(pos)) {
                    cnt--;
                    cerr << "Position already taken, please retry !" << endl;
                }
                this->game_.addPiece(Piece(piece.first,
                                           player), pos);
                view_.printGame(game_);

            }
        }
    }
}


