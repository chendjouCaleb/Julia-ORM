//
// Created by HP on 23/12/2022.
//

#include "SQL/SqlQueryBuilder.hpp"
#include <string>
#include <sstream>
#include <algorithm>

std::string SQLQueryBuilder::build(Query *query) {
    assert(query != nullptr);

    std::stringstream result;
    std::string alias = query->dbSet->name.substr(0, 1);

    std::string select;

    auto fields = query->dbSet->entity->fields;
    std::cout << "Alias: " << alias << std::endl;
    std::cout << "Fields count: " << fields.size() << alias << std::endl;

    for (int i = 0; i < fields.size(); ++i) {
        select += alias + "." + fields[i]->name;
        if(i < fields.size() -1 ) {
            select += ", ";
        }
    }

    result << "SELECT " + select + " FROM " << query->dbSet->entity->name + " AS " + alias;

    return result.str();
}