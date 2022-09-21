#include "piecebox.h"

PieceBox::PieceBox()
{
    // setParent(parent);
    // create a square containing a piece;
    setRect(0, 0, 50, 50);
    // places the box on the back
    setZValue(-1);
    // holds no piece at first
    currentPiece = nullptr;
}

void PieceBox::setPiece(GuiPiece * p)
{
    //25 -> images height are 50px
    //17.5 -> images width are 35px
    p->setPos(x() + 25 - p->pixmap().width() / 2,
              y() + 17.5 - p->pixmap().width() / 2);
    p->setCurrentBox(this);
    currentPiece = p;
}

bool PieceBox::containsPiece()
{
    return currentPiece != nullptr;
}

int PieceBox::getCol()
{
    return this->col;
}

void PieceBox::setCol(int col)
{
    this->col = col;
}
int PieceBox::getRow()
{
    return this->row;
}
void PieceBox::setRow(int row)
{
    this->row = row;
}

GuiPiece * PieceBox::getCurrentPiece()
{
    return this->currentPiece;
}
