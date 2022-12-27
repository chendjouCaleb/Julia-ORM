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
    FT_CHAR
};

class Field {
public:
    std::wstring name;
    std::wstring typeName;
    FieldType basicType;

    std::vector<Annotation*> annotations;

    [[nodiscard]] std::wstring toString() const {
        std::wstring value;

        for (auto annotation: annotations) {
            value += annotation->toString() + L" ";
        }

        return value + name + L": " + typeName + L";";
    }
};


#endif //JULIA_ORM_FIELD_HPP
