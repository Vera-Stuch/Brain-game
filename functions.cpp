#include "functions.h"
#include <windows.h>
int flipCount = 0;
// Звуки
void playMatchSound() {
    Beep(800, 200);
}
void playNoMatchSound() {
    Beep(300, 200); // низкий тон
}

// Создание игрового поля
vector<vector<char>> createBoard(int pairs) {
    int size = pairs * 2;
    vector<char> cards(size);

    for (int i = 0; i < pairs; ++i) {
        cards[i] = 'A' + i % 26;
        cards[i + pairs] = 'A' + i % 26;
    }

    srand((unsigned int)time(nullptr));
    for (int i = 0; i < size; ++i) {
        int j = rand() % size;
        swap(cards[i], cards[j]);
    }

    int cols = static_cast<int>(sqrt(size));
    int rows = (size + cols - 1) / cols;

    vector<vector<char>> board(rows, vector<char>(cols));
    for (int r = 0, idx = 0; r < rows && idx < size; ++r) {
        for (int c = 0; c < cols && idx < size; ++c, ++idx) {
            board[r][c] = cards[idx];
        }
    }

    return board;
}

// Вывод доски
void printBoard(const vector<vector<char>>& board, const vector<vector<bool>>& revealed) {
    int rows = board.size();
    int cols = board[0].size();

    cout << "\n";
    cout << "   ";
    for (int c = 0; c < cols; ++c)
        cout << c << " ";
    cout << "\n";

    for (int r = 0; r < rows; ++r) {
        cout << r << ": ";
        for (int c = 0; c < cols; ++c) {
            if (revealed[r][c])
                cout << board[r][c] << " ";
            else
                cout << HIDDEN_SYMBOL << " ";
        }
        cout << "\n";
    }
}

// Получить координаты карты
void getCardCoords(int& row, int& col,
    const vector<vector<bool>>& revealed,
    const vector<vector<char>>& board,
    const string& prompt,
    int prevRow, int prevCol) {
    int rows = board.size();
    int cols = board[0].size();

    while (true) {
        cout << prompt;
        cin >> row >> col;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода. Повторите." << endl;
            continue;
        }

        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            if (!revealed[row][col]) {
                if (row != prevRow || col != prevCol) {
                    break;
                }
                else {
                    cout << "Нельзя выбирать одну и ту же карту дважды. Повторите ввод." << endl;
                }
            }
            else {
                cout << "Карта уже открыта. Выберите другую." << endl;
            }
        }
        else {
            cout << "Неверные координаты. Повторите ввод." << endl;
        }
    }
}

// Основная логика игры
void playGame(int pairs, int playerCount) {
    vector<vector<char>> board = createBoard(pairs);
    int rows = board.size();
    int cols = board[0].size();
    int totalMatches = pairs * 2;

    vector<vector<bool>> revealed(rows, vector<bool>(cols, false));
    vector<int> scores(playerCount, 0);

    time_t startTime = time(nullptr);
    int matched = 0;
    int currentPlayer = 0;

    while (matched < totalMatches) {
        system("cls");
        cout << "Ход игрока " << currentPlayer + 1 << endl;
        printBoard(board, revealed);

        int r1, c1, r2, c2;

        getCardCoords(r1, c1, revealed, board, "Введите первую карту (строка столбец): ");
        getCardCoords(r2, c2, revealed, board, "Введите вторую карту (строка столбец): ", r1, c1);

        revealed[r1][c1] = true;
        revealed[r2][c2] = true;
        flipCount += 2;
        system("cls");
        cout << "Ход игрока " << currentPlayer + 1 << endl;
        printBoard(board, revealed);

        if (board[r1][c1] == board[r2][c2]) {
            playMatchSound();
            matched += 2;
            scores[currentPlayer]++;
            cout << "\nПара найдена! Игрок " << currentPlayer + 1 << " ходит снова!" << endl;
            Sleep(1000);
        }
        else {
            playNoMatchSound();
            cout << "\nНе совпадает! Ход переходит следующему игроку." << endl;
            Sleep(1500);
            revealed[r1][c1] = false;
            revealed[r2][c2] = false;
            currentPlayer = (currentPlayer + 1) % playerCount;
        }

        Sleep(700);
    }

    time_t endTime = time(nullptr);
    double duration = difftime(endTime, startTime);

    system("cls");
    cout << "Игра окончена!\n\n";
    cout << "Результаты:" << endl;
    for (int i = 0; i < playerCount; ++i) {
        cout << "Игрок " << i + 1 << ": " << scores[i] << " пар(а/ы)" << endl;
    }
    cout << "\nВремя игры: " << static_cast<int>(duration) << " секунд" << endl;
    cout << "Число переворотов карт: " << flipCount << "\n";
}
