import GameBoard
import colorfont as cf
import random

class Match:
    def __init__(self, Player1, Player2):
        self.player1 = Player1
        self.player2 = Player2
        self.Board = GameBoard.Board(self.player1, self.player2)

    def start(self, player = True):
        self.Board.print_board()
        over = self.Board.gameover()
        if not over[0]:
            if player:
                while True:
                    if self.Board.is_checked(self.player1):
                        print(f"Watch out {self.player1}! You're checked!")
                    selected = self.Board.retrieve_move(cf.Green(f'{self.player1}, Please select a game piece: '), p = 's', retriver = self.player2)
                    available = self.Board.avaliable_moves(selected)
                    self.Board.show_avaliable_moves(available)
                    self.Board.print_board()
                    destination = self.Board.retrieve_move(cf.Green(f'{self.player1}, Please select a destination: '), p = 'd', retriver = self.player2, position = selected)
                    if destination is None:
                        continue
                    self.Board.move(selected, destination)
                    self.Board.unshow_avaliable_moves(available)
                    break
                self.start(False)
            else:
                while True:
                    if self.Board.is_checked(self.player2):
                        print(f"Watch out {self.player2}! You're checked!")
                    selected = self.Board.retrieve_move(cf.Blue(f'{self.player2}, Please select a game piece: '), p = 's', retriver = self.player1)
                    available = self.Board.avaliable_moves(selected)
                    self.Board.show_avaliable_moves(available)
                    self.Board.print_board()
                    destination = self.Board.retrieve_move(cf.Blue(f'{self.player2}, Please select a destination: '), p = 'd', retriver = self.player1, position = selected)
                    if destination is None:
                        continue
                    self.Board.move(selected, destination)
                    self.Board.unshow_avaliable_moves(available)
                    break
                self.start(True)
        else:
            print(f"Congratulation! {over[1].name} won!!")


def player_names(phrase):
    while True:
            name = input(phrase).strip()
            if name.lower() in ['ai', 'bot']:
                continue
            if len(name) < 2:
                print(cf.Red("Try again! Name have to be at least 2 character long."))
                continue
            elif not name.isalpha():
                print(cf.Red("Try again! Name can only contain alphabets."))
            else:
                return name[0].upper() + name[1:].lower()
            
def generate():
    return random.choice(["A", "B", "C", "D", "E", "F", "G", "H"]) + random.choice(['1', '2', '3', '4', '5', '6', '7', '8'])

if __name__ == '__main__':
    # Event = Match(player_names('Enter name: '), player_names('Enter name: '))
    Event = Match('John', 'Alex')
    Game = Event.start()