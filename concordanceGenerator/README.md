In this program you will build a software tool that is a fundamental part of the analysis of large documents: a concordance generator. In overview, your program will read a corpus, or body of text, and assemble a binary search tree (BST) of (key, value) pairs. Each word in the corpus (that is not a stop word) is used as a key; the words surrounding it (i.e., several words before and after) — its context — are its value. You will use this tree to collect the context information for each non-stop-word in the corpus; you will then output this information as a concordance in a specific format: KWIC. 

Concordances

A concordance is conceptually similar to an index, in which information is presented for each non-trivial word in a corpus, sorted alphabetically by those words. Generally, indices are generated only for words that correspond to important concepts in a text. On the other hand, concordances are generally created for all words in a text, possibly excluding words such as “a,” “an,” “the,” etc. We will call these words to be excluded stop words. You can find a (very) brief overview of concordances and their uses at this Northern Illinois University web site; a freeware tool for constructing concordances is AntConc. 



Key Words in Context (KWIC)

The most common way to format concordance information for human consumption is the Key Words in Context (KWIC) format, in which each usage of a word is aligned at the same column on each line. For our purposes, we will use five words of context before and after for KWIC output (unless the word is so close to the beginning or end of the corpus that there aren’t five words before or after it). 



Statement of Work

Write a program that reads a text corpus from a file and outputs its concordance in KWIC format to cout, excluding a specified set of stop words. The stop words should be read from a text file called stopwords.txt, in the same directory as your program, with one stop word per line. (Note that file name capitalization must be matched exactly.) If no stop word file exists, then your program should continue without excluding any words from the concordance. Your program should take the file name for the corpus file as its sole command line argument. 

Your program must use a BST to collect the concordance information. You may use or modify the Carrano code, but you may find it easier to write your own from scratch. Nodes in the tree should be indexed by each non-stop-word in the corpus; each tree node should contain a linked list of context information (five words before and after each key word). In other words, each item in a key word’s linked list should be the context information for one of its appearances in the corpus — each list item should have the five words before and the five words after. You may use or modify the Carrano list code, but you may find it easier to write your own from scratch. You are free to include whatever additional information you deem necessary in your classes, as long as you have the BST and linked lists of context information. 

The concordance information should be output first alphabetized by keyword; the output for each keyword should be ordered by occurrence in the input text. The first of these requirements is easily met by the BST, of course. The second implies something regarding how the linked list of context information is assembled (what does it imply?). 



What’s in a word?

For simplicity’s sake, you may use the following definitions to constrain how you identify words in the input stream. You are free to go beyond the following, but your program should at least implement these: 
•Words are bounded by white space (or, for the first word, the start of the input and white space; for the last word, white space and eof() being true). 
•If what you get from the above contains only punctuation characters, you should not consider it a word. 
•Your program should “clean” all trailing punctuation at the end of a “word” (periods, commas, quotes, etc).
