// unordered_map.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    #include <unordered_map>
#elif defined(BOOST)
    #include <boost/unordered_map.hpp>
#else   // Unboost
    #include <unboost/unordered_map.hpp>
#endif

#include <iostream>
#include <cassert>

void test_unordered_map(void) {
    std::cout << "unorderd_map" << std::endl;

#ifdef CXX11
    using std::unordered_map;
#elif defined(BOOST)
    using boost::unordered_map;
#else   // Unboost
    using unboost::unordered_map;
#endif

    unordered_map<int, int> um1, um2;

    assert(um1.empty());
    assert(um1.size() == 0);

    um1.insert(std::make_pair(2, 3));
    assert(!um1.empty());
    assert(um1.size() == 1);
    assert(um1.find(2)->second == 3);
    assert(um1.count(2) == 1);
    assert(um1.count(4) == 0);
    assert(um1.count(5) == 0);

    um1.insert(std::make_pair(4, 5));
    assert(!um1.empty());
    assert(um1.size() == 2);
    assert(um1.find(2)->second == 3);
    assert(um1.find(4)->second == 5);
    assert(um1.count(2) == 1);
    assert(um1.count(4) == 1);
    assert(um1.count(5) == 0);

    um1.insert(std::make_pair(4, 6));
    assert(!um1.empty());
    assert(um1.size() == 2);
    assert(um1.find(2)->second == 3);
    assert(um1.find(4)->second == 5);
    assert(um1.count(2) == 1);
    assert(um1.count(4) == 1);
    assert(um1.count(5) == 0);

    assert(um2.empty());

    um2 = um1;
    um1.clear();
    assert(um1.empty());
    assert(um1.size() == 0);

    assert(!um2.empty());
    assert(um2.size() == 2);
    assert(um2.find(2)->second == 3);
    assert(um2.find(4)->second == 5);
    assert(um2.count(2) == 1);
    assert(um2.count(4) == 1);
    assert(um2.count(5) == 0);

    um1.swap(um2);
    assert(um1.size() == 2);
    assert(um1.find(2) != um1.end());
    assert(um1.find(3) == um1.end());
    assert(um1.find(4) != um1.end());
    assert(um2.empty());

    um1[10] = 10;
    assert(um1.size() == 3);
    assert(um1.find(10) != um1.end());
    assert(um1[10] == 10);

    {
        unordered_map<int, int>::iterator it, end = um1.end();
        for (it = um1.begin(); it != end; ++it) {
            std::cout << it->first << ", " << it->second << std::endl;
        }
    }

    um1.clear();
    um1.max_load_factor(10000);
    um1.rehash(5);
    for (int i = 0; i < 100; ++i) {
        um1.insert(std::make_pair(i, i + 1));
    }

    std::cout << "##" << um1.bucket_count() << std::endl;
    for (size_t i = 0; i < 5; ++i) {
        unordered_map<int, int>::local_iterator lit = um1.begin(i), lend = um1.end(i);
        while (lit != lend) {
            std::cout << "(" << lit->first << ", " << lit->second << "), ";
            ++lit;
        }
        std::cout << std::endl;
    }

    std::cout << "success" << std::endl;
} // test_unordered_map

void test_unordered_multimap(void) {
    std::cout << "unorderd_multimap" << std::endl;

#ifdef CXX11
    using std::unordered_multimap;
#elif defined(BOOST)
    using boost::unordered_multimap;
#else   // Unboost
    using unboost::unordered_multimap;
#endif

    unordered_multimap<int, int> um1, um2;

    assert(um1.empty());
    assert(um1.size() == 0);

    um1.insert(std::make_pair(2, 3));
    assert(!um1.empty());
    assert(um1.size() == 1);
    assert(um1.count(2) == 1);
    assert(um1.count(4) == 0);
    assert(um1.count(5) == 0);

    um1.insert(std::make_pair(4, 5));
    assert(!um1.empty());
    assert(um1.size() == 2);
    assert(um1.count(2) == 1);
    assert(um1.count(4) == 1);
    assert(um1.count(5) == 0);

    um1.insert(std::make_pair(4, 5));
    assert(!um1.empty());
    assert(um1.size() == 3);
    assert(um1.count(2) == 1);
    assert(um1.count(4) == 2);
    assert(um1.count(5) == 0);

    um1.insert(std::make_pair(4, 6));
    assert(!um1.empty());
    assert(um1.size() == 4);
    assert(um1.count(2) == 1);
    assert(um1.count(4) == 3);
    assert(um1.count(5) == 0);

    assert(um2.empty());

    um2 = um1;
    um1.clear();
    assert(um1.empty());
    assert(um1.size() == 0);

    assert(!um2.empty());
    assert(um2.size() == 4);
    assert(um2.count(2) == 1);
    assert(um2.count(4) == 3);
    assert(um2.count(5) == 0);

    um1.swap(um2);
    assert(um1.size() == 4);
    assert(um1.find(2) != um1.end());
    assert(um1.find(3) == um1.end());
    assert(um1.find(4) != um1.end());
    assert(um2.empty());

    {
        unordered_multimap<int, int>::iterator it, end = um1.end();
        for (it = um1.begin(); it != end; ++it) {
            std::cout << it->first << ", " << it->second << std::endl;
        }
    }

    um1.clear();
    um1.max_load_factor(10000);
    um1.rehash(5);
    for (int i = 0; i < 100; ++i) {
        um1.insert(std::make_pair(i, i + 1));
    }

    std::cout << "##" << um1.bucket_count() << std::endl;
    for (size_t i = 0; i < 5; ++i) {
        unordered_multimap<int, int>::local_iterator lit = um1.begin(i), lend = um1.end(i);
        while (lit != lend) {
            std::cout << "(" << lit->first << ", " << lit->second << "), ";
            ++lit;
        }
        std::cout << std::endl;
    }

    std::cout << "success" << std::endl;
} // test_unordered_multimap

int main(void) {
    test_unordered_map();
    test_unordered_multimap();

    return 0;
} // main
