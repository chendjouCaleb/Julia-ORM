//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_SCHEMATREEBUILDER_HPP
#define JULIA_ORM_SCHEMATREEBUILDER_HPP


#include <schema/Schema.hpp>
#include <schema/DbSet.hpp>
#include <schema/TypeBlock.hpp>
#include "Token.hpp"
#include "../tools/Iterator.hpp"

class SchemaTreeBuilder {
private:
    Iterator<Token*> _it;
    DbSchema* _schema;

public:
    explicit SchemaTreeBuilder(Iterator<Token*> it) : _it(it), _schema(nullptr) {
    }


    static SchemaTreeBuilder create(std::vector<Token*>* tokens);

    void build();

    void takeDatabase();
    Entity* takeEntity();
    Field* takeField();
    DbSet* takeDbSet();
    Interface* takeInterface();
    TypeBlock takeBlock();

    Annotation* takeAnnotation();
    std::vector<Annotation*> takeAnnotations();

    DbSchema* schema() {
        return _schema;
    }
};


#endif //JULIA_ORM_SCHEMATREEBUILDER_HPP
