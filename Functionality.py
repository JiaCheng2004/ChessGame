class GamePiece():

    def __init__(self, name, piece):

        self.piece_movements = {
         'king' : ((0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,-1),(-1,1)),              # King
         'queen' : ((0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,-1),(-1,1)),             # Queen
         'knight' : ((1,2),(-1,2),(2,1),(2,-1),(2,1),(-2,1),(-2,-1),(-1,-2),(1,-2)),    # Knight
         'bishop' : ((1,1),(1,-1),(-1,1),(-1,-1)),                                      # Bishop
         'rook' : ((1,0),(-1,0),(0,1),(0,-1)),                                          # Rook
         'pawn' : ((0,1),(0,2),(1,1),(-1,1))                                            # Pawn
         }
        
        self.moves = self.piece_movements[piece.lower()]
        self.name = name
        
        
        

    # def king(self):
    #     return None
    
    # def queen(self):
    #     return None
    
    # def bishop(self):
    #     return None
    
    # def rook(self):
    #     return None
    
    # def knight(self):
    #     return None
    
    # def pawn(self):
    #     return None
    
    # NEED MORE EDIT **DETAILS**