// chrono.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#define UNBOOST_USE_CHRONO
#include <unboost.hpp>

int main(void) {
    using namespace unboost::chrono;
    std::cout << "chrono" << std::endl;
    //{
    //    seconds sec(1);
    //    std::cout << duration_cast<microseconds>(sec).count() << " microseconds" << std::endl;
    //    std::cout << duration_cast<milliseconds>(sec).count() << " milliseconds" << std::endl;
    //    std::cout << duration_cast<seconds>(sec).count() << " seconds" << std::endl;
    //    assert(duration_cast<microseconds>(sec).count() == 1000000);
    //    assert(duration_cast<milliseconds>(sec).count() == 1000);
    //    assert(duration_cast<seconds>(sec).count() == 1);
    //}
    //{
    //    unboost_auto_duration sec(seconds(1));
    //    std::cout << duration_cast<microseconds>(sec).count() << " microseconds" << std::endl;
    //    std::cout << duration_cast<milliseconds>(sec).count() << " milliseconds" << std::endl;
    //    std::cout << duration_cast<seconds>(sec).count() << " seconds" << std::endl;
    //    assert(duration_cast<microseconds>(sec).count() == 1000000);
    //    assert(duration_cast<milliseconds>(sec).count() == 1000);
    //    assert(duration_cast<seconds>(sec).count() == 1);
    //}
    //{
    //    milliseconds ms(3);
    //    microseconds us = 2 * ms;
    //    duration<double, unboost::ratio<1, 30> > hz30(3.5);
    //    assert(ms.count() == 3);
    //    assert(us.count() == 6000);
    //    assert(hz30.count() == 3.5);
    //}
    //{
    //    milliseconds ms(3);
    //    unboost_auto_duration us = microseconds(2 * ms);
    //    duration<double, unboost::ratio<1, 30> > hz30(3.5);
    //    assert(ms.count() == 3);
    //    assert(us.count() == 6000);
    //    assert(hz30.count() == 3.5);
    //}
    //{
    //    seconds s1(10);
    //    seconds s2 = -s1;
    //    assert(s2.count() == -10);
    //}
    //{
    //    seconds s1(10);
    //    unboost_auto_duration s2 = -s1;
    //    assert(s2.count() == -10);
    //}
    //{
    //    hours h(1);
    //    minutes m = ++h;
    //    m--;
    //    assert(m.count() == 119);
    //}
    //{
    //    hours h(1);
    //    unboost_auto_duration m = minutes(++h);
    //    m--;
    //    assert(m.count() == 119);
    //}
    //{
    //    minutes m(11);
    //    m *= 2;
    //    m += hours(10);
    //    assert(m.count() == 622);
    //    assert(duration_cast<hours>(m).count() == 10);
    //    m %= hours(1);
    //    assert(m.count() == 22);
    //}
    //{
    //    unboost_auto_duration m = minutes(11);
    //    m *= 2;
    //    m += hours(10);
    //    assert(m.count() == 622);
    //    assert(duration_cast<hours>(m).count() == 10);
    //    m %= hours(1);
    //    assert(m.count() == 22);
    //}
        // FIXME
        {
            std::cout << "MMMM" << std::endl;
            //seconds s = hours(1) + minutes(1);
            hours(1) + minutes(1);
        }
        //{
        //    seconds s = hours(1) + 2 * minutes(10) + seconds(70) / 10;
        //    std::cout << "1 hour + 2*10 min + 70/10 sec = " << s.count() << " seconds\n";
        //    assert(s.count() == 4807);
        //
        //    assert(duration_cast<hours>(s).count() == 1);
        //    assert(duration_cast<minutes>(s % hours(1)).count() == 20);
        //    assert(duration_cast<seconds>(s % minutes(1)).count() == 7);
        //}
        //{
        //    unboost_auto_duration s = hours(1) + 2 * minutes(10) + seconds(70) / 10;
        //    std::cout << "1 hour + 2*10 min + 70/10 sec = " << s.count() << " seconds\n";
        //    assert(s.count() == 4807);
        //
        //    assert(duration_cast<hours>(s).count() == 1);
        //    assert(duration_cast<minutes>(s % hours(1)).count() == 20);
        //    assert(duration_cast<seconds>(s % minutes(1)).count() == 7);
        //}
        //{
        //    assert(seconds(2) == milliseconds(2000));
        //    assert(seconds(61) > minutes(1));
        //}
    //{
    //    unboost_auto_duration sec2 = seconds(2);
    //    unboost_auto_duration sec61 = seconds(61);
    //    assert(sec2 == milliseconds(2000));
    //    assert(sec61 > minutes(1));
    //}
    //{
    //    typedef duration<int, unboost::ratio<1, 100000000> >    shakes;
    //    typedef duration<int, unboost::centi>                   jiffies;
    //    typedef duration<float, unboost::ratio<12096,10000> >   microfortnights;
    //    typedef duration<float, unboost::ratio<3155,1000> >     nanocenturies;
    //    seconds sec(1);
    //
    //    assert(duration_cast<shakes>(sec).count() == 100000000);
    //    assert(duration_cast<jiffies>(sec).count() == 100);
    //    double f1 = duration_cast<microfortnights>(sec).count();
    //    assert(0.8267 <= f1 && f1 <= 0.8268);
    //    double f2 = duration_cast<nanocenturies>(sec).count();
    //    assert(0.31695 <= f2 && f2 <= 0.31696);
    //}

    //const unsigned threshold = 1200;
    //{
    //    for (size_t ms = 1000; ms < 2000; ms += 500) {
    //        high_resolution_clock::time_point start = high_resolution_clock::now();
    //        milliseconds dura(ms);
    //        unboost::this_thread::sleep_for(dura);
    //        high_resolution_clock::time_point end = high_resolution_clock::now();
    //
    //        unboost_auto_duration elapsed = end - start;
    //        assert(ms - threshold <= elapsed.count() && elapsed.count() + threshold);
    //    }
    //}
    //{
    //    for (size_t ms = 1000; ms < 2000; ms += 500) {
    //        unboost_auto_time_point start = high_resolution_clock::now();
    //        milliseconds dura(ms);
    //        unboost::this_thread::sleep_for(dura);
    //        unboost_auto_time_point end = high_resolution_clock::now();
    //
    //        unboost_auto_duration elapsed = end - start;
    //        assert(ms - threshold <= elapsed.count() && elapsed.count() + threshold);
    //    }
    //}
    //// steady_clock
    //{
    //    for (size_t ms = 1000; ms < 2000; ms += 500) {
    //        steady_clock::time_point start = steady_clock::now();
    //        milliseconds dura(ms);
    //        unboost::this_thread::sleep_for(dura);
    //        steady_clock::time_point end = steady_clock::now();
    //
    //        unboost_auto_duration elapsed = end - start;
    //        assert(ms - threshold <= elapsed.count() && elapsed.count() + threshold);
    //    }
    //}
    //{
    //    for (size_t ms = 1000; ms < 2000; ms += 500) {
    //        unboost_auto_time_point start = steady_clock::now();
    //        milliseconds dura(ms);
    //        unboost::this_thread::sleep_for(dura);
    //        unboost_auto_time_point end = steady_clock::now();
    //
    //        unboost_auto_duration elapsed = end - start;
    //        assert(ms - threshold <= elapsed.count() && elapsed.count() + threshold);
    //    }
    //}
    //// system_clock
    //{
    //    for (size_t ms = 1000; ms < 2000; ms += 500) {
    //        system_clock::time_point start = system_clock::now();
    //        milliseconds dura(ms);
    //        unboost::this_thread::sleep_for(dura);
    //        system_clock::time_point end = system_clock::now();
    //
    //        unboost_auto_duration elapsed = end - start;
    //        assert(ms - threshold <= elapsed.count() && elapsed.count() + threshold);
    //    }
    //}
    //{
    //    for (size_t ms = 1000; ms < 2000; ms += 500) {
    //        unboost_auto_time_point start = system_clock::now();
    //        milliseconds dura(ms);
    //        unboost::this_thread::sleep_for(dura);
    //        unboost_auto_time_point end = system_clock::now();
    //
    //        unboost_auto_duration elapsed = end - start;
    //        assert(ms - threshold <= elapsed.count() && elapsed.count() + threshold);
    //    }
    //}
    //{
    //    time_point<system_clock> p1, p2, p3;
    //    typedef duration<_int64_t, ratio<3600 * 24> >  days;
    //    typedef duration<_int64_t, ratio<3600 * 24 * 31> > months;
    //    typedef duration<_int64_t, ratio<3600 * 24 * 356> >  years;
    //
    //    p2 = system_clock::now();
    //    p3 = p2 - hours(24);
    //
    //    std::time_t epoch_time = system_clock::to_time_t(p1);
    //    std::cout << "epoch: " << std::ctime(&epoch_time);
    //
    //    std::time_t today_time = system_clock::to_time_t(p2);
    //    std::cout << "today: " << std::ctime(&today_time);
    //
    //    std::cout << "years since epoch: "
    //              << duration_cast<years>(p2.time_since_epoch()).count()
    //              << '\n';
    //    std::cout << "yesterday, years since epoch: "
    //              << duration_cast<years>(p3.time_since_epoch()).count()
    //              << '\n';
    //}
    //{
    //    time_point<system_clock> now = system_clock::now();
    //    std::vector<time_point<system_clock>> times;
    //    times.push_back(now - hours(24));
    //    times.push_back(now - hours(48));
    //    times.push_back(now + hours(24));
    //
    //    time_point<system_clock> earliest = time_point<system_clock>::max();
    //
    //    std::cout << "all times:\n";
    //    for (const auto &time : times) {
    //        std::time_t t = system_clock::to_time_t(time);
    //        std::cout << std::ctime(&t);
    //
    //        if (time < earliest) earliest = time;
    //    }
    //
    //    std::time_t t = system_clock::to_time_t(earliest);
    //    std::cout << "earliest:\n" << std::ctime(&t);
    //}

    std::cout << "success" << std::endl;

    return 0;
}
