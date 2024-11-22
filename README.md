# Overview
The goal of Assignment 2 was to simulate the Banker's Algorithm used in process resource allocation to determine if a given set of processes had a Safe Sequence of allocation, and then if this was true to write out the order of that sequence.

There are two files used in this program: "bankers.cpp" and "data.txt". The .cpp file holds all relevant code that reads in the data of each process from a source file, calculates the Need Table (Where Need[i][j] = Max[i][j] - Allocation[i][j]) and then uses all of these tables to determine if a Safe Sequence exists with the given processes. The data given for this assignment needed to be transferred to and read from a .txt file, and so the file "data.txt" holds all information for the number of processes/resources in the system, the Allocation Tables of each process and then the maximum number of resources need by each process.

An example output for this program can be seen in the text file 'bankerExample.txt' in this repository!

# Running The Code
To run the code, simply copy "bankers.cpp" into any appropriate Linux/Unix environment to run the C++ code and add data.txt as a resource file of this code. From there, the program will run on the terminal and show the given output based on the data file!
