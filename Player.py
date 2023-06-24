import random
from Functionality import GamePiece


# 从聪明到简单 100 - 0
bot_choices = {
    'Albert': 100,
    'Simon' : 97,
    'Richard' : 97,
    'Jack' : 94,
    'Thomas' : 91, 
    'William' : 87,
    'Matthew' : 84,
    'Charles' : 81,
    'Daniel' : 78,
    'Joshua' : 75,
    'Adam': 72,
    'Edward' : 69,
    'Luke' : 66,
    'Jacob' : 63,
    'Christopher': 60,
    'James' : 57,
    'Timothy' : 54,
    'Steven ' : 51,
    'Robert' : 48,
    'Leonard' : 45,
    'Stanley' : 42,
    'Lawrence' : 39,
    'Philip' : 36,
    'Julia' : 33,
    'Eddie': 30,
    'Tommy' :27,
    'Pete' : 24,
    'Jason' : 21,
    'Jackson' : 18,
    'Leo' : 15,
    'Nicholas' : 12,
    'Arthur' : 9,
    'Hugo' : 6,
    'Nathan': 3,
    'Anthony' : 0,
    }

# 玩家Class

class Player:
    def __init__(self, name = random.choice(bot_choices), bot = True):
        self.name = name
        self.bot = False
        
        # self.棋子[ True/False(是否还有这个棋子)  ,  棋子的机动性]
        self.king = [True, GamePiece.king]
        self.queen = [True, GamePiece.queen]
        self.knight_1 = [True, GamePiece.knight]
        self.knight_2 = [True, GamePiece.knight]
        self.bishop_1 = [True, GamePiece.bishop]
        self.bishop_2 = [True, GamePiece.bishop]
        self.rook_1 = [True, GamePiece.rook]
        self.rook_2 = [True, GamePiece.rook]
        self.pawn_1 = [True, GamePiece.pawn]
        self.pawn_2 = [True, GamePiece.pawn]
        self.pawn_3 = [True, GamePiece.pawn]
        self.pawn_4 = [True, GamePiece.pawn]
        self.pawn_5 = [True, GamePiece.pawn]
        self.pawn_6 = [True, GamePiece.pawn]
        self.pawn_7 = [True, GamePiece.pawn]
        self.pawn_8 = [True, GamePiece.pawn]

        # 所有的棋子状态 (collection)
        self.collection_status = [ self.king, self.queen,
                                    self.knight_1, self.knight_2,
                                    self.bishop_1, self.bishop_2,
                                    self.rook_1, self.rook_2,
                                    self.pawn_1, self.pawn_2,
                                    self.pawn_3, self.pawn_4,
                                    self.pawn_5, self.pawn_6,
                                    self.pawn_7, self.pawn_8 ]

    def won(self):
        return all(self.collection_status)
    
    def winner_name(self):
        return self.name
    
    def is_bot(self):
        return self.bot
    
class AI:

    def __init__(self, difficulty):
        pass