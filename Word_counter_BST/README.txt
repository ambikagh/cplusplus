BUILD.sh ->  compiles the program
RUN.sh -> 1. Processes a text input file("textfile.txt") and outputs "wordperline.txt"
             that contains 1 word per line using a python program. Pythong program 
             "wordperline.py" is also provided
          2. Executes the program by taking "wordperline.txt" as an input file.
             Output written to standard output file is collected in "result.txt"
bst_runtime_plot.png -> Contains the plot of run time complexity behaviour for 
             Binary Search Tree. This plot contains 2 curves,
             a. Unsorted: Unsorted curve represents the time taken by the 
             BST for a random data, on an average random data is likely to 
             result in a balanced tree with run time complexity of O(nlogn)
             b. Sorted: Sorted curve represent the time takn by the BST for a
             completely sorted input. Run time complexitry of an input size 
             of 'n' for BST is O(n2). 
	     This plot makes a compulsive argument and explains the
             motivation behind innumerable logarithms out there.
unsorted.png -> since it was difficult to view the behaviour of BST run time 
             in 'bst_runtime_plot.eps' for unsorted input, I have plotted the
             behaviour in unsorted.eps. From the plot it is evident that even for 
             larger input size run time fairly remains flat.
plot.txt ->  List of "input size" and resulting "Real time" from "time" command
             for random unsorted data
plot1.txt -> For sorted data
textfile.txt -> Input text file
              
