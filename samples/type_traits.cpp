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

    using namespace unboost;
    {
        typedef integral_constant<int, 2> two_t;
        typedef integral_constant<int, 4> four_t;
        assert(two_t::value * 2 == four_t::value);

        //enum my_e {
        //   e1,
        //   e2
        //};
        typedef integral_constant<int, 0> my_e_e1;
        typedef integral_constant<int, 0> my_e_e2;

        assert((is_same<my_e_e2, my_e_e2>::value));
    }
    {
        assert(is_void<void>::value);
        assert(!is_void<int>::value);
    }
    {
        assert(!is_integral<A>::value);
        assert(!is_integral<float>::value);
        assert(is_integral<int>::value);
    }
    {
        assert(!is_floating_point<A>::value);
        assert(is_floating_point<float>::value);
        assert(!is_floating_point<int>::value);
    }
    {
        assert(!is_array<A>::value);
        assert(is_array<A[3]>::value);
        assert(!is_array<float>::value);
        assert(!is_array<int>::value);
        assert(is_array<int[3]>::value);
    }
    {
        assert(!is_pointer<A>::value);
        assert(is_pointer<A*>::value);
        assert(!is_pointer<float>::value);
        assert(!is_pointer<int>::value);
        assert(is_pointer<int*>::value);
        assert(is_pointer<int**>::value);
    }
    {
        assert(!is_lvalue_reference<A>::value);
        assert(is_lvalue_reference<A&>::value);
        assert(!is_lvalue_reference<UNBOOST_RVALREF_TYPE(A) >::value);
        assert(!is_lvalue_reference<int>::value);
        assert(is_lvalue_reference<int&>::value);
        assert(!is_lvalue_reference<UNBOOST_RVALREF_TYPE(int) >::value);
    }
    {
        assert(!is_rvalue_reference<A>::value);
        assert(!is_rvalue_reference<A&>::value);
        assert(is_rvalue_reference<UNBOOST_RVALREF_TYPE(A) >::value);
        assert(!is_rvalue_reference<int>::value);
        assert(!is_rvalue_reference<int&>::value);
        assert(is_rvalue_reference<UNBOOST_RVALREF_TYPE(int) >::value);
    }
    {
        assert(!is_reference<A>::value);
        assert(is_reference<A&>::value);
        assert(is_reference<UNBOOST_RVALREF_TYPE(A) >::value);
        assert(!is_reference<int>::value);
        assert(is_reference<int&>::value);
        assert(is_reference<UNBOOST_RVALREF_TYPE(int) >::value);
    }
    {
        assert(!is_const<int>::value);
        assert(is_const<const int>::value);
    }
    {
        assert(!is_volatile<int>::value);
        assert(is_volatile<volatile int>::value);
    }
#ifndef __BORLANDC__
    {
        assert(extent<int[3]>::value == 3);
        assert(extent<int[3][4]>::value == 3);
        assert((extent<int[3][4], 1>::value == 4));
        assert((extent<int[3][4], 2>::value == 0));
        assert(extent<int[]>::value == 0);
    }
#endif
    {
        assert((is_same<int, int>::value));
        assert(!(is_same<int, float>::value));
    }
    {
        typedef remove_cv<const int>::type type1;
        typedef remove_cv<volatile int>::type type2;
        typedef remove_cv<const volatile int>::type type3;
        typedef remove_cv<const volatile int*>::type type4;
        typedef remove_cv<int * const volatile>::type type5;
        assert((is_same<int, type1>::value));
        assert((is_same<int, type2>::value));
        assert((is_same<int, type3>::value));
        assert((is_same<const volatile int*, type4>::value));
        assert((is_same<int*, type5>::value));
    }
    {
        check = 0;
        call_m<foo>();
        assert(check == 1);
        check = 0;
        call_m<add_const<foo>::type>();
        assert(check == -1);
    }
    {
        assert((is_same<remove_reference<int&>, int>::value));
        assert((is_same<add_lvalue_reference<int>, int&>::value));
        assert((is_same<add_rvalue_reference<int>, UNBOOST_RVALREF_TYPE(int) >::value));
        assert((is_same<remove_pointer<int*>, int>::value));
        assert((is_same<add_pointer<int>, int*>::value));
    }
    return 0;
}
