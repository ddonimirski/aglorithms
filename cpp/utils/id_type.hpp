#if !defined ID_TYPE_HPP
#define ID_TYPE_HPP

#include <iostream>
#include <type_traits>


#if defined(_MSC_VER) 

#define DISABLE_WARNING_PUSH  __pragma(warning( push ))
#define DISABLE_WARNING_POP   __pragma(warning( pop ))
#define DISABLE_WARNING(warning_name) __pragma(warning( disable : warning_name))

#elif defined(__GNUC__) || defined(__clang__)

#define DO_PRAGMA(X) _Pragma(#X)

#if defined(__GNUC__)

#define DISABLE_WARNING_PUSH
#define DISABLE_WARNING_POP
#define DISABLE_WARNING(warning_name) DO_PRAGMA(GCC diagnostic ignored #warning_name)

#elif defined(__clang__)
#define CLANG_PRAGMA(#X) DO_PRAGMA(clang diagnostic #X)

#define DISABLE_WARNING_PUSH CLANG_PRAGMA(push)
#define DISABLE_WARNING_POP  CLANG_PRAGMA(pop)
#define DISABLE_WARNING(warning_name) CLANG_PRAGMA(ignored #warning_name)

#endif

#define DISABLE_WARNING_SHIFT_COUNT_OVERFLOW  DISABLE_WARNING(-Wshift-count-overflow)

#else

#define DISABLE_WARNING_PUSH
#define DISABLE_WARNING_POP
#define DISABLE_WARNING

#endif


template<class BASE=unsigned, int FLAGS_BITS = 1>
struct base_type {

    using inner_type = BASE;

    constexpr static inner_type NIL{ static_cast<inner_type>(-1) >> FLAGS_BITS };
    constexpr static inner_type FLG{ ~NIL };
    constexpr static inner_type NUM_ID_BITS { sizeof(inner_type)*8 - FLAGS_BITS };
    constexpr static inline auto get_id(inner_type id) noexcept { return id & NIL; }
    constexpr static inline auto get_flags(inner_type id) noexcept { return id & FLG; }
DISABLE_WARNING_PUSH
DISABLE_WARNING_SHIFT_COUNT_OVERFLOW
    constexpr static inline auto lm2mask(inner_type mid = 1u) noexcept { return mid << NUM_ID_BITS; }
    constexpr static inline auto mask2lm(inner_type id) noexcept { return get_flags(id) >> NUM_ID_BITS; }
DISABLE_WARNING_POP

    static_assert(FLAGS_BITS < (sizeof(inner_type)*8), "");

    inner_type __id;

    // provide non-explict conversion base_type -> id_type_t
    base_type(inner_type id=NIL): __id{get_id(id)} {}
    // provide non-explict conversion id_type_t -> base_type
    operator inner_type() const { return (get_id(__id)); }

    base_type(base_type const&) = default; // copy all

    // might this oprator should be deleted 
    base_type& operator = (base_type const& id) noexcept {
         __id = get_flags(__id) | get_id(id.__id);
         return *this;
    }

    void set_NIL() noexcept { __id = NIL; };

    bool is_NIL() const noexcept { return get_id(__id) == NIL; }

    base_type operator++ () noexcept { ++__id; return *this; }

    void on(inner_type mask = FLG) noexcept { __id |= mask; } 
    void off(inner_type mask = FLG) noexcept { __id &= ~mask; } 
    void set_flag(int flag_id = 0) noexcept { on(lm2mask(1 << flag_id)); }

    bool is_on() const noexcept { return !!get_flags(__id); }
    bool is_set(int flag_id = 0) const noexcept { return !!(__id & lm2mask(1 << flag_id)); }

    void copy_flags(base_type const& src) noexcept { __id = get_id(__id) | get_flags(src.__id); }
    void copy(base_type const& src) { __id = src.__id; }
    void copy_id(base_type const& src) noexcept { __id = get_flags(__id) | get_id(src.__id); }

    void flip_flags() noexcept { __id = (~get_flags(__id)) & get_id(__id); }

    friend std::ostream& operator<<(std::ostream& os, base_type const& n) {
#if defined DEBUG
        os << '(' << mask2lm(n.__id) << ')';
#endif
        if (n.is_NIL())
            return os << "NIL";
        return os << get_id(n.__id);
    }
};


template<class T, unsigned FB>
struct id_type_t: public base_type<T, FB> {
    using base = base_type<T, FB>;
    using inner_type = typename base::inner_type;

    id_type_t(inner_type id=base::NIL):base{id}{}
};


template<class T>
struct id_type_t <T, 0>: public base_type<T, 0> {
    using base = base_type<T, 0>;
    using inner_type = typename base::inner_type;

    id_type_t(inner_type id=base::NIL):base{id}{}

    void on(inner_type mask = base::FLG) = delete;
    void off(inner_type mask = base::FLG) = delete;
    bool is_on() const = delete;
    void set_flag(int) = delete;
    bool is_set(int) = delete;
    void copy_flags(id_type_t const& src) = delete;

    void copy_id(id_type_t const& src) noexcept { base::copy(src); }

};


using id_ui0f_type = id_type_t<unsigned, 0>;
using id_ui1f_type = id_type_t<unsigned, 1>;
using id_ui2f_type = id_type_t<unsigned, 2>;

#endif // ID_TYPE_HPP
