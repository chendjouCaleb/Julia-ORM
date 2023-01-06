//
// Created by HP on 19/12/2022.
//

#include <cassert>
#include <fmt/format.h>
#include "SchemaTreeBuilder.hpp"


SchemaTreeBuilder SchemaTreeBuilder::create(std::vector<Token *> *tokens) {
    auto builder = SchemaTreeBuilder(Iterator<Token *>(tokens));
    return builder;
}

void SchemaTreeBuilder::build() {
    _schema = new DbSchema();
    while (_it.has()) {
        if (_it.current()->kind == Tk_Word && _it.current()->value == "database") {
            takeDatabase();
        }
        else if (_it.current()->kind == Tk_Word && _it.current()->value == "interface") {
            auto interface = takeInterface();
            _schema->interfaces.push_back(interface);
        }

        else if (_it.current()->kind == Tk_Word && _it.current()->value == "entity") {
            auto entity = takeEntity();
            _schema->entities.push_back(entity);
        } else {
            if(!syntaxErrors.empty()) {
                break;
            }

            auto token = _it.current();
            Error error = {
                    .type = ERR_TYPE_SYNTAX,
                    .syntaxErrorCode = SYNTAX_ERR_UNKNOWN_TOKEN,
                    .message = fmt::format("Unknown token {} at [{}, {}]", token->value, token->index.row(), token->index.col())
            };
            syntaxErrors.push_back(error);
            break;
        }
    }

    if(!syntaxErrors.empty()){
        return;
    }

    for (const auto &item : _schema->database->dbSets) {
        item.second->entity = _schema->findEntity(item.second->entityName);
    }

}

void SchemaTreeBuilder::takeDatabase() {
    // skip database keyword.
    auto keywordToken = _it.current();
    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_Word) {
        takeDatabaseNameError(keywordToken);
        return;
    }

    auto db = new Database();
    db->name = _it.current()->value;
    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_BraceOpen) {
        // Expect brace open.
    }
    _it.next();

    while (_it.has() && _it.current()->kind == Tk_Word && _it.current()->value == "dbset") {
        //std::wcout << _it.current()->value << std::endl;
        auto dbSet = takeDbSet();
        db->dbSets[dbSet->name] = dbSet;


    }

    if (!_it.has() || _it.current()->kind != Tk_BraceClose) {
        // Expect brace close.
    }
    _it.next();

    _schema->database = db;
}

DbSet *SchemaTreeBuilder::takeDbSet() {
    // Skip dbSet keyword.
    _it.next();
    auto dbSet = new DbSet();

    if (!_it.has() || _it.current()->kind != Tk_SymbolOperator || _it.current()->value != "<") {
        // Expect chevron open.
    }

    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_Word) {
        // Expect entity type name.
    }

    dbSet->entityName = _it.current()->value;
    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_SymbolOperator || _it.current()->value != ">") {
        // Expect chevron close.
    }
    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_Word) {
        // Expect dbset name.
    }
    dbSet->name = _it.current()->value;
    _it.next();
    // std::wcout << _it.current()->value << std::endl;
    if (!_it.has() || _it.current()->kind != Tk_SemiColon) {
        // Expect ;.
    }
    _it.next();
    return dbSet;
}

Entity *SchemaTreeBuilder::takeEntity() {
    // skip entity keyword.
    _it.next();
    auto keywordToken = _it.current();

    if(!_it.has() || _it.current()->kind != Tk_Word) {
        // Expect entity name.
       Error error = takeEntityNameError(keywordToken);
        std::cout << error.message << std::endl;
        return nullptr;
    }


    TypeBlock block = takeBlock();

    auto* entity = new Entity();
    entity->name = block.name;
    entity->fields = block.fields;

    return entity;
}

Interface* SchemaTreeBuilder::takeInterface() {
    // skip interface keyword.
    _it.next();
    auto keywordToken = _it.current();

    if(!_it.has() || _it.current()->kind != Tk_Word) {
        // Expect interface name.
        takeInterfaceNameError(keywordToken);
        return nullptr;
    }

    TypeBlock block = takeBlock();
    auto interface = new Interface();
    interface->name = block.name;
    interface->fields = block.fields;

    return interface;
}

TypeBlock SchemaTreeBuilder::takeBlock() {
    assert(_it.current()->kind == Tk_Word);

    auto block = TypeBlock {};
    block.name = _it.current()->value;
    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_BraceOpen) {
        // Expect brace open.
        assert(_it.has() && _it.current()->kind == Tk_BraceOpen);
    }
    _it.next();

    while (_it.has() && _it.current()->kind != Tk_BraceClose) {
        auto field = takeField();
        block.fields.push_back(field);
    }

    if (!_it.has() || _it.current()->kind != Tk_BraceClose) {
        // Expect brace close.
        assert(_it.has() && _it.current()->kind == Tk_BraceClose);
    }
    _it.next();

    return block;
}


Field *SchemaTreeBuilder::takeField() {
    auto *field = new Field();

    field->annotations = takeAnnotations();
    field->name = _it.current()->value;
    _it.next();

    if (!_it.has() || _it.current()->value != ":") {
        // Expect : close.
    }
    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_Word) {
        // Expect entity name
    }
    field->typeName = _it.current()->value;
    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_SemiColon) {
        // Expect ;.
    }
    _it.next();

    return field;
}


std::vector<Annotation *> SchemaTreeBuilder::takeAnnotations() {
    auto items = std::vector<Annotation *>();
    while (_it.has() && _it.current()->kind == Tk_Arobase) {
        auto annotation = takeAnnotation();
        items.push_back(annotation);
    }
    return items;
}

Annotation *SchemaTreeBuilder::takeAnnotation() {
    // Skip @
    _it.next();
    auto *annotation = new Annotation();

    if (!_it.has() || _it.current()->kind != Tk_Word) {
        // Expect word.
    }
    annotation->name = _it.current()->value;
    _it.next();


    return annotation;
}


Error SchemaTreeBuilder::takeInterfaceNameError(Token* keywordToken) {
    auto index = keywordToken->index;
    Error error = Error {
            .type = ERR_TYPE_SYNTAX,
            .syntaxErrorCode = SYNTAX_ERR_NO_TYPE_NAME,
            .message = fmt::format("Expect interface name at [{}, {}].", index.row(), index.col())
    };
    syntaxErrors.push_back(error);
    return error;
}

Error SchemaTreeBuilder::takeEntityNameError(Token* keywordToken) {
    auto index = keywordToken->index;
    Error error = Error {
            .type = ERR_TYPE_SYNTAX,
            .syntaxErrorCode = SYNTAX_ERR_NO_TYPE_NAME,
            .message = fmt::format("Expect entity name at [{}, {}].", index.row(), index.col())
    };
    syntaxErrors.push_back(error);
    return error;
}


Error SchemaTreeBuilder::takeDatabaseNameError(Token* keywordToken) {
    auto index = keywordToken->index;
    Error error = Error {
            .type = ERR_TYPE_SYNTAX,
            .syntaxErrorCode = SYNTAX_ERR_NO_TYPE_NAME,
            .message = fmt::format("Expect database name at [{}, {}].", index.row(), index.col())
    };
    syntaxErrors.push_back(error);
    return error;
}