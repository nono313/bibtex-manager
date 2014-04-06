# Bibtex manager (C)

####Authors
Maxime Bourgeois (maxime.bourgeois@utbm.fr)<br>
Nathan Olff (nathan.olff@utbm.fr)

####Objective
The goal of this project is to parse a bibtex file into a doubly linked list, sort it and display it.

####Implementation
We created generic doubly linked list by using void pointers (written void*) which can point on any type of data.<br>
The parsing of the file was made line by line, with the help of regular expressions.<br>
In order to sort the linked list, we implemented the quicksort algorithm. As our linked list were generic, we had to implement the quicksort in a generic way by using comparative functions sent into the quicksort.<br>
We choose to export the bibtex library into an HTML file rather than a simple text file.

