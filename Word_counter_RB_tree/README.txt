BUILD.sh ->  compiles the program
RUN.sh -> 1. Takes an input text file and outputs one word per line
	     input file: 'textfile.txt'
             output file: 'wordperline.txt'
          2. Executes the program 
             input file: 'wordperline.txt' generated in first step
             Output file: "result.txt"
plot.txt ->  Run time analysis of Red Black tree for unsorted/random input of size 10000 to  	100000
plot1.txt -> Run time analysis of Red Black tree for sorted input size 10000 to 100000

Image files:
Folder contains plot of 'Run time analysis of Red Black Tree'
1. random_RBTree.png : Run time analysis of random inputs
2. sorted_RBTree.png : Run time analysis of sorted inputs
3. Runtime_analysis_Red_Black_Tree.png : Run time analysis of both sorted and random inputs

Debugging option:
-----------------
Functions 'verify()' and 'dump()' are implemented as debug features.
To enable debugging uncomment the line (disabled by default)
#define DEBUG_RBTREE
in 'RB_Tree.h' file.

Verify(): Function checks whether all invariants of Red Black Tree are satisfied.
dump(): Dump function outputs the final Red Black tree in indented fashion for easy readability.
        Children are displayed as indented text to its parent as shown below.
0xc3dd70 subscribe --> parent
+--------0xc2e8e0 subordination -->left child
+--------0xbd7d50 subsequent --> right child

              
              


