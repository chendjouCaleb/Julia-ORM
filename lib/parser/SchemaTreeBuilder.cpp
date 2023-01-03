//
// Created by HP on 19/12/2022.
//

#include <cassert>
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

        if (_it.current()->kind == Tk_Word && _it.current()->value == "entity") {
            auto entity = takeEntity();
            _schema->entities.push_back(entity);
        }
    }

    for (const auto &item : _schema->database->dbSets) {
        item.second->entity = _schema->findEntity(item.second->entityName);
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

Interface* SchemaTreeBuilder::takeInterface() {
    auto interface = new Interface();

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
Entity *SchemaTreeBuilder::takeEntity() {
    // skip entity keyword.
    _it.next();
    TypeBlock block = takeBlock();

    auto* entity = new Entity();
    entity->name = block.name;
    entity->fields = block.fields;

    return entity;
}
void takeEntity1() {
//    // skip entity keyword.
//    auto entity = new Entity();
//    _it.next();
//    if (!_it.has() || _it.current()->kind != Tk_Word) {
//        // Expect entity name
//    }
//    entity->name = _it.current()->value;
//    _it.next();
//
//    if (!_it.has() || _it.current()->kind != Tk_BraceOpen) {
//        // Expect brace open.
//    }
//    _it.next();
//
//    while (_it.has() && _it.current()->kind != Tk_BraceClose) {
//        auto field = takeField();
//        entity->fields.push_back(field);
//    }
//
//    if (!_it.has() || _it.current()->kind != Tk_BraceClose) {
//        // Expect brace close.
//    }
//    _it.next();
//
//    return entity;
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

