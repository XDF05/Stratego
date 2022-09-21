#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <string.h>

#include "game.h"

using std::cerr;
using std::cout;
using std::endl;
using std::array;
using std::optional;

using std::ifstream;
using std::string;

/**
 * @brief readFile asks a given player to read a template file and initialises its board
 * @param fileName name of the template file (including extension ex: .txt)
 * @param game instance of the game
 * @param player given player
 * @return whether the reading and initialisation of the game succeeded or not.
 */
bool readFile(std::string fileName, Game & game, int player)
{
    ifstream inFile;
    inFile.open(fileName);
    if (inFile.fail()) {
        return false;
    }

    array<array<optional<Piece>, 10>, 4> pieces;
    string line;

    int row{0};
    int col{0};

    string token;
    int val{};

    while (getline(inFile, line)) {
        std::stringstream s(line);
        while (getline(s, token, ' ')) {
            Pieces piece;
            std::stringstream stream(token);
            if (stream >> val) {
                switch (val) {
                    case 1:
                        piece = Pieces::ESPIONNE;
                        break;
                    case 2:
                        piece = Pieces::ECLAIREUR;
                        break;
                    case 3:
                        piece = Pieces::DEMINEUR;
                        break;
                    case 4:
                        piece = Pieces::SERGENT;
                        break;
                    case 5:
                        piece = Pieces::LIEUTENANT;
                        break;
                    case 6:
                        piece = Pieces::COMMANDANT;
                        break;
                    case 7:
                        piece = Pieces::MAJOR;
                        break;
                    case 8:
                        piece = Pieces::COLONEL;
                        break;
                    case 9:
                        piece = Pieces::GENERAL;
                        break;
                    case 10:
                        piece = Pieces::MARECHAL;
                        break;
                    default:
                        throw std::invalid_argument("file format not valid!");
                }
            }
            else {
                if (token.compare("D") == 0) {
                    piece = Pieces::DRAPEAU;
                }
                if (token.compare("B") == 0) {
                    piece = Pieces::BOMBE;
                }
            }
            pieces[row][col] = Piece(piece, player);
            col++;
        }
        row++;
        col = 0;
    }
    inFile.close();
    game.init(pieces);
    return true;
}


#endif // UTILS_H
