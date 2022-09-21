#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
class Keyboard
{
    /**
     * @brief lineFromKbd
     * Retrieves user input on a line,
     * stores every delimited element by a whitespace into a vector
     * @return vector containing each element separated by a whitespace
     */
public :
    static std::vector<string> lineFromKbd()
    {
        string inputLine;
        string token;

        std::getline(std::cin, inputLine);
        std::stringstream s(inputLine);

        std::vector<string> inputs;
        while (getline(s, token, ' ')) {
            inputs.push_back(token);
        }
        return inputs;
    }


};
#endif // KEYBOARD_H
