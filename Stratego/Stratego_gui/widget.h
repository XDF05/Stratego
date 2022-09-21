#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    Game * game_;
    Ui::Widget * ui;

  public:
    Widget(QWidget * parent = nullptr);
    ~Widget();

  private:
    /**
     * @brief start starts the game
     */
    void start();

  private slots:
    /**
     * @brief on_btnStart_clicked slot for the start button inside the main menu
     * If the player asked to use a template,
     * Asks the him for a template file and initializes its board
     *
     * If the player wants to manualy place his pieces,
     * Opens a window that asks the user to place his pieces
     *
     */
    void on_btnStart_clicked();
    /**
     * @brief on_btnQuit_clicked slot for the quit button inside the main menu
     * Closes the application
     */
    void on_btnQuit_clicked();

};
#endif // WIDGET_H
