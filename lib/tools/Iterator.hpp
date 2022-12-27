//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_ITERATOR_HPP
#define JULIA_ORM_ITERATOR_HPP


#include <vector>

template <typename T>
class Iterator {
private:
    std::vector<T>* _items;
    size_t _index;

public:
    explicit Iterator(std::vector<T>* items) {
        _items = items;
        _index = 0;
    }

    T& current() {
        return _items->at(_index);
    }

    size_t index() {
        return _index;
    }

    size_t size() {
        return _items->size();
    }

    bool has() {
        return _index <= _items -> size() - 1;
    }

    void next() {
        _index += 1;
    }
};


#endif //JULIA_ORM_ITERATOR_HPP
