#include <QFileDialog>
#include <QMessageBox>

#include "widget.h"
#include "guiUtils.h"
#include "ui_widget.h"
#include "gameView.h"

// changes page to the game
void Widget::on_btnStart_clicked()
{
    if (ui->cbCheatMode->checkState() == Qt::Checked) {
        this->game_ = new Game(true);
    }
    else {
        this->game_ = new Game(false);
    }

    GameView * gameView = new GameView(*game_, ui->gamePage);
    gameView->start();
    // if template checked -> ask for a file
    // else: let user place his pieces
    if (ui->cbTemplateP1->checkState() == Qt::Checked) {
        initPlayerBoardTemplate(this, *game_, game_->getCurrentPlayer());

    }
    else {
        gameView->defaultInit(game_->getCurrentPlayer());
    }
    game_->nextPlayer();
    if (ui->cbTemplateP2->checkState() == Qt::Checked) {
        initPlayerBoardTemplate(this, *game_, game_->getCurrentPlayer());
    }
    else {
        gameView->defaultInit(game_->getCurrentPlayer());
    }

    ui->stackedWidget->setCurrentIndex(1);

    // creates the game view with pieces placed inside the gamePage
    gameView->show();
}

// quits the application
void Widget::on_btnQuit_clicked()
{
    Widget::close();
}
