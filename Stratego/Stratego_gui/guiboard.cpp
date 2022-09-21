#include "guiboard.h"
#include "piecebox.h"
#include "gameView.h"

GuiBoard::GuiBoard(GameView * view, int x, int y,
                   Game * subject) :
    x(x),
    y(y),
    subject(subject),
    view(view)

{
    started = false;
    drawBoxes();
}
void GuiBoard::drawBoxes()
{
    const int SHIFT = 50;

    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            PieceBox * box = new PieceBox();
            box->setParent(this);
            this->boxes[row][col] = box;
            box->setRow(row);
            box->setCol(col);
            box->setPos(x + SHIFT * col, y + SHIFT * row);
        }
    }
    addBoardToScene();
    initWater();

}

void GuiBoard::reCreatePieces()
{
    GuiPiece * piece;
    PieceBox * box;
    const std::array<std::array<std::optional<Piece>, 10>, 10> & board =
        subject->getBoard();

    for (size_t row = 0; row < board.size(); row++) {
        for (size_t col = 0; col < board[row].size(); col++) {
            int player = board[row][col]->getPlayer();
            int pieceName = board[row][col]->getName();
            if (player != -1 && board[row][col].has_value()) {
                piece = new GuiPiece(player, QString::number(pieceName), this);
                box = boxes[row][col];
                box->setPiece(piece);
                this->view->addToScene(piece);
            }
        }
    }
}

void GuiBoard::defaultInit(int player)
{
    std::map<Pieces, int> piecesCount{
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

    const std::array<std::array<std::optional<Piece>, 10>, 10> & board =
        subject->getBoard();
    std::map<Pieces, int>::iterator it = piecesCount.begin();

    int count{};

    GuiPiece * p;
    int rowOffset{0};
    size_t maxRow{4};

    if (player == 1) {
        rowOffset = 6;
        maxRow = board.size();
    }

    for (size_t row = rowOffset; row < maxRow; row++) {
        for (size_t col = 0; col < board[row].size(); col++) {
            p = new GuiPiece(player, QString::number(it->first), this);
            boxes[row][col]->setPiece(p);
            this->subject->addPiece(Piece(it->first, player),
                                    Position(row, col));
            this->view->addToScene(p);
            count++;
            if (it->second == count) {
                it++;
                count = 0;
            }
        }
    }
    if (!this->subject->isCheatModeOn()) {
        hideOpponentPieces();
    }
}

void GuiBoard::initPieces(int player)
{
    GuiPiece * piece;
    PieceBox * box;
    const std::array<std::array<std::optional<Piece>, 10>, 10> & board =
        subject->getBoard();

    int rowOffset{0};
    size_t maxRow{4};

    if (player == 1) {
        rowOffset = 6;
        maxRow = board.size();
    }

    for (size_t row = rowOffset; row < maxRow; row++) {
        for (size_t col = 0; col < board[row].size(); col++) {
            int player = board[row][col]->getPlayer();
            int pieceName = board[row][col]->getName();
            if (player != -1) {
                piece = new GuiPiece(player, QString::number(pieceName), this);
                box = boxes[row][col];
                box->setPiece(piece);
                this->view->addToScene(piece);
            }
        }
    }
}

void GuiBoard::initWater()
{
    GuiPiece * piece;
    const std::array<std::array<std::optional<Piece>, 10>, 10> & board =
        subject->getBoard();

    for (size_t row = 4; row < 6; row++) {
        for (size_t col = 0; col < board[row].size(); col++) {
            int player = board[row][col]->getPlayer();
            if (player == -1) {
                int pieceName = board[row][col]->getName();
                PieceBox * box = boxes[row][col];
                piece = new GuiPiece(-1, QString::number(pieceName), this);
                box->setPiece(piece);
                this->view->addToScene(piece);
            }
        }
    }
}


void GuiBoard::addBoardToScene()
{
    for (auto const & arr : boxes) {
        for (auto const & box : arr) {
            this->view->addToScene(box);
        }
    }

}

void GuiBoard::resetPiecePosition(GuiPiece * p)
{
    p->resetPosition();
}

void GuiBoard::redrawBoard()
{
    for (auto const & arr : boxes) {
        for (auto const & box : arr) {
            if (box->containsPiece()) {
                this->view->removeFromScene(box->getCurrentPiece());
                delete box->getCurrentPiece();
            }
            this->view->removeFromScene(box);
            delete box;
        }
    }
    drawBoxes(); // re create & place boxes
    reCreatePieces(); // re create & place pieces
    if (!this->subject->isCheatModeOn() && !this->subject->isGameOver()) {
        hideOpponentPieces();
    }
}
void GuiBoard::disablePieces()
{
    for (auto const & arr : boxes) {
        for (auto const & box : arr) {
            if (box->containsPiece()) {
                box->getCurrentPiece()->disableEvents();
            }
        }
    }
}

void GuiBoard::disablePlayerPieces(int player)
{
    int row;
    int rowMax;
    if (player == 0) {
        row = 0;
        rowMax = 3;
    }
    else {
        row = 6;
        rowMax = this->boxes.size();
    }

    for (; row < rowMax; row++) {
        for (auto const & box : boxes[row]) {
            if (box->containsPiece()) {
                box->getCurrentPiece()->disableEvents();
            }
        }
    }
}

void GuiBoard::reEnablePieces()
{
    for (auto const & arr : boxes) {
        for (auto const & box : arr) {
            if (box->containsPiece()) {
                box->getCurrentPiece()->setEnabled(true);
            }
        }
    }
}

void GuiBoard::hideOpponentPieces()
{
    int currentPlayer = this->subject->getCurrentPlayer();
    for (auto const & arr : boxes) {
        for (auto const & box : arr) {
            if (box->containsPiece() &&
                    box->getCurrentPiece()->getPlayer() != -1) {
                if (box->getCurrentPiece()->getPlayer() != currentPlayer) {
                    box->getCurrentPiece()->setImage("hidden");
                }
            }
        }
    }
}

void GuiBoard::onPieceDrag(PieceBox * box)
{
    beforeMove = Position(box->getRow(), box->getCol());
}

void GuiBoard::onPieceDrop(QPoint & pos)
{
    QGraphicsItem * item = this->view->itemAt(pos);

    PieceBox * box = qgraphicsitem_cast<PieceBox *>(item);
    if (box != nullptr) {
        this->afterMove = Position(box->getRow(), box->getCol());
        if (this->started) {
            try {
                this->subject->move(beforeMove, afterMove);
                view->setErrorMsgText("");
            }
            catch (std::invalid_argument const & ex) {
                view->showError(ex.what());
                resetPiecePosition(
                    this->boxes[beforeMove.row_][beforeMove.col_]->getCurrentPiece());
            }
        }
        else {
            try {
                this->subject->swap(beforeMove, afterMove);
                view->setErrorMsgText("");
            }
            catch (std::invalid_argument const & ex) {
                view->showError(ex.what());
                resetPiecePosition(
                    this->boxes[beforeMove.row_][beforeMove.col_]->getCurrentPiece());
            }
        }
    }
    else {
        //prevents moving a piece outside of the boards
        resetPiecePosition(
            this->boxes[beforeMove.row_][beforeMove.col_]->getCurrentPiece());
    }
}

void GuiBoard::update(const Subject * subject,
                      const std::string & propertyName)
{
    if (this->subject == subject) {
        if (propertyName.compare("INIT") == 0) {
            initPieces(this->subject->getCurrentPlayer());
        }
        else if (propertyName.compare("SWAP") == 0) {
            redrawBoard();
        }
        else if (propertyName.compare("START") == 0) {
            this->started = true;
        }
        else if (propertyName.compare("MOVE") == 0) {
            redrawBoard();
            if (this->subject->isGameOver()) {
                disablePieces();
                view->showGameOver();
            }
        }
    }
}


