//Name: Chloe Mitchell
//File Name: prog1.cpp
//Date: 07 September, 2023
//Program Description: Uses recursive backtracking to find a path through a maze produced in a text file
#include <iostream>
#include <fstream>
using namespace std;

const int ROW = 12, COL = 12;

void loadMaze(char maze[][COL], char* argv);
void startEnd(int &, int &, int &, int &, char maze[][COL]);
void printMaze(char maze[][COL]);
bool findPath(int, int, int, int, char maze[][COL]);


int main(int argc, char* argv[]) {
    char maze[ROW][COL];
    int startRow, startCol;
    int endRow, endCol;

    if(argc == 1) {
        cout << "No file has been entered." << endl;
        return 0;
    }

    loadMaze(maze, argv[1]);
    printMaze(maze);
    startEnd(startRow, startCol, endRow, endCol, maze);
    if (!findPath(startRow, startCol, endRow, endCol, maze))
        cout << "There is no path!" << endl;
    else {
        maze[startRow][startCol] = 'S';
        maze[endRow][endCol] = 'E';
        printMaze(maze);
    }


    return 0;
} //end of main

//recursive function for finding a valid path through the maze and returns true/false on whether there is a path
bool findPath( int curRow, int curCol, int endRow, int endCol, char maze[][COL]) {
    if (curRow < 0 || curRow >= ROW || curCol < 0 || curCol >= COL)
        return false;
    if (curRow == endRow && curCol == endCol)
        return true;
    if (maze[curRow][curCol] == '*')
        return false;
    if (maze[curRow][curCol] == 'o')
        return false;
    if (maze[curRow][curCol] == ' ')
        maze[curRow][curCol] = 'o';

    //checking for a path north
    if (findPath(curRow - 1, curCol, endRow, endCol, maze))
        return true;
    //checking for a path east
    if (findPath(curRow, curCol + 1, endRow, endCol, maze))
        return true;
    //checking for a path south
    if (findPath(curRow + 1, curCol, endRow, endCol, maze))
        return true;
    //checking for a path west
    if (findPath(curRow, curCol - 1, endRow, endCol, maze))
        return true;
    if (maze[curRow][curCol] == 'o') {
    maze[curRow][curCol] = ' ';
    cout << endl << curRow << " " << curCol << endl;
}
    return false;
}

//this function gets the start and end positions from the user
void startEnd(int &start1, int &start2, int &end1, int &end2, char maze[][COL]){
    cout << "Enter two numbers between 1-12 inclusive for the start position: ";
    cin >> start1 >> start2;
    start1 -= 1;
    start2 -= 1;
    cout << "Enter a # between 1-12 inclusive for the end position: ";
    cin >> end1 >> end2;
    end1 -= 1;
    end2 -=1;
}

//this functions reads the maze from a text file into a 2D array
void loadMaze(char maze[][COL], char* argv){
    ifstream inFile(argv);
    if(!inFile) {
        cout << "Not in the file!";
        exit(0);
    }

    while(!(inFile.eof())) {
        for (int r = 0; r < ROW; r++) {
            for (int c = 0; c < COL; c++) {
                maze[r][c] = inFile.get();
            }
            inFile.ignore(1, '\n');
        }
    }
    inFile.close();
}

//this functions displays the current maze to the user
void printMaze(char maze[][COL]){
    for(int r = 0; r < ROW; r++){
        for (int c = 0; c < COL; c++){
            cout << maze[r][c];
        }
        cout << endl;
    }
}