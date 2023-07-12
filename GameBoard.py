from Functionality import GamePiece
from Player import *
from colorfont import *
import random

class Board:
    
    def __init__(self, player1, player2):
        self.player1 = Player(player1)
        self.player2 = Player(player2)
        self.board = [
                [["A1", GamePiece(player1, 'rook'), Blue('R')], ["A2", GamePiece(player1, 'knight'), Blue('H')], ["A3", GamePiece(player1, 'bishop'), Blue('B')], ["A4", GamePiece(player1, 'queen'), Blue('Q')], ["A5", GamePiece(player1, 'king'), Blue('K')], ["A6", GamePiece(player1, 'bishop'), Blue('B')], ["A7", GamePiece(player1, 'knight'), Blue('H')], ["A8", GamePiece(player1, 'rook'), Blue('R')]],
                [["B1", GamePiece(player1, 'pawn'), Blue('P')], ["B2", GamePiece(player1, 'pawn'), Blue('P')], ["B3", GamePiece(player1, 'pawn'), Blue('P')], ["B4", GamePiece(player1, 'pawn'), Blue('P')], ["B5", GamePiece(player1, 'pawn'), Blue('P')], ["B6", GamePiece(player1, 'pawn'), Blue('P')], ["B7", GamePiece(player1, 'pawn'), Blue('P')], ["B8", GamePiece(player1, 'pawn'), Blue('P')]],
                [["C1", None, ' '], ["C2", None, ' '], ["C3", None, ' '], ["C4", None, ' '], ["C5", None, ' '], ["C6", None, ' '], ["C7", None, ' '], ["C8", None, ' ']],
                [["D1", None, ' '], ["D2", None, ' '], ["D3", None, ' '], ["D4", None, ' '], ["D5", None, ' '], ["D6", None, ' '], ["D7", None, ' '], ["D8", None, ' ']],
                [["E1", None, ' '], ["E2", None, ' '], ["E3", None, ' '], ["E4", None, ' '], ["E5", None, ' '], ["E6", None, ' '], ["E7", None, ' '], ["E8", None, ' ']],
                [["F1", None, ' '], ["F2", None, ' '], ["F3", None, ' '], ["F4", None, ' '], ["F5", None, ' '], ["F6", None, ' '], ["F7", None, ' '], ["F8", None, ' ']],
                [["G1", GamePiece(player2, 'pawn'), Green('P')], ["G2", GamePiece(player2, 'pawn'), Green('P')], ["G3", GamePiece(player2, 'pawn'), Green('P')], ["G4", GamePiece(player2, 'pawn'), Green('P')], ["G5", GamePiece(player2, 'pawn'), Green('P')], ["G6", GamePiece(player2, 'pawn'), Green('P')], ["G7", GamePiece(player2, 'pawn'), Green('P')], ["G8", GamePiece(player2, 'pawn'), Green('P')]],
                [["H1", GamePiece(player2, 'rook'), Green('R')], ["H2", GamePiece(player2, 'knight'), Green('H')], ["H3", GamePiece(player2, 'bishop'), Green('B')], ["H4", GamePiece(player2, 'queen'), Green('Q')], ["H5", GamePiece(player2, 'king'), Green('K')], ["H6", GamePiece(player2, 'bishop'), Green('B')], ["H7", GamePiece(player2, 'knight'), Green('H')], ["H8", GamePiece(player2, 'rook'), Green('R')]]
                ]

        self.input_options = (("A", "B", "C", "D", "E", "F", "G", "H"), ('1', '2', '3', '4', '5', '6', '7', '8'))
        self.castle_checker = [['A2','A3','A4'], ['A6','A7'], ['H2','H3','H4'], ['H6','H7']]
        self.castle_position = {('A5','A1'): ['A3','A4'], ('A5','A8'): ['A7','A6'], ('H5','H1'): ['H3','H4'], ('H5','H8'): ['H7','H6']}
        
    def retrieve_move(self, phrase, p = None, *, retriver = None, position = None):
        if p == 's':
            while True:
                response = input(phrase).upper()
                if len(response) != 2 or not self.valid_move(response):
                    print(Red("Invalid input![A-H, 1-8]"))
                    continue
                elif len(response) == 2 and self.valid_move(response):
                    if self.locate(response)[1] is None:
                        print(Red("You can't select a blank space."))
                        continue
                    elif self.locate(response)[1].owner != retriver:
                        print(Red("Please only pick your own game piece."))
                        continue
                    else:
                        if len(self.avaliable_moves(response.upper())) != 0:
                            return response
                        else:
                            print(Red("This piece can't move anywhere."))
                            continue
                continue
        
        elif p == 'd':
            available_moves = self.avaliable_moves(position.upper())
            while True:
                response = input(phrase).upper()
                if response.lower() in ['undo','cancel']:
                    self.unshow_avaliable_moves(available_moves)
                    self.print_board()
                    return None
                if len(response) != 2 or not self.valid_move(response):
                    print(Red("Invalid input![A-H, 1-8]"))
                    continue
                if response not in available_moves:
                    print(Red("You can't move there."))
                    continue
                else: 
                    self.unshow_avaliable_moves(available_moves)
                    return response
        
    def valid_move(self, move):
        return True if (move[0] in self.input_options[0]) and (move[1] in self.input_options[1]) else False

    def move(self, origin , destination):
        piece, piece_letter = self.locate(origin)[1:]
        piece2 = self.locate(destination)[1]
        if piece.piece == 'pawn':
            piece.moved = True
            if piece.owner == self.player1.name and destination[0] == 'H':
                piece, piece_letter = GamePiece(self.player1, 'queen'), Blue('Q')
            elif piece.owner == self.player2.name and destination[0] == 'A':
                piece, piece_letter = GamePiece(self.player2, 'queen'), Green('Q')
        elif piece is not None and piece2 is not None:
            if (piece.piece == 'king') and (piece2.piece == 'rook') and (piece.owner == piece2.owner):
                self.castle(origin, destination)
                piece.moved, piece2.moved = True, True
                return
        self.locate(origin)[1:] = None, ' '
        self.locate(destination)[1:] = piece, piece_letter
        return
    
    def return_board_status(self):
        return self.board
    
    def locate(self, location):
        return self.board[ord(location[0].upper())-ord('A')][int(location[1])-1]
    
    def index_locate(self, alph, num):
        return self.board[alph][num]
    
    def string_to_index(self, location):
        return ord(location[0].upper())-ord('A'), int(location[1])-1
    
    def index_to_string(self, alph, num):
        return chr(alph+ord('A')) + str(num+1)
    
    def find_pieces(self, player, piece_name):
        piece = []
        for row in range(len(self.board)):
            for square in range(len(self.board[row])):
                if self.board[row][square][1] is None:
                    continue 
                elif self.board[row][square][1].owner == player.name and self.board[row][square][1].piece == piece_name:
                    piece.append(self.index_to_string(row, square))
        return piece
    
    def find_all_pieces(self, player):
        piece = []
        for row in range(len(self.board)):
            for square in range(len(self.board[row])):
                if self.board[row][square][1] is None:
                    continue 
                elif self.board[row][square][1].owner == player.name:
                    piece.append(self.index_to_string(row, square))
        return piece
    
    def is_checked(self, check_player):
        if check_player == self.player1.name:
            player = self.player1
            opponent = self.player2
        else:
            player = self.player2
            opponent = self.player1
            
        king_location = self.find_pieces(player, 'king')[0]
        pieces_location = self.find_all_pieces(opponent)
        for location in pieces_location:
            if king_location in self.avaliable_moves(location):
                return location
        return False
    
    def is_checkmate(self, check_player):
        player = self.player1 if check_player == self.player1.name else self.player2
        
        player_pieces = self.find_all_pieces(player)
        
        for location in player_pieces:
            for next_move in self.avaliable_moves(location):

                piece, piece_letter = self.locate(location)[1:]
                piece2, piece_letter2 = self.locate(next_move)[1:]
                self.locate(location)[1:] = None, ' '
                self.locate(next_move)[1:] = piece, piece_letter

                if self.is_checked(player.name):
                    self.locate(next_move)[1:] = piece2, piece_letter2
                    self.locate(location)[1:] = piece, piece_letter
                    continue
                else:
                    self.locate(next_move)[1:] = piece2, piece_letter2
                    self.locate(location)[1:] = piece, piece_letter
                    return False
            
        return True
    
    def gameover(self):
        p1, p2 = False, False
        for row in self.board:
            for square in row:
                if square[1] is None:
                    continue
                if square[1].piece == 'king':
                    if square[1].owner == self.player1.name:
                        p1 = True
                    elif square[1].owner == self.player2.name:
                        p2 = True
        if p1 and p2:
            return False, None
        elif p1:
            return True, self.player1
        elif p2:
            return True, self.player2

    def generate(self):
        return random.choice(["A", "B", "C", "D", "E", "F", "G", "H"]) + random.choice(['1', '2', '3', '4', '5', '6', '7', '8'])
    
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
            if tag.moved == False:
                return self.pawn_moves(tag, alph_index, num_index)
            else:
                return self.pawn_moves(tag, alph_index, num_index, start = False)
        
    def show_avaliable_moves(self, locations):
        for location in locations:
            square = self.locate(location)
            if square[2] == ' ':
                square[2] = Yellow('*')
            else:
                square[2] = Yellow(square[1].letter)

    def unshow_avaliable_moves(self, locations): # True is Green, False is Blue
        for location in locations:
            square = self.locate(location)
            if square[2] == Yellow('*'):
                square[2] = ' '
            elif square[2] != ' ':
                if square[1].owner == self.player1.name:
                    square[2] = Blue(square[1].letter)
                else:
                    square[2] = Green(square[1].letter)

    def knight_moves(self, tag, alph_index, num_index):
        avaliable = []
        
        for alph, num in tag.moves:
            alph, num = alph_index+alph, num_index+num
            if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) != tag.owner):
                avaliable.append(self.index_to_string(alph, num))
        
        return avaliable

    def bishop_moves(self, tag, alph_index, num_index):
        avaliable = []
        
        for alph, num in tag.moves:
            avaliable.extend(self.swing(tag, alph_index, num_index, alph, num))
        
        return avaliable

    def rook_moves(self, tag, alph_index, num_index):
        avaliable = []
        
        for alph, num in tag.moves:
            avaliable.extend(self.swing(tag, alph_index, num_index, alph, num))
        
        return avaliable

    def queen_moves(self, tag, alph_index, num_index):
        avaliable = []
        
        for alph, num in tag.moves:
            avaliable.extend(self.swing(tag, alph_index, num_index, alph, num))
        
        return avaliable

    def king_moves(self, tag, alph_index, num_index):
        avaliable = []

        if not tag.moved:
            if tag.owner == self.player1.name:
                rook1, rook2 = self.locate('A1')[1], self.locate('A8')[1]
                if rook1 != None:
                    if not rook1.moved:
                        if all([self.locate(location)[1] is None for location in self.castle_checker[0]]):
                            avaliable.append('A1') 
                if rook2 != None:
                    if not rook2.moved:
                        if all([self.locate(location)[1] is None for location in self.castle_checker[1]]):
                            avaliable.append('A8')
            elif tag.owner == self.player2.name:
                rook3, rook4 = self.locate('H1')[1], self.locate('H8')[1]
                if rook3 != None:
                    if not rook3.moved:
                        if all([self.locate(location)[1] is None for location in self.castle_checker[2]]):
                            avaliable.append('H1') 
                if rook4 != None:
                    if not rook4.moved:
                        if all([self.locate(location)[1] is None for location in self.castle_checker[3]]):
                            avaliable.append('H8')

        for alph, num in tag.moves:
            alph, num = alph_index+alph, num_index+num
            if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) != tag.owner):
                avaliable.append(self.index_to_string(alph, num))

        return avaliable

    def pawn_moves(self, tag, alph_index, num_index, start = True):
        avaliable = []
        if start:
            for alph, num in tag.moves[2]:
                if tag.owner == self.player2.name: alph *= -1
                alph, num = alph_index+alph, num_index+num
                if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) not in [tag.owner, None]):
                    avaliable.append(self.index_to_string(alph, num))
            for alph, num in tag.moves[1]:
                if tag.owner == self.player2.name: alph *= -1
                alph, num = alph_index+alph, num_index+num
                if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) is None):
                    avaliable.append(self.index_to_string(alph, num))
            for alph, num in tag.moves[0]:
                if tag.owner == self.player2.name: alph *= -1
                alph, num = alph_index+alph, num_index+num
                if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) is None):
                    avaliable.append(self.index_to_string(alph, num))
        else:
            for alph, num in tag.moves[2]:
                if tag.owner == self.player2.name: alph *= -1
                alph, num = alph_index+alph, num_index+num
                if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) not in [tag.owner, None]):
                    avaliable.append(self.index_to_string(alph, num))
            for alph, num in tag.moves[0]:
                if tag.owner == self.player2.name: alph *= -1
                alph, num = alph_index+alph, num_index+num
                if self.in_bounds(alph, num) and (self.piece_owner_index(alph, num) is None):
                    avaliable.append(self.index_to_string(alph, num))
        
        return avaliable
    
    def castle(self, king_origin, rook_origin):
        king_destination, rook_destination = self.castle_position[(king_origin, rook_origin)]

        king, king_letter = self.locate(king_origin)[1:]
        self.locate(king_origin)[1:] = None, ' '
        self.locate(king_destination)[1:] = king, king_letter

        rook, rook_letter = self.locate(rook_origin)[1:]
        self.locate(rook_origin)[1:] = None, ' '
        self.locate(rook_destination)[1:] = rook, rook_letter

        return

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
    print(Red('Go to Chess.py'))