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

void bruteforce(vector<vector<piece>>& board, int x, int y, list<piece>& pieces, int r, int c, int direction) {
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

    auto it = pieces.begin();
    auto after_it = pieces.begin();
    for(size_t i = 0; i < pieces.size(); i++, it++) {
        after_it++;
        for(int j = 0; j < 4; j++) {
            if((*it).match(board[max(nextX-1, 0)][nextY], 2) &&
                (*it).match(board[nextX][max(nextY - 1, 0)], 0) &&
                (*it).match(board[nextX][min(nextY + 1, c - 1)], 1)) {
                
                board[nextX][nextY] = *it;
                pieces.erase(it);
                bruteforce(board, nextX, nextY, pieces, r, c, direction);
                if(solved)
                    return;
                pieces.insert(after_it, board[nextX][nextY]);
                board[nextX][nextY] = piece();
            }
            (*it).rotate();
        }
    }
}

int main() {

    int t, n, r, c, w, x, y, z;
    cin >> t;

    while(t--) {
        solved = false;
        cin >> n >> r >> c;

        list<piece> pieces;

        vector<vector<piece>> board(r, vector<piece>(c));

        for(int i = 0; i < n; i++) {
            cin >> w >> x >> y >> z;

            pieces.emplace_back(w, x, y, z);
        }

        board[0][0] = *pieces.begin();
        

        bruteforce(board, 0, 0, pieces, r, c, 0);
        pieces.pop_front();
        
        if(solved) {
            print_board(board, r, c);
        } else
            cout << "impossible puzzle!" << endl;
    }

    return 0;
}
