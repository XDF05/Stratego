#include <stdio.h>
#include <cctype>

#include "viewConsole.h"
#include "keyboard.h"

using std::string;
using std::vector;
using std::endl;
using std::cout;
using std::cerr;
ViewConsole::ViewConsole() {}
void ViewConsole::printGame(Game & game)
{
    cout << game << endl;
}
void ViewConsole::printWinner(Game & game)
{
    cout << "The winner is: " << game.getWinner() << endl;
}
bool ViewConsole::askUseFile(int player)
{

    string s = "Player: " + std::to_string(player) +
               ", would you like to use a template?";
    return askYesOrNo(s);
}

bool ViewConsole::askCheatMode()
{
    return askYesOrNo("Would you like to use the cheat  mode?");
}

bool ViewConsole::askYesOrNo(std::string msg)
{
    char yesOrNo = '\0';
    std::vector<string> inputs;
    cout << msg << " (y/n)" << endl;
    do {
        inputs = Keyboard::lineFromKbd();
        if (inputs.size() != 1) {
            cerr << "Wrong amount of parameters received!" << endl;
            continue;
        }
        std::stringstream ss = std::stringstream(inputs.at(0));
        ss.get(yesOrNo);
        yesOrNo = std::tolower(yesOrNo);
        if (yesOrNo != 'y' && yesOrNo != 'n') {
            cout << "Wrong value, please enter y or n" << endl;
        }
    }
    while (inputs.size() != 1 || (yesOrNo != 'y' && yesOrNo != 'n'));
    return yesOrNo == 'y';

}

std::string ViewConsole::askFile(std::string message)
{
    std::vector<string> inputs;
    cout << message << endl;
    do {
        inputs = Keyboard::lineFromKbd();
        if (inputs.size() != 1) {
            cout << "Incorrect file name, please retry!" << endl;
        }
    }
    while (inputs.size() != 1);
    return inputs.at(0);

}


Position ViewConsole::askPosition(std::string message)
{
    int row {};
    char col{'\0'};
    std::vector<string> inputs;

    cout << message << endl;
    do {
        inputs = Keyboard::lineFromKbd();
    }
    while (!isValidPos(inputs));
    std::stringstream streamRow(inputs.at(0));
    streamRow >> row;

    std::stringstream streamCol = std::stringstream(inputs.at(1));
    streamCol.get(col);
    col = tolower(col);

    return Position(row - 1, col - 'a');
}
void ViewConsole::askNextPlayer()
{
    cout << "Enter any key to go to the next player!" << endl;
    Keyboard::lineFromKbd();
    clear();
}
