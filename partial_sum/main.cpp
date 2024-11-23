#include<bits/stdc++.h>
using namespace std;

#define ll long long

#define loop(n) for(int i = 0; i < n; ++i)
//parital sum.

//simple but yet a powerful technique.

/*
Assume you have N counters, intialized to 0.

    1 2 3 4 5 6 7 8 9 10
    0 0 0 0 0 0 0 0 0 0


The updates are of the following form:
Increment the counters from L to R by K.

Ex:    2 7 1
       4 9 3

    1 2 3 4 5 6 7 8 9 10
    0 1 1 4 4 4 4 3 3 0

>> complexity :o(n*m), n = numcounters, m = numupdates.

Can we reduce the complexity to o(n+m)?

L = 2, R = 7, K = 1;

      1 2 3 4 5 6 7 8 9 10                   here if i have 1 uptade.
a=    0 1 0 0 0 0 0 -1 0 0
pre=  0 1 1 1 1 1 1  0  0  0

 --------------------------------------
 L = 2, R = 7, K = 1;
 L = 4, R = 9, K = 3;

      1 2 3 4 5 6 7  8  9 10
a=    0 1 0 3 0 0 0 -1  0 -3
pre=  0 1 1 4 4 4 4  3  3  0

*/
// ----------------------------------------------
///int a[MAXN+9];
//global----> MAXN here refer to the maximum N counter int the problem,
// and the 9 to free up more space in the array in case i wanted to switch to 1 based.
int a[1000];


int main(){

    std::ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m; cin >> n >> m;

    for(int i = 0; i < m; ++i){
        int l, r, k; cin >> l >> r >> k;
        a[l] += k;
        a[r+1] -= k;
    }
    for(int i = 1; i < n; ++i) a[i] += a[i-1];  //same as prefix sum way, but smarter.




    return 0;
}
