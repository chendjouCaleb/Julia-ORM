//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_TEXTINDEX_HPP
#define JULIA_ORM_TEXTINDEX_HPP

#include <iostream>

class TextIndex {
private:
    size_t _index;
    size_t _row;
    size_t _col;

public:
    TextIndex(size_t index, size_t row, size_t col) {
        _index = index;
        _row = row;
        _col = col;
    }

    TextIndex(TextIndex &copy) {
        _index = copy.index();
        _col = copy.col();
        _row = copy.row();
    }

    TextIndex(const TextIndex &index) {
        _index = index.index();
        _col = index.col();
        _row = index.row();
    }

    TextIndex() {
        _index = 0;
        _row = 0;
        _col = 0;
    }

    static TextIndex zero() {
        return TextIndex(0, 0, 0);
    }

    static TextIndex to(size_t index) {
        return TextIndex(index, 0, index);
    }

    TextIndex copy() {
        return TextIndex(this->index(), this->row(), this->col());
    }

    [[nodiscard]] size_t index() const { return _index; }
    size_t row() const { return _row; }
    size_t col() const {return _col; }


};


#endif //JULIA_ORM_TEXTINDEX_HPP
