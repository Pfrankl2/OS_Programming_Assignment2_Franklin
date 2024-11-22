# Overview
The goal of Assignment 2 was to simulate the Banker's Algorithm used in process resource allocation to determine if a given set of processes has a Safe Sequence of allocation, and then if this was true to write out the order of that sequence.

There are two files used in this program: "bankers.cpp" and "data.txt". The .cpp file holds all relevant code that reads in the data of each process from a source file (data.txt), calculates the Need Table of each process (Where Need[i][j] = Max[i][j] - Allocation[i][j]) and then uses all of these tables to determine if a Safe Sequence exists between the given processes. The data given for this assignment needed to be transferred to and read from a .txt file, and so the file "data.txt" holds all information for the number of processes/resources in the system (The first two numbers in the file), the Allocation Tables of each process (The next five lines of numbers) and then the maximum number of resources need by each process (The finaly five lines of numbers). "bankers.cpp" is set up to understand the format of the data file, and so it parses the file and extracts the values to add to each appropriate table.

An example output for this program can be seen in the text file 'bankerExample.txt' in this repository!

# Running The Code
To run the code, copy "bankers.cpp" into any appropriate Linux/Unix directory and add "data.txt" as a text file in the same directory. From there, you can compile bankers.cpp with the following command:

        g++ -o bankers bankers.cpp

From here, the created object file can be run with the following command right afterwards:

        ./bankers
