//
// Created by HP on 23/12/2022.
//

#include "SQL/SqlQueryBuilder.hpp"
#include <string>
#include <sstream>
#include <algorithm>

std::wstring SQLQueryBuilder::build(Query *query) {
    assert(query != nullptr);

    std::wstringstream result;
    std::wstring alias = query->dbSet->name.substr(0, 1);

    std::wstring select;

    auto fields = query->dbSet->entity->fields;
    std::wcout << "Alias: " << alias << std::endl;
    std::wcout << "Fields count: " << fields.size() << alias << std::endl;

    for (int i = 0; i < fields.size(); ++i) {
        select += alias + L"." + fields[i]->name;
        if(i < fields.size() -1 ) {
            select += L", ";
        }
    }

    result << L"SELECT " + select + L" FROM " << query->dbSet->entity->name + L" AS " + alias;

    return result.str();
}