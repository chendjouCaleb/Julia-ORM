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
    std::wstring name;
    std::vector<Field*> fields;

    std::wstring toString() {
        std::wstring value = L"entity " + name + L" {\n";

        for(auto field: fields) {
            value.append(L"    " + field->toString() + L"\n");
        }

        value.append(L"}");

        return value;
    }
};


#endif //JULIA_ORM_ENTITY_HPP
