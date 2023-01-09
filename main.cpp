#include <iostream>
#include <windows.h>
#include <julia_orm/DbContext.hpp>
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

    std::string schema_text2 = R"(
                        database DbName {dbset <Book> books; dbset<Author> authors;}
                       interface PrimaryKey { id: int; name: string; }
                       entity Book{ @Auto @PrimaryKey id: int; title: string; subTitle: string; author: Author; authorId: int; }
                       entity Author { id: int; name: string; books: Book [];})"
                        ;
//    float a = .8;
//    Tokenizer tokenizer = Tokenizer::create(schema_text2);
//    tokenizer.tokenize();
//    std::vector<Token*> tokens = tokenizer.getTokens();
//    Iterator<Token*> iterator = Iterator(&tokens);
//    while (iterator.has()) {
//        std::wcout << iterator.current()->value << std::endl;
//        iterator.next();
//    }
//    std::wcout << "Length : " << tokens.size() << std::endl;
//    for (auto token:tokens) {
//        std::wcout << token->value << std::endl;
//    }

//    auto schemaBuilder = SchemaTreeBuilder::create(&tokens);
//    schemaBuilder.build();
//    auto schema = schemaBuilder.schema();

//    std::wcout << schema->database->toString() << std::endl;
//
//    for (auto entity: schema->entities) {
//        std::wcout << entity->toString() << std::endl;
//    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DbContextCreateResult buildResult = DbContext::create(schema_text2);

    if(!buildResult.isSuccess()) {
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << buildResult.syntaxErrors.size() << " errors in your db schema." << std::endl;
        for (auto error : buildResult.syntaxErrors) {
            std::cout << "    > " << error.message << std::endl;
        }

        return 0;
    } else {
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << "Your db schema is ok!" << std::endl;
        SetConsoleTextAttribute(hConsole, 7);
    }

    DbContext* dbContext = buildResult.dbContext;

    std::cout << "This is Db Schema: " << std::endl;
    std::cout << dbContext->schema->database->toString() << std::endl;

    QueryResult queryResult = dbContext->toSQL("from b in books;");
    std::cout << "Query: " << queryResult.sql << std::endl;
    return 0;
}
