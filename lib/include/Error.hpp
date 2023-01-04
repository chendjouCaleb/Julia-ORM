//
// Created by HP on 20/12/2022.
//

#ifndef JULIA_ORM_ERROR_HPP
#define JULIA_ORM_ERROR_HPP

enum ErrorType {
    ERR_TYPE_SYNTAX,
    ERR_TYPE_QUERY,
    ERR_TYPE_SCHEMA
};

enum SyntaxErrorCode {
    SYNTAX_ERR_EMPTY = 0,
    SYNTAX_ERR_UNEXPECTED_CHAR,
    SYNTAX_ERR_UNEXPECTED_TOKEN
};

enum QueryErrorCode {
    QUERY_ERR_UNEXPECTED_EMPTY = 0,
    QUERY_ERR_UNEXPECTED_CHAR,
    QUERY_ERR_UNEXPECTED_TOKEN
};

enum SchemaErrorCode {
    SCHEMA_ERR_UNKNOWN_EMPTY = 0,
    SCHEMA_ERR_UNKNOWN_DB_SET,
};

struct Error {
    ErrorType type;
    SchemaErrorCode code = SCHEMA_ERR_UNKNOWN_EMPTY;
    QueryErrorCode queryErrorCode = QUERY_ERR_UNEXPECTED_EMPTY;
    SyntaxErrorCode syntaxErrorCode = SYNTAX_ERR_EMPTY;
    std::string message;
};


#endif //JULIA_ORM_ERROR_HPP
