#include <QGraphicsProxyWidget>

#include "gameView.h"
#include "piecebox.h"

GameView::GameView(Game & game,
                   QWidget * parent): QGraphicsView(parent), game(game)
{

    // creating Scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1280, 768);
    this->setParent(parent);
    setAttribute(Qt::WA_DeleteOnClose);

    // setting up view
    setFixedSize(1280, 768);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(scene);

    //create confirm placement button for each player

    //p1
    btnConfirmP1 = new QPushButton("Confirm");
    scene->addWidget(btnConfirmP1);
    btnConfirmP1 ->setGeometry(QRect((width() / 2 - 50), 50,
                                     100,
                                     30));
    //p2
    btnConfirmP2 = new QPushButton("Confirm");
    scene->addWidget(btnConfirmP2);
    btnConfirmP2->setGeometry(QRect((width() / 2 - 50),
                                    height() - 50 - 30,
                                    100,
                                    30));
    //create start button
    btnStart = new QPushButton("START");
    scene->addWidget(btnStart);
    btnStart->setGeometry(QRect((width() / 2) - 50, (height() / 2 - 25),
                                100,
                                50));

    //create and add the error message label on the game panel
    lErrorMessage = new QGraphicsTextItem();
    this->scene->addItem(lErrorMessage);
    connectAll();
}

void GameView::start()
{
    board = new GuiBoard(this, width() / 2 - 250,
                         (this->height() / 2 - 250), &game);
    game.addObserver(board);
}

void GameView::defaultInit(int player)
{
    this->board->defaultInit(player);
}
void GameView::addToScene(QGraphicsItem * item)
{
    scene->addItem(item);
}

void GameView::removeFromScene(QGraphicsItem * item)
{
    scene->removeItem(item);
}

void GameView::connectAll()
{
    QObject::connect(btnConfirmP1, SIGNAL(clicked()), this,
                     SLOT(confirmP1()));

    QObject::connect(btnConfirmP2, SIGNAL(clicked()), this,
                     SLOT(confirmP2()));

    QObject::connect(btnStart, SIGNAL(clicked()), this,
                     SLOT(startGame()));
}

void GameView::showGameOver()
{
    QString winner = (game.getCurrentPlayer() == 0) ? "Red" : "Blue";
    lGameOver = new QGraphicsTextItem("Game Over!\nWinner: " + winner);
    QFont gameOverFont("arial", 20);
    lGameOver->setFont(gameOverFont);
    lGameOver ->setPos((width() / 2 - 75), 50);
    this->scene->addItem(lGameOver);

}

void GameView::showError(QString errorMsg)
{
    lErrorMessage->setPlainText(errorMsg);

    lErrorMessage->setDefaultTextColor(Qt::red);
    QFont gameOverFont("arial", 13);

    lErrorMessage->setFont(gameOverFont);
    lErrorMessage->setPos((width() - 350), height() / 2);

}

void GameView::setErrorMsgText(QString errorMsg)
{
    lErrorMessage->setPlainText(errorMsg);
}

void GameView::startGame()
{
    if (!this->btnConfirmP1->isEnabled() && !btnConfirmP2->isEnabled()) {
        //GraphcisProxyWidget is necessary because btn's are QWidgets and are not QGraphicsItems

        scene->removeItem(this->btnConfirmP1->graphicsProxyWidget());
        scene->removeItem(this->btnConfirmP2->graphicsProxyWidget());
        scene->removeItem(this->btnStart->graphicsProxyWidget());
        delete this->btnConfirmP1;
        delete this->btnConfirmP2;
        delete this->btnStart;

        if (game.getCurrentPlayer() == 0) {
            game.nextPlayer();
        }
        this->board->reEnablePieces();
        this->game.start();
    }
}

void GameView::confirmP1()
{
    if (this->game.getCurrentPlayer() == 0) {
        this->btnConfirmP1->setDisabled(true);
        game.nextPlayer();
        board->redrawBoard();
        this->board->disablePlayerPieces(game.getCurrentPlayer());
    }
}

void GameView::confirmP2()
{
    if (this->game.getCurrentPlayer() == 1) {
        this->btnConfirmP2->setDisabled(true);
        game.nextPlayer();
        board->redrawBoard();
        this->board->disablePlayerPieces(game.getCurrentPlayer());
    }
}
