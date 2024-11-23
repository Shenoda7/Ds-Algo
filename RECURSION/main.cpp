#include <iostream>

using namespace std;
#define loop(n) for(int i = 0; i < n; ++i)

void right_max(int arr[], int len){
    if(len == 1)
        return;
    arr[len - 2] = max(arr[len - 2], arr[len - 1]);
    right_max(arr, len - 1);
}

int suffix_sum(int arr[], int len, int cnt){
    if(cnt == 0)
        return 0;
    return arr[len - 1] + suffix_sum(arr, len - 1, cnt - 1);
}

int prefix_sum(int arr[], int len, int cnt){
    if(cnt == 0)
        return 0;
    return arr[cnt - 1] + prefix_sum(arr, len - 1, cnt - 1);
}


bool is_palindrome(int arr[], int start, int endd) {
    if(start >= endd)
        return true;
    if(arr[start] != arr[endd])
        return false;
    return is_palindrome(arr, start + 1, endd - 1);
}

bool is_palindrome_v2(int arr[], int endd){
    if(endd <= 0)
        return true;

    if(arr[0] != arr[endd])
        return false;

    return is_palindrome_v2(arr + 1, endd - 2);
}

bool is_prefix(string main, string prefix, int start_idx = 0){
    if(start_idx == (int) prefix.size())
        return true;

    if(main[start_idx] != prefix[start_idx])
        return false;

    return is_prefix(main, prefix, start_idx + 1);
}


void do_somehing(int n){
    if(n) {
        do_somehing(n/10);
        cout << n % 10;

    }
}

int main(){

    return 0;
}
