// safe_delete.hpp --- Unboost safe delete and safe release
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_SAFE_DELETE_HPP_
#define UNBOOST_SAFE_DELETE_HPP_

#include "unboost.hpp"

namespace unboost {
    template <typename TYPE>
    inline void safe_delete(TYPE*& pobj) {
        delete pobj;
        pobj = NULL;
    }

    template <typename TYPE>
    inline void safe_delete_array(TYPE*& parray) {
        delete[] parray;
        parray = NULL;
    }

    template <typename TYPE>
    inline void safe_release(TYPE*& pobj) {
        pobj->Release();
        pobj = NULL;
    }

    #ifdef UNBOOST_SMART_PTR_HPP_
        template <typename TYPE>
        inline void safe_delete(shared_ptr<TYPE>& ptr) {
            ptr.reset();
        }

        template <typename TYPE>
        inline void safe_delete(unique_ptr<TYPE>& ptr) {
            ptr.reset();
        }

        template <typename TYPE>
        inline void safe_delete(weak_ptr<TYPE>& ptr) {
            ptr.reset();
        }

        template <typename TYPE>
        inline void safe_release(shared_ptr<TYPE>& ptr) {
            ptr->Release();
            ptr.reset();
        }

        template <typename TYPE>
        inline void safe_release(unique_ptr<TYPE>& ptr) {
            ptr->Release();
            ptr.reset();
        }

        template <typename TYPE>
        inline void safe_release(weak_ptr<TYPE>& ptr) {
            ptr->Release();
            ptr.reset();
        }
    #endif  // def UNBOOST_SMART_PTR_HPP_
} // namespace unboost

#endif  // ndef UNBOOST_SAFE_DELETE_HPP_
