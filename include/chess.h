#pragma once

#ifndef CHESS_H_
#define CHESS_H_

#include <array>

#define BOARD_WIDTH 8
#define BOARD_ROWS 8

using Chessboard = std::array<std::array<int, BOARD_WIDTH>, BOARD_ROWS>;

Chessboard newBoard();

#endif