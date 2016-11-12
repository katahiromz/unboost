// thread.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#ifdef CXX11
    #include <thread>
    #include <mutex>
    #include <functional>       // for std::ref, std::cref, ...
#elif defined(BOOST)
    #include <boost/ref.hpp>    // for boost::ref, boost::cref, ...
    #include <boost/thread.hpp>
#else   // Unboost
    #include <unboost/ref.hpp>  // for unboost::ref, unboost::cref, ...
    #include <unboost/thread.hpp>
#endif

bool checked = false;

//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    void thread_proc0(void) {
        checked = true;
        std::cout << "in thread_proc #" << std::this_thread::get_id() << std::endl;
    }

    void thread_proc1(int n) {
        checked = true;
        std::cout << "in thread_proc #" << std::this_thread::get_id() << std::endl;
        std::cout << "n = " << n << std::endl;
        assert(n == 2);
    }

    void thread_proc2(int n, const int& m) {
        checked = true;
        std::cout << "in thread_proc #" << std::this_thread::get_id() << std::endl;
        std::cout << "n = " << n << ", m = " << m << std::endl;
        assert(n == 2);
        assert(m == 3);
    }
#elif defined(BOOST)
    void thread_proc0(void) {
        checked = true;
        std::cout << "in thread_proc #" << boost::this_thread::get_id() << std::endl;
    }

    void thread_proc1(int n) {
        checked = true;
        std::cout << "in thread_proc #" << boost::this_thread::get_id() << std::endl;
        std::cout << "n = " << n << std::endl;
        assert(n == 2);
    }

    void thread_proc2(int n, const int& m) {
        checked = true;
        std::cout << "in thread_proc #" << boost::this_thread::get_id() << std::endl;
        std::cout << "n = " << n << ", m = " << m << std::endl;
        assert(n == 2);
        assert(m == 3);
    }
#else   // Unboost
    void thread_proc0(void) {
        checked = true;
        std::cout << "in thread_proc #" << unboost::this_thread::get_id() << std::endl;
    }

    void thread_proc1(int n) {
        checked = true;
        std::cout << "in thread_proc #" << unboost::this_thread::get_id() << std::endl;
        std::cout << "n = " << n << std::endl;
        assert(n == 2);
    }

    void thread_proc2(int n, const int& m) {
        checked = true;
        std::cout << "in thread_proc #" << unboost::this_thread::get_id() << std::endl;
        std::cout << "n = " << n << ", m = " << m << std::endl;
        assert(n == 2);
        assert(m == 3);
    }
#endif


//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    int n = 0;
    std::timed_mutex my_mutex;
    std::chrono::milliseconds interval1(100);
    std::chrono::milliseconds interval2(200);

    void mutex_test_thread_proc1(void) {
        checked = true;
        for (int i = 0; i < 20; ++i) {
            my_mutex.lock();
            std::this_thread::sleep_for(interval1);
            ++n;
            std::cout << "mutex_test_thread_proc1: " << n << std::endl;
            my_mutex.unlock();
        }
    }

    void mutex_test_thread_proc2(void) {
        checked = true;
        for (int i = 0; i < 20; ++i) {
            my_mutex.lock();
            std::this_thread::sleep_for(interval2);
            ++n;
            std::cout << "mutex_test_thread_proc2: " << n << std::endl;
            my_mutex.unlock();
        }
    }
#elif defined(BOOST)
    int n = 0;
    boost::timed_mutex my_mutex;
    boost::chrono::milliseconds interval1(100);
    boost::chrono::milliseconds interval2(200);

    void mutex_test_thread_proc1(void) {
        checked = true;
        for (int i = 0; i < 20; ++i) {
            my_mutex.lock();
            boost::this_thread::sleep_for(interval1);
            ++n;
            std::cout << "mutex_test_thread_proc1: " << n << std::endl;
            my_mutex.unlock();
        }
    }

    void mutex_test_thread_proc2(void) {
        checked = true;
        for (int i = 0; i < 20; ++i) {
            my_mutex.lock();
            boost::this_thread::sleep_for(interval2);
            ++n;
            std::cout << "mutex_test_thread_proc2: " << n << std::endl;
            my_mutex.unlock();
        }
    }
#else   // Unboost
    int n = 0;
    unboost::timed_mutex my_mutex;
    unboost::chrono::milliseconds interval1(100);
    unboost::chrono::milliseconds interval2(200);

    void mutex_test_thread_proc1(void) {
        checked = true;
        for (int i = 0; i < 10; ++i) {
            my_mutex.lock();
            unboost::this_thread::sleep_for(interval1);
            ++n;
            std::cout << "mutex_test_thread_proc1: " << n << std::endl;
            my_mutex.unlock();
        }
    }

    void mutex_test_thread_proc2(void) {
        checked = true;
        for (int i = 0; i < 10; ++i) {
            my_mutex.lock();
            unboost::this_thread::sleep_for(interval2);
            ++n;
            std::cout << "mutex_test_thread_proc2: " << n << std::endl;
            my_mutex.unlock();
        }
    }
#endif


//////////////////////////////////////////////////////////////////////////////

int main(void) {
    std::cout << "thread" << std::endl;

#ifdef CXX11
    std::thread::id cur_id = std::this_thread::get_id();
    std::cout << "current thread: " << cur_id << std::endl;

    std::chrono::milliseconds dura(2000);
    checked = false;
    std::thread t0(thread_proc0);
    t0.join();
    assert(checked);

    std::cout << "sleep 2 seconds" << std::endl;
    std::this_thread::sleep_for(dura);
    checked = false;
    std::thread t1(thread_proc1, 2);
    assert(t1.get_id() != cur_id);
    std::cout << t1.get_id() << std::endl;
    t1.join();
    assert(checked);

    std::cout << "sleep 2 seconds" << std::endl;
    auto two_sec_later =
        std::chrono::system_clock::now() + std::chrono::seconds(2);
    std::this_thread::sleep_until(two_sec_later);
    checked = false;
    int m = 3;
    std::thread t2(thread_proc2, 2, std::cref(m));
    std::cout << t2.get_id() << std::endl;
    t2.join();
    assert(checked);

    std::cout << "sleep 4 seconds" << std::endl;
    std::chrono::seconds s = std::chrono::seconds(2) * 2;
    std::this_thread::sleep_for(s);
    std::cout << "OK" << std::endl;

    checked = false;
    std::thread thread1(mutex_test_thread_proc1);
    std::thread thread2(mutex_test_thread_proc2);
    thread1.detach();
    thread2.detach();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    assert(checked);
#elif defined(BOOST)
    boost::thread::id cur_id = boost::this_thread::get_id();
    std::cout << "current thread: " << cur_id << std::endl;

    boost::chrono::milliseconds dura(2000);
    checked = false;
    boost::thread t0(thread_proc0);
    t0.join();
    assert(checked);

    std::cout << "sleep 2 seconds" << std::endl;
    boost::this_thread::sleep_for(dura);
    checked = false;
    boost::thread t1(thread_proc1, 2);
    assert(t1.get_id() != cur_id);
    std::cout << t1.get_id() << std::endl;
    t1.join();
    assert(checked);

    std::cout << "sleep 2 seconds" << std::endl;
    auto two_sec_later =
        boost::chrono::system_clock::now() + boost::chrono::seconds(2);
    boost::this_thread::sleep_until(two_sec_later);
    checked = false;
    int m = 3;
    boost::thread t2(thread_proc2, 2, boost::cref(m));
    std::cout << t2.get_id() << std::endl;
    t2.join();
    assert(checked);

    std::cout << "sleep 4 seconds" << std::endl;
    boost::chrono::seconds s = boost::chrono::seconds(2) * 2;
    boost::this_thread::sleep_for(s);
    std::cout << "OK" << std::endl;

    checked = false;
    boost::thread thread1(mutex_test_thread_proc1);
    boost::thread thread2(mutex_test_thread_proc2);
    thread1.detach();
    thread2.detach();
    boost::this_thread::sleep_for(boost::chrono::seconds(10));
    assert(checked);
#else   // Unboost
    unboost::thread::id cur_id = unboost::this_thread::get_id();
    std::cout << "current thread: " << cur_id << std::endl;

    unboost::chrono::milliseconds dura(2000);
    checked = false;
    unboost::thread t0(thread_proc0);
    t0.join();
    assert(checked);

    std::cout << "sleep 2 seconds" << std::endl;
    unboost::this_thread::sleep_for(dura);
    checked = false;
    unboost::thread t1(thread_proc1, 2);
    assert(t1.get_id() != cur_id);
    std::cout << t1.get_id() << std::endl;
    t1.join();
    assert(checked);

    std::cout << "sleep 2 seconds" << std::endl;
    unboost_auto_time_point two_sec_later =
        unboost::chrono::system_clock::now() + unboost::chrono::seconds(2);
    unboost::this_thread::sleep_until(two_sec_later);
    checked = false;
    int m = 3;
    unboost::thread t2(thread_proc2, 2, unboost::cref(m));
    std::cout << t2.get_id() << std::endl;
    t2.join();
    assert(checked);

    std::cout << "sleep 4 seconds" << std::endl;
    unboost::chrono::seconds s = unboost::chrono::seconds(2) * 2;
    unboost::this_thread::sleep_for(s);
    std::cout << "OK" << std::endl;

    checked = false;
    unboost::thread thread1(mutex_test_thread_proc1);
    unboost::thread thread2(mutex_test_thread_proc2);
    thread1.detach();
    thread2.detach();
    unboost::this_thread::sleep_for(unboost::chrono::seconds(5));
    assert(checked);
#endif  // Unboost

    std::cout << "success" << std::endl;

    return 0;
}
