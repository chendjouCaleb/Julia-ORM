//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_DATABASE_HPP
#define JULIA_ORM_DATABASE_HPP

#include <string>
#include <vector>
#include "DbSet.hpp"

class Database {
public:
    std::wstring name;
    std::vector<DbSet*> dbSets;

    std::wstring toString() {
        std::wstring value = L"database " + name + L" {\n";

        for(auto set: dbSets) {
            value.append(L"    " + set->toString() + L"\n");
        }

        value.append(L"}");

        return value;
    }
};


#endif //JULIA_ORM_DATABASE_HPP
