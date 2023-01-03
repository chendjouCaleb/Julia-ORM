//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_DBSET_HPP
#define JULIA_ORM_DBSET_HPP
#include <string>
#include "Entity.hpp"

class DbSet {
public:
    std::string name;
    std::string entityName;
    Entity* entity;

    [[nodiscard]] std::string toString() const {
        return "dbset<" + entityName + "> " + name + ";";
    }
};


#endif //JULIA_ORM_DBSET_HPP
