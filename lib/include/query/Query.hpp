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
    std::wstring statement;
    std::wstring dbSetName;
    std::wstring alias;
    std::map<Entity*, std::string> aliases;

    DbSet* dbSet;
    std::vector<QueryInclude*> includes;

    std::wstring toString() const {
        std::wstring value = L"from ";
        //assert(dbSet != nullptr, "dbSet cannot be null.");

        std::wcout << (dbSet == nullptr) << std::endl;
        value += alias + L" in " + dbSet->name ;

        value += L";";

        return value;
    }
};


#endif //JULIA_ORM_QUERY_HPP
