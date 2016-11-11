// chrono.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>
#include <vector>

#ifdef CXX11
    #include <ratio>
    #include <chrono>
    #include <thread>
#elif defined(BOOST)
    #include <boost/ratio.hpp>
    #include <boost/chrono.hpp>
    #include <boost/thread.hpp>
#else   // Unboost
    #include <unboost/ratio.hpp>
    #include <unboost/chrono.hpp>
    #include <unboost/thread.hpp>
#endif

int main(void) {
    std::cout << "chrono" << std::endl;
    {
#ifdef CXX11
        using namespace std::chrono;
#elif defined(BOOST)
        using namespace boost::chrono;
#else   // Unboost
        using namespace unboost::chrono;
#endif
        seconds sec(1);
        std::cout << duration_cast<microseconds>(sec).count() << " microseconds" << std::endl;
        std::cout << duration_cast<milliseconds>(sec).count() << " milliseconds" << std::endl;
        std::cout << duration_cast<seconds>(sec).count() << " seconds" << std::endl;
        assert(duration_cast<microseconds>(sec).count() == 1000000);
        assert(duration_cast<milliseconds>(sec).count() == 1000);
        assert(duration_cast<seconds>(sec).count() == 1);
    }

    {
#ifdef CXX11
        using namespace std::chrono;
        auto sec = seconds(1);
#elif defined(BOOST)
        using namespace boost::chrono;
        auto sec = seconds(1);
#else   // Unboost
        using namespace unboost::chrono;
        unboost_auto_duration sec = seconds(1);
#endif
        std::cout << duration_cast<microseconds>(sec).count() << " microseconds" << std::endl;
        std::cout << duration_cast<milliseconds>(sec).count() << " milliseconds" << std::endl;
        std::cout << duration_cast<seconds>(sec).count() << " seconds" << std::endl;
        assert(duration_cast<microseconds>(sec).count() == 1000000);
        assert(duration_cast<milliseconds>(sec).count() == 1000);
        assert(duration_cast<seconds>(sec).count() == 1);
    }

    {
#ifdef CXX11
        using namespace std::chrono;
        using std::ratio;
#elif defined(BOOST)
        using namespace boost::chrono;
        using boost::ratio;
#else   // Unboost
        using namespace unboost::chrono;
        using unboost::ratio;
#endif
        milliseconds ms(3);
        microseconds us = 2 * ms;
        duration<double, ratio<1, 30> > hz30(3.5);
        assert(ms.count() == 3);
        assert(us.count() == 6000);
        assert(hz30.count() == 3.5);
    }

    {
#ifdef CXX11
        using namespace std::chrono;
        using std::ratio;
        milliseconds ms(3);
        auto us = microseconds(2 * ms);
#elif defined(BOOST)
        using namespace boost::chrono;
        using boost::ratio;
        milliseconds ms(3);
        auto us = microseconds(2 * ms);
#else   // Unboost
        using namespace unboost::chrono;
        using unboost::ratio;
        milliseconds ms(3);
        unboost_auto_duration us = microseconds(2 * ms);
#endif
        duration<double, ratio<1, 30> > hz30(3.5);
        assert(ms.count() == 3);
        assert(us.count() == 6000);
        assert(hz30.count() == 3.5);
    }

    {
#ifdef CXX11
        using namespace std::chrono;
#elif defined(BOOST)
        using namespace boost::chrono;
#else   // Unboost
        using namespace unboost::chrono;
#endif
        seconds s1(10);
        seconds s2 = -s1;
        assert(s2.count() == -10);
        seconds s3(10);
#ifdef CXX11
        auto s4 = -s3;
#elif defined(BOOST)
        auto s4 = -s3;
#else   // Unboost
        unboost_auto_duration s4 = -s3;
#endif
        assert(s4.count() == -10);
        hours h1(1);
        minutes m1 = ++h1;
        m1--;
        assert(m1.count() == 119);
        hours h2(1);
#ifdef CXX11
        auto m2 = minutes(++h2);
#elif defined(BOOST)
        auto m2 = minutes(++h2);
#else   // Unboost
        unboost_auto_duration m2 = minutes(++h2);
#endif
        m2--;
        assert(m2.count() == 119);
        minutes m3(11);
        m3 *= 2;
        m3 += hours(10);
        assert(m3.count() == 622);
        assert(duration_cast<hours>(m3).count() == 10);
        m3 %= hours(1);
        assert(m3.count() == 22);
    }

    {
#ifdef CXX11
        using namespace std::chrono;
        auto m = minutes(11);
#elif defined(BOOST)
        using namespace boost::chrono;
        auto m = minutes(11);
#else   // Unboost
        using namespace unboost::chrono;
        unboost_auto_duration m = minutes(11);
#endif
        m *= 2;
        m += hours(10);
        assert(m.count() == 622);
        assert(duration_cast<hours>(m).count() == 10);
        m %= hours(1);
        assert(m.count() == 22);
    }

    {
#ifdef CXX11
        using namespace std::chrono;
#elif defined(BOOST)
        using namespace boost::chrono;
#else   // Unboost
        using namespace unboost::chrono;
#endif
        seconds s = hours(1) + 2 * minutes(10) + seconds(70) / 10;
        std::cout << "1 hour + 2*10 min + 70/10 sec = " << s.count() << " seconds\n";
        assert(s.count() == 4807);

        assert(duration_cast<hours>(s).count() == 1);
        assert(duration_cast<minutes>(s % hours(1)).count() == 20);
        assert(duration_cast<seconds>(s % minutes(1)).count() == 7);
    }

    {
#ifdef CXX11
        using namespace std::chrono;
        auto s = hours(1) + 2 * minutes(10) + seconds(70) / 10;
#elif defined(BOOST)
        using namespace boost::chrono;
        auto s = hours(1) + 2 * minutes(10) + seconds(70) / 10;
#else   // Unboost
        using namespace unboost::chrono;
        unboost_auto_duration s = hours(1) + 2 * minutes(10) + seconds(70) / 10;
#endif
        std::cout << "1 hour + 2*10 min + 70/10 sec = " << s.count() << " seconds\n";
        assert(s.count() == 4807);

        assert(duration_cast<hours>(s).count() == 1);
        assert(duration_cast<minutes>(s % hours(1)).count() == 20);
        assert(duration_cast<seconds>(s % minutes(1)).count() == 7);
    }

    {
#ifdef CXX11
        using namespace std::chrono;
#elif defined(BOOST)
        using namespace boost::chrono;
#else   // Unboost
        using namespace unboost::chrono;
#endif
        assert(seconds(2) == milliseconds(2000));
        assert(seconds(61) > minutes(1));
    }

    {
#ifdef CXX11
        using namespace std::chrono;
        auto sec2 = seconds(2);
        auto sec61 = seconds(61);
#elif defined(BOOST)
        using namespace boost::chrono;
        auto sec2 = seconds(2);
        auto sec61 = seconds(61);
#else   // Unboost
        using namespace unboost::chrono;
        unboost_auto_duration sec2 = seconds(2);
        unboost_auto_duration sec61 = seconds(61);
#endif
        assert(sec2 == milliseconds(2000));
        assert(sec61 > minutes(1));
    }

    {
#ifdef CXX11
        using namespace std::chrono;
        using std::ratio;
        typedef ratio<1, 100> centi;
#elif defined(BOOST)
        using namespace boost::chrono;
        using boost::ratio;
        typedef ratio<1, 100> centi;
#else   // Unboost
        using namespace unboost::chrono;
        using unboost::ratio;
        typedef ratio<1, 100> centi;
#endif
        typedef duration<int, ratio<1, 100000000> >    shakes;
        typedef duration<int, centi>                   jiffies;
        typedef duration<float, ratio<12096, 10000> >  microfortnights;
        typedef duration<float, ratio<3155, 1000> >    nanocenturies;
        seconds sec(1);

        assert(duration_cast<shakes>(sec).count() == 100000000);
        assert(duration_cast<jiffies>(sec).count() == 100);
        double f1 = duration_cast<microfortnights>(sec).count();
        assert(0.8267 <= f1 && f1 <= 0.8268);
        double f2 = duration_cast<nanocenturies>(sec).count();
        assert(0.31695 <= f2 && f2 <= 0.31696);
    }
    {
#ifdef CXX11
        using namespace std::chrono;
        using std::ratio;
#elif defined(BOOST)
        using namespace boost::chrono;
        using boost::ratio;
#else   // Unboost
        using namespace unboost::chrono;
        using unboost::ratio;
#endif
        seconds a(1);
        milliseconds b = a;
        assert(b.count() == 1000);

        milliseconds c(1200);
        seconds d = duration_cast<seconds>(c);
        assert(d.count() == 1);

        typedef duration<float, ratio<1, 1000> > milliseconds_f;
        typedef duration<float, ratio<1, 1> > seconds_f;

        milliseconds_f x(1200.0f);
        seconds_f y = x;
        assert(1.1 <= y.count() && y.count() <= 1.3);
    }
    const unsigned threshold = 100;
    // high_resolution_clock
    std::cout << "high_resolution_clock" << std::endl;
    {
#ifdef CXX11
        using namespace std::chrono;
        using std::this_thread::sleep_for;
#elif defined(BOOST)
        using namespace boost::chrono;
        using boost::this_thread::sleep_for;
#else   // Unboost
        using namespace unboost::chrono;
        using unboost::this_thread::sleep_for;
#endif
        for (size_t ms = 1000; ms < 2000; ms += 300) {
            high_resolution_clock::time_point start = high_resolution_clock::now();
            milliseconds dura(ms);
            sleep_for(dura);
            high_resolution_clock::time_point end = high_resolution_clock::now();

#ifdef CXX11
            auto span = end - start;
            auto elapsed = duration_cast<milliseconds>(span);
#elif defined(BOOST)
            auto span = end - start;
            auto elapsed = duration_cast<milliseconds>(span);
#else   // Unboost
            unboost_auto_duration span = end - start;
            unboost_auto_duration elapsed = duration_cast<milliseconds>(span);
#endif
            std::cout << "elapsed.count(): " << elapsed.count() << std::endl;
            assert(abs(long(ms) - long(elapsed.count())) < threshold);
        }
    }
    // steady_clock
    std::cout << "steady_clock" << std::endl;
    {
#ifdef CXX11
        using namespace std::chrono;
        using std::this_thread::sleep_for;
#elif defined(BOOST)
        using namespace boost::chrono;
        using boost::this_thread::sleep_for;
#else   // Unboost
        using namespace unboost::chrono;
        using unboost::this_thread::sleep_for;
#endif
        for (size_t ms = 1000; ms < 2000; ms += 300) {
            steady_clock::time_point start = steady_clock::now();
            milliseconds dura(ms);
            sleep_for(dura);
            steady_clock::time_point end = steady_clock::now();

#ifdef CXX11
            auto span = end - start;
            auto elapsed = duration_cast<milliseconds>(span);
#elif defined(BOOST)
            auto span = end - start;
            auto elapsed = duration_cast<milliseconds>(span);
#else   // Unboost
            unboost_auto_duration span = end - start;
            unboost_auto_duration elapsed = duration_cast<milliseconds>(span);
#endif
            std::cout << "elapsed.count(): " << elapsed.count() << std::endl;
            assert(abs(long(ms) - long(elapsed.count())) < threshold);
        }
    }
    // system_clock
    std::cout << "system_clock" << std::endl;
    {
#ifdef CXX11
        using namespace std::chrono;
        using std::this_thread::sleep_for;
#elif defined(BOOST)
        using namespace boost::chrono;
        using boost::this_thread::sleep_for;
#else   // Unboost
        using namespace unboost::chrono;
        using unboost::this_thread::sleep_for;
#endif
        for (size_t ms = 1000; ms < 2000; ms += 300) {
            system_clock::time_point start = system_clock::now();
            milliseconds dura(ms);
            sleep_for(dura);
            system_clock::time_point end = system_clock::now();

#ifdef CXX11
            auto span = end - start;
            auto elapsed = duration_cast<milliseconds>(span);
#elif defined(BOOST)
            auto span = end - start;
            auto elapsed = duration_cast<milliseconds>(span);
#else   // Unboost
            unboost_auto_duration span = end - start;
            unboost_auto_duration elapsed = duration_cast<milliseconds>(span);
#endif
            std::cout << "elapsed.count(): " << elapsed.count() << std::endl;
            assert(abs(long(ms) - long(elapsed.count())) < threshold);
        }
    }
    {
#ifdef CXX11
        using namespace std::chrono;
#elif defined(BOOST)
        using namespace boost::chrono;
#else   // Unboost
        using namespace unboost::chrono;
#endif
        duration<int> foo;
        duration<int> bar(10);

        foo = bar;               // 10  10
        foo = foo + bar;         // 20  10
        ++foo;                   // 21  10
        --bar;                   // 21   9
        foo *= 2;                // 42   9
        foo /= 3;                // 14   9
        bar += (foo % bar);      // 14  14

        assert(foo == bar);
        assert(foo.count() == 14);
        assert(bar.count() == 14);

#ifdef CXX11
        auto foo2 = duration<int>();
        auto bar2 = duration<int>(10);
#elif defined(BOOST)
        auto foo2 = duration<int>();
        auto bar2 = duration<int>(10);
#else   // Unboost
        unboost_auto_duration foo2 = duration<int>();
        unboost_auto_duration bar2 = duration<int>(10);
#endif

        foo2 = bar2;                // 10  10
        foo2 = foo2 + bar2;         // 20  10
        ++foo2;                     // 21  10
        --bar2;                     // 21   9
        foo2 *= 2;                  // 42   9
        foo2 /= 3;                  // 14   9
        bar2 += (foo2 % bar2);      // 14  14

        assert(foo2 == bar2);
        assert(foo2.count() == 14);
        assert(bar2.count() == 14);
    }
    {
#ifdef CXX11
        using namespace std::chrono;
        using std::ratio;
        time_point<system_clock> p1, p2, p3;
        typedef duration<long long, ratio<3600 * 24 * 365> >  years;
#elif defined(BOOST)
        using namespace boost::chrono;
        using boost::ratio;
        time_point<system_clock> p1, p2, p3;
        typedef duration<long long, ratio<3600 * 24 * 365> >  years;
#else   // Unboost
        using namespace unboost::chrono;
        using unboost::ratio;
        time_point<system_clock> p1, p2, p3;
        typedef duration<unboost::_int64_t, ratio<3600 * 24 * 365> >  years;
#endif

        p2 = system_clock::now();
        p3 = p2 - hours(24);

        std::time_t epoch_time = system_clock::to_time_t(p1);
        std::cout << "epoch: " << std::asctime(std::gmtime(&epoch_time));

        std::time_t today_time = system_clock::to_time_t(p2);
        std::cout << "today: " << std::asctime(std::gmtime(&today_time));

        std::cout << "years since epoch: "
                  << duration_cast<years>(p2.time_since_epoch()).count()
                  << '\n';
        std::cout << "yesterday, years since epoch: "
                  << duration_cast<years>(p3.time_since_epoch()).count()
                  << '\n';
    }
    {
#ifdef CXX11
        using namespace std::chrono;
#elif defined(BOOST)
        using namespace boost::chrono;
#else   // Unboost
        using namespace unboost::chrono;
#endif
        time_point<system_clock> now = system_clock::now();
        std::vector<time_point<system_clock> > times;
        times.push_back(now - hours(24));
        times.push_back(now - hours(48));
        times.push_back(now + hours(24));

        time_point<system_clock> earliest = time_point<system_clock>::max();

        std::cout << "all times:\n";
        size_t count = times.size();
        for (size_t i = 0; i < count; ++i) {
            std::time_t t = system_clock::to_time_t(times[i]);
            std::cout << std::asctime(std::gmtime(&t));

            if (times[i] < earliest) earliest = times[i];
        }

        std::time_t t = system_clock::to_time_t(earliest);
        std::cout << "earliest:\n";
        std::cout << std::asctime(std::gmtime(&t)) << std::endl;
    }

    std::cout << "success" << std::endl;

    return 0;
}
