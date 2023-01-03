//
// Created by HP on 27/12/2022.
//

#ifndef JULIA_ORM_DBCONTEXT_HPP
#define JULIA_ORM_DBCONTEXT_HPP

#include "schema/Schema.hpp"
#include "Error.hpp"
#include "../parser/QueryBuilder.hpp"

typedef class DbContext DbContext;

struct DbContextCreateResult {
    DbContext *dbContext;
    std::vector<Error> lexerErrors;
    std::vector<Error> syntaxErrors;
    std::vector<Error> schemaErrors;

    bool isSuccess() {
        return lexerErrors.empty() && syntaxErrors.empty() && schemaErrors.empty();
    }
};



class DbContext {
public:
    DbSchema* schema;

    static DbContextCreateResult create(std::string schema);
    static void destroy(DbContext* context);

    QueryResult toSQL(std::string text);
    QueryResult query(std::string text);
};

#endif //JULIA_ORM_DBCONTEXT_HPP
