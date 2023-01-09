//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_SCHEMATREEBUILDER_HPP
#define JULIA_ORM_SCHEMATREEBUILDER_HPP


#include <schema/Schema.hpp>
#include <schema/DbSet.hpp>
#include <schema/TypeBlock.hpp>
#include <julia_orm/Error.hpp>
#include "Token.hpp"
#include "../tools/Iterator.hpp"

class SchemaTreeBuilder {
private:
    Iterator<Token*> _it;
    DbSchema* _schema;

public:
    std::vector<Error> syntaxErrors;
    std::vector<Error> schemaErrors;

public:
    explicit SchemaTreeBuilder(Iterator<Token*> it) : _it(it), _schema(nullptr) {
    }


    static SchemaTreeBuilder create(std::vector<Token*>* tokens);

    void build();

    bool hasError();

    void takeDatabase();
    Entity* takeEntity();
    Field* takeField();
    DbSet* takeDbSet();
    Interface* takeInterface();
    TypeCall* takeTypeCall();
    TypeBlock takeBlock();


    Annotation* takeAnnotation();
    std::vector<Annotation*> takeAnnotations();

    Error takeInterfaceNameError(Token* lastToken);
    Error takeEntityNameError(Token* lastToken);
    Error takeDatabaseNameError(Token* lastToken);
    Error takeBlockBraceOpenError(Token* token);
    Error takeBlockBraceCloseError(Token* token);
    Error takeUnknownTokenError(Token* token);

    Error takeFieldNameError(Token* token);
    Error takeFieldColonError(Token* token);
    Error takeFieldTypeError(Token* token);

    Error takeSemiColonError(Token* token);

    Error takeTypeArrayCloseError(Token* token);

    Error takeDbSetTypeError(Token *token);
    Error takeDbSetNameError(Token* token);
    Error takeDbSetTypeOpenError(Token* token);
    Error takeDbSetTypeCloseError(Token* token);

    DbSchema* schema() {
        return _schema;
    }
};


#endif //JULIA_ORM_SCHEMATREEBUILDER_HPP
