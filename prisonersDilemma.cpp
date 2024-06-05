#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdint>

using namespace std;

// Алгоритм 1: всегда сотрудничает
bool algorithm1(int32_t round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    return true;
}

// Алгоритм 2: всегда предает
bool algorithm2(int32_t round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    return false;
}

// Алгоритм 3: предает, если противник предавал в предыдущем раунде, иначе сотрудничает
bool algorithm3(int32_t round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    if (round_number == 0) {
        return true;
    }
    return !enemy_choices[round_number - 1];
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Генерация случайного количества раундов
    int32_t num_rounds = rand() % 101 + 100;

    // Инициализация счетчиков очков для каждого алгоритма
    int32_t score1 = 0, score2 = 0, score3 = 0;

    // Массивы для хранения выборов каждого алгоритма
    vector<bool> choices1(num_rounds), choices2(num_rounds), choices3(num_rounds);

    for (int32_t round = 0; round < num_rounds; ++round) {
        // Вызов алгоритмов для получения их выборов
        bool choice1 = algorithm1(round, choices1, choices2);
        bool choice2 = algorithm2(round, choices2, choices1);
        bool choice3 = algorithm3(round, choices3, choices2);

        // Обновление счетчиков очков
        if (choice1 && choice2) {
            score1 += 24;
            score2 += 24;
        } else if (choice1 && !choice2) {
            score2 += 20;
        } else if (!choice1 && choice2) {
            score1 += 20;
        } else {
            score1 += 4;
            score2 += 4;
        }

        if (choice1 && choice3) {
            score1 += 24;
            score3 += 24;
        } else if (choice1 && !choice3) {
            score3 += 20;
        } else if (!choice1 && choice3) {
            score1 += 20;
        } else {
            score1 += 4;
            score3 += 4;
        }

        if (choice2 && choice3) {
            score2 += 24;
            score3 += 24;
        } else if (choice2 && !choice3) {
            score3 += 20;
        } else if (!choice2 && choice3) {
            score2 += 20;
        } else {
            score2 += 4;
            score3 += 4;
        }

        // Сохранение выборов для каждого алгоритма
        choices1[round] = choice1;
        choices2[round] = choice2;
        choices3[round] = choice3;
    }

    // Вывод результатов
    cout << "Количество раундов: " << num_rounds << endl;
    cout << "Всегда сотрудничаем: " << score1 << endl;
    cout << "Всегда предаем: " << score2 << endl;
    cout << "Око за око: " << score3 << endl;

    return 0;
}
