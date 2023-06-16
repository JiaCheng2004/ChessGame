from Functionality import GamePiece

class Board:
    
    def __init__(self, player1, player2):
        self.board = [
                [["A1", GamePiece(player1, 'rook')], ["A2", GamePiece(player1, 'knight')], ["A3", GamePiece(player1, 'bishop')], ["A4", GamePiece(player1, 'queen')], ["A5", GamePiece(player1, 'king')], ["A6", GamePiece(player1, 'bishop')], ["A7", GamePiece(player1, 'knight')], ["A8", GamePiece(player1, 'rook')]],
                [["B1", GamePiece(player1, 'pawn')], ["B2", GamePiece(player1, 'pawn')], ["B3", GamePiece(player1, 'pawn')], ["B4", GamePiece(player1, 'pawn')], ["B5", GamePiece(player1, 'pawn')], ["B6", GamePiece(player1, 'pawn')], ["B7", GamePiece(player1, 'pawn')], ["B8", GamePiece(player1, 'pawn')]],
                [["C1", None], ["C2", None], ["C3", None], ["C4", None], ["C5", None], ["C6", None], ["C7", None], ["C8", None]],
                [["D1", None], ["D2", None], ["D3", None], ["D4", None], ["D5", None], ["D6", None], ["D7", None], ["D8", None]],
                [["E1", None], ["E2", None], ["E3", None], ["E4", None], ["E5", None], ["E6", None], ["E7", None], ["E8", None]],
                [["F1", None], ["F2", None], ["F3", None], ["F4", None], ["F5", None], ["F6", None], ["F7", None], ["F8", None]],
                [["G1", GamePiece(player2, 'pawn')], ["G2", GamePiece(player2, 'pawn')], ["G3", GamePiece(player2, 'pawn')], ["G4", GamePiece(player2, 'pawn')], ["G5", GamePiece(player2, 'pawn')], ["G6", GamePiece(player2, 'pawn')], ["G7", GamePiece(player2, 'pawn')], ["G8", GamePiece(player2, 'pawn')]],
                [["H1", GamePiece(player2, 'rook')], ["H2", GamePiece(player2, 'knight')], ["H3", GamePiece(player2, 'bishop')], ["H4", GamePiece(player2, 'queen')], ["H5", GamePiece(player2, 'king')], ["H6", GamePiece(player2, 'bishop')], ["H7", GamePiece(player2, 'knight')], ["H8", GamePiece(player2, 'rook')]]
                ]

        self.input_options = (
            ("A", "B", "C", "D", "E", "F", "G", "H")
            (1, 2, 3, 4, 5, 6)
        )

    def get_move(self, phrase):
        response = input(phrase)
        if self.valid_move(response.upper()):
            return response

    def valid_move(self, move):
        if ((len(move) == 2) and (move[0] in self.input_options[0]) and (move[1] in self.input_options[1])):
            return True

    def move(self, origin , destination):
        piece = self.board[ord(origin[0].upper())-ord('A')].pop([origin[1]-1])
        self.board[ord(origin[0].upper())-ord('A')][origin[1]-1] = None
        self.board[ord(destination[0].upper())-ord('A')][destination[1]-1] = piece
        return

    def return_board_status(self):
        return self.board