#include <bits/stdc++.h>

using namespace std;

struct piece {
    
    vector<int> values;
    bool used;
    int id;

    piece() {
        values = vector<int>();
        used = false;
        id = -1;
    }

    piece(int a, int b, int c, int d, int _id) {
        used = false;
        values = vector<int>{a, b, c, d};
        id = _id;
    }

    void rotate() {
        // rotate 90
        vector<int> aux(values);
        for(int i = 1; i < 4; i++)
            values[i] = aux[i-1];
        values[0] = aux[3];
    }

    bool match(piece& other, int option) {
        if(other.values.size() == 0)
            return true;
        switch(option) {
            case 0: // Check if the current left side = other right side
                return values[0] == other.values[1] && values[3] == other.values[2];
            case 1: // Check if the current right side = other left side
                return values[1] == other.values[0] && values[2] == other.values[3];
            case 2: // Check if the current top side = other bottom side
                return values[0] == other.values[3] && values[1] == other.values[2];
            case 3: // Check if the current bottom side = other top side
                return values[3] == other.values[0] && values[2] == other.values[1];
            default:
                return false;
        }
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
            if(board[i][j]->values.size() == 0)
                cout << "_ _";
            else
                cout << board[i][j]->values[0] << " " << board[i][j]->values[1];
            if(j < c - 1)
                cout << "  ";
        }
        cout << endl;
        for(int j = 0; j < c; j++) {
            if(board[i][j]->values.size() == 0)
                cout << "_ _";
            else
                cout << board[i][j]->values[3] << " " << board[i][j]->values[2];
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

void bruteforce(map<piece, vector<piece *>, piece_comparator>& graph, vector<vector<piece*>>& board, int x, int y, int r, int c, int direction) {
    // direction 0: left
    // direction 1: right
    if(solved)
        return;
    if((direction == 0 && x == r - 1 && y == c - 1) || (direction == 1 && x == r - 1 && y == 0)) {
        solved = true;
        return;
    }

    int nextX = x, nextY = y;
    if(direction == 0) {
        nextY++;
        if(nextY >= c) {
            nextX++;
            nextY = c - 1;
            direction = 1;
        }
    } else {
        if(direction == 1) {
            nextY--;
            if(nextY < 0) {
                nextX++;
                nextY = 0;
                direction = 0;
            }
        }
    }

    for(size_t i = 0; i < graph[*board[x][y]].size(); i++) {
        piece * current_piece = graph[*board[x][y]][i];
        if(!current_piece->used) {
            for(int j = 0; j < 4; j++) {
                if(current_piece->match(*board[max(nextX-1, 0)][nextY], 2) &&
                    current_piece->match(*board[nextX][max(nextY - 1, 0)], 0) &&
                    current_piece->match(*board[nextX][min(nextY + 1, c- 1)], 1)) {
                    
                    current_piece->used = true;
                    board[nextX][nextY] = current_piece;
                    bruteforce(graph, board, nextX, nextY, r, c, direction);
                    if(solved)
                        return;
                    board[nextX][nextY] = empty_piece;
                    current_piece->used = false;
                }
                current_piece->rotate();
            }
        }
    }

}

int main() {

    int t, n, r, c, w, x, y, z;
    cin >> t;

    while(t--) {
        solved = false;
        cin >> n >> r >> c;

        vector<piece> pieces(n);
        vector<vector<piece *>> board(r, vector<piece *>(c, empty_piece));
        map<piece, vector<piece *>, piece_comparator> graph;

        for(int i = 0; i < n; i++) {
            cin >> w >> x >> y >> z;
            pieces[i] = piece(w, x, y, z, i);
            graph[pieces[i]] = vector<piece *>();
        }
        
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                for(int k = 0; k < 4; k++){
                    if(pieces[i].match(pieces[j], 0) ||
                        pieces[i].match(pieces[j], 1) ||
                        pieces[i].match(pieces[j], 2) ||
                        pieces[i].match(pieces[j], 3)) {

                        graph[pieces[i]].push_back(&pieces[j]);
                        graph[pieces[j]].push_back(&pieces[i]);
                    }
                    pieces[i].rotate();
                }
            }
        }

        board[0][0] = &pieces[0];
        pieces[0].used = true;

        bruteforce(graph, board, 0, 0, r, c, 0);
        
        if(solved) {
            print_board(board, r, c);
        } else
            cout << "impossible puzzle!" << endl;
    }

    return 0;
}