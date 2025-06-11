#include "functions.h"
#include <conio.h>

int main() {
    setlocale(LC_ALL, "Russian");

    int pairs, players;

    cout << "Добро пожаловать в игру \"Память\"!" << endl;
    cout << "Введите количество пар (до " << MAX_PAIRS << "): ";
    cin >> pairs;

    if (pairs <= 0 || pairs > MAX_PAIRS) {
        cerr << "Неверное количество пар." << endl;
        return 1;
    }

    cout << "Введите количество игроков (минимум 2): ";
    cin >> players;

    if (players < 2) {
        cerr << "Минимальное количество игроков: 2" << endl;
        return 1;
    }

    playGame(pairs, players);

    cout << "\nБлагодарим за то, что выбрали нашу игру:)";
    cout << "\nНажмите любую клавишу для выхода...";
    _getch();

    return 0;
}
