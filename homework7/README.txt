HOMEWORK 7: SUPER SMASH BROS. FRAMES


NAME:  < Anannya Punia >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

<stack overflow and Cplusplus>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 hours >



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity for both running
time AND space along with a short justification for each of the queries below.
For the commands, do not count the space occupied by the database in the space
complexity analysis.

f: The total number of fighters
m: The number of different moves
t: The highest number of moves that have the same starting frame for a particular move

reading the database/populating your initial data structure:

TIME COMPLEXITY
-q (specific move): O(log (f)) - because it's using the find command

-q (all): O(log (f)) - it's looking for the find command as well

-f: o(log(m) - because it uses the command find on the moves to find the frames

-s: o(log(m) - because it uses the command find on the moves to find the frames(it's the same function with a tiny difference)

-d: o(log(m) - it uses the find command, to find the frames

SPACE COMPLEXITY
-q (specific move): o(1) because it only has one move

-q (all): o(m) depends on the amount of moves it has to store

-f: o(t) it depends on how many moves you are putting in set that are sorted

-s: o(t) it depends on how many moves you are putting in set that are sorted

-d: o(m) depends on the moves

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
Please be nice. i need a good grade on this






