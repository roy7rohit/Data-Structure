#include<iostream>
#include<vector>
using namespace std;


void printAbreviations(string str, string ans, int count, int pos){
    if(pos == str.length()){
        if(count == 0){
            cout << ans << endl;
        }else{
            cout << ans + to_string(count) << endl;
        }
        return;
    }

    if(count > 0){
        printAbreviations(str, ans + to_string(count) + str[pos], 0, pos + 1);
    }else{

        printAbreviations(str, ans + str[pos], 0, pos + 1);
    }
    printAbreviations(str, ans, count + 1, pos + 1);
}
//================================================================================================
void lexicoDFS(int i, int n){
    if(i > n){
        return;
    }
    cout << i << endl;
    for(int j = 0; j< 10; j++){
        lexicoDFS(10 * i + j, n);
    }
}


//================================================================================================

vector<int> charToNumMapping(26, 0);
int isUsed = 0;
string str1 = "send";
string str2 = "more";
string str3 = "money";

int stringToNum(string str){
    int res = 0;
    for(int i=0; i<=9; i++){
        res = res * 10 + charToNumMapping[str[i] - 'a'];
    }
    return res;
}

int cryptoSolver(string str, int idx){
    if(idx == str.length()){
        int num1 = stringToNum(str1);
        int num2 = stringToNum(str2);
        int num3 = stringToNum(str3);

        if(num1 + num2 == num3 && charToNumMapping[str3[0] - 'a'] != 0){
            cout << num1 << endl;
            cout << "+" + num2 << endl;
            cout << "------" << endl;
            cout << num3 << endl;
            cout << endl;

            return 1;
            }
            return 0;
        }

        int count = 0;
        for(int num=0; num<=9; num++){
            int mask = (1 << num);
            if((isUsed & mask) == 0){
                isUsed ^= mask;
                charToNumMapping[str[idx] - 'a'] = num;

                count += cryptoSolver(str, idx + 1);

                isUsed ^= mask;
                charToNumMapping[str[idx] - 'a'] = 0;

            }
        }
        return count;
    }


void isSolvable() {
    vector<int> freq(26, 0);
    string str = str1 + str2 + str3;
    for (int i = 0; i < str.length(); i++) {
        freq[str[i] - 'a']++;
   }

        str = "";
        for (int i = 0; i < 26; i++){
            if (freq[i] > 0) {
                str += (char) (i + 'a');
            }
        }

        cout<< cryptoSolver(str, 0) << endl;
    }


// =============================================================================================
int permutationWithDuplicates(string str, string ans){
    if(str.length() == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i=0; i<str.length(); i++){
        char ch = str[i];
        string ros = str.substr(0, i) + str.substr(i + 1);
        count += permutationWithDuplicates(ros, ans + ch);
    }
    return count;
}

int permutationWithoutDuplicates(string str, string ans){
    if(str.length() == 0){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    vector<bool> vis(26, 0);
    for(int i=0; i<str.length(); i++){
        char ch = str[i];
        if(!vis[ch - 'a']){
            vis[ch - 'a'] = true;
            string ros = str.substr(0, i) + str.substr(i + 1);
            count += permutationWithoutDuplicates(ros, ans + ch);
        }
    }
    return count;
}


int main(){
    // printAbreviations("pep", "", 0, 0);
    // for(int i=1; i<=9; i++){
    //     lexicoDFS(i, 200);
    // }

    isSolvable();
    // cout << permutationWithDuplicates("abc", "");
    // cout << permutationWithoutDuplicates("ab", "");
    return 0;
}
