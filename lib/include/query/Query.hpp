//
// Created by HP on 23/12/2022.
//

#ifndef JULIA_ORM_QUERY_HPP
#define JULIA_ORM_QUERY_HPP

#include <string>
#include <vector>
#include <map>
#include <schema/Entity.hpp>
#include "Include.hpp"

class Query {
public:
    std::wstring entityName;
    std::wstring alias;
    std::map<Entity*, std::string> aliases;

    Entity* entity;
    std::vector<QueryInclude*> includes;

    std::wstring toString() {
        std::wstring value = L"from ";
        value += alias + L" in " + entity->name;


        return value;
    }
};


#endif //JULIA_ORM_QUERY_HPP
