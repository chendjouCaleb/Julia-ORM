//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_TOKENIZER_HPP
#define JULIA_ORM_TOKENIZER_HPP


#include <vector>
#include <Error.hpp>
#include "../tools/TextIterator.hpp"
#include "Token.hpp"

class Tokenizer {
private:
    TextIterator _it;
    std::vector<Token*> tokens;

public:
    std::vector<Error> errors;

public:
    Tokenizer(TextIterator it, std::vector<Token *> tokens);

    static Tokenizer create(std::string text);

    std::vector<Token *> getTokens() const;

    std::vector<Token *> tokenize();

    void take_word();

    void take_number();

    void take_operator_symbol();

    void skip_white_space();

    void take_single_char(char value, TokenKind kind);

    void take_unknown_token_error();

    bool is_word_start();

    bool is_word_char();
};


#endif //JULIA_ORM_TOKENIZER_HPP
