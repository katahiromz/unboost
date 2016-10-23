// type_traits.hpp --- Unboost type traits and R-value reference
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_TYPE_TRAITS_HPP_
#define UNBOOST_TYPE_TRAITS_HPP_

#include "unboost.hpp"

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_TYPE_TRAITS) + defined(UNBOOST_USE_BOOST_TYPE_TRAITS) + defined(UNBOOST_USE_UNBOOST_TYPE_TRAITS)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_TYPE_TRAITS
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_TYPE_TRAITS
    #else
        #define UNBOOST_USE_UNBOOST_TYPE_TRAITS
    #endif
#endif

// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_TYPE_TRAITS
    #include <utility>          // for std::move, std::forward
    #include <type_traits>
    namespace unboost {
        using std::move;
        using std::forward;
        using std::integral_constant;
        using std::true_type;
        using std::false_type;
        using std::is_void;
        using std::is_integral;
        using std::is_floating_point;
        using std::is_array;
        using std::is_enum;
        using std::is_union;
        using std::is_class;
        using std::is_function;
        using std::is_pointer;
        using std::is_lvalue_reference;
        using std::is_rvalue_reference;
        using std::is_member_object_pointer;
        using std::is_member_function_pointer;
        using std::is_fundamental;
        using std::is_arithmetic;
        using std::is_scalar;
        using std::is_object;
        using std::is_compound;
        using std::is_reference;
        using std::is_member_pointer;
        using std::is_const;
        using std::is_volatile;
        using std::is_trivial;
        using std::is_trivially_copyable;
        using std::is_standard_layout;
        using std::is_pod;
        using std::is_literal_type;
        using std::is_empty;
        using std::is_polymorphic;
        using std::is_abstract;
        using std::is_signed;
        using std::is_unsigned;
        using std::is_constructible;
        using std::is_trivially_constructible;
        using std::is_nothrow_constructible;
        using std::is_default_constructible;
        using std::is_trivially_default_constructible;
        using std::is_nothrow_default_constructible;
        using std::is_copy_constructible;
        using std::is_trivially_copy_constructible;
        using std::is_nothrow_copy_constructible;
        using std::is_move_constructible;
        using std::is_trivially_move_constructible;
        using std::is_nothrow_move_constructible;
        using std::is_assignable;
        using std::is_trivially_assignable;
        using std::is_nothrow_assignable;
        using std::is_copy_assignable;
        using std::is_trivially_copy_assignable;
        using std::is_nothrow_copy_assignable;
        using std::is_move_assignable;
        using std::is_trivially_move_assignable;
        using std::is_nothrow_move_assignable;
        using std::is_destructible;
        using std::is_trivially_destructible;
        using std::is_nothrow_destructible;
        using std::has_virtual_destructor;
        using std::alignment_of;
        using std::rank;
        using std::extent;
        using std::is_same;
        using std::is_base_of;
        using std::is_convertible;
        using std::remove_cv;
        using std::remove_const;
        using std::remove_volatile;
        using std::add_cv;
        using std::add_const;
        using std::add_volatile;
        using std::remove_reference;
        using std::add_lvalue_reference;
        using std::add_rvalue_reference;
        using std::remove_pointer;
        using std::add_pointer;
        using std::make_signed;
        using std::make_signed;
        using std::remove_extent;
        using std::remove_all_extents;
        using std::aligned_storage;
        using std::aligned_storage;
        using std::decay;
        using std::enable_if;
        using std::conditional;
        using std::common_type;
        using std::underlying_type;
        using std::result_of;
    } // namespace unboost

    #define UNBOOST_RVALREF_TYPE(...)     __VA_ARGS__&&
    #define UNBOOST_RVALREF(value)        value
#elif defined(UNBOOST_USE_BOOST_TYPE_TRAITS)
    #include <boost/utility.hpp>    // for boost::move, boost::forward
    #include <boost/type_traits.hpp>

    namespace unboost {
        //using boost::move;
        //using boost::forward;
        using boost::integral_constant;
        using boost::true_type;
        using boost::false_type;
        using boost::is_void;
        using boost::is_integral;
        using boost::is_floating_point;
        using boost::is_array;
        using boost::is_enum;
        using boost::is_union;
        using boost::is_class;
        using boost::is_function;
        using boost::is_pointer;
        using boost::is_lvalue_reference;
        //using boost::is_rvalue_reference;
        using boost::is_member_object_pointer;
        using boost::is_member_function_pointer;
        using boost::is_fundamental;
        using boost::is_arithmetic;
        using boost::is_scalar;
        using boost::is_object;
        using boost::is_compound;
        //using boost::is_reference;
        using boost::is_member_pointer;
        using boost::is_const;
        using boost::is_volatile;
        using boost::is_pod;
        using boost::is_empty;
        using boost::is_polymorphic;
        using boost::is_abstract;
        using boost::is_signed;
        using boost::is_unsigned;
        using boost::is_constructible;
        using boost::is_default_constructible;
        using boost::is_copy_constructible;
        using boost::is_nothrow_move_constructible;
        using boost::is_assignable;
        using boost::is_copy_assignable;
        using boost::is_nothrow_move_assignable;
        using boost::is_destructible;
        using boost::has_virtual_destructor;
        using boost::alignment_of;
        using boost::rank;
        using boost::extent;
        using boost::is_same;
        using boost::is_base_of;
        using boost::is_convertible;
        using boost::remove_cv;
        using boost::remove_const;
        using boost::remove_volatile;
        using boost::add_cv;
        using boost::add_const;
        using boost::add_volatile;
        //using boost::remove_reference;
        //using boost::add_lvalue_reference;
        //using boost::add_rvalue_reference;
        using boost::remove_pointer;
        using boost::add_pointer;
        using boost::make_signed;
        using boost::make_signed;
        using boost::remove_extent;
        using boost::remove_all_extents;
        using boost::aligned_storage;
        using boost::aligned_storage;
        using boost::decay;
        using boost::enable_if;
        using boost::conditional;
        using boost::common_type;

        #ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
            // R-value reference
            template <typename T>
            struct rvalue_ref {
                T& m_ref;
                rvalue_ref(T& ref) : m_ref(ref) { }
            };

            #ifdef UNBOOST_OLD_BORLAND
                #define UNBOOST_RVALREF_TYPE(type) \
                    unboost::rvalue_ref<type > /**/
            #else
                #define UNBOOST_RVALREF_TYPE(...) \
                    unboost::rvalue_ref<__VA_ARGS__ > /**/
            #endif
            #define UNBOOST_RVALREF(value)          (value).m_ref

            template <typename T>
            struct remove_reference { typedef T type; }
            template <typename T>
            struct remove_reference<T&> { typedef T type; }
            template <typename T>
            struct remove_reference<UNBOOST_RVALREF_TYPE(T) >
            { typedef T type; }

            template <typename T>
            inline typename rvalue_ref<remove_reference<T>::type> move(T& t) {
                rvalue_ref ref(t);
                return ref;
            }

            template <typename T>
            inline UNBOOST_RVALREF_TYPE(T)
            forward(typename remove_reference<T>::type& t) {
                return static_cast<UNBOOST_RVALREF_TYPE(T) >(t);
            }
            template <typename T>
            inline UNBOOST_RVALREF_TYPE(T)
            forward(UNBOOST_RVALREF_TYPE(typename remove_reference<T>::type) t) {
                return static_cast<UNBOOST_RVALREF_TYPE(T) >(t);
            }

            template <typename>
            struct is_rvalue_reference : public false_type { };
            template <typename T>
            struct is_rvalue_reference<UNBOOST_RVALREF_TYPE(T) > : public true_type { };

            template <typename T>
            struct is_reference : false_type { };
            template <typename T>
            struct is_reference<T&> : true_type { };
            template <typename T>
            struct is_reference<UNBOOST_RVALREF_TYPE(T) > : true_type { };

            template <typename T>
            struct add_lvalue_reference {
                typedef T& type;
            };
            template <typename T>
            struct add_lvalue_reference<T&> {
                typedef T& type;
            };
            template <typename T>
            struct add_lvalue_reference<UNBOOST_RVALREF_TYPE(T) > {
                typedef T& type;
            };

            template <typename T>
            struct add_rvalue_reference {
                typedef UNBOOST_RVALREF_TYPE(T) type;
            };
            template <typename T>
            struct add_rvalue_reference<T&> {
                typedef T& type;
            };
            template <typename T>
            struct add_rvalue_reference<UNBOOST_RVALREF_TYPE(T) > {
                typedef UNBOOST_RVALREF_TYPE(T) type;
            };
        #else
            using boost::is_rvalue_reference;
            using boost::is_reference;
            using boost::remove_reference;
            using boost::add_lvalue_reference;
            using boost::add_rvalue_reference;
            #define UNBOOST_RVALREF_TYPE(...)       __VA_ARGS__&&
            #define UNBOOST_RVALREF(value)          value
        #endif
    } // namespace unboost
#elif defined(UNBOOST_USE_UNBOOST_TYPE_TRAITS)
    namespace unboost {
        // R-value reference
        template <typename T>
        struct rvalue_ref {
            T& m_ref;
            rvalue_ref(T& ref) : m_ref(ref) { }
        };

        #ifdef UNBOOST_OLD_BORLAND
            #define UNBOOST_RVALREF_TYPE(type) \
                unboost::rvalue_ref<type > /**/
        #else
            #define UNBOOST_RVALREF_TYPE(...) \
                unboost::rvalue_ref<__VA_ARGS__ > /**/
        #endif
        #define UNBOOST_RVALREF(value)      (value).m_ref

        template <typename T>
        struct remove_reference { typedef T type; };
        template <typename T>
        struct remove_reference<T&> { typedef T type; };
        template <typename T>
        struct remove_reference<UNBOOST_RVALREF_TYPE(T) > { typedef T type; };

        template <typename T>
        inline rvalue_ref<typename remove_reference<T>::type>
        move(T& t) {
            rvalue_ref<T> ref(t);
            return ref;
        }

        template <typename T>
        inline UNBOOST_RVALREF_TYPE(T)
        forward(typename remove_reference<T>::type& t) {
            return static_cast<UNBOOST_RVALREF_TYPE(T) >(t);
        }
        template <typename T>
        inline UNBOOST_RVALREF_TYPE(T)
        forward(UNBOOST_RVALREF_TYPE(typename remove_reference<T>::type) t) {
            return static_cast<UNBOOST_RVALREF_TYPE(T) >(t);
        }

        template <typename T, T v>
        struct integral_constant {
            typedef T value_type;
            typedef integral_constant<T, v> type;
            enum { value = (int)v };
            operator value_type() const { return (value_type)value; }
        };
        typedef integral_constant<bool, true> true_type;
        typedef integral_constant<bool, false> false_type;

        template <typename T, typename U>
        struct is_same : false_type { };

        template <typename T>
        struct is_same<T, T> : true_type { };

#ifndef UNBOOST_OLD_BORLAND
        template <typename T>
        struct remove_const          { typedef T type; };
        template <typename T>
        struct remove_const<const T> { typedef T type; };

        template <typename T>
        struct remove_volatile             { typedef T type; };
        template <typename T>
        struct remove_volatile<volatile T> { typedef T type; };

        template <typename T>
        struct remove_cv {
            typedef typename remove_const<T>::type no_const_type;
            typedef typename remove_volatile<no_const_type>::type type;
        };
#endif

        template <typename T>
        struct is_void : false_type { };
        template <>
        struct is_void<void> : true_type { };

        template <typename T>
        struct is_integral : public false_type { };
#ifndef UNBOOST_OLD_BORLAND
        template <typename T>
        struct is_integral<const T> : public is_integral<T> { };
        template <typename T>
        struct is_integral<volatile const T> : public is_integral<T>{ };
        template <typename T>
        struct is_integral<volatile T> : public is_integral<T> { };
#endif

        template <>
        struct is_integral<unsigned char> : public true_type { };
        template <>
        struct is_integral<unsigned short> : public true_type{ };
        template <>
        struct is_integral<unsigned int> : public true_type{ };
        template <>
        struct is_integral<unsigned long> : public true_type{ };

        template <>
        struct is_integral<signed char> : public true_type { };
        template <>
        struct is_integral<short> : public true_type { };
        template <>
        struct is_integral<int> : public true_type { };
        template <>
        struct is_integral<long> : public true_type { };

        template <>
        struct is_integral<char> : public true_type { };
        template <>
        struct is_integral<bool> : public true_type { };

        template <>
        struct is_integral<wchar_t> : public true_type { };

        template <>
        struct is_integral<unsigned __int64> : public true_type { };
        template <>
        struct is_integral<__int64> : public true_type { };

#ifdef UNBOOST_OLD_BORLAND
        template <typename T>
        struct is_floating_point {
            typedef bool value_type;
            enum {
                value = (is_same<float, T>::value || is_same<double, T>::value ||
                         is_same<long double, T>::value)
            };
            operator value_type() const { return (value_type)value; }
        };
#else
        template <typename T>
        struct is_floating_point {
            typedef bool value_type;
            enum {
                value = (is_same<float, typename remove_cv<T>::type>::value ||
                         is_same<double, typename remove_cv<T>::type>::value ||
                         is_same<long double, typename remove_cv<T>::type>::value)
            };
            operator value_type() const { return (value_type)value; }
        };
#endif

        template <typename>
        struct is_array : public false_type { };
        template <typename T, size_t N>
        struct is_array<T[N]> : public true_type { };
#ifndef UNBOOST_OLD_BORLAND
        template <typename T>
        struct is_array<T[]> : public true_type { };
#endif

        // FIXME: is_enum, is_union, is_class, is_function

        template <typename T>
        struct _is_pointer_helper     : false_type { };
        template <typename T>
        struct _is_pointer_helper<T*> : true_type { };
#ifndef UNBOOST_OLD_BORLAND
        template <typename T>
        struct is_pointer : _is_pointer_helper<typename remove_cv<T>::type> { };
#else
        template <typename T>
        struct is_pointer : _is_pointer_helper<T> { };
#endif

        template <typename>
        struct is_lvalue_reference : public false_type { };
        template <typename T>
        struct is_lvalue_reference<T&> : public true_type { };

        template <typename>
        struct is_rvalue_reference : public false_type { };
        template <typename T>
        struct is_rvalue_reference<UNBOOST_RVALREF_TYPE(T) > : public true_type { };

        // FIXME: is_member_object_pointer, is_member_function_pointer

        template <typename T>
        struct is_arithmetic : integral_constant<bool,
            is_integral<T>::value || is_floating_point<T>::value> { };

        // FIXME: is_scalar, is_object, is_compound

        template <typename T>
        struct is_reference : false_type { };
        template <typename T>
        struct is_reference<T&> : true_type { };
        template <typename T>
        struct is_reference<UNBOOST_RVALREF_TYPE(T) > : true_type { };

        // FIXME: is_member_pointer

#ifndef UNBOOST_OLD_BORLAND
        template <typename T>
        struct is_const : false_type { };
        template <typename T>
        struct is_const<const T> : true_type { };

        template <typename T>
        struct is_volatile : false_type { };
        template <typename T>
        struct is_volatile<volatile T> : true_type { };
#endif

        // FIXME: is_trivial, is_trivially_copyable
        // FIXME: is_standard_layout, is_pod, is_literal_type
        // FIXME: is_empty, is_polymorphic, is_abstract
        // FIXME: is_signed

        template <typename T>
        struct is_unsigned : false_type { };

        template <>
        struct is_unsigned<unsigned char> : true_type { };
        template <>
        struct is_unsigned<unsigned short> : true_type { };
        template <>
        struct is_unsigned<unsigned int> : true_type { };
        template <>
        struct is_unsigned<unsigned long> : true_type { };
        template <>
        struct is_unsigned<unsigned long long> : true_type { };

        // FIXME: operations, alignment_of

        template <typename T>
        struct rank {
            // integral_constant<std::size_t, 0>
            typedef size_t value_type;
            typedef rank<T> type;
            enum { value = 0 };
            operator value_type() const { return (value_type)value; }
        };
        template <typename T, size_t N>
        struct rank<T[N]> {
            // integral_constant<std::size_t, rank<T>::value + 1>
            typedef size_t value_type;
            typedef rank<T[]> type;
            typedef rank<T> _refered_type;
            enum { value = _refered_type::value + 1 };
            operator value_type() const { return (value_type)value; }
        };
#ifndef UNBOOST_OLD_BORLAND
        template <typename T>
        struct rank<T[]> {
            // integral_constant<std::size_t, rank<T>::value + 1>
            typedef size_t value_type;
            typedef rank<T[]> type;
            typedef rank<T> _refered_type;
            enum { value = _refered_type::value + 1 };
            operator value_type() const { return (value_type)value; }
        };
#endif

#ifndef UNBOOST_OLD_BORLAND
        template <typename T, size_t N = 0>
        struct extent {
            // integral_constant<std::size_t, 0>
            typedef size_t value_type;
            typedef extent<T, N> type;
            enum { value = 0 };
            operator value_type() const { return (value_type)value; }
        };
        template <typename T, size_t N>
        struct extent<T[N], 0> {
            // integral_constant<std::size_t, N>
            typedef size_t value_type;
            typedef extent<T[N], 0> type;
            enum { value = N };
            operator value_type() const { return (value_type)value; }
        };
        template <typename T, unsigned I, size_t N>
        struct extent<T[I], N> : extent<T, N - 1> {
            // integral_constant<std::size_t, std::extent<T, N-1>::value>
        };
        template <typename T>
        struct extent<T[], 0> {
            // std::integral_constant<std::size_t, 0>
            typedef size_t value_type;
            typedef extent<T[], 0> type;
            enum { value = 0 };
            operator value_type() const { return (value_type)value; }
        };
        template <typename T, unsigned N>
        struct extent<T[], N> : extent<T, N - 1>::value {
            // integral_constant<std::size_t, std::extent<T, N-1>::value>
        };
#endif

        // FIXME: is_base_of, is_convertible

        template <typename T>
        struct add_const        { typedef const T type; };
        template <typename T>
        struct add_volatile     { typedef volatile T type; };

        template <typename T>
        struct add_cv {
            typedef typename add_const<T>::type const_added_type;
            typedef typename add_volatile<const_added_type>::type type;
        };

        template <typename T>
        struct add_lvalue_reference {
            typedef T& type;
        };
        template <typename T>
        struct add_lvalue_reference<T&> {
            typedef T& type;
        };
        template <typename T>
        struct add_lvalue_reference<UNBOOST_RVALREF_TYPE(T) > {
            typedef T& type;
        };

        template <typename T>
        struct add_rvalue_reference {
            typedef UNBOOST_RVALREF_TYPE(T) type;
        };
        template <typename T>
        struct add_rvalue_reference<T&> {
            typedef UNBOOST_RVALREF_TYPE(T) type;
        };
        template <typename T>
        struct add_rvalue_reference<UNBOOST_RVALREF_TYPE(T) > {
            typedef UNBOOST_RVALREF_TYPE(T) type;
        };

        template <typename T>
        struct remove_pointer                    { typedef T type; };
        template <typename T>
        struct remove_pointer<T*>                { typedef T type; };
        template <typename T>
        struct remove_pointer<T* const>          { typedef T type; };
        template <typename T>
        struct remove_pointer<T* volatile>       { typedef T type; };
        template <typename T>
        struct remove_pointer<T* const volatile> { typedef T type; };

        template <typename T>
        struct add_pointer {
            typedef typename remove_reference<T>::type* type;
        };

        // FIXME: make_signed, make_unsigned

        template <typename T>
        struct remove_extent { typedef T type; };
        template <typename T, size_t N>
        struct remove_extent<T[N]> { typedef T type; };
#ifndef UNBOOST_OLD_BORLAND
        template <typename T>
        struct remove_extent<T[]> { typedef T type; };
#endif

        // FIXME: transformations

        template<bool B, typename T = void>
        struct enable_if { };

        template <typename T>
        struct enable_if<true, T> { typedef T type; };

        template <bool B, typename T, typename F>
        struct conditional { typedef T type; };

        template <typename T, typename F>
        struct conditional<false, T, F> { typedef F type; };

        template <typename T1, typename T2 = T1>
        struct common_type {
#ifdef UNBOOST_OLD_BORLAND
            typedef T1 _type1;
            typedef T2 _type2;
#else
            typedef typename remove_cv<T1>::type _type1;
            typedef typename remove_cv<T2>::type _type2;
#endif
            typedef typename conditional<
                is_same<_type1, float>::value && is_same<_type2, float>::value,
                float, double>::type _floating;

            typedef typename conditional<
                sizeof(_type1) < sizeof(long long) && sizeof(_type2) < sizeof(long long),
                unsigned int, unsigned long long>::type _unsigned;

            typedef typename conditional<
                sizeof(_type1) >= sizeof(int) && sizeof(_type2) >= sizeof(int) &&
                is_unsigned<_type1>::value && is_unsigned<_type2>::value,
                _unsigned, int>::type _integral;

            typedef typename conditional<
                (is_floating_point<_type1>::value || is_floating_point<_type2>::value),
                _floating, _integral>::type type;
        };

        template <typename T>
        struct common_type<T, T> {
            typedef T type;
        };

        // FIXME: underlying_type, result_of
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_TYPE_TRAITS_HPP_
