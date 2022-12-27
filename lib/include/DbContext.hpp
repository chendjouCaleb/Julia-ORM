//
// Created by HP on 27/12/2022.
//

#ifndef JULIA_ORM_DBCONTEXT_HPP
#define JULIA_ORM_DBCONTEXT_HPP

#include "schema/Schema.hpp"

typedef class DbContext DbContext;

struct DbContextCreateResult {
    DbContext *dbContext;
    std::vector<Error> errors;

    bool isSuccess() {
        return errors.size() == 0;
    }
};

struct QueryResult {
    DbContext *dbContext;
    std::vector<Error> errors;
};

class DbContext {
public:
    Schema* schema;

    static DbContextCreateResult build(std::wstring schema);

    static void destroy(DbContext* context);

    QueryResult toSQL(std::wstring text);


};

#endif //JULIA_ORM_DBCONTEXT_HPP
