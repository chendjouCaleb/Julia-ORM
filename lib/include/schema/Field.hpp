//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_FIELD_HPP
#define JULIA_ORM_FIELD_HPP

#include <string>
#include <schema/Entity.hpp>
#include "Annotation.hpp"

enum FieldType {
    FT_INT,
    FT_DOUBLE,
    FT_STRING,
    FT_CHAR,
    FT_BOOLEAN
};

class Field {
public:
    std::string name;
    std::string typeName;
    FieldType basicType;

    std::vector<Annotation*> annotations;

    [[nodiscard]] std::string toString() const {
        std::string value;

        for (auto annotation: annotations) {
            value += annotation->toString() + " ";
        }

        return value + name + ": " + typeName + ";";
    }
};


#endif //JULIA_ORM_FIELD_HPP
