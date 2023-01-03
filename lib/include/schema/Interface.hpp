//
// Created by HP on 03/01/2023.
//

#ifndef JULIA_ORM_INTERFACE_HPP
#define JULIA_ORM_INTERFACE_HPP

#include <string>
#include <vector>

class Interface {
    std::string name;
    std::vector<Field*> fields;

    std::string toString() {
        std::string value = "interface " + name + " {\n";

        for(auto field: fields) {
            value.append("    " + field->toString() + "\n");
        }

        value.append("}");

        return value;
    }
};

#endif //JULIA_ORM_INTERFACE_HPP
