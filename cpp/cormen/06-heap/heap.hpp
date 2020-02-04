#if !defined HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <iostream>


template<class T>
struct min_cmp {
    bool operator() (T const& v1, T const& v2) const noexcept {
        return v1 <= v2;
    }
};

template<class T>
struct max_cmp {
    bool operator() (T const& v1, T const& v2) const noexcept {
        return v1 >= v2;
    }
};


template<class NODE, template<typename...> class CONT, class CMP = min_cmp<NODE>>
struct heap {

    using value_type = NODE;
    using container_type = CONT<NODE>;

    container_type _cont;
    size_t _count;
    CMP _cmp;

    heap():_count(0) {}

    heap(CONT<NODE>& c, size_t s):_cont{c}, _count{s} {
        make(*this);
    }

    explicit heap(CONT<NODE>& c): heap{c, c.size()} {}

    size_t size() const noexcept { return _count; }

    static auto parent(size_t i) noexcept { return (i-1) / 2; }
    static auto left2right(size_t i) noexcept { return ++i; }
    static auto left(size_t i) noexcept { return 2u * i + 1; }
    static auto right(size_t i) noexcept { return 2u * i + 2u; }

    NODE& operator[] (size_t i) { return _cont[i]; }
    NODE const& operator[] (size_t i) const { return _cont[i]; }

    void swap(size_t i1, size_t i2) noexcept {
        auto tmp = _cont[i1];
        _cont[i1] = _cont[i2];
        _cont[i2] = tmp;
    }

    void swim(size_t i) noexcept {
        while (i > 0) {
            auto const p = parent(i);
            if (_cmp(_cont[p], _cont[i])) break;
            swap(p, i);
            i = p;
        }
    }

    void sink(size_t p = 0u) noexcept {
        size_t i;
        while ((i = left(p)) < _count) {
            if (auto const r = left2right(i);
                    r < _count && !_cmp(_cont[i], _cont[r])) {
                i = r;
            }
            if (_cmp(_cont[p],_cont[i])) break;
            swap(p, i);
            p = i;
        }
    }

    template<class T, template <typename...> class C>
    static void add_element(C<T>& cont, size_t i, T const& v) {
        // throw when no place
        cont[i] = v;
    }

    template<class T>
    void add_element(std::vector<T>& cont, size_t i, T const& v) {
        
        if (i < cont.size()) {
            cont[i] = v;
        } else {
            cont.push_back(v);
        }
    }

    void insert(value_type const& v) {
        add_element(_cont, _count, v);
        swim(_count++);
    }

    value_type pop() {
        auto const v = _cont[0u];
        swap(0u, --_count);
        sink(0u);

        return v;
    }

    value_type top() const {
        return _cont[0u];
    }

    friend void make(heap& h) {
        for (size_t i = 1u; i < h._count; ++i) {
            h.swim(i);
        }
    }

    friend bool is_heap(heap const& h) {
        auto const& c = h._cont;
        auto const& cmp = h._cmp;
        for (size_t i = 1u; i < h._count; ++i) {
            auto const p = parent(i);
            if (!cmp(c[p], c[i]))
                return false;
        }
        return true;
    }

    friend std::ostream& operator << (std::ostream& os, heap const& h) {
        for (auto i = 0u; i < h._count; ++i)
            os << h._cont[i] << ' ';
        return os << '\n';
    }
};

#endif // HEAP_HPP
