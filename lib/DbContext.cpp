//
// Created by HP on 27/12/2022.
//

#include "DbContext.hpp"

#include <utility>
#include <SQL/SqlQueryBuilder.hpp>
#include "parser/Tokenizer.hpp"
#include "parser/SchemaTreeBuilder.hpp"

DbContextCreateResult DbContext::create(std::string schema) {
    std::cout << schema << std::endl;
    Tokenizer tokenizer = Tokenizer::create(std::move(schema));

    auto tokens = tokenizer.tokenize();

    std::cout << "Schema tokenized." << std::endl;

    SchemaTreeBuilder schemaBuilder = SchemaTreeBuilder::create(&tokens);
    schemaBuilder.build();

    std::cout << "Schema built." << std::endl;
    auto* dbContext = new DbContext();
    dbContext->schema = schemaBuilder.schema();

    DbContextCreateResult result = DbContextCreateResult {};
    result.dbContext = dbContext;

    return result;
}

QueryResult DbContext::toSQL(std::string queryText) {
    QueryBuilder builder = QueryBuilder::create(schema, std::move(queryText));
    builder.parse();

    SQLQueryBuilder sqlQueryBuilder = SQLQueryBuilder::create();
    auto sql = sqlQueryBuilder.build(&builder.query);

    QueryResult queryResult {.query = builder.query, .sql = sql};

    return queryResult;
}

QueryResult DbContext::query(std::string queryText) {
    QueryBuilder builder = QueryBuilder::create(schema, std::move(queryText));
    builder.parse();

    QueryResult queryResult{.query = builder.query};

    return queryResult;
}

void DbContext::destroy(DbContext* context) {
    delete context;
}




