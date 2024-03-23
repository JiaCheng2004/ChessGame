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
    std::string userChoose = "";
    std::string userGo = "";
    printBoard(board);
    // for (int i = 0; i < 8; ++i) {
    //     for (int j = 0; j < 8; ++j) {
    //         printChessPiece(board[i][j]);
    //     }
    // }
    while ( userChoose != "quit" || userGo != "quit") {
        std::cin >> userChoose;
        Moves moves = getAvailableMoves(board, Map, userChoose);
        printMoves(moves);
        std::cin >> userGo;
        navigatePiece(board, userChoose, userGo);
        printBoard(board);
    }

    return 0;
}