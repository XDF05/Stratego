#ifndef GUIUTILS_H
#define GUIUTILS_H
#include <QWidget>

#include "game.h"

/**
 * @brief askFile Creates a QFileDialog that asks for a file.
 * @param parent parent widget
 * @param player given player that asks for a file to be opened
 * @return Path to the given file
 */
QString askFile(QWidget * parent, int player);
/**
 * @brief initPlayerBoardTemplate initializes the player's board with a template file
 * @param parent parent widget
 * @param game Instance of the game
 * @param player player that asks to initialize its board with a template
 */
void initPlayerBoardTemplate(QWidget * parent, Game & game,
                             int player);
#endif // GUIUTILS_H
