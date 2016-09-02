#!/bin/bash

./a.out < wordperline.txt > result.txt
LC_COLLATE=C sort wordperline.txt > sort.txt 
diff --normal sort.txt result.txt

