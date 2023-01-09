//
// Created by HP on 07/01/2023.
//

#ifndef JULIA_ORM_TYPECALL_HPP
#define JULIA_ORM_TYPECALL_HPP

#include <string>
#include <fmt/format.h>
#include "BasicType.hpp"
#include "schema/Entity.hpp"
#include "Entity.hpp"

class TypeCall {
public:
    std::string typeName;
    BasicType basicType;
    bool isArray;

    std::string toString() {
        std::string text = fmt::format(": {}", typeName);
        if(isArray) {
            text += "[]";
        }

        return text;
    }
};


#endif //JULIA_ORM_TYPECALL_HPP
