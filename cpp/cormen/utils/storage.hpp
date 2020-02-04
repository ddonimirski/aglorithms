#if !defined STORAGE_HPP
#define STORAGE_HPP

#include <iostream>
#include <array>
#include <vector>
#include <type_traits>
#include "id_type.hpp"

#include <cassert>

//TODO: protect to free the same id few times
//TODO: add an extension storage during allocation

#define UNION_PORTION


template<class NODE, template<typename...> class CONT, class ID_TYPE = id_ui0f_type>
struct storage_type {

    using id_type = ID_TYPE;

    static_assert(sizeof(NODE) > sizeof(id_type), " ");

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

    using container_type = CONT<portion>;

    static void fill_next(container_type& cont, id_type id) {
        if (cont.size() < 1) return;
        for (; id < cont.size()-1; ++id) {
            cont[id].next = id+1;
        }
    }


    template<class C>
    static id_type try_extend_capacity(C& cont, size_t count = 20) {
        // default CONT can not be extended
        return {};
    }


    template<class T>
    static id_type try_extend_capacity(std::vector<T>& vec, size_t count = 20) {
        id_type const id = vec.size();
        vec.resize(count + id);
        return id;
    }



    id_type __free;
    container_type arr;


    //template<>
    //id_type::inner_type size() const {
    //}

    //template<>
    //id_type::inner_type size() const {
    //}

    storage_type() {
        //TODO: add check (N < id_type::NIL, "");
        try_extend_capacity(arr);
        fill_next(arr, 0u);
        __free = 0u;
    }


    storage_type(CONT<NODE> 

    id_type alloc() {
        if (__free.is_NIL()) {
            __free = try_extend_capacity(arr);
            if (__free.is_NIL()) return {};
            fill_next(arr, __free);
        }
        auto const ret = __free;
        __free = arr[__free].next;

        assert(!ret.is_NIL());
        return ret;
    }

    void free(id_type id) {
        arr[id].node = NODE{};
        arr[id].next.copy(__free);
        __free = id;
    }

    bool is_empty() const {
        return __free.is_NIL();
    }

    NODE& operator[](unsigned id) {
        return arr[id].node;
    }

    NODE const& operator[](unsigned id) const {
        return arr[id].node;
    }


    friend std::ostream& operator<<(std::ostream& os, storage_type const& s) {

        os << "free " << s.__free << '\n';

        for (id_type i = 0u; i < s.arr.size(); ++i) {
            os << i << ':' << s.arr[i].next << '\n';
        }
        return os;
    }
};

#endif // STORAGE_HPP
