/* Alexis Veliz
 *  Coded on the week of January 27, 2018
 *  Sudoku Solver inspired by https://projecteuler.net/problem=96
 */
#include <iostream>
#include <vector>
#include <set>
#include <cctype>

#ifdef __WIN32__
#include <windows.h>
#define sleep(n) Sleep(1000 * n)  //Windows Sleep in ms

#define clear() system("cls")
#endif

#ifdef __APPLE__
#include <unistd.h>

#define clear() system("clear")
#endif

using namespace std;

int chartoint(const char c);
void printBoard(const std::vector< std::vector<int> > Board);
bool wellPlaced(std::vector< std::vector<int> > Board, int i, int j);
bool assignable(std::vector< std::vector<int> > Board, int x,const int i,const int j);
bool solve(std::vector< std::vector<int> >& Board);
bool filled(const std::vector< std::vector<int> > Board);
bool findEmptyCell(const std::vector< std::vector<int> > Board, int& row, int& col);
void game(std::vector< std::vector<int> >& Board);

int main(int argc, char** argv) {
    std::vector< std::vector<int> > Board;
    char buffer[100];
    char tmp[9];
    int i = 0;


    //file opening
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        std::cout << "file not opened" << std::endl;  // error handling
    } else std::cout << "opened" << std::endl;


    while (fgets(buffer, 100, fp)) {
        if (sscanf(buffer, "%s", &tmp)) {                            //reads a string into tmp
            //std::cout << tmp << std::endl;
            if (!isalpha(tmp[0])) {                                  //First string will have a G, we dont want that
                std::vector<int> xBoard;
                for (int x = 0; x < 9; x++) {
                    xBoard.push_back(chartoint(tmp[x]));            //convert chars into ints & place in board

                }
                Board.push_back(xBoard);
            }
            i++;
        }
        if (i > 9)
            break;
    }



    printBoard(Board);
    char input;
    while(1) {
        std::cout << "Enter 's' to solve automatically or enter 'p' to play" << std::endl;
        std::cin>>input;
        if (input == 'p' || input == 's')
            break;
    }

    if(input == 'p') {
       game(Board);
    }

    if(solve(Board))
        printBoard(Board);

}

void game(std::vector< std::vector<int> >& Board){
    int x, y, num;
    bool solve = false;

    std::cout << "Enter 999  to quit & solve automatically " << std::endl;
    while(solve != true) {
        while (!filled(Board)) {
            printBoard(Board);
            std::cin >> x;
            if(x == 999){
                solve = true;
                break;
            }

            std::cin >> y;
            if(y == 999){
                solve = true;
                break;
            }

            std::cin >> num;
            if(num == 999){
                solve = true;
                break;
            }



            Board[y][x] = num;
            if (!wellPlaced(Board, y, x))
                Board[y][x] = 0;

            clear();
        }
    }
}
int chartoint(const char c){
    int tmp = c;
    return tmp - 48;
}

void printBoard(std::vector< std::vector<int> > Board){
    std::cout<<"_____________________________________"<<std::endl;
    for (int a = 0; a < 9; a++) {

        for (int b = 0; b < 9; b++) {
            if(Board[a][b] == 0)
                std::cout<<"|   ";

            if(Board[a][b] != 0)
                std::cout<<"| "<< Board[a][b] << " ";
        }
        std::cout <<"|" <<std::endl;

        std::cout<<"|___|___|___|___|___|___|___|___|___|"<<std::endl;    //separating line
    }

}

bool wellPlaced(std::vector< std::vector<int> > Board, int i, int j){
    //scan column
    for(int n = 0; n < 9; n++){
        if(Board[i][j] == Board[i][n]) {
            if (j != n) {
                return false;
            }
        }
    }

    //scan row
    for(int n = 0; n < 9; n++){
        if(Board[i][j] == Board[n][j]) {
            if(i != n) {
                return false;
            }
        }
    }

    //places the iterator at the top left of each box
    int c = j - (j % 3);
    int r = i - (i % 3);

    //scan its box
    for(int y = r; y < r + 2; y++) {
        for(int x = c; x < c + 2; x++) {
            if((Board[y][x] ==  Board[i][j]) && (i != r &&  j != c) )           //if duplicate is found
                return false;                                                   //and its not the same as the cell we're testing
        }
    }

    std::cout<< "Well Placed"<<std::endl;
    return true;
}

bool filled(const std::vector< std::vector<int> > Board){
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            if(Board[row][col] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool findEmptyCell(const std::vector< std::vector<int> > Board, int& row, int& col){
    for(int r = 0; r < 9; r++){
        for(int c = 0; c < 9; c++){
            if(Board[r][c] == 0) {
                row = r;
                col = c;
                return true;
            }
        }
    }
    return false;
}


bool assignable(std::vector< std::vector<int> > Board, int x,const int i,const  int j){
    //scan column
    for(int a = 0; a < 9; ++a){
        if(j != a && x == Board[i][a])
            return false;
    }

    //scan row
    for(int n = 0; n < 9; ++n){
        if(i != n && x == Board[n][j])
            return false;
    }

    //places the iterator at the top left of each box
    int c = j - (j % 3);
    int r = i - (i % 3);

    for(int i = 3 * (r / 3); i < 3 * (r / 3) + 3; ++i) {
        for(int j = 3 * (c / 3); j < 3 * (c / 3) + 3; ++j) {
            if((i != r || j != c) && x == Board[i][j])
                return false;
        }
    }
    return true;
}


bool solve(std::vector< std::vector<int> >& Board){
    if(filled(Board))
        return true;

    int row, col;
    findEmptyCell(Board, row, col);

    for(int num  = 1; num <= 9; num++){
        if(assignable(Board, num, row, col)){

            Board[row][col] = num;

            if(solve(Board))
                return true;

            Board[row][col] = 0;
        }

    }
    return false;
}

/* Reduce the problem
 * - scan the board for obvious soltuions
 * = keep track of which cells have the least amount of candidates
 *
 * Backtracking method
 * - start from 1 -> 9
 * - insert a candidate as a possible solutiion into a cell
 * - move around the board
 * - if we run into solutions later, "Backtrack"
 */