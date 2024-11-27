#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

struct Student {
    string name;
    int course;
    int debt;
};

// Глобальная очередь индексов студентов и необходимые примитивы синхронизации
mutex mtx; // Мьютекс для доступа к очереди
condition_variable cv; // Условная переменная для ожидания наличия задач

string nameGenerator() {
    vector<string> surnames = {"Иванов", "Смирнов", "Кузнецов", "Попов", "Васильев", "Петров", "Соколов", "Михайлов", "Новиков",
    "Фёдоров", "Морозов", "Волков", "Алексеев", "Лебедев", "Семёнов", "Егоров", "Павлов", "Козлов", "Степанов", "Николаев",
    "Орлов", "Андреев", "Макаров", "Никитин", "Захаров"};
    vector<string> names = {"Александр", "Данила", "Алексей", "Кирилл", "Сергей", "Никита", "Андрей", "Артём", "Дмитрий",
    "Иван", "Михаил", "Пётр", "Павел", "Егор", "Илья", "Матвей", "Константин", "Максим", "Виктор", "Григорий"};
    string result = surnames[rand() % surnames.size()] + " " + names[rand() % names.size()];
    return result;
}

void process_student(const vector<Student>& students, vector<string>& to_expel, int course, int debtsAmount, int start, int end) {
    vector<string> local_result;
    for (int i = start; i < end; ++i) {
        if (students[i].debt > debtsAmount && students[i].course > course) {
            local_result.push_back(students[i].name);
        }
    }
    
    // Блокируем доступ к общему вектору to_expel
    lock_guard<mutex> lock(mtx);
    to_expel.insert(to_expel.end(), local_result.begin(), local_result.end());
}

int main() {
    int studentsAmount;
    int threadsAmount;
    int course;
    int debtsAmount;
    cout << "Enter amount of students: ";
    cin >> studentsAmount;
    cout << "Enter amount of threads: ";
    cin >> threadsAmount;
    cout << "Enter course: ";
    cin >> course;
    cout << "Enter amount of debts: ";
    cin >> debtsAmount;

    vector<Student> students;
    for (int i = 0; i < studentsAmount; i++) {
        students.push_back({nameGenerator(), rand() % 5 + 1, rand() % 11});
    }

    vector<string> to_expel;  // вектор студентов на отчисление

    // запуск с многозадачностью
    auto start = chrono::high_resolution_clock::now();

    vector<thread> threads;
    int size_thread = students.size() / threadsAmount;
    for (int i = 0; i < threadsAmount; ++i) { 
        int start = i * size_thread;
        int end = (i == threadsAmount - 1) ? students.size() : (i + 1) * size_thread;
        threads.push_back(thread(process_student, cref(students), ref(to_expel), course, debtsAmount, start, end));
    }
    
    for (auto& t : threads) { // ждем завершения всех потоков
        t.join();
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "With multithreads, time taken: " << duration.count() << " ms" << endl;

    threads.clear();

    // запуск без многозадачности
    auto startAgain = chrono::high_resolution_clock::now();
    
    // запускаем один поток для выполнения задачи
    int beginning = 0;
    int ending = students.size();
    thread single_thread(process_student, cref(students), ref(to_expel), course, debtsAmount, beginning, ending);
    single_thread.join(); // ждем завершения потока

    auto endAgain = chrono::high_resolution_clock::now();
    auto durationAgain = chrono::duration_cast<chrono::microseconds>(endAgain - startAgain);
    cout << "Without multithreads, time taken: " << durationAgain.count() << " ms" << endl;

    // Вывод студентов на отчисление
    // cout << "Students to expel:" << endl;
    // for (const auto& name : to_expel) {
    //     cout << name << endl;
    // }

    return 0;
}