import random
from Functionality import GamePiece

class Player:
    def __init__(self, name):
        self.name = name
        self.bot = False
        self.piece_value = 39
        self.piece_collection = ['king', 'queen', 'rook', 'bishop', 'knight', 'pawn']
    
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

        self.bot = True
        self.piece_count = 39
        self.piece_collection = ('king', 'queen', 'rook', 'bishop', 'knight', 'pawn')

    def get_move(self, board, depth, pov = True): # True -> player1, MAXIMIZING, False -> player2, MINIMIZING
        piece_value = {
            "pawn": 1.0, 
            "bishop": 3.0,
            "rook": 5.0,
            "queen": 9.0,
            "king": float('inf')
        }

        if pov:
            board.player1