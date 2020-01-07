#if !defined STORAGE_HPP
#define STORAGE_HPP

#include <iostream>
#include "id_type.hpp"

using id_type = id_ui1f_type;

template<class NODE=unsigned, unsigned N=20>
struct storage_type {

    constexpr static unsigned capacity = N;

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

    portion arr[N];

    storage_type(): __free{0u} {
        static_assert(N < id_type::NIL, "");
        for (id_type i{0u}; i < N-1; ++i) {
            arr[i].next = i+1;
        }
    }

    id_type alloc() {
        if (__free.is_NIL())
            return id_type{};
        auto const ret = __free;
        __free = arr[__free].next;
        return ret;
    }

    void free(id_type id) {
        copy(arr[id].next, __free);
        __free = id;
    }

    bool is_empty() const {
        return __free.is_NIL();
    }

    NODE& operator[](unsigned id) {
        return arr[id].node;
    }

    friend std::ostream& operator<<(std::ostream& os, storage_type const& s) {

        os << "free " << s.__free << '\n';

        for (id_type i = 0u; i < storage_type::capacity; ++i) {
            os << i << ':' << s.arr[i].next << '\n';
        }
        return os;
    }
};

#endif // STORAGE_HPP
