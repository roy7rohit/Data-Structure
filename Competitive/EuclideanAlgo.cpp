#include<iostream>
#include<utility>
using namespace std;

int gcd_01(int a, int b){
    if(b == 0){
        return a;
    }
    else{
        return gcd_01(b, a % b);
    }
}

int gcd_02(int a, int b){
    return b ? gcd_02(b, a % b) : a;
}

int gcd_03(int a, int b){
    while(b){
        a %= b;
        swap(a, b);
    }
    return a;
}

int lcm(int a, int b){
    return (a / gcd_03(a, b))* b;
}


// pair<int, int> fib(int n) {
//     if (n == 0)
//         return {0, 1};

//     auto p = fib(n >> 1);
//     int c = p.first * (2 * p.second - p.first);
//     int d = p.first * p.first + p.second * p.second;
//     if (n & 1)
//         return {d, c + d};
//     else
//         return {c, d};
// }



void solve(){

    cout << lcm(60, 24) << endl;
}


int main(){

    solve();
    return 0;
}
