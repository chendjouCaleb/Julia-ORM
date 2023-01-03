//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_ANNOTATION_HPP
#define JULIA_ORM_ANNOTATION_HPP

#include <string>

class Annotation {
public:
    std::string name;

    [[nodiscard]] std::string toString() const {
        return "@" + name + "()";
    }
};


#endif //JULIA_ORM_ANNOTATION_HPP
