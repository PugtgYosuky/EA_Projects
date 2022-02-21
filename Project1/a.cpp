#include <bits/stdc++.h>

using namespace std;

struct piece {
    
    vector<int> values;

    piece() {
        values = vector<int>();
    }

    piece(int a, int b, int c, int d) {
        values = vector<int>{a, b, c, d};
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

void print_board(vector<vector<piece>>& board, int r, int c) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(board[i][j].values.size() == 0)
                cout << "_ _";
            else
                cout << board[i][j].values[0] << " " << board[i][j].values[1];
            if(j < c - 1)
                cout << "  ";
        }
        cout << endl;
        for(int j = 0; j < c; j++) {
            if(board[i][j].values.size() == 0)
                cout << "_ _";
            else
                cout << board[i][j].values[3] << " " << board[i][j].values[2];
            if(j < c - 1)
                cout << "  ";
        }
        cout << endl;
        if(i < r - 1)
            cout << endl;
    }
}

bool solved = false;

void bruteforce(vector<vector<piece>>& board, int x, int y, vector<pair<piece, bool>>& pieces, int r, int c, int direction) {
    // direction 0: esquerda
    // direction 1: direita
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

    for(size_t i = 1; i < pieces.size(); i++) {
        if(pieces[i].second) {
            for(int j = 0; j < 4; j++) { //!!!!!!!!!!!!!!!!!!ISTO ESTAVA MAL!!!!!!!!!!!!!!!!!!
                if(pieces[i].first.match(board[max(nextX-1, 0)][nextY], 2) &&
                    pieces[i].first.match(board[nextX][max(nextY - 1, 0)], 0) &&
                    pieces[i].first.match(board[nextX][min(nextY + 1, c- 1)], 1)) {
                    
                    pieces[i].second = false;
                    board[nextX][nextY] = pieces[i].first;
                    bruteforce(board, nextX, nextY, pieces, r, c, direction);
                    if(solved)
                        return;
                    board[nextX][nextY] = piece();
                    pieces[i].second = true;
                }
                pieces[i].first.rotate();
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

        vector<pair<piece, bool>> pieces(n);

        vector<vector<piece>> board(r, vector<piece>(c));

        for(int i = 0; i < n; i++) {
            cin >> w >> x >> y >> z;

            pieces[i] = make_pair(piece(w, x, y, z), true);
        }

        board[0][0] = pieces[0].first;
        pieces[0].second = false;

        bruteforce(board, 0, 0, pieces, r, c, 0);
        
        if(solved) {
            print_board(board, r, c);
        } else
            cout << "impossible puzzle!" << endl;
    }

    return 0;
}
