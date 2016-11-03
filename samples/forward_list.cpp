// forward_list.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>

#ifdef CXX11
    #include <forward_list>
    using std::forward_list;
#else   // Unboost
    #include <unboost/forward_list.hpp>
    using unboost::forward_list;
#endif

typedef forward_list<char> FL;

void print(const FL& fl) {
    FL::const_iterator it = fl.begin();
    while (it != fl.end()) {
        std::cout << (int)*it << " ";
        ++it;
    }
    std::cout << std::endl;
}

int main(void) {
    std::cout << "forward_list" << std::endl;

    FL lis;
    FL::iterator it, it2;
    assert(lis.empty());
    lis.push_front(1);
    lis.push_front(2);
    // 2, 1
    print(lis);
    it = lis.begin();
    assert(*it == 2);
    ++it;
    assert(*it == 1);
    ++it;
    assert(it == lis.end());

    FL lis2 = lis;
    // 2, 1
    print(lis2);
    it = lis2.begin();
    assert(*it == 2);
    ++it;
    assert(*it == 1);
    ++it;
    assert(it == lis2.end());

    lis2.insert_after(lis2.before_begin(), -1);
    // -1, 2, 1
    print(lis2);
    it = lis2.begin();
    assert(*it == -1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 1);
    ++it;
    assert(it == lis2.end());

    lis2.erase_after(lis2.before_begin());
    // 2, 1
    print(lis2);
    it = lis2.begin();
    assert(*it == 2);
    ++it;
    assert(*it == 1);
    ++it;
    assert(it == lis2.end());

    lis2.emplace_front(-1);
    // -1, 2, 1
    print(lis2);
    it = lis2.begin();
    assert(*it == -1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 1);
    ++it;
    assert(it == lis2.end());

    lis2.erase_after(lis2.before_begin());
    lis2.erase_after(lis2.before_begin());
    // 1
    print(lis2);
    it = lis2.begin();
    assert(*it == 1);
    ++it;
    assert(it == lis2.end());

    lis2.insert_after(lis2.begin(), lis.begin(), lis.end());
    // 1, 2, 1
    print(lis2);
    it = lis2.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 1);
    ++it;
    assert(it == lis2.end());

    lis2.sort();
    // 1, 1, 2
    print(lis2);
    it = lis2.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(it == lis2.end());

    lis.sort();
    // 1, 2
    print(lis);
    it = lis.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(it == lis.end());

    // 1, 1, 2
    print(lis2);
    it = lis2.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(it == lis2.end());

    lis2.reverse();
    // 2, 1, 1
    print(lis2);
    it = lis2.begin();
    assert(*it == 2);
    ++it;
    assert(*it == 1);
    ++it;
    assert(*it == 1);
    ++it;
    assert(it == lis2.end());

    lis2.reverse();
    // 1, 1, 2
    print(lis2);
    it = lis2.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(it == lis2.end());

    lis.merge(lis2);
    assert(lis2.empty());
    // 1, 1, 1, 2, 2
    print(lis);
    it = lis.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 1);
    ++it;
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 2);
    ++it;
    assert(it == lis.end());

    lis.remove(1);
    // 2, 2
    print(lis);
    it = lis.begin();
    assert(*it == 2);
    ++it;
    assert(*it == 2);
    ++it;
    assert(it == lis.end());

    lis.clear();
    // empty
    it = lis.begin();
    assert(it == lis.end());
    assert(lis.empty());

    FL chars;
    chars.assign(3, (char)99);
    assert(chars.front() == 99);
    // 99, 99, 99
    print(chars);
    it = chars.begin();
    assert(*it == 99);
    ++it;
    assert(*it == 99);
    ++it;
    assert(*it == 99);
    ++it;
    assert(it == chars.end());

    lis2.emplace_front(1);
    lis2.emplace_front(2);
    // 2, 1
    print(lis2);
    it = lis2.begin();
    assert(*it == 2);
    ++it;
    assert(*it == 1);
    ++it;
    assert(it == lis2.end());

    chars.splice_after(chars.begin(), lis2);
    // 99, 2, 1, 99, 99
    print(chars);
    it = chars.begin();
    assert(*it == 99);
    ++it;
    assert(*it == 2);
    ++it;
    assert(*it == 1);
    ++it;
    assert(*it == 99);
    ++it;
    assert(*it == 99);
    ++it;
    assert(it == chars.end());
    assert(lis2.empty());

    it = chars.begin();
    ++it;
    lis2.splice_after(lis2.before_begin(), chars, it, chars.end());
    // 1, 99, 99
    print(lis2);
    it = lis2.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 99);
    ++it;
    assert(*it == 99);
    ++it;
    assert(it == lis2.end());

    // 99, 2
    print(chars);
    it = chars.begin();
    assert(*it == 99);
    ++it;
    assert(*it == 2);
    ++it;
    assert(it == chars.end());

    chars.splice_after(chars.before_begin(), lis2, lis2.before_begin(), lis2.end());
    // 1, 99, 99, 99, 2
    print(chars);
    it = chars.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 99);
    ++it;
    assert(*it == 99);
    ++it;
    assert(*it == 99);
    ++it;
    assert(*it == 2);
    ++it;
    assert(it == chars.end());

    it = chars.begin();
    it2 = it;
    ++it2;
    ++it2;
    ++it2;
    ++it2;
    chars.erase_after(it, it2);
    // 1, 2
    print(chars);
    it = chars.begin();
    assert(*it == 1);
    ++it;
    assert(*it == 2);
    ++it;
    assert(it == chars.end());

    return 0;
} // main
