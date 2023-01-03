//
// Created by HP on 19/12/2022.
//

#include "TextIterator.hpp"

#include <utility>

TextIterator TextIterator::create(const std::string& value) {
    TextIterator it = TextIterator(value);
    return it;
}

std::string TextIterator::text() {
    return _text;
}

TextIterator::TextIterator(std::string value) {
    _text = std::move(value);
}

void TextIterator::next() {
    if (!has()) {
        return;
    }
    if (current() == '\n') {
        _row += 1;
        _col = 0;
    } else {
        _row += 1;
    }
    _index++;
}

bool TextIterator::has() {
    return _index <= _text.length() - 1;
}

bool TextIterator::is(char c) {
    return has() && current() == c;
}


bool TextIterator::isNot(char c) {
    return has() && current() != c;
}

void TextIterator::skipIfIs(char t) {
    if(is(t)) {
        next();
    }
}

/**
 * Checks if the current char is in the provided string.
 * @param text The provided string.
 * @return True if the current is in the provided string.
 */
bool TextIterator::isIn(std::string text) {
    return has() && text.find(current()) < text.length();
}


/**
 * Checks if the current char is a digits.
 * @return
 */
bool TextIterator::isDigit() {
    return has() && current() >= '0' && current() <= '9';
}


/**
 * Checks if the current char is a letter.
 * @return
 */
bool TextIterator::isLetter() {
    char _char = current();
    return has() && ((_char >= 'a' && _char <= 'z') || (_char >= 'A' && _char <= 'Z'));
}

/**
 * Gets the current char.
 * @return
 */
wchar_t TextIterator::current() {
    if (has()) {
        return _text[_index];
    }
    return '\0';
}


wchar_t TextIterator::t() {
    return current();
}


/**
 * Get is the current char is a whitespace.
 * Whitespace is a
 * @return
 */
bool TextIterator::isWhiteSpace() {
    std::string text = "\u0009\u000A\u000C\u000D\u0020";
    return has() && text.find(current()) < text.length();
}

void TextIterator::skipWhiteSpace() {
    while (isWhiteSpace()) {
        next();
    }
}

//size_t TextIterator::index() {
//    return _index;
//}
//
//size_t TextIterator::line() {
//    return _line;
//}
//
//
//size_t TextIterator::lineIndex() {
//    return _lineIndex;
//}

TextIndex TextIterator::textIndex() const {
    return {_index, _row, _col};
}

