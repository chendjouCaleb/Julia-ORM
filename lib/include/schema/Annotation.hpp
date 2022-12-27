//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_ANNOTATION_HPP
#define JULIA_ORM_ANNOTATION_HPP

#include <string>

class Annotation {
public:
    std::wstring name;

    [[nodiscard]] std::wstring toString() const {
        return L"@" + name + L"()";
    }
};


#endif //JULIA_ORM_ANNOTATION_HPP
