#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> dp(100001, vector<pair<int, int>>(2, make_pair(-1, -1)));

pair<int, int> solve(vector<pair<int, vector<int>>>& graph, int current, bool force) {
    if(dp[current][force].first != -1)
        return dp[current][force];
    pair<int, int> sol(force, force * graph[current].first);
    if(!force) {
        for(auto adj : graph[current].second) {
            pair<int, int> res = solve(graph, adj, true);
            sol.first += res.first;
            sol.second += res.second;
        }
    } else {
        for(auto adj : graph[current].second) {
            pair<int, int> resA = solve(graph, adj, true);
            pair<int, int> resB = solve(graph, adj, false);

            if((resA.first < resB.first) || (resA.first == resB.first && resA.second > resB.second)) {
                sol.first += resA.first;
                sol.second += resA.second;
            } else {
                sol.first += resB.first;
                sol.second += resB.second;
            }
        }

        dp[current][force] = sol;
    }

    return sol;
}

int main() {

    string line;

    vector<pair<int, vector<int>>> graph (100001, make_pair(0, vector<int>()));

    while(getline(cin, line)) {
        if(line == "-1") {
            pair<int, int> solA = solve(graph, 0, false);
            pair<int, int> solB = solve(graph, 0, true);

            if((solB.first < solA.first) || (solB.first == solA.first && solB.second > solA.second))
                cout << solB.first << " " << solB.second << '\n';
            else
                cout << solA.first << " " << solA.second << '\n';

            continue;
        }
        stringstream ss(line);

        vector<int> input;
        int x;
        while(ss >> x)
            input.push_back(x);

        graph[input[0]] = make_pair(0, vector<int>());
        dp[input[0]] = vector<pair<int, int>>(2, make_pair(-1, -1));

        graph[input[0]].first = input[input.size()-1];
        for(int i = 1; i < (int) input.size() - 1; i++)
            graph[input[0]].second.push_back(input[i]);
    }

    return 0;
}
