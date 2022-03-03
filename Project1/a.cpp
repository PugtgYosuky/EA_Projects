#include <bits/stdc++.h>

using namespace std;

struct piece {
    
    vector<vector<int>> values;
    vector<vector<vector<pair<piece*, int>>>> adj;
    bool used;
    int id;
    int rotation; // 0 = top, 1 -> right, 2 -> bottom, 3 -> left

    piece() {
        values = vector<vector<int>>();
        used = false;
        id = -1;
        rotation = 0;
        adj = vector<vector<vector<pair<piece*, int>>>> (4, vector<vector<pair<piece*, int>>>(4));
    }

    piece(int a, int b, int c, int d, int _id) {
        used = false;
        values = vector<vector<int>>(4);
        // lado -- rotacao
        adj = vector<vector<vector<pair<piece*, int>>>> (4, vector<vector<pair<piece*, int>>>(4));
        values[0] = vector<int>{a, b, c, d};
        values[1] = vector<int>{d, a, b, c};
        values[2] = vector<int>{c, d, a, b};
        values[3] = vector<int>{b, c, d, a};

        id = _id;
        rotation = 0;
    }

    // option: 0 -> top, 1 -> right, 2 -> bottom, 3 -> left
    pair<int, int> edge(int option, int rotation) {
        pair<int, int> res = make_pair(values[rotation][option], values[rotation][(option + 1) % 4]);
        if(option > 1)
            return make_pair(res.second, res.first);
        return res;
    }

};

void print_board(vector<vector<piece *>>& board, int r, int c) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            piece * p = board[i][j];
            if(p->values.size() == 0)
                cout << "_ _";
            else
                cout << p->values[p->rotation][0] << " " << p->values[p->rotation][1];
            if(j < c - 1)
                cout << "  ";
        }
        cout << endl;
        for(int j = 0; j < c; j++) {
            piece * p = board[i][j];
            if(p->values.size() == 0)
                cout << "_ _";
            else
                cout << p->values[p->rotation][3] << " " << p->values[p->rotation][2];
            if(j < c - 1)
                cout << "  ";
        }
        cout << endl;
        if(i < r - 1)
            cout << endl;
    }
}

bool solved = false;
piece * empty_piece = new piece();

void bruteforce(vector<vector<piece *>>& board, vector<int>& colors, int x, int y, int r, int c) {
    if(x == r - 1 && y == c - 1) {
        solved = true;
        return;
    }


    // x = linha, y = coluna
    int nextX, nextY;
    if(c <= r) { // ir por linhas
        nextX = x;
        nextY = y + 1;
        if(nextY >= c){
            nextX++;
            nextY = 0;
        }
    } else { // ir por colunas
        nextX = x + 1;
        nextY = y;
        if(nextX >= r){
            nextY++;
            nextX = 0;
        }
    }

    if(nextX > 0 && nextY > 0) {
        piece * prevTop = board[nextX-1][nextY];
        piece * prevLeft = board[nextX][nextY-1];

        if(prevTop->adj[2][prevTop->rotation].size() < prevLeft->adj[1][prevLeft->rotation].size()) {
            for(auto p : prevTop->adj[2][prevTop->rotation]) {
                if(p.first->used) continue;
                if(binary_search(prevLeft->adj[1][prevLeft->rotation].begin(), prevLeft->adj[1][prevLeft->rotation].end(), p)) {
                    board[nextX][nextY] = p.first;
                    p.first->rotation = p.second;
                    p.first->used = true;
                    bruteforce(board, colors, nextX, nextY, r, c);
                    if(solved)
                        return;
                    p.first->used = false;
                }
            }
        } else {
            for(auto p : prevLeft->adj[1][prevLeft->rotation]) {
                if(p.first->used) continue;
                if(binary_search(prevTop->adj[2][prevTop->rotation].begin(), prevTop->adj[2][prevTop->rotation].end(), p)) {
                    board[nextX][nextY] = p.first;
                    p.first->rotation = p.second;
                    p.first->used = true;
                    bruteforce(board, colors, nextX, nextY, r, c);
                    if(solved)
                        return;
                    p.first->used = false;
                }
            }
        }
    } else {
        int side = nextY == 0 ? 2 : 1;
        piece * prev = nextY == 0 ? board[nextX-1][nextY] : board[nextX][nextY-1];
        for(auto& adj : prev->adj[side][prev->rotation]) {
            if(adj.first->used) continue;
            board[nextX][nextY] = adj.first;
            adj.first->rotation = adj.second;
            adj.first->used = true;
            bruteforce(board, colors, nextX, nextY, r, c);
            if(solved)
                return;
            adj.first->used = false;
        }
    }
}

int main() {

    int t, n, r, c, w, x, y, z;
    cin >> t;
    int count_odd;
    
    while(t--) {
        vector <int> colors (1000, 0);
        solved = false;
        cin >> n >> r >> c;
        vector<piece> pieces(n);
        vector<vector<piece *>> board(r, vector<piece *>(c, empty_piece));

        for(int i = 0; i < n; i++) {
            cin >> w >> x >> y >> z;
            pieces[i] = piece(w, x, y, z, i);
            colors[w]++;
            colors[x]++;
            colors[y]++;
            colors[z]++;
        }
        
        count_odd = 0;
        for(int i = 0; i < 1000; i++)
            count_odd += colors[i] % 2;

        bool possible = count_odd <= 4;

        for(int i = 0; i < n; i++){
            if(!possible)
                break;
            for(int j = i + 1; j < n; j++){
                for(int k = 0; k < 4; k++) {
                    for(int l = 0; l < 4; l++){
                        if(pieces[i].edge(0, k) == pieces[j].edge(2, l)) {
                            pieces[i].adj[0][k].emplace_back(&pieces[j], l);
                            pieces[j].adj[2][l].emplace_back(&pieces[i], k);
                        }
                        if(pieces[i].edge(1, k) == pieces[j].edge(3, l)) {
                            pieces[i].adj[1][k].emplace_back(&pieces[j], l);
                            pieces[j].adj[3][l].emplace_back(&pieces[i], k);
                        }
                        if(pieces[i].edge(2, k) == pieces[j].edge(0, l)) {
                            pieces[i].adj[2][k].emplace_back(&pieces[j], l);
                            pieces[j].adj[0][l].emplace_back(&pieces[i], k);
                        }
                        if(pieces[i].edge(3, k) == pieces[j].edge(1, l)) {
                            pieces[i].adj[3][k].emplace_back(&pieces[j], l);
                            pieces[j].adj[1][l].emplace_back(&pieces[i], k);
                        }
                    }
                }
            }
            int adj_count = 0;
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 4; k++) {
                    sort(pieces[i].adj[j][k].begin(), pieces[i].adj[j][k].end(), [&](const pair<piece *, int>& a, const pair<piece *, int>& b) {
                        if(a.first->id == b.first->id)
                            return a.first->rotation < b.first->rotation;
                        return a.first->id < b.first->id;
                    });
                    adj_count += pieces[i].adj[j][k].size();
                }
            }
            if(!adj_count) {
                possible = false;
                break;
            }
        }

        board[0][0] = &pieces[0];
        pieces[0].used = true;
        
        if(possible)
            bruteforce(board, colors, 0, 0, r, c);
        
        if(solved) {
            print_board(board, r, c);
        } else
            cout << "impossible puzzle!" << endl;
    }

    return 0;
}