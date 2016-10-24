// chrono.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_CHRONO
#include <unboost.hpp>

int main(void) {
    using namespace unboost::chrono;
    std::cout << "chrono" << std::endl;
    {
        seconds sec(1);
        std::cout << duration_cast<microseconds>(sec).count() << " microseconds" << std::endl;
        std::cout << duration_cast<milliseconds>(sec).count() << " milliseconds" << std::endl;
        std::cout << duration_cast<seconds>(sec).count() << " seconds" << std::endl;
        assert(duration_cast<microseconds>(sec).count() == 1000000);
        assert(duration_cast<milliseconds>(sec).count() == 1000);
        assert(duration_cast<seconds>(sec).count() == 1);
    }
    {
        unboost_auto_duration sec(seconds(1));
        std::cout << duration_cast<microseconds>(sec).count() << " microseconds" << std::endl;
        std::cout << duration_cast<milliseconds>(sec).count() << " milliseconds" << std::endl;
        std::cout << duration_cast<seconds>(sec).count() << " seconds" << std::endl;
        assert(duration_cast<microseconds>(sec).count() == 1000000);
        assert(duration_cast<milliseconds>(sec).count() == 1000);
        assert(duration_cast<seconds>(sec).count() == 1);
    }
    {
        milliseconds ms(3);
        microseconds us = 2 * ms;
        duration<double, unboost::ratio<1, 30> > hz30(3.5);
        assert(ms.count() == 3);
        assert(us.count() == 6000);
        assert(hz30.count() == 3.5);
    }
    {
        milliseconds ms(3);
        unboost_auto_duration us = microseconds(2 * ms);
        duration<double, unboost::ratio<1, 30> > hz30(3.5);
        assert(ms.count() == 3);
        assert(us.count() == 6000);
        assert(hz30.count() == 3.5);
    }
    {
        seconds s1(10);
        seconds s2 = -s1;
        assert(s2.count() == -10);
    }
    {
        seconds s1(10);
        unboost_auto_duration s2 = -s1;
        assert(s2.count() == -10);
    }
    {
        hours h(1);
        minutes m = ++h;
        m--;
        assert(m.count() == 119);
    }
    {
        hours h(1);
        unboost_auto_duration m = minutes(++h);
        m--;
        assert(m.count() == 119);
    }
    {
        minutes m(11);
        m *= 2;
        m += hours(10);
        assert(m.count() == 622);
        assert(duration_cast<hours>(m).count() == 10);
        m %= hours(1);
        assert(m.count() == 22);
    }
    {
        unboost_auto_duration m = minutes(11);
        m *= 2;
        m += hours(10);
        assert(m.count() == 622);
        assert(duration_cast<hours>(m).count() == 10);
        m %= hours(1);
        assert(m.count() == 22);
    }
        // FIXME
        {
            std::cout << "MMMM" << std::endl;
            seconds s = hours(1) + minutes(1);
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
    {
        unboost_auto_duration sec2 = seconds(2);
        unboost_auto_duration sec61 = seconds(61);
        assert(sec2 == milliseconds(2000));
        assert(sec61 > minutes(1));
    }
    {
        typedef duration<int, unboost::ratio<1, 100000000> >    shakes;
        typedef duration<int, unboost::centi>                   jiffies;
        typedef duration<float, unboost::ratio<12096,10000> >   microfortnights;
        typedef duration<float, unboost::ratio<3155,1000> >     nanocenturies;
        seconds sec(1);
    
        assert(duration_cast<shakes>(sec).count() == 100000000);
        assert(duration_cast<jiffies>(sec).count() == 100);
        double f1 = duration_cast<microfortnights>(sec).count();
        assert(0.8267 <= f1 && f1 <= 0.8268);
        double f2 = duration_cast<nanocenturies>(sec).count();
        assert(0.31695 <= f2 && f2 <= 0.31696);
    }
    {
        //unboost::chrono::time_point<unboost::chrono::steady_clock> t1, t2;
        //for (unsigned __int64 size = 1; size < 10000000; size *= 10) {
        //    t1 = unboost::chrono::steady_clock::now();
        //    std::vector<int> v(size, 42);
        //    t2 = unboost::chrono::steady_clock::now();
        //    std::cout << t1.time_since_epoch().count() << std::endl;
        //    std::cout << t2.time_since_epoch().count() << std::endl;
        //    std::cout << size << ": " << (t1 - t2).count() << std::endl;
        //}
    }
    std::cout << "success" << std::endl;

    return 0;
}
