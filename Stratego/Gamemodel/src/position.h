#ifndef POSITION_H
#define POSITION_H

/**
 * @brief Position used to access an element inside an array
 */
struct  Position { //struct
    /**
     * @brief row_ row in which a piece is located on the Board
     */
    unsigned row_;
    /**
     * @brief col_ col in which a piece is located on the Board
     */
    unsigned col_;

    /**
     * @brief Position Constructor for a position
     * creates a position(0,0) if no parameters are given
     * @param row given row
     * @param col given column
     */
    Position(int row = 0, int col = 0) : row_(row), col_(col) {}
};
#endif // POSITION_H
