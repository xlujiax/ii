# http://stackoverflow.com/questions/4499073/printing-without-newline-print-a-prints-a-space-how-to-remove
from __future__ import print_function
import os,random

def get_phrase():
    # http://www.regexprn.com/2008/11/read-random-line-in-large-file-in.html
    filename="frazy"
    file = open(filename,'r')

    file_size = os.stat(filename)[6]

    # Seek to a place in the file which is a random distance away
    # Mod by file size so that it wraps around to the beginning
    file.seek((file.tell()+random.randint(0,file_size-1))%file_size)

    # dont use the first readline since it may fall in the middle of a line
    file.readline()
    # this will return the next (complete) line from the file
    line = file.readline()

    # here is your random line in the file
    return line

def draw_hangman(wrong):
    if wrong == 0:
        print("             ")
        print("             ")
        print("             ")
        print("             ")
        print("             ")
        print("             ")
        print("             ")
    elif wrong == 1:
        print("             ")
        print("|            ")
        print("|            ")
        print("|            ")
        print("|            ")
        print("|            ")
        print("|            ")
    elif wrong == 2:
        print(" _________   ")
        print("|            ")
        print("|            ")
        print("|            ")
        print("|            ")
        print("|            ")
        print("|            ")
    elif wrong == 3:
        print(" _________   ")
        print("|         |  ")
        print("|            ")
        print("|            ")
        print("|            ")
        print("|            ")
        print("|            ")
    elif wrong == 4:
        print(" _________   ")
        print("|         |  ")
        print("|         0  ")
        print("|            ")
        print("|            ")
        print("|            ")
        print("|            ")
    elif wrong == 5:
        print(" _________   ")
        print("|         |  ")
        print("|         0  ")
        print("|         |  ")
        print("|            ")
        print("|            ")
        print("|            ")
    elif wrong == 6:
        print(" _________   ")
        print("|         |  ")
        print("|         0  ")
        print("|        /|  ")
        print("|            ")
        print("|            ")
        print("|            ")
    elif wrong == 7:
        print(" _________   ")
        print("|         |  ")
        print("|         0  ")
        print("|        /|\ ")
        print("|            ")
        print("|            ")
        print("|            ")
    elif wrong == 8:
        print(" _________   ")
        print("|         |  ")
        print("|         0  ")
        print("|        /|\ ")
        print("|        /   ")
        print("|            ")
        print("|            ")
    elif wrong == 9:
        print(" _________   ")
        print("|         |  ")
        print("|         0  ")
        print("|        /|\ ")
        print("|        / \ ")
        print("|   GAME     ")
        print("|   OVER!    ")
        
phrase = get_phrase()
print(phrase)

def print_phrase(phrase, history):
    for c in phrase:
        if c in history:
            print(c, end='')
        else:
            print('_', end='')
    print('')

history = set([])
letters = set(phrase)
wrong = 0

while True:
    from_user = raw_input()
    if len(from_user) == 1:
        guess = from_user[0]
        history.add(guess)
        print_phrase(phrase, history)
        if not guess in letters:
            wrong = wrong + 1
        if letters - history == set([]):
            print("You won!")
            exit(0)
    else:
        phrase_guess = from_user
        if not phrase == phrase_guess:
            wrong = wrong + 1
        else:
            print("You won!")
            exit(0)

    draw_hangman(wrong)
    if wrong == 9:
        exit(1)
            
