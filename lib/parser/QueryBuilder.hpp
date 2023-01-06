//
// Created by HP on 27/12/2022.
//

#ifndef JULIA_ORM_QUERYBUILDER_HPP
#define JULIA_ORM_QUERYBUILDER_HPP


#include <schema/Schema.hpp>
#include <query/Query.hpp>
#include <julia_orm/Error.hpp>
#include "Token.hpp"
#include "../tools/Iterator.hpp"

struct QueryResult {
    Query query;
    Query* query_ptr;
    std::string sql;
    std::vector<Error> errors;
};

class QueryBuilder {
    DbSchema* schema;
    std::vector<Token*> tokens;
    Iterator<Token*> _it;

public:
    Query query;

public:
    QueryBuilder(DbSchema *schema, std::vector<Token*> tokens);

    static QueryBuilder create(DbSchema *schema, std::string);

    void parse();

    void takeSelect();

};


#endif //JULIA_ORM_QUERYBUILDER_HPP
