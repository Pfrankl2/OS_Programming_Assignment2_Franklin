// Implementation of Banker's Algorithm.
// Parker Franklin

// Large portions of the code in "bankers.cpp" were created based on my own
// personal research of the Banker's Algorithm from both online and in-class
// sources. Some of the notable resources I used to help put this file together
//  include:
//     - "Banker’s Algorithm in Operating System" by GeeksForGeeks
//     - "Banker's algorithm for deadlock avoidance | An example." by Scholarly Things (YouTube)
//     - "<sstream>" by cplusplus.com
//     - Chapter 7 Slides from Operating Systems
//     - Any additional Article/Forum/Code references found in class or online
//
// Every resource that helped in creating this file was used purely for
// my own reference while working on Assignment 2!

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//
// Function Declarations
//

// Calculates the Need Vector of each process.
void calculateNeedTable(vector<vector<int>>& needTable, vector<vector<int>>& maxTable, vector<vector<int>>& allocationTable, int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            needTable[i][j] = maxTable[i][j] - allocationTable[i][j];
        }
    }
}

// Finds if a Safe Sequence is possible for the given processes and prints it (If possible).
bool isSafeSequence(vector<vector<int>>& allocationTable, vector<vector<int>>& needTable, vector<int>& availableTable, int processes, int resources) {
    //
    // Temporary Vector Declaration
    //
    vector<bool> finished(processes, false); // Bool vector that holds if each process has finished executing or not.
    vector<int> safeSequence(processes); // Vector to hold the safe sequence of processes in the order they can execute (If possible) at the end.
    vector<int> currentResources = availableTable; // Holds the currently avialble resources at any time during allocation.

    // Main 'while' loop that determines the order in which the Banker's Algorithm can be run.
    int count = 0;
    while (count < processes) { // While every process has not yet been checked:
        bool found = false; // Sets 'found' to false for each new iteration of a process until a safe sequence can be calculated.

        // 'for' loop that runs each processes to check for a possible allocation.
        for (int i = 0; i < processes; i++) { // While all processes have not been checked (Where i = The current process):
            if (!finished[i]) {
                bool canAllocate = true; // Initially assumes a process can be allocated safely before checking.

                // Checks the amount of NEEDED resources for the current process and compares them to the amount of AVAILABLE resources.
                for (int j = 0; j < resources; j++) {
                    if (needTable[i][j] > currentResources[j]) { // If any Need[i][j] is larger than the currently available resources:
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) { // If there are enough available resources to allocate to the current process:
                    for (int j = 0; j < resources; j++) {
                        currentResources[j] += allocationTable[i][j]; // Add the resources held by the process to the amount of available 
                        // resources to simulate the process using its allocated resources and
                        // then releasing them.
                    }
                    safeSequence[count] = i; // Sets this process as the next process in the safe sequence.
                    ++count;

                    finished[i] = true;
                    found = true;

                    i = -1; // Resets 'i' so that all processes are iterated through again.
                }
            }
        }
        if (!found) { // If an allocation could not be found for a process:
            cout << "The system is not in a Safe State." << endl;
            return false;
        }
    }

    // Prints Safe Sequence of processes.
    cout << "The system is in a Safe State." << endl;
    cout << "The Safe Sequence for the processes is: ";
    for (size_t i = 0; i < safeSequence.size(); i++) {
        cout << "P" << safeSequence[i];
        if (i < safeSequence.size() - 1) cout << " - ";
    }
    cout << endl;

    return true;
}

int main() {
   
    //
    // Declaring Process/Resource Variables
    //

    int processes, resources; // Number of Processes and Resources (The first numbers in the text file).

    // The vectors for the Allocation, Max and Available tables of each process.
    vector<vector<int>> allocationTable;
    vector<vector<int>> maxTable;
    vector<int> availableTable;

    //
    // Reading the Input File
    //

    // Opens and attempts to read the input file.
    ifstream input("data.txt");
    if (!input) {
        cerr << "Unable to open file data.txt";
        return 1;
    }

    string line;

    // Reads in the number of Processes and Resources (The first two numbers in the file).
    getline(input, line);
    istringstream iss(line);
    iss >> processes >> resources;

    // Initializing vectors to the correct size for the number of Processes.
    allocationTable.resize(processes, vector<int>(resources));
    maxTable.resize(processes, vector<int>(resources));
    availableTable.resize(resources);

    // Reads data file & Takes input for the Allocation Table (The next five lines of numbers in the file).
    for (int i = 0; i < processes; i++) {
        getline(input, line);
        istringstream iss(line);
        for (int j = 0; j < resources; j++) {
            iss >> allocationTable[i][j];
        }
    }
    // Reads data file & Takes input for the Max Resources Table (The following five lines of numbers after the Allocation Table).
    for (int i = 0; i < processes; i++) {
        getline(input, line);
        istringstream iss(line);
        for (int j = 0; j < resources; j++) {
            iss >> maxTable[i][j];
        }
    }
    // Reads data file & Takes input for the Available Resources Table (The last line of numbers in the file).
    getline(input, line);
    istringstream issAvailable(line);
    for (int j = 0; j < resources; j++) {
        issAvailable >> availableTable[j];
    }

    input.close();

    //
    // Implementing the Banker's Algorithm
    //

    // Creating a Need Vector from the given processes and resources.
    vector<vector<int>> needTable(processes, vector<int>(resources));
    calculateNeedTable(needTable, maxTable, allocationTable, processes, resources);

    // Checks if an allocation pattern is possible to put the system in a Safe State.
    isSafeSequence(allocationTable, needTable, availableTable, processes, resources);
}
