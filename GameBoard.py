from Functionality import GamePiece
from colorfont import *

class Board:
    
    def __init__(self, player1, player2):
        self.board = [
                [["A1", GamePiece(player1, 'rook'), Red('R')], ["A2", GamePiece(player1, 'knight'), Red('H')], ["A3", GamePiece(player1, 'bishop'), Red('B')], ["A4", GamePiece(player1, 'queen'), Red('Q')], ["A5", GamePiece(player1, 'king'), Red('K')], ["A6", GamePiece(player1, 'bishop'), Red('B')], ["A7", GamePiece(player1, 'knight'), Red('H')], ["A8", GamePiece(player1, 'rook'), Red('R')]],
                [["B1", GamePiece(player1, 'pawn'), Red('P')], ["B2", GamePiece(player1, 'pawn'), Red('P')], ["B3", GamePiece(player1, 'pawn'), Red('P')], ["B4", GamePiece(player1, 'pawn'), Red('P')], ["B5", GamePiece(player1, 'pawn'), Red('P')], ["B6", GamePiece(player1, 'pawn'), Red('P')], ["B7", GamePiece(player1, 'pawn'), Red('P')], ["B8", GamePiece(player1, 'pawn'), Red('P')]],
                [["C1", None, ' '], ["C2", None, ' '], ["C3", None, ' '], ["C4", None, ' '], ["C5", None, ' '], ["C6", None, ' '], ["C7", None, ' '], ["C8", None, ' ']],
                [["D1", None, ' '], ["D2", None, ' '], ["D3", None, ' '], ["D4", None, ' '], ["D5", None, ' '], ["D6", None, ' '], ["D7", None, ' '], ["D8", None, ' ']],
                [["E1", None, ' '], ["E2", None, ' '], ["E3", None, ' '], ["E4", None, ' '], ["E5", None, ' '], ["E6", None, ' '], ["E7", None, ' '], ["E8", None, ' ']],
                [["F1", None, ' '], ["F2", None, ' '], ["F3", None, ' '], ["F4", None, ' '], ["F5", None, ' '], ["F6", None, ' '], ["F7", None, ' '], ["F8", None, ' ']],
                [["G1", GamePiece(player2, 'pawn'), Green('P')], ["G2", GamePiece(player2, 'pawn'), Green('P')], ["G3", GamePiece(player2, 'pawn'), Green('P')], ["G4", GamePiece(player2, 'pawn'), Green('P')], ["G5", GamePiece(player2, 'pawn'), Green('P')], ["G6", GamePiece(player2, 'pawn'), Green('P')], ["G7", GamePiece(player2, 'pawn'), Green('P')], ["G8", GamePiece(player2, 'pawn'), Green('P')]],
                [["H1", GamePiece(player2, 'rook'), Green('R')], ["H2", GamePiece(player2, 'knight'), Green('H')], ["H3", GamePiece(player2, 'bishop'), Green('B')], ["H4", GamePiece(player2, 'queen'), Green('Q')], ["H5", GamePiece(player2, 'king'), Green('K')], ["H6", GamePiece(player2, 'bishop'), Green('B')], ["H7", GamePiece(player2, 'knight'), Green('H')], ["H8", GamePiece(player2, 'rook'), Green('R')]]
                ]

        self.input_options = (("A", "B", "C", "D", "E", "F", "G", "H"),('1', '2', '3', '4', '5', '6', '7', '8'))

    def retrieve_move(self, phrase, p = None):
        if p == 'move':
            while True:
                response = input(phrase).upper()
                if len(response) == 2 and self.valid_move(response):
                    return response
        
    def valid_move(self, move):
        return True if (move[0] in self.input_options[0]) and (move[1] in self.input_options[1]) else False

    def move(self, origin , destination):
        piece, piece_letter = self.locate(origin)[1:]
        self.locate(origin)[1:] = None, ' '
        self.locate(destination)[1:] = piece, piece_letter
        return

    def return_board_status(self):
        return self.board
    
    def locate(self, location):
        return self.board[ord(location[0].upper())-ord('A')][int(location[1])-1]
    
    def string_to_index(self, location):
        return ord(location[0].upper())-ord('A'), int(location[1])-1
    
    def index_to_string(self, alph, num):
        return chr(alph+ord('A')) + str(num+1)
    
    def game_over(self):
        pass
    
    def piece_owner_str(self, location):
        return None if self.locate(location)[1] is None else self.locate(location)[1].owner
    
    def piece_owner_index(self, alph_index, num_index):
        return None if self.board[alph_index][num_index][1] is None else self.board[alph_index][num_index][1].owner
    
    def in_bounds(self, alph, num):
        return True if (0 <= alph < 8) and (0 <= num < 8) else False
    
    def avaliable_moves(self, location):
        piece = self.locate(location)
        if piece[1] is None: return []
        
        tag = piece[1]
        alph_index, num_index = self.string_to_index(location)
        
        if tag.piece == 'king':
            return self.king_moves(tag, alph_index, num_index)
        elif tag.piece == 'knight':
            return self.knight_moves(tag, alph_index, num_index)
        elif tag.piece == 'queen':
            return self.queen_moves(tag, alph_index, num_index)
        elif tag.piece == 'bishop':
            return self.bishop_moves(tag, alph_index, num_index)
        elif tag.piece == 'rook':
            return self.rook_moves(tag, alph_index, num_index)
        elif tag.piece == 'pawn':
            return self.pawn_moves(tag, alph_index, num_index)

    def knight_moves(self, tag, alph_index, num_index):
        avaliable = []
        
        for alph, num in tag.moves:
            alph, num = alph_index+alph, num_index+num
            if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) != tag.owner):
                avaliable.append(self.index_to_string(alph, num))
        
        print(avaliable)
        return avaliable

    def bishop_moves(self, tag, alph_index, num_index):
        avaliable = []
        
        for alph, num in tag.moves:
            avaliable.extend(self.swing(tag, alph_index, num_index, alph, num))
        
        print(avaliable)
        return avaliable

    def rook_moves(self, tag, alph_index, num_index):
        avaliable = []
        
        for alph, num in tag.moves:
            avaliable.extend(self.swing(tag, alph_index, num_index, alph, num))
        
        print(avaliable)
        return avaliable

    def queen_moves(self, tag, alph_index, num_index):
        avaliable = []
        
        for alph, num in tag.moves:
            avaliable.extend(self.swing(tag, alph_index, num_index, alph, num))
        
        print(avaliable)
        return avaliable

    def king_moves(self, tag, alph_index, num_index, casteling = True):
        avaliable = []
        
        for alph, num in tag.moves:
            alph, num = alph_index+alph, num_index+num
            if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) != tag.owner):
                avaliable.append(self.index_to_string(alph, num))

        print(avaliable)
        return avaliable

    def pawn_moves(self, tag, alph_index, num_index, start = False):
        avaliable = []
        if start:
            for alph, num in tag.moves[2]:
                alph, num = alph_index+alph, num_index+num
                if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) not in [tag.owner, None]):
                    avaliable.append(self.index_to_string(alph, num))
            for alph, num in tag.moves[1]:
                alph, num = alph_index+alph, num_index+num
                if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) is None):
                    avaliable.append(self.index_to_string(alph, num))
            for alph, num in tag.moves[0]:
                alph, num = alph_index+alph, num_index+num
                if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) is None):
                    avaliable.append(self.index_to_string(alph, num))
        else:
            for alph, num in tag.moves[2]:
                alph, num = alph_index+alph, num_index+num
                if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) not in [tag.owner, None]):
                    avaliable.append(self.index_to_string(alph, num))
            for alph, num in tag.moves[0]:
                alph, num = alph_index+alph, num_index+num
                if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) is None):
                    avaliable.append(self.index_to_string(alph, num))
        
        print(avaliable)
        return avaliable

    def swing(self, tag, alph_index, num_index, alph_movement, num_movement):
        alph, num = alph_index + alph_movement, num_index + num_movement
        if not self.in_bounds(alph, num):
            return []
        if self.piece_owner_index(alph, num) == tag.owner:
            return []
        elif self.piece_owner_index(alph, num) not in [tag.owner, None]:
            return [self.index_to_string(alph, num)]
        
        return [self.index_to_string(alph, num)] + self.swing(tag, alph, num, alph_movement, num_movement)
    
    def print_board(self):
        print(f'''
    1   2   3   4   5   6   7   8
  +---+---+---+---+---+---+---+---+
A | {self.board[0][0][2]} | {self.board[0][1][2]} | {self.board[0][2][2]} | {self.board[0][3][2]} | {self.board[0][4][2]} | {self.board[0][5][2]} | {self.board[0][6][2]} | {self.board[0][7][2]} |
  +---+---+---+---+---+---+---+---+
B | {self.board[1][0][2]} | {self.board[1][1][2]} | {self.board[1][2][2]} | {self.board[1][3][2]} | {self.board[1][4][2]} | {self.board[1][5][2]} | {self.board[1][6][2]} | {self.board[1][7][2]} |
  +---+---+---+---+---+---+---+---+
C | {self.board[2][0][2]} | {self.board[2][1][2]} | {self.board[2][2][2]} | {self.board[2][3][2]} | {self.board[2][4][2]} | {self.board[2][5][2]} | {self.board[2][6][2]} | {self.board[2][7][2]} |
  +---+---+---+---+---+---+---+---+
D | {self.board[3][0][2]} | {self.board[3][1][2]} | {self.board[3][2][2]} | {self.board[3][3][2]} | {self.board[3][4][2]} | {self.board[3][5][2]} | {self.board[3][6][2]} | {self.board[3][7][2]} |
  +---+---+---+---+---+---+---+---+
E | {self.board[4][0][2]} | {self.board[4][1][2]} | {self.board[4][2][2]} | {self.board[4][3][2]} | {self.board[4][4][2]} | {self.board[4][5][2]} | {self.board[4][6][2]} | {self.board[4][7][2]} |
  +---+---+---+---+---+---+---+---+
F | {self.board[5][0][2]} | {self.board[5][1][2]} | {self.board[5][2][2]} | {self.board[5][3][2]} | {self.board[5][4][2]} | {self.board[5][5][2]} | {self.board[5][6][2]} | {self.board[5][7][2]} |
  +---+---+---+---+---+---+---+---+
G | {self.board[6][0][2]} | {self.board[6][1][2]} | {self.board[6][2][2]} | {self.board[6][3][2]} | {self.board[6][4][2]} | {self.board[6][5][2]} | {self.board[6][6][2]} | {self.board[6][7][2]} |
  +---+---+---+---+---+---+---+---+
H | {self.board[7][0][2]} | {self.board[7][1][2]} | {self.board[7][2][2]} | {self.board[7][3][2]} | {self.board[7][4][2]} | {self.board[7][5][2]} | {self.board[7][6][2]} | {self.board[7][7][2]} |
  +---+---+---+---+---+---+---+---+''')

if __name__ == '__main__':
    Game = Board('Alex', 'John')
    while True:
        Game.print_board()
        origin, destination = Game.retrieve_move('Select you want to move: ', p = 'move'), Game.retrieve_move('Move it to: ', p = 'move')
        Game.move(origin, destination)
        Game.avaliable_moves(destination)