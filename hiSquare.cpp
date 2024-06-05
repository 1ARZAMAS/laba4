#include <iostream>
#include <random>
#include <vector>
#include <math.h>

using namespace std;

float realMathExpected(vector<int> vec) { // реальное математическое ожидание
    int sum = 0;
    for (int i : vec) {
        sum += i;
    }
    return sum / vec.size();
}

int CountEl(const vector<int>& vec, int element) {
    int count = 0;
    for (const int& el : vec) {
        if (el == element) count++;
    }
    return count;
}

double Laplas(double i) {
    return 0.5 * (1.0 + erf(i / sqrt(2.0)));
}

double Dispersion(const vector<int>& vec) {
    double mathReal = realMathExpected(vec);
    double sum = 0.0;
    for (int value : vec) {
        sum += pow(value - mathReal, 2);
    }
    return sum / (vec.size() - 1);
}

float hiSquare(vector<int> vec, float expected) { // хи квадрат
    int size = vec.size();
    float hi = 0.0;
    float Vn = realMathExpected(vec);
    double Dispers = sqrt(Dispersion(vec));

    for (int i = 1; i <= 125; i++) {//разность между наблюдаемой и ожидаемой частотой, возводится в квадрат и делится на ожидаемую частоту
        double realIncidence = CountEl(vec, i); // считаем количество элементов
        double expIncidence = vec.size() * (Laplas((i - Vn) / Dispers) - Laplas((i - 1 - Vn) / Dispers));
        hi += pow(realIncidence - expIncidence, 2) / expIncidence; //значение хи-квадрат суммируется на каждом элементе
    }
    return hi;
}

int main() {
    system("chcp 65001");
    minstd_rand gen(std::random_device{}());
    uniform_int_distribution<> dis(1, 100);

    int mas1 = 50, mas2 = 100, mas3 = 1000;
    vector<int> first50(mas1);
    for (int& num : first50) {
        num = dis(gen);
    }

    float expected = 50.5;
    float criticalValue =  66.339; // Критическое значение критерия хи-квадрат
    cout << "Хи-квадрат: " << hiSquare(first50, expected) << endl;
    if (hiSquare(first50, expected) <= criticalValue){
        cout << "Гипотеза о нормальном распределении выборки верна" << endl;
    } else {
        cout << "Гипотеза о нормальном распределении выборки не верна" << endl;
    }
    cout << "Ожидаемое математическое ожидание для массива из 50 символов: " << expected << endl;
    cout << "Реальное математическое ожидание для массива из 50 символов: " << realMathExpected(first50) << endl << endl;
    

    vector<int> second100(mas2);
    for (int& num : second100) {
        num = dis(gen);
    }

    criticalValue = 124.342; // Значение критерия хи-квадрат
    cout << "Хи-квадрат: " << hiSquare(second100, expected) << endl;
    if (hiSquare(second100, expected) <= criticalValue){
        cout << "Гипотеза о нормальном распределении выборки верна" << endl;
    } else {
        cout << "Гипотеза о нормальном распределении выборки не верна" << endl;
    }
    cout << "Ожидаемое математическое ожидание для массива из 100 символов: " << expected << endl;
    cout << "Реальное математическое ожидание для массива из 100 символов: " << realMathExpected(second100) << endl << endl;

    vector<int> third1000(mas3);
    for (int& num : third1000) {
        num = dis(gen);
    }

    criticalValue = 1107.148; // Значение критерия хи-квадрат
    cout << "Хи-квадрат: " << hiSquare(third1000, expected) << endl;
    if (hiSquare(third1000, expected) <= criticalValue){
        cout << "Гипотеза о нормальном распределении выборки верна" << endl;
    } else {
        cout << "Гипотеза о нормальном распределении выборки не верна" << endl;
    }
    cout << "Ожидаемое математическое ожидание для массива из 1000 символов: " << expected << endl;
    cout << "Реальное математическое ожидание для массива из 1000 символов: " << realMathExpected(third1000) << endl;

}
