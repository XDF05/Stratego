#ifndef VIEWCONSOLE_H
#define VIEWCONSOLE_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include <game.h>

using std::cerr;
using std::endl;
class ViewConsole
{

  public:
    /**
     * @brief ViewConsole controller for the console view
     */
    ViewConsole();
    /**
     * @brief askFile Asks the current player for a file to read
     * @param message message displayed when asking the user for a file
     * @return file name
     */
    std::string askFile(std::string message);
    /**
     * @brief askUseFile asks the current player whether he wants to use a template file or not
     * valid input (y/n)
     * @param player current player
     * @return whether the current player wants to use a template file
     */
    bool askUseFile(int player);
    /**
     * @brief askPosition asks the user for a position
     * valid input  (row[1-10] col[A-J]
     * @param message displayed message when asking the user for the input
     * @return given position by the current player
     */
    Position askPosition(std::string message);

    bool askYesOrNo(std::string msg);

    bool askCheatMode();
    /**
     * @brief printGame prints the board of a game
     * @param game given instance of the game
     */
    void printGame(Game & game);

    /**
     * @brief printWinner prints the winner of the game
     * @param game finished game.
     */
    void printWinner(Game & game);

    void askNextPlayer();
  private:
    /**
     * @brief clear clears the terminal
     */
    void clear()
    {
        printf("\033c");
    }
    /**
     * @brief inRange verifies whether a given x is inside a range
     * @param low lowest accepted value
     * @param high highest accepted value
     * @param x given integer
     * @return whether x is inside the range
     */
    bool inRange(int low, int high, int x)
    {
        return ((x - high) * (x - low) <= 0);
    }
    /**
     * @brief isValidPos verifies whether a given entered position by the player is valid
     * @param inputs given input by the user
     * @return whether the input entered by the user is valid
     */
    bool isValidPos(std::vector<std::string> inputs)
    {
        std::string allowedCol =
            "ABCDEFGHIJ"; //pattern of allowed positions for col
        int row{};
        char col{};
        if (inputs.size() == 2) {
            std::stringstream stream(inputs.at(0));
            if (stream >> row) {
                if (!inRange(1, 10, row)) {
                    cerr << "row value is not inside!" << endl;
                    return false;
                }
                stream = std::stringstream(inputs.at(1));
                stream.get(col);
                col = std::toupper(col); //sets char to upperCase
                if ((allowedCol.find(col) ==
                        std::string::npos)) {
                    cerr << "Invalid col, please retry! " << endl;
                    return false;
                }
            }
            else {
                cerr << "Invalid row, please retry! " << endl;
                return false;
            }
        }
        else {
            cerr << "Invalid amount of parameters for a position! " << endl;
            return false;
        }
        return true;
    }

};

#endif // VIEWCONSOLE_H
