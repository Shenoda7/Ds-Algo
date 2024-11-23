#include <bits/stdc++.h>

using namespace std;
class ObjectIdMapper{
private:
    unordered_map<string, int> str_to_id;
    unordered_map<int, string> id_to_str;

public:
    int getId(string &str) {
        if(str_to_id.count(str)) {
            return str_to_id[str];
        }
        else {
            int id = str_to_id.size();
            str_to_id[str] = id;
            id_to_str[id] = str;
            return id;
        }
    }

    string getStr(int id) {
        return id_to_str[id];
    }
};

struct edge {
    int to;
    int cost;
};

class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};

typedef vector<vector<int>> GRAPH;

void add_edge(GRAPH &graph, int from, int to) {
    graph[from].push_back(to);
}


void dfs(GRAPH &graph, int node, vector<bool> &vis, vector<int> &ans) {
    vis[node] = true;
    ans.push_back(node);
    for(int x : graph[node]) {
        if(!vis[x]) {
            dfs(graph, x, vis, ans);
        }
    }
}

vector<int> kill_process(vector<int> &pid, vector<int> &ppid, int kill) {
    int nodes = pid.size() + 1;
    GRAPH graph(nodes);
    for(int i = 0; i < (int) ppid.size(); ++i) {
        add_edge(graph, ppid[i], pid[i]);
    }
    vector<bool> vis(nodes, 0);
    vector<int> res;
    dfs(graph, kill, vis, res);
    if(res.size() == nodes) return {0};
    return res;
}


void dfs(int id, vector<bool> &vis, vector<Employee*> &employees, int &total) {
    vis[id] = true;
    cout << id << " ";
    total += employees[id]->importance;
    for(int &x : employees[id]->subordinates) {
        if(!vis[x]) {
            dfs(x, vis, employees, total);
        }
    }
}

int getImportance(vector<Employee*> employees, int id) {
    int nodes = employees.size();
    vector<bool> vis(2000, 0);
    int total = 0;
    dfs(id, vis, employees, total);
    return total;
}

void dfs(GRAPH &graph, int node, vector<bool> &vis) {
    vis[node] = true;
    for(int x : graph[node]) {
        if(!vis[x]) {
            dfs(graph, x, vis);
        }
    }
}

int number_of_connected_components(GRAPH &graph) {
    int cnt = 0;
    int nodes = graph.size();
    vector<bool> vis(nodes, 0);
    for(int node = 0; node < nodes; ++node) {
        if(!vis[node]) {
            dfs(graph, node, vis);
            cnt++;
        }
    }
    return cnt;
}


typedef vector<vector<int>> GRAPH;
void topological_sorting_using_dfs(vector<bool>& vis, stack<int>& st, GRAPH& grid, int& node) {
    vis[node] = true;
    for(int neighbor : grid[node]) {
        if(!vis[neighbor]) {
            topological_sorting_using_dfs(vis, st, grid, neighbor);
        }
    }
    st.push(node);
}

void test1() {
    int nodes, edges;
    cin >> nodes >> edges;

    GRAPH graph(nodes + 1);
    for(int e = 0; e < edges + 1; ++e) {
        int from, to;
        cin >> from >> to;
        add_edge(graph, from, to);
    }
    vector<bool> vis(nodes + 1, 0);
    stack<int> st;
    for(int i = 0; i < nodes ; ++i) {
        if(!vis[i]) {
            topological_sorting_using_dfs(vis, st, graph, i);
        }
    }
    vector<int> res;
    while(!st.empty()) {
        res.push_back(st.top());
        st.pop();
    }
    for(int i = 0; i < (int) res.size(); ++i) {
        if(res[i] == 0)continue;
        if(i) cout << " ";
        cout << res[i];

    }
}

int main(){
    test1();

    return 0;
}
//in testing --> always consider special graphs
//graph of a single node(maybe with a loop)
//graph of N nodes
//graph that is :chain, tree, complete, dense, sparse


//weighted
/*
5 7
0 1 10
0 2 20
1 3 15
1 4 67
2 3 101
3 4 34
4 3 43
*/

/*
5 10
0 1 10
1 2 7
0 1 7
2 3 9
2 3 15
3 4 50
0 4 52
0 4 30
2 4 36
4 0 150
*/

//unweighted
/*
6 8
0 1
0 2
2 1
2 4
2 5
2 3
2 4
4 5
*/

