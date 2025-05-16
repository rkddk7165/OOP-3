#include <iostream>
#include <string>
using namespace std;

struct Node {
    int value;
    Node* up;
    Node* down;
    Node* left;
    Node* right;
    Node(int v) : value(v), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
};

class Board {
public:
    int N;
    Node* nodes[100][100];

    Board(int n) : N(n) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int v;
                cin >> v;
                nodes[i][j] = new Node(v);
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                nodes[i][j]->up = nodes[(i - 1 + N) % N][j];
                nodes[i][j]->down = nodes[(i + 1) % N][j];
                nodes[i][j]->right = nodes[i][(j + 1) % N];
                nodes[i][j]->left = nodes[i][(j - 1 + N) % N];
            }
        }
    }
    ~Board() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                delete nodes[i][j];
            }
        }
    }

    void shift_row(int row_idx, char direction) {
        
        if (direction == 'R') {
            int tmp = nodes[row_idx][N - 1]->value;

            for (int i = N - 1; i > 0; i--) {
                nodes[row_idx][i]->value = nodes[row_idx][i - 1]->value;
            }

            nodes[row_idx][0]->value = tmp;
        }
        else if (direction == 'L') {
            int tmp = nodes[row_idx][0]->value;

            for (int i = 0; i < N - 1; i++) {
                nodes[row_idx][i]->value = nodes[row_idx][i + 1]->value;
            }

            nodes[row_idx][N - 1]->value = tmp;
        }
    }

    void shift_col(int col_idx, char direction) {
        if (direction == 'D') {
            int tmp = nodes[N - 1][col_idx]->value;

            for (int i = N - 1; i > 0; i--) {
                nodes[i][col_idx]->value = nodes[i - 1][col_idx]->value;
            }

            nodes[0][col_idx]->value = tmp;
        }
        else if (direction == 'U') {
            int tmp = nodes[0][col_idx]->value;

            for (int i = 0; i < N - 1; i++) {
                nodes[i][col_idx]->value = nodes[i + 1][col_idx]->value;
            }

            nodes[N - 1][col_idx]->value = tmp;
        }
    }

    void print_board() {
    
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << nodes[i][j]->value << " ";
            }
            cout << endl;
        }
    }

    // DO NOT MODIFY print_node FUNCTION
    void print_node(int r, int c) {
        Node* target = nodes[r][c];
        cout << target->value << " "
            << target->up->value << " "
            << target->down->value << " "
            << target->left->value << " "
            << target->right->value << " " << endl;
    }
};

// DO NOT MODIFY MAIN FUNCTION
int main() {
    int N;
    cin >> N;
    Board board(N);

    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        string cmd;
        cin >> cmd;
        if (cmd == "R") {
            int r;
            char dir;
            cin >> r >> dir;
            board.shift_row(r, dir);
        }
        else if (cmd == "C") {
            int c;
            char dir;
            cin >> c >> dir;
            board.shift_col(c, dir);
        }
        else if (cmd == "print_board") {
            board.print_board();
        }
        else if (cmd == "print_node") {
            int r, c;
            cin >> r >> c;
            board.print_node(r, c);
        }
    }

    return 0;
}