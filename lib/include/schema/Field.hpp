//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_FIELD_HPP
#define JULIA_ORM_FIELD_HPP

#include <string>
#include <schema/Entity.hpp>
#include "Annotation.hpp"
#include "BasicType.hpp"
#include "TypeCall.hpp"

class Field {
public:
    std::string name;
    std::string typeName;
    TypeCall *type;


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
