//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_ENTITY_HPP
#define JULIA_ORM_ENTITY_HPP

#include <string>
#include <vector>
#include "Field.hpp"

class Entity {
public:
    std::string name;
    std::vector<Field*> fields;

    std::string toString() {
        std::string value = "entity " + name + " {\n";

        for(auto field: fields) {
            value.append("    " + field->toString() + "\n");
        }

        value.append("}");

        return value;
    }
};


#endif //JULIA_ORM_ENTITY_HPP
