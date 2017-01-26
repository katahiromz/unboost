// type_traits.cpp --- Unboost sample
//////////////////////////////////////////////////////////////////////////////

#ifdef CXX11
    #include <type_traits>
#elif defined(BOOST)
    #include <boost/type_traits.hpp>
#else   // Unboost
    #include <unboost/type_traits.hpp>
#endif

#include <iostream>
#include <cassert>

#ifdef CXX11
    #define UNBOOST_RV_REF(type)  type&&
#elif defined(BOOST)
    #define UNBOOST_RV_REF(type)  type&&
#else   // Unboost
    //
#endif

//////////////////////////////////////////////////////////////////////////////

struct A { };

//////////////////////////////////////////////////////////////////////////////

int check = 0;
struct foo {
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
void call_m() {
    T().m();
}

//////////////////////////////////////////////////////////////////////////////

int main(void) {
    std::cout << "type_traits" << std::endl;

#ifdef CXX11
    using namespace std;
#elif defined(BOOST)
    using namespace boost;
#else   // Unboost
    using namespace unboost;
#endif

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
#ifndef __WATCOMC__
    {
        assert(!is_array<A>::value);
        assert(is_array<A[3]>::value);
        assert(!is_array<float>::value);
        assert(!is_array<int>::value);
        assert(is_array<int[3]>::value);
    }
#endif
    {
        assert(!is_pointer<A>::value);
        assert(is_pointer<A*>::value);
        assert(is_pointer<const A*>::value);
        assert(is_pointer<volatile A*>::value);
        assert(!is_pointer<float>::value);
        assert(!is_pointer<int>::value);
        assert(is_pointer<int*>::value);
        assert(is_pointer<int**>::value);
    }
    {
        assert(!is_lvalue_reference<A>::value);
        assert(is_lvalue_reference<A&>::value);
        assert(!is_lvalue_reference<UNBOOST_RV_REF(A) >::value);
        assert(!is_lvalue_reference<int>::value);
        assert(is_lvalue_reference<int&>::value);
        assert(!is_lvalue_reference<UNBOOST_RV_REF(int) >::value);
    }
    {
        assert(!is_rvalue_reference<A>::value);
        assert(!is_rvalue_reference<A&>::value);
        assert(is_rvalue_reference<UNBOOST_RV_REF(A) >::value);
        assert(!is_rvalue_reference<int>::value);
        assert(!is_rvalue_reference<int&>::value);
        assert(is_rvalue_reference<UNBOOST_RV_REF(int) >::value);
    }
    {
        assert(!is_reference<A>::value);
        assert(is_reference<A&>::value);
        assert(is_reference<UNBOOST_RV_REF(A) >::value);
        assert(!is_reference<int>::value);
        assert(is_reference<int&>::value);
        assert(is_reference<UNBOOST_RV_REF(int) >::value);
    }
#ifndef UNBOOST_NO_CV_INFO
    {
        assert(!is_const<int>::value);
        assert(is_const<const int>::value);
    }
    {
        assert(!is_volatile<int>::value);
        assert(is_volatile<volatile int>::value);
    }
#endif
#ifndef __WATCOMC__
#ifndef UNBOOST_OLD_COMPILER
    {
        std::cout << "extent<int[3]>::value: " << extent<int[3]>::value << std::endl;
        std::cout << "extent<int[3][4]>::value: " << extent<int[3][4]>::value << std::endl;
        std::cout << "extent<int[3][4], 1>::value: " << extent<int[3][4], 1>::value << std::endl;
        std::cout << "extent<int[3][4], 2>::value: " << extent<int[3][4], 2>::value << std::endl;
        assert(extent<int[3]>::value == 3);
        assert(extent<int[3][4]>::value == 3);
        assert((extent<int[3][4], 1>::value == 4));
        assert((extent<int[3][4], 2>::value == 0));
#ifdef UNBOOST_NO_EMPTY_ARRAY
        assert(extent<int[]>::value == 0);
#endif
    }
#endif
    {
        assert(rank<int[1][2][3]>::value == 3);
#ifndef UNBOOST_NO_EMPTY_ARRAY
        assert(rank<int[][2][3][4]>::value == 4);
#endif
        assert(rank<int>::value == 0);
    }
#endif  // ndef __WATCOMC__
    {
        assert((is_same<int, int>::value));
        assert(!(is_same<int, float>::value));
    }
#ifndef UNBOOST_NO_CV_INFO
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
#endif
    {
        assert((is_same<remove_reference<int&>::type, int>::value));
        assert((is_same<add_lvalue_reference<int>::type, int&>::value));
        assert((is_same<add_rvalue_reference<int>::type, UNBOOST_RV_REF(int) >::value));
        assert((is_same<remove_pointer<int*>::type, int>::value));
        assert((is_same<add_pointer<int>::type, int*>::value));
    }
    {
        typedef common_type<int, int>::type int_ct;
        typedef common_type<int, char>::type ic_ct;
        typedef common_type<int, short>::type is_ct;
        typedef common_type<unsigned int, unsigned int>::type uu_ct;
        typedef common_type<short, unsigned int>::type su_ct;
        typedef common_type<double, int>::type di_ct1;
        typedef common_type<double, char>::type di_ct2;
        typedef common_type<int, double>::type di_ct3;
        typedef common_type<char, double>::type di_ct4;
        assert((is_same<int_ct, int>::value));
        assert((is_same<ic_ct, int>::value));
        assert((is_same<is_ct, int>::value));
        assert((is_same<uu_ct, unsigned int>::value));
        assert((is_same<su_ct, unsigned int>::value));
        assert((is_same<di_ct1, double>::value));
        assert((is_same<di_ct2, double>::value));
        assert((is_same<di_ct3, double>::value));
        assert((is_same<di_ct4, double>::value));
    }

    std::cout << "success" << std::endl;
    return 0;
} // main
