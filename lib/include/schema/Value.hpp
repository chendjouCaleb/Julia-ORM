//
// Created by HP on 19/12/2022.
//

#ifndef JULIA_ORM_VALUE_HPP
#define JULIA_ORM_VALUE_HPP

enum ValueType {
    VT_INT,
    VT_DOUBLE,
    VT_STRING,
    VT_CHAR
};

class Value {
public:

    Value(ValueType type, void* ptr_value):type(type), ptr_value(ptr_value) {

    }

    void* ptr_value;
    ValueType type;
};


#endif //JULIA_ORM_VALUE_HPP
