//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_DBSET_HPP
#define JULIA_ORM_DBSET_HPP
#include <string>
#include "Entity.hpp"

class DbSet {
public:
    std::wstring name;
    std::wstring entityName;
    Entity* entity;

    [[nodiscard]] std::wstring toString() const {
        return L"dbset<" + entityName + L"> " + name + L";";
    }
};


#endif //JULIA_ORM_DBSET_HPP
