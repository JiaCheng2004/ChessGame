#include <../include/minimax.h>

std::pair<Coordinates, Coordinates> findMax(valueMap &valMap) {
    std::pair<Coordinates, Coordinates> maxKey;
    int maxValue = INT_MIN;

    for (auto &key_value : valMap) {
        if (maxValue < key_value.second) {
            maxValue = key_value.second;
            maxKey = key_value.first;
        }
    }

    return maxKey;
}

std::pair<Coordinates, Coordinates> findMin(valueMap &valMap) {
    std::pair<Coordinates, Coordinates> minKey;
    int minValue = INT_MAX;

    for (auto &key_value : valMap) {
        if (minValue > key_value.second) {
            minValue = key_value.second;
            minKey = key_value.first;
        }
    }

    return minKey;
}

int vectMin(std::vector<int> &vect) {
    if (vect.empty())
        throw std::invalid_argument("Vector is empty");
    return *std::min_element(vect.begin(), vect.end());
}

int vectMax(std::vector<int> &vect) {
    if (vect.empty())
        throw std::invalid_argument("Vector is empty");
    return *std::max_element(vect.begin(), vect.end());
}

int Minimax(Chessboard &board, Movemaps Map, int depth, bool White) {
    Moves allPieces = findAllPieces(board, White);
    std::vector<int> vect;

    for (Coordinates &pieceLocation : allPieces) {
        Moves allmoves = getAvailableMoves(board, Map, IndextoAddress(pieceLocation));
        for (Coordinates &destination : allmoves) {
            navigatePiece(board, pieceLocation, destination);
            vect.push_back(Minimax(board, Map, depth - 1, !White));
            navigatePiece(board, destination, pieceLocation);
        }
    }

    return White ? vectMax(vect) : vectMin(vect);
}

std::pair<Coordinates, Coordinates> Darwin(Chessboard &board, Movemaps Map, int depth, bool White) {
    Moves allPieces = findAllPieces(board, White);
    valueMap vMap;

    for (Coordinates &pieceLocation : allPieces) {
        Moves allmoves = getAvailableMoves(board, Map, IndextoAddress(pieceLocation));
        for (Coordinates &destination : allmoves) {
            navigatePiece(board, pieceLocation, destination);
            vMap[std::make_pair(pieceLocation, destination)]
                = Minimax(board, Map, depth - 1, !White);
        }
    }

    return White ? findMax(vMap) : findMin(vMap);
}
