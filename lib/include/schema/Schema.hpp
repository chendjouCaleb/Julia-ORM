//
// Created by HP on 20/12/2022.
//

#ifndef JULIA_ORM_SCHEMA_HPP
#define JULIA_ORM_SCHEMA_HPP

#include <vector>
#include <iostream>
#include "schema/Database.hpp"
#include "schema/Entity.hpp"

class DbSchema {

public:
    std::vector<Entity*> entities;
    Database* database = nullptr;
    Entity* findEntity(std::wstring name){
       // std::wcout << "count: "<< entities.size() << std::endl;
        for (const auto &item : entities){
            if(item->name == name) {
                //std::wcout << "find: "<< item->name << std::endl;
                return item;

            }
        }

        return nullptr;
    }
};


#endif //JULIA_ORM_SCHEMA_HPP
