//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_TOKENIZER_HPP
#define JULIA_ORM_TOKENIZER_HPP


#include <vector>
#include "../tools/TextIterator.hpp"
#include "Token.hpp"

class Tokenizer {
private:
    TextIterator _it;
    std::vector<Token*> tokens;

public:
    Tokenizer(TextIterator it, std::vector<Token *> tokens);

    static Tokenizer create(std::wstring text);

    const std::vector<Token *> &getTokens() const;

    void tokenize();

    void take_word();

    void take_number();

    void take_operator_symbol();

    void skip_white_space();

    void take_single_char(wchar_t value, TokenKind kind);

    bool is_word_start();

    bool is_word_char();
};


#endif //JULIA_ORM_TOKENIZER_HPP