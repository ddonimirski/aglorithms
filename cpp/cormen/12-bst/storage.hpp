#if !defined STORAGE_HPP
#define STORAGE_HPP

#include <iostream>
#include <array>
#include <vector>
#include <type_traits>
#include "id_type.hpp"

using id_type = id_ui1f_type;

#define UNION_PORTION



template<class NODE, template<typename, size_t> class CONT>
struct storage_type {

    static_assert(sizeof(NODE) > sizeof(id_type), " ");

    id_type __free;

#if defined UNION_PORTION
    union portion {
        id_type next;
        NODE node;
        portion(): next{} {}
    };
#else
    struct portion {
        id_type next;
        NODE node;
    };
#endif

    CONT<portion, 20> arr;


    //template<>
    //id_type::inner_type size() const {
    //}

    //template<>
    //id_type::inner_type size() const {
    //}

    storage_type(): __free{0u} {
        ///static_assert(N < id_type::NIL, "");
        //for (id_type i{0u}; i < arr.size(); ++i) {
        //    arr[i].next = i+1;
        //}
    }

//    id_type alloc() {
//        if (__free.is_NIL())
//            return id_type{};
//        auto const ret = __free;
//        __free = arr[__free].next;
//        return ret;
//    }
//
//    void free(id_type id) {
//        copy(arr[id].next, __free);
//        __free = id;
//    }
//
//    bool is_empty() const {
//        return __free.is_NIL();
//    }
//
//    NODE& operator[](unsigned id) {
//        return arr[id].node;
//    }
//
//    friend std::ostream& operator<<(std::ostream& os, storage_type const& s) {
//
//        os << "free " << s.__free << '\n';
//
//        for (id_type i = 0u; i < storage_type::capacity; ++i) {
//            os << i << ':' << s.arr[i].next << '\n';
//        }
//        return os;
//    }
};

#endif // STORAGE_HPP
