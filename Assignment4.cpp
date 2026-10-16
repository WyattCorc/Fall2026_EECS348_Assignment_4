/*
Program Name: Recursive Sodoku solver
Disc: This program takes a text file input and uses a recursive brute force algorithm to solve.
Inputs: .txt files containing Sodoku puzzles
Outputs: Solved Puzzles.
Collaborators: Google Gemini
Author: Wyatt Corcoran
Created 10/15/2026
*/

#include <iostream>//Manages I/O functionality
#include <fstream>//Reading .txt files
#include <vector>//Implements lists
#include <string>//Allows strings to be used in C++
#include <set>//Sets, similar to lists, can only contain unique elems
//NOTICE - ALL ORIGINAL CODE BY GEMINI, revisions all made by me are clairified
/*
Class Grid has 3 functions, Instantiate the grid using Nested vectors making a 9x9 element "grid"
Iterates and adds '_' to each section of the board, Then it looks for legal nums in each index,
Finally uses backtracking till a solution is found.
*/
class Grid {//Defines class Grid
private:
    char board[9][9]; //Creates and instance of the nested list max 9 rows, 9 cols.

    //Written by Wyatt to merge a defunct "Solver" class with the grid class

    bool findEmptyCell(int& r, int& c) const{//Iterates till it finds the first empty space
        for (r = 0; r < 9; ++r) {//iterates 0,8
            for (c = 0; c < 9; ++c) {//iterates 0,8
                if(board[r][c] == '_')//Returns true if an empty space exists
                return true;//Found an empty cell returns true
            }
        }
        return false;//returns false if the whole grid is full
    }
    //Original by Gemini rewritten by Wyatt
    //Function that uses sets to determine if a block of 9 is legal
     std::vector<char> SectionFilter(int r, int c) const { //output is a vector with chars 
        std::set<char> taken;//Creates a set to find what nums have already been taken in a given:
        for (int i = 0; i < 9; ++i) {//iterates 0-8
            taken.insert(board[r][i]);//row
            taken.insert(board[i][c]);//col
        }
        //Original by Gemini rewritten by Wyatt
        //This block determines if the 3x3 boxes are valid
        int startRow = (r / 3) * 3;//Finds which of the 9, 3x3 boxes you are in
        int startCol = (c / 3) * 3;
        for (int rowOffset = 0; rowOffset < 3; ++rowOffset) {//Iterates through the row of the box
            for (int colOffset = 0; colOffset < 3; ++colOffset) {//Iterates through the col of that box
                taken.insert(board[startRow + rowOffset][startCol + colOffset]);//Appends found values to the filter list
            }
        }       //Original by Gemini rewritten by Wyatt
                //Generates a list containing all of the Unused values
                std::vector<char> possible_vals;//Outputs a vector
        for (char digit = '1'; digit <= '9'; ++digit) {//Iterates through 1-9
            if (taken.find(digit) == taken.end()) {//Compates it to the set
                possible_vals.push_back(digit);//Add the value if it isnt in the set
            }
        }
        return possible_vals;//returns the list of available values
     }
     //Original by Gemini rewritten by Wyatt
     //Backtracking approach implementation
      void solveRecursive(int& solutionCount) { //Solution count is passed to the final print for each success
        int r, c;
        //Base case for the recursion is a legal full grid
        if (!findEmptyCell(r, c)) {//If there are no empty cells
            solutionCount++;//Add a solution to the count
            std::cout << "Solution " << solutionCount << ":\n";//Print which solution number this is
            gridprint(); //calls the gridprint
            return;//exit
        }
        std::vector<char> possible_vals = SectionFilter(r, c);//Find legal values
        for (char val : possible_vals) {//attempt a plugin for each legal value
            board[r][c] = val;//Plugs in the value at this point 
            solveRecursive(solutionCount);//Recur back through maintaing the number of successful solutions
            board[r][c] = '_';//This does the backtrack replacing the index with nothing if the calls return to here
        }
    }
public:
    //Initalize an empty grid
    Grid() {//Make a grid
        for (int r = 0; r < 9; ++r) {//Iterate row
            for (int c = 0; c < 9; ++c) {//Iterate col
                board[r][c] = '_';//Replace all 81 indicies with '_'
            }
        }
    }
    //Rewritten by Wyatt
     bool loadFromFile(const std::string& filename) {//Uses the fstream lib to read the files char by char
        std::ifstream file(filename);//Grabs filename
        if (!file.is_open()) return false;//No file exists returns false, causes error to be printed from main
        for (int r = 0; r < 9; ++r) {//Iterates row
            for (int c = 0; c < 9; ++c) {//Iterates col
                if (!(file >> board[r][c])) return false;//Item by item replaces with equivelant from file if it cant, returns error
            }
        }
        return true;//returns true when the read succeeds
    }

    //section rewritten by Wyatt to fit to the output standards in solution1.txt
    void solve(const std::string& filename) {//Takes a file
        std::cout << "Puzzle file: " << filename << "\n";//Prints the original for comparason sake
        gridprint();//prints the original

        int solutionCount = 0;//initalizes solutions at 0
        solveRecursive(solutionCount);//Begins recursion for the first solution

        if (solutionCount == 0) {//No solution found, returns no solution
            std::cout << "No solution found.\n\n";//Prints no solution found
        }
    }

    // Print function that displays output cleanly
    //section rewritten by Wyatt to fit to the output standards in solution1.txt
    void gridprint() const {//This iterates through row and col, printing off the result,
        for (int r = 0; r < 9; ++r) {//iterate by row
            for (int c = 0; c < 9; ++c) {//iterate by col
                std::cout << board[r][c] << ' ';//print at index
            }
            std::cout << '\n';//Break to represent rows properly
        }
        std::cout << '\n';//Break when the 9x9 print is done
    }
};
/*
Main Instantiates the 2 classes, the .txt files are hard coded as is but this could be easily changed
For each file presented, Grid class loads from the respective file and solves using backtracking recursion
Main was completely rewritten by me to work with the class changes
*/
//Main Fully rewritten by Wyatt
int main() {
    //Hard assigned the 5 puzzles
    std::string files[] = {"puzzle1.txt", "puzzle2.txt", "puzzle3.txt", "puzzle4.txt", "puzzle5.txt",};
    //Iterates through each file
    for (const std::string& filename : files) {
        Grid grid;//Makes a new grid
        if (grid.loadFromFile(filename)) { //Loads the starting values from the file
            grid.solve(filename);//Runs the recursive solve
        } else {//if FALSE is output during the loadFromFile funct you get this error printed
            std::cout << "Could not open or read file: " << filename << "\n\n";//error printed here
        }
    }
    
    return 0; //Finishes running successfully 
}