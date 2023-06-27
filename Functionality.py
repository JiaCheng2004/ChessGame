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
        self.piece_letter = {
         'king' : 'K',                                                                      # King
         'queen' : 'Q',                                                                     # Queen
         'knight' : 'H',                                                                    # Knight
         'bishop' : 'B',                                                                    # Bishop
         'rook' : 'R',                                                                      # Rook
         'pawn' : 'P'                                                                       # Pawn
         }
        
        self.letter = self.piece_letter[piece.lower()]
        self.moves = self.piece_movements[piece.lower()]
        self.piece = piece
        self.moved = False
        self.owner = owner