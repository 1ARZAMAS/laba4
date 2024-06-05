#include <iostream>

using namespace std;

void Input(int& A, int& B, int& X0, int& C){
    cout << "Введите значение C, большее нуля: ";
    cin >> C;
    while (C <= 0){
        cout << "\nДанные введены неправильно, попробуйте еще раз: ";
        cin >> C;
    }

    cout << "Введите значение A, для которого: 0 <= A <= "<< C << ": ";
    cin >> A;
    while (A < 0 or A > C){
        cout << "\nДанные введены неправильно, попробуйте еще раз: ";
        cin >> A;
    }

    cout << "Введите значение B, для которого: 0 <= B <= "<< C << ": ";
    cin >> B;
    while (B < 0 or B > C){
        cout << "\nДанные введены неправильно, попробуйте еще раз: ";
        cin >> B;
    }

    cout << "Введите значение X0, для которого: 0 <= X0 < "<< C << ": ";
    cin >> X0;
    while (X0 < 0 or X0 >= C){
        cout << "\nДанные введены неправильно, попробуйте еще раз: ";
        cin >> X0;
    }
}

void generator(int& A, int& B, int& X0, int& C){
    int X_curr = X0;
    int X_prev;
    int index;
    bool indexFound = false;
    for (int i = 0; i < C; i++){
        cout << X_curr << " ";
        X_prev = X_curr;
        X_curr = (A * X_prev + B) % C;
        if (indexFound == false and X_curr == X0){
            indexFound = true;
            index = i;
        }
    }
    cout << "\nИндекс, с которого повторяется последовательность: " << index;
}

int main(){
    system("chcp 65001");
    int A, B, X0, C;
    Input(A, B, X0, C);
    generator(A, B, X0, C);
}
