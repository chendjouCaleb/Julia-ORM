//
// Created by HP on 23/12/2022.
//

#ifndef JULIA_ORM_SQLQUERYBUILDER_HPP
#define JULIA_ORM_SQLQUERYBUILDER_HPP

#include <string>
#include <query/Query.hpp>

class SQLQueryBuilder {
public:
    std::string build(Query* query);

    static SQLQueryBuilder create() {
        return SQLQueryBuilder();
    }
};


#endif //JULIA_ORM_SQLQUERYBUILDER_HPP
