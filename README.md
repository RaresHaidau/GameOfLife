# FEATURES
Task1: -implements the basic rules of John Conway's Game of Life;
Task2: -uses a Stack of Lists to contain the coordonates of the cells that changed their state from the past generation;
       -each element of the Stack represent a generation;
       -the stack is written backwards in the output file;
Task3: -implements a new set of rules for the game;
       -uses a binary tree to apply the rules(left is the normal game and right is the new one);
       -each node contains only the coordonates of the cells that changed their state from the past generation;
Task4: -for each node from Task3 it finds the longest Hamiltonian path;
       -the code puts the longest path in the output file
       !NOTE!:**Task4 doesn't work**

# HOW TO USE
The code must be given an input and output file when run, both have to be .txt files.
Input file: MUST follow this exact input
T //number of the task;
N M //dimensions of the matrix;
K //number of generations;
The matrix containing the initial state of the cells;

# FUNCTIONS
reguli_GoL - apply the basic rules of Game of Life;
aflare_coordonate - puts the modified cells in the stack;
reguli_GoL_left/reguli_GoL_right - containd the rules for each direction;
reguli_noi_GoL - aply the set of rules for each direction;
matrice_adiacenta - does the adjacency matrix;
DFS - calculates the longest path;
aplicare_hamilton - does the vector for longest hamiltonian path;
aplicare_hamilton_node - applyes hamilton for only one node;

# NEEDS FIXING
Task4: Determine, for each node of the tree obtained in Task 3 up to a given generation K, the longest Hamiltonian path.
##Problem
Only prints -1 if hamilton and aplicare_hamilton are used;
Prints nothing if hamilton_recursiv and aplicare_hamilton_node are used;

# BONUS
Reverse the actions from Task2;
