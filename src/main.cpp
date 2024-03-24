#include <../include/main.h>

int main(int argc, char* argv []) {
    int verbose = 0;
    std::string testFile;
    std::string aiName;

    const char *const short_opts = "vVdDt:T:a:";
    const option long_opts[] = {
        {"verbose", no_argument, nullptr, 'v'},
        {"debug", no_argument, nullptr, 'd'},
        {"test", required_argument, nullptr, 't'},
        {"bot", required_argument, nullptr, 'a'},
        {"ai", required_argument, nullptr, 'a'},
        {nullptr, 0, nullptr, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
        switch (opt) {
            case 'v':
            case 'V':
            case 'd':
            case 'D':
                verbose = 1;
                break;
            case 't':
            case 'T':
                testFile = optarg;
                break;
            case 'a':
                aiName = optarg;
                break;
            default:
                print_usage();
        }
    }

    if (verbose) {
        if (!testFile.empty())
            std::cout << "Test File: " << testFile << std::endl;
        if (!aiName.empty())
            std::cout << "AI Name: " << aiName << std::endl;
    }

    Chessboard board = newBoard();
    Movemaps Map = createPossibleMovesMap();
    bool Game = true;
    bool White = true;
    std::string origin = "";
    std::string destination = "";

    while (Game) {
        printBoard(board);
        getInput(origin);
        Coordinates o = AddresstoIndex(origin);

        if (White) {
            if (board[o.first][o.second].identity <= 0)
                continue;
        } else {
            if (board[o.first][o.second].identity >= 0)
                continue;  
        }

        Moves availableMoves = getAvailableMoves(board, Map, origin);
        highlight(board, availableMoves);

        while (true) {
            printBoard(board);
            getInput(destination);
            if (destination == "undo") {
                unhighlight(board, availableMoves);
                break;
            }
            Coordinates address = AddresstoIndex(destination);
            if (existCoordinate(availableMoves, address)) {
                navigatePiece(board, origin, destination);
                unhighlight(board, availableMoves);
                White = !White;
            } else {
                continue;
            }
        }
    }

    return 0;
}