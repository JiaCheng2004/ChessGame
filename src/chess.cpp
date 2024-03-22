#include <../include/chess.h>

// Create a new board with all pieces
Chessboard newBoard() {
    Chessboard board = {{
        {-ROOK, -KNIGHT, -BISHOP, -QUEEN, -KING, -BISHOP, -KNIGHT, -ROOK},
        {-PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN},
        {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK}
    }};

    // Initialize all the board piece to unmoved
    for (int i = 0; i < 8; i++) {
        setUnmoved(board[i][0]);
        setUnmoved(board[i][1]);
        setUnmoved(board[i][6]);
        setUnmoved(board[i][7]);
    }

    return board;
}

// Check if x is in bound of board size
bool inBound(int x) {
    return 0 <= x && x <= BOARD_SIZE;
}

// Check if y has the opposite sign of x
bool hasOppositeSign(int x, int y) {
    return x * y < 0;
}

// Perform a bit wise OR to set the piece's 10th bit to 1 (unmoved)
void setUnmoved(int16_t& piece) {
    piece |= 1 << 10;
}

// Perform a bit wise AND to check if the piece's 10th bit is 1 (unmoved)
bool getUnmoved(int16_t piece) {
    return (piece & (1 << 10)) != 0;
}

// Translate a square's name to a pair of indices that refers to rows and columns
std::pair<int, int> AddresstoIndex(std::string& square) {
    // Check if input is size two
    if (square.length() != 2)
        throw std::range_error("Only rows and colum [A-H][1-8]");

    // Change input to all uppercase
    std::transform(square.begin(), square.end(), square.begin(), ::toupper);

    // Calculate the columns index
    int column = square[0] - 'A';

    // Calculate the rows index
    int row = square[1] - '1';

    // if the rows and columns are valid
    if (inBound(row) && inBound(column)){
        return std::make_pair(row, column);
    } else {
        // else throw range error and exit
        throw std::range_error("Row must be A-H, and Column must be 1-8");
        exit(EXIT_FAILURE);
    }
}

// Get all the possible moves, except for Bishop, Rook, and Queen where it return all the directions
std::vector<std::pair<int, int>> allPossibleMoves(int& piece) {

    // initialize a vector to contain all the moves
    std::vector<std::pair<int, int>> moves;

    // Check which piece's move
    switch (piece) {
        // Nothing, zero means empty square
        case EMPTY:
            break;
        
        // All possible move for White Pawn
        case PAWN:
            moves.push_back(std::make_pair(0, 1));
            moves.push_back(std::make_pair(0, 2));
            moves.push_back(std::make_pair(1, 1));
            moves.push_back(std::make_pair(-1, 1));
            break;

        // All possible move for Black Pawn
        case -PAWN:
            moves.push_back(std::make_pair(0, -1));
            moves.push_back(std::make_pair(0, -2));
            moves.push_back(std::make_pair(1, -1));
            moves.push_back(std::make_pair(-1, -1));
            break;

        // All possible moves for Knights
        case KNIGHT:
        case -KNIGHT:
            moves.push_back(std::make_pair(1, 2));
            moves.push_back(std::make_pair(-1, 2));
            moves.push_back(std::make_pair(2, 1));
            moves.push_back(std::make_pair(-2, 1));
            moves.push_back(std::make_pair(2, -1));
            moves.push_back(std::make_pair(-2, -1));
            moves.push_back(std::make_pair(-1, -2));
            moves.push_back(std::make_pair(1, -2));   
            break;

        // All possible moves directions for Bishops
        case BISHOP:
        case -BISHOP:
            moves.push_back(std::make_pair(1, 1));
            moves.push_back(std::make_pair(1, -1));
            moves.push_back(std::make_pair(-1, 1));
            moves.push_back(std::make_pair(-1, -1));
            break;

        // All possible moves directions for Rooks
        case ROOK:
        case -ROOK:
            moves.push_back(std::make_pair(0, 1));
            moves.push_back(std::make_pair(1, 0));
            moves.push_back(std::make_pair(0, -1));
            moves.push_back(std::make_pair(-1, 0));
            break;

        // All possible moves directions for Queens
        case QUEEN:
        case -QUEEN:
            moves.push_back(std::make_pair(1, 1));
            moves.push_back(std::make_pair(1, -1));
            moves.push_back(std::make_pair(-1, 1));
            moves.push_back(std::make_pair(-1, -1));
            moves.push_back(std::make_pair(0, 1));
            moves.push_back(std::make_pair(1, 0));
            moves.push_back(std::make_pair(0, -1));
            moves.push_back(std::make_pair(-1, 0));
            break;

        // All possible moves directions for King
        case KING:
        case -KING:
            moves.push_back(std::make_pair(1, 1));
            moves.push_back(std::make_pair(1, -1));
            moves.push_back(std::make_pair(-1, 1));
            moves.push_back(std::make_pair(-1, -1));
            moves.push_back(std::make_pair(0, 1));
            moves.push_back(std::make_pair(1, 0));
            moves.push_back(std::make_pair(0, -1));
            moves.push_back(std::make_pair(-1, 0));
            break;

        // Got a value outside the game board
        default:
            throw std::range_error("THE FUCK?");   
    }
    return moves;
}

// Get all the moves of the selected square
std::vector<std::pair<int, int>> getMoves(Chessboard& Board, std::pair<int, int> square) {

    // Get the column index
    int x = square.first;

    // Get the row index
    int y = square.second;

    // Initialize the vector that will contain all the valid moves
    std::vector<std::pair<int, int>> moves;

    // Get the value of the piece at the square
    int piece = Board[x][y];

    // Get the absolute value of the piece at the square
    int piece_identiy = abs(Board[x][y]);

    // If the piece is an empty square
    if (piece == 0){ 
        // return an empty vector meaning no moves are available
        return moves;
    }

    // If the piece is any of the sliding pieces
    if (piece_identiy == BISHOP || piece_identiy == ROOK || piece_identiy == QUEEN) {

        // Loop through all the possible directions the piece can go
        for (std::pair<int, int>& move : allPossibleMoves(piece)) {

            // Set a temperary copy of x varaible
            int temp_x = x;

            // Set a temperary copy of y varaible
            int temp_y = y;
            
            // Loop until reached a piece or the boundary
            while (true) {
                // Change the value of temp_x and temp_y based on the direction
                temp_x += move.first;
                temp_y += move.second;

                // Check if now temp_x and temp_y is in bound or a valid game position
                if (!(inBound(temp_x) && inBound(temp_y)))
                    // break or give up the iteration if true
                    break;
                
                // Check if this new square is an empty equare (0) or opponent piece that can be captured
                if (Board[temp_x][temp_y] == EMPTY || hasOppositeSign(piece, Board[temp_x][temp_y])) {
                    // If so, add the position to the valid move container
                    moves.push_back(std::make_pair(temp_x, temp_y));
                    break;
                }
            }
        }
    } 
    // Else if the piece is a non-sliding piece
    else if (piece_identiy == KNIGHT) {
        // Iterate through all the possible moves of that piece
        for (std::pair<int, int>& move : allPossibleMoves(piece)) {
            // calculate for the new position after moving
            int temp_x = x + move.first;
            int temp_y = y + move.second;

            // Check if the new position is outside the board
            if (!(inBound(temp_x) && inBound(temp_y)))
                // If outside the board, ignore and continue
                continue;
            
            // Check if the new position is empty(0) or opponent piece that can be captured
            if (Board[temp_x][temp_y] == EMPTY || hasOppositeSign(piece, Board[temp_x][temp_y]))
                // If so, add the position to the valid move container
                moves.push_back(std::make_pair(temp_x, temp_y));
        }
    }
    // Else if we're encountering a king
    else if (piece_identiy == KING) {
        
    }
    // Else if encountering a pawn
    else {
        bool blocking = false;
        
    }

    return moves;
}