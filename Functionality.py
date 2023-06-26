class GamePiece():

    def __init__(self, owner, piece):

        self.piece_movements = {
         'king' : ((0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,-1),(-1,1)),                  # King
         'queen' : ((0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,-1),(-1,1)),                 # Queen
         'knight' : ((1,2),(-1,2),(2,1),(2,-1),(2,1),(-2,1),(-2,-1),(-1,-2),(1,-2)),        # Knight
         'bishop' : ((1,1),(1,-1),(-1,1),(-1,-1)),                                          # Bishop
         'rook' : ((1,0),(-1,0),(0,1),(0,-1)),                                              # Rook
         'pawn' : [[[1,0]],[[2,0]],[[1,1],[1,-1]]]                                          # Pawn
         }
        
        self.moves = self.piece_movements[piece.lower()]
        self.piece = piece
        self.moved = True if piece.lower() in ['king', 'rook', 'pawn'] else None
        self.owner = owner