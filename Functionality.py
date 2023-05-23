class GamePiece:

    def __init__(self):
        self.King = ((0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,-1),(-1,1))
        self.Queen = ((0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,-1),(-1,1))
        self.Knight = ((1,2),(-1,2),(2,1),(2,-1),(2,1),(-2,1),(-2,-1),(-1,-2),(1,-2))
        self.Bishop = ((1,1),(1,-1),(-1,1),(-1,-1))
        self.Rook = ((1,0),(-1,0),(0,1),(0,-1))
        self.Pawn = ((0,1),(0,2),(1,1),(-1,1))

    def king(self):
        return None
    
    def queen(self):
        return None
    
    def bishop(self):
        return None
    
    def rook(self):
        return None
    
    def knight(self):
        return None
    
    def pawn(self):
        return None
    
    # NEED MORE EDIT **DETAILS**