#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define ll long long
#define ld long double
#define loop(n) for(int i = 0; i < n; ++i)
#define Shenoda ios_base::sync_with_stdio(false); cin.tie(NULL);

const long long M = 1e9+7;
ll mod(ll x) { return ((x % M + M) % M); }
ll add(ll a, ll b) { return mod(mod(a) + mod(b)); }
ll mul(ll a, ll b) { return mod(mod(a) * mod(b)); }
ll gcd(ll x, ll y) { return (!y ? x : gcd(y, x % y)); } //if y is zero return x;
ll lcm(ll x, ll y) { return x / gcd(x, y) * y; }
ll fastpow(ll x, ll n){ll res = 1;while(n){if(n % 2 == 1)res = (res * x);x = mul(x, x);n /= 2;} return res; }

string encode(vector<string>& strs) {
        string encoded = "";
        for(int i = 0; i < strs.size(); ++i) {
            int sz = strs[i].size();
            string sz_as_str = to_string(sz) + "#";
            encoded += sz_as_str;
            for(int j = 0; j < strs[i].size(); ++j){
                encoded += strs[i][j];
            }
        }
        return encoded;
    }

    vector<string> decode(string s) {
        vector<string> decoded;
        string str = "";
        int cnt = 0;
        int sz = s[0] - '0'+ 1;
        for(int i = 0; i < s.size(); ++i) {
            if(cnt == sz) {
                sz = s[i] - '0';
                cnt = 0;
                decoded.push_back(str);
                str = "";
            }
            if(s[i + 1] == '#' && ((s[i] - '0') == sz ))
                continue;
            str += s[i+1];
            cnt++;
        }
        return decoded;
    }

int main(){
    Shenoda;

    int t = 1;
    //cin >> t;
    while(t--) {
        vector<string> strs = {"neet", "code"};
        string str = encode(strs);
        cout << str << "\n";
        vector<string> res = decode(str);
        for(string str : res) cout << str;

    }
    return 0;
}



