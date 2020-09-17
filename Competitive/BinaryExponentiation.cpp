#include<iostream>
using namespace std;

long binPow_01(long a, long b){
    if(b == 0){
        return 1;
    }
    long res = binPow_01(a, b / 2);
    if(b % 2){
        return res * res;
    }else{
        return res * res * a;
    }
}

long binPow_02(long a, long b){
    long res = 1;
    while(b > 0){
        if(b & 1){
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}

long long binpow_03(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

void solve(){
    // cout << binPow_01(4, 8) << endl;
    // cout << binPow_02(8, 99) << endl;
    // cout << binpow_03(8, 99, 2);
}



int main(){
    solve();
    return 0;
}
