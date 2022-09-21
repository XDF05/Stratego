#include <QFileDialog>
#include <QMessageBox>

#include "utils.h"
#include "guiUtils.h"
#include "widget.h"

QString askFile(QWidget * parent, int player)
{
    QString filename = QFileDialog::getOpenFileName(parent,
                       "Select the template", "../../Stratego/templates/");
    QString title = "Player " + QString::number(player + 1);
    return filename;
}
void initPlayerBoardTemplate(QWidget * parent, Game & game,
                             int player)
{
    bool success;
    QString filename;
    QString title = "Player " + QString::number(player);
    do {
        filename = askFile(parent, player);
        success = readFile(filename.toStdString(), game, player);
        if (!success) {
            QMessageBox::information(parent, title, "Failed opening the file.");
        }
    }
    while (!success);

    QMessageBox::information(parent, title, filename);

}
