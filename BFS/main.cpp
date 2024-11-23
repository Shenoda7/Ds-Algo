#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> GRAPH;
const int OO = INT_MAX;


void add_edge(int from, int to, GRAPH& adjList) {
    adjList[from].push_back(to);
    adjList[to].push_back(from);
}

vector<int> BFS_v1(GRAPH& adjList, int start) {
    vector<int> len(adjList.size(), OO);
    queue<pair<int, int>> q;
    q.push( {start, 0} );
    len[start] = 0;

    while(!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        int cur = p.first, level = p.second;

        for(int neighbor : adjList[cur]) {
            if(len[neighbor] == OO) {
                q.push( {neighbor, level + 1} );
                len[neighbor] = level + 1;
            }
        }
    }
    return len;
}

bool BFS_v2(GRAPH& adjList, int start) {
    vector<int> len(adjList.size(), OO);
    vector<int> parent(adjList.size(), -1);

    queue<int> q;
    q.push(start);
    len[start] = 0;

    int visitedNodes = 1;

    for(int level = 0, sz = 1; !q.empty(); ++level, sz = q.size()) {
        while(sz--) {
            int cur = q.front();
            q.pop();

            for(int neighbor : adjList[cur]) {
                if(neighbor == parent[cur])
                    continue;//fake cycle
                if(len[neighbor] == OO) {//never visited
                    q.push(neighbor);
                    len[neighbor] = level + 1;
                    parent[neighbor] = cur;
                    visitedNodes++;

                }
                else return false; //visited before, then it's a cycle
            }
        }
    }

    return visitedNodes == (int) adjList.size();
}

/*
to check if the graph is a valid tree
we need to check that we have 1) N - 1 edges
                      and --->2) No cycles in the graph at all
*/

int main(){

    int n, e;
    cin >> n >> e;
    GRAPH adjList(n);

    for(int i = 0; i < e; ++i) {
        int from, to;
        cin >> from >> to;

        add_edge(from, to, adjList);
    }
    if(e != n - 1)
        cout << 0 << ": here i am";
    else
        cout << BFS_v2(adjList, 0);

    return 0;
}
