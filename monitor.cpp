/*
Монитор - высокоуровневый механизм синхронизации процессов, 
обеспечивающий доступ к разделяемым ресурсам.При 
многозадачности, основанной на мониторах, компилятор или 
интерпретатор прозрачно для программиста вставляет код блокировки-
разблокировки в оформленные соответствующим образом процедуры,
избавляя программиста от явного обращения к примитивам синхронизации.
Монитор состоит из:
1. набора процедур, взаимодействующих с общим ресурсом
2. мьютекса
3. переменных, связанных с этим ресурсом
4. инварианта, который определяет условия, позволяющие избежать 
состояние гонки
*/

/*
Mutexes - примитив синхронизации, который обеспечивает взаимное исключение
исполнения критических участков кода. В один момент времени мьютексом
может обладать только 1 поток, который его и освобождает
*/

/*
Легковесная версия семафора, для использования в многопоточных 
приложениях, где требуется синхронизация потоков, более 
эффективен по сравнению с обычным, использует меньше ресурсов
*/

#include <iostream>
#include <random>
#include <string>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <condition_variable>

using namespace std;

class Monitor {
public:
    void Acquire(){
        unique_lock<std::mutex> lock(Mutex);
        cv.wait(lock, [this]() {return !is_locked; }); // ждем освобождения
        is_locked = true; // забираем ресурс
    }

    void Release(){
        lock_guard<std::mutex> lock(Mutex);
        is_locked = false; // освобождаем ресурс
        cv.notify_one(); // оповещаем один ожидающий поток
    }
private:
    mutex Mutex; // мьютекс для защиты состояния
    condition_variable cv; // условная переменная для ожидания
    bool is_locked; // флаг блокировки
};

Monitor monitor; // только 1 поток может работать одновременно

void randomChars(int thread_id, int letter_count) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(32, 126);  // ASCII диапазон видимых символов
    string chars;
    monitor.Acquire();
    for (int i = 0; i < letter_count; ++i){
        char letter = static_cast<char>(dis(gen));
        chars += letter;
    }
    cout << "Thread " << thread_id << ": " << chars << endl;  
    monitor.Release();
}

int main(){
    using namespace std::chrono;

    vector<thread> threads;
    auto start = high_resolution_clock::now(); // начало таймера
    
    for (int i = 0; i < 4; ++i) { // Запуск потоков
        threads.push_back(thread(randomChars, i, 10));
    }

    // Ожидание завершения всех потоков
    for (auto& t : threads) {
        t.join();
    }

    auto end = high_resolution_clock::now(); // конец таймера
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken: " << duration.count() << " microseconds\n";
    return 0;
}