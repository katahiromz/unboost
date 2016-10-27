// emplace.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    //
#elif defined(CXX03)
    //
#else   // Unboost
    #include <unboost/emplace.hpp>
#endif

#include <cstdio>
#include <vector>
#include <list>
#include <map>
#include <string>

int main(void) {
    std::cout << "emplace" << std::endl;

#ifdef CXX11
    std::vector<int> v;
    v.emplace_back(1);
    v.emplace_back(2);
    assert(v.size() == 2);
    assert(v[0] == 1);
    assert(v[1] == 2);

    std::list<int> lis;
    lis.emplace_back(1);
    lis.emplace_back(2);
    std::list<int>::iterator it = lis.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);

    lis.emplace(lis.end(), 3);
    it = lis.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);

    std::map<int, std::string> m;
    m.emplace(1, "one");
    m.emplace(2, "two");
    m.emplace(3, "three");
    assert(m[1] == "one");
    assert(m[2] == "two");
    assert(m[3] == "three");
#elif defined(CXX03)
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    assert(v.size() == 2);
    assert(v[0] == 1);
    assert(v[1] == 2);

    std::list<int> lis;
    lis.push_back(1);
    lis.push_back(2);
    std::list<int>::iterator it = lis.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);

    lis.insert(lis.end(), 3);
    it = lis.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);

    std::map<int, std::string> m;
    m.insert(std::make_pair<int, std::string>(1, "one"));
    m.insert(std::make_pair<int, std::string>(2, "two"));
    m.insert(std::make_pair<int, std::string>(3, "three"));
    assert(m[1] == "one");
    assert(m[2] == "two");
    assert(m[3] == "three");
#else   // Unboost
    std::vector<int> v;
    unboost::emplace_back(v, 1);
    unboost::emplace_back(v, 2);
    assert(v.size() == 2);
    assert(v[0] == 1);
    assert(v[1] == 2);

    std::list<int> lis;
    unboost::emplace_back(lis, 1);
    unboost::emplace_back(lis, 2);
    std::list<int>::iterator it = lis.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);

    unboost::emplace_at(lis, lis.end(), 3);
    it = lis.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 3);

    std::map<int, std::string> m;
    unboost::emplace(m, 1, "one");
    unboost::emplace(m, 2, "two");
    unboost::emplace(m, 3, "three");
    assert(m[1] == "one");
    assert(m[2] == "two");
    assert(m[3] == "three");
#endif  // Unboost

    std::cout << "success" << std::endl;

    return 0;
}
