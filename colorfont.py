
COLOR_RED = '\033[91m'
COLOR_GREEN = '\033[92m'
COLOR_YELLOW = '\033[93m'
COLOR_BLUE = '\033[94m'
COLOR_PURPLE = '\033[95m'
COLOR_CYAN = '\033[96m'
COLOR_RESET = '\033[0m'

def Red(phrase):
    return COLOR_RED + phrase + COLOR_RESET

def Green(phrase):
    return COLOR_GREEN + phrase + COLOR_RESET

def Yellow(phrase):
    return COLOR_YELLOW + phrase + COLOR_RESET

def Blue(phrase):
    return COLOR_BLUE + phrase + COLOR_RESET

def Purple(phrase):
    return COLOR_PURPLE + phrase + COLOR_RESET

def Cyan(phrase):
    return COLOR_CYAN + phrase + COLOR_RESET
