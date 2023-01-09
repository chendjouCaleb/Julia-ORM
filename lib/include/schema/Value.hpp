//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_VALUE_HPP
#define JULIA_ORM_VALUE_HPP

#include "BasicType.hpp"

class Value {
public:

    Value(BasicType type, void* ptr_value): type(type), ptr_value(ptr_value) {

    }

    void* ptr_value;
    BasicType type;
};


#endif //JULIA_ORM_VALUE_HPP
