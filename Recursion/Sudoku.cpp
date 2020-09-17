#include<iostream>
using namespace std;

void sudokuSolve(int board[][], int i, int j){
    int next_i = 0;
    int next_j = 0;

    if(j == board[0].length - 1){
        next_i = i + 1;
        next_j = 0;
    }
    else{
        next_i = 0;
        next_j = j + 1;
    }

    //non zero values:

    if(board[i][j] != 0){
        sudokuSolve(board, next_i, next_j);
    }else{
        for(int num = 1; num <= 9; num++){
            if(isValid(board, i, j, num)){ // if the place is valid to put the no the place it
                board[i][j] = num;
                sudokuSolve(board, ni, nj); // call for the next col
                board[i][j] = 0; //if u didn't found valid value in the end backtrack(in a postorder manner)
            }
        }
    }
}

bool isValid(int board[][], int x, int y, int num){
    //col
    for(int i=0; i<9; i++){
        if(board[x][i] == num){
            return false;
        }
    }

    //row
    for(int j=0; j<9; j++){
        if(board[j][y] == num){
            return false;
        }
    }
    int smi = x / 3 * 3;
    int smj = y / 3 * 3;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[smi + i][smj + j] == num){
                return false;
            }
        }
    }
    return true;
}

void solve(){
    int board[][] = {{3,0,6,5,0,8,4,0,0},
                {5,2,0,0,0,0,0,0,0},
                {0,8,7,0,0,0,0,3,1},
                {0,0,3,0,1,0,0,8,0},
                {9,0,0,8,6,3,0,0,5},
                {1,3,0,0,0,0,2,5,0},
                {0,0,0,0,0,0,0,7,4},
                {0,0,5,2,0,6,3,0,0},
                {0,5,0,0,9,0,6,0,0}
                };
    for(int i=0; i<board.length; i++){
        for(int j=0; j<board[0].length; j++){
            sudokuSolve(board, i, j);
        }
        cout << endl;
    }
}
int main(){
    solve();
    return 0;
}
