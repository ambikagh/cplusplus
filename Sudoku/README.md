Write a program that creates a Puzzle object and reads a Sudoku puzzle from cin. It should then display the original puzzle. 
Your program should then apply a backtracking algorithm to solve the puzzle. A simple outline of such an algorithm might be: 

Solve(row, column)  
   if (row, column) past end of puzzle, return success  
   Move to next square without a value  
   foreach value from 1 through 9  
      if value is legal, set square to it  
         if Solve(next row and column) succeeds  
            return success  
         erase square value  
   endfor  
   return failure  
end Solve 

Your program should then display the solved puzzle or, if it couldn’t be solved, output a message to indicate so. 
