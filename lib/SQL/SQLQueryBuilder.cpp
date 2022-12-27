//
// Created by HP on 23/12/2022.
//

#include "SQL/SqlQueryBuilder.hpp"
#include <string>
#include <sstream>

std::wstring SQLQueryBuilder::build(Query *query) {
    std::wstringstream result;
    result << L"SELECT * FROM " << query->entity->name;

    return result.str();
}