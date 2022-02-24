#include <bits/stdc++.h>

using namespace std;

struct piece {
    
    vector<vector<int>> values;
    vector<vector<pair<piece*, int>>> adj;
    bool used;
    int id;
    int rotation; // 0 = top, 1 -> right, 2 -> bottom, 3 -> left

    piece() {
        values = vector<vector<int>>();
        used = false;
        id = -1;
        rotation = 0;
        adj = vector<vector<pair<piece*, int>>> (4);
    }

    piece(int a, int b, int c, int d, int _id) {
        used = false;
        values = vector<vector<int>>(4);
        adj = vector<vector<pair<piece*, int>>> (4);
        values[0] = vector<int>{a, b, c, d};
        values[1] = vector<int>{b, c, d, a};
        values[2] = vector<int>{c, d, a, b};
        values[3] = vector<int>{d, a, b, c};
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

struct piece_comparator {

    bool operator() (const piece& a, const piece& b) const {
        return a.id < b.id;
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


int main() {

    int t, n, r, c, w, x, y, z;
    cin >> t;

    while(t--) {
        solved = false;
        cin >> n >> r >> c;

        vector<piece> pieces(n);
        vector<vector<piece *>> board(r, vector<piece *>(c, empty_piece));

        for(int i = 0; i < n; i++) {
            cin >> w >> x >> y >> z;
            pieces[i] = piece(w, x, y, z, i);
            
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; i++){
                if(i != j) {
                    for(int l = 0; l < 4; l++){ // rotation j
                        if(pieces[i].edge(0, 0) == pieces[j].edge(2, l)) {
                            pieces[i].adj[0].emplace_back(&pieces[j], l);
                        }
                        if(pieces[i].edge(1, 0) == pieces[j].edge(3, l)) {
                            pieces[i].adj[1].emplace_back(&pieces[j], l);
                        }
                        if(pieces[i].edge(2, 0) == pieces[j].edge(0, l)) {
                            pieces[i].adj[2].emplace_back(&pieces[j], l);
                        }
                        if(pieces[i].edge(3, 0) == pieces[j].edge(1, l)) {
                            pieces[i].adj[3].emplace_back(&pieces[j], l);
                        }
                    }
                }
            }
        }

        board[0][0] = &pieces[0];
        pieces[0].used = true;

        
        if(solved) {
            print_board(board, r, c);
        } else
            cout << "impossible puzzle!" << endl;
    }

    return 0;
}
