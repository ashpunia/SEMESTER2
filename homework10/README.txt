HOMEWORK 9: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  < Anannya Punia>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 25 hours >

w = the width of the input image
h = the height of the input image
p = the number of black pixels in the input image

——————————————————————————————————————————————————————————————————————————————————————————
NAIVE ALGORITHM:

Order Notation: O(w^2 * h^2)

Timing Experiment Data:
Test Case	                 Real	          User	          Sys
tiny_5x5.ppm	           0m0.012s  	0m0.001s		0m0.002s
small_10x10.ppm 	          0m0.011s	  0m0.001s		0m0.002s
squiggle_30x30.ppm	       0m0.025s	   0m0.016s		0m0.003s
lines_100x100.ppm	           0m1.472s	        0m1.451s		0m0.004s
data_structures_300x300.ppm    2m9.714s	        2m9.285s        0m0.142s
dots_1000x1000.ppm	       three hours had past, but the result still didn’t run out		
Discussion:
This naive algorithm is based on a four-level nested loop which tries to compute
 the distance between every pixels. It does a lot of work that we don’t need at all. 
So it is very ineffective and slow.
——————————————————————————————————————————————————————————————————————————————————————————
IMPROVED ALGORITHM:

Order Notation:O(w*h*p)

Timing Experiment Data:
Test Case                      	Real	          User         	  Sys
tiny_5x5.ppm            	0m0.013s	0m0.001s	0m0.003s
small_10x10.ppm        		0m0.014s	0m0.002s	0m0.002s
squiggle_30x30.ppm              0m0.017s	0m0.006s	0m0.003s
lines_100x100.ppm	       	0m0.081s	0m0.069s	0m0.003s
data_structures_300x300.ppm	0m15.929s	0m15.907s	0m0.008s
dots_1000x1000.ppm              half an hour had past, but the result still didn’t run out


Discussion:
This improved algorithm is just a little better than naive algorithm. 
Instead of four-level nested loop, we first use a nested loop to collect 
all the black pixels(O(w*h)), then use another nested loop to compute all
other white pixels closest distance to these black pixels(O(w*h*p)), so 
total is O(w*h)+O(w*h*p), which can be concluded as O(w*h*p). 
This method is faster in some degree, but is still not very good and 
very slow when the input is very big.DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:




FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:

MISC. COMMENTS TO GRADER:  
Optional, please be concise!






