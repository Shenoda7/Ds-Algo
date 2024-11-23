#include <bits/stdc++.h>

using namespace std;

class trie {
private:
    static const int MAX_CHAR = 256;
    trie* child[MAX_CHAR];
    bool isLeaf { };

public:
    trie() {
        memset(child, 0, sizeof(child));
    }

    void insert(string str, int idx = 0) {
        if(idx == (int) str.size())
            isLeaf = 1;
        else {
            int cur = str[idx] - 'a';
            if(child[cur] == 0)
                child[cur] = new trie();
            child[cur]->insert(str, idx + 1);
        }
    }

    void insert_iterativly(string str) {
        trie *node = this;
        for(int i = 0; i < (int) str.size(); ++i) {
            int cur = str[i] - 'a';
            if(node->child[cur] == 0)
                node->child[cur] = new trie();
            node = node->child[cur];
        }
        node->isLeaf = 1;
    }

    bool word_exist_iterativly(string str) {
        trie* node = this;
        for(char c : str) {
            int cur = c - 'a';
            if(node->child[cur] == 0)
                return 0;
            node = node->child[cur];
        }
        return node->isLeaf;
    }

    bool word_exist(string str, int idx = 0) {
        if(idx == (int) str.size())//here it might not be a leaf so it's not a complete word
            return isLeaf;

        int cur = str[idx] - 'a';
        if(child[cur] == 0)
            return 0;

        return child[cur]->word_exist(str, idx + 1);
    }

     bool prefix_exist_iterativly(string str) {
        trie* node = this;
        for(char c : str) {
            int cur = c - 'a';
            if(node->child[cur] == 0)
                return 0;
        }
        return true;
    }

     bool prefix_exist(string str, int idx = 0) {
        if(idx == (int) str.size())//all size of prefix is checked which is true
            return true;

        int cur = str[idx] - 'a';
        if(child[cur] == 0)
            return false;
        return prefix_exist(str, idx + 1);
    }

    string first_word_prefix(const string &str) {//xyzabc, xyz, a, abc, ab
        trie* node = this;

        for(int i = 0; i < (int) str.size(); ++i) {
            int cur = str[i] - 'a';
            if(!node->child[cur])//path don't exist
                break;

            if(node->child[cur]->isLeaf)
                return str.substr(0, i + 1);

            node = node->child[cur];
        }
        return str;
    }

};


class Trie {//only 2 methods insert and isSuffix
private:
    static const int MAX_CHAR = 26;
    Trie* child[MAX_CHAR];
    bool isLeaf { };

public:
    Trie () {
        memset(child, 0, sizeof(child));
    }

    void insert(string str) {
        reverse(str.begin(), str.end());
        Trie *node = this;
        for(int i = 0; i < (int)str.size(); ++i) {
            int cur = str[i] - 'a';
            if(node->child[cur] == 0)
                node->child[cur] = new Trie();
            node = node->child[cur];
        }
    }

    bool suffix_exist(string str) {
        reverse(str.begin(), str.end());
        Trie *node = this;
        for(int i = 0; i < (int) str.size(); ++i) {
            int cur = str[i] - 'a';
            if(!node->child[cur])
                return 0;
        }
        return true;
    }
};


class trie2 {//using map
private:
    map<int, trie2*> child;
    bool isLeaf { };

public:
    trie2() {
    }

    void insert(string str) {
        trie2* node = this;
        for(int idx = 0; idx < (int) str.size(); ++idx) {
            int cur = str[idx] - 'a';
            if(!node->child.count(cur))
                node->child[cur] = new trie2();

            node = node->child[cur];
        }
        node->isLeaf = 1;
    }

    bool word_exist(string str) {
        trie2* node = this;

        for(int idx = 0; idx < (int) str.size(); ++idx) {
            int cur = str[idx] - 'a';
            if(!node->child.count(cur))
                return false;
            node = node->child[cur];
        }
        return node->isLeaf;
    }

};



int main(){

    return 0;
}
