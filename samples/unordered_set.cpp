// unordered_set.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cassert>

#ifdef CXX11
    #include <unordered_set>
#elif defined(BOOST)
    #include <boost/unordered_set.hpp>
#else   // Unboost
    #include <unboost/unordered_set.hpp>
#endif

void test_unordered_set(void) {
    std::cout << "unorderd_set" << std::endl;

#ifdef CXX11
    using std::unordered_set;
#elif defined(BOOST)
    using boost::unordered_set;
#else   // Unboost
    using unboost::unordered_set;
#endif

    unordered_set<int> usi1;
    unordered_set<int> usi2;
    unordered_set<std::string> uss;

    assert(usi1.empty());
    assert(usi1.size() == 0);
    assert(usi1.find(1) == usi1.end());

    usi1.insert(1);
    assert(usi1.size() == 1);
    assert(usi1.find(1) != usi1.end());
    assert(usi1.count(1) == 1);

    usi1.insert(2);
    assert(usi1.size() == 2);
    assert(usi1.find(2) != usi1.end());
    assert(usi1.count(2) == 1);

    {
        unordered_set<int>::iterator it, end = usi1.end();
        for (it = usi1.begin(); it != end; ++it) {
            std::cout << *it << std::endl;
        }
    }

    std::cout << "#" << usi1.count(1) << std::endl;
    assert(usi1.count(1) == 1);
    assert(usi1.count(2) == 1);
    assert(usi1.count(3) == 0);
    usi1.rehash(10);

    std::cout << "#" << usi1.count(1) << std::endl;
    assert(usi1.count(1) == 1);
    assert(usi1.count(2) == 1);
    assert(usi1.count(3) == 0);

    assert(usi1.find(1) != usi1.end());
    assert(usi1.find(2) != usi1.end());
    assert(usi1.find(3) == usi1.end());

    usi1.clear();
    assert(usi1.empty());
    assert(usi1.size() == 0);

    usi1.insert(1);
    usi1.insert(2);
    usi1.insert(2);

    assert(usi1.count(1) == 1);
    assert(usi1.count(2) == 1);
    assert(usi1.count(3) == 0);

    assert(usi1.find(1) != usi1.end());
    assert(usi1.find(2) != usi1.end());
    assert(usi1.find(3) == usi1.end());
    assert(usi1.size() == 2);

    usi2 = usi1;

    assert(usi2.count(1) == 1);
    assert(usi2.count(2) == 1);
    assert(usi2.count(3) == 0);

    assert(usi2.find(1) != usi1.end());
    assert(usi2.find(2) != usi1.end());
    assert(usi2.find(3) == usi1.end());
    assert(usi2.size() == 2);

    usi1.erase(2);
    assert(usi1.find(1) != usi1.end());
    assert(usi1.find(2) == usi1.end());
    assert(usi1.find(3) == usi1.end());
    assert(usi1.size() == 1);

    usi1.erase(1);
    assert(usi1.find(1) == usi1.end());
    assert(usi1.find(2) == usi1.end());
    assert(usi1.find(3) == usi1.end());

    assert(usi1.empty());
    assert(usi1.size() == 0);

    uss.insert("1");
    uss.insert("2");
    uss.insert("2");

    assert(uss.find("1") != uss.end());
    assert(uss.find("2") != uss.end());
    assert(uss.find("3") == uss.end());
    assert(uss.count("1") == 1);
    assert(uss.count("2") == 1);
    assert(uss.count("3") == 0);

    uss.erase("2");
    uss.insert("3");
    assert(uss.find("1") != uss.end());
    assert(uss.find("2") == uss.end());
    assert(uss.find("3") != uss.end());
    assert(uss.count("1") == 1);
    assert(uss.count("2") == 0);
    assert(uss.count("3") == 1);

    {
        unordered_set<std::string>::iterator it, end = uss.end();
        for (it = uss.begin(); it != end; ++it) {
            std::cout << "\"" << *it << "\"" << std::endl;
        }
    }

    usi1.clear();
    usi1.max_load_factor(10000);
    usi1.rehash(5);
    for (int i = 0; i < 100; ++i) {
        usi1.insert(i);
    }

    {
        unordered_set<int>::local_iterator lit = usi1.begin(1), lend = usi1.end(1);
        while (lit != lend) {
            std::cout << *lit << ", ";
            ++lit;
        }
        std::cout << std::endl;
    }

    std::cout << "success" << std::endl;
}


void test_unordered_multiset(void) {
    std::cout << "unorderd_multiset" << std::endl;

#ifdef CXX11
    using std::unordered_multiset;
#elif defined(BOOST)
    using boost::unordered_multiset;
#else   // Unboost
    using unboost::unordered_multiset;
#endif

    unordered_multiset<int> usi1;
    unordered_multiset<int> usi2;
    unordered_multiset<std::string> uss;

    assert(usi1.empty());
    assert(usi1.size() == 0);
    assert(usi1.find(1) == usi1.end());

    usi1.insert(1);
    assert(usi1.size() == 1);
    assert(usi1.find(1) != usi1.end());
    assert(usi1.count(1) == 1);

    usi1.insert(2);
    assert(usi1.size() == 2);
    assert(usi1.find(2) != usi1.end());
    assert(usi1.count(2) == 1);

    usi1.insert(2);
    assert(usi1.size() == 3);
    assert(usi1.find(2) != usi1.end());
    assert(usi1.count(2) == 2);

    {
        unordered_multiset<int>::iterator it, end = usi1.end();
        for (it = usi1.begin(); it != end; ++it) {
            std::cout << *it << std::endl;
        }
    }

    std::cout << "#" << usi1.count(1) << std::endl;
    assert(usi1.count(1) == 1);
    assert(usi1.count(2) == 2);
    assert(usi1.count(3) == 0);
    usi1.rehash(10);

    {
        unordered_multiset<int>::iterator it, end = usi1.end();
        for (it = usi1.begin(); it != end; ++it) {
            std::cout << *it << std::endl;
        }
    }

    std::cout << "#" << usi1.count(1) << std::endl;
    std::cout << "#" << usi1.count(2) << std::endl;
    assert(usi1.count(1) == 1);
    assert(usi1.count(2) == 2);
    assert(usi1.count(3) == 0);

    assert(usi1.find(1) != usi1.end());
    assert(usi1.find(2) != usi1.end());
    assert(usi1.find(3) == usi1.end());

    usi1.clear();
    assert(usi1.empty());
    assert(usi1.size() == 0);

    usi1.insert(1);
    usi1.insert(2);
    usi1.insert(2);

    assert(usi1.count(1) == 1);
    assert(usi1.count(2) == 2);
    assert(usi1.count(3) == 0);

    assert(usi1.find(1) != usi1.end());
    assert(usi1.find(2) != usi1.end());
    assert(usi1.find(3) == usi1.end());
    assert(usi1.size() == 3);

    usi2 = usi1;

    assert(usi2.count(1) == 1);
    assert(usi2.count(2) == 2);
    assert(usi2.count(3) == 0);

    assert(usi2.find(1) != usi1.end());
    assert(usi2.find(2) != usi1.end());
    assert(usi2.find(3) == usi1.end());
    assert(usi2.size() == 3);

    usi1.erase(2);
    assert(usi1.find(1) != usi1.end());
    assert(usi1.find(2) == usi1.end());
    assert(usi1.find(3) == usi1.end());
    assert(usi1.size() == 1);

    usi1.erase(1);
    assert(usi1.find(1) == usi1.end());
    assert(usi1.find(2) == usi1.end());
    assert(usi1.find(3) == usi1.end());

    assert(usi1.empty());
    assert(usi1.size() == 0);

    uss.insert("1");
    uss.insert("2");
    uss.insert("2");

    assert(uss.find("1") != uss.end());
    assert(uss.find("2") != uss.end());
    assert(uss.find("3") == uss.end());
    assert(uss.count("1") == 1);
    assert(uss.count("2") == 2);
    assert(uss.count("3") == 0);

    uss.erase("2");
    uss.insert("3");
    assert(uss.find("1") != uss.end());
    assert(uss.find("2") == uss.end());
    assert(uss.find("3") != uss.end());
    assert(uss.count("1") == 1);
    assert(uss.count("2") == 0);
    assert(uss.count("3") == 1);

    uss.insert("3");
    assert(uss.find("3") != uss.end());
    assert(uss.count("3") == 2);

    {
        unordered_multiset<std::string>::iterator it, end = uss.end();
        for (it = uss.begin(); it != end; ++it) {
            std::cout << "\"" << *it << "\"" << std::endl;
        }
    }

    usi1.clear();
    usi1.max_load_factor(10000);
    usi1.rehash(5);
    for (int i = 0; i < 100; ++i) {
        usi1.insert(i);
        usi1.insert(i);
    }

    {
        unordered_multiset<int>::local_iterator lit = usi1.begin(1), lend = usi1.end(1);
        while (lit != lend) {
            std::cout << *lit << ", ";
            ++lit;
        }
        std::cout << std::endl;
    }

    std::cout << "success" << std::endl;
}

int main(void) {
    test_unordered_set();
    test_unordered_multiset();
    return 0;
} // main
