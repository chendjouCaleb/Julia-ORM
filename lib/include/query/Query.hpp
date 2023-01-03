//
// Created by HP on 23/12/2022.
//

#ifndef JULIA_ORM_QUERY_HPP
#define JULIA_ORM_QUERY_HPP

#include <string>
#include <vector>
#include <map>
#include <schema/Entity.hpp>
#include <cassert>
#include <iostream>
#include "schema/DbSet.hpp"
#include "Include.hpp"

enum QueryKind {
    QK_SELECT,
    QK_INSERT,
    QK_DELETE,
    QK_UPDATE
};

class Query {
public:
    QueryKind kind;
    std::string statement;
    std::string dbSetName;
    std::string alias;
    std::map<Entity*, std::string> aliases;

    DbSet* dbSet;
    std::vector<QueryInclude*> includes;

    [[nodiscard]] std::string toString() const {
        assert(dbSet != nullptr);

        std::string value = "from ";
        value += alias + " in " + dbSet->name ;

        value += ";";

        return value;
    }
};


#endif //JULIA_ORM_QUERY_HPP
