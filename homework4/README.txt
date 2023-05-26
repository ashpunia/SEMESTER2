HOMEWORK 4: TOOL RENTAL LISTS


NAME:  <Anannya Punia>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

<Mike Cautella, Kevin Shreenauth>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  <30 hours >



ORDER NOTATION:
Use these variables to analyze each phase of computation.  Briefly
justify your answer for each part.


i = # of different inventory items
c = # of different customers
p = # of pending customers
q = max quantity of a particular tool owned by the store
r = max # of tools rented or requested by a customer at one time
p = total # of pending tool rentals
e = # of rental or return events


Load inventory file: 0(i) depending on how many objects we would have to make,
			 the loading inventory file

Rental event: o(i*c) because i'm looping through all the object in both lists

Return event - no pending customer(s):  o(i*c) i'm looping through both lists, and 
pushing back which should be o(1)

Return event - with pending customer(s):o(i*c) i'm looping through both lists, and 
pushing back which should be o(1) and taking it awau form the pending list

Entire program:
0(i*C+pe)
there are a lot of loops but they're of the same lists. 


MISC. COMMENTS TO GRADER:
(optional, please be concise!)

pending list would be another list in customer class as a a list of inventory objects 
that would, so each customer could have its own pending and rent lists. 
