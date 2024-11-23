#include<bits/stdc++.h>
using namespace std;

#define ll long long


int main(){

    std::ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);


    int arr[] = {2, 5, 5, 3, 5, 2};
    int sz = sizeof(arr)/sizeof(arr[0]);

    for(int i = 0; i < sz; ++i)
        cout << arr[i] << " ";
    cout << "\n";

    int prefix_sum[sz];

    prefix_sum[0] = arr[0];
    for(int i = 1; i < sz; ++i){
        prefix_sum[i] = prefix_sum[i-1] + arr[i];
    }

    for(int i = 0; i < sz; ++i)
        cout << prefix_sum[i] << " ";
    cout << "\n";

    int prefix_sum_5[sz] = {0};
    for(int i = 0; i < sz; ++i){
            prefix_sum_5[i] = prefix_sum_5[i-1] + (arr[i] == 5);// to find how many times 5 appeared.
    }
    cout << prefix_sum_5[5];
    return 0;
}
