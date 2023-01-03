//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_TEXTITERATOR_HPP
#define JULIA_ORM_TEXTITERATOR_HPP


#include <string>
#include "TextIndex.hpp"

class TextIterator {
private:
    std::string _text;
    size_t _index = 0;
    size_t _row = 0;
    size_t _col = 0;

public:
    static TextIterator create(const std::string& value);

    explicit TextIterator(std::string value);

    std::string text();

    void next();

    bool isDigit();

    bool isLetter();

    bool isWhiteSpace();

    void skipWhiteSpace();

    wchar_t current();
    wchar_t t();

    bool has();

    bool is(char c);
    bool isNot(char c);

    void skipIfIs(char t);

    TextIndex textIndex() const;

    bool isIn(std::string c);
};


#endif //JULIA_ORM_TEXTITERATOR_HPP
