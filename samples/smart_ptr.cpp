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
}

//////////////////////////////////////////////////////////////////////////////

int main(void) {
    std::cout << "smart ptr" << std::endl;

    {
        assert(count == 0);
        unboost::shared_ptr<Foo> sh1; 
        unboost::shared_ptr<Foo> sh2(new Foo);
        assert(count == 1);
        unboost::shared_ptr<Foo> sh3(sh2);
        assert(sh2.use_count() == 2);
        assert(sh3.use_count() == 2);
        assert(count == 1);
        unboost::shared_ptr<Foo> sh4(new Foo, D());
        assert(count == 2);
    }
    {
        int* pInt = new int(42);
        IntPtr pShared(new int(42));

        output("Naked pointer ", pInt);
        // output("Shared pointer ", pShared); // compiler error
        output("Shared pointer with get() ", pShared.get());

        delete pInt;
    }
    {
        unboost::shared_ptr<int> sp1 = unboost::make_shared<int>(5);
        unboost::cout << "sp1.use_count() == " << sp1.use_count() << unboost::endl;
        assert(sp1.use_count() == 1);
        fun(sp1);
        assert(sp1.use_count() == 1);
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////
