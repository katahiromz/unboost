#define UNBOOST_USE_THREAD
#define UNBOOST_USE_MUTEX
#include <unboost.hpp>

void thread_proc0(void) {
    std::cout << "in thread_proc #" << unboost::this_thread::get_id() << std::endl;
}

void thread_proc1(int n) {
    std::cout << "in thread_proc #" << unboost::this_thread::get_id() << std::endl;
    std::cout << "n: " << n << std::endl;
}

void thread_proc2(int n, int m) {
    std::cout << "in thread_proc #" << unboost::this_thread::get_id() << std::endl;
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
}

int n = 0;
unboost::timed_mutex my_mutex;
unboost::chrono::milliseconds interval1(100);
unboost::chrono::milliseconds interval2(200);
void mutex_test_thread_proc1(void) {
    for (int i = 0; i < 20; ++i) {
        my_mutex.lock();
        unboost::this_thread::sleep_for(interval1);
        ++n;
        std::cout << "mutex_test_thread_proc1: " << n << std::endl;
        my_mutex.unlock();
    }
}

void mutex_test_thread_proc2(void) {
    for (int i = 0; i < 20; ++i) {
        my_mutex.lock();
        unboost::this_thread::sleep_for(interval2);
        ++n;
        std::cout << "mutex_test_thread_proc2: " << n << std::endl;
        my_mutex.unlock();
    }
}

int main(void) {
    unboost::chrono::milliseconds dura(2000);
    std::cout << "thread" << std::endl;
    unboost::thread t0(thread_proc0);
    t0.join();

    std::cout << "sleep 2 seconds" << std::endl;
    unboost::this_thread::sleep_for(dura);
    unboost::thread t1(thread_proc1, 2);
    t1.join();

    std::cout << "sleep 2 seconds" << std::endl;
    unboost::this_thread::sleep_for(dura);
    unboost::thread t2(thread_proc2, 2, 3);
    t2.join();

    std::cout << "sleep 4 seconds" << std::endl;
    unboost_auto_duration s = unboost::chrono::seconds(2) * 2;
    unboost::this_thread::sleep_for(s);
    std::cout << "OK" << std::endl;

    unboost::thread thread1(mutex_test_thread_proc1);
    unboost::thread thread2(mutex_test_thread_proc2);
    thread1.detach();
    thread2.detach();
    unboost::this_thread::sleep_for(unboost::chrono::seconds(10));

    return 0;
}
