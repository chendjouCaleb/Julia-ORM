//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_TEXTITERATOR_HPP
#define JULIA_ORM_TEXTITERATOR_HPP


#include <string>
#include "TextIndex.hpp"

class TextIterator {
private:
    std::wstring _text;
    size_t _index = 0;
    size_t _row = 0;
    size_t _col = 0;

public:
    static TextIterator create(const std::wstring& value);

    explicit TextIterator(std::wstring value);

    std::wstring text();

    void next();

    bool isDigit();

    bool isLetter();

    bool isWhiteSpace();

    void skipWhiteSpace();

    wchar_t current();
    wchar_t t();

    bool has();

    bool is(char c);
    bool is_t(wchar_t t);
    bool isNot(char c);

    void skipIfIs(wchar_t t);

    TextIndex textIndex() const;

    bool isIn(std::wstring c);
};


#endif //JULIA_ORM_TEXTITERATOR_HPP
