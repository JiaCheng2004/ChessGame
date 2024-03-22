#pragma once

#ifndef CHESS_H_
#define CHESS_H_

#include <algorithm>
#include <array>
#include <string>
#include <exception>

#define BOARD_COLUMNS 8
#define BOARD_ROWS 8

using Chessboard = std::array<std::array<int, BOARD_COLUMNS>, BOARD_ROWS>;

Chessboard newBoard();

std::pair<int, int> getIndex(std::string& square);

#endif