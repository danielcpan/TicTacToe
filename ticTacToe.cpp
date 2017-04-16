#include <iostream>
#include <string>
#include <cstdio> // this for sscanf

using namespace std;

bool checkWinning(string board[][3], string player);
bool checkWinningRow(string board[][3], string player, int row);
bool checkWinningCol(string board[][3], string player, int col);
bool checkWinningDiagonal(string board[][3], string player);
void displayBoard(string board[][3]);
int play1Game();
int getUserMakeMove(string board[][3], string playerType, string prompt);
int getAnInt(double lowerBound, double upperBound, string askUser);
bool getYesOrNo(string prompt);

int main()
{
    bool again = true;
    do {
        play1Game();
        again = getYesOrNo("Do you want to play another game (y/n)? ");

    } while (again == true);
    return 0;
}
bool getYesOrNo(string prompt) {
    string answer;
    do {
        cout << prompt << endl;
        cin >> answer;
        if ((answer == "Y") ||(answer == "y")) return true;
        else if ((answer == "N") || (answer == "n")) return false;
        else
            cout << "Invalid Input";
    } while (true);

}

int play1Game() {
    string board[3][3] = {"*","*","*","*","*","*","*","*","*" };
    int moveCount=0;
    string user1 = "X";
    string user2 = "O";

    while (moveCount < 9) {
        // let user1 make a move
        getUserMakeMove(board, user1, "Player 1's turn to move.");
        // display board
        displayBoard(board);  
        // check winning if winning return 1
        if (checkWinning(board, user1)) {
            cout << "Player 1 wins! ";
            break;
        }
        // increment moveCount
        moveCount++;  
        // if it is last move we will quit
        if (moveCount == 9) {
            cout << "Tie! ";
            break;
        }
        // let user2 make a move
        getUserMakeMove(board, user2, "Player 2's turn to move.");
        // display board
        displayBoard(board);
        // check user2 win
        if (checkWinning(board, user2)) {
            cout << "Player 2 wins! ";
            break;
        }
        // increment moveCount
        moveCount++;
    }
    return 0;
}

int getUserMakeMove(string board[][3], string playerType, string prompt) {
    int row =4, col=4;
    bool invalidInput=true; // use to repeat the loop

    cout << prompt << endl; // display message like Player 1 Turn to Move
    // loop while invalid input
    while (invalidInput) {
        // get user to enter a good row value
        row = getAnInt(0, 2, "Please enter row number as 0, 1, 2: ");
        // get user to enter a good column val
        col = getAnInt(0, 2, "Please enter column number as 0, 1, 2: ");
        // check if the slot is free, mark the move and return 1
        if (board[row][col]== "*") {
            board[row][col] = playerType; // either "X" or "O"
            return 1;
        }
        else
            cout << "oops! position is taken!" << endl;

    }
    return 0;
}

void displayBoard(string board[][3]) {
    cout << " " << board[0][0] << " " << board[0][1] << " " << board[0][2] << endl;
    cout << " " << board[1][0] << " " << board[1][1] << " " << board[1][2] << endl;
    cout << " " << board[2][0] << " " << board[2][1] << " " << board[2][2] << endl;
}

int getAnInt(double lowerBound, double upperBound, string askUser) {
    string inputStr;
    bool badInput = true;
    int number;

    do {
        cout << askUser << endl; // endl is go to new line
        cin >> inputStr;
        badInput = !(sscanf(inputStr.c_str(), "%d", &number));
        if (badInput != true) {
                if ( (number >= lowerBound) && (number <= upperBound) ) {
                    return number; // we got a valid number
                }
                else {
                    badInput = true; // make sure we get another input
                }
        }
        cout << "Invalid input!" << endl;
    } while (badInput == true);
    return 0;
}

bool checkWinning(string board[][3], string player) {
    if ( checkWinningRow(board, player, 0) || checkWinningRow(board, player, 1)
          || checkWinningRow(board, player, 2) )  {
        return true;
    }
    if ( checkWinningCol(board, player, 0) || checkWinningCol(board, player, 1)
          || checkWinningCol(board, player, 2) )  {
        return true;
    }
    if (checkWinningDiagonal(board, player) ) {
        return true;
    }

    return false;
}

bool checkWinningRow(string board[][3], string player, int row) {
    // if all element of a row has player string
    if ( (board[row][0] == player) && (board[row][1] == player) && (board[row][2] == player) )  {
        return true;
    }
    return false;
}
bool checkWinningCol(string board[][3], string player, int col) {
    // if all element of a row has player string
    if ( (board[0][col] == player) && (board[1][col] == player) && (board[2][col] == player) )  {
        return true;
    }
    return false;
}


bool checkWinningDiagonal(string board[][3], string player) {
    // for top-left to bottom-right diagonal line which has player string X or O
   if ( (board[0][0] == player) && (board[1][1] == player) && (board[2][2] == player) )  {
        return true;
    }
    else if ( (board[0][2] == player) && (board[1][1] == player) && (board[2][0] == player) ){
    // for top-right to bottom left diagonal line which has player string of X or O
        return true;
    }
    return false;
}
