//
// Created by HP on 03/01/2023.
//

#ifndef JULIA_ORM_TYPEBLOCK_HPP
#define JULIA_ORM_TYPEBLOCK_HPP

#include <string>
#include <vector>

class TypeBlock {
public:
    std::string name;
    std::vector<Field*> fields;
};


#endif //JULIA_ORM_TYPEBLOCK_HPP
