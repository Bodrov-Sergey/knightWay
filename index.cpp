#include <iostream>

using namespace std;

struct Quadr {
    int x, y;
    Quadr(int x, int y) { this->x = x; this->y = y; }
    void show_square_info() { cout << "(" << x << ", " << y << ")" << endl; }
    bool square_occupied(int **board) {
        if (board[x][y] == 1) return true;
        return false;
    }
    bool in_board(int board_size) {
        if (x < board_size && x >= 0 && y < board_size && y >= 0) return true;
        return false;
    }
    Quadr operator+(Quadr& other_square) { Quadr p(*this); p.x += other_square.x; p.y += other_square.y; return p; }
    bool operator==(Quadr& other_square) {
        if (x == other_square.x && y == other_square.y) return true;
        return false;
    }
};

Quadr knight_moves[8] = { Quadr(1, 2), Quadr(-1, 2), Quadr(2, 1), Quadr(-2, 1), Quadr(1, -2), Quadr(-1, -2), Quadr(2, -1), Quadr(-2, -1)};

void print_board(Quadr k, int board_size, int **board) {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (Quadr(i, j) == k) cout << "♞ ";
            else if (board[i][j] == 1) cout << "* ";
            else cout << "[]";
        }
        cout << endl;
    }
}

int moves_count = 0;
bool passed = false;
void move_knight(Quadr last_move, int board_size, int **board, int move_number = 1) {
    for (int i = 0; i < 8; i++) {
        Quadr move_here = last_move + knight_moves[i];
        moves_count++;
        if (move_here.in_board(board_size) && !move_here.square_occupied(board)) {
            board[move_here.x][move_here.y] = 1;
            move_knight(move_here, board_size, board, move_number+1);
            if (passed || move_number == board_size*board_size - 1) {
                passed = true;
                print_board(move_here, board_size, board);
                board[move_here.x][move_here.y] = 0;
                cout << "Номер хода: " << move_number << "\n\n";
                break;
            }
            board[move_here.x][move_here.y] = 0;
        }
    }
}

int main() {
    int board_size;
    while (1) {
        cout << "Введите размерность шахматной доски: "; cin >> board_size;
        if (board_size <= 3) cout << "Конь не может обойти доску такой размерности.\n\n";
        else break;
    }
    cout << endl; int start_x, start_y;
    cout << "Стартовые координаты фигуры.\n\n";
    while (1) {
        cout << "x: "; cin >> start_x;
        if (0 <= start_x <= board_size-1) break;
        else cout << "Данная клетка вне диапазона доски.\n";
    }
    while (1) {
        cout << "Введите координату y: "; cin >> start_y;
        if (0 <= start_y <= board_size-1) break;
        else cout << "Данная клетка вне диапазона доски.\n";
    }
    cout << endl; int **board = new int *[board_size];
    for (int i = 0; i < board_size; i++) { board[i] = new int[board_size]; }
    for (int i = 0; i < board_size; i++) { for (int j = 0; j < board_size; j++) { board[i][j] = 0; } }
    board[start_x][start_y] = 1;
    cout << "Ходы:\n\n";
    move_knight(Quadr(start_x, start_y), board_size, board);
    cout << "Всего ходов: " << moves_count << endl;
    return 0;
}