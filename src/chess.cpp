#include <../include/chess.h>

Chessboard newBoard() {
    Chessboard board = {{
        {-5, -3, -4, -10, -255, -4, -3, -5},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 0,  0,  0,  0,  0,  0,  0,  0},
        { 1,  1,  1,  1,  1,  1,  1,  1},
        { 5,  3,  4,  10, 255,  4,  3,  5}
    }};
    return board;
}

std::pair<int, int> getIndex(std::string& square) {
    // Check if input is size two
    if (square.length() != 2)
        throw std::range_error("A-H, 1-8");

    // Change input to all lowercase
    std::transform(square.begin(), square.end(), square.begin(), ::toupper);

    // Calculate the rows index
    int row = square[0] - 'A';

    // Calculate the columns index
    int column = (int)square[1];

    // if the rows and columns are valid
    if (row >= 0 && row <= 8 && column > 0 && column < 9){
        return std::make_pair(row, column);
    } else {
        // else throw range error and exit
        throw std::range_error("A-H, 1-8");
        exit(EXIT_FAILURE);
    }
}
