#include <../include/chess.h>

Movemaps createPossibleMovesMap() {
    Movemaps movesMap;

    // // Create moves for pawn
    // movesMap[PAWN] = {{0, 1}, {1, 1}, {-1, 1}};
    // movesMap[-PAWN] = {{0, -1}, {1, -1}, {-1, -1}};

    // Create moves for rook
    movesMap[ROOK] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    movesMap[-ROOK] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // Create moves for knight
    movesMap[KNIGHT] = {{1, 2}, {-1, 2}, {2, 1}, {-2, 1},
                        {2, -1}, {-2, -1}, {-1, -2}, {1, -2}};
    movesMap[-KNIGHT] = {{1, 2}, {-1, 2}, {2, 1}, {-2, 1},
                         {2, -1}, {-2, -1}, {-1, -2}, {1, -2}};

    // Create moves for bishop
    movesMap[BISHOP] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    movesMap[-BISHOP] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    // Create moves for queen
    movesMap[QUEEN] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0},
                       {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    movesMap[-QUEEN] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0},
                        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    // Create moves for king
    movesMap[KING] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0},
                      {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    movesMap[-KING] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0},
                       {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    return movesMap;
}

ChessPiece createPawn(bool isWhite) {
    int identity = isWhite ? PAWN : -PAWN;
    char* exhibit = const_cast<char*>(isWhite ? K_WHITE(C_PAWN) : K_BLACK(C_PAWN));
    int weight = PAWN;
    return {identity, weight, exhibit, false};
}

ChessPiece createRook(bool isWhite) {
    int identity = isWhite ? ROOK : -ROOK;
    char* exhibit = const_cast<char*>(isWhite ? K_WHITE(C_ROOK) : K_BLACK(C_ROOK));
    int weight = ROOK; 
    return {identity, weight, exhibit, false};
}

ChessPiece createKnight(bool isWhite) {
    int identity = isWhite ? KNIGHT : -KNIGHT;
    char* exhibit = const_cast<char*>(isWhite ? K_WHITE(C_KNIGHT) : K_BLACK(C_KNIGHT));
    int weight = KNIGHT;
    return {identity, weight, exhibit, false};
}

ChessPiece createBishop(bool isWhite) {
    int identity = isWhite ? BISHOP : -BISHOP;
    char* exhibit = const_cast<char*>(isWhite ? K_WHITE(C_BISHOP) : K_BLACK(C_BISHOP));
    int weight = BISHOP;
    return {identity, weight, exhibit, false};
}

ChessPiece createQueen(bool isWhite) {
    int identity = isWhite ? QUEEN : -QUEEN;
    char* exhibit = const_cast<char*>(isWhite ? K_WHITE(C_QUEEN) : K_BLACK(C_QUEEN));
    int weight = QUEEN;
    return {identity, weight, exhibit, false};
}

ChessPiece createKing(bool isWhite) {
    int identity = isWhite ? KING : -KING;
    char* exhibit = const_cast<char*>(isWhite ? K_WHITE(C_KING) : K_BLACK(C_KING));
    int weight = KING;
    return {identity, weight, exhibit, false};
}

// Create a new board with all pieces
Chessboard newBoard() {
    Chessboard board;

    // Place white pieces
    board[0][0] = createRook(false);
    board[0][1] = createKnight(false);
    board[0][2] = createBishop(false);
    board[0][3] = createQueen(false);
    board[0][4] = createKing(false);
    board[0][5] = createBishop(false);
    board[0][6] = createKnight(false);
    board[0][7] = createRook(false);

    // Place white pawns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[1][i] = createPawn(false);
    }

    // Place black pawns
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[6][i] = createPawn(true);
    }
    // Place black pieces
    board[7][0] = createRook(true);
    board[7][1] = createKnight(true);
    board[7][2] = createBishop(true);
    board[7][3] = createQueen(true);
    board[7][4] = createKing(true);
    board[7][5] = createBishop(true);
    board[7][6] = createKnight(true);
    board[7][7] = createRook(true);

    // Place empty squares
    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = {EMPTY, 0, C_EMPTY, false};
        }
    }

    return board;
}

Moves getAvailableMoves(Chessboard& Board, Movemaps& Map, std::string Square) {
    Coordinates location = AddresstoIndex(Square);
    int x = location.first;
    int y = location.second;
    ChessPiece piece = Board[x][y];
    Moves availableMoves;

    if ( piece.identity == PAWN ) {

        int temp_x = x;
        int temp_y = y;
        
        ++temp_y;

        if ( Board[temp_x][temp_y].identity == EMPTY ) {
            availableMoves.push_back(std::make_pair(temp_x, temp_y));
            if ( !piece.moved ) {
                ++temp_y;
                if ( Board[temp_x][temp_y].identity == EMPTY ) {
                    availableMoves.push_back(std::make_pair(temp_x, temp_y));
                }
                --temp_y;
            }
        }

        if ( haveOppositeSign(piece.identity, Board[temp_x + 1][temp_y].identity) ) {
            availableMoves.push_back(std::make_pair(temp_x + 1, temp_y));
        }

        if ( haveOppositeSign(piece.identity, Board[temp_x - 1][temp_y].identity) ) {
            availableMoves.push_back(std::make_pair(temp_x - 1, temp_y));
        }

    } else if ( piece.identity == -PAWN ) {

        int temp_x = x;
        int temp_y = y;
        
        --temp_y;

        if ( Board[temp_x][temp_y].identity == EMPTY ) {
            availableMoves.push_back(std::make_pair(temp_x, temp_y));
            if ( !piece.moved ) {
                --temp_y;
                if ( Board[temp_x][temp_y].identity == EMPTY ) {
                    availableMoves.push_back(std::make_pair(temp_x, temp_y));
                }
                ++temp_y;
            }
        }

        if ( haveOppositeSign(piece.identity, Board[temp_x + 1][temp_y].identity) ) {
            availableMoves.push_back(std::make_pair(temp_x + 1, temp_y));
        }

        if ( haveOppositeSign(piece.identity, Board[temp_x - 1][temp_y].identity) ) {
            availableMoves.push_back(std::make_pair(temp_x - 1, temp_y));
        }

    } else if ( piece.identity == ROOK ) {

    } else if ( piece.identity == -ROOK ) {

    } else if ( piece.identity == KNIGHT ) {

    } else if ( piece.identity == -KNIGHT ) {

    } else if ( piece.identity == BISHOP ) {

    } else if ( piece.identity == -BISHOP ) {

    } else if ( piece.identity == QUEEN ) {

    } else if ( piece.identity == -QUEEN ) {

    } else if ( piece.identity == KING ) {

    } else if ( piece.identity == -KING ) {

    } else {

    }

    return availableMoves;
}

// Translate a square's name to a pair of indices that refers to rows and columns
Coordinates AddresstoIndex(std::string& square) {
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

// Check if x is in bound of board size
bool inBound(int x) {
    return 0 <= x && x <= BOARD_SIZE;
}

bool haveOppositeSign(int x, int y) {
    // Check if one number is negative and the other is positive or vice versa
    return (x < 0 && y > 0) || (x > 0 && y < 0);
}

// Function to print the chessboard
void printBoard(const Chessboard& board) {
    // Print the column labels
    std::cout << "  ";
    for (char c = 'A'; c <= 'H'; ++c) {
        std::cout << std::setw(4) << c;
    }
    std::cout << std::endl;

    // Print the top border
    std::cout << std::setw(4) << "+";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << std::setw(4) << "---+";
    }
    std::cout << std::endl;

    // Print each row
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << std::setw(2) << BOARD_SIZE - i << " |"; // Row label

        for (int j = 0; j < BOARD_SIZE; ++j) {
            std::cout << " " << board[i][j].exhibit << " |"; // Exhibit
        }

        std::cout << std::endl;

        // Print the border between rows
        std::cout << std::setw(4) << "+";
        for (int k = 0; k < BOARD_SIZE; ++k) {
            std::cout << std::setw(4) << "---+";
        }
        std::cout << std::endl;
    }
}