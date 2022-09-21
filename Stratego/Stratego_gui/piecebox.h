#ifndef PIECEBOX_H
#define PIECEBOX_H
#include <QGraphicsRectItem>
#include "guiPiece.h"

class GuiPiece;
/**
 * @brief The PieceBox class used to represent a box in which a piece can be played
 * (part of the board)
 */
class PieceBox : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
  public:
    /**
     * @brief PieceBox constructor
     * @param parent parent item
     */
    PieceBox();
    /**
     * @brief setPiece places a piece inside the current box
     * @param p given piece
     */
    void setPiece(GuiPiece * p);
    /**
     * @brief containsPiece  verifies whether the current box contains a piece
     * @return whether the current box contains a piece
     */
    bool containsPiece();
    /**
     * @brief getRow getter for the row attribute
     * @return row of the current box
     */
    int getRow();
    /**
     * @brief setRow setter for the current row of the box
     * @param row given row
     */
    void setRow(int row);
    /**
     * @brief getCol getter for the col attribute
     * @return column of the current box
     */
    int getCol();
    /**
     * @brief setCol setter for the current column of the box
     * @param col given col
     */
    void setCol(int col);

    /**
     * @brief getCurrentPiece getter for the piece in the current box
     * @return piece which is inside the current box
     */
    GuiPiece * getCurrentPiece();

  private:
    /**
     * @brief row given row for the box
     */
    int row;
    /**
     * @brief col given column for the box
     */
    int col;

    /**
     * @brief currentPiece piece which has been placed inside the current box, initialized at nullptr
     */
    GuiPiece * currentPiece;

};

#endif // PIECEBOX_H
