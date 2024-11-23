#include <bits/stdc++.h>

using namespace std;

void insertion_sort(vector<int> &nums) {//time O(n^2)  space O(1)
    for(int i = 1; i < (int) nums.size(); ++i) {
        for(int j = i; j - 1 >= 0 && nums[j] < nums[j - 1]; --j)
            swap(nums[j], nums[j - 1]);
    }
}

void sortArray(vector<int> nums) {//leetcode 912
        const int shift_factor = 50000;
        for(int i = 0; i < (int) nums.size(); ++i)
            nums[i] += shift_factor;

        int mx = nums[0];
        for(int i = 1; i < (int) nums.size(); ++i) {
            mx = max(mx, nums[i]);
        }

        vector<int> count(mx + 1, 0);
        for(int i = 0; i < (int) nums.size(); ++i) {
            count[nums[i]]++;
        }
        int idx = 0;
        for(int i = 0; i <= mx; ++i) {
            for(int j = 0; j < count[i]; ++j, ++idx)
                nums[idx] = i - shift_factor;
        }
    for(int x : nums) cout << x << " ";

 }

void count_sort_strings(vector<string> strs) {
//    vector<string> res;
    const int LETTERS_SZ = 26;
    vector<vector<string>> mp(LETTERS_SZ);//we also could use map.

    for(int i = 0; i < (int) strs.size(); ++i) {
        mp[strs[i][0] - 'a'].push_back(strs[i]);
    }
    for(int letter = 0; letter < LETTERS_SZ; ++letter) {
        for(int str_idx = 0; str_idx < (int) mp[letter].size(); ++str_idx)
            cout << mp[letter][str_idx] << " ";
    }

}

int id(const string &str) {
    assert(str.size() >= 2);
    int f = str[0] - 'a';
    int s = str[1] - 'a';

    return f * 26 + s; //letters_sz;
}
void count_sort_strings2(vector<string> strs) { //bases on first 2 letters
    int sz = strs.size();
    int LETTERS_SZ = 26;
    int range = LETTERS_SZ * LETTERS_SZ;
    vector<vector<string>> mp(range);

    for(int i = 0; i < sz; ++i)
        mp[id(strs[i])].push_back(strs[i]);

    for(int letter = 0; letter < range; ++letter) {
        for(int str_idx = 0; str_idx < (int) mp[letter].size(); ++str_idx)
            cout << mp[letter][str_idx] << " ";
    }

}


void selection_sort(vector<int> &nums) {//time O(n^2)  space O(1)
    int n = nums.size();
    for(int i = 0; i < n - 1; ++i) {

        int min_idx = i;
        for(int j = i + 1; j < n; ++j) {
            if(nums[j] < nums[min_idx]) {
                min_idx = j;
            }
        }

        swap(nums[i], nums[min_idx]);
    }
}

vector<int> countsort(const vector<int> arr) {
    int sz = arr.size();
    int maxVal = arr[0];
    for(int i = 1; i < sz; ++i)
        if(arr[i] > maxVal)
            maxVal = arr[i];

    //compute freq
    vector<int> Count(maxVal + 1, 0);
    for(int i = 0; i < sz; ++i)
        Count[arr[i]]++;

    //accumulate the freq
    for(int i = 1; i <= maxVal; ++i)
        Count[i] += Count[i - 1];

    //find the idx and put the number
    vector<int> output(sz);
    for(int i = sz - 1; i >= 0; --i) {
        output[Count[arr[i]] - 1] = arr[i];
        Count[arr[i]]--;
    }
    return output;
}

int main(){

    count_sort_strings2({"shenoda", "ahmed", "adam", "yassa", "yaso"});
    return 0;
}
