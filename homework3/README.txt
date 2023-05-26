HOMEWORK 3: MATRIX CLASS


NAME:  <Anannya Punia>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

<Masha Karach, Mike Cautelli>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  <30>


ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get: O(1) - Since there are no loops, the big O notation is o{1)

set: O(1) -Since there are no loops, the big O notation is o{1)

num_rows: O(1) -Since there are no loops, the big O notation is o{1)

get_column: O(m) - Since there is one loop, m = row hence the big o notation is o(m). 


operator<< : O(m*n) - Since there are two loops on a row and col, the big o notation is m times n

quarter : O(m*n) - Since there are two loops on a row and col, the big o notation is m times n

operator== : O(m*n) - Since there are two loops on a row and col, the big o notation is m times n

operator!= : O(m*n) - Since there are two loops on a row and col, the big o notation is m times n

swap_rows: O(1) - since there are no loops, the big o notation is O(1)

rref (provided in matrix_main.cpp) = 0(n^3) a large for loop with a while loop and a for loop all nested
it also has the same variables looping through it 



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I used valgrind to check for memeory leaks. I also used it to figure where to the memory 
leaks are and how to fix them. I used gdb a little bit to figure out where my asserts are failing
There were also times where I just used printing to debug my code. 



EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


