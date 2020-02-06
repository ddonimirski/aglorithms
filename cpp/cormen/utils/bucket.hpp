#if !defined UTILS_BUCKET_HPP
#define UTILS_BUCKET_HPP

#include <iostream>
#include <utility>
#include <vector>

// tip how to use std::array
// template<class T>
// using cont20_type = std::array<T, 20>;

template<class NODE, template<typename...> class CONT=std::vector>
struct bucket {

    using value_type = NODE;

    CONT<value_type> cont;
    size_t count = 0u;

    auto size() const { return count; }

    void insert(value_type&& val) {
        count = add(cont, std::forward<value_type>(val), count);
    }

    template<class C>
    static size_t add(C& cont, value_type&& val, size_t count) {
        cont[++count] = val;
        return count;
    }

    template<class T>
    static size_t add(std::vector<T>& vec, value_type&& val, size_t count) {
        //assert (vec.size() == count);
        if (count == vec.size()) {
            vec.push_back(std::forward<T>(val));
            ++count;
        }
        else {
            vec[++count] = val;
        }
        return count;
    }

    void erase(size_t id , bool destroy = false) {
        if (id < count) {
            cont[id] = cont[--count];
            if (destroy) {
                cont[count] = {};
            }
        }
    }

    size_t find(value_type const& val) const {
        for (size_t id = 0u; id < count; ++id) {
            if (cont[id] == val) return id;
        }
        return -1;
    }

    value_type& operator[](unsigned id) {
        return cont[id];
    }

    value_type const& operator[](unsigned id) const {
        return cont[id];
    }


    friend std::ostream& operator<<(std::ostream& os, bucket const& bb) {
        for (size_t id = 0u; id < bb.size(); ++id) {
            os << bb.cont[id] << ' ';
        }
        return os << '\n';
    }

};

#endif
