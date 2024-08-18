#include <iostream>
#include <cstdlib> // For random number generation
#include <ctime>   // For seeding the random number generator
using namespace std;

char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
char currentMarker;
int currentPlayer;

void drawBoard() {
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentMarker;
        return true;
    }
    return false;
}

int checkWinner() {
    // Rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return currentPlayer;
    }
    // Columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return currentPlayer;
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return currentPlayer;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return currentPlayer;

    return 0; // No winner yet
}

int getRandomMove() {
    int slot;
    do {
        slot = rand() % 9 + 1;
    } while (!placeMarker(slot));  // Keep generating random moves until a valid one is found

    return slot;
}

void swapPlayerAndMarker() {
    if (currentMarker == 'X') currentMarker = 'O';
    else currentMarker = 'X';

    if (currentPlayer == 1) currentPlayer = 2;
    else currentPlayer = 1;
}

int main() {
    srand(time(0));  // Seed the random number generator

    cout << "Welcome to Tic-Tac-Toe!" << endl;
    currentPlayer = 1;
    currentMarker = 'X';

    int winner = 0;
    int slot;

    drawBoard();

    for (int i = 0; i < 9; i++) {
        if (currentPlayer == 1) {
            // Player's turn
            cout << "Your turn babyDoll!. Enter a slot (1-9): ";
            cin >> slot;

            if (slot < 1 || slot > 9) {
                cout << "Invalid slot niger! Try again." << endl;
                i--; // Retry the same turn
                continue;
            }

            if (!placeMarker(slot)) {
                cout << "Slot already taken Stupid! Try again." << endl;
                i--; // Retry the same turn
                continue;
            }
        } else {
            // Machine's turn
            cout << "Machine's turn..." << endl;
            slot = getRandomMove();
            cout << "Machine placed at slot " << slot << endl;
        }

        drawBoard();
        winner = checkWinner();

        if (winner != 0) {
            if (winner == 1) cout << "Congratulations! You win! You got lucky lil bro!!" << endl;
            else cout << "Machine wins! Aap men nhi ho! LOLOLOLOLOL!!" << endl;
            break;
        }

        swapPlayerAndMarker();
    }

    if (winner == 0) {
        cout << "F**k , It's a draw!" << endl;
    }

    return 0;
}
