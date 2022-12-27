//
// Created by HP on 19/12/2022.
//

#include "SchemaTreeBuilder.hpp"


SchemaTreeBuilder SchemaTreeBuilder::create(std::vector<Token *> *tokens) {
    auto builder = SchemaTreeBuilder(Iterator<Token *>(tokens));
    return builder;
}

void SchemaTreeBuilder::build() {
    _schema = new DbSchema();
    while (_it.has()) {
        if (_it.current()->kind == Tk_Word && _it.current()->value == L"database") {
            takeDatabase();
        }

        if (_it.current()->kind == Tk_Word && _it.current()->value == L"entity") {
            auto entity = takeEntity();
            _schema->entities.push_back(entity);
        }
    }
}

void SchemaTreeBuilder::takeDatabase() {
    // skip database keyword.
    auto db = new Database();
    _it.next();
    if (!_it.has() || _it.current()->kind != Tk_Word) {
        // Expect db name
    }
    db->name = _it.current()->value;
    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_BraceOpen) {
        // Expect brace open.
    }
    _it.next();

    while (_it.has() && _it.current()->kind == Tk_Word && _it.current()->value == L"dbset") {
        std::wcout << _it.current()->value << std::endl;
        auto dbSet = takeDbSet();
        db->dbSets.push_back(dbSet);
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

    if (!_it.has() || _it.current()->kind != Tk_SymbolOperator || _it.current()->value != L"<") {
        // Expect chevron open.
    }

    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_Word) {
        // Expect entity type name.
    }

    dbSet->entityName = _it.current()->value;
    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_SymbolOperator || _it.current()->value != L">") {
        // Expect chevron close.
    }
    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_Word) {
        // Expect dbset name.
    }
    dbSet->name = _it.current()->value;
    _it.next();
    std::wcout << _it.current()->value << std::endl;
    if (!_it.has() || _it.current()->kind != Tk_SemiColon) {
        // Expect ;.
    }
    _it.next();
    return dbSet;
}

Entity *SchemaTreeBuilder::takeEntity() {
    // skip entity keyword.
    auto entity = new Entity();
    _it.next();
    if (!_it.has() || _it.current()->kind != Tk_Word) {
        // Expect entity name
    }
    entity->name = _it.current()->value;
    _it.next();

    if (!_it.has() || _it.current()->kind != Tk_BraceOpen) {
        // Expect brace open.
    }
    _it.next();

    while (_it.has() && _it.current()->kind != Tk_BraceClose) {
        auto field = takeField();
        entity->fields.push_back(field);
    }

    if (!_it.has() || _it.current()->kind != Tk_BraceClose) {
        // Expect brace close.
    }
    _it.next();

    return entity;
}

Field *SchemaTreeBuilder::takeField() {
    auto *field = new Field();

    field->annotations = takeAnnotations();
    field->name = _it.current()->value;
    _it.next();

    if (!_it.has() || _it.current()->value != L":") {
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

