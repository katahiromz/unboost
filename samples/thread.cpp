// thread.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

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

#include <iostream>
#include <cassert>

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

#ifdef CXX11
    using std::thread;
    using std::this_thread::get_id;
    using std::this_thread::sleep_for;
    using std::this_thread::sleep_until;
    using namespace std::chrono;
    using std::mutex;
    using std::recursive_mutex ;
    using std::lock;
    using std::try_lock;
    using std::unique_lock;
    using std::defer_lock;
    using std::lock_guard;
    using std::cref;
#elif defined(BOOST)
    using boost::thread;
    using boost::this_thread::get_id;
    using boost::this_thread::sleep_for;
    using boost::this_thread::sleep_until;
    using namespace boost::chrono;
    using boost::mutex;
    using boost::recursive_mutex ;
    using boost::lock;
    using boost::try_lock;
    using boost::unique_lock;
    using boost::defer_lock;
    using boost::lock_guard;
    using boost::cref;
#else   // Unboost
    using unboost::thread;
    using unboost::this_thread::get_id;
    using unboost::this_thread::sleep_for;
    using unboost::this_thread::sleep_until;
    using namespace unboost::chrono;
    using unboost::mutex;
    using unboost::recursive_mutex ;
    using unboost::lock;
    using unboost::try_lock;
    using unboost::unique_lock;
    using unboost::defer_lock;
    using unboost::lock_guard;
    using unboost::cref;
#endif

//////////////////////////////////////////////////////////////////////////////

mutex mtx1;
recursive_mutex mtx2;

void the_thread_proc(void) {
    unique_lock<mutex>              lk1(mtx1, defer_lock);
    unique_lock<recursive_mutex>    lk2(mtx2, defer_lock);
    int result = try_lock(lk1, lk2);
    std::cout << "result: " << result << std::endl;
    assert(result == 1);
    assert(!lk1.owns_lock());
}

void test_locking() {
    {
        int result = try_lock(mtx1, mtx2);
        assert(result == -1);
        mtx1.unlock();
        mtx2.unlock();
    }
    {
        unique_lock<mutex>              lk1(mtx1, defer_lock);
        unique_lock<recursive_mutex>    lk2(mtx2, defer_lock);
        int result = try_lock(lk1, lk2);
        assert(result == -1);
    }
    {
        lock_guard<recursive_mutex>     lk2_main_thread(mtx2);
        thread th(the_thread_proc);
        th.join();
    }
}

//////////////////////////////////////////////////////////////////////////////

void test_threading(void) {
    thread::id cur_id = get_id();
    std::cout << "current thread: " << cur_id << std::endl;

    milliseconds dura(2000);
    checked = false;
    thread t0(thread_proc0);
    assert(t0.joinable());
    t0.join();
    assert(!t0.joinable());
    assert(checked);

    std::cout << "sleep 2 seconds" << std::endl;
    sleep_for(dura);
    checked = false;
    thread t1(thread_proc1, 2);
    assert(t1.get_id() != cur_id);
    std::cout << t1.get_id() << std::endl;
    t1.join();
    assert(checked);

    std::cout << "sleep 2 seconds" << std::endl;
    unboost_auto_time_point two_sec_later = system_clock::now() + seconds(2);
    sleep_until(two_sec_later);
    checked = false;
    int m = 3;
    thread t2(thread_proc2, 2, cref(m));
    std::cout << t2.get_id() << std::endl;
    t2.join();
    assert(checked);

    std::cout << "sleep 4 seconds" << std::endl;
    seconds s = seconds(2) * 2;
    sleep_for(s);
    std::cout << "OK" << std::endl;

    checked = false;
    thread thread1(mutex_test_thread_proc1);
    thread thread2(mutex_test_thread_proc2);
    thread1.detach();
    thread2.detach();
    sleep_for(seconds(10));
    assert(checked);
}

//////////////////////////////////////////////////////////////////////////////

int main(void) {
    std::cout << "thread" << std::endl;

    test_locking();
    test_threading();

    std::cout << "success" << std::endl;

    return 0;
}
