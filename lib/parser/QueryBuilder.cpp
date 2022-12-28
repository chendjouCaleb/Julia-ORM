//
// Created by HP on 27/12/2022.
//

#include "QueryBuilder.hpp"

#include <utility>
#include "Tokenizer.hpp"


QueryBuilder::QueryBuilder(DbSchema *schema, std::vector<Token *> tokens) : schema(schema), tokens(tokens),
                                                                            _it(Iterator<Token *>(&tokens)) {
    _it = Iterator<Token *>(&tokens);
}

QueryBuilder QueryBuilder::create(DbSchema *schema, std::wstring text) {
    Tokenizer tokenizer = Tokenizer::create(std::move(text));
    auto tokens = tokenizer.tokenize();
    return QueryBuilder{schema, tokens};
}


void QueryBuilder::parse() {
    while (_it.has()) {
        if (_it.current()->kind == Tk_Word && _it.current()->value == L"from") {

            takeSelect();
            if (_it.current()->kind == Tk_SemiColon) {
                _it.next();
                break;
            }
        } else {
            auto value = _it.current()->value;
            char tmp[255];
            sprintf(tmp, "%ls", value.c_str());
            std::string message = "Unknown token ";
            message.push_back(*tmp);
            throw std::invalid_argument(message);
        }
    }
}

void QueryBuilder::takeSelect() {
    query.statement = _it.current()->value;
    query.kind = QK_SELECT;
    // Skip current from or select keyword.
    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_Word) {
        // Expect alias.
    }
    query.alias = _it.current()->value;
    _it.next();
    if (!_it.has() || _it.current()->kind != Tk_Word || _it.current()->value != L"in") {
        // Expect 'in' keyword.
    }
    _it.next();


    if (!_it.has() || _it.current()->kind != Tk_Word) {
        // Expect dbset name.
    }
    auto dbSetName = _it.current()->value;
    _it.next();

    if (!schema->database->hasDbSet(dbSetName)) {
        // Expect know dbset.
    }

    query.dbSetName = dbSetName;
    query.dbSet = schema->database->dbSets[dbSetName];
}