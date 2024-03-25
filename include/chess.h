#pragma once

#ifndef CHESS_H_
#define CHESS_H_

// ========================================================================================
// ----------------------------------  Included Library
// ----------------------------------
// ========================================================================================

// Public Library:

#include <algorithm>
#include <array>
#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// Private Library:
#include "colors.h"

// ========================================================================================
// ----------------------------------  Constant  Values
// ----------------------------------
// ========================================================================================

#define BOARD_SIZE    8
#define BOARD_COLUMNS 8
#define BOARD_ROWS    8

#define EMPTY  0
#define PAWN   1
#define ROOK   5
#define KNIGHT 3
#define BISHOP 4
#define QUEEN  10
#define KING   255

#define C_EMPTY  " "
#define C_PAWN   "P"
#define C_ROOK   "R"
#define C_KNIGHT "H"
#define C_BISHOP "B"
#define C_QUEEN  "Q"
#define C_KING   "K"

#define C_AVAILABLE "*"

// ========================================================================================
// ---------------------------  Customized Type and Structures
// ---------------------------
// ========================================================================================

// Define the ChessPiece structure
struct ChessPiece {
    int identity; // Identity of the piece
    int weight; // Weight of the piece for minimax
    const char *exhibit; // Exhibit for text form showcase
    bool moved; // Whether the piece has ever been moved before
};

// Define aliases for chessboard dimensions

using Chessboard = std::array<std::array<ChessPiece, BOARD_SIZE>, BOARD_SIZE>;

using Coordinates = std::pair<int, int>;

using Moves = std::vector<Coordinates>;

using Weight = std::pair<int, int>;

using Movemaps = std::map<int, Moves>;

// ========================================================================================
// ----------------------------------  Helper Functions
// ----------------------------------
// ========================================================================================

// Create a move maps to get every piece's available moves
std::map<int, Moves> createPossibleMovesMap();

// Define function prototypes
ChessPiece createPawn(bool isWhite);
ChessPiece createRook(bool isWhite);
ChessPiece createKnight(bool isWhite);
ChessPiece createBishop(bool isWhite);
ChessPiece createQueen(bool isWhite);
ChessPiece createKing(bool isWhite);

// Create a new board with all pieces
Chessboard newBoard();

Moves getAvailableMoves(Chessboard &Board, Movemaps &Map, std::string Square);

// Translation of Address to Index
Coordinates AddresstoIndex(std::string &square);

std::string IndextoAddress(Coordinates move);

Moves findPiece(Chessboard &board, int Identity);

Weight getTotalWeight(Chessboard &board);

Moves findAllPieces(Chessboard &board, bool White);

bool isChecked(Chessboard &board, Movemaps Map, bool White);

bool isCheckmated(Chessboard &board, Movemaps Map, bool White);

void highlight(Chessboard &board, Moves moves);

void unhighlight(Chessboard &board, Moves moves);

bool existCoordinate(Moves &moves, const Coordinates location);

void navigatePiece(Chessboard &Board, Coordinates Origin, Coordinates Destination);

// Check if the input is inboard
bool inBound(int x);

// Check if x and y are opposite signs
bool haveOppositeSign(int x, int y);

// print the board in text
void printBoard(const Chessboard &board);

void printMoves(const Moves &moves);

void printChessPiece(const ChessPiece &piece);

std::string toChessSquare(const Coordinates &coord);

// Print the ninja confusion
void printConfusion();

#endif