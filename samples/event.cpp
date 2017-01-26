// emplace.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

// Unboost only
#include <unboost/thread.hpp>
#include <unboost/event.h>

#include <iostream>
#include <cassert>

unboost::event ev;

void thread_func1(void) {
    ev.create();
    std::cout << "wait for event" << std::endl;
    ev.wait_for_event();
    ev.reset();

    for (size_t i = 0; i < 10; ++i) {
        unboost::chrono::milliseconds msec(100);
        unboost::this_thread::sleep_for(msec);
        std::cout << i << std::endl;
    }
}
void thread_func2(void) {
    unboost::chrono::seconds sec5(5);
    unboost::this_thread::sleep_for(sec5);
    ev.set();
}

int main(void) {
    unboost::thread thread1(thread_func1);
    unboost::thread thread2(thread_func2);

    thread1.detach();
    thread2.detach();

    unboost::chrono::seconds sec10(10);
    unboost::this_thread::sleep_for(sec10);

    std::cout << "success" << std::endl;

    return 0;
}
