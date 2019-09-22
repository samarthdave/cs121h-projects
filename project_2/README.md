---------------------
### Project 2 - Histogram
### due: Fri, 9/27/19, 8:00am
---------------------

Write a C++ program that reads a list of numbers in from a file,
prints out some statistics (count, range, mean, standard deviation),
and then prints a histogram of the values in ASCII.
The histogram should span between the min and max of the values,
and have 20 evenly spaced bins (for now).

The filename should be given on the command-line.
Assume it has one value on each line.

Do the calculation of the statistics yourself; don't use library functions.

Since the input file could have an arbitrary number of values, you
will have to store them in a dynamic data structure, like a vector.
An important part of this program is setting up an array or similar
data structure to count how many items are in each bin (try to do 
this in one pass).