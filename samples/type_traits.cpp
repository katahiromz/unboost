// type_traits.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#define UNBOOST_USE_TYPE_TRAITS
#include <unboost.hpp>

//////////////////////////////////////////////////////////////////////////////

struct A { };

//////////////////////////////////////////////////////////////////////////////

int check = 0;
struct foo
{
    void m() {
        std::cout << "Non-cv\n";
        check = 1;
    }
    void m() const {
        std::cout << "Const\n";
        check = -1;
    }
};
 
template <class T>
void call_m()
{
    T().m();
}

//////////////////////////////////////////////////////////////////////////////

int main(void) {
    std::cout << "type_traits" << std::endl;

    {
        typedef std::integral_constant<int, 2> two_t;
        typedef std::integral_constant<int, 4> four_t;
        assert(two_t::value * 2 == four_t::value);

        enum my_e {
           e1,
           e2
        };
        typedef std::integral_constant<my_e, e1> my_e_e1;
        typedef std::integral_constant<my_e, e2> my_e_e2;

        assert(std::is_same<my_e_e2, my_e_e2>::value);
    }
    {
        assert(std::is_void<void>::value);
        assert(!std::is_void<int>::value);
    }
    {
        assert(!std::is_integral<A>::value);
        assert(!std::is_integral<float>::value);
        assert(std::is_integral<int>::value);
    }
    {
        assert(!std::is_floating_point<A>::value);
        assert(std::is_floating_point<float>::value);
        assert(!std::is_floating_point<int>::value);
    }
    {
        assert(!std::is_array<A>::value);
        assert(std::is_array<A[3]>::value);
        assert(!std::is_array<float>::value);
        assert(!std::is_array<int>::value);
        assert(std::is_array<int[3]>::value);
    }
    {
        assert(!std::is_pointer<A>::value);
        assert(std::is_pointer<A*>::value);
        assert(!std::is_pointer<float>::value);
        assert(!std::is_pointer<int>::value);
        assert(std::is_pointer<int*>::value);
        assert(std::is_pointer<int**s>::value);
    }
    {
        assert(!std::is_lvalue_reference<A>::value);
        assert(std::is_lvalue_reference<A&>::value);
        assert(!std::is_lvalue_reference<UNBOOST_RVALREF_TYPE(A) >::value);
        assert(!std::is_lvalue_reference<int>::value);
        assert(std::is_lvalue_reference<int&>::value);
        assert(!std::is_lvalue_reference<UNBOOST_RVALREF_TYPE(int) >::value);
    }
    {
        assert(!std::is_rvalue_reference<A>::value);
        assert(!std::is_rvalue_reference<A&>::value);
        assert(std::is_rvalue_reference<UNBOOST_RVALREF_TYPE(A) >::value);
        assert(!std::is_rvalue_reference<int>::value);
        assert(!std::is_rvalue_reference<int&>::value);
        assert(std::is_rvalue_reference<UNBOOST_RVALREF_TYPE(int) >::value);
    }
    {
        assert(!std::is_reference<A>::value);
        assert(std::is_reference<A&>::value);
        assert(std::is_reference<UNBOOST_RVALREF_TYPE(A) >::value);
        assert(!std::is_reference<int>::value);
        assert(std::is_reference<int&>::value);
        assert(std::is_reference<UNBOOST_RVALREF_TYPE(int) >::value);
    }
    {
        assert(!std::is_const<int>::value);
        assert(std::is_const<const int>::value);
    }
    {
        assert(!std::is_volatile<int>::value);
        assert(std::is_volatile<volatile int>::value);
    }
    {
        assert(std::extent<int[3]>::value == 3);
        assert(std::extent<int[3][4]>::value == 3);
        assert(std::extent<int[3][4], 1>::value == 4);
        assert(std::extent<int[3][4], 2>::value == 0);
        assert(std::extent<int[]>::value == 0);
    }
    {
        assert(std::is_same<int, int>::value);
        assert(!std::is_same<int, float>::value);
    }
    {
        typedef std::remove_cv<const int>::type type1;
        typedef std::remove_cv<volatile int>::type type2;
        typedef std::remove_cv<const volatile int>::type type3;
        typedef std::remove_cv<const volatile int*>::type type4;
        typedef std::remove_cv<int * const volatile>::type type5;
        assert(std::is_same<int, type1>::value);
        assert(std::is_same<int, type2>::value);
        assert(std::is_same<int, type3>::value);
        assert(std::is_same<const volatile int*, type4>::value);
        assert(std::is_same<int*, type5>::value);
    }
    {
        check = 0;
        call_m<foo>();
        assert(check == 1);
        check = 0;
        call_m<std::add_const<foo>::type>();
        assert(check == -1);
    }
    {
        assert(std::is_same<std::remove_reference<int&>, int>::value);
        assert(std::is_same<std::add_lvalue_reference<int>, int&>::value);
        assert(std::is_same<std::add_rvalue_reference<int>, UNBOOST_RVALREF_TYPE(int) >::value);
        assert(std::is_same<std::remove_pointer<int*>, int>::value);
        assert(std::is_same<std::add_pointer<int>, int*>::value);
    }
    return 0;
}
