//
// Created by HP on 20/12/2022.
//

#ifndef JULIA_ORM_SCHEMA_HPP
#define JULIA_ORM_SCHEMA_HPP

#include <vector>
#include "schema/Database.hpp"
#include "schema/Entity.hpp"

class DbSchema {

public:
    std::vector<Entity*> entities;
    Database* database = nullptr;
};


#endif //JULIA_ORM_SCHEMA_HPP
