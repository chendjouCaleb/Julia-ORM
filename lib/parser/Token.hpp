//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_TOKEN_HPP
#define JULIA_ORM_TOKEN_HPP

#include <string>
#include <map>
#include <TextIndex.hpp>


enum TokenKind {
    Tk_Word,
    Tk_Number,
    Tk_ParenthesisOpen,
    Tk_ParenthesisClose,
    Tk_SymbolOperator,

    Tk_BraceOpen,
    Tk_BraceClose,
    Tk_BracketOpen,
    Tk_BracketClose,
    Tk_Equals,


    Tk_Colon, // :
    Tk_SemiColon, // ;
    Tk_Coma, // ,
    Tk_Arobase, // @
    Tk_QuestionMark, // ?
};

const std::map<wchar_t, TokenKind> SINGLE_SYMBOLS = {
        {':', Tk_Colon},
        {';', Tk_SemiColon },
        {',', Tk_Coma },
        {'@', Tk_Arobase },
        {'?', Tk_QuestionMark },

        {'[', Tk_BracketOpen },
        {']', Tk_BracketClose },

        {'{', Tk_BraceOpen },
        {'}', Tk_BraceClose },

        {'(', Tk_ParenthesisOpen },
        {')', Tk_ParenthesisClose },
};

class Token {
public:
    TextIndex index;
    TokenKind kind;


    Token(const TextIndex index, const std::wstring &value, TokenKind kind) : index(index), value(value), kind(kind) {}

    std::wstring value;
};

#endif //JULIA_ORM_TOKEN_HPP
