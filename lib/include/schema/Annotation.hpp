//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_ANNOTATION_HPP
#define JULIA_ORM_ANNOTATION_HPP

#include <string>
#include <fmt/format.h>

class Annotation {
public:
    std::string name;

    [[nodiscard]] std::string toString() const {
        auto text = fmt::format("@{}", name);
        return text;
    }
};


#endif //JULIA_ORM_ANNOTATION_HPP
