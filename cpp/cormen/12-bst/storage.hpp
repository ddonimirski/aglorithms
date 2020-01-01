#if !defined STORAGE_HPP
#define STORAGE_HPP

#include <iostream>

struct id_type {
    using inner_type = unsigned;
    inner_type __id;
    constexpr static inner_type NIL{ (static_cast<inner_type>(-1)-1)>>1 };

    id_type(inner_type id=NIL): __id{id} {}
    operator inner_type() const { return (__id & NIL); }


    id_type operator++ () {
        ++__id;
        return *this;
    }

    friend bool is_on(id_type const& id) {
        return !!(id.__id & ~NIL);
    }

    friend bool is_NIL(id_type const& id) {
        return (id.__id & NIL) == NIL;
    }

    friend id_type& on(id_type& id) {
        id.__id |= ~NIL;
        return id;
    }

    friend id_type& off(id_type& id) {
        id.__id &= NIL;
        return id;
    }

    friend void copy_on(id_type const& src, id_type& dst) {
        off(dst).__id |= (src.__id & ~NIL);
    }

    friend std::ostream& operator<<(std::ostream& os, id_type const& n) {
        if (n.__id == NIL)
            return os << "NIL";
        return os << (n.__id & NIL);
    }
};


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
        for (id_type i = 0u; i < N-1; ++i) {
            arr[i].next = i+1;
        }
    }

    id_type alloc() {
        if (is_NIL(__free))
            return id_type{};
        auto const ret = __free;
        __free = arr[__free].next;
        return ret;
    }

    void free(id_type id) {
        arr[id].next = __free;
        __free = id;
    }

    bool is_empty() const {
        return is_NIL(__free);
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
