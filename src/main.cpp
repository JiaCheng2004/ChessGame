#include <../include/main.h>

int main(int argc, char *argv[]) {
    int verbose = 0;
    std::string testFile;
    std::string aiName;

    const char *const short_opts = "vVdDt:T:a:";
    const option long_opts[] = { { "verbose", no_argument, nullptr, 'v' },
        { "debug", no_argument, nullptr, 'd' }, { "test", required_argument, nullptr, 't' },
        { "bot", required_argument, nullptr, 'a' }, { "ai", required_argument, nullptr, 'a' },
        { nullptr, 0, nullptr, 0 } };

    int opt;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
        switch (opt) {
        case 'v':
        case 'V':
        case 'd':
        case 'D': verbose = 1; break;
        case 't':
        case 'T': testFile = optarg; break;
        case 'a': aiName = optarg; break;
        default: print_usage();
        }
    }

    if (verbose) {
        if (!testFile.empty())
            std::cout << "Test File: " << testFile << std::endl;
        if (!aiName.empty())
            std::cout << "AI Name: " << aiName << std::endl;
    }

    Chessboard Board = newBoard();
    Movemaps Map = createPossibleMovesMap();
    bool Game = true;
    bool White = true;
    bool playerSelect = false;
    std::string origin = "";
    std::string destination = "";

    while (Game) {
        std::cout << CLEAR_SCREEN;
        printBoard(Board);
        std::cout << "Please select your piece by [A-H][1-8]. Ex: a1, b2, A1, B2" << std::endl;

        //Problem: 当有棋子挡路时，对方king仍是红色（正常情况应该变回原色）, 对方king可以变色，但己方king不行
        Coordinates B_kingpos = findPiece(Board, -KING)[0]; // black king, opponent king, up side king
        Coordinates W_kingpos = findPiece(Board, KING)[0]; // white king, your king, bottom side king

        // Check if one of the kings is gone, then the game is over.
        // if () {
        //     std::cout << "Game over!!!" << std::endl;
        //     if (White) {
        //         std::cout << "White win!!!" << std::endl;
        //     } else {
        //         std::cout << "Black win!!!" << std::endl;
        //     }

        //     Game = false;
        // }

        // incomplete
        std::cout << "现在是" << (White ? "white" : "black") << std::endl;
        std::cout << (isChecked(Board, Map, White) ? "Ch_White: Yes" : "Ch_White: No") << std::endl;
        std::cout << (isChecked(Board, Map, !White) ? "Ch_Black: Yes" : "Ch_Black: No") << std::endl;
        
        if (isChecked(Board, Map, White)) { //white side turn
            std::cout << "黑色被警告" << std::endl;
        } else if (isChecked(Board, Map, !White)) { //black side turn
            std::cout << "白色被警告" << std::endl;
        }

        // if ((isChecked(Board, Map, White)) || (isChecked(Board, Map, !White))) {
        //     if (!White){
        //         Board[B_kingpos.first][B_kingpos.second].exhibit = BOLD(FRED(C_KING));
        //         std::cout << CLEAR_SCREEN;
        //         printBoard(Board);
        //         std::cout << "Please select your piece by [A-H][1-8]. Ex: a1, b2, A1, B2" << std::endl;
        //         std::cout << "CHECK by White" << std::endl;
        //     }else{
        //         Board[W_kingpos.first][W_kingpos.second].exhibit = BOLD(FRED(C_KING));
        //         std::cout << CLEAR_SCREEN;
        //         printBoard(Board);
        //         std::cout << "Please select your piece by [A-H][1-8]. Ex: a1, b2, A1, B2" << std::endl;
        //         std::cout << "CHECK by Black" << std::endl;
        //     }
        // }

        //PAWN Promotion
        // findPiece(Board, PAWN);
        // findPiece(Board, -PAWN);
        // if (true) {
        //     std::cout << "Please select your PAWN to any piece that you want" << std::endl;
        //     std::cout << "except the KING" << std::endl;
        //     std::cout << "R for ROOK, K for KNIGHT, B for BISHOP, Q for QUEEN" << std::endl;
        //     getInput(origin);
        //     if (origin == "R" || origin == "r") {
        //         /* code */
        //     } else if (origin == "K" || origin == "k") {
        //         /* code */
        //     } else if (origin == "B" || origin == "b") {
        //         /* code */
        //     } else if (origin == "Q" || origin == "q") {
        //         /* code */
        //     } else {
        //         std::cout << "Unavailable select: You can only choose R, K, B, or Q" << std::endl;
        //     }
        // }

        // check if the game is done
        // if (isCheckmated(Board, Map, White)) {
        //     Game = false;
        //     break;
        // }

        if (playerSelect)
            std::cout << "Please select your own game piece" << std::endl;

        getInput(origin);
        if (origin == "UNDO")
            continue;

        Coordinates o = AddresstoIndex(origin);

        if ((White && Board[o.first][o.second].identity <= 0)
            || (!White && Board[o.first][o.second].identity >= 0)) {
            playerSelect = true;
            continue;
        }

        playerSelect = false;

        Moves availableMoves = getAvailableMoves(Board, Map, origin);
        highlight(Board, availableMoves);

        while (true) {
            std::cout << CLEAR_SCREEN;
            printBoard(Board);
            printMoves(availableMoves);

            getInput(destination);

            if (destination == "UNDO") {
                unhighlight(Board, availableMoves);
                break;
            }

            Coordinates d = AddresstoIndex(destination);

            if (!existCoordinate(availableMoves, d))
                continue;

            navigatePiece(Board, o, d);
            unhighlight(Board, availableMoves);
            White = !White;
            break;
        }
    }

    //print the ending message of the game
    if (Game == false) {
        std::cout << "Game Over" << std::endl;
        if (White) {
            std::cout << "YOU WIN" << std::endl;
        } else {
            std::cout << "YOU LOST" << std::endl;
        }
    }

    return 0;
}
