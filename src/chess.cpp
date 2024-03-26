#include <../include/chess.h>

Movemaps createPossibleMovesMap() {
    Movemaps movesMap;

    // Create moves for pawn
    movesMap[PAWN] = { { 0, 1 }, { 1, 1 }, { -1, 1 } };
    movesMap[-PAWN] = { { 0, -1 }, { 1, -1 }, { -1, -1 } };

    // Create moves for rook
    movesMap[ROOK] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
    movesMap[-ROOK] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

    // Create moves for knight
    movesMap[KNIGHT] = { { 1, 2 }, { -1, 2 }, { 2, 1 }, { -2, 1 }, { 2, -1 }, { -2, -1 },
        { -1, -2 }, { 1, -2 } };
    movesMap[-KNIGHT] = { { 1, 2 }, { -1, 2 }, { 2, 1 }, { -2, 1 }, { 2, -1 }, { -2, -1 },
        { -1, -2 }, { 1, -2 } };

    // Create moves for bishop
    movesMap[BISHOP] = { { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };
    movesMap[-BISHOP] = { { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };

    // Create moves for queen
    movesMap[QUEEN]
        = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }, { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };
    movesMap[-QUEEN]
        = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }, { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };

    // Create moves for king
    movesMap[KING]
        = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }, { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };
    movesMap[-KING]
        = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }, { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };

    return movesMap;
}

ChessPiece createPawn(bool isWhite) {
    int identity = isWhite ? PAWN : -PAWN;
    char *exhibit = const_cast<char *>(isWhite ? K_WHITE(C_PAWN) : K_BLACK(C_PAWN));
    int weight = PAWN;
    return { identity, weight, exhibit, false };
}

ChessPiece createRook(bool isWhite) {
    int identity = isWhite ? ROOK : -ROOK;
    char *exhibit = const_cast<char *>(isWhite ? K_WHITE(C_ROOK) : K_BLACK(C_ROOK));
    int weight = ROOK;
    return { identity, weight, exhibit, false };
}

ChessPiece createKnight(bool isWhite) {
    int identity = isWhite ? KNIGHT : -KNIGHT;
    char *exhibit = const_cast<char *>(isWhite ? K_WHITE(C_KNIGHT) : K_BLACK(C_KNIGHT));
    int weight = KNIGHT;
    return { identity, weight, exhibit, false };
}

ChessPiece createBishop(bool isWhite) {
    int identity = isWhite ? BISHOP : -BISHOP;
    char *exhibit = const_cast<char *>(isWhite ? K_WHITE(C_BISHOP) : K_BLACK(C_BISHOP));
    int weight = BISHOP;
    return { identity, weight, exhibit, false };
}

ChessPiece createQueen(bool isWhite) {
    int identity = isWhite ? QUEEN : -QUEEN;
    char *exhibit = const_cast<char *>(isWhite ? K_WHITE(C_QUEEN) : K_BLACK(C_QUEEN));
    int weight = QUEEN;
    return { identity, weight, exhibit, false };
}

ChessPiece createKing(bool isWhite) {
    int identity = isWhite ? KING : -KING;
    char *exhibit = const_cast<char *>(isWhite ? K_WHITE(C_KING) : K_BLACK(C_KING));
    int weight = KING;
    return { identity, weight, exhibit, false };
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
            board[i][j] = { EMPTY, EMPTY, C_EMPTY, false };
        }
    }

    return board;
}

Moves getAvailableMoves(Chessboard &Board, Movemaps &Map, std::string Square) {
    Coordinates location = AddresstoIndex(Square);
    int x = location.first;
    int y = location.second;
    ChessPiece piece = Board[x][y];
    Moves availableMoves;

    if (piece.weight == PAWN) {

        int temp_x = x;
        int temp_y = y;

        (piece.identity == PAWN) ? --temp_x : ++temp_x;

        if (Board[temp_x][temp_y].identity == EMPTY) {
            availableMoves.push_back(std::make_pair(temp_x, temp_y));
            if (!piece.moved) {
                (piece.identity == PAWN) ? --temp_x : ++temp_x;
                if (Board[temp_x][temp_y].identity == EMPTY) {
                    availableMoves.push_back(std::make_pair(temp_x, temp_y));
                }
                ++temp_x;
                (piece.identity == PAWN) ? ++temp_x : --temp_x;
            }
        }

        if (haveOppositeSign(piece.identity, Board[temp_x][temp_y + 1].identity)) {
            availableMoves.push_back(std::make_pair(temp_x, temp_y + 1));
        }

        if (haveOppositeSign(piece.identity, Board[temp_x][temp_y - 1].identity)) {
            availableMoves.push_back(std::make_pair(temp_x, temp_y - 1));
        }

    } else if (piece.weight == KNIGHT) {

        for (Coordinates &move : Map[piece.identity]) {
            int temp_x = x + move.first;
            int temp_y = y + move.second;

            if (inBound(temp_x) && inBound(temp_y)) {
                if (Board[temp_x][temp_y].identity == EMPTY
                    || haveOppositeSign(piece.identity, Board[temp_x][temp_y].identity))
                    availableMoves.push_back(std::make_pair(temp_x, temp_y));
            }
        }

    } else if (piece.weight == BISHOP || piece.weight == QUEEN || piece.weight == ROOK) {

        for (Coordinates &move : Map[piece.identity]) {
            int temp_x = x;
            int temp_y = y;

            while (true) {
                temp_x += move.first;
                temp_y += move.second;

                if (!inBound(temp_x) || !inBound(temp_y))
                    break;

                if (Board[temp_x][temp_y].identity == EMPTY) {
                    availableMoves.push_back(std::make_pair(temp_x, temp_y));
                    continue;
                }

                if (haveOppositeSign(piece.identity, Board[temp_x][temp_y].identity))
                    availableMoves.push_back(std::make_pair(temp_x, temp_y));
                break;
            }
        }

    } else if (piece.weight == KING) {

        if (!piece.moved) {
            int temp_x = x;
            int temp_y = y;

            while (true) {
                ++temp_x;

                if (!inBound(temp_x) || !inBound(temp_y))
                    break;

                if (Board[temp_x][temp_y].identity == EMPTY)
                    continue;

                if (Board[temp_x][temp_y].identity == ROOK
                    && !haveOppositeSign(piece.identity, Board[temp_x][temp_y].identity)
                    && !Board[temp_x][temp_y].moved) {

                    availableMoves.push_back(std::make_pair(temp_x, temp_y));
                    break;
                }
            }

            temp_x = x;

            while (true) {
                --temp_x;

                if (!inBound(temp_x) || !inBound(temp_y))
                    break;

                if (Board[temp_x][temp_y].identity == EMPTY)
                    continue;

                if (Board[temp_x][temp_y].identity == ROOK
                    && !haveOppositeSign(piece.identity, Board[temp_x][temp_y].identity)
                    && !Board[temp_x][temp_y].moved) {

                    availableMoves.push_back(std::make_pair(temp_x, temp_y));
                    break;
                }
            }

            temp_x = x;
        }

        for (Coordinates &move : Map[piece.identity]) {
            int temp_x = x + move.first;
            int temp_y = y + move.second;

            if (inBound(temp_x) && inBound(temp_y)) {
                if (Board[temp_x][temp_y].identity == EMPTY
                    || haveOppositeSign(piece.identity, Board[temp_x][temp_y].identity))
                    availableMoves.push_back(std::make_pair(temp_x, temp_y));
            }
        }
    } else {
        printConfusion();
    }

    return availableMoves;
}

// Translate a square's name to a pair of indices that refers to rows and
// columns
Coordinates AddresstoIndex(std::string &square) {
    // Check if input is size two
    if (square.length() != 2)
        throw std::range_error("Only rows and colum [A-H][1-8]");

    // Change input to all uppercase
    std::transform(square.begin(), square.end(), square.begin(), ::toupper);

    // Calculate the columns index
    int column = square[0] - 'A';

    // Calculate the rows index
    int row = 7 - (square[1] - '1');

    // if the rows and columns are valid
    if (inBound(row) && inBound(column)) {
        return std::make_pair(row, column);
    } else {
        // else throw range error and exit
        throw std::range_error("Row must be A-H, and Column must be 1-8");
        exit(EXIT_FAILURE);
    }
}

std::string IndextoAddress(Coordinates move) {
    std::stringstream ss;
    ss << (char) ('A' + move.second) << 8 - move.first;
    return ss.str();
}

Moves findPiece(Chessboard &board, int Identity) {
    Moves Location;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j].identity == Identity)
                Location.push_back(std::make_pair(i, j));
        }
    }

    return Location;
}

Weight getTotalWeight(Chessboard &board) {
    int white = 0;
    int black = 0;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j].identity == 0) {
                continue;
            } else if (board[i][j].identity > 0) {
                white += board[i][j].weight;
            } else {
                black -= board[i][j].weight;
            }
        }
    }

    // white on left black on right
    return std::make_pair(white, black);
}

Moves findAllPieces(Chessboard &board, bool White) {
    Moves allPieces;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((White && board[i][j].identity > 0) || (!White && board[i][j].identity < 0)) {
                allPieces.push_back(std::make_pair(i, j));
            }
        }
    }

    return allPieces;
}

bool isChecked(Chessboard &board, Movemaps Map, bool White) {
    Coordinates pos = White ? findPiece(board, KING)[0] : findPiece(board, -KING)[0];
    Moves OpponentPieces = White ? findAllPieces(board, -KING) : findAllPieces(board, KING);

    for (Coordinates &opponent : OpponentPieces) {
        Moves opponentMoves = getAvailableMoves(board, Map, IndextoAddress(opponent));
        for (Coordinates &move : opponentMoves) {
            if (move == pos) {
                return true;
            }
        }
    }
    return false;
}

// incomplete
bool isCheckmated(Chessboard &board, Movemaps Map, bool White) {
    //Check if currently is isChecked.
    if (!isChecked(board, Map, White)) {
        return false;
    }
    
    //Check next move for every pieces
    Moves OpponentPieces = White ? findAllPieces(board, -KING) : findAllPieces(board, KING);
    for (Coordinates &opponent : OpponentPieces) {
            Moves opponentMoves = getAvailableMoves(board, Map, IndextoAddress(opponent));
            for (Coordinates &move : opponentMoves) {
                Chessboard tempBoard = board;
                //move one time of every available move
                navigatePiece(tempBoard, opponent, move);
                // if there have one of available move is not been Checked, then it is not checkmate.
                if (!isChecked(tempBoard, Map, White)) {
                    return false;
                }
            }
        }
    return true;
}

void highlight(Chessboard &board, Moves moves) {
    for (Coordinates &move : moves) {
        switch (board[move.first][move.second].weight) {
        case EMPTY: board[move.first][move.second].exhibit = K_AVAILABLE(C_AVAILABLE); break;
        case PAWN: board[move.first][move.second].exhibit = K_AVAILABLE(C_PAWN); break;
        case ROOK: board[move.first][move.second].exhibit = K_AVAILABLE(C_ROOK); break;
        case BISHOP: board[move.first][move.second].exhibit = K_AVAILABLE(C_BISHOP); break;
        case KNIGHT: board[move.first][move.second].exhibit = K_AVAILABLE(C_KNIGHT); break;
        case QUEEN: board[move.first][move.second].exhibit = K_AVAILABLE(C_QUEEN); break;
        case KING: board[move.first][move.second].exhibit = K_AVAILABLE(C_KING); break;
        }
    }
}

void unhighlight(Chessboard &board, Moves moves) {
    for (Coordinates &move : moves) {
        switch (board[move.first][move.second].identity) {
        case EMPTY: board[move.first][move.second].exhibit = C_EMPTY; break;
        case PAWN: board[move.first][move.second].exhibit = K_WHITE(C_PAWN); break;
        case -PAWN: board[move.first][move.second].exhibit = K_BLACK(C_PAWN); break;
        case ROOK: board[move.first][move.second].exhibit = K_WHITE(C_ROOK); break;
        case -ROOK: board[move.first][move.second].exhibit = K_BLACK(C_ROOK); break;
        case BISHOP: board[move.first][move.second].exhibit = K_WHITE(C_BISHOP); break;
        case -BISHOP: board[move.first][move.second].exhibit = K_BLACK(C_BISHOP); break;
        case KNIGHT: board[move.first][move.second].exhibit = K_WHITE(C_KNIGHT); break;
        case -KNIGHT: board[move.first][move.second].exhibit = K_BLACK(C_KNIGHT); break;
        case QUEEN: board[move.first][move.second].exhibit = K_WHITE(C_QUEEN); break;
        case -QUEEN: board[move.first][move.second].exhibit = K_BLACK(C_QUEEN); break;
        case KING: board[move.first][move.second].exhibit = K_WHITE(C_KING); break;
        case -KING: board[move.first][move.second].exhibit = K_BLACK(C_KING); break;
        }
    }
}

bool existCoordinate(Moves &moves, const Coordinates location) {
    for (Coordinates &move : moves) {
        if (move == location)
            return true;
    }
    return false;
}

void navigatePiece(Chessboard &Board, Coordinates Origin, Coordinates Destination) {
    ChessPiece &o = Board[Origin.first][Origin.second];
    ChessPiece &d = Board[Destination.first][Destination.second];

    //When the pawn touch the wall, then PAWN change to QUEEN
    // if (o.identity == PAWN) {
    //     if (Destination.second == 7) {
    //         o.identity == QUEEN;
    //     }

    // } else if (o.identity == -PAWN) {
    //     if (Destination.second == 0) {
    //         o.identity == -QUEEN;
    //     }
    // }

    if (d.identity == EMPTY || haveOppositeSign(o.identity, d.identity)) {
        o.moved = true;
        d = o;
        o = { EMPTY, EMPTY, C_EMPTY, false };
    } else {
        o.moved = true;
        d.moved = true;
        if (Destination.second == 0) {
            Board[Origin.first][Origin.second - 2] = o;
            o = { EMPTY, EMPTY, C_EMPTY, false };
            Board[Destination.first][Destination.second + 3] = d;
            d = { EMPTY, EMPTY, C_EMPTY, false };
        } else {
            Board[Origin.first][Origin.second + 2] = o;
            o = { EMPTY, EMPTY, C_EMPTY, false };
            Board[Destination.first][Destination.second - 2] = d;
            d = { EMPTY, EMPTY, C_EMPTY, false };
        }
    }
}

// Check if x is in bound of board size
bool inBound(int x) {
    return 0 <= x && x < BOARD_SIZE;
}

bool haveOppositeSign(int x, int y) {
    // Check if one number is negative and the other is positive or vice versa
    return (x < 0 && y > 0) || (x > 0 && y < 0);
}

// Function to print the chessboard
void printBoard(const Chessboard &board) {
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

void printMoves(const Moves &moves) {
    std::cout << "[";
    for (Coordinates move : moves) {
        std::cout << " \"" << IndextoAddress(move) << "\"";
    }
    std::cout << " ]" << std::endl;
}

void printChessPiece(const ChessPiece &piece) {
    std::cout << "Identity: " << piece.identity << std::endl;
    std::cout << "Weight: " << piece.weight << std::endl;
    std::cout << "Exhibit: " << piece.exhibit << std::endl;
    std::cout << "Moved: " << (piece.moved ? "Yes" : "No") << std::endl;
}

void printConfusion() {
    const char *confusion = R"(
⢠⠘⠤⠐⠤⡀⠄⢢⡐⢆⠲⡐⢆⢣⠚⡔⢣⡚⡔⢣⠚⡔⢣⠜⡤⢃⠜⡠⠃⠜⡀⠣⠐⠀⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠨⠑⣯⡹⣝⢯⡹⣏⢿⡼⣏⢾⣱⢳⡞⡽⣎⢷⡹⣎⢷⣫⢗⡯⣝⢯⡝⣯⠽⣭⢻⡝⡾⣭⢳⢯⡝⣯
⠀⢎⠰⣉⠦⣑⡘⢦⡘⢆⢣⢉⢎⠲⡩⢜⡡⠞⣌⢣⡙⣌⢣⠚⡄⠣⠐⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢲⡝⣬⠳⣝⡞⣧⠿⣜⡧⣏⢷⣹⢳⡝⣮⢳⡹⣎⢗⣫⢼⣫⢞⡽⣎⠿⣜⡳⣝⡳⣭⢇⡏⣾⢳
⠈⢆⠱⢂⠖⠤⣉⠖⡸⢌⠢⢍⢢⢃⡕⢪⠴⡩⢔⢢⡑⢆⢣⡙⢄⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢣⢞⡵⣫⢶⡹⣎⡿⣹⡞⡽⣎⢷⣫⢞⣱⢫⠵⣎⢯⡜⣣⣝⢮⡳⣭⢻⡼⣹⢎⡷⣹⠎⣹⢎⡿
⠈⡄⠳⣈⢎⠲⣄⠫⡔⢣⠜⡌⢆⠣⣌⠣⢎⡑⢎⠲⡘⢤⠣⠜⣂⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡸⣎⢷⣣⢞⡵⣫⢗⣳⢻⡵⢯⡞⡵⢯⡞⣭⠷⣞⢧⣻⡵⣺⢏⡷⣽⢣⡟⣵⢫⣞⡵⣏⢳⢯⡽
⠈⡔⠣⠜⣂⠳⢨⠱⣌⢣⠚⡜⣌⠳⢌⠳⡌⡜⣌⢣⡙⢢⡙⡒⠤⢈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢰⣉⠷⠙⢮⢧⣛⢼⢣⡟⣼⢣⡟⣧⢻⡝⣧⣻⢭⡻⣜⢯⡖⢯⡳⢏⡾⡳⢯⡽⣚⢯⡞⣵⡋⢯⡞⣽
⢈⠰⢉⠜⡠⢍⠢⡑⠤⢂⠡⢂⠤⣉⠌⡓⡜⠰⡌⢦⢡⠃⡖⣉⠆⡡⢀⠆⢠⠀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠣⠜⣊⢧⢈⡚⡽⢎⡷⣹⣎⢷⡻⣜⢷⡻⣼⢧⣏⠷⣎⢷⡚⢧⡻⣜⠳⣭⢳⣜⡹⣆⡻⣆⢇⡳⣜⢷
⢀⠣⡘⢬⠱⢌⡒⢍⠲⣉⠦⡑⠲⢌⢪⠱⣌⠱⡘⢦⢡⢚⡰⢄⠣⡑⢌⡘⠤⠁⠐⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⢀⡀⢠⢀⡀⢄⡀⣀⢀⢀⡀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠂⠉⠈⠉⠘⠳⣎⢯⣳⡝⣮⢳⡝⡾⣜⢯⣚⢧⡻⣵⣛⡼⣻⣜⡳⣎⠷⣭⡳⣝⢦⡱⢯⣞
⢠⢃⠜⠢⣍⠲⡘⣌⠓⡔⣊⠱⣉⠦⡡⠣⢌⠲⣉⠆⢎⠒⠤⢋⠔⡉⠆⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⢤⠰⡰⢤⣀⠤⣠⡐⢦⡘⢦⡄⣔⢢⠠⡜⣥⢲⡀⠀⠁⠊⡔⠠⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠖⣻⢧⡻⣽⡱⣏⡾⣹⣎⢷⣣⢏⡶⣳⢎⣷⡹⣏⡷⣝⡞⣧⢺⡝⣮
⢂⠌⢎⡱⢄⢣⠱⡌⡜⡰⢡⠓⣌⠲⢡⡙⢢⠓⡬⡘⢢⢉⠂⠥⢈⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡐⢦⡙⠦⠓⠥⠋⠕⠣⠎⢳⡡⢬⡄⡭⣤⢻⡜⣦⠧⣬⢤⢧⣏⢇⡀⠀⢸⡑⢦⠢⣄⡀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠲⡱⢆⡿⣜⢳⢧⣏⢷⡹⣎⢷⡹⢞⢶⡻⣝⡾⣱⣛⢦⡻⣜⣳
⢈⡘⢄⡒⣉⠆⢣⠒⡡⠜⡡⢍⠤⢋⢆⡱⢃⠭⣐⠱⡂⢌⡘⠄⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⡐⢎⡜⢤⡑⣦⠳⣖⢶⣒⠶⣜⢧⡝⣧⢻⡵⣫⣥⣛⣌⣻⣜⡮⣖⣌⣛⠶⣤⡀⡙⢎⡳⣌⠓⠤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢳⡜⢮⡳⡞⣜⣫⠷⣙⢮⡝⢮⡳⣹⢎⡷⣣⣏⢧⢳⡝⣞
⠐⡰⡈⠴⡁⢎⠥⡙⡰⢉⠖⡩⠜⡌⡒⡌⢎⡒⣡⠚⡔⢢⠐⡩⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⠘⡴⣉⠞⣬⠣⡙⣶⢻⡜⣣⠯⣝⢮⡳⣙⣬⣳⣜⡳⣟⡾⣹⢧⡻⣝⣻⡞⣭⡛⢶⣹⢳⢮⡵⣎⡟⣤⣈⠈⠒⠦⢠⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢂⠒⠤⡀⠀⠀⠀⠀⠀⠀⣞⣣⠷⣹⢎⡳⢯⣹⠲⣝⢧⡳⣝⢾⣱⢟⡼⣋⢮⡽⣞
⡘⠤⡑⡘⠬⣘⠰⡑⢌⢃⠎⣅⠳⣈⠵⡘⢢⡑⠦⠱⣘⠢⡑⠤⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⢤⡙⠤⣑⠺⣔⡣⢗⣎⠷⣞⢧⡿⣼⢶⡽⣯⢷⡿⣾⢿⣼⣻⣽⡿⣽⣯⢳⢻⣷⣛⡧⢏⣏⡞⣵⠺⣝⢧⡻⣝⢶⣆⡄⠐⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠘⠤⢡⢃⠄⠀⢀⢀⡴⢣⡞⡽⣸⢫⣝⣣⢗⡻⣜⠮⡵⣎⢷⣹⢎⡷⣫⠞⣵⣫
⡘⠤⡑⢌⡱⢄⡓⠌⢎⠢⡍⠤⢓⠌⢦⠙⡔⡘⢆⠳⢄⠓⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠐⡈⠤⣘⠑⣂⢍⡲⢍⡳⢬⡹⢞⣜⣣⢛⣮⡽⣞⣯⢿⡭⢿⡽⣯⣟⣾⣳⢯⣻⢷⣯⢷⣯⠜⣧⡟⡽⢦⢻⡴⣻⢮⣳⣟⡼⣳⢮⣛⡿⡼⣯⣟⡷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠊⠜⡰⢌⡞⣜⢣⡝⣲⢭⢳⣎⡞⣮⠵⣋⢾⡱⣏⢾⡱⣯⢞⡥⣟⢮⣳
⡘⠤⡑⠬⡐⠦⡘⠜⡨⠑⡬⢑⠪⢜⠢⢍⠢⡍⡜⡌⢂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⡄⢢⡐⣌⠳⠤⡙⡌⢞⡰⢣⡝⢦⡝⣺⠼⣜⣳⢎⡳⢟⡾⣯⣟⣯⣽⠳⣿⣾⡽⣿⣽⣻⣞⡻⣞⡿⢼⣹⡝⣯⢳⣜⡳⣏⢶⡹⣞⡵⣏⡷⣝⡳⣟⣾⣽⣻⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠐⠀⠘⣬⢳⠼⡱⢎⠷⢮⡝⣶⡹⣹⢲⡝⣮⢳⡝⣎⠿⣜⣣⢟⡼
⡘⠤⡑⡘⠴⢡⡉⠖⡡⢩⠰⡉⡜⢢⢍⣊⠱⡰⡘⢌⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠠⣀⠣⠀⢢⠱⡌⢲⢡⢳⡩⢖⡭⢓⡜⣣⠞⣥⠻⣜⢧⡻⣜⢯⡞⣴⠛⣞⣷⣻⣵⢫⡽⣞⣵⣳⠾⣽⢯⡿⣅⢷⡻⣜⡳⣎⢷⡹⣎⢷⡹⣞⣭⠿⣼⢽⡽⣞⣾⣳⣟⡿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠯⡹⣍⡏⣞⢣⡟⢶⣙⢧⡏⣞⢥⡻⣼⡹⣎⠷⣸⢏⡾
⡘⠤⢡⠑⣌⠢⣑⢊⡑⢆⢣⠱⣈⠥⠒⡌⢂⡕⢉⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠄⡂⠁⢠⠂⣄⢣⠳⣜⡡⢇⡳⣌⠳⡜⣣⠞⣥⢛⡴⢫⡜⣣⢻⡜⣣⢟⡼⣻⡔⢯⣗⢯⣏⣷⢻⡼⣧⢿⣭⣟⡷⣭⢊⡽⣾⣱⢯⡞⡽⣞⢧⡻⣜⢧⡟⡽⣾⣹⣳⢞⣳⢯⣿⣝⣲⢃⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠱⢎⡼⣜⣣⢞⣣⣛⣎⢷⡩⣞⡱⣣⡝⣮⢏⡵⣺⡝
⠰⢡⠂⡍⢄⡓⢌⠢⣑⠪⣐⠣⣐⠊⠵⡘⢢⠘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢑⠨⠀⠈⠀⠰⣌⢣⡛⡴⣙⢮⡱⢎⡽⡜⣥⠻⣌⠷⣚⢧⡻⣵⣋⢾⡱⣏⢾⣱⢋⡷⣞⡿⣚⣞⣯⡽⣏⡟⡼⣏⢿⡼⣯⢻⡵⣫⢞⡽⣳⢯⣞⣳⠽⣮⣝⡻⢶⢯⡽⡾⣭⣻⣞⢯⣟⣧⠞⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢚⡜⢶⡱⣎⡵⢺⡜⡮⡵⢎⡵⣣⠟⣦⡛⣼⢣⡟
⡑⢢⠑⡌⠢⢜⢨⠱⢠⠓⠤⠓⡌⡉⢆⠱⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢁⠊⠄⠁⠀⢎⡅⡈⢇⡳⢱⢩⠖⣹⢆⡶⣩⠖⣝⢮⢳⣩⢶⣹⢶⡹⣎⠷⣞⣧⣟⡾⣽⢏⣞⡿⣚⣷⢻⣝⣻⡽⢯⣳⣝⡳⣏⢷⡛⣮⢳⡝⡾⣜⣳⣛⠶⣭⡻⣽⣛⡾⣽⢳⣳⣏⡟⡾⣽⣻⢮⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡞⣥⢳⢎⡵⣫⣜⢳⣭⢫⠶⣭⡛⣴⢻⡜⣧⢻
⢰⠁⡎⢰⠉⡆⢇⠸⢁⡎⢁⠇⡰⢁⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⠈⡰⠀⠀⠸⣆⠸⢱⢎⡱⢏⡎⣹⢇⡿⣸⢇⣿⣸⡾⣷⣏⣿⣸⣎⣷⣏⢿⣹⡾⣹⠿⣷⢿⣾⣷⢿⣾⢿⡾⣇⡿⣏⣷⡎⣷⣏⣷⢿⣸⢷⣏⢷⣹⢶⣉⡿⣷⢿⣱⣏⡹⣏⡿⢷⣏⡿⣹⢷⣏⣷⠾⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠾⣰⠏⣾⢱⢇⡾⢇⡾⣱⠿⣶⢹⡸⣏⡹⣎⢷
⢢⠑⡌⢢⠑⠬⢌⠱⣂⠜⡄⢊⠔⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢁⠒⠀⢀⠰⢣⠘⣌⠇⢮⡱⢫⡜⡵⣎⢷⣫⢞⡶⣫⢷⣧⡼⣷⣟⡿⣾⣽⣻⣾⣽⣷⣿⣽⣻⣾⣽⣿⣾⣯⢿⡽⣾⣹⢾⣹⠶⣝⣮⢷⣹⠾⣼⢫⡷⢯⣎⠷⣭⣟⡷⣾⡹⣧⣛⡷⣯⠽⣽⡳⣟⣮⢧⠱⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡹⢆⠿⣘⠧⣏⠾⣹⠶⣍⡻⡴⣫⢵⣫⢷⡹⣞
⢢⠑⡌⢢⢉⠦⣉⠒⡔⢊⠔⠡⠈⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠡⢂⠀⠀⠀⡙⠦⣉⠆⡙⢦⣙⢣⢎⡁⠘⠃⠉⠊⠑⠉⠓⠚⠙⠓⢻⣟⣿⣳⣟⣿⣿⣾⣳⣿⢿⣿⣿⣻⣽⣿⣿⣿⣳⣯⢯⣿⣹⣏⣞⣧⢯⣻⡭⣷⣹⣟⡾⣝⣦⣉⠹⢳⣟⣷⣻⣽⣳⢯⣳⣝⢮⡗⣎⢳⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⠽⣍⡞⣭⢳⡭⣋⢧⡻⣜⡳⣝⣣⠟⣼⢣⡟⣼
⢢⠑⡌⠢⠜⣐⠢⢍⡰⠁⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⡔⢈⠀⠀⢀⠍⡒⡅⢊⡝⡀⢎⠞⡬⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠘⠓⠉⠘⠙⣿⣿⣽⣿⣿⣿⣿⣿⣻⣿⣿⣿⣿⣿⣷⣻⣽⣾⣽⣳⢷⣻⣞⣧⡻⣽⢻⡜⠯⠃⠀⠈⠈⠓⠋⠟⢯⡷⣾⣽⣚⡬⣃⠧⣁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢃⡛⣦⢹⢬⡓⣞⡹⢮⡵⣣⠿⡼⣥⢻⡜⣧⢻⣜
⢢⠑⡌⡑⢊⠤⣉⠆⡐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢁⠆⠀⠀⡰⢌⠚⠤⠱⣈⠖⡱⠊⠁⠀⠀⣀⣼⣿⣿⣿⣷⣤⠀⠠⡀⠠⢀⠀⠀⠀⠈⠠⠀⠙⠿⣿⢿⡿⠻⠿⣿⣿⣿⣿⣿⣿⣟⣷⡿⣯⠟⡿⡛⠟⠞⠣⠛⠁⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠒⠧⣛⠶⣉⠖⡠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣡⢛⢮⡝⣮⢳⣏⠶⣭⠻⣕⣣⠟⣼⢣⡟⡼
⠢⡑⢄⠣⢡⠊⡔⠨⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠌⠀⠀⡜⡐⢊⠅⣎⠱⣌⠚⡥⠁⢰⡀⠸⣿⣿⣿⣿⣿⣿⣿⢷⠀⡱⠀⠀⠈⠀⠀⠀⠀⠀⠁⠀⠈⠁⠙⠣⠄⠉⠻⣿⣿⣿⣿⣿⠯⠛⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠡⢍⠲⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⢋⠲⠙⠌⡳⢎⡿⡼⣹⢮⢵⡻⣜⢧⡻⣝
⡑⢌⠢⡑⢢⠑⡌⡑⢂⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢘⠠⢄⠪⠔⡡⢊⠜⣠⠓⡔⣪⠕⣂⠇⠃⠐⠉⠉⠉⠉⠉⠉⠈⠉⠀⠐⠀⠀⠀⠀⢀⠂⠄⠀⠀⠀⠀⠀⠀⠀⠈⠑⠄⠘⣿⣿⡿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⢤⢠⡀⣄⣀⣀⠀⠀⢈⡓⢬⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣜⡳⢧⣛⢶⡹⢮⡳⣝⢮
⢌⠢⡑⢄⠣⡘⠤⡑⠌⠂⠄⠁⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⠘⡄⢣⠘⡄⢣⢊⡔⣩⢒⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣵⢶⣏⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢑⠊⠱⠙⠦⠓⡮⡝⡤⠀⡘⠰⡈⡐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠞⣼⡙⣧⣛⢮⡝⣯⢳⡝⣞
⢌⠢⡑⢌⠰⡁⢆⠱⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡈⢆⠱⡈⡄⢣⠜⡠⢃⠔⡠⠊⠀⠀⠀⠀⣠⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⢠⡀⠀⠀⠀⠑⢌⠲⣉⠎⡱⠀⠀⠀⠀⠀⠀⢀⡼⢯⣟⡿⣾⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠐⠣⠁⠁⠀⠄⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣉⠎⡵⣊⢟⡲⡹⡖⡽⣎⡽⢎⡷⣹⢞
⢌⠢⡑⢌⠰⡁⠎⠤⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⡑⠌⢢⠑⡌⢆⡘⢄⠣⠈⠀⠀⠀⠀⠀⣰⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣷⣄⠀⠀⠈⡱⢌⢎⡱⢩⠄⠀⠀⣀⢼⣳⣟⡿⣮⡽⣷⣻⢦⠀⠀⠀⠢⡌⠱⣃⠜⠰⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠀⠀⠀⠀⠀⠀⠠⠈⠄⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠨⡌⡱⣍⠮⣕⢫⡝⣞⠵⣺⡹⢞⡱⢯
⢌⠢⡑⠌⣂⠱⡈⠆⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⡑⢌⠢⡑⢌⠢⢜⡈⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿⠦⠀⠀⡵⢊⠦⣱⠫⡜⣆⠶⣹⡞⣷⢯⡿⣵⣛⣷⣟⣯⣳⢸⡄⠀⠩⠄⠘⠈⠀⢀⣴⣶⣶⠀⠀⠀⠀⠀⠀⠀⠈⣧⡄⠀⠀⠀⠀⠡⠈⠄⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⢨⡑⣎⡗⣎⢳⡹⢮⠽⣱⢫⣏⢽⣣
⠢⡑⢌⠒⠄⢣⠐⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⡑⢌⠢⡁⢎⡘⠆⡌⠀⠀⠀⠀⠀⢀⣀⡀⠉⢻⡿⣟⣦⢤⢤⡤⢦⡤⣼⣄⣀⣀⣀⠀⠀⠀⠑⢫⢆⡱⢣⡽⣸⣀⠷⣻⡽⣯⢿⡷⣯⣗⡿⣾⢥⣋⢞⠀⠀⠀⠀⠀⠰⣿⣿⣿⣿⡃⠀⠀⠐⠀⠀⠀⠀⣿⣟⠀⠀⠀⠀⠐⠀⠂⡐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠰⡹⢎⡷⣙⢮⣝⣣⢟⡼⢮⡵
⡑⢌⠢⢉⠜⡀⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡌⢢⡑⡰⢂⡌⠃⠀⣀⢀⣀⠀⡔⣊⠶⡙⠆⠀⢉⡹⢾⣹⢦⠶⣥⣛⡶⣏⣟⢮⡳⢆⡾⡰⢤⡂⣆⢭⠳⣜⡳⣜⢯⢷⡻⣽⣿⣿⣟⣯⢿⣻⢯⣟⣯⢷⣀⡀⠀⠀⠀⠉⠛⠛⠋⠁⣄⡀⠀⠀⠀⠀⣰⠿⣏⠂⠀⠀⠀⠀⢀⠐⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠫⡔⢯⣚⢦⡝⣮⡝⣶⡹
⢌⠢⡑⠌⠂⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⡰⠰⡡⠃⠀⢠⡚⣤⠳⣌⠻⣔⡡⢤⣈⡼⣫⢯⡽⣏⣷⢫⣟⡳⢭⠷⣛⣮⢷⣹⡀⠱⢙⡦⡝⡜⡮⠝⠮⠓⠁⠀⢀⣠⣤⣼⣿⣿⣿⣿⣿⣿⣿⣯⣟⡷⡝⡄⠀⠀⠀⠲⢶⢶⡾⣽⣹⡗⣦⢤⠲⠅⠋⠀⠀⠀⠀⠀⠀⠂⠌⡐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠶⣙⢮⣝⡲⣝⢶⡹
⢂⠱⡈⠂⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡒⡡⢃⠀⣠⢐⡣⡕⢮⡱⣌⠷⢮⡵⣫⢞⣱⣣⢻⣜⡽⣺⣟⣾⣻⣟⡾⡵⣎⠿⣖⡻⠄⠀⠱⡍⠃⠀⠀⠀⣀⣤⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡽⡆⠀⠀⠀⠀⠀⠙⢞⣳⢷⣫⢧⡉⠀⠀⠠⢌⡃⢆⠰⢠⠄⡄⢠⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠨⠱⣎⠶⡹⣜⢮⢳
⢈⠂⢅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠁⢈⠖⣡⠏⠶⢁⢮⡱⣭⣚⢧⡞⣵⣫⣾⣽⣿⣯⢿⡷⣯⣾⡽⣮⣽⢿⣯⢿⡼⡡⠀⠀⣰⢆⠀⣤⣄⣾⠿⠳⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣳⢇⣀⡀⠀⠀⠀⢲⣎⡝⣾⢣⡷⣡⢤⡀⣄⠀⠀⠀⠀⠀⠈⠐⠣⢌⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠳⣌⣳⠹⣬⢏⡳
⠠⠉⠄⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⢂⠡⠈⠄⢂⠐⠠⠀⠀⠀⢀⠀⠈⢲⢡⠞⡁⠘⣧⣛⠶⣝⡾⣹⣞⡽⣳⣟⡾⣽⣿⣽⣿⣽⣿⣳⣯⣿⣻⢯⠓⠁⢀⣈⠱⢎⡈⠓⠩⠐⠠⠀⠋⠘⠛⠻⠻⠟⠻⠟⠻⠻⠟⠻⠟⠛⠳⠛⢮⠳⣭⠳⡲⣄⡻⣼⡹⡼⣏⡷⣏⣶⡹⣎⣟⡶⣤⣤⣄⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠳⣘⢦⡛⢦⣋⠷
⠠⠁⡌⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡐⢀⠂⢀⠂⠀⠠⢈⠐⠀⠀⢀⠢⢡⠀⢈⠶⡙⡄⠀⡰⣏⢻⡼⣹⢧⢯⣽⣳⢯⡿⣽⣻⣽⣾⣷⣯⣷⣿⡽⠁⠀⠀⣠⠞⡜⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠀⢀⡠⢤⢤⡠⢤⡄⠀⠀⠀⠀⠀⠀⠒⢄⣂⢱⡘⡵⢣⡞⣵⢻⣜⡻⣜⡻⣝⠾⡽⢧⣟⣮⢗⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⡩⢖⡭⢣⣛⡼
⢀⠡⢀⠁⡀⠂⠀⠀⠀⠀⠀⠀⠀⠀⢀⠐⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠎⡄⠀⠀⢣⡝⡀⠀⢳⡝⡆⣟⣳⢯⣛⣾⡽⣻⡽⣿⣟⣿⣿⣿⣿⣿⠋⠀⠀⢀⡞⡥⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢉⠞⣢⠝⠦⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠛⣜⢣⡟⣼⡳⣞⣽⢣⡟⣮⢻⡽⢧⡟⣮⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⠝⡮⡜⢧⣣⡝
⠀⠂⠄⠂⢀⠐⠀⠠⠀⠀⠀⠀⠀⠀⠀⡈⠀⠀⠀⠀⠀⣾⣟⡆⠀⠀⢈⠒⢌⡀⠀⠱⣌⠣⠀⠡⣻⢵⡻⡘⠫⣟⡾⣽⣷⣻⣿⣿⣿⣿⣿⣿⠿⢟⡻⠜⠀⡜⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⠮⡜⢤⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠡⠙⢧⢿⡜⣧⢟⡽⣭⢟⡽⣣⠉⢈⠂⠀⡄⣠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡘⢮⡱⣙⢮⡱⢞
⢈⠐⡈⠐⠀⡀⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⡐⠀⠀⠀⣼⣿⠿⡄⠀⠀⢂⡉⠤⣀⠀⠀⢌⡓⢆⠀⠘⣧⢻⢵⣂⠈⠽⣻⣷⣟⣿⣾⣿⣿⣿⣿⡶⠞⠀⣠⠞⠀⠀⠀⠀⠀⠀⠄⠀⣠⠀⣄⠀⢀⡀⠀⣀⣎⢆⠀⠂⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠂⠄⠀⠹⢨⢷⡹⣎⠿⣜⣧⢻⡜⠁⠀⠀⠀⠰⡑⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⢥⠳⣍⠶⣙⢮
⠀⠂⠄⡁⠐⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⣿⢾⣻⠀⠀⠀⢂⠰⠀⠔⡂⠄⠀⠹⡌⠆⠀⠘⣏⢮⡳⢧⡄⠙⣾⣽⣾⣿⣿⣿⢋⣰⢲⣝⣻⢬⡳⠀⠀⠀⠀⠀⠀⠀⠙⢆⢻⣬⣛⢧⡻⣜⣳⣎⣟⢾⡰⣃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢄⠊⠤⠀⠀⠡⢏⡿⣼⠻⣜⠎⠃⠀⣠⠒⠀⢠⠃⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⣣⢏⠲⡹⡜⣎
⠈⡐⠄⠐⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣟⢯⡳⠀⠀⠀⠂⠄⠃⠀⡘⡐⢂⠀⢩⠃⢄⠀⠙⣮⢵⣋⢶⣄⠈⠛⠹⠋⠹⠞⢯⡳⢻⡜⠃⠋⠂⠁⠀⠀⠀⡀⠈⡙⢮⠤⣘⢦⡝⣮⢵⣫⢷⡽⣞⣯⠷⣭⠳⣄⢠⠀⡀⠀⠀⠀⠀⠀⠀⠂⡉⠂⠅⠀⠀⠠⣝⠦⣥⠎⠀⡠⡜⠁⠀⣠⠂⠀⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⡘⡔⣣⢎⢣⣓⡱⢎
⠐⠠⠈⠄⠁⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣙⢮⡱⠀⠀⠀⠀⠌⠀⠀⠠⢑⠢⡀⠀⠹⢀⢧⠀⠈⠞⣥⠯⣜⢳⡲⣤⢤⣠⣄⣄⡐⠃⠚⠁⠀⠀⠃⠄⣂⢀⡠⢀⠱⢌⡳⣀⢏⡾⣱⡞⣜⠯⣞⡽⣚⠿⣜⡻⣬⢇⠛⣜⢣⠇⡤⣀⠀⠀⠀⠀⠀⢂⠀⠀⢘⣮⣛⠆⠀⡰⠁⠀⠀⡘⠤⠀⠀⠌⠀⠀⢂⠀⠀⠀⠀⠀⠀⠀⢀⠈⠀⠀⣀⠣⢠⠈⠀⠀⠀⠀⠀⡜⡱⠜⣌⢇⠦⡓⢎
⠀⠡⢈⠀⢂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣩⠖⡁⠀⠀⠀⠡⠈⠄⠀⠀⡃⢆⢡⠀⠀⠀⣋⠞⡤⠀⠉⠓⠩⢷⣙⢮⢇⠓⠚⠈⠃⠀⠀⠀⠀⡀⠀⢠⢃⠮⠔⠁⣀⡄⠃⣡⢮⠵⣣⠻⣭⢻⢼⣱⣋⠷⣬⣳⢭⡢⣝⣨⢓⢮⠱⡌⡄⡀⡉⠌⠑⠂⠀⠀⢸⠒⣭⣃⠀⠓⠀⠀⡰⢉⠀⠀⡈⠄⠀⠐⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⢀⠃⢆⡘⡀⠀⠀⠀⠀⡜⣡⠛⣌⠮⡱⣉⢎
⠀⡁⠂⢈⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡑⢦⠹⡄⠀⠀⠈⠄⡁⢂⠀⠀⠈⠄⠈⠎⡄⠀⢨⠝⡈⠉⠁⢆⠀⠀⠈⠉⠈⢁⡠⠖⠈⠀⠀⢀⠡⠀⠀⠀⣨⠤⣤⣚⡵⣢⢾⣝⣮⡻⣥⢷⣎⡷⣫⢶⣭⣛⢶⡹⣎⢷⢣⠮⣝⠊⢧⡙⡴⣡⢉⠎⡀⠃⣄⢃⡀⢂⢗⡂⠀⠀⠀⠘⠄⠁⠀⡐⠀⠀⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠑⡌⠒⡄⢢⠁⠀⠀⠀⢈⠖⣡⢋⠬⢣⡑⢎⡜
⠀⠄⢁⠀⢂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠤⡓⠤⠀⠀⢈⠐⡀⢂⠀⠀⠀⠨⡁⢄⠈⠐⠈⠎⡱⢉⡛⡌⠒⠉⠂⠑⠉⠂⡙⠀⠀⢀⠐⠠⠀⠤⢁⡸⢥⡛⡴⠣⠻⠱⣻⢎⡷⢻⠝⠾⢾⣱⢏⡿⣼⡹⣎⠷⣭⢞⡣⡟⣬⢛⣦⢛⡴⢣⠌⠀⠠⣉⠴⠨⡜⠡⠎⠀⢠⠀⠀⠈⠀⠀⠂⠀⠀⠠⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢃⠄⡡⠘⠄⠂⠀⠀⠀⢎⡜⡡⢎⡙⢦⡙⢬⡘
⠀⠌⢀⠐⡀⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢒⣉⠒⠀⠀⠀⠂⠄⠂⠀⠀⠀⠠⠑⡌⠰⣀⠀⡀⠀⠁⡖⡡⢓⡌⢃⡈⡐⠀⡁⠀⢀⠆⣀⠣⠁⠐⠦⡙⠆⠁⠄⢲⠒⠄⢺⡜⣱⢃⣀⡤⣜⢯⣻⢳⢧⡟⡾⡽⣖⢯⠶⣝⢮⡳⢎⢯⡜⡣⠀⢀⠒⡄⢎⠱⠈⠁⠀⠒⡀⠀⠀⠀⠐⠀⡐⠠⢁⠂⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢂⠁⠎⡐⢉⠀⠀⠀⠀⠠⢎⡔⢣⠎⣜⢢⢱⢢⡙
⠀⠌⡀⠄⠐⡀⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢠⠉⠀⠀⠀⠁⠂⠁⠀⠀⠀⠀⠣⢌⡑⢄⠣⡁⠃⡄⠈⡁⠣⠜⢢⠱⠘⠀⠀⢀⠂⠰⡀⠃⠀⠈⠀⡀⠄⡠⠄⡊⠁⠠⠃⠈⠁⠉⠐⠛⠜⠣⠍⠛⠊⠙⠓⠙⠪⠇⠻⡜⢦⡙⠎⠂⠁⢀⠄⠢⠁⠀⠀⠀⢀⠀⡀⠀⠀⠀⠀⠀⢀⠐⠠⢁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠐⠀⠀⠀⠀⢠⢙⠢⡜⢢⡙⡤⢋⢆⢣⢚
⠀⢂⠀⠌⠐⢀⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠌⠀⠀⠀⠀⠁⠂⠀⠀⠀⠀⠁⢂⠌⡠⢃⠰⡐⠌⡄⠈⠁⠉⠀⠀⡀⡐⠌⡄⢊⠔⠁⠀⡀⠆⡐⠰⢀⠀⠀⠐⠀⣀⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣄⠀⠀⠀⠀⠀⠄⠠⠀⠀⢀⠀⢄⠢⠑⠂⠀⠠⠁⠈⠀⠀⡀⠂⠌⡐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢐⢪⠱⣌⠣⡜⡰⢋⡌⢖⡩
⠀⠂⠄⡈⠄⠂⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⡨⠄⠀⠀⠀⠐⠀⠀⠀⠄⠀⠀⠈⠐⡁⠆⡑⠌⡒⢌⠡⢂⠔⡨⠐⠤⢑⠢⠀⠁⠀⠀⠀⡐⠠⢀⠁⠂⠀⠀⠰⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⡄⠀⠀⢄⡀⠢⠌⡈⢄⠂⠀⡁⠀⠀⠀⠀⡀⢂⠐⢀⠂⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡌⢆⡓⠬⡱⢌⡱⢣⠜⣢⠱
⠀⠡⠀⠄⠐⠈⠠⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠅⠢⠀⠀⠀⠀⠂⠀⠀⠂⠀⠀⠀⠀⢀⠣⠘⠀⠁⠈⠢⢁⠎⠀⠃⠢⡁⢎⠀⠀⠀⠐⠠⢠⠁⢂⠈⡐⠀⠀⠀⠙⠻⠿⠛⠛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀⢀⠢⠄⠡⡐⠠⠌⡠⠀⠀⠀⠀⠠⠐⠀⠂⠠⠀⠈⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠒⡜⢢⡘⣡⠓⡬⢒⢥⠚⣤⢋
⠀⠂⠄⡈⠠⠁⠂⡁⠐⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⡀⠀⠀⠀⢂⠉⡔⢁⢂⠀⠀⠀⠠⢀⠀⠀⠀⠀⠀⢂⠀⡀⢀⡈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠂⠌⠡⠐⠡⢂⠡⠐⠀⠀⠠⠐⡀⠡⠈⠄⠁⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣙⠰⡃⠴⣁⢎⡱⣉⠦⣋⠴⣩
⠀⠌⠀⠄⠐⠠⢁⠠⠁⠄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⡀⠁⡀⠀⠂⠐⠈⠄⠂⠄⡠⢀⠀⠉⠐⠂⢡⠀⢈⢂⠑⢢⠘⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⢀⡀⠀⠠⢁⠀⠀⠠⠐⡀⠁⠌⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣨⠱⢌⠣⢜⢢⡱⢌⡖⡡⢞⡰
⠀⡐⠀⠌⢀⠂⠄⠂⡁⢂⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠁⡀⠀⠀⠌⡐⠈⠌⡐⢀⠂⢄⠂⢌⠐⡂⢌⠀⠀⠈⠀⠃⡌⠱⣀⠆⡤⢠⠄⡤⢠⡄⢦⣠⢤⡠⣄⣀⣀⢀⡀⣀⢀⡀⣀⢀⡀⡀⢀⡀⢀⢠⡔⣣⡝⣣⢎⠀⠀⠂⠀⠀⠁⠂⠄⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠱⢄⠳⣈⠣⢎⠦⡑⢎⠴⣩⠖⡱
⠀⠄⠂⡐⠠⠐⡀⢂⠐⠠⠀⠌⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠁⠐⠠⠁⠌⢠⠊⢄⠊⠐⠀⠀⠀⡀⠀⠀⠀⠁⠀⠉⢞⣥⠻⣜⢧⡛⣧⣛⣞⣳⡻⣼⣳⣯⣾⣵⣯⣾⣵⣫⢾⣽⣳⡽⣏⡷⣹⡱⢎⠵⠈⠀⠀⡐⠀⠀⠄⠁⡈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡌⢎⡘⠆⡥⠓⣌⢲⣉⢎⠲⡡⢞⡱
⠀⠂⡁⠄⡐⠠⠐⠀⠌⢀⠡⠈⠀⠄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠐⢈⠠⠁⠄⠀⢂⠀⠀⠀⠀⠄⢂⠡⠐⠠⢀⠀⠈⠓⡄⠈⢾⡹⣎⢯⡿⣟⡿⣿⢿⣿⣟⣯⣿⢿⣿⢿⣿⣟⣿⣿⣳⣯⡽⣞⡵⢣⡉⠌⠀⠀⠠⠐⠀⠀⠀⠈⠄⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⡌⡒⢌⡱⢌⠓⡌⡒⡌⢎⡱⢍⠶⡱
⠀⢁⠀⠆⡀⠆⠁⠈⠀⠆⠀⠆⢁⠰⠀⡀⢀⠀⠀⡀⠀⠀⠀⢀⠀⠀⡀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⡀⠈⡀⠁⠆⠈⠰⠈⠰⠈⡀⠀⠁⠆⡀⠆⠀⠀⠈⠀⠀⠱⣏⡿⣾⣹⢿⣹⡿⣾⣹⣏⡿⣏⣿⣏⣿⡿⣾⣹⡿⣷⢿⡹⠈⠁⠀⠀⠀⡈⢀⠁⠀⠀⠀⠆⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡸⢰⢁⡎⢰⠎⢱⡈⢱⡸⢸⠰⠏⣶⢱
⠀⢂⠈⠠⠐⢀⠡⠈⡐⠈⠐⠈⡀⠄⠐⠀⠄⢈⠐⠠⠁⠌⡐⠠⢈⠐⡀⠂⠄⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⢀⠂⠠⠁⠌⠀⠡⠈⠄⠡⢀⠂⠁⡐⠀⡐⠠⠀⠀⠀⠀⠀⠙⠽⣯⢷⡻⢿⡽⣿⣻⢿⡿⣿⢿⡿⣿⢿⣟⠯⠟⠑⠃⠀⠀⠀⠀⡀⡐⠄⠂⠄⠀⠀⢈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠰⣁⠆⢲⢈⠣⢎⡱⣘⠣⡜⣡⢋⡳⠜⡦
⠀⠂⠌⠐⢀⠂⠄⠐⡀⠌⠠⠁⠠⢈⠀⠡⠐⠠⠈⠄⡁⠂⠄⡁⠂⡐⠠⠁⠄⠠⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠀⠂⠐⠈⠠⠁⠌⠠⠁⢂⠈⡐⠀⠀⠀⠄⠂⠐⠀⠀⠀⠀⠀⠀⠁⠙⠃⠙⠂⠙⠊⠑⠉⠊⠑⠉⠈⠀⠀⠀⠂⠀⠀⠀⡀⠒⠠⠐⠠⠁⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢌⠒⡄⢎⡱⢊⡱⢢⠱⣌⠳⣘⠤⡓⣬⠛⡴
⠀⠡⠐⠈⡀⠄⡈⠀⠄⠠⠁⠂⢁⠠⠈⠄⡁⢂⠁⠂⠄⡁⠂⠄⠡⠐⠠⠁⠌⠠⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠁⠈⠄⢁⠂⠄⠐⡀⠄⢁⠈⠀⠄⢁⠈⡐⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⢠⢀⠂⠅⡐⢁⠂⡁⠂⠠⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠀⢆⠰⢈⠔⣂⠡⢂⠀⠀⠀⠀⠀⠀⢀⡔⢣⢑⡊⡜⢤⠃⡖⡡⢎⠥⡓⡌⠶⣡⢃⢳⠰⣋⠖
⠀⠡⢀⠁⠄⡐⠀⠡⠈⢀⠂⠡⠀⠄⢂⠐⡀⠂⠌⡐⢈⠠⠁⠌⠠⢁⠂⠡⠈⠄⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡐⠠⠐⢈⠀⠄⠐⡀⠈⠄⠂⠠⠀⠄⡀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠂⠌⠁⠘⠠⠁⠌⠠⢁⠠⠈⠐⡀⢂⠐⠀⠄⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡘⠤⠉⡄⢣⠈⠆⡄⢣⠀⠀⠀⠀⠀⠀⣄⢣⡘⠤⢢⠱⣘⠢⢍⠴⡡⢎⢲⢡⡙⢦⡑⢮⢡⢛⡬⣙
⠀⢁⠀⢂⠠⠀⠌⠀⢂⠠⠈⠄⡁⠂⠄⠂⠄⡁⢂⠐⡀⢂⠡⢈⠐⠠⠈⠄⠡⠈⠄⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠈⡀⠌⢀⠂⡀⠄⢂⠠⠁⠌⠠⢀⠐⠠⠀⠀⢣⢉⡌⢡⡙⠤⢃⠄⡀⠀⠀⠀⠀⠀⠐⢀⠂⠌⡐⢀⠂⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠰⢀⠣⡑⢌⠢⣉⠒⢌⠢⠌⠀⠀⠀⠀⡒⠤⢂⢌⠣⣑⢊⠴⡩⠜⢢⢱⡉⢆⡣⢚⠤⡙⢆⢧⡚⢴⢣
⠀⠂⢈⠀⠄⠂⡈⠐⡀⠄⡈⠄⡀⠐⡈⠐⠠⠐⡈⠐⠠⢂⠐⠠⠈⠄⠡⠈⠄⠡⠈⠄⠡⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢁⠠⠐⢀⠂⠄⠂⠄⠂⠌⠠⢁⠂⠌⡀⠀⠀⠣⢎⡴⢣⡚⡵⣩⢒⡡⢒⡀⠌⢄⠀⠀⠠⢈⠐⡀⠂⢀⠁⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠢⡑⢌⢢⠑⡌⡒⠤⣉⠂⠆⠀⠀⠀⠀⠢⢱⠘⣂⠎⡱⢄⡋⠴⣡⢋⡜⢢⡙⠦⡱⣉⠶⣉⠎⡖⣩⠞⣢
⠀⢈⠀⠄⠂⢁⠀⠂⠠⠐⢀⠐⠠⠁⠄⡁⢂⠡⢀⠁⠒⠠⠈⠄⠡⠈⠄⠡⠈⠄⠡⠈⠄⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢂⠀⠂⠄⡁⠂⠌⠠⠁⠂⠌⡐⠀⠀⡀⠈⠖⡥⢃⠧⡱⢌⡳⢔⠠⡘⠄⠂⠀⢠⢁⠂⠀⠠⢈⠀⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠒⡀⠎⡄⢋⠴⣁⠲⢄⠃⠌⠀⠀⠀⠀⠀⠡⠓⡤⢚⡐⠦⣉⠖⡡⠎⡜⡡⢎⠱⡱⡘⢆⣣⢚⡑⠦⣙⠴
⠀⠂⢀⠂⠌⠀⠄⡁⠂⠁⠄⡈⠐⡈⠄⡐⢀⠂⠤⠘⠠⠁⠌⠠⠁⠌⠠⠁⠌⠠⠁⠌⡀⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠈⢀⠐⠠⠐⠈⡐⠀⡁⢂⠌⠁⠀⠰⠀⠙⡬⢃⣎⠱⣎⠜⠊⠴⡉⠀⢐⡈⠄⠂⠌⠠⢁⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⢣⠘⡰⠨⢅⠲⢄⡓⠌⡌⠀⠀⠀⠀⠀⠀⠀⠉⡔⢣⡘⢤⠃⣎⠱⠱⣨⠑⣌⠒⢥⡙⡌⢆⡣⠜⡲⣉⠞
⠀⠌⠀⠄⠂⢁⠐⡀⠄⠁⠂⠄⠡⠐⠠⠐⠠⠈⠐⠠⠁⠌⠠⠁⠌⠠⠁⠌⠐⠠⠁⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⢀⠈⡐⠈⠄⡀⠀⠐⠠⢈⠂⠀⠀⠀⠘⠰⣉⢆⠫⠔⠁⠈⠒⠀⠀⠂⠌⡐⢁⠂⠐⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡐⢌⠢⡑⠤⣉⠆⣍⠲⡘⢂⠀⠀⠀⠀⡀⠄⠀⠀⠀⠈⠢⠜⢢⠱⢌⡊⠕⣠⠃⠆⡍⠢⢄⡙⠦⣑⢣⠱⡜⡸
⠀⠐⠈⡀⠌⢀⠐⠀⡐⠈⠐⢈⠠⠁⠂⡁⠂⠌⠠⠁⠌⢀⠁⡈⠀⠂⢁⠐⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠀⠌⠀⠄⠀⢁⠂⠄⠂⢈⠰⢀⡀⠀⠀⠈⠀⠂⠘⡐⠠⢀⠂⢉⠐⠄⠂⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⢈⠆⡱⢐⠰⡈⢆⠱⠈⠀⠀⠀⠀⠠⡐⢌⡀⠀⠀⠀⠀⢉⢆⠣⢆⡑⢪⠄⣍⢢⠱⢡⠎⡔⢣⠜⣢⠱⡌⠵
⠀⠌⠀⠄⡐⠠⠀⠂⢀⠡⠈⠀⠄⠂⠁⠠⢀⠐⠀⠡⠀⢂⠀⠐⠀⠁⡀⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠠⠀⠀⠀⢈⠐⠠⠐⠠⠀⠁⠂⠀⠐⠀⠁⠠⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠈⠐⢌⠢⡑⠌⠂⠁⠀⠀⠀⢀⠢⡑⠢⢌⠀⠀⠀⠀⠈⠆⣍⠒⡬⣁⠎⡔⢢⢃⡕⢪⠜⣡⠚⣄⠳⣌⠳
⠀⠐⠈⢀⠠⠀⠂⠁⠀⡀⠂⢁⠠⠐⠈⢀⠀⠂⠄⠀⠂⠀⠀⠈⢀⠐⠀⠀⡀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠁⠀⠀⠈⠀⢈⠀⠄⠠⠀⠄⡀⢀⠀⡀⢀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠐⠡⢈⠀⠀⠀⠀⠀⢂⠱⣈⠱⡈⢆⠀⠀⠀⠀⠘⡄⢫⡐⢅⡚⣌⠣⢎⡸⢡⠞⢤⢋⡔⢣⣌⠳
⠀⠈⠀⢀⠀⠐⠀⠀⠁⠀⠐⠀⠀⠄⠂⠀⠐⠀⡈⠀⢁⠈⠀⠌⠀⠀⠄⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠈⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡄⠃⢄⠣⡘⠤⠀⠀⠀⠀⠀⠜⡡⠜⢢⠜⣄⢋⠦⣑⢣⠚⡤⢃⣎⠱⣌⠳
⠀⠈⠀⠀⠀⠀⡀⠐⠀⠀⠠⠀⢀⠀⠀⠄⠂⠀⠀⠀⢀⠀⠂⡀⢀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠡⠌⡑⡈⠆⠥⢃⡅⠀⠀⡀⠀⠈⢅⡋⢆⡚⠄⣎⠲⡡⢎⡱⢌⢣⡌⠳⣌⠳
⠀⠀⠀⠄⠐⠀⠀⠀⠠⠀⢀⠠⠀⢀⠈⢀⠐⡈⠐⡈⠀⠄⡁⢀⠂⠐⠀⢁⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡁⠎⡐⠤⡉⠜⢢⠐⠀⠀⠠⠀⠀⠐⡘⢢⠜⡌⡔⢣⠱⣊⠴⢋⠖⣌⠳⣌⠳
⠀⠀⠠⠀⠀⠀⠐⠀⡀⠐⠀⠄⠂⠠⠈⠄⢂⠠⢁⠐⠠⢀⠐⠠⢀⠂⢁⠠⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠘⢌⠂⡍⢀⠀⠀⠠⠀⠀⠑⡂⢎⠔⣌⢃⠳⡌⢎⡱⢊⢆⡳⢌⠳
⠀⠀⠀⠐⠈⠀⢀⠂⠀⠌⡀⠄⠠⠁⠌⡐⡀⠢⢀⠌⡐⠄⢂⠐⡀⢈⠀⡐⠈⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢀⠀⠀⠀⢈⠒⡈⠄⠀⠀⠀⠀⠀⠀⠘⠤⢊⠤⣃⠎⡜⢢⠱⣉⠦⡑⢎⡱
⠀⠐⡀⠄⠂⠐⠀⠀⠁⠂⠀⠌⠠⠁⠒⠠⠁⠂⠁⠂⠐⠌⡀⠆⢀⠂⠄⠐⠀⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠠⠀⠀⠁⠀⠀⠀⠀⠁⠂⠀⠀⠀⠀⠀⠈⠬⢡⠚⣄⠳⣈⠤⠓⡤⢒⠍⢦⡑
    )";

    std::cerr << confusion << std::endl;
}