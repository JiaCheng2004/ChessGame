from Functionality import GamePiece
class Board:
    
    def __init__(self):
        self.board = [
                [["A1", GamePiece().Rook], ["A2", GamePiece().Knight], ["A3", GamePiece().Bishop], ["A4", GamePiece().Queen], ["A5", GamePiece().King], ["A6", GamePiece().Bishop], ["A7", GamePiece().Knight], ["A8", GamePiece().Rook]],
                [["B1", GamePiece().Pawn], ["B2", GamePiece().Pawn], ["B3", GamePiece().Pawn], ["B4", GamePiece().Pawn], ["B5", GamePiece().Pawn], ["B6", GamePiece().Pawn], ["B7", GamePiece().Pawn], ["B8", GamePiece().Pawn]],
                [["C1"], ["C2"], ["C3"], ["C4"], ["C5"], ["C6"], ["C7"], ["C8"]],
                [["D1"], ["D2"], ["D3"], ["D4"], ["D5"], ["D6"], ["D7"], ["D8"]],
                [["E1"], ["E2"], ["E3"], ["E4"], ["E5"], ["E6"], ["E7"], ["E8"]],
                [["F1"], ["F2"], ["F3"], ["F4"], ["F5"], ["F6"], ["F7"], ["F8"]],
                [["G1", GamePiece().Pawn], ["G2", GamePiece().Pawn], ["G3", GamePiece().Pawn], ["G4", GamePiece().Pawn], ["G5", GamePiece().Pawn], ["G6", GamePiece().Pawn], ["G7", GamePiece().Pawn], ["G8", GamePiece().Pawn]],
                [["H1", GamePiece().Rook], ["H2", GamePiece().Knight], ["H3", GamePiece().Bishop], ["H4", GamePiece().Queen], ["H5", GamePiece().King], ["H6", GamePiece().Bishop], ["H7", GamePiece().Knight], ["H8", GamePiece().Rook]]
                ]

