// smart_ptr.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    #include <memory>
#elif defined(BOOST)
    #include <boost/smart_ptr.hpp>
    #include <boost/smart_ptr/make_shared.hpp>
    #include <boost/move/unique_ptr.hpp>
    #include <boost/pointer_cast.hpp>
#else   // Unboost
    #include <unboost/smart_ptr.hpp>
#endif

#include <iostream>
#include <cassert>

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

#ifdef CXX11
    typedef std::shared_ptr<int> IntPtr;
#elif defined(BOOST)
    typedef boost::shared_ptr<int> IntPtr;
#else   // Unboost
    typedef unboost::shared_ptr<int> IntPtr;
#endif
 
void output(const std::string& msg, int* pInt)
{
    std::cout << msg.c_str() << *pInt << "\n";
    assert(*pInt == 42);
}

//////////////////////////////////////////////////////////////////////////////

#ifdef BOOST
    template <typename T>
    struct array_deleter {
        typedef array_deleter<T> self_type;
        void operator()(T *ptr) {
            if (sizeof(T) > 0) {
                delete[] ptr;
            }
        }
        template <typename T2>
        void operator()(T2 *ptr) { }
    };
#endif

//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    void fun(std::shared_ptr<int> sp)
    {
        std::cout << "fun: sp.use_count() == " << sp.use_count() << std::endl;
        assert(sp.use_count() == 2);
        assert(!sp.unique());
    }
#elif defined(BOOST)
    void fun(boost::shared_ptr<int> sp)
    {
        std::cout << "fun: sp.use_count() == " << sp.use_count() << std::endl;
        assert(sp.use_count() == 2);
        assert(!sp.unique());
    }
#else   // Unboost
    void fun(unboost::shared_ptr<int> sp)
    {
        std::cout << "fun: sp.use_count() == " << sp.use_count() << std::endl;
        assert(sp.use_count() == 2);
        assert(!sp.unique());
    }
#endif

//////////////////////////////////////////////////////////////////////////////

struct Foo2 {
    int n1;
    int n2; 
    Foo2(int a, int b) : n1(a), n2(b) {}
};

//////////////////////////////////////////////////////////////////////////////

int main(void) {
    std::cout << "smart pointer" << std::endl;

#ifdef CXX11
    using std::shared_ptr;
    using std::make_shared;
#elif defined(BOOST)
    using boost::shared_ptr;
    using boost::make_shared;
#else   // Unboost
    using unboost::shared_ptr;
    using unboost::make_shared;
#endif

    {
        assert(count == 0);
        shared_ptr<Foo> sh1;
        assert(sh1.use_count() == 0);
        {
            shared_ptr<Foo> sh2(new Foo);
            assert(count == 1);
            {
                shared_ptr<Foo> sh3(sh2);
                assert(sh2.use_count() == 2);
                assert(sh3.use_count() == 2);
                assert(count == 1);
                {
                    shared_ptr<Foo> sh4(new Foo, D());
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
        shared_ptr<int> sp1 = make_shared<int>(5);
        std::cout << "sp1.use_count() == " << sp1.use_count() << std::endl;
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

#ifdef CXX11
    {
        std::unique_ptr<int[]> a(new int[32]);
        a[0] = 1;
        assert(a[0] == 1);
    }
#elif defined(BOOST)
    {
        boost::movelib::unique_ptr<int, array_deleter<int>> a(new int[32]);
        a[0] = 1;
        assert(a[0] == 1);
    }
#else   // Unboost
    {
        unboost::unique_array<int> a(new int[32]);
        a[0] = 1;
        assert(a[0] == 1);
    }
#endif  // Unboost

    std::cout << "success" << std::endl;
    return 0;
} // main

//////////////////////////////////////////////////////////////////////////////
