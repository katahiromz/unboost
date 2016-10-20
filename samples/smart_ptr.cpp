// smart_ptr.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_SMART_PTR
#include "unboost.hpp"

//////////////////////////////////////////////////////////////////////////////

int count = 0;

struct Foo {
    Foo() {
        std::cout << "Foo...\n";
        count++;
    }
    ~Foo() {
        std::cout << "~Foo...\n";
        count++;
    }
};

struct D { 
    void operator()(Foo* p) const {
        std::cout << "Call delete for Foo object...\n";
        delete p;
        count++;
    }
};

//////////////////////////////////////////////////////////////////////////////

typedef std::shared_ptr<int> IntPtr;
 
void output(const std::string& msg, int* pInt)
{
    std::cout << msg << *pInt << "\n";
    assert(*pInt == 42);
}

//////////////////////////////////////////////////////////////////////////////

void fun(std::shared_ptr<int> sp)
{
    std::cout << "fun: sp.use_count() == " << sp.use_count() << std::endl;
    assert(sp.use_count() == 2);
    assert(!sp.unique());
}

//////////////////////////////////////////////////////////////////////////////

struct Foo2 {
    int n1;
    int n2; 
    Foo2(int a, int b) : n1(a), n2(b) {}
};

//////////////////////////////////////////////////////////////////////////////

int main(void) {
    std::cout << "smart ptr" << std::endl;

    {
        assert(count == 0);
        unboost::shared_ptr<Foo> sh1;
        assert(sh1.use_count() == 0);
        {
            unboost::shared_ptr<Foo> sh2(new Foo);
            assert(count == 1);
            {
                unboost::shared_ptr<Foo> sh3(sh2);
                assert(sh2.use_count() == 2);
                assert(sh3.use_count() == 2);
                assert(count == 1);
                {
                    unboost::shared_ptr<Foo> sh4(new Foo, D());
                    assert(count == 2);
                    assert(sh4.use_count() == 1);
                }
            }
            assert(sh2.use_count() == 1);
        }
        assert(sh1.use_count() == 0);
    }
    {
        int* pInt = new int(42);
        IntPtr pShared(new int(42));

        output("Naked pointer ", pInt);
        output("Shared pointer with get() ", pShared.get());

        delete pInt;
    }
    {
        unboost::shared_ptr<int> sp1 = unboost::make_shared<int>(5);
        unboost::cout << "sp1.use_count() == " << sp1.use_count() << unboost::endl;
        assert(sp1.use_count() == 1);
        assert(sp1.unique());
        fun(sp1);
        assert(sp1.use_count() == 1);
        assert(sp1.unique());
    }
    {
        IntPtr ptr;
        assert(!ptr);
        ptr = IntPtr(new int(7));
        assert(ptr);
    }
    {
        unboost::shared_ptr<Foo2> p1 = unboost::make_shared<Foo2>(1, 2);

        unboost::shared_ptr<int> p2(p1, &p1->n1);
        unboost::shared_ptr<int> p3(p1, &p1->n2);
        assert(p2 < p3);
        assert(!(p2 > p3));
        assert(p2.owner_before(p3));
        assert(!p3.owner_before(p2));

        unboost::weak_ptr<int> w2(p2);
        unboost::weak_ptr<int> w3(p3);
        assert(!w2.owner_before(w3));
        assert(!w3.owner_before(w2));
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
