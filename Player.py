import random
from Functionality import GamePiece
from colorfont import *

class Player:
    def __init__(self, name):
        self.name = name
        self.bot = False
        self.piece_value = 39
        self.piece_collection = ['king', 'queen', 'rook', 'bishop', 'knight', 'pawn']

    def retrieve_move(self, p = None, *, retriver = None, position = None):
        if p == 's':
            while True:
                response = input(Blue(f'{self.player1}, Please select a game piece: ')).upper()
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
                response = input(f'{self.player1}, Please select a destination: ').upper()
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
    
class AI:

    def __init__(self, difficulty = None):
        # difficulty:
            # Beginner   0 - 19
            # Easy      20 - 39
            # Normal    40 - 59
            # Advanced  60 - 79
            # Master    80 - 100

        # Complex to S1mple 100 - 0
        self.bot_choices = (('Stacey', 100, 37),('Simon' , 97, 36), ('Richard' , 97, 35), ('Jack' , 94, 34), ('Thomas' , 91, 33), ('William' , 87, 32), ('Matthew' , 84, 31), ('Charles' , 81, 30), 
            ('Daniel' , 78, 29),('Joshua' , 75, 28), ('Adam', 72, 27), ('Edward' , 69, 26), ('Luke' , 66, 25), ('Jacob' , 63, 24), ('Christopher', 60, 23), ('James', 57, 22), ('Timothy', 54, 21), 
            ('Steven ', 51, 20),('Robert', 48, 19), ('Leonard', 45, 18), ('Stanley', 42, 17), ('Lawrence', 39, 16), ('Philip', 36, 15), ('Julia', 33, 14), ('Eddie', 30, 13), ('Tommy', 27, 12), 
            ('Pete', 24, 11), ('Jason', 21, 10), ('Jackson', 18, 9), ('Leo', 15, 8), ('Nicholas', 12, 7), ('Arthur', 9, 6), ('Hugo', 6, 5), ('Nathan', 3, 4), ('Anthony', 0, 3))
        
        if difficulty is None:
            self.name, self.complexity, self.depth = random.choice(self.bot_choices)
        elif difficulty == 'beginner': # Beginner   0 - 19
            self.name, self.complexity, self.depth = random.choice(self.bot_choices)[:8]
        elif difficulty == 'easy':     # Easy      20 - 39
            self.name, self.complexity, self.depth = random.choice(self.bot_choices)[8:15]
        elif difficulty == 'normal':   # Normal    40 - 59
            self.name, self.complexity, self.depth = random.choice(self.bot_choices)[15:21]
        elif difficulty == 'advanced': # Advanced  60 - 79
            self.name, self.complexity, self.depth = random.choice(self.bot_choices)[21:28]
        elif difficulty == 'master':   # Master    80 - 100
            self.name, self.complexity, self.depth = random.choice(self.bot_choices)[28:]
        elif difficulty == 'custom': 
            self.name, self.complexity, self.depth = ('TEST', 1, 4)

        self.bot = True
        self.piece_count = 39
        self.piece_collection = ('king', 'queen', 'rook', 'bishop', 'knight', 'pawn')

        print(f"Name: {self.name}\nComplexity: {self.complexity}\nHardness: {self.depth}")

    def get_move(self, board, pov = True): # True -> player1, MAXIMIZING, False -> player2, MINIMIZING
        value_map = {
            "pawn": 1.0, 
            "bishop": 3.0,
            "knight": 3.0,
            "rook": 5.0,
            "queen": 9.0,
            "king": float('inf')
        }
        score_1, score_2 = board.player1.piece_value, board.player2.piece_value

        best_move, best_move_value = None, -float('inf')

        for piece_location in board.find_all_pieces(board.player1):
            for next_move in board.avaliable_moves(piece_location):
                piece, piece_letter = board.locate(piece_location)[1:]
                piece2, piece_letter2  = board.locate(next_move)[1:]
                board.locate(piece_location)[1:] = None, ' '
                board.locate(next_move)[1:] = piece, piece_letter

                if piece2 is not None:
                    if pov:
                        board.player1.piece_value += value_map[piece2.piece]
                        board.player2.piece_value -= value_map[piece2.piece]
                    else:
                        board.player1.piece_value -= value_map[piece2.piece]
                        board.player2.piece_value += value_map[piece2.piece]

                self.minimax(board, self.depth-1, value_map, False)
                
                if board.player1.piece_value > best_move_value:
                    best_move, best_move_value = (piece_location, next_move), board.player1.piece_value

                board.locate(next_move)[1:] = piece2, piece_letter2
                board.locate(piece_location)[1:] = piece, piece_letter
                board.player1.piece_value, board.player2.piece_value = score_1, score_2
                
        return best_move
    
    def minimax(self, board, depth, value_map, pov):
        board.print_board()
        pov = False if pov else True

        if pov: player, opponent = board.player1, board.player2
        else: player, opponent = board.player2, board.player1
        finish = board.gameover()

        score_1, score_2 = board.player1.piece_value, board.player2.piece_value

        if depth == 0 or finish[0]:
            if finish[1] == board.player1:
                board.player1.piece_value += float('inf') 
            else: 
                board.player2.piece_value += float('inf')
            return

        for piece_location in board.find_all_pieces(player):
            for next_move in board.avaliable_moves(piece_location):
                piece, piece_letter = board.locate(piece_location)[1:]
                piece2, piece_letter2 = board.locate(next_move)[1:]
                board.locate(piece_location)[1:] = None, ' '
                board.locate(next_move)[1:] = piece, piece_letter
                if piece2 is not None:
                    player.piece_value += value_map[piece2.piece]
                    opponent.piece_value -= value_map[piece2.piece]

                self.minimax(board, depth-1, value_map, pov)

                board.locate(next_move)[1:] = piece2, piece_letter2
                board.locate(piece_location)[1:] = piece, piece_letter
                board.player1.piece_value, board.player2.piece_value = score_1, score_2
        return