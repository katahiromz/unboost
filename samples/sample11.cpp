#define UNBOOST_USE_CHRONO
#include <unboost.hpp>

int main(void) {
    std::cout << "chrono" << std::endl;
    {
        // 4807 seconds
        unboost_auto_duration s = unboost::chrono::hours(1)
                                  + 2 * unboost::chrono::minutes(10)
                                  + unboost::chrono::seconds(70) / 10;
        std::cout << "1 hour + 2*10 min + 70/10 sec = " << s.count() << " seconds\n";
    }
    {
        using namespace unboost::chrono;
        seconds sec(1);
        std::cout << duration_cast<microseconds>(sec).count() << " microseconds" << std::endl;
        std::cout << duration_cast<milliseconds>(sec).count() << " milliseconds" << std::endl;
        std::cout << duration_cast<seconds>(sec).count() << " seconds" << std::endl;
        std::cout << duration_cast<hours>(sec).count() << " hours" << std::endl;
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

    return 0;
}
