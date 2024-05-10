#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    system("chcp 65001");
    // 1. Определение и инициализация массива случайными числами

    minstd_rand gen(std::random_device{}());
    uniform_int_distribution<> dis1(150, 300);

    int n = 10;
    int randNums[n];

    for (int& num : randNums) {
        num = dis1(gen);
    }

    // 2. Поиск и вывод самой длинной последовательности в убывающем порядке
    vector<int> longest;
    int current_length = 1;
    int max_length = 0;
    for (int i = 1; i < n; i++) {
        if (randNums[i] > randNums[i-1]) { // Если текущий элемент больше предыдущего, увеличиваем последовательность
            current_length++;
        } else { // Если предыдущий больше, то выполним проверку
            if (current_length > max_length) { // не больше ли текущая длина максимальной
                max_length = current_length; // если да, то перезаписываем счетчик
                longest = vector<int>(randNums + i - current_length, randNums + i); // и в вектор записываем последовательность
            }
            current_length = 1;
        }
    } // если последовательность находится в конце массива, то при выходе из цикла максимальная длина может не обновиться
    if (current_length > max_length) { // поэтому добавляем это сравнение
        longest = vector<int>(randNums + n - current_length, randNums + n);
    }
    reverse(longest.begin(), longest.end()); // Переворачиваем, так как записывали до этого от меньшего к большему
    cout << "Самая длинная последовательность в убывающем порядке:" << endl;
    for (int num : longest) {
        cout << num << " ";
    }
    cout << endl << endl;

    // 3. Определение и инициализация нового массива меньше среднеарифметического
    int sum = 0;
    for (int i = 0; i < n; i++) { // проходимся по всему массиву и суммируем
        sum += randNums[i];
    }
    double avg = static_cast<double>(sum) / n; // среднее арифметическое

    vector<int> new_arr; // создаем новый массив куда записываем числа, 
    for (int i = 0; i < n; i++) { // меньшие среднего арифметического
        if (randNums[i] < avg) {
            new_arr.push_back(randNums[i]);
        }
    }

    cout << "Новый массив, состоящий из чисел меньше среднеарифметического:"<< endl;
    for (int num : new_arr) {
        cout << num << " ";
    }
    cout << endl << endl;

    // 4. Модификация массива случайных символов
    char symbol_arr[n];
    for (int i = 0; i < n; i++) {
        symbol_arr[i] = 'A' + (rand() % 26);
    }
    cout << "Изначальный массив символов:"<< endl;
    for (int i = 0; i < n; i++) {
        cout << "[" << symbol_arr[i] << "]";
    }
    cout << endl << endl;
    random_shuffle(symbol_arr, symbol_arr + n);
    cout << "Модифицированный массив символов:"<< endl;
    for (int i = 0; i < n; i++) {
        cout << "[" << symbol_arr[i] << "]";
    }
    cout << endl<< endl;

    // 5. Определение и инициализация нового массива случайных чисел, его сортировка и подсчет повторяющихся цифр
    n = 20;
    vector<int> new_numbers_arr(n);
    
    uniform_int_distribution<> dis2(100, 900);
    for (int& num : new_numbers_arr) {
        num = dis2(gen);
    }

    sort(new_numbers_arr.begin(), new_numbers_arr.end(), greater<int>()); // указываем на начало
    cout << "Новый массив случайных чисел в порядке убывания:" << endl; // на конец и пишем функциональный объект
    for (int num : new_numbers_arr) {
        cout << num << " ";
    }
    cout << endl << endl;
    
    vector<int> digit_count(10, 0); // создаем вектор из 10 нулей
    for (int num : new_numbers_arr) { // проходимся по вектору
        while (num > 0) { // и пока у нас число больше нуля
            digit_count[num % 10]++; // в вектор записываем остаток по месту числа
            num /= 10;
        }
    }
    cout << "Количество повторяющихся цифр в новом массиве:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << i << ": " << digit_count[i] << "\t";
    }
    cout << endl << endl;

    return 0;
}
