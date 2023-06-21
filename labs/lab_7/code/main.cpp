#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <queue>

using namespace std;

mutex barber_mutex;
mutex queue_mutex;
condition_variable queue_cv;
queue<int> waiting_queue;
int max_waiting_clients = 5;
bool barber_sleeping = true;
bool shop_open = true;

void barber() {
    while (shop_open) {
        unique_lock<mutex> lock(barber_mutex);
        if (waiting_queue.empty()) {
            // Если нет клиентов в очереди, то брадобрей засыпает
            barber_sleeping = true;
            cout << "Barber is sleeping" << endl;
            queue_cv.wait(lock);
        } else {
            // Брадобрей бреет клиента
            barber_sleeping = false;
            int client = waiting_queue.front();
            waiting_queue.pop();
            cout << "Barber is shaving client " << client << endl;
            lock.unlock();
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void client(int id) {
    unique_lock<mutex> lock(queue_mutex);
    if (waiting_queue.size() >= max_waiting_clients) {
        // Если очередь полная, клиент уходит
        cout << "Client " << id << " leaves because the shop is full" << endl;
        return;
    }
    // Клиент ждет, пока брадобрей не освободит кресло
    waiting_queue.push(id);
    cout << "Client " << id << " sits in the waiting room" << endl;
    queue_cv.notify_one();
    lock.unlock();

    unique_lock<mutex> barber_lock(barber_mutex);
    if (barber_sleeping) {
        // Если брадобрей спит, клиент будит его
        cout << "Client " << id << " wakes up the barber" << endl;
        queue_cv.notify_one();
    }
    barber_lock.unlock();
}

int main() {
    thread barber_thread(barber);
    thread client_threads[10];

    // Создаем потоки для каждого клиента
    for(int i=0; i<10; i++) {
        client_threads[i] = thread(client, i);
        this_thread::sleep_for(chrono::seconds(1));
    }

    // Ожидаем завершения работы всех потоков
    for(int i=0; i<10; i++) {
        client_threads[i].join();
    }
    shop_open = false;
    barber_thread.join();

    return 0;
}
