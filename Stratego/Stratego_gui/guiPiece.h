#ifndef GUIPIECE_H
#define GUIPIECE_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class GuiBoard;
class PieceBox;
/**
 * @brief The GuiPiece class used to represent the pieces graphically
 * Images have been retrieved from : http://vector.gissen.nl/stratego.html
 */
class GuiPiece : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
  public:
    /**
     * @brief GuiPiece constructor for the graphical pieces
     * @param player given owner of the piece
     * @param pieceName given name of the piece
     * @param parent parent object
     */
    GuiPiece(int player, QString pieceName, GuiBoard * parent);
    /**
     * @brief setCurrentBox places a piece inside a box
     * @param box given box
     */
    void setCurrentBox(PieceBox * box);
    /**
     * @brief getPlayer getter for the player attribute
     * @return given player
     */
    int getPlayer();
    /**
     * @brief setImage sets the image for the piece
     * player 0 = blue
     * player 1 = red
     * @param pieceName given piece name
     */
    void setImage(QString pieceName);
    /**
     * @brief disableEvents disabled the events of the current piece
     */
    void disableEvents();
    /**
     * @brief resetPosition resets the position of the current piece to its initial position
     */
    void resetPosition();
  private:
    // private attributes

    /**
     * @brief currentBox box in which the piece is
     */
    PieceBox * currentBox;
    /**
     * @brief initPos initial position of the piece
     * used to reset the piece's position after a failed move
     */
    QPointF initPos;
    /**
     * @brief player owner of the piece
     */
    int player;

  private:
    // private methods

    /**
     * @brief mousePressEvent when a piece is clicked, sends a signal to the board
     * @param event mouse press event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    /**
     * @brief mouseMoveEvent when the mouse is moving (after clicking a piece)
     * updates the position of the piece in order to follow the cursor
     * @param event mouse move event
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    /**
     * @brief mouseReleaseEvent when the mouse is released (after clicking and moving a piece)
     * emits a signal to the board with the position of the box in which the mouse has been released
     * @param event mouse release event
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

  signals:
    /**
     * @brief sendClickedBoxToBoard sends the box on which the user has clicked to the board.
     * @param box clicked box
     */
    void sendClickedBoxToBoard(PieceBox * box);
    /**
     * @brief sendDestinationBoxToBoard sends the position of the box on which the mouse click was released to board
     * @param pos position on which the mouse click was released
     */
    void sendDestinationBoxToBoard(QPoint & pos);



};

#endif // GUIPIECE_H
