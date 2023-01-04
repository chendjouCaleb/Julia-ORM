//
// Created by HP on 19/12/2022.
//

#include <const.hpp>
#include <utility>
#include <vector>
#include "Tokenizer.hpp"


Tokenizer Tokenizer::create(std::string text) {
    auto tokenizer = Tokenizer(TextIterator(std::move(text)), {});
    return tokenizer;
}

Tokenizer::Tokenizer(TextIterator it, std::vector<Token *> tokens) : _it(std::move(it)), tokens(std::move(tokens)) {};


std::vector<Token *> Tokenizer::tokenize() {
    while(_it.has()) {
        skip_white_space();
        if (is_word_start()) {
            take_word();
        } else if (_it.isDigit()) {
            take_number();
        } else if (_it.isIn(S_SYMBOL_OPERATORS)) {
            take_operator_symbol();
        } else if (SINGLE_SYMBOLS.find(_it.current()) != SINGLE_SYMBOLS.end()) {
            take_single_char(_it.current(), SINGLE_SYMBOLS.find(_it.current())->second);
        } else {
            take_unknown_token_error();
        }
    }
    return tokens;
}

void Tokenizer::take_word() {
    auto index = _it.textIndex();
    std::string value;

    while (_it.has() && is_word_char()) {
        value.push_back(_it.current());
        _it.next();
    }
    auto token = new Token(index, value, Tk_Word);
    tokens.push_back(token);
}

void Tokenizer::take_number() {
    auto index = _it.textIndex();
    std::string value;

    while (_it.has() && _it.isDigit()) {
        value.push_back(_it.current());
        _it.next();
    }
    auto token = new Token(index, value, Tk_Number);
    tokens.push_back(token);
}


void Tokenizer::take_operator_symbol() {
    auto index = _it.textIndex();
    std::string value;
    while (_it.has() && _it.isIn(S_SYMBOL_OPERATORS)) {
        value.push_back(_it.current());
        _it.next();
    }
    auto token = new Token(index, value, Tk_SymbolOperator);
    tokens.push_back(token);
}


void Tokenizer::take_single_char(char value, TokenKind kind) {
    if (_it.has() && _it.current() == value) {
        auto index = _it.textIndex();
        std::string str(1, _it.current());
        auto token = new Token(index, str, kind);
        _it.next();
        tokens.push_back(token);
    }
}

void Tokenizer::take_unknown_token_error() {
    char token = _it.current();
    auto index = _it.textIndex();

    char msgBuffer[100];
    snprintf(msgBuffer, sizeof(msgBuffer), "Unknown character '%c' at [%d, %d].", token, index.row(), index.col());
    std::string message = msgBuffer;
    Error error = Error {
        .type = ERR_TYPE_SYNTAX,
        .syntaxErrorCode = SYNTAX_ERR_UNEXPECTED_CHAR,
        .message = message
    };

    errors.push_back(error);
    _it.next();
}

void Tokenizer::skip_white_space() {
    while (_it.has() && _it.isWhiteSpace()) {
        _it.next();
    }
}


bool Tokenizer::is_word_char() {
    auto c = _it.current();
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

bool Tokenizer::is_word_start() {
    auto c = _it.current();
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

std::vector<Token *> Tokenizer::getTokens() const {
    return tokens;
}


