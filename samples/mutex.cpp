// mutex.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_THREAD
#define UNBOOST_USE_MUTEX
#include <unboost.hpp>

bool checked = false;

//////////////////////////////////////////////////////////////////////////////

void thread_proc0(void) {
    checked = true;
    std::cout << "in thread_proc #" << unboost::this_thread::get_id() << std::endl;
}

void thread_proc1(int n) {
    checked = true;
    std::cout << "in thread_proc #" << unboost::this_thread::get_id() << std::endl;
    assert(n == 2);
}

void thread_proc2(int n, int m) {
    checked = true;
    std::cout << "in thread_proc #" << unboost::this_thread::get_id() << std::endl;
    assert(n == 2);
    assert(m == 3);
}

//////////////////////////////////////////////////////////////////////////////

int n = 0;
unboost::timed_mutex my_mutex;
unboost::chrono::milliseconds interval1(100);
unboost::chrono::milliseconds interval2(200);

void mutex_test_thread_proc1(void) {
    checked = true;
    for (int i = 0; i < 20; ++i) {
        my_mutex.lock();
        unboost::this_thread::sleep_for(interval1);
        ++n;
        std::cout << "mutex_test_thread_proc1: " << n << std::endl;
        my_mutex.unlock();
    }
}

void mutex_test_thread_proc2(void) {
    checked = true;
    for (int i = 0; i < 20; ++i) {
        my_mutex.lock();
        unboost::this_thread::sleep_for(interval2);
        ++n;
        std::cout << "mutex_test_thread_proc2: " << n << std::endl;
        my_mutex.unlock();
    }
}

//////////////////////////////////////////////////////////////////////////////

int main(void) {
    unboost::chrono::milliseconds dura(2000);
    std::cout << "thread" << std::endl;
    checked = false;
    unboost::thread t0(thread_proc0);
    t0.join();
    assert(checked);

    std::cout << "sleep 2 seconds" << std::endl;
    unboost::this_thread::sleep_for(dura);
    checked = false;
    unboost::thread t1(thread_proc1, 2);
    t1.join();
    assert(checked);

    std::cout << "sleep 2 seconds" << std::endl;
    unboost::this_thread::sleep_for(dura);
    checked = false;
    unboost::thread t2(thread_proc2, 2, 3);
    t2.join();
    assert(checked);

    std::cout << "sleep 4 seconds" << std::endl;
    unboost_auto_duration s = unboost::chrono::seconds(2) * 2;
    unboost::this_thread::sleep_for(s);
    std::cout << "OK" << std::endl;

    checked = false;
    unboost::thread thread1(mutex_test_thread_proc1);
    unboost::thread thread2(mutex_test_thread_proc2);
    thread1.detach();
    thread2.detach();
    unboost::this_thread::sleep_for(unboost::chrono::seconds(10));
    assert(checked);

    std::cout << "success" << std::endl;

    return 0;
}
