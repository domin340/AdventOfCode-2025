from os import mkdir, makedirs
from shutil import rmtree
from os.path import exists

def to_bool(s: str) -> bool:
    yes_variants = ['y', 'yes', 'true', 'sure', 'ok', 'k', 'yeah', 'yh']
    norm = s.strip().lower();
    if norm in yes_variants:
        return True
    else:
        return False


def initialize_directories(ask: bool = True, silent: bool = False):
    yell = not silent and not ask

    if exists('bin') and ask:
        ans = to_bool(input('clear bin? '))
        if ans == True:
            rmtree('bin')
            print('bin tree removed!')

    if exists('bin/debug'):
        if yell:
            print('bin directory already exists!')
    else:
        makedirs('bin/debug') # create bin and debug for c compiler

    if exists('inputs') and ask:
        ans = to_bool(input('clear inputs? '))
        if ans == True:
            rmtree('inputs')

    if exists('inputs'):
        if yell:
            print('inputs directory already exists!')
    else:
        mkdir('inputs') # create inputs


if __name__ == '__main__':
    print('initializing aoc directories!')
    initialize_directories()
    print('aoc directories initialized')

