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

print get_phrase()
