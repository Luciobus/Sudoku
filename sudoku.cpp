#include <iostream>
#include <utility>
#include <vector>

class Sudoku {
public:
    explicit Sudoku(std::vector<std::vector<int>> field) : field_(std::move(field)) {
    }

    void Solve() {
        if (CanBeSolved()) {
            std::cout << "Solution exists\n";
            PrintField();
        } else {
            std::cout << "No solution\n";
        }
    }

    void PrintField() {
        for (int row = 0; row < 9; ++row) {
            if (row == 3 || row == 6) {
                std::cout << std::string(21, '-') << "\n";
            }
            for (int col = 0; col < 9; ++col) {
                if (col == 3 || col == 6) {
                    std::cout << "| ";
                }
                std::cout << field_[row][col] << " ";
            }
            std::cout << "\n";
        }
    }

private:
    std::vector<std::vector<int>> field_;

    bool CanBePlaced(int row, int col, int value) {
        return !IsPresentedInRow(row, value) && !IsPresentedInCol(col, value) &&
               !IsPresentedInSquare(row / 3, col / 3, value);
    }

    bool FindEmpty(int& row, int& col) {
        for (row = 0; row < 9; ++row) {
            for (col = 0; col < 9; ++col) {
                if (!field_[row][col]) {
                    return true;
                }
            }
        }
        return false;
    }

    bool IsPresentedInRow(int row, int value) {
        for (int col = 0; col < 9; ++col) {
            if (field_[row][col] == value) {
                return true;
            }
        }
        return false;
    }

    bool IsPresentedInCol(int col, int value) {
        for (int row = 0; row < 9; ++row) {
            if (field_[row][col] == value) {
                return true;
            }
        }
        return false;
    }

    bool IsPresentedInSquare(int square_row, int square_col, int value) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (field_[square_row * 3 + i][square_col * 3 + j] == value) {
                    return true;
                }
            }
        }
        return false;
    }

    bool CanBeSolved() {
        int row, col;
        if (!FindEmpty(row, col)) {
            return true;
        }
        for (int value = 1; value < 10; ++value) {
            if (CanBePlaced(row, col, value)) {
                field_[row][col] = value;
                if (CanBeSolved()) {
                    return true;
                }
                field_[row][col] = 0;
            }
        }
        return false;
    }
};

Sudoku ReadField() {
    std::vector<std::vector<int>> field(9, std::vector<int>(9));
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            char c;
            std::cin >> c;
            field[row][col] = c == '*' ? 0 : (c - '0');
        }
    }
    return Sudoku(field);
}

int main() {
    std::cout << "Input field\n";
    Sudoku sudoku = ReadField();
    sudoku.Solve();
    return 0;
}
