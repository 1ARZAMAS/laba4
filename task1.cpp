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

/*ostream& operator<<(ostream& os, const vector<float>& vec){
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
            os << ", ";
    }
    return os;
}
*/

float f(float x){
    return 2 * log(x) - 1/2 * x + 1;
}

float df(float x){
    return 2/x - 1/2;
}

float g(float x){
    return 0;
}

ostream& operator<< (ostream& os, const vector <float>& roots) {
    for (size_t i = 0; i < roots.size(); ++i){
        os << roots[i] << ' ';
    }
    return os;
}

vector <float> graphMethod(float& leftEdge, float& rightEdge, float& x0){ // графический метод нахождения корней
    vector <float> roots1;
    for (float i = 0; i < 13.0; i+=0.01){
        if ((f(i) > 0 and f(i + 0.01) < 0) or (f(i) < 0 and f(i + 0.01) > 0)){
            cout << i << endl;
            float rt = (2*i + 0.01)/2;
            roots1.push_back(rt);
        }
    }
    return roots1;
}

int main(){ // 2 * ln(x) - 0.5 * x + 1 = 0 
    float leftEdge = 0, rightEdge = 0, x0 = 0;
    vector<float> roots = graphMethod(leftEdge, rightEdge, x0);
    
    std::cout << roots;
}
