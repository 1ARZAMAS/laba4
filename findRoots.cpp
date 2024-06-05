#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;

float f(float x) {
    return x*x - 3* sin(x);
}

float df(float x) {
    return 2 * x - 3 * cos(x);
}

float g(float x) {
    return 2 + 3 * sin(x);
}

void printTable(int iteration, float leftEdge, float rightEdge) {
    cout << "-----------------------------------" << endl;
    cout << setw(2) << iteration << "|" << setw(10) << leftEdge << setw(10) << rightEdge << setw(10) << rightEdge - leftEdge << endl;
}

vector <float> graphMethod(float leftEdge, float rightEdge) { // графический метод нахождения корней
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

float bisectionMethod(float leftEdge, float rightEdge, float eps, float root) { // метод половинного деления
    int iteration = 1;
    double middlePoint = 0.0;
    if (f(leftEdge) * f(rightEdge) < 0) { // проверка на разность знаков функции на концах отрезка
        while (abs(rightEdge - leftEdge) > eps) { // пока интервал больше погрешности
            middlePoint = (rightEdge + leftEdge) / 2;
            printTable(iteration, leftEdge, rightEdge);
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

void NewtonMethod(float root, float eps) {
    int k = 0;
    int iteration = 1;
    if (f(root) * df(root) > 0) {
        while (true) {
            float root1 = root - (f(root) / df(root));
            printTable(iteration, root1, root);
            if (abs(root1 - root) < eps) {
                break;
            }
            root = root1;
            iteration++;
        }
    }
}

float chordMethod(float leftEdge, float rightEdge, float eps) {
    for (int i = 1; abs(rightEdge - leftEdge) >= eps; i++) {
        leftEdge = leftEdge - (rightEdge - leftEdge) * f(leftEdge) / (f(rightEdge) - f(leftEdge));
        rightEdge = rightEdge - (leftEdge - rightEdge) * f(rightEdge) / (f(leftEdge) - f(rightEdge));
        printTable(i, leftEdge, rightEdge);
    }
    return rightEdge;
}

int main() { 
    setlocale(LC_ALL, "Rus");
    system("chcp 65001");
    float leftEdge = -0.5, rightEdge = 3;
    vector<float> roots = graphMethod(leftEdge, rightEdge); // корни в векторе
    float eps = 0.0001;

    cout << "Результаты методом половинного деления для первого корня:" << endl;
    float root = roots[0];
    leftEdge = root - 1.0, rightEdge = root + 1.0;
    cout << "N" << "\t" << "a" << "\t" << setw(3) << "b" << "\t" << setw(8) << "b - a" << fixed << setprecision(3) << endl;
    bisectionMethod(leftEdge, rightEdge, eps, root);

    cout << "\nРезультаты методом Ньютона для первого корня:" << endl;
    cout << "N" << "\t" << "x(n)" << "\t" << setw(3) << "x(n+1)" << "\t" << setw(8) << "x(n+1) - x(n)" << fixed << setprecision(3) << endl;
    NewtonMethod(root, eps);

    cout << "\nРезультаты методом хорд для первого корня:" << endl;
    cout << "N" << "\t" << "a" << "\t" << setw(3) << "b" << "\t" << setw(8) << "b - a" << fixed << setprecision(3) << endl;
    chordMethod(leftEdge, rightEdge,eps);


    cout << "\nРезультаты методом половинного деления для второго корня:" << endl;
    root = roots[1];
    leftEdge = root - 1.0, rightEdge = root + 1.0;
    cout << "N" << "\t" << "a" << "\t" << setw(3) << "b" << "\t" << setw(8) << "b - a" << fixed << setprecision(3) << endl;
    bisectionMethod(leftEdge, rightEdge, eps, root);

    cout << "\nРезультаты методом Ньютона для второго корня:" << endl;
    root = roots[1];
    cout << "N" << "\t" << "x(k)" << "\t" << setw(3) << "x(k+1)" << "\t" << setw(8) << "x(k+1) - x(k)" << fixed << setprecision(3) << endl;
    NewtonMethod(root, eps);

    cout << "\nРезультаты методом хорд для второго корня:" << endl;
    cout << "N" << "\t" << "a" << "\t" << setw(3) << "b" << "\t" << setw(8) << "b - a" << fixed << setprecision(3) << endl;
    chordMethod(leftEdge, rightEdge, eps);
}
