//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_DATABASE_HPP
#define JULIA_ORM_DATABASE_HPP

#include <string>
#include <vector>
#include <map>
#include "DbSet.hpp"

class Database {
public:
    std::string name;
    std::map<std::string, DbSet*> dbSets;


    bool hasDbSet(const std::string& dbSetName) {
        return dbSets.find(dbSetName) != dbSets.end();
    }

    std::string toString() {
        std::string value = "database " + name + " {\n";

        for(auto &set: dbSets) {
            value.append("    " + set.second->toString() + "\n");
        }

        value.append("}");

        return value;
    }
};


#endif //JULIA_ORM_DATABASE_HPP
