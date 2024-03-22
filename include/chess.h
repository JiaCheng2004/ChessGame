#pragma once

#ifndef CHESS_H_
#define CHESS_H_

// ========================================================================================
// ----------------------------------  Included Library  ----------------------------------
// ========================================================================================

#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include <exception>
#include <vector>

// ========================================================================================
// ----------------------------------  Constant  Values  ----------------------------------
// ========================================================================================

#define BOARD_SIZE      8
#define BOARD_COLUMNS   8
#define BOARD_ROWS      8

#define EMPTY           0
#define PAWN            1
#define ROOK            5
#define KNIGHT          3
#define BISHOP          4
#define QUEEN           10
#define KING            255

// ========================================================================================
// ---------------------------  Customized Type and Structures  ---------------------------
// ========================================================================================

using Chessboard = std::array<std::array<int16_t, BOARD_COLUMNS>, BOARD_ROWS>;

// ========================================================================================
// ----------------------------------  Helper Functions  ----------------------------------
// ========================================================================================

// Create a new board with all pieces
Chessboard newBoard();

// Check if x is in bound of board size
bool inBound(int x);

void setUnmoved(int16_t& piece);

bool getUnmoved(int16_t piece);

// Check if y has the opposite sign of x
bool hasOppositeSign(int x, int y);

// Translate a square's name to a pair of indices that refers to rows and columns
std::pair<int, int> AddresstoIndex(std::string& square);

// Get all the possible moves, except for sliding pieces where it return all the directions
std::vector<std::pair<int, int>> allPossibleMoves(int& piece);

// Get all the moves of the selected square
std::vector<std::pair<int, int>> getMoves(Chessboard& Board, std::pair<int, int> square);

#endif