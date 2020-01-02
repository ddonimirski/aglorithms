#if !defined STORAGE_HPP
#define STORAGE_HPP

#include <iostream>

//TODO: implement more the 1 flags
template<class base_type=unsigned, unsigned FLAGS_BITS=1>
struct id_type_t {
    using inner_type = base_type;
    constexpr static inner_type NIL{ static_cast<inner_type>(-1) >> FLAGS_BITS };
    constexpr static inner_type FLG{ ~NIL };
    constexpr static inline auto get_id(inner_type id) { return id & NIL; }
    constexpr static inline auto get_flags(inner_type id) { return id & FLG; }
    constexpr static inline auto get_flags_as_low(inner_type id) {
        return (id & FLG) >> (sizeof(base_type)*8 - FLAGS_BITS);
    }

    inner_type __id;

    // provide non-explict conversion base_type -> id_type_t
    id_type_t(inner_type id=NIL): __id{get_id(id)} {}
    // provide non-explict conversion id_type_t -> base_type
    operator inner_type() const { return (get_id(__id)); }

    id_type_t(id_type_t const&) = default; // copy all
    id_type_t(id_type_t&&) = delete;

    // might this oprator should be deleted 
    id_type_t& operator = (id_type_t const& id) noexcept {
         __id = get_flags(__id) | get_id(id.__id);
         return *this;
    }

    id_type_t operator++ () {
        ++__id;
        return *this;
    }

    void set_NIL() { __id = NIL; };

    //TODO: consider friend inline add to the interface
    friend inline bool is_on(id_type_t const& id) {
        return !!get_flags(id.__id);
    }

    friend inline bool is_NIL(id_type_t const& id) {
        return get_id(id.__id) == NIL;
    }

    friend inline id_type_t& on(id_type_t& id) {
        id.__id |= FLG;
        return id;
    }

    friend inline id_type_t& off(id_type_t& id) {
        id.__id &= NIL;
        return id;
    }

    friend inline void copy_id(id_type_t& dst, id_type_t const& src) {
        dst.__id = get_flags(dst.__id) | get_id(src.__id);
    }

    friend inline void copy_flags(id_type_t& dst, id_type_t const& src) {
        dst.__id = get_id(dst.__id) | get_flags(src.__id);
    }

    friend inline void copy(id_type_t& dst, id_type_t const& src) {
        dst.__id = src.__id;
    }

    friend std::ostream& operator<<(std::ostream& os, id_type_t const& n) {
        if (n.__id == NIL)
            return os << "NIL";
        return os << get_id(n.__id);
    }
};

using id_type = id_type_t<>;


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
        if (is_NIL(__free))
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
