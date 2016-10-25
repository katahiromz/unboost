// emplace.hpp --- Unboost emplace
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_EMPLACE_HPP_
#define UNBOOST_EMPLACE_HPP_

#include "unboost.hpp"

#ifndef UNBOOST_EMPLACE
    namespace unboost {
        #ifdef UNBOOST_CXX11    // C++11
            //
            // emplace(obj, ...)
            //
            template <class T>
            inline void emplace(T& obj)
            {
                obj.emplace();
            }
            template <class T, typename ARG1>
            inline void emplace(T& obj, const ARG1& arg1)
            {
                obj.emplace(arg1);
            }
            template <class T, typename ARG1, typename ARG2>
            inline void emplace(T& obj, const ARG1& arg1, const ARG2& arg2)
            {
                obj.emplace(arg1, arg2);
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3)
            {
                obj.emplace(arg1, arg2, arg3);
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4)
            {
                obj.emplace(arg1, arg2, arg3, arg4);
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5)
            {
                obj.emplace(arg1, arg2, arg3, arg4, arg5);
            }

            //
            // emplace_at(obj, pos, ...)
            //
            template <class T, typename POS>
            inline void emplace_at(T& obj, const POS& pos)
            {
                obj.emplace(pos);
            }
            template <class T, typename POS, typename ARG1>
            inline void emplace_at(T& obj, const POS& pos, const ARG1& arg1)
            {
                obj.emplace(pos, arg1);
            }
            template <class T, typename POS, typename ARG1, typename ARG2>
            inline void emplace_at(T& obj, const POS& pos, const ARG1& arg1, const ARG2& arg2)
            {
                obj.emplace(pos, arg1, arg2);
            }
            template <class T, typename POS, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace_at(T& obj, const POS& pos, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3)
            {
                obj.emplace(pos, arg1, arg2, arg3);
            }
            template <class T, typename POS, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace_at(T& obj, const POS& pos, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4)
            {
                obj.emplace(pos, arg1, arg2, arg3, arg4);
            }
            template <class T, typename POS, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace_at(T& obj, const POS& pos, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5)
            {
                obj.emplace(pos, arg1, arg2, arg3, arg4, arg5);
            }

            //
            // emplace_front(obj, ...)
            //
            template <class T>
            inline void emplace_front(T& obj)
            {
                obj.emplace_front();
            }
            template <class T, typename ARG1>
            inline void emplace_front(T& obj, const ARG1& arg1)
            {
                obj.emplace_front(arg1);
            }
            template <class T, typename ARG1, typename ARG2>
            inline void emplace_front(T& obj, const ARG1& arg1, const ARG2& arg2)
            {
                obj.emplace_front(arg1, arg2);
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace_front(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3)
            {
                obj.emplace_front(arg1, arg2, arg3);
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace_front(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4)
            {
                obj.emplace_front(arg1, arg2, arg3, arg4);
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace_front(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5)
            {
                obj.emplace_front(arg1, arg2, arg3, arg4, arg5);
            }

            //
            // emplace_back(obj, ...)
            //
            template <class T>
            inline void emplace_back(T& obj)
            {
                obj.emplace_back();
            }
            template <class T, typename ARG1>
            inline void emplace_back(T& obj, const ARG1& arg1)
            {
                obj.emplace_back(arg1);
            }
            template <class T, typename ARG1, typename ARG2>
            inline void emplace_back(T& obj, const ARG1& arg1, const ARG2& arg2)
            {
                obj.emplace_back(arg1, arg2);
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace_back(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3)
            {
                obj.emplace_back(arg1, arg2, arg3);
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace_back(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4)
            {
                obj.emplace_back(arg1, arg2, arg3, arg4);
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace_back(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5)
            {
                obj.emplace_back(arg1, arg2, arg3, arg4, arg5);
            }
        #else   // Not C++11
            //
            // emplace(obj, ...)
            //
            template <class T>
            inline void emplace(T& obj)
            {
                typedef T::value_type value_type;
                obj.insert(value_type());
            }
            template <class T, typename ARG1>
            inline void emplace(T& obj, const ARG1& arg1)
            {
                typedef T::value_type value_type;
                obj.insert(value_type(arg1));
            }
            template <class T, typename ARG1, typename ARG2>
            inline void emplace(T& obj, const ARG1& arg1, const ARG2& arg2)
            {
                typedef T::value_type value_type;
                obj.insert(value_type(arg1, arg2));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3)
            {
                typedef T::value_type value_type;
                obj.insert(value_type(arg1, arg2, arg3));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4)
            {
                typedef T::value_type value_type;
                obj.insert(value_type(arg1, arg2, arg3, arg4));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5)
            {
                typedef T::value_type value_type;
                obj.insert(value_type(arg1, arg2, arg3, arg4, arg5));
            }

            //
            // emplace_at(obj, pos, ...)
            //
            template <class T, typename POS>
            inline void emplace_at(T& obj, const POS& pos)
            {
                typedef T::value_type value_type;
                obj.insert(pos, value_type());
            }
            template <class T, typename POS, typename ARG1>
            inline void emplace_at(T& obj, const POS& pos, const ARG1& arg1)
            {
                typedef T::value_type value_type;
                obj.insert(pos, value_type(arg1));
            }
            template <class T, typename POS, typename ARG1, typename ARG2>
            inline void emplace_at(T& obj, const POS& pos, const ARG1& arg1, const ARG2& arg2)
            {
                typedef T::value_type value_type;
                obj.insert(pos, value_type(arg1, arg2));
            }
            template <class T, typename POS, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace_at(T& obj, const POS& pos, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3)
            {
                typedef T::value_type value_type;
                obj.insert(pos, value_type(arg1, arg2, arg3));
            }
            template <class T, typename POS, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace_at(T& obj, const POS& pos, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4)
            {
                typedef T::value_type value_type;
                obj.insert(pos, value_type(arg1, arg2, arg3, arg4));
            }
            template <class T, typename POS, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace_at(T& obj, const POS& pos, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5)
            {
                typedef T::value_type value_type;
                obj.insert(pos, value_type(arg1, arg2, arg3, arg4, arg5));
            }

            //
            // emplace_front(obj, ...)
            //
            template <class T>
            inline void emplace_front(T& obj)
            {
                typedef T::value_type value_type;
                obj.push_front(value_type());
            }
            template <class T, typename ARG1>
            inline void emplace_front(T& obj, const ARG1& arg1)
            {
                typedef T::value_type value_type;
                obj.push_front(value_type(arg1));
            }
            template <class T, typename ARG1, typename ARG2>
            inline void emplace_front(T& obj, const ARG1& arg1, const ARG2& arg2)
            {
                typedef T::value_type value_type;
                obj.push_front(value_type(arg1, arg2));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace_front(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3)
            {
                typedef T::value_type value_type;
                obj.push_front(value_type(arg1, arg2, arg3));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace_front(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4)
            {
                typedef T::value_type value_type;
                obj.push_front(value_type(arg1, arg2, arg3, arg4));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace_front(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5)
            {
                typedef T::value_type value_type;
                obj.push_front(value_type(arg1, arg2, arg3, arg4, arg5));
            }

            //
            // emplace_back(obj, ...)
            //
            template <class T>
            inline void emplace_back(T& obj)
            {
                typedef T::value_type value_type;
                obj.push_back(value_type());
            }
            template <class T, typename ARG1>
            inline void emplace_back(T& obj, const ARG1& arg1)
            {
                typedef T::value_type value_type;
                obj.push_back(value_type(arg1));
            }
            template <class T, typename ARG1, typename ARG2>
            inline void emplace_back(T& obj, const ARG1& arg1, const ARG2& arg2)
            {
                typedef T::value_type value_type;
                obj.push_back(value_type(arg1, arg2));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace_back(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3)
            {
                typedef T::value_type value_type;
                obj.push_back(value_type(arg1, arg2, arg3));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace_back(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4)
            {
                typedef T::value_type value_type;
                obj.push_back(value_type(arg1, arg2, arg3, arg4));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace_back(T& obj, const ARG1& arg1, const ARG2& arg2, const ARG3& arg3, const ARG4& arg4, const ARG5& arg5)
            {
                typedef T::value_type value_type;
                obj.push_back(value_type(arg1, arg2, arg3, arg4, arg5));
            }
        #endif
    } // namespace unboost
#endif

#endif  // ndef UNBOOST_EMPLACE_HPP_
