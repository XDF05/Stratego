#include <QPainter>
#include <QPixmap>
#include <QGraphicsColorizeEffect>

#include "guiPiece.h"
#include "guiboard.h"

GuiPiece::GuiPiece(int player, QString pieceName,
                   GuiBoard * parent)
    : player(player)
{
    setParent(parent);
    setImage(pieceName);
    this->setZValue(1);
    connect(this, SIGNAL(sendClickedBoxToBoard(PieceBox *)), parent,
            SLOT(onPieceDrag(PieceBox *)));


    connect(this, SIGNAL(sendDestinationBoxToBoard(QPoint &)),
            parent,
            SLOT(onPieceDrop(QPoint &)));
}

void GuiPiece::setCurrentBox(PieceBox * box)
{
    this->currentBox = box;
    this->initPos = this->pos();
}
int GuiPiece::getPlayer()
{
    return this->player;
}

void GuiPiece::setImage(QString pieceName)
{
    setPixmap(QPixmap(":/" + pieceName));
    // colors the image according to the owner of the piece
    // 0 = blue
    // 1 = red
    QGraphicsColorizeEffect * effect = new QGraphicsColorizeEffect;
    switch (player) {
        case -1:
            effect->setColor(Qt::cyan);
            break;
        case 0:
            effect->setColor(Qt::blue);
            break;
        case 1:
            effect->setColor(Qt::red);
            break;
        default:
            effect->setColor(Qt::black);

    }
    effect->setStrength(1);
    setGraphicsEffect(effect);
}

void GuiPiece::disableEvents()
{
    this->setEnabled(false);
}

void GuiPiece::resetPosition()
{
    this->setPos(this->initPos);
}

void GuiPiece::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if (this->player != -1) {
        emit sendClickedBoxToBoard(this->currentBox);
    }
}
void GuiPiece::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    if (this->player != -1) {
        this->setPos( event->scenePos());
    }
}

void GuiPiece::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    QPoint p = QPoint();
    p.setX(event->scenePos().x());
    p.setY(event->scenePos().y());
    emit sendDestinationBoxToBoard(p);
}
