#include <iostream>
#include <DbContext.hpp>
#include "lib/parser/Tokenizer.hpp"
#include "lib/parser/SchemaTreeBuilder.hpp"

int main() {
    auto query_text = L"from u in users include u.books where (u.age >= 10)";
    auto schema_text = L"database BookShop { \n"
                       "    dbset<Books> books; \n"
                       "    dbset<Authors> authors;\n "
                       "}\n"
                       "entity Book { @Auto @PrimaryKey id: int; title: String; subTitle: String? author: Author }\n"
                       "entity Author { @PrimaryKey id: int; name: string ; books: Book[] }";

    auto schema_text2 = "database DbName {dbset<Book> books; dbset<Author> authors;}"
                        "entity Book { @Auto @PrimaryKey id: int; title: string; subTitle: string; author: Author; authorId: int; }"
                        "entity Author { id: int; name: string;}"
                        ;
    float a = .8;
    Tokenizer tokenizer = Tokenizer::create(schema_text2);
    tokenizer.tokenize();
    std::vector<Token*> tokens = tokenizer.getTokens();
//    Iterator<Token*> iterator = Iterator(&tokens);
//    while (iterator.has()) {
//        std::wcout << iterator.current()->value << std::endl;
//        iterator.next();
//    }
//    std::wcout << "Length : " << tokens.size() << std::endl;
//    for (auto token:tokens) {
//        std::wcout << token->value << std::endl;
//    }

    auto schemaBuilder = SchemaTreeBuilder::create(&tokens);
    schemaBuilder.build();
    auto schema = schemaBuilder.schema();

//    std::wcout << schema->database->toString() << std::endl;
//
//    for (auto entity: schema->entities) {
//        std::wcout << entity->toString() << std::endl;
//    }

    DbContextCreateResult buildResult = DbContext::create(schema_text2);

    DbContext* dbContext = buildResult.dbContext;

    std::cout << "This is Db Schema: " << std::endl;
    std::cout << dbContext->schema->database->toString() << std::endl;

    QueryResult queryResult = dbContext->toSQL("from b in books;");
    std::cout << "Query: " << queryResult.sql << std::endl;
    return 0;
}
