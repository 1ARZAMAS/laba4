/*Отделите графически все корни уравнения.
1. Составьте методику решения нелинейного уравнения для метода
половинного деления, метода Ньютона, метода простых итераций.
2. Составьте программу уточнения корня методом половинного деления с
точностью до ε, выводящую результаты в таблицу:
N an bn bn – an
… … … …
где an bn – концы вложенных отрезков.
3. Составьте программу уточнения корня методом Ньютона и методом
простых итераций с точностью до ε, выводящую результаты в таблицу:
*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

float f(float x) {
    return x*x - 3* sin(x);
}

float df(float x) {
    return 2 * x - 3 * cos(x);
}

float g(float x) {
    return 0;
}

void printTable(float leftEdge, float RightPoint, int iteration) {

}

vector <float> graphMethod(float& leftEdge, float& rightEdge) { // графический метод нахождения корней
    vector<float> roots;
    float step = 0.01;
    float x = leftEdge;
    while (x < rightEdge) {
        float y1 = f(x);
        float y2 = f(x + step);
        if ((y1 > 0 && y2 < 0) or (y1 < 0 && y2 > 0)) {
            float root = (x + x + step) / 2;
            roots.push_back(root);
        }
        x += step;
    }
    return roots;
}

float bisectionMethod(float& leftEdge, float& rightEdge, float eps) { // метод половинного деления
    int iteration = 1;
    double middlePoint = 0.0;
    if (f(leftEdge) * f(rightEdge) < 0) { // проверка на разность знаков функции на концах отрезка
        while (abs(rightEdge - leftEdge) > eps) { // пока интервал больше погрешности
            middlePoint = (rightEdge + leftEdge) / 2;
            printTable(leftEdge, rightEdge, iteration);

            if (f(leftEdge) * f(middlePoint) < 0) {
                rightEdge = middlePoint; // если функция имеет разные знаки, то правая точка середина отрезка
            } else {
                leftEdge = middlePoint;
            }
            iteration++;
        }
    }
    return middlePoint;
}


int main() { // x*x - 3* sin(x)
    float leftEdge = -0.5, rightEdge = 3;
    vector<float> roots = graphMethod(leftEdge, rightEdge); // корни в векторе
    float eps = 0.0001;
    float mid = bisectionMethod(leftEdge, rightEdge, eps);
}
