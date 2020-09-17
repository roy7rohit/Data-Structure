#include<iostream>
#include<Array>
using namespace std;

bool matrix_search(int matrix[4][4], int num){
    int i = 0;
    int j = matrix[0].size();
    while(i < matrix.length && j >= 0){
        if(num == matrix[i][j]){
            cout << i << endl;
            cout << j << endl;
            return true;
        }
        else if(num < matrix[i][j]){
            j--;
        }
        else{
            i++;
        }
    }
   return false;
}


void solve(){
    int matrix[i][j] = {{11, 12, 13, 14},
                    {21, 22, 23, 24},
                    {31, 32, 33, 34},
                    {41, 42, 43, 44}};

    cout << matrix_search(matrix, 42) << endl;

}

int main(){
    solve();
    return 0;
}
