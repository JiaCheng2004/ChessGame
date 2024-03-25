#pragma once

#ifndef MINIMAX_H_
#define MINIMAX_H_

#include <../include/chess.h>
#include <climits>
std::pair<Coordinates, Coordinates> Darwin(Chessboard &board, Movemaps Map, int depth, bool White);

std::pair<Coordinates, Coordinates> Darwin(Chessboard &board, Movemaps Map, int depth, bool White);

int Minimax(Chessboard &board, Movemaps Map, int d, bool White);

using valueMap = std::map<std::pair<Coordinates, Coordinates>, int>;

std::pair<Coordinates, Coordinates> findMax(valueMap &valMap);

std::pair<Coordinates, Coordinates> findMin(valueMap &valMap);

#endif