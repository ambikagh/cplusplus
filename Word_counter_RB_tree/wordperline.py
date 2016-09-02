#! /usr/bin/python3.4

#Read a text file, output one word per line in a new text file
#For example program reads the text "This is a test file"
#Outputs the words into a new file in the following format
#This
#is
#a
#test
#file
# Open a file to read

#import tkinter
import sys

def wordperline(infile):
    infilep = open(infile,'r')
    # Create a file to write
    outfilep = open("wordperline.txt",'w')
    # Read input file line by line
    line = infilep.readline()
    while(line != ''):
     # Split each line into words
     splitline = line.split()
     for word in splitline:
       word = word.strip(".,!\';:[]-()\"%$#@? ")
       # Write each word in new line
       if (word.isalpha()):
         outfilep.write(word)
         outfilep.write('\n')
        # Read next line
     line = infilep.readline()
    # Close input and output files
    infilep.close()
    outfilep.close()

if __name__=='__main__':
    infile = "textfile.txt"
    if len(sys.argv) > 1:
        infile = sys.argv[1]
    wordperline(infile)



