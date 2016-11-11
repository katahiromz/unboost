// emplace.hpp --- Unboost emplace
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_EMPLACE_HPP_
#define UNBOOST_EMPLACE_HPP_

#include "unboost.hpp"
#include "rv_ref.hpp"   // for unboost::forward

// unboost::emplace(obj, ...)
// unboost::emplace_at(obj, pos, ...)
// unboost::emplace_front(obj, ...)
// unboost::emplace_back(obj, ...)

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
            inline void emplace(T& obj, ARG1 arg1)
            {
                obj.emplace(forward<ARG1>(arg1));
            }
            template <class T, typename ARG1, typename ARG2>
            inline void emplace(T& obj, ARG1 arg1, ARG2 arg2)
            {
                obj.emplace(forward<ARG1>(arg1), forward<ARG2>(arg2));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3)
            {
                obj.emplace(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
            {
                obj.emplace(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
            {
                obj.emplace(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4), forward<ARG5>(arg5));
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
            inline void emplace_at(T& obj, const POS& pos, ARG1 arg1)
            {
                obj.emplace(pos, arg1);
            }
            template <class T, typename POS, typename ARG1, typename ARG2>
            inline void emplace_at(T& obj, const POS& pos, ARG1 arg1, ARG2 arg2)
            {
                obj.emplace(pos, arg1, arg2);
            }
            template <class T, typename POS, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace_at(T& obj, const POS& pos, ARG1 arg1, ARG2 arg2, ARG3 arg3)
            {
                obj.emplace(pos, arg1, arg2, arg3);
            }
            template <class T, typename POS, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace_at(T& obj, const POS& pos, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
            {
                obj.emplace(pos, arg1, arg2, arg3, arg4);
            }
            template <class T, typename POS, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace_at(T& obj, const POS& pos, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
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
            inline void emplace_front(T& obj, ARG1 arg1)
            {
                obj.emplace_front(forward<ARG1>(arg1));
            }
            template <class T, typename ARG1, typename ARG2>
            inline void emplace_front(T& obj, ARG1 arg1, ARG2 arg2)
            {
                obj.emplace_front(forward<ARG1>(arg1), forward<ARG2>(arg2));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace_front(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3)
            {
                obj.emplace_front(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace_front(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
            {
                obj.emplace_front(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace_front(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
            {
                obj.emplace_front(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4), forward<ARG5>(arg5));
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
            inline void emplace_back(T& obj, ARG1 arg1)
            {
                obj.emplace_back(forward<ARG1>(arg1));
            }
            template <class T, typename ARG1, typename ARG2>
            inline void emplace_back(T& obj, ARG1 arg1, ARG2 arg2)
            {
                obj.emplace_back(forward<ARG1>(arg1), forward<ARG2>(arg2));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace_back(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3)
            {
                obj.emplace_back(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace_back(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
            {
                obj.emplace_back(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace_back(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
            {
                obj.emplace_back(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4), forward<ARG5>(arg5));
            }
        #else   // Not C++11
            //
            // emplace(obj, ...)
            //
            template <class T>
            inline void emplace(T& obj)
            {
                typedef typename T::value_type value_type;
                obj.insert(value_type());
            }
            template <class T, typename ARG1>
            inline void emplace(T& obj, ARG1 arg1)
            {
                typedef typename T::value_type value_type;
                obj.insert(value_type(forward<ARG1>(arg1)));
            }
            template <class T, typename ARG1, typename ARG2>
            inline void emplace(T& obj, ARG1 arg1, ARG2 arg2)
            {
                typedef typename T::value_type value_type;
                obj.insert(value_type(forward<ARG1>(arg1), forward<ARG2>(arg2)));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3)
            {
                typedef typename T::value_type value_type;
                obj.insert(value_type(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3)));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
            {
                typedef typename T::value_type value_type;
                obj.insert(value_type(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4)));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
            {
                typedef typename T::value_type value_type;
                obj.insert(value_type(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4), forward<ARG5>(arg5)));
            }

            //
            // emplace_at(obj, pos, ...)
            //
            template <class T, typename POS>
            inline void emplace_at(T& obj, const POS& pos)
            {
                typedef typename T::value_type value_type;
                obj.insert(pos, value_type());
            }
            template <class T, typename POS, typename ARG1>
            inline void emplace_at(T& obj, const POS& pos, ARG1 arg1)
            {
                typedef typename T::value_type value_type;
                obj.insert(pos, value_type(forward<ARG1>(arg1)));
            }
            template <class T, typename POS, typename ARG1, typename ARG2>
            inline void emplace_at(T& obj, const POS& pos, ARG1 arg1, ARG2 arg2)
            {
                typedef typename T::value_type value_type;
                obj.insert(pos, value_type(forward<ARG1>(arg1), forward<ARG2>(arg2)));
            }
            template <class T, typename POS, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace_at(T& obj, const POS& pos, ARG1 arg1, ARG2 arg2, ARG3 arg3)
            {
                typedef typename T::value_type value_type;
                obj.insert(pos, value_type(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3)));
            }
            template <class T, typename POS, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace_at(T& obj, const POS& pos, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
            {
                typedef typename T::value_type value_type;
                obj.insert(pos, value_type(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4)));
            }
            template <class T, typename POS, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace_at(T& obj, const POS& pos, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
            {
                typedef typename T::value_type value_type;
                obj.insert(pos, value_type(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4), forward<ARG5>(arg5)));
            }

            //
            // emplace_front(obj, ...)
            //
            template <class T>
            inline void emplace_front(T& obj)
            {
                typedef typename T::value_type value_type;
                obj.push_front(value_type());
            }
            template <class T, typename ARG1>
            inline void emplace_front(T& obj, ARG1 arg1)
            {
                typedef typename T::value_type value_type;
                obj.push_front(value_type(forward<ARG1>(arg1)));
            }
            template <class T, typename ARG1, typename ARG2>
            inline void emplace_front(T& obj, ARG1 arg1, ARG2 arg2)
            {
                typedef typename T::value_type value_type;
                obj.push_front(value_type(forward<ARG1>(arg1), forward<ARG2>(arg2)));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace_front(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3)
            {
                typedef typename T::value_type value_type;
                obj.push_front(value_type(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3)));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace_front(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
            {
                typedef typename T::value_type value_type;
                obj.push_front(value_type(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4)));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace_front(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
            {
                typedef typename T::value_type value_type;
                obj.push_front(value_type(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4), forward<ARG5>(arg5)));
            }

            //
            // emplace_back(obj, ...)
            //
            template <class T>
            inline void emplace_back(T& obj)
            {
                typedef typename T::value_type value_type;
                obj.push_back(value_type());
            }
            template <class T, typename ARG1>
            inline void emplace_back(T& obj, ARG1 arg1)
            {
                typedef typename T::value_type value_type;
                obj.push_back(value_type(forward<ARG1>(arg1)));
            }
            template <class T, typename ARG1, typename ARG2>
            inline void emplace_back(T& obj, ARG1 arg1, ARG2 arg2)
            {
                typedef typename T::value_type value_type;
                obj.push_back(value_type(forward<ARG1>(arg1), forward<ARG2>(arg2)));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3>
            inline void emplace_back(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3)
            {
                typedef typename T::value_type value_type;
                obj.push_back(value_type(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3)));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            inline void emplace_back(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
            {
                typedef typename T::value_type value_type;
                obj.push_back(value_type(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4)));
            }
            template <class T, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            inline void emplace_back(T& obj, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
            {
                typedef typename T::value_type value_type;
                obj.push_back(value_type(forward<ARG1>(arg1), forward<ARG2>(arg2), forward<ARG3>(arg3), forward<ARG4>(arg4), forward<ARG5>(arg5)));
            }
        #endif
    } // namespace unboost
#endif

#endif  // ndef UNBOOST_EMPLACE_HPP_
