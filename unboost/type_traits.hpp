// type_traits.hpp --- Unboost type traits and R-value reference
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_TYPE_TRAITS_HPP_
#define UNBOOST_TYPE_TRAITS_HPP_

#include <unboost/core.hpp>

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
    #include <utility>          // for std::move
    #include <type_traits>
    namespace unboost {
        using std::move;
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
    #define UNBOOST_RVALREF_TYPE(type)  type&&
    #define UNBOOST_RVALREF(value)      value
#elif defined(UNBOOST_USE_BOOST_TYPE_TRAITS)
    #include <boost/utility.hpp>    // for boost::move
    #include <boost/type_traits.hpp>
    namespace unboost {
        using boost::move;
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
        using boost::is_trivial;
        using boost::is_trivially_copyable;
        using boost::is_standard_layout;
        using boost::is_pod;
        using boost::is_literal_type;
        using boost::is_empty;
        using boost::is_polymorphic;
        using boost::is_abstract;
        using boost::is_signed;
        using boost::is_unsigned;
        using boost::is_constructible;
        using boost::is_trivially_constructible;
        using boost::is_nothrow_constructible;
        using boost::is_default_constructible;
        using boost::is_trivially_default_constructible;
        using boost::is_nothrow_default_constructible;
        using boost::is_copy_constructible;
        using boost::is_trivially_copy_constructible;
        using boost::is_nothrow_copy_constructible;
        using boost::is_move_constructible;
        using boost::is_trivially_move_constructible;
        using boost::is_nothrow_move_constructible;
        using boost::is_assignable;
        using boost::is_trivially_assignable;
        using boost::is_nothrow_assignable;
        using boost::is_copy_assignable;
        using boost::is_trivially_copy_assignable;
        using boost::is_nothrow_copy_assignable;
        using boost::is_move_assignable;
        using boost::is_trivially_move_assignable;
        using boost::is_nothrow_move_assignable;
        using boost::is_destructible;
        using boost::is_trivially_destructible;
        using boost::is_nothrow_destructible;
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
        using boost::underlying_type;
        using boost::result_of;

        #ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
            // R-value reference
            template <typename T>
            struct rvalue_ref {
                T& m_ref;
                rvalue_ref(T& ref) : m_ref(ref) { }
            };
            #define UNBOOST_RVALREF_TYPE(type)  unboost::rvalue_ref<type>
            #define UNBOOST_RVALREF(value)      (value).m_ref

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
                typedef UNBOOST_RVALREF_TYPE(T) type;
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
            #define UNBOOST_RVALREF_TYPE(type)  type&&
            #define UNBOOST_RVALREF(value)      value
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
        #define UNBOOST_RVALREF_TYPE(type)  unboost::rvalue_ref<type>
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

        template <typename T>
        struct is_integral : public false_type { };
        template <typename T>
        struct is_integral<const T> : public is_integral<T> { };
        template <typename T>
        struct is_integral<volatile const T> : public is_integral<T>{ };
        template <typename T>
        struct is_integral<volatile T> : public is_integral<T> { };

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

        template <typename T>
        struct is_floating_point : integral_constant<
            bool,
            is_same<float, typename remove_cv<T>::type>::value  ||
            is_same<double, typename remove_cv<T>::type>::value  ||
            is_same<long double, typename remove_cv<T>::type>::value> { };

        template <typename>
        struct is_array : public false_type { };
        template <typename T, size_t N>
        struct is_array<T[N]> : public true_type { };
        template <typename T>
        struct is_array<T[]> : public true_type { };

        // FIXME: is_enum, is_union, is_class, is_function

        template <typename T>
        struct _is_pointer_helper     : false_type { };
        template <typename T>
        struct _is_pointer_helper<T*> : true_type { };
        template <typename T>
        struct is_pointer : _is_pointer_helper<typename remove_cv<T>::type> { };

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

        template <typename T>
        struct is_const : false_type { };
        template <typename T>
        struct is_const<const T> : true_type { };

        template <typename T>
        struct is_volatile : false_type { };
        template <typename T>
        struct is_volatile<volatile T> : true_type { };

        // FIXME: is_trivial, is_trivially_copyable
        // FIXME: is_standard_layout, is_pod, is_literal_type
        // FIXME: is_empty, is_polymorphic, is_abstract
        // FIXME: is_signed, is_unsigned
        // FIXME: operations, alignment_of

        template <typename T>
        struct rank : integral_constant<size_t, 0> { };

        template <typename T>
        struct rank<T[]> :
            public integral_constant<size_t, rank<T>::value + 1> { };

        template<class T, size_t N>
        struct rank<T[N]> :
            public integral_constant<size_t, rank<T>::value + 1> { };

        template <typename T, unsigned N = 0>
        struct extent : integral_constant<size_t, 0> { };

        template <typename T>
        struct extent<T[], 0> : integral_constant<size_t, 0> { };

        template <typename T, unsigned N>
        struct extent<T[], N> :
            integral_constant<size_t, extent<T, N - 1>::value> { };

        template <typename T, size_t N>
        struct extent<T[N], 0> : integral_constant<size_t, N> { };

        template <typename T, size_t I, unsigned N>
        struct extent<T[I], N> :
            integral_constant<size_t, extent<T, N - 1>::value> { };

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

        template <typename T>
        struct remove_extent<T[]> { typedef T type; };

        template <typename T, size_t N>
        struct remove_extent<T[N]> { typedef T type; };

        // FIXME: transformations

        template<bool B, typename T = void>
        struct enable_if { };

        template <typename T>
        struct enable_if<true, T> { typedef T type; };

        template <bool B, typename T, typename F>
        struct conditional { typedef T type; };

        template <typename T, typename F>
        struct conditional<false, T, F> { typedef F type; };

        // FIXME: common_type, underlying_type, result_of
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_TYPE_TRAITS_HPP_
