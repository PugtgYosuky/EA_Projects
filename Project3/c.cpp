#include <bits/stdc++.h>

using namespace std;

int start_node = -1, end_node = -1;

enum node_state {
    WHITE, GRAY, BLACK
};

bool has_cycles(int current_node, vector<vector<int>>& graph, vector<node_state>& state){
    state[current_node] = GRAY;

    for(int& child : graph[current_node])
        if((state[child] == GRAY) || (state[child] == WHITE && has_cycles(child, graph, state)))
            return true;

    state[current_node] = BLACK;

    return false;
}

bool valid(int n, vector<vector<int>>& graph, vector<vector<int>>& i_graph) {

    for(int i = 0; i < n; i++){
        if (i_graph[i].size() == 0){
            if(start_node == -1)
                start_node = i;
            else
                return false; // more than 1 initial node
        }
    }

    for(int i = 0; i < n; i++) {
        if(graph[i].size() == 0) {
            if(end_node == -1)
                end_node = i;
            else
                return false; // more than 1 terminal node
        }
    }

    if(start_node == -1 || end_node == -1)
        return false;

    vector<bool> visited(n, false);
    queue<int> q;
    int cnt_visited = 0;

    q.push(start_node);
    visited[start_node] = true;
    int node;
    while(!q.empty()){
        node = q.front();
        q.pop();

        cnt_visited++;

        for(int& v : graph[node]){
            if(!visited[v]){
                visited[v] = true;
                q.push(v);
            }
        }
    }

    if(cnt_visited != n)
        return false;
    
    vector<node_state> state(n, WHITE);

    return !has_cycles(start_node, graph, state);
}

void statistic_1(int n, vector<int>& t, vector<vector<int>>& graph, vector<vector<int>>& i_graph) {
    int time = 0;

    priority_queue<int, vector<int>, greater<int>> q;
    q.push(start_node);

    vector<int> counter(n, 0);

    vector<int> order;

    while(!q.empty()) {
        int node = q.top();
        q.pop();
        time += t[node];
        order.push_back(node);

        for(int& v : graph[node]) {
            counter[v]++;
            if(counter[v] == (int) i_graph[v].size())
                q.push(v);
        }
    }

    cout << time << endl;
    for(auto& node : order)
        cout << (node + 1) << endl;
}

void statistic_2(int n, vector<int>& t, vector<vector<int>>& graph, vector<vector<int>>& i_graph) {
    queue<pair<int, int>> q;

    q.emplace(start_node, 0);
    vector<int> counter(n, 0), mx(n, 0);
    mx[start_node] = t[start_node];
    
    while(!q.empty()) {
        pair<int, int> node = q.front();
        q.pop();
        for(int& v : graph[node.first]){
            mx[v] = max(mx[v], mx[node.first] + t[v]);
            counter[v]++;
            if(counter[v] == (int) i_graph[v].size())
                q.emplace(v, node.second + 1);
        }

    }

    cout << mx[end_node] << endl;
}

void statistic_3(int n, vector<vector<int>>& graph, vector<vector<int>>& i_graph) {
    queue<pair<int, int>> q;

    vector<int> counter(n, 0), level(n);

    q.emplace(start_node, 0);

    while(!q.empty()) {
        pair<int, int> node = q.front();
        q.pop();

        level[node.first] = node.second;

        for(int& v : graph[node.first]){
            counter[v]++;
            if(counter[v] == (int) i_graph[v].size())
                q.emplace(v, node.second + 1);
        }
    }

    q.emplace(start_node, 0);
    counter = vector<int>(n, 0);

    while(!q.empty()) {
        pair<int, int> node = q.front();
        q.pop();

        vector<bool> visited(n, false);
        vector<bool> prev(n, false);

        queue<int> q2;
        q2.emplace(node.first);
        visited[node.first] = true;

        while(!q2.empty()) {
            int x = q2.front();
            q2.pop();

            prev[x] = true;

            for(int& adj : i_graph[x]) {
                if(!visited[adj]) {
                    visited[adj] = true;
                    q2.push(adj);
                }
            }
        }

        bool bottleneck = true;

        for(int i = 0; i < n; i++) {
            if(level[i] <= level[node.first] && !prev[i]) {
                bottleneck = false;
                break;
            }
        }

        if(bottleneck)
            cout << (node.first+1) << endl;

        for(int& v : graph[node.first]){
            counter[v]++;
            if(counter[v] == (int) i_graph[v].size())
                q.emplace(v, node.second + 1);
        }
    }
}

int main() {

    int n, d, a, s;
    cin >> n;

    vector<int> t(n);
    vector<vector<int>> graph(n), i_graph(n);
    
    for(int i = 0; i < n; i++) {
        cin >> t[i];
        cin >> d;
        for(int j = 0; j < d; j++) {
            cin >> a;
            a--;
            i_graph[i].push_back(a);
            graph[a].push_back(i);
        }
            
    }
    
    cin >> s;

    if(!valid(n, graph, i_graph)) {
        cout << "INVALID" << endl;
        return 0;
    }

    switch(s) {
        case 0:
            cout << "VALID" << endl;
            break;
        case 1:
            statistic_1(n, t, graph, i_graph);
            break;
        case 2:
            statistic_2(n, t, graph, i_graph);
            break;
        case 3:
            statistic_3(n, graph, i_graph);
            break;
        default:
            break;
    }

    return 0;
}
